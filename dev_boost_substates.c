/* 
 * File:   dev_boost_substates.c
 * Author: M91406
 * Comments: Boost converter operation sub-states header file
 * Revision history: 
 *   10/28/20   1.0  initial version
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stdlib.h> // include C standard library header

#include "dev_boost_pconfig.h" // include boost converter
#include "dev_boost_typedef.h" // include boost converter data object declarations

// Private function prototypes of sub-state functions
volatile uint16_t __attribute__((always_inline)) SubState_PowerOnDelay(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) Substate_VCapMonitor(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) SubState_PrepareVRampUp(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) SubState_VRampUp(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) SubState_IRampUp(volatile struct BOOST_CONVERTER_s *boostInstance);
volatile uint16_t __attribute__((always_inline)) SubState_PowerGoodDelay(volatile struct BOOST_CONVERTER_s *boostInstance);


// Declaration of function pointer array listing sub-state functions in order of execution
volatile uint16_t (*BoostConverterRampUpSubStateMachine[])(volatile struct BOOST_CONVERTER_s *boostInstance) = 
{
    SubState_PowerOnDelay,      ///< Sub-State #1: Wait programmed number of state machine ticks until startup is triggered
    Substate_VCapMonitor,       ///< Sub-State #0: Monitors the output capacitor voltage until the voltage has settled
    SubState_PrepareVRampUp,    ///< Sub-State #2: Determine ramp up condition, pre-charge controllers and program PWM/Peripherals
    SubState_VRampUp,           ///< Sub-State #3: Output voltage ramp up
    SubState_IRampUp,           ///< Sub-State #4: Output current ramp up (optional, for startup current limiting only)
    SubState_PowerGoodDelay     ///< Sub-State #5: Wait until power good delay has expired and optionally set a GPIO
};

// Declaration variable capturing the size of the sub-state function pointer array 
volatile uint16_t BoostRampUpSubStateList_size = (sizeof(BoostConverterRampUpSubStateMachine)/sizeof(BoostConverterRampUpSubStateMachine[0])); 


/***********************************************************************************
 * @fn      uint16_t Substate_VCapMonitor(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function monitors the output capacitor voltage waiting until the voltage has settled
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * The boost converter output capacitor is by default automatically charged 
 * through the boost rectifier resp. the high-side MOSFET body diode. Before 
 * the power supply is started, the state machine waits for the output
 * capacitor voltage to settle to reduce component stress during startup.
 **********************************************************************************/

volatile uint16_t Substate_VCapMonitor(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t _source=0;

    // Set BUSY bit until process is complete
    boostInstance->status.bits.busy = true;
    
    // Capture compare value
    _source = abs(boostInstance->data.v_in - boostInstance->data.v_out); 

    if((_source > boostInstance->startup.vcap_monitor.v_drop) &&
       (boostInstance->startup.vcap_monitor.period > 0))
        boostInstance->startup.vcap_monitor.counter = 0; // Reset counter if voltage is not tuned in yet

    // Monitor settled voltage for the given period of time
    if (++boostInstance->startup.vcap_monitor.counter > 
        boostInstance->startup.vcap_monitor.period)
    {
        boostInstance->startup.vcap_monitor.counter = 0;
        boostInstance->startup.vcap_monitor.timeout_counter = 0;
        
        Nop();  // Please Debugging Breakpoint
        Nop();
        Nop();

        return(BOOST_OPSRET_COMPLETE);
        
    }
    
    // In case of a timeout, reset state machine and try again
    if (boostInstance->startup.vcap_monitor.timeout_counter++ > 
        boostInstance->startup.vcap_monitor.timeout)
    {
        boostInstance->startup.vcap_monitor.counter = 0;
        boostInstance->startup.vcap_monitor.timeout_counter = 0;

        Nop();  // Please Debugging Breakpoint
        Nop();
        Nop();

        return (BOOST_OPSRET_ERROR);

    }

    // Recall this sub-state
    return(BOOST_OPSRET_REPEAT);
         
}

/***********************************************************************************
 * @fn      uint16_t SubState_PowerOnDelay(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function delays the startup until the Power-on Delay has expired 
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 *  After the converter has been cleared to get started, the power-on
 *  delay counter is incremented until the defined power-on delay period
 *  has expired.
 **********************************************************************************/

