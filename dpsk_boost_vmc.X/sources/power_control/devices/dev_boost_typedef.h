/**
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany Microchip
 *  software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 *  MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
 *  HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
 *  THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 *  CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY,
 *  YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 *  @file    dev_boost_typedef.h
 *  @brief   This file contains APIs to for the power control
 *
 *  @note
 *  Microchip Technology Inc. has followed development methods required by
 *  IEC-60730 and performed extensive validation and static testing to ensure
 *  that the code operates as intended. Any modification to the code can
 *  invalidate the results of Microchip's validation and testing.
 *
 */

/* 
 * File:   dev_boost_typedef.h
 * Author: M91406
 * Comments: Type definitions of single- and multiphase Boost Converter data object
 * Revision history: 
 * 1.0  initial release
 * 1.1  restructured phase arrays in data object to optimize code execution and stay with unified API
 *      with regards to other power converter object libraries
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BOOST_CONVERTER_TYPE_DEF_H
#define	BOOST_CONVERTER_TYPE_DEF_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)
#include <stddef.h> // include standard definition data types

#include "power_control/drivers/npnz16b.h"
#include "config/hal.h"


/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-public-defines
 * @def     BOOST_MPHASE_COUNT
 * @brief   Declaration of the number of power train phases of the Boost Converter
 **************************************************************************************************** */
#define BOOST_MPHASE_COUNT           BOOST_NO_OF_PHASES

// Controller Status Bits
/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @enum    BOOST_STATUS_FLAGS_e
 * @brief   Enumeration of status and control flags
 * @extends BOOST_CONVERTER_CONSTANTS_s
 **************************************************************************************************** */
enum BOOST_STATUS_FLAGS_e 
{  
    BOOST_STAT_READY                = 0b0000000000000001,
    BOOST_STAT_ADC_ACTIVE           = 0b0000000000000010,
    BOOST_STAT_PWM_ACTIVE           = 0b0000000000000100,
    BOOST_STAT_POWERSOURCE_DETECTED = 0b0000000000001000,
    BOOST_STAT_CS_SENSE_READY       = 0b0000000000010000,
    
    BOOST_STAT_FORCED_SHUT_DOWN     = 0b0000000010000000,
    BOOST_STAT_BUSY                 = 0b0000000100000000,

// Controller Control Bits
    BOOST_STAT_GO                   = 0b0010000000000000,
    BOOST_STAT_AUTORUN              = 0b0100000000000000,
    BOOST_STAT_NO_AUTORUN           = 0b0000000000000000,
    
    BOOST_STAT_ENABLED              = 0b1000000000000000,
    BOOST_STAT_DISABLED             = 0b0000000000000000
}; ///< Enumeration of all status and control flags of the Boost Converter status word
typedef enum BOOST_STATUS_FLAGS_e BOOST_STATUS_FLAGS_t;

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @enum    BOOST_OPSTATES_e
 * @brief   Enumeration of state machine operating states 
 * @extends BOOST_STATE_ID_s
 * @extends BOOST_CONVERTER_CONSTANTS_s
 **************************************************************************************************** */
enum BOOST_OPSTATES_e {  
    
    BOOST_OPSTATE_ERROR          = 0x00,  ///< power converter control state #0: in case of an error, state machine will reset to RESET
    BOOST_OPSTATE_INITIALIZE     = 0x01,  ///< power converter control state #1: initialize variables and hijack controller reference
    BOOST_OPSTATE_RESET          = 0x02,  ///< power converter control state #2: Initializing variable but bypassing delays
    BOOST_OPSTATE_STANDBY        = 0x03,  ///< power converter control state #3: power converter control state #2 standing by, ready to launch, waiting for GO (no action)
    BOOST_OPSTATE_RAMPUP         = 0x04,  ///< power converter control state #4: Startup handler sub-state machine
    BOOST_OPSTATE_ONLINE         = 0x05   ///< power converter control state #5: Output in regulation and power is OK (normal continuous operation)
        
}; ///< Enumeration of state machine operating states 
typedef enum BOOST_OPSTATES_e BOOST_OPSTATE_t; ///< Enumeration of state machine operating states

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @enum    BOOST_SUBSTATES_e
 * @brief   Enumeration of state machine operating sub-states 
 * @extends BOOST_STATE_ID_s
 * @extends BOOST_CONVERTER_CONSTANTS_s
 **************************************************************************************************** */
