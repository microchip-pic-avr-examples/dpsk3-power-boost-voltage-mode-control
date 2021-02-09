/*
 * File:   app_power_config.c
 * Author: M91406
 *
 * Created on January 13, 2021, 12:18 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "config/hal.h" // include hardware abstraction layer declarations
#include "app_power_control.h"

#include "devices/dev_boost_converter.h"
#include "drivers/v_loop.h"

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	volatile uint16_t appPowerSupply_ConverterObjectInitialize(void)
 * @brief  This function initializes the boost converter device driver instance
 * @return unsigned integer (0=failure, 1=success)
 *  
 * @details
 *  This function initialize the boost converter object status, reset the boost state 
 *  machine, set reference values, clear the runtime data, initialize the switch node,
 *  and setup the feedback channels and start-up settings.
 *********************************************************************************/

volatile uint16_t appPowerSupply_ConverterObjectInitialize(void)
{
    volatile uint16_t retval = 1;
    
    // Initialize Boost Converter Object Status
    boost.status.bits.ready = false; // Clear READY flag
    boost.status.bits.adc_active = false; // Clear ADC STARTED flag
    boost.status.bits.pwm_active = false; // clear PWM STARTED flag
    boost.status.bits.fault_active = true; // Set global FAULT flag
    
    boost.status.bits.cs_calib_enable = BOOST_ISNS_OFFSET_CALIBRATION_ENABLE; // Disable current sense feedback calibration
    boost.status.bits.async_mode = false; // Start up converter in synchronous mode
    boost.status.bits.autorun = true;    // Allow the boost converter to start automatically when cleared of faults
    boost.status.bits.enabled = false; // Disable boost converter
 
    // Set Initial State Machine State
    boost.state_id.value = BOOST_OPSTATE_INITIALIZE; // Reset Boost State Machine
    
    // Set Reference values
    boost.set_values.control_mode = BOOST_CONTROL_MODE_VMC; // Set Control Mode
    boost.set_values.no_of_phases = BOOST_NO_OF_PHASES; // Set number of power train phases
    boost.set_values.i_ref = BOOST_ISNS_REF; // Set current loop reference
    boost.set_values.v_ref = BOOST_VOUT_REF; // Set voltage loop reference
    
    // Clear Runtime Data
    boost.data.v_out = 0; // Reset output voltage value
    boost.data.i_sns[0] = 0; // Reset output current value
    boost.data.v_in = 0;  // Reset input voltage value
    boost.data.temp = 0;  // Reset output temperature value
    
    // Initialize Switch Node
    boost.sw_node[0].pwm_instance = BOOST_PWM_CHANNEL;
    boost.sw_node[0].gpio_instance = BOOST_PWM_GPIO_INSTANCE;
    boost.sw_node[0].gpio_high = BOOST_PWM_GPIO_PORT_PINH;
    boost.sw_node[0].gpio_low = BOOST_PWM_GPIO_PORT_PINL;
    boost.sw_node[0].swap_outputs = BOOST_PWM_OUTPUT_SWAP;
    boost.sw_node[0].master_period_enable = false;
    boost.sw_node[0].sync_drive = false; 
    boost.sw_node[0].period = BOOST_PWM_PERIOD;
    boost.sw_node[0].phase = BOOST_PWM_PHASE_SHIFT;
    boost.sw_node[0].duty_ratio_min = BOOST_PWM_DC_MIN;
    boost.sw_node[0].duty_ratio_init = BOOST_PWM_DC_MIN;
    boost.sw_node[0].duty_ratio_max = BOOST_PWM_DC_MAX;
    boost.sw_node[0].dead_time_rising = BOOST_PWM_DEAD_TIME_LE;
    boost.sw_node[0].dead_time_falling = BOOST_PWM_DEAD_TIME_FE;
    boost.sw_node[0].leb_period = BOOST_LEB_PERIOD;
    boost.sw_node[0].trigger_offset = BOOST_PWM_ADTR1OFS;
    boost.sw_node[0].trigger_scaler = BOOST_PWM_ADTR1PS;
    boost.sw_node[0].high_resolution_enable = PWM_CLOCK_HIGH_RESOLUTION;

    // Initialize additional GPIOs 
    
    // ~~~ EXTERNAL ENABLE INPUT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    boost.gpio.EnableInput.enabled = false; // this converter doesn't support external enable control
    // ~~~ EXTERNAL ENABLE INPUT END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ~~~ POWER GOOD OUTPUT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    boost.gpio.PowerGood.enabled = true; // This converter supports an additional POWER GOOD output
    boost.gpio.PowerGood.port = PWRGOOD_PORT; // Number of the GPIO port (0=A, 1=B, 2=C, etc.)
    boost.gpio.PowerGood.pin = PWRGOOD_PIN; // Number of the GPIO port pin
    boost.gpio.PowerGood.polarity = 0;   // This pin is ACTIVE HIGH (only required if io_type = OUTPUT)
    boost.gpio.PowerGood.io_type = 0;    // This pin is configured as OUTPUT
    
    // ~~~ POWER GOOD OUTPUT END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Initialize Feedback Channels
    
    // ~~~ OUTPUT VOLTAGE FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    boost.feedback.ad_vout.enabled = true;   // Use this channel

    boost.feedback.ad_vout.adc_input = BOOST_VOUT_ADCIN;
    boost.feedback.ad_vout.adc_core = BOOST_VOUT_ADCCORE;
    boost.feedback.ad_vout.adc_buffer = &BOOST_VOUT_ADCBUF;
    boost.feedback.ad_vout.trigger_source = BOOST_VOUT_TRGSRC;

    boost.feedback.ad_vout.differential_input = false;
    boost.feedback.ad_vout.interrupt_enable = true;
    boost.feedback.ad_vout.early_interrupt_enable = true;
    boost.feedback.ad_vout.level_trigger = true;
    boost.feedback.ad_vout.signed_result = false;
    
    boost.feedback.ad_vout.scaling.factor = BOOST_VOUT_NORM_FACTOR;
    boost.feedback.ad_vout.scaling.scaler = BOOST_VOUT_NORM_SCALER;
    boost.feedback.ad_vout.scaling.offset = BOOST_VOUT_OFFSET;

    BOOST_VOUT_ANSEL = boost.feedback.ad_vout.enabled;
    
    // ~~~ OUTPUT VOLTAGE FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ~~~ INPUT VOLTAGE FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    boost.feedback.ad_vin.enabled = true;   // Use this channel

    boost.feedback.ad_vin.adc_input = BOOST_VIN_ADCIN;
    boost.feedback.ad_vin.adc_core = BOOST_VIN_ADCCORE;
    boost.feedback.ad_vin.adc_buffer = &BOOST_VIN_ADCBUF;
    boost.feedback.ad_vin.trigger_source = BOOST_VIN_TRGSRC;

    boost.feedback.ad_vin.differential_input = false;
    boost.feedback.ad_vin.interrupt_enable = false;
    boost.feedback.ad_vin.early_interrupt_enable = false;
    boost.feedback.ad_vin.level_trigger = false;
    boost.feedback.ad_vin.signed_result = false;

    boost.feedback.ad_vin.scaling.factor = BOOST_VIN_NORM_FACTOR;
    boost.feedback.ad_vin.scaling.scaler = BOOST_VIN_NORM_SCALER;
    boost.feedback.ad_vin.scaling.offset = BOOST_VIN_OFFSET;

    BOOST_VIN_ANSEL = boost.feedback.ad_vin.enabled;
    
    // ~~~ INPUT VOLTAGE FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~ OUTPUT CURRENT FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    boost.feedback.ad_isns[0].enabled = true;   // Use this channel

    boost.feedback.ad_isns[0].adc_input = BOOST_ISNS_ADCIN;
    boost.feedback.ad_isns[0].adc_core = BOOST_ISNS_ADCCORE;
    boost.feedback.ad_isns[0].adc_buffer = &BOOST_ISNS_ADCBUF;
    boost.feedback.ad_isns[0].trigger_source = BOOST_ISNS_TRGSRC;

    boost.feedback.ad_isns[0].differential_input = false;
    boost.feedback.ad_isns[0].interrupt_enable = false;
    boost.feedback.ad_isns[0].early_interrupt_enable = false;
    boost.feedback.ad_isns[0].level_trigger = true;
    boost.feedback.ad_isns[0].signed_result = false;

    boost.feedback.ad_isns[0].scaling.factor = BOOST_ISNS_NORM_FACTOR;
    boost.feedback.ad_isns[0].scaling.scaler = BOOST_ISNS_NORM_SCALER;
    boost.feedback.ad_isns[0].scaling.offset = BOOST_ISNS_FB_OFFSET;

    BOOST_ISNS_ANSEL = boost.feedback.ad_isns[0].enabled;
    
    // ~~~ OUTPUT CURRENT FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~ TEMPERATURE FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    boost.feedback.ad_temp.enabled = true;   // Use this channel

    boost.feedback.ad_temp.adc_input = BOOST_TEMP_ADCIN;
    boost.feedback.ad_temp.adc_core = BOOST_TEMP_ADCCORE;
    boost.feedback.ad_temp.adc_buffer = &BOOST_TEMP_ADCBUF;
    boost.feedback.ad_temp.trigger_source = BOOST_TEMP_TRGSRC;

    boost.feedback.ad_temp.differential_input = false;
    boost.feedback.ad_temp.interrupt_enable = false;
    boost.feedback.ad_temp.early_interrupt_enable = false;
    boost.feedback.ad_temp.level_trigger = false;
    boost.feedback.ad_temp.signed_result = false;

    BOOST_TEMP_ANSEL = boost.feedback.ad_temp.enabled;
    
    // ~~~ TEMPERATURE FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Initialize Startup Settings
    
    boost.startup.power_on_delay.counter = 0;
    boost.startup.power_on_delay.period = BOOST_POD;
    boost.startup.power_on_delay.ref_inc_step = 0;
    boost.startup.power_on_delay.reference = 0;
    
    boost.startup.v_ramp.counter = 0;
    boost.startup.v_ramp.period = BOOST_VRAMP_PER;
    boost.startup.v_ramp.ref_inc_step = BOOST_VREF_STEP;
    if (boost.startup.v_ramp.ref_inc_step == 0)
        boost.startup.v_ramp.ref_inc_step = 1;
    boost.startup.v_ramp.reference = 0;
    
    if (boost.set_values.control_mode == BOOST_CONTROL_MODE_ACMC) 
    {
        boost.startup.i_ramp.counter = 0;
        boost.startup.i_ramp.period = BOOST_IRAMP_PER;
        boost.startup.i_ramp.ref_inc_step = BOOST_IREF_STEP;
        boost.startup.i_ramp.reference = 0;
    }
    
    boost.startup.power_good_delay.counter = 0;
    boost.startup.power_good_delay.period = BOOST_PGD;
    boost.startup.power_good_delay.ref_inc_step = 0;
    boost.startup.power_good_delay.reference = BOOST_VOUT_REF;
    
    
    return(retval);
}


