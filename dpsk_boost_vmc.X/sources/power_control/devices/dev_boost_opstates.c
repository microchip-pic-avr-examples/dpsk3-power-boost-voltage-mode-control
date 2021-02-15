/*
 * File:   dev_boost_opstates.c
 * Author: M91406
 * Created on October 9, 2020, 9:16 AM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types

#include "dev_boost_pconfig.h" // include boost converter
#include "dev_boost_typedef.h" // include boost converter data object declarations
#include "dev_boost_substates.h" // include state machine sub-state declarations
#include "dev_boost_special_functions.h" // include boost converter special function declarations


// Private function prototypes of state functions

volatile uint16_t __attribute__((always_inline)) State_Error(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) State_Initialize(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) State_Reset(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) State_Standby(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) State_RampUp(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) State_Online(volatile struct BOOST_CONVERTER_s *boostInstance);

// Declaration of function pointer array listing op-state functions in order of execution
volatile uint16_t (*BoostConverterStateMachine[])(volatile struct BOOST_CONVERTER_s *boostInstance) = 
{
    State_Error,        ///< State #0: That's the blank "undefined default state", causing the state machine to reset
    State_Initialize,   ///< State #1: Initialize state machine by resetting all runtime flags to default
    State_Reset,        ///< State #2: Reset key runtime flags when power converter was already turned on
    State_Standby,      ///< State #3: After successful initialization, power converter waits to be launched
    State_RampUp,       ///< State #4: Topology-specific startup sub-states are handled in Ramp-Up function
    State_Online        ///< State #5: During normal operation the converter responds to changes in reference
};

// Declaration variable capturing the size of the sub-state function pointer array 
volatile uint16_t BoostStateList_size = (sizeof(BoostConverterStateMachine)/sizeof(BoostConverterStateMachine[0])); 

/*******************************************************************************
 * @fn uint16_t State_Initialize(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function resets the counters and conditional flag bits.
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 *
 * @details
 * If the controller has not been run yet, the POWER ON and POWER GOOD delay
 * counters are reset and all conditional flag bits are cleared. Status of 
 * power source, ADC and current sensor calibration have to be set during
 * runtime by system check routines. 
 *********************************************************************************/
volatile uint16_t State_Initialize(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t _i=0;
    
    boostInstance->startup.power_on_delay.counter = 0;   // Reset power on counter
    boostInstance->startup.power_good_delay.counter = 0; // Reset power good counter

    // Reset all status bits
    boostInstance->status.bits.adc_active = false;

    // Initiate current sensor calibration flag bit
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_VMC)
        boostInstance->status.bits.cs_calib_complete = true; 
    else if (boostInstance->status.bits.cs_calib_enable)
        boostInstance->status.bits.cs_calib_complete = false; 
    else 
        boostInstance->status.bits.cs_calib_complete = true; 
    
    // Disable control loops
    boostInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) // In current mode...
    {
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) {
            boostInstance->i_loop[_i].controller->status.bits.enabled = false; // Disable current loop
        }        
    }
    
    // Clear busy bit
    boostInstance->status.bits.busy = false; // Clear BUSY bit
    boostInstance->status.bits.ready = true; // Set READY bit indicating state machine has passed INITIALIZED state
    
    // Transition to STATE_RESET
    return(BOOST_OPSRET_COMPLETE); 
    
}

/*******************************************************************************
 * @fn uint16_t State_Reset(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function resets the boost control operation by re-initiating the control mode,
 * references and status bits. 
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * After successful initialization or after an externally triggered state machine reset,
 * the state machine returns to this RESET mode, re-initiating control mode, references 
 * and status bits before switching further into STANDBY mode. 
 *********************************************************************************/
volatile uint16_t State_Reset(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;

    // Disable all PWM outputs & control loops (immediate power cut-off)
    retval &= boostPWM_Suspend(boostInstance); // Disable PWM outputs
    
    // Disable voltage loop controller and reset control loop histories
    boostInstance->v_loop.controller->status.bits.enabled = false; // disable voltage control loop
    boostInstance->v_loop.ctrl_Reset(boostInstance->v_loop.controller); // Reset control histories of outer voltage controller
    *boostInstance->v_loop.controller->Ports.Target.ptrAddress = 
        boostInstance->v_loop.controller->Limits.MinOutput;

    // Disable current loop controller and reset control loop histories
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) 
    {   // Disable all current control loops and reset control loop histories
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) {
            boostInstance->i_loop[_i].controller->status.bits.enabled = false; 
            boostInstance->i_loop[_i].ctrl_Reset(boostInstance->i_loop[_i].controller); 
            *boostInstance->i_loop[_i].controller->Ports.Target.ptrAddress = 
                boostInstance->i_loop[_i].controller->Limits.MinOutput;
        }
    }

    // Reset the bulk voltage settling counters
    boostInstance->startup.power_on_delay.counter = 0; // Clear Power On Delay counter
    boostInstance->startup.power_good_delay.counter = 0; // Clear Power Good Delay counter

    // Reset all status bits
    boostInstance->status.bits.adc_active = false;
    boostInstance->status.bits.busy = false; // Clear BUSY bit
    
    // If any sub-function call went unsuccessful, reset state machine
    // else, move on to next state
    
    if (retval)
        return(BOOST_OPSRET_COMPLETE);
    else
        return(BOOST_OPSRET_ERROR);
    
}
                