enum BOOST_SUBSTATES_e {  // Enumeration of state machine operating sub-states

    BOOST_OPSTATE_POWER_ON_DELAY = 0x00,  ///< power converter control state #3: power on delay (no action)
    BOOST_OPSTATE_VCAP_MONITOR   = 0x01,  ///< power converter control state #4: wait for the output voltage to settle
    BOOST_OPSTATE_PREPARE_V_RAMP = 0x02,  ///< power converter control state #5: turn on PWM outputs and enable controller
    BOOST_OPSTATE_V_RAMP_UP      = 0x03,  ///< power converter control state #6: perform output voltage ramp up based on parameters and system response 
    BOOST_OPSTATE_I_RAMP_UP      = 0x04,  ///< power converter control state #7: perform output current ramp up based on parameters and system response (average current mode only)
    BOOST_OPSTATE_PWRGOOD_DELAY  = 0x05   ///< power converter control state #8: Output reached regulation point but waits until things have settled
    
}; ///< Enumeration of state machine operating sub-states 
typedef enum BOOST_SUBSTATES_e BOOST_OP_SUBSTATES_t; ///< Enumeration of state machine operating sub-states data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @enum BOOST_OPSTATE_RETURNS_e
 * @brief Enumeration of state machine operating state return values
 * @extends BOOST_CONVERTER_CONSTANTS_s
 **************************************************************************************************** */
enum BOOST_OPSTATE_RETURNS_e {  // Enumeration of state machine operating state return values
    
    BOOST_OPSRET_ERROR           = 0x0000,  ///< power converter state return #0: internal error occurred
    BOOST_OPSRET_COMPLETE        = 0x0001,  ///< power converter state return #1: operation state has completed
    BOOST_OPSRET_REPEAT          = 0x0002   ///< power converter state return #2: operation state is in progress and needs to be recalled
        
}; // Enumeration of state machine operating state return values
typedef enum BOOST_OPSTATE_RETURNS_e BOOST_OPSTATE_RETURNS_t; // State Machine Operating State Return Values

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @enum    BOOST_CONTROL_MODE_e
 * @brief   Enumeration of the power supply mode control
 * @extends BOOST_CONVERTER_SETTINGS_s
 * @extends BOOST_CONVERTER_CONSTANTS_s
 **************************************************************************************************** */
enum BOOST_CONTROL_MODE_e{
    
    BOOST_CONTROL_MODE_VMC = 0,              ///< Voltage Mode Control
//    BOOST_CONTROL_MODE_PCMC = 1,           // Peak Current Mode Control (not supported yet)
    BOOST_CONTROL_MODE_ACMC = 2              ///< Average Current Mode Control
        
}; ///< Boost Converter Control Modes
typedef enum BOOST_CONTROL_MODE_e BOOST_CONTROL_MODE_t; ///< Boost Converter Control Modes data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-public-data-types
 * @struct  BOOST_CONVERTER_CONSTANTS_s
 * @brief   Structure providing all public enumerated lists of constants 
 **************************************************************************************************** */
struct BOOST_CONVERTER_CONSTANTS_s
{
    volatile enum BOOST_STATUS_FLAGS_e StatusFlags; ///< List of all status and control flags of the Boost Converter status word
    volatile enum BOOST_OPSTATES_e OpStateOpCodes;  ///< List of State Machine Operating State IDs
    volatile enum BOOST_SUBSTATES_e SubStateOpCodes;  ///< List of State Machine Sub-State IDs
    volatile enum BOOST_OPSTATE_RETURNS_e OpStateReturnValues;  ///< List of State Machine Operating State Return Values
    volatile enum BOOST_CONTROL_MODE_e ControlModes;  ///< List of Supported Control Modes
};
typedef struct BOOST_CONVERTER_CONSTANTS_s BOOST_CONVERTER_CONSTANTS_t;

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-public-variables
 * @var     BoostConverterConstants
 * @brief   Structure providing all public enumerated lists of constants 
 **************************************************************************************************** */
