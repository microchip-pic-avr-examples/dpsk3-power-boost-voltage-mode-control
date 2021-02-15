/*
 * File:   dev_boost_converter.c
 * Author: M91406
 *
 * Created on July 9, 2019, 1:10 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types header file
#include <stdbool.h> // include standard boolean types header file

#include "dev_boost_typedef.h"
#include "dev_boost_opstates.h"
#include "dev_boost_pconfig.h"

/*******************************************************************************
 * @fn	volatile uint16_t drv_BoostConverter_Initialize(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-converter-functions-public
 * @brief   This function initializes all peripheral modules and their instances used by the power controller
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 *  
 * @details
 * This function initializes the PWM module, PWM channels, ADC channels for temperature,
 *  input voltage, output voltage and phase current. The boost IO pins are also initialize
 * while keeping the boost converter operation disabled. The state machine is set to Initialize. 
 *********************************************************************************/

volatile uint16_t drv_BoostConverter_Initialize(volatile struct BOOST_CONVERTER_s *boostInstance) 
{
    volatile uint16_t retval = 1;
    volatile uint16_t _i=0;
    
    retval &= boostPWM_ModuleInitialize(boostInstance); // Initialize PWM Module
    retval &= boostPWM_ChannelInitialize(boostInstance);  // Initialize PWM Channel of Boost Converter
    
    retval &= boostADC_ModuleInitialize();     // Initialize ADC Module
    
    retval &= boostADC_ChannelInitialize(&boostInstance->feedback.ad_temp); // Initialize Temperature Channel
    retval &= boostADC_ChannelInitialize(&boostInstance->feedback.ad_vin);  // Initialize Input Voltage Channel
    retval &= boostADC_ChannelInitialize(&boostInstance->feedback.ad_vout); // Initialize Output Voltage Channel
    
    for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) // Reset phase current values
        retval &= boostADC_ChannelInitialize(&boostInstance->feedback.ad_isns[_i]); // Initialize Phase Current Channel
    
    retval &= boostGPIO_Initialize(boostInstance); // Initialize additional control IOs

    
    boostInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) { // In current mode...
     
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) // Reset phase current values
        { boostInstance->i_loop[_i].controller->status.bits.enabled = false; } // Disable current loop
    
    }
        
    boostInstance->status.bits.enabled = false;  // Disable Boost Converter
    boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE; // Reset state machine
    
    return(retval);
}

/*******************************************************************************
 * @fn	volatile uint16_t drv_BoostConverter_Execute(volatile struct BOOST_CONVERTER_s * boostInstance)
 * @ingroup lib-layer-boost-converter-functions-public
 * @brief   This function is the main boost converter state machine executing the most recent state 
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  0 = BOOST_OPSRET_REPEAT
 * @return  1 = BOOST_OPSRET_COMPLETE
 * @return  2 = BOOST_OPSRET_REPEAT
 *
 * @details
 * This function performs tasks in the state machine.  
 *  - If state machine state returns ERROR, switch to ERROR state in next execution cycle
 *  - If state machine state signals state completion, move on to next state in line
 *  - When state machine state returns REPEAT, the recent state function will be called again
 *  - When state machine state returns an unknown result, the state machine will be reset to INITIALIZE again 
 *********************************************************************************/

volatile uint16_t drv_BoostConverter_Execute(volatile struct BOOST_CONVERTER_s *boostInstance) 
{
    volatile uint16_t retval=1;
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* NULL POINTER PROTECTION                                                            */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // If no boost instance has been declared, leave here
    if(boostInstance == NULL)
        return(0);
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* CAPTURE ENABLE PIN STATE IF ENABLED BY USER CODE                                   */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(boostInstance->gpio.EnableInput.enabled)
    {
        // Capture Enable Input pin status (1=high, 0=low)
        uint16_t pin_state = boostGPIO_GetPinState(&boostInstance->gpio.EnableInput);
        
        if(!boostInstance->gpio.EnableInput.polarity)
        // If POLARITY setting 0 = Active High (default)
            boostInstance->status.bits.enabled = (bool)(pin_state == 1);
        else
        // If POLARITY setting 1 = Active Low
            boostInstance->status.bits.enabled = (bool)(pin_state == 0);
    }
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* DISABLE/SUSPEND/FAULT-RESET                                                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // When enable status has changed from ENABLED to DISABLED or a fault condition 
    // is active, reset the state machine and hold it in RESET state
    if ((!boostInstance->status.bits.enabled) || (boostInstance->status.bits.suspend) ||
        (boostInstance->status.bits.fault_active))
    {
        if (!boostInstance->status.bits.ready)
            boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE;
        else
            boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_RESET;
        
        // Call most recent state
        retval = BoostConverterStateMachine[boostInstance->state_id.bits.opstate_id](boostInstance);
        
        return((bool)(retval>0)); // Return
    }    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* FUNCTION CALL PROTECTION                                                           */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // If the state array pointer is out of range, roll over and start from first 
    // valid state
    if(boostInstance->state_id.bits.opstate_id >= BoostStateList_size)
        boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE;
    
    if (BoostConverterStateMachine[boostInstance->state_id.bits.opstate_id] == NULL)
        return(0);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Execute state machine step
    retval = BoostConverterStateMachine[boostInstance->state_id.bits.opstate_id](boostInstance);
    
    switch (retval) 
    {
        /* If state machine state returns ERROR, switch to ERROR state in next execution cycle */
        case BOOST_OPSRET_ERROR:
            
            boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE;
            retval = 0;
            break;
            
        /* IF state machine state signals state completion, move on to next state in line */
        case BOOST_OPSRET_COMPLETE:
            
            // Increment main operating state pointer by one tick
            boostInstance->state_id.value = (uint32_t)(boostInstance->state_id.bits.opstate_id++);
            
            // Check if new index is out of range, reset to RESET if so
            if (boostInstance->state_id.bits.opstate_id >= BoostStateList_size)
                boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_RESET;

            retval = 1;
            break;
            
        /* When state machine state returns REPEAT, the recent state function will be called again */
        case BOOST_OPSRET_REPEAT:
            // Do nothing, same state will be called next time
            retval = 1;
            break;
            
        /* When state machine state returns an unknown result, the 
         * state machine will be reset to INITIALIZE again */
        default:
            // In case an undefined return value has been received,
            // REset state machine and start from scratch
            boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE;
            retval = 0;
            break;
    }

    return(retval);
}