/*******************************************************************************
 * @fn uint16_t State_Standby(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function waits until all start-up conditions are met.
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * After a successful state machine reset, the state machine waits in  
 * STANDBY mode until all conditional flag bits are set/cleared allowing  
 * the converter to run.
 *********************************************************************************/
volatile uint16_t State_Standby(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=0;

    // if the 'autorun' option is set, automatically set the GO bit when the 
    // converter is enabled
    if ((boostInstance->status.bits.enabled) && (boostInstance->status.bits.autorun))
    { boostInstance->status.bits.GO = true; }

    // If current sense feedback offset calibration is enabled, 
    // call calibration sub-state routine
    retval = drv_BoostConverter_SpecialFunctionExecute(boostInstance, CS_OFSET_CALIBRATION);
        
    switch (retval)
    {
        case BOOST_OPSRET_COMPLETE:
            boostInstance->status.bits.cs_calib_complete = true; // Set CS Calibration Flag to COMPLETE
            boostInstance->status.bits.busy = false; // Clear BUSY bit indicating on-going activity
            break;
        case BOOST_OPSRET_REPEAT:
            boostInstance->status.bits.cs_calib_complete = false; // Set CS Calibration Flag to COMPLETE
            boostInstance->status.bits.busy = true; // Set BUSY bit indicating on-going activity
            return(BOOST_OPSRET_REPEAT);
            break;
        default:
            boostInstance->status.bits.cs_calib_complete = false; // Set CS Calibration Flag to COMPLETE
            boostInstance->status.bits.busy = false; // Clear BUSY bit indicating on-going activity
            return(BOOST_OPSRET_ERROR);
            break;
    }

    // Wait for all startup conditions to be met
    if ((boostInstance->status.bits.enabled) &&          // state machine needs to be enabled
        (boostInstance->status.bits.GO) &&               // GO-bit needs to be set
        (boostInstance->status.bits.adc_active) &&       // ADC needs to be running
        (boostInstance->status.bits.pwm_active) &&       // PWM needs to be running 
        (!boostInstance->status.bits.fault_active) &&    // No active fault is present
        (!boostInstance->status.bits.suspend) &&         // Power supply is not held in suspend mode
        (boostInstance->status.bits.cs_calib_complete)   // Current Sensor Calibration complete
        )
    {
        boostInstance->status.bits.GO = false;
        return(BOOST_OPSRET_COMPLETE);
    }
    else
    // Remain in current state until bit-test becomes true
    {
        return(BOOST_OPSRET_REPEAT);
    }
    
}

/*******************************************************************************
 * @fn uint16_t State_RampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function ramps up the voltage/input to its nominal value
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  0 = BOOST_OPSRET_REPEAT
 * @return  1 = BOOST_OPSRET_COMPLETE
 * @return  2 = BOOST_OPSRET_REPEAT
 *
 * @details
 * After a successful state machine Standby, the state machine executes the RAMPUP 
 * mode. In this mode, the voltage/current ramps up to the nominal value.  
 *********************************************************************************/