extern volatile struct BOOST_CONVERTER_CONSTANTS_s BoostConverterConstants;

/*****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct BOOST_CONVERTER_STATUS_s
 * @brief Generic power controller status word
 * @extends BOOST_CONVERTER_s
 * 
 * @details
 * The power controller status/control word contains status (low-byte) and control bits (high-byte). 
 * -# Status Bits:
 *      - ADC_ACTIVE: ADC is active and running (read only)
 *      - PWM_STARTED: PWM is active and running generating ADC triggers (read only)
 *      - POWERSOURCE_DETECTED: A valid power source has been detected allowing the converter to run (read only)
 *      - CS_READ: Current sense feedback ready (read only)
 *      - FORCED_SHUT_DOWN: Control(Status bit for external software components forcing the converter to stay off
 *      - BUSY: Converter is currently going through an internal process (e.g. ramp up/down) (read only)
 *      
 * -# Control Bits
 *      - ENABLE: Enables/Disables the power converter
 *      - AUTORUN: When set, the power converter will automatically start up once all status bits are set accordingly
 *      - GO: Control bit to manually start the power converter if (AUTOSTART=0)
 *  
 **************************************************************************************************** */
struct BOOST_CONVERTER_STATUS_s
{
    union {
    struct{
        volatile bool ready:1;                  ///< Bit #0: status bit, indicating boost converter is initialized and ready to run
        volatile bool adc_active:1;             ///< Bit #1: indicating that ADC has been started and samples are taken
        volatile bool pwm_active:1;             ///< Bit #2: indicating that PWM has been started and ADC triggers are generated
        volatile unsigned :1;                   ///< Bit #3: (reserved)
        volatile bool cs_calib_complete :1;     ///< Bit #4: indicating that current sensor calibration has completed
        volatile bool fault_active :1;          ///< Bit #5: Flag bit indicating system is in enforced shut down mode (usually due to a fault condition)
        volatile bool suspend :1;               ///< Bit #6: Control bit to put the converter in suspend mode (turned off while ENABLE bit is still on)
        volatile bool busy :1;                  ///< Bit #7:  Flag bit indicating that the state machine is executing a process (e.g. startup-ramp)

        volatile bool cs_calib_enable :1;       ///< Bit #8:  Flag bit indicating that current sensors need to calibrated
        volatile bool async_mode :1;            ///< Bit #9:  Control bit suspending the synchronous rectifier switch PWM channel
        volatile unsigned :1;                   ///< Bit #10: (reserved)
        volatile unsigned :1;                   ///< Bit #11: (reserved)
        volatile unsigned :1;                   ///< Bit #12: (reserved)
        volatile bool GO :1;                    ///< Bit #13: When set, the GO-bit fires up the power supply
        volatile bool autorun :1;               ///< Bit #14: Control bit determining if charger is starting automatically or on command (using the GO bit)
        volatile bool enabled :1;               ///< Bit #15: Control bit enabling/disabling the charger port
    } __attribute__((packed)) bits;             ///< data structure for single bit addressing operations

	volatile uint16_t value; // buffer for 16-bit word read/write operations
    };
}; // Boost Converter Status & Control word
typedef struct BOOST_CONVERTER_STATUS_s BOOST_CONVERTER_STATUS_t; // Boost Converter Status & Control word data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct BOOST_STATE_ID_s 
 * @brief data structure for the boost statement ID for sub-operating and operating states 
 * @extends BOOST_CONVERTER_s
 **************************************************************************************************** */