/*******************************************************************************
 * @fn	volatile uint16_t drv_BoostConverter_Start(volatile struct BOOST_CONVERTER_s * boostInstance)
 * @ingroup lib-layer-boost-converter-functions-public
 * @brief   This function starts the boost converter
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 *  
 * @details
 * This function starts the boost converter operation by enabling the the boost PWM and ADC peripherals, 
 * enabling the boost converter and reseting the state machine to Initialize. 
 *********************************************************************************/

volatile uint16_t drv_BoostConverter_Start(volatile struct BOOST_CONVERTER_s * boostInstance) {

    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    
    // Disable control loops
    boostInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    boostInstance->v_loop.ctrl_Reset(boostInstance->v_loop.controller); // Reset voltage loop histories

    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) { // In current mode...
        
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++)
        { 
            boostInstance->i_loop[_i].controller->status.bits.enabled = false; // Disable current loop
            boostInstance->i_loop[_i].ctrl_Reset(boostInstance->i_loop[_i].controller); // Reset current loop histories
        }
    }
    
    // Sequence PWM and ADC peripheral startup
    retval &= boostPWM_Start(boostInstance);   // Start PWM (All Outputs Disabled)
    if (retval) boostInstance->status.bits.pwm_active = 1; // IF PWM startup was successful, set PWM_ACTIVE flag
    retval &= boostADC_Start();              // Start ADC

    // Enable boost converter and reset state machine to INITIALIZE
    boostInstance->status.bits.enabled = true;   // Enable Boost Converter
    boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE; // Reset state machine

    return(retval);
}

/*******************************************************************************
 * @fn	volatile uint16_t drv_BoostConverter_Stop(volatile struct BOOST_CONVERTER_s * boostInstance)
 * @ingroup lib-layer-boost-converter-functions-public
 * @brief  This function stop the boost converter opration
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This function stops the boost converter operation by shutting down the PWM generator, 
 * disabling the voltage/current loop and reset the state machine to Initialize.
 * 
 *********************************************************************************/

volatile uint16_t drv_BoostConverter_Stop(volatile struct BOOST_CONVERTER_s *boostInstance) {

    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    
    // Stop PWM completely (shuts down PWM generator)
    retval &= boostPWM_Stop(boostInstance); // Stop PWM
    
    boostInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) {// In current mode...
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++)
        { boostInstance->i_loop[_i].controller->status.bits.enabled = false; } // Disable current loop
    }
    
    boostInstance->status.bits.enabled = false;  // Disable Boost Converter
    boostInstance->state_id.value = (uint32_t)BOOST_OPSTATE_INITIALIZE; // Reset state machine

    return(retval);
}

/*******************************************************************************
 * @ingroup lib-layer-boost-converter-functions-public
 * @fn	volatile uint16_t drv_BoostConverter_Suspend(volatile struct BOOST_CONVERTER_s * boostInstance)
 * @brief  This function suspends the operation of the boost converter
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 *
 * @details
 * This function sets the suspend bit terminating operation. This bit will be evaluated in the
 * State machine tasks which eventually shuts down the operation of the boost converter.
 *********************************************************************************/

volatile uint16_t drv_BoostConverter_Suspend(volatile struct BOOST_CONVERTER_s *boostInstance) {
    
    volatile uint16_t retval=1;
    
    boostInstance->status.bits.suspend = true;  // Set SUSPEND bit terminating operation
    retval &= drv_BoostConverter_Execute(boostInstance);  // Enforce state switch immediately
    
    return(retval);
}

/*******************************************************************************
 * @fn	volatile uint16_t drv_BoostConverter_Resume(volatile struct BOOST_CONVERTER_s * boostInstance)
 * @ingroup lib-layer-boost-converter-functions-public
 * @brief  This function resume the operation of the boost converter
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This function executes the latest task in the state machine enforcing state switch immediately.
 *********************************************************************************/

volatile uint16_t drv_BoostConverter_Resume(volatile struct BOOST_CONVERTER_s *boostInstance) {
    
    volatile uint16_t retval=1;
    
    boostInstance->status.bits.suspend = false;  // Reset running state machine
    retval &= drv_BoostConverter_Execute(boostInstance);  // Enforce state switch immediately
    
    return(retval);
}

// end of file