volatile uint16_t SubState_PowerOnDelay(volatile struct BOOST_CONVERTER_s *boostInstance)
{
   volatile uint16_t retval=0;

    // Set BUSY bit until process is complete
    boostInstance->status.bits.busy = true;
    
    // delay startup until POWER ON DELAY has expired
    if(boostInstance->startup.power_on_delay.counter++ > boostInstance->startup.power_on_delay.period)
    {
        // Clamp POD counter to EXPIRED
        boostInstance->startup.power_on_delay.counter = 
            (boostInstance->startup.power_on_delay.period + 1); // Saturate power on counter

        retval = BOOST_OPSRET_COMPLETE; 
    }
    else
    // When the period has not expired yet, return to this function
    {
        retval = BOOST_OPSRET_REPEAT;
    }    

    return(retval);
}

/***********************************************************************************
 * @fn      uint16_t SubState_PrepareVRampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function calculate and pre-charge PWM outputs with ideal duty cycle 
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * After the POWER ON DELAY has expired, the ramp up starting point is determined  
 * by measuring the input and output voltage and calculates the ideal duty ratio 
 * of the PWM. This value is then programmed into the PWM module duty cycle register 
 * and is also used to pre-charge the control loop output history. In addition the 
 * measured output voltage also set as reference to ensure the loop starts without 
 * jerks and jumps.
 * 
 * When voltage mode control is enabled, the voltage loop control history is 
 * charged, when average current mode control is enabled, the current loop control 
 * history is charged.
 **********************************************************************************/

volatile uint16_t SubState_PrepareVRampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t _i=0;
    volatile uint32_t _vout=0;
    volatile uint32_t _vin=0;
    volatile uint32_t _start_dc=0;

    // Set BUSY bit until process is complete
    boostInstance->status.bits.busy = true;

    // Copy user setting for voltage reference
    boostInstance->v_loop.reference = boostInstance->set_values.v_ref;
    
    // Hijack voltage loop controller reference
    boostInstance->startup.v_ramp.reference = 0; // Reset Soft-Start Voltage Reference
    boostInstance->startup.i_ramp.reference = 0; // Reset Soft-Start Current Reference
    boostInstance->v_loop.controller->Ports.ptrControlReference = 
        &boostInstance->startup.v_ramp.reference; // Voltage loop is pointing to Soft-Start Reference

    // Pre-charge reference
    // Never start above the pre-biased output voltage.
    // Always start at or slightly below the pre-biased output voltage
    boostInstance->startup.v_ramp.reference = boostInstance->data.v_out;

    // In average current mode, set current reference limit to max startup current level
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) 
    {   // Disable all current control loops and reset control loop histories
        boostInstance->v_loop.maximum = boostInstance->set_values.i_ref_startup;
        boostInstance->v_loop.controller->Limits.MaxOutput = boostInstance->v_loop.maximum;
    }

    // Pre-charge PWM and control loop history 
    if(((boostInstance->data.v_in - boostInstance->feedback.ad_vin.scaling.offset) > 0) &&
       ((boostInstance->data.v_out - boostInstance->feedback.ad_vout.scaling.offset) > 0) )
    {
        _vout = __builtin_muluu(
            (boostInstance->data.v_out - boostInstance->feedback.ad_vout.scaling.offset), 
            boostInstance->feedback.ad_vout.scaling.factor);
        _vout >>= (16 - boostInstance->feedback.ad_vout.scaling.scaler);

        _vin = __builtin_muluu(
            (boostInstance->data.v_in - boostInstance->feedback.ad_vin.scaling.offset), 
            boostInstance->feedback.ad_vin.scaling.factor);
        _vin >>= (16 - boostInstance->feedback.ad_vin.scaling.scaler);

        // Protect against negative duty cycle results
        if (_vout < _vin) _vout = _vin;
        
        // CALCULATE BOOST CONVERTER STARTUP DUTY RATIO 
        // DC = (VOUT-VIN) / VOUT, where DC = D * PERIOD
        
        if(_vin > 0)
        {
            _start_dc = __builtin_muluu((_vout-_vin), boostInstance->sw_node[0].period);
            _start_dc = __builtin_divud(_start_dc, (uint16_t)_vout);
        }
        else
        { _start_dc = (uint16_t)boostInstance->sw_node[_i].duty_ratio_min; }
    }
    else
    // If there is no input voltage or no output voltage, start with minimum duty ratio
    {
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) {
            _start_dc = (uint16_t)boostInstance->sw_node[_i].duty_ratio_min;
        }
    }

    // Program PWM module and pre-charge control loop
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_VMC)
    {
        if(_start_dc < boostInstance->v_loop.minimum) 
        { _start_dc = boostInstance->v_loop.minimum; }
        else if(_start_dc > boostInstance->v_loop.maximum) 
        { _start_dc = boostInstance->v_loop.maximum; }
        else { /* continue */ }

        boostInstance->v_loop.ctrl_Precharge(boostInstance->v_loop.controller, 0, _start_dc);
        *boostInstance->v_loop.controller->Ports.Target.ptrAddress = _start_dc; // set initial PWM duty ratio
        if(boostInstance->v_loop.controller->Ports.AltTarget.ptrAddress != NULL)
            *boostInstance->v_loop.controller->Ports.AltTarget.ptrAddress = _start_dc; // set initial PWM duty ratio
        else { /* continue */ }

    }
    else if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC) 
    {   
        // Limit startup duty cycle to largest minimum/smallest maximum
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) {
            
            if(_start_dc < boostInstance->i_loop[_i].minimum) 
            { _start_dc = boostInstance->i_loop[_i].minimum; }
            else if(_start_dc > boostInstance->i_loop[_i].maximum) 
            { _start_dc = boostInstance->i_loop[_i].maximum; }
            else { /* continue */ }
        }
        
        // Set initial duty cycle
        for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) 
        {
            // pre-charge current loop control histories with ideal duty cycle
            boostInstance->i_loop[_i].ctrl_Precharge(
                        boostInstance->i_loop[_i].controller, 0, _start_dc
                    );

            // pre-charge PWM outputs with ideal duty cycle
            *boostInstance->i_loop[_i].controller->Ports.Target.ptrAddress = _start_dc; // set initial PWM duty ratio
            if(boostInstance->i_loop[_i].controller->Ports.AltTarget.ptrAddress != NULL)
                *boostInstance->i_loop[_i].controller->Ports.AltTarget.ptrAddress = _start_dc; // set initial PWM duty ratio
            else { /* continue */ }
        }
    }
    else
    {
        return(BOOST_OPSRET_ERROR);
    }

    return(BOOST_OPSRET_COMPLETE);
    
}