struct BOOST_STATE_ID_s 
{
    union {
    struct { 
        volatile enum BOOST_OPSTATES_e opstate_id;   ///< Most recent operating state of main state machine
        volatile enum BOOST_SUBSTATES_e substate_id; ///< Most recent operating state of active sub state machine
    } bits;
    volatile uint32_t value; // full state ID value access to main and sub-state machine state
    };
}; // Boost Converter State Machine operating state ID
typedef struct BOOST_STATE_ID_s BOOST_STATE_ID_t;  // Boost Converter State Machine operating state ID data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_STARTUP_PERIOD_HANDLER_s
 * @brief   Generic power controller startup period settings
 * @extends BOOST_CONVERTER_STARTUP_s
 * 
 * @details
 * This data structure is used to set the startup settings such as power on delay, power good delay
 * and ramp up time. It further covers private values like startup counters and reference values
 * for voltage and current, which are used internally by the controller (read only) but are still
 * accessible for external code modules for monitoring, diagnostics and fault handling purposes.
 * 
 **************************************************************************************************** */
struct BOOST_STARTUP_PERIOD_HANDLER_s {
    
    volatile uint16_t counter;      ///< Soft-Start Execution Counter (read only)
    volatile uint16_t period;       ///< Soft-Start Period (POD, RAMP PERIOD, PGD, etc.)
    volatile uint16_t reference;    ///< Internal dummy reference used to increment/decrement controller reference
    volatile uint16_t ref_inc_step; ///< Size/value of one reference increment/decrement or this period
    
}; // Power converter soft-start auxiliary variables
typedef struct BOOST_STARTUP_PERIOD_HANDLER_s BOOST_STARTUP_PERIOD_HANDLER_t; // Power converter soft-start auxiliary variables data types

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_STARTUP_VCAP_PRECHARGE_s
 * @brief   Boost converter output capacitor voltage monitor charge-up monitor settings
 * @extends BOOST_CONVERTER_STARTUP_s
 * 
 * @details
 * This data structure is used to set the startup settings such as power on delay, power good delay
 * and ramp up time. It further covers private values like startup counters and reference values
 * for voltage and current, which are used internally by the controller (read only) but are still
 * accessible for external code modules for monitoring, diagnostics and fault handling purposes.
 * 
 **************************************************************************************************** */
struct BOOST_STARTUP_VCAP_PRECHARGE_s {
    
    volatile uint16_t counter;      ///< Soft-Start VCAP Charge-Up Period Counter
    volatile uint16_t period;       ///< Soft-Start VCAP Charge-Up Period (minimum time to wait when voltage has settled)
    volatile uint16_t timeout_counter; ///< Soft-Start VCAP Charge-Up Timeout Counter
    volatile uint16_t timeout;      ///< Soft-Start VCAP Charge-Up Monitor Period Counter Timeout (state machine fault state trigger)
    volatile uint16_t v_drop;       ///< Acceptable voltage drop between input and output voltage when output capacitor is charging up
    
}; // Power converter soft-start Vcap auxiliary variables
typedef struct BOOST_STARTUP_VCAP_PRECHARGE_s BOOST_STARTUP_VCAP_PRECHARGE_t; // Power converter Vcap pre-charge auxiliary variables data types

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_CONVERTER_STARTUP_s
 * @brief   Power Converter Startup Timing Settings
 * @extends BOOST_CONVERTER_s
 * *************************************************************************************************** */
 struct BOOST_CONVERTER_STARTUP_s {
    
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s power_on_delay;
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s power_good_delay;
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s i_ramp;
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s v_ramp;
    volatile struct BOOST_STARTUP_VCAP_PRECHARGE_s vcap_monitor;
    
}; // Power converter start-up settings and variables
typedef struct BOOST_CONVERTER_STARTUP_s  BOOST_CONVERTER_STARTUP_t; // Power converter start-up settings and variables data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_CONVERTER_DATA_s
 * @brief   Publicly accessible data buffer of most recent runtime data values
 * @extends BOOST_CONVERTER_s
 * 
 **************************************************************************************************** */
struct BOOST_CONVERTER_DATA_s {
    
    volatile uint16_t i_sns[BOOST_MPHASE_COUNT];     ///< BOOST output current
    volatile uint16_t i_out;                        ///< BOOST common output current
    volatile uint16_t v_in;                         ///< BOOST input voltage
    volatile uint16_t v_out;                        ///< BOOST output voltage
    volatile uint16_t temp;                         ///< BOOST board temperature
    