volatile uint16_t State_RampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=0;
    
    // If sub-state pointer index is out of range, reset to ZERO
    if ((uint16_t)(boostInstance->state_id.bits.substate_id) >= (uint16_t)(BoostRampUpSubStateList_size))
        boostInstance->state_id.bits.substate_id = 0;
    
    // If selected sub-state index contains a NULL-pointer, exit here
    if (BoostConverterRampUpSubStateMachine[boostInstance->state_id.bits.substate_id] == NULL)
        return(BOOST_OPSRET_ERROR);
    
    // Execute ramp-up sub-state
    retval = BoostConverterRampUpSubStateMachine[boostInstance->state_id.bits.substate_id](boostInstance);
    
    // Validate sub-state function return
    switch (retval) 
    {   
        // If the sub-state returns a REPEAT, leave the sub-state pointer at the recent 
        // index and return REPEAT to the outer state machine to call State_RampUp again
        case BOOST_OPSRET_REPEAT:
            
            retval = BOOST_OPSRET_REPEAT;
            
            break;

        // If the sub-state returns a COMPLETE, increment the sub-state pointer to call the 
        // next sub-state next time and return REPEAT to the outer state machine to call
        // State_RampUp again
        case BOOST_OPSRET_COMPLETE:

            // Increment sub-state pointer by one tick
            boostInstance->state_id.bits.substate_id++;
            
            // CHeck if pointer is out of range
            if ((uint16_t)(boostInstance->state_id.bits.substate_id) < (uint16_t)(BoostRampUpSubStateList_size))
            { // if execution list is not complete yet, return op-state as REPEAT
                retval = BOOST_OPSRET_REPEAT;

                if (boostInstance->state_id.bits.substate_id == BOOST_OPSTATE_I_RAMP_UP)
                { // if the next state is set to "I Ramp-Up", check if converter supports
                  // this sub-state in its current configuration and step over it if not

                    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_VMC)
                        boostInstance->state_id.bits.substate_id++; // Increment sub-state pointer
                    
                }

            }
            else
            {
            // if last item of execution list is complete. return op-state as COMPLETE
                retval = BOOST_OPSRET_COMPLETE;
            }
            
            break;

        // If the sub-state returns any other value, something went wrong. In this case
        // return ERROR to outer state machine triggering a main state machine reset.
        default:
            // if any other return value is received, switch immediately to ERROR
            retval = BOOST_OPSRET_ERROR;        
            
            break;
    }
    
    return(retval);
}

/*******************************************************************************
 * @fn uint16_t State_Online(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function tunes the controller reference to the new user control reference level.
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * After soft-start and when state POWER_GOOD_DELAY has expired, the converter 
 * enters normal operation.
 * 
 * During normal operation the state machine scans the user reference setting. 
 * Once a change between the user reference setting and the most recent controller 
 * reference has been detected, the state machine will tune the controller 
 * reference to the new user control reference level in incremental steps,
 * applying the same ramp slope as during soft-start.
 * 
 * While ramping the output voltage up or down, the BUSY bit will be set and any 
 * new changes to the reference will be ignored until the ramp up/down is complete.
 *********************************************************************************/

volatile uint16_t State_Online(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    if(boostInstance->set_values.v_ref != boostInstance->v_loop.reference) 
    {
        // Set the BUSY bit indicating a delay/ramp period being executed
        boostInstance->status.bits.busy = true;

        // New reference value is less than controller reference value => ramp down
        if(boostInstance->set_values.v_ref < boostInstance->v_loop.reference){
            // decrement reference until new reference level is reached
            boostInstance->v_loop.reference -= boostInstance->startup.v_ramp.ref_inc_step; // decrement reference
            if(boostInstance->v_loop.reference < boostInstance->set_values.v_ref) { // check if ramp is complete
                boostInstance->v_loop.reference = boostInstance->set_values.v_ref; // clamp reference level to setting
            }

        }
        // New reference value is greater than controller reference value => ramp up
        else if(boostInstance->set_values.v_ref > boostInstance->v_loop.reference){
            // increment reference until new reference level is reached
            boostInstance->v_loop.reference += boostInstance->startup.v_ramp.ref_inc_step; // increment reference
            if(boostInstance->v_loop.reference > boostInstance->set_values.v_ref) { // check if ramp is complete
                boostInstance->v_loop.reference = boostInstance->set_values.v_ref; // clamp reference level to setting
            }

        }

    }
    else{
        // Clear the BUSY bit indicating "no state machine activity"
        boostInstance->status.bits.busy = false;
    }

    // remain in STATE_ONLINE
    return(BOOST_OPSRET_REPEAT);
    
}

/*******************************************************************************
 * @fn uint16_t State_Error(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   If this function is called, the state machine is reset to INITIALIZE (URL=@ref State_Initialize).
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This function is a default anchor in case task list index #0 is ever called.
 * This is the equivalent of a switch case "default".
 *********************************************************************************/
volatile uint16_t State_Error(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=0;
    
    // If this function is ever called, bring state machine back on track 
    // by resetting it to INITIALIZE
    
    retval = boostPWM_Suspend(boostInstance);             // Hold PWM output (turning off power)
    boostInstance->status.bits.busy = false;             // Reset busy bit

    if(retval)
        retval = BOOST_OPSRET_COMPLETE;
    else
        retval = BOOST_OPSRET_ERROR;

    
    return(retval);
}


// ______________________________________
// end of file