/***********************************************************************************
 * @fn      uint16_t SubState_VRampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function ramps up the output voltage to its nominal regulation point
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This is the essential step in which the output voltage is ramped up by 
 * incrementing the outer control loop reference. In voltage mode the output  
 * voltage will ramp up to the nominal regulation point. 
 * In average current mode the inner loop will limit the voltage as soon as the 
 * current reference limit is hit and the output is switched to constant current 
 * mode.
 **********************************************************************************/

volatile uint16_t SubState_VRampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    
    // Set BUSY bit until process is complete
    boostInstance->status.bits.busy = true;
    
    // ensure control loop is enabled
    if(!boostInstance->v_loop.controller->status.bits.enabled) {

        // Enable all PWM channels
        retval &= boostPWM_Resume(boostInstance);  // Enable PWM outputs

        // In voltage mode control...
        if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_VMC)
        {   // only enable voltage loop
            boostInstance->v_loop.controller->status.bits.enabled = true; // enable voltage loop controller
        }
        // In average current mode control...
        else if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC)
        {
            // enable voltage loop controller
            boostInstance->v_loop.controller->status.bits.enabled = true; 
            
            // enable all phase current loop controllers
            for (_i=0; _i<boostInstance->set_values.no_of_phases; _i++) {
                boostInstance->i_loop[_i].controller->status.bits.enabled = true; 
            }
        }
        // IF control mode is set to unsupported control mode, return error
        else
        {
            return(BOOST_OPSRET_ERROR);
        }

    }

    // increment reference
    boostInstance->startup.v_ramp.reference += boostInstance->startup.v_ramp.ref_inc_step;

    // check if ramp is complete
    if (boostInstance->startup.v_ramp.reference > boostInstance->v_loop.reference) 
    {
        // Set reference to the desired level
        boostInstance->startup.v_ramp.reference = boostInstance->v_loop.reference;

        // Reconnect API reference to controller
        boostInstance->v_loop.controller->Ports.ptrControlReference = &boostInstance->v_loop.reference;

        retval = BOOST_OPSRET_COMPLETE;
        
    }
    else
    // remain in this state until ramp is complete
    {
        retval = BOOST_OPSRET_REPEAT;
    }

    
    return(retval);
    
}