    volatile uint16_t control_input;                ///< BOOST most recent control input value (raw input)
    volatile uint16_t control_error;                ///< BOOST most recent control error value
    volatile uint16_t control_output;               ///< BOOST most recent control output value
    
}; // BOOST runtime data buffer
typedef struct BOOST_CONVERTER_DATA_s BOOST_CONVERTER_DATA_t; // BOOST runtime data buffer data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct BOOST_CONVERTER_SETTINGS_s
 * @brief Generic power controller control settings
 * @extends BOOST_CONVERTER_s
 * 
 * @details
 * This data structure is used to set the overall settings to allow external software instances 
 * to control the power control object, such as voltage and current references.
 *  
 **************************************************************************************************** */
struct BOOST_CONVERTER_SETTINGS_s {
    
    volatile enum BOOST_CONTROL_MODE_e control_mode;  ///< Fundamental control mode 
    volatile uint16_t no_of_phases;             ///< number of converter phases
    volatile uint16_t v_ref;                    ///< User reference setting used to control the power converter controller
    volatile uint16_t i_ref;                    ///< User reference setting used to control the power converter controller
    
};  ///> Boost converter main settings
typedef struct BOOST_CONVERTER_SETTINGS_s BOOST_CONVERTER_SETTINGS_t;  ///> Boost converter main settings

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_LOOP_SETTINGS_s
 * @brief   Generic power control loop settings
 * @extends BOOST_CONVERTER_s
 * 
 * @details
 * This data structure is used to set the control loop settings such as pointers to controller 
 * objects and its function calls as well as basic user settings such as reference, feedback
 * signal offsets, trigger delays and minimum/maximum output clamping values.
 * 
 * *************************************************************************************************** */
struct BOOST_LOOP_SETTINGS_s {
    
    // Properties (user settings)
    volatile uint16_t reference;            ///< Control loop reference variable
    volatile uint16_t feedback_offset;      ///< Feedback offset value for calibration or bi-direction feedback signals
    volatile uint16_t trigger_offset;       ///< ADC trigger offset value for trigger fine-tuning
    volatile int16_t  minimum;              ///< output clamping value (minimum)
    volatile uint16_t maximum;              ///< output clamping value (maximum)
    // Control Loop Object
    volatile struct NPNZ16b_s* controller;  ///< pointer to control loop object data structure
    // Function pointers
    volatile uint16_t (*ctrl_Initialize)(volatile struct NPNZ16b_s*); ///< Function pointer to INIT routine
    void (*ctrl_Reset)(volatile struct NPNZ16b_s*); ///< Function pointer to RESET routine
    void (*ctrl_Update)(volatile struct NPNZ16b_s*); ///< Function pointer to UPDATE routine
    void (*ctrl_Precharge)(volatile struct NPNZ16b_s*, volatile fractional, volatile fractional); ///< Function pointer to PRECHARGE routine
    
}; ///< User defined settings for control loops; 
typedef struct BOOST_LOOP_SETTINGS_s BOOST_LOOP_SETTINGS_t; ///< User defined settings for control loops data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_SWITCH_NODE_SETTINGS_s
 * @brief   Generic power converter switch-node specifications
 * @extends BOOST_CONVERTER_s
 * 
 * @details
 * This data structure is used to set the converter switch-node specifications declaring which
 * PWM channel is used as well as its switching frequency, phase-shift, dead times and duty ratio
 * limits.
 * 
 * *************************************************************************************************** */
struct BOOST_SWITCH_NODE_SETTINGS_s {
    
