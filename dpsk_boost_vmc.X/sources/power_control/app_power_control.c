/*
 * File:   app_power_control.c
 * Author: M91406
 *
 * Created on March 12, 2020, 11:55 AM
 */

#include <stdbool.h>

#include "drivers/v_loop.h"
#include "devices/dev_boost_typedef.h"
#include "devices/dev_boost_converter.h"
#include "config/hal.h"

#include "fault_handler/app_fault_monitor.h"

/**************************************************************************************************
 * @ingroup app-layer-power-control-properties-public
 * @var volatile struct BOOST_CONVERTER_s  boost
 * @brief Global data object for a BOOST CONVERTER 
 * 
 * @details
 * The 'boost' data object holds all status, control and monitoring values of the BOOST power 
 * controller. The BOOST_CONVERTER_s data structure is defined in dev_boost_converter.h.
 * Please refer to the comments on top of this file for further information.
 * 
 **************************************************************************************************/
volatile struct BOOST_CONVERTER_s boost;

/* PRIVATE FUNCTION PROTOTYPES */
extern volatile uint16_t appPowerSupply_ConverterObjectInitialize(void);
extern volatile uint16_t appPowerSupply_ControllerInitialize(void);
extern volatile uint16_t appPowerSupply_PeripheralsInitialize(void);

/* *************************************************************************************************
 * PRIVATE VARIABLE DECLARATIONS
 * ************************************************************************************************/
#define ISNS_AVG_BITMASK    (uint16_t)0x0007
volatile uint16_t _isns_sample_count = 0;
volatile uint16_t isns_samples;

/* *************************************************************************************************
 * PUBLIC FUNCTIONS
 * ************************************************************************************************/


/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Execute(void)
 * @brief This is the top-level function call triggering the most recent state 
 * machine of all associated power supply controllers
 * @return 0=failure
 * @return 1=success
 * 
 * @details 
 * After initialization, the proprietary user code has to call this function 
 * on a deterministic, constant time base. In each execution step this function
 * will call the power control state machines of each supported/included power
 * supply unit. 
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Execute(void)
{ 
    volatile uint16_t retval=1;

    // Capture data values
    boost.data.v_in = (BOOST_VIN_ADCBUF - BOOST_VIN_OFFSET);
    boost.data.temp = BOOST_TEMP_ADCBUF;
    boost.data.i_sns[0] = BOOST_ISNS_ADCBUF;
    
    // Average inductor current value and calculate output current
    isns_samples += boost.data.i_sns[0];
    
    if(!(++_isns_sample_count & ISNS_AVG_BITMASK))
    {
        isns_samples = (isns_samples >> 3);
        isns_samples -= boost.i_loop[0].feedback_offset;
        if((int16_t)isns_samples < 0) isns_samples = 0;

        // Output current is estimated without considering internal power losses
        isns_samples = (uint16_t)( (float)boost.data.v_in * (float)isns_samples / (float)boost.data.v_out );
        boost.data.i_out = isns_samples;
        
        isns_samples = 0; // Reset data buffer
    }
    
    // Execute boost converter state machine
    retval &= drv_BoostConverter_Execute(&boost);

    // Boost regulation error is only active while controller is running
    // and while being tied to a valid reference
    if( (boost.state_id.bits.opstate_id >= BOOST_OPSTATE_RAMPUP) &&
        (boost.state_id.bits.substate_id >= BOOST_OPSTATE_V_RAMP_UP) )
    {
        fltobj_BoostRegErr.ReferenceObject.ptrObject = boost.v_loop.controller->Ports.ptrControlReference;
        #if (PLANT_MEASUREMENT == false)
        fltobj_BoostRegErr.Status.bits.Enabled = boost.v_loop.controller->status.bits.enabled;
        fltobj_BoostOCP.Status.bits.Enabled = boost.v_loop.controller->status.bits.enabled;
        #endif
    }
    else {
        fltobj_BoostRegErr.Status.bits.Enabled = false;
        fltobj_BoostOCP.Status.bits.Enabled = false;
    }
    
    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Initialize(void)
 * @brief  Calls the application layer power controller initialization
 * @return 0=failure
 * @return 1=success
 * 
 * @details 
 * The power control application layer is the proprietary user code layer
 * used to tailor the generic power converter device driver to the specific 
 * hardware of this design. The initialization routine covers three levels
 * 
 * - Converter Object Configuration
 * - Controller Configuration
 * - Peripheral Set Configuration
 * - Interrupt Vector Configuration
 * 
 * Once all modules have been configured successfully, the power converter 
 * object is started with control loops and PWM outputs disabled. However, 
 * the PWM module will start triggering the ADC to allow the standby monitoring
 * of system conditions to allow the firmware to decide if it is safe to start
 * up the power converter.
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Initialize(void)
{ 
    volatile uint16_t retval=1;

    // Run initialization sequence
    retval &= appPowerSupply_ConverterObjectInitialize();
    retval &= appPowerSupply_ControllerInitialize();
    retval &= appPowerSupply_PeripheralsInitialize();

    // Initialize Control Interrupt
    _BOOST_VLOOP_ISR_IP = BOOST_VOUT_ISR_PRIORITY;
    _BOOST_VLOOP_ISR_IF = 0;
    _BOOST_VLOOP_ISR_IE = true;
    
    // Enable Boost Converter
    retval &= drv_BoostConverter_Start(&boost);
    
    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Start(void)
 * @brief  This function calls the boost converter device driver function starting the power supply 
 * @return 0=failure
 * @return 1=success
 *  
 * @details 
 *  This function exposes the Power Converter Start function of the device driver.
 *********************************************************************************/

volatile uint16_t appPowerSupply_Start(void)
{
    volatile uint16_t retval=1;

    retval &= drv_BoostConverter_Start(&boost); // Start PWM with outputs disabled to start ADC triggering

    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Stop(void)
 * @brief This function calls the boost converter device driver function stopping the power supply 
 * @return 0=failure
 * @return 1=success
 *  
 * @details
 *  This function exposes the Power Converter Stop function of the device driver.
 * 
 * @note
 *  The STOP function terminates the state machine and all peripherals used by
 *  the power controller. This includes the PWM and ADC peripheral modules and 
 *  will therefore also stop all data acquisition. 
 *  If you are trying to stop the power supply but keep its state machine and
 *  data acquisition running, use the SUSPEND function instead
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Stop(void)
{
    volatile uint16_t retval=1;

    retval &= drv_BoostConverter_Stop(&boost); // Shut down all power supply peripherals and data objects

    return(retval); 
}
/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	   volatile uint16_t appPowerSupply_Suspend(void)
 * @brief  This function stops the power supply operation
 * @return 0=failure
 * @return 1=success
 *  
 * @details
 *  The SUSPEND function stops the power supply operation but keep its state machine
 *  and data acquisition running.
 *********************************************************************************/

volatile uint16_t appPowerSupply_Suspend(void)
{ 
    volatile uint16_t retval=1;

    retval &= drv_BoostConverter_Suspend(&boost); // Shut down PWM immediately

    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	   volatile uint16_t appPowerSupply_Resume(void)
 * @brief  This function resumes the power supply operation
 * @return unsigned integer (0=failure, 1=success)
 *  
 * @details
 *  This function calls the boost converter device driver function recovering
 *  the power supply operation from a previously initiated shut-down.
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Resume(void)
{ 
    volatile uint16_t retval=0;

    retval &= drv_BoostConverter_Resume(&boost); // Shut down PWM immediately
    
    return(retval); 
}

/* *************************************************************************************************
 * PRIVATE FUNCTIONS
 * ************************************************************************************************/

 // (none)

// end of file