/***********************************************************************************
 * @fn      uint16_t SubState_IRampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   This function is for the average current mode control where the output current is ramped up to nominal current
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This phase of the soft-start ramp is only executed in average current mode and 
 * will only take effect when the declared current limit is hit before the nominal 
 * voltage regulation point. In this case the outer voltage loop will clamp the 
 * current reference value and the state will be switched to IRampUp, where the 
 * clamping value of the voltage loop output is ramped up to the declared maximum
 * current reference value.
 * This additional state allows powering up the power converter against highly 
 * capacitive loads preventing overshoots caused by down-stream capacitor inrush 
 * currents or when the converter is used as battery charger, where this state 
 * will tune into the constant current charging mode.
 **********************************************************************************/
volatile uint16_t SubState_IRampUp(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=0;
    
    // Set BUSY bit until process is complete
    boostInstance->status.bits.busy = true;

    // in average current mode if voltage limit is hit, increment 
    // voltage loop limit to ramp up current loop
    if (boostInstance->set_values.control_mode == BOOST_CONTROL_MODE_ACMC)
    {
        // Increment maximum current limit
        boostInstance->v_loop.controller->Limits.MaxOutput += boostInstance->startup.i_ramp.ref_inc_step; 

        if (boostInstance->v_loop.controller->Limits.MaxOutput >= boostInstance->set_values.i_ref_startup)
        // check if ramp is complete
        {
            boostInstance->v_loop.maximum = boostInstance->set_values.i_ref_startup;
            boostInstance->v_loop.controller->Limits.MaxOutput = boostInstance->v_loop.maximum;
            retval = BOOST_OPSRET_COMPLETE;
        }
        else
        // if ramp is not complete yet, remain in this state
        {
            retval = BOOST_OPSRET_REPEAT;
        }
    }
    else // Non-Current Loops Ending up here need to be lifted to PG_DELAY
    { 
        boostInstance->v_loop.controller->Limits.MaxOutput = boostInstance->v_loop.maximum;
        retval = BOOST_OPSRET_COMPLETE; 
    }

    return(retval);
    
}

/***********************************************************************************
 * @fn      uint16_t SubState_PowerGoodDelay(volatile struct BOOST_CONVERTER_s *boostInstance)
 * @ingroup lib-layer-boost-state-machine-functions
 * @brief   In this function, a counter is incremented until the power good delay has expired.
 * @param	boostInstance  Pointer to a Boost Converter data object of type struct BOOST_CONVERTER_s
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * In this phase of the soft-start procedure a counter is incremented until the 
 * power good delay has expired before the soft-start process is marked as COMPLETED.
 * If option for driving a user-defined general purpose output (PG output) is enabled
 * in proprietary user code, this pin will be set automatically.
 **********************************************************************************/
volatile uint16_t SubState_PowerGoodDelay(volatile struct BOOST_CONVERTER_s *boostInstance)
{
    volatile uint16_t retval=0;
    
    // Set BUSY bit until process is complete
    boostInstance->status.bits.busy = true;

    // increment delay counter until the GOWER GOOD delay has expired
    if(boostInstance->startup.power_good_delay.counter++ > boostInstance->startup.power_good_delay.period)
    {
        boostInstance->startup.power_good_delay.counter = 
            (boostInstance->startup.power_good_delay.period + 1); // Clamp to PERIOD_EXPIRED for future startups

        // If defined, set POWER_GOOD output
        if(boostInstance->gpio.PowerGood.enabled)
        {
            retval = boostGPIO_Set(&boostInstance->gpio.PowerGood);
            
            if(!retval) 
            { retval = BOOST_OPSTATE_ERROR; }
        }

        retval = BOOST_OPSRET_COMPLETE;

    }
    else
    // if period has not expired yet, remain in this state
    {
        retval = BOOST_OPSRET_REPEAT;
    }

    return(retval);
    
}

// end of file