    volatile uint16_t pwm_instance;         ///< number of the PWM channel used
    volatile uint16_t gpio_instance;        ///< GPIO instance of the selected PWM generator
    volatile uint16_t gpio_high;            ///< GPIO port pin-number of PWMxH of the selected PWM generator
    volatile uint16_t gpio_low;             ///< GPIO port pin-number of PWMxL of the selected PWM generator
    volatile bool     swap_outputs;         ///< Selecting if PWMxH (default) or PWMxL should be the leading PWM output
    volatile bool     master_period_enable; ///< Selecting MASTER or Individual period register
    volatile bool     high_resolution_enable; ///< Selecting if PWM module should use high-resolution mode 
    volatile bool     sync_drive;           ///< Selecting if switch node is driven in synchronous or asnchronous mode
    volatile uint16_t period;               ///< Switching period
    volatile uint16_t phase;                ///< Switching signal phase-shift
    volatile uint16_t duty_ratio_init;      ///< Initial duty cycle when the PWM module is being turned on
    volatile uint16_t duty_ratio_min;       ///< Absolute duty cycle minimum during normal operation
    volatile uint16_t duty_ratio_max;       ///< Absolute duty cycle maximum during normal operation
    volatile uint16_t dead_time_rising;     ///< Dead time setting at rising edge of a half-bridge drive
    volatile uint16_t dead_time_falling;    ///< Dead time setting at falling edge of a half-bridge drive
    volatile uint16_t leb_period;           ///< Leading-Edge Blanking period
    volatile uint16_t trigger_scaler;       ///< PWM triggers for ADC will be generated every n-th cycle
    volatile uint16_t trigger_offset;       ///< PWM triggers for ADC will be offset by n cycles
    
}; ///< Switching signal timing settings
typedef struct BOOST_SWITCH_NODE_SETTINGS_s  BOOST_SWITCH_NODE_SETTINGS_t; ///< Switching signal timing settings data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_ADC_INPUT_SCALING_s 
 * @brief   Generic power converter feedback specifications
 * @extends BOOST_ADC_INPUT_SETTINGS_s
 * @details
 * This data structure is used to set the converter feedback specifications declaring which
 * ADC channels are used including the individual AD input configuration such as trigger mode,
 * input mode, result format and value normalization.
 * 
 * *************************************************************************************************** */
struct BOOST_ADC_INPUT_SCALING_s {
    
    volatile int16_t factor; ///< Fractional scaling factor (range -1 ... 0.99969)
    volatile int16_t scaler; ///< Feedback bit-shift scaler used for number normalization
    volatile int16_t offset; ///< Signal offset as signed integer to be subtracted from ADC input

}; ///< ADC input signal scaling = (ADCBUF - <offset>) * <factor> >> 2^<scaler>
typedef struct BOOST_ADC_INPUT_SCALING_s BOOST_ADC_INPUT_SCALING_t; ///< ADC input signal scaling data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_ADC_INPUT_SETTINGS_s
 * @brief   Generic power converter ADC input channel configuration
 * @extends BOOST_FEEDBACK_SETTINGS_s
 * *************************************************************************************************** */
struct BOOST_ADC_INPUT_SETTINGS_s {
    
    volatile bool enabled;                  ///< input channel enable bit
    volatile uint16_t* adc_buffer;          ///< pointer to ADC result buffer
    volatile uint16_t gpio_instance;        ///< GPIO instance of the selected PWM generator
    volatile uint8_t adc_input;             ///< number of the ADC input channel used
    volatile uint8_t adc_core;              ///< number of the ADC core connected to the selected channel
    volatile uint8_t trigger_source;        ///< input channel trigger source
    volatile bool interrupt_enable;         ///< input channel interrupt enable bit
    volatile bool early_interrupt_enable;   ///< input channel early interrupt enable bit
    volatile bool differential_input;       ///< input channel differential mode enable bit
    volatile bool signed_result;            ///< input channel singed result mode enable bit
    volatile bool level_trigger;            ///< input channel level trigger mode enable bit
    volatile struct BOOST_ADC_INPUT_SCALING_s scaling; ///< normalization scaling settings

}; ///< ADC input channel configuration
typedef struct BOOST_ADC_INPUT_SETTINGS_s BOOST_ADC_INPUT_SETTINGS_t; ///< ADC input channel configuration data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct  BOOST_FEEDBACK_SETTINGS_s
 * @brief   Power converter feedback input channel declarations
 * @extends BOOST_CONVERTER_s
 * *************************************************************************************************** */