/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	volatile uint16_t appPowerSupply_ControllerInitialize(void)
 * @brief  This function initializes the control system feedback loop objects
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * This function allows the user to set up and initialize the loop configuration. This 
 * includes the following setup.
 *     - Initialize Default Loop Configuration
 *     - Set Controller Object of Voltage Loop
 *     - Configure Voltage Loop Controller Object
 *     - Configure controller input/output ports
 *     - Data Input/Output Limit Configuration
 *     - ADC Trigger Control Configuration
 *     - Data Provider Configuration
 *     - Cascaded Function Configuration
 *     - Initialize Advanced Control Settings 
 *     - Custom Advanced Control Settings
 *********************************************************************************/

volatile uint16_t appPowerSupply_ControllerInitialize(void)
{
    volatile uint16_t retval = 1;
    
    // ~~~ VOLTAGE LOOP CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // Initialize Default Loop Configuration
    boost.v_loop.feedback_offset = BOOST_VOUT_OFFSET;
    boost.v_loop.reference = BOOST_VOUT_REF;
    boost.v_loop.minimum = BOOST_PWM_DC_MIN;
    boost.v_loop.maximum = BOOST_PWM_DC_MAX;
    boost.v_loop.trigger_offset = ((BOOST_PWM_PERIOD >> 1) + BOOST_VOUT_ADC_TRGDLY);
    
     // Set Controller Object of Voltage Loop
    boost.v_loop.controller = &v_loop;
    boost.v_loop.ctrl_Initialize = &v_loop_Initialize;
    boost.v_loop.ctrl_Update = &v_loop_Update;
    boost.v_loop.ctrl_Reset = &v_loop_Reset;
    boost.v_loop.ctrl_Precharge = &v_loop_Precharge;
    
    // Configure Voltage Loop Controller Object
    boost.v_loop.ctrl_Initialize(&v_loop);   // Call Initialization Routine setting histories and scaling
    
    // Configure controller input ports
    boost.v_loop.controller->Ports.Source.ptrAddress = &BOOST_VOUT_ADCBUF; // Output Voltage is Common Source
    boost.v_loop.controller->Ports.Source.Offset = boost.v_loop.feedback_offset; // Output Voltage feedback signal offset 
    boost.v_loop.controller->Ports.Source.NormScaler = BOOST_VOUT_NORM_SCALER; // Output voltage normalization factor bit-shift scaler 
    boost.v_loop.controller->Ports.Source.NormFactor = BOOST_VOUT_NORM_FACTOR; // Output voltage normalization factor fractional
    
    boost.v_loop.controller->Ports.AltSource.ptrAddress = &BOOST_VIN_ADCBUF; // Input Voltage Is Alternate Source
    boost.v_loop.controller->Ports.AltSource.Offset = BOOST_VIN_OFFSET; // Input Voltage feedback signal offset 
    boost.v_loop.controller->Ports.AltSource.NormScaler = BOOST_VIN_NORM_SCALER; // Input voltage normalization factor bit-shift scaler 
    boost.v_loop.controller->Ports.AltSource.NormFactor = BOOST_VIN_NORM_FACTOR; // Input voltage normalization factor fractional

    // Configure controller output ports
    boost.v_loop.controller->Ports.Target.ptrAddress = &BOOST_PWM_PDC; // PWM Duty Cycle is Control Target
    boost.v_loop.controller->Ports.Target.Offset = 0; // Static primary output value offset
    boost.v_loop.controller->Ports.Target.NormScaler = 0; // Primary control output normalization factor bit-shift scaler 
    boost.v_loop.controller->Ports.Target.NormFactor = 0x7FFF; // Primary control output normalization factor fractional 

    boost.v_loop.controller->Ports.AltTarget.ptrAddress = NULL; // No alternate target used
    boost.v_loop.controller->Ports.AltTarget.Offset = 0; // Static secondary output value offset
    boost.v_loop.controller->Ports.AltTarget.NormScaler = 0; // Secondary control output normalization factor bit-shift scaler
    boost.v_loop.controller->Ports.AltTarget.NormFactor = 0x7FFF; // Secondary control output normalization factor fractional 
    
    // Configure controller control ports
    boost.v_loop.controller->Ports.ptrControlReference = &boost.set_values.v_ref; // Set pointer to Reference
    
    // Data Input/Output Limit Configuration
    boost.v_loop.controller->Limits.MinOutput = boost.v_loop.minimum;
    boost.v_loop.controller->Limits.MaxOutput = boost.v_loop.maximum;
    boost.v_loop.controller->Limits.AltMinOutput = 0; // not used
    boost.v_loop.controller->Limits.AltMaxOutput = 0; // not used

    // ADC Trigger Control Configuration
    boost.v_loop.controller->ADCTriggerControl.ptrADCTriggerARegister = &BOOST_VOUT_ADCTRIG;
    boost.v_loop.controller->ADCTriggerControl.ADCTriggerAOffset = boost.v_loop.trigger_offset;
    boost.v_loop.controller->ADCTriggerControl.ptrADCTriggerBRegister = &BOOST_VIN_ADCTRIG;
    boost.v_loop.controller->ADCTriggerControl.ADCTriggerBOffset = BOOST_ISNS_ADC_TRGDLY; 
    
    // Data Provider Configuration
    boost.v_loop.controller->DataProviders.ptrDProvControlInput = &boost.data.control_input; 
    boost.v_loop.controller->DataProviders.ptrDProvControlInputCompensated = &boost.data.v_out; 
    boost.v_loop.controller->DataProviders.ptrDProvControlError = &boost.data.control_error; 
    boost.v_loop.controller->DataProviders.ptrDProvControlOutput = &boost.data.control_output;
    
    // User Extension Function Configuration
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * 
     * PowerSmart DCLD allows users to create and call user extension 
     * functions from specific locations of the main control loop to 
     * cover design-specific requirements and features which are not
     * supported by the main controller by default.
     * 
     * Control Loop User Extension Declaration Example:
     * 
     *  boost.v_loop.controller->ExtensionHooks.ptrExtHookStartFunction = (uint16_t)&my_function; 
     * 
     * Control Loop User Extension Parameter Declaration Example (optional):
     * 
     *  boost.v_loop.controller->ExtensionHooks.ExtHookStartFunctionParam = 512;
     * 
     * Please refer to the PowerSmart DCLD User Guide for more details about
     * how to use this feature, its requirements and limitations.
     * 
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    */
    
    boost.v_loop.controller->ExtensionHooks.ptrExtHookStartFunction = NULL;
    boost.v_loop.controller->ExtensionHooks.ExtHookStartFunctionParam = 0;
    boost.v_loop.controller->ExtensionHooks.ptrExtHookSourceFunction = NULL;
    boost.v_loop.controller->ExtensionHooks.ExtHookSourceFunctionParam = 0;
    boost.v_loop.controller->ExtensionHooks.ptrExtHookPreAntiWindupFunction = NULL;
    boost.v_loop.controller->ExtensionHooks.ExtHookPreAntiWindupFunctionParam = 0;
    boost.v_loop.controller->ExtensionHooks.ptrExtHookTargetFunction = NULL;
    boost.v_loop.controller->ExtensionHooks.ExtHookTargetFunctionParam = 0;
    boost.v_loop.controller->ExtensionHooks.ptrExtHookStopFunction = NULL;
    boost.v_loop.controller->ExtensionHooks.ExtHookStopFunctionParam = 0;
    boost.v_loop.controller->ExtensionHooks.ptrExtHookEndFunction = NULL;
    boost.v_loop.controller->ExtensionHooks.ExtHookEndFunctionParam = 0;
    
    // Initialize Advanced Control Settings (not used in this code example)
    boost.v_loop.controller->GainControl.AgcFactor = 0x7FFF; // Adaptive Gain Control factor fractional
    boost.v_loop.controller->GainControl.AgcScaler = 0x0000; // Adaptive Gain Control factor bit-shift scaler
    boost.v_loop.controller->GainControl.AgcMedian = 0x0000; // Q15 number representing normalized Nominal Operating Point

    // Custom Advanced Control Settings
    boost.v_loop.controller->Advanced.usrParam0 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam1 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam2 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam3 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam4 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam5 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam6 = 0; // No additional advanced control options used
    boost.v_loop.controller->Advanced.usrParam7 = 0; // No additional advanced control options used
    
    // Reset Controller Status
    boost.v_loop.controller->status.bits.enabled = false; // Keep controller disabled
    boost.v_loop.controller->status.bits.swap_source = false; // use SOURCE as major control input
    boost.v_loop.controller->status.bits.swap_target = false; // use TARGET as major control output
    boost.v_loop.controller->status.bits.invert_input = false; // Do not invert input value
    boost.v_loop.controller->status.bits.lower_saturation_event = false; // Reset Anti-Windup Minimum Status bit
    boost.v_loop.controller->status.bits.upper_saturation_event = false; // Reset Anti-Windup Minimum Status bits
    boost.v_loop.controller->status.bits.agc_enabled = false;   // Enable Adaptive Gain Modulation by default

    // ~~~ VOLTAGE LOOP CONFIGURATION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    return(retval);
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	volatile uint16_t appPowerSupply_PeripheralsInitialize(void)
 * @brief  This function is used to load peripheral configuration templates from the power controller device driver
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * This function hand over the peripheral configuration to the boost converter driver
 *********************************************************************************/

volatile uint16_t appPowerSupply_PeripheralsInitialize(void)
{
    volatile uint16_t retval=1;
    
    retval &= drv_BoostConverter_Initialize(&boost);
    
    return(retval);
}


// end of file