struct BOOST_FEEDBACK_SETTINGS_s {
    
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_vin;                       ///< ADC input sampling input voltage
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_vout;                      ///< ADC input sampling output voltage
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_isns[BOOST_MPHASE_COUNT];   ///< ADC input sampling phase current
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_temp;                      ///< ADC input sampling temperature
    
}; ///< Boost converter feedback declarations
typedef struct BOOST_FEEDBACK_SETTINGS_s BOOST_FEEDBACK_SETTINGS_t; ///< Boost converter feedback declarations data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct BOOST_GPIO_INSTANCE_s
 * @brief Generic power converter GPIO specifications
 * @extends BOOST_GPIO_SETTINGS_s
 * 
 * @details
 * This data structure is used to set the converter GPIO specifications declaring which
 * if and which additional GPIOs are used by the converter controller, such as POWER_GOOD.
 * 
 * *************************************************************************************************** */
struct BOOST_GPIO_INSTANCE_s {
    
    volatile bool enabled;      ///< Specifies, if this IO is used or not
    volatile uint16_t port;     ///< GPIO port instance number (0=Port RA, 0=Port RB, 0=Port RC, etc.)
    volatile uint16_t pin;      ///< GPIO port pin number
    volatile uint16_t polarity; ///< Output polarity, where 0=ACTIVE HIGH, 1=ACTIVE_LOW
    volatile uint16_t io_type;  ///< Input/Output definition (0=push-pull output, 1=input, 2=open-drain output)

}; ///< GPIO instance of the converter control GPIO
typedef struct BOOST_GPIO_INSTANCE_s BOOST_GPIO_INSTANCE_t; ///< GPIO instance of the converter control GPIO data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-private-data-types
 * @struct BOOST_GPIO_SETTINGS_s
 * @brief Generic power converter GPIO specifications
 * @extends BOOST_CONVERTER_s
 * *************************************************************************************************** */
struct BOOST_GPIO_SETTINGS_s {
    
    volatile struct BOOST_GPIO_INSTANCE_s EnableInput; ///< External ENABLE input
    volatile struct BOOST_GPIO_INSTANCE_s PowerGood; ///< Power Good Output

}; ///< GPIO instance of the converter control GPIO
typedef struct BOOST_GPIO_SETTINGS_s BOOST_GPIO_SETTINGS_t; ///< GPIO instance of the converter control GPIO data type

/****************************************************************************************************
 * @ingroup lib-layer-boost-converter-properties-public-data-types
 * @struct  BOOST_CONVERTER_s
 * @brief   Boost Converter data object
 *****************************************************************************************************/
struct BOOST_CONVERTER_s 
{
    volatile struct BOOST_CONVERTER_STATUS_s status;     ///< BOOST operation status bits 
    volatile struct BOOST_STATE_ID_s state_id;           ///< BOOST state machine operating state ID
    volatile struct BOOST_CONVERTER_STARTUP_s startup;   ///< BOOST startup timing settings 
    volatile struct BOOST_CONVERTER_SETTINGS_s set_values;///< Control field for global access to references
    volatile struct BOOST_CONVERTER_DATA_s data;         ///< BOOST runtime data
    volatile struct BOOST_FEEDBACK_SETTINGS_s feedback;  ///< BOOST converter feedback settings

    volatile struct BOOST_SWITCH_NODE_SETTINGS_s sw_node[BOOST_MPHASE_COUNT]; ///< BOOST converter switch node settings
    volatile struct BOOST_GPIO_SETTINGS_s gpio;          ///< BOOST converter additional GPIO specification
    
    volatile struct BOOST_LOOP_SETTINGS_s v_loop;        ///< BOOST voltage control loop object
    volatile struct BOOST_LOOP_SETTINGS_s i_loop[BOOST_MPHASE_COUNT]; ///< BOOST Current control loop objects
    
}; ///< BOOST control & monitoring data structure
typedef struct BOOST_CONVERTER_s BOOST_POWER_CONTROLLER_t; ///< BOOST control & monitoring data structure data type


//#else
//    #pragma message "Warning: dev_boost_typedef.h inclusion bypassed"
#endif	/* BOOST_CONVERTER_TYPE_DEF_H */
