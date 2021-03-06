# Boost Converter Device Driver

<span id="startDoc"> </span> <!-- start tag for internal references -->

### Class
PowerSmart™ Firmware Framework Component

### Summary
Voltage and average current mode controlled single- and multiphase asynchronous or synchronous boost converter device driver.

### Table Of Contents

- [Introduction](#intro)
- [Library Usage Guidelines](#lib_use)
- [API Quick-Start Guide](#api_guide)
- [API Public Data Object](#api_objects)
- [Boost Converter State Machine](#state_machine)
- [History](#history)


<span id="intro"> </span>
### Introduction
#### Supported Variants
* Single Phase Converter
* Multiphase Converter 
* Synchronous Boost Converter
* Asynchronous Boost Converter 

#### Special Features
* Tunable Startup Timing
* Current Ramp-Up State for Constant Current Sources for battery chargers (automatic)
* Slope controlled Reference Tuning during normal operation
* Current Sense Calibration Extension (optional)
* GPIO extensions for Power Good Output and Enable Input (optional)

#### Description
This generic synchronous boost converter device driver provides a state machine, peripheral configuration template and controller interface for driving one single- or multiphase synchronous or asynchronous boost converter instance in voltage or average current mode control.

All settings of this code library are made in the Boost Converter Controller Object defined by the BOOST_POWER_CONTROLLER_s data structure. Each API function takes an pointer to a Boost Converter Controller Object of type `struct BOOST_POWER_CONTROLLER_s` as parameter. This allows to define multiple Boost Converter Controller Objects and using the same library files to drive and control multiple, independent converters in parallel. 

#### Tool Support
This device driver uses control loop code based on `NPNZ16b` data objects which is generated by the [PowerSmart™ Digital Control Library Designer (DCLD)](https://areiter128.github.io/DCLD). 


[[back](#startDoc)]

<span id="lib_use"> </span>
### Library Usage Guidance

This code library repository must be included in an independent directory within the target project. Changes to any of the files of this repository in the target project environment can be pushed back to this library repository from where these changes can be distributed to one, more or all target projects this library has been used in. The upgrade of library files in a particular target project needs to be performed individually, allowing to individually manage the device driver version used.

#### Adding Subtree Repository

##### Step 1 - Adding Subtree Repository to Target Project
###### a) Using Sourcetree Application

Open *Sourcetree* Application
* Open menu *Repository* → *Repository Settings*
* Click *Add* to open the Add Repository dialog

Inside the Repository dialog
* Enter *Remote Name* `subrepo-boost`
* Enter clone URL/path https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-boost-converter.git
* Under *Optional extended integration* → *Remote Account* select your user account
* Click *OK* to close the dialog

###### b) Using Git Bash

Open Git Bash at root of target project repository and use the following command for adding the new subtree remote:

* `$ git remote add subrepo-boost https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-boost-converter.git`

##### Step 2) Cloning Subtree Repository

Further using Git Bash use the `subtree add` command to clone the contents of this code library into the target project

* `$ git subtree add --prefix=<code_library_target> subrepo-boost main --squash`

with `<code_library_target>` = path to sub-folder within the target project directory structure this code library should be cloned to (e.g. my_project.X/sources/power_control/devices).

#### 3) Pulling latest version from Library Repository
When a new version of this code library is available, you can pull it by using the `subtree pull` command in the Git Bash:

`$ git subtree pull --prefix=<code_library_target> subtree-boost main --squash`

with `<code_library_target>` = path to sub-folder within the target project directory structure this code library has been cloned to (e.g. my_project.X/sources/fault_handler/drivers).

#### 4) Pushing new version back to Library Repository
When changes have been made to files of this code library, the new version can be pushed back to the library repository by using the `subtree push` command in the Git Bash:

`$ git subtree push --prefix=<code_library_target> subtree-boost feature/version-update --squash`

with `<code_library_target>` = path to sub-folder within the target project directory structure this code library has been cloned to (e.g. my_project.X/sources/fault_handler/drivers).

<span style="color:red">
    <u><b>Note:</b></u><br>
    Pushing directly to the library project 'main' or 'develop' branches may be prohibited. 
    Hence, <i><u><b>changes can only be pushed to feature branches</b></u></i>. A Pull Request is required to review and merge changes to 'develop'. Once changes have been approved and merged int 'develop', they may be merged into branch 'main' and thus released as new version through another pull request. This new version of 'main' can be tagged with a new version number and pulled into target projects.
</span>


<br>&nbsp;

[[back](#startDoc)]

<span id="api_guide"> </span>
### API Quick-Start Guide

#### API Public Functions

The API of this device driver provides the following standard power converter functions:

```c
volatile uint16_t drv_BoostConverter_Initialize(volatile BOOST_POWER_CONTROLLER_t* boostInstance);
volatile uint16_t drv_BoostConverter_Execute(volatile BOOST_POWER_CONTROLLER_t* boostInstance);
volatile uint16_t drv_BoostConverter_Start(volatile BOOST_POWER_CONTROLLER_t* boostInstance);
volatile uint16_t drv_BoostConverter_Stop(volatile BOOST_POWER_CONTROLLER_t* boostInstance);
volatile uint16_t drv_BoostConverter_Suspend(volatile BOOST_POWER_CONTROLLER_t* boostInstance);
volatile uint16_t drv_BoostConverter_Resume(volatile BOOST_POWER_CONTROLLER_t* boostInstance);
```

Each of these functions takes a function call parameter of type *struct BOOST_POWER_CONTROLLER_s* (see blow) to be applied to a particular boost converter object and returns an integer return value indicating success (= 1) or failure (= 0) of the function execution.

* **`uint16_t drv_BoostConverter_Initialize(volatile BOOST_POWER_CONTROLLER_t* boostInstance)`**<br>&nbsp;
Initializes the boost converter object by first loading the built-in peripheral configuration templates into the required peripheral special function registers, adding the user settings specified in the *struct BOOST_POWER_CONTROLLER_s* Boost Converter data object. After a successful peripheral initialization the specified control loop objects will be reset and their histories cleared. <br>&nbsp;<br>All peripherals and control loops will be initialized but kept disabled. The state machine will later enable the peripherals and controller objects used in their proper enable sequence during the startup procedure and no user code intervention is required.<br>&nbsp;<br>

* **`uint16_t drv_BoostConverter_Start(volatile BOOST_POWER_CONTROLLER_t* boostInstance)`**<br>&nbsp;
The *BoostConverter Start* function is initiating the state machine from scratch, by enabling the fundamental peripherals PWM and ADC to start the acquisition of feedback data allowing the state machine to analyze the most recent operating conditions. <br>&nbsp;
Function *BoostConverter Execute* **should be** called after the execution of this function at a constant frequency.<br>&nbsp;

* **`uint16_t drv_BoostConverter_Stop(volatile BOOST_POWER_CONTROLLER_t* boostInstance)`**<br>&nbsp;
The *BoostConverter Stop* function is terminating the state machine and disabling the fundamental peripherals PWM and ADC to stop the acquisition of feedback data stopping the analysis of the most recent operating conditions. <br>&nbsp;
Function *BoostConverter Execute* should **not** be called after the execution of this function.<br>&nbsp;

* **`uint16_t drv_BoostConverter_Suspend(volatile BOOST_POWER_CONTROLLER_t* boostInstance)`**<br>&nbsp;
The *BoostConverter Suspend* function is terminating the state machine but keeps the fundamental peripherals PWM and ADC running to continue the acquisition of feedback data allowing the analysis of the most recent operating conditions. <br>&nbsp;
Function *BoostConverter Execute* **should continued to be** called after the execution of this function at a constant frequency.<br>&nbsp;

* **`uint16_t drv_BoostConverter_Resume(volatile BOOST_POWER_CONTROLLER_t* boostInstance)`**<br>&nbsp;
The *BoostConverter Resume* function is re-initiating the state machine to recover from RESET during which the fundamental peripherals PWM and ADC are running to continue the acquisition of feedback data allowing the analysis of the most recent operating conditions. <br>&nbsp;
Function *BoostConverter Execute* **should be** called after the execution of this function at a constant frequency.<br>&nbsp;

* **`uint16_t drv_BoostConverter_Execute(volatile BOOST_POWER_CONTROLLER_t* boostInstance)`**<br>&nbsp;
The *BoostConverter Execute* function is executing the state machine managing the initialization, startup and online regulation in voltage and average current mode control. It provides mechanisms for fault handlers to shut down and recover the power supply control in controlled, deterministic procedures using the *drv_BoostConverter_Suspend* and *drv_BoostConverter_Resume* function calls described above.<br>&nbsp;

[[back](#startDoc)]

<span id="api_objects"> </span>
#### API Public Data Objects

The Boost Converter Data Object holds all configuration data of the user-defined boost converter, covering

* Functional Declarations
    * Startup Timing Declarations
    * User Set Value Declarations
<br> 
* Peripheral Configuration Declarations
    * Switch Node Declarations (PWM and ACMP Configuration)
    * Feedback Channel Declarations (ADC Configuration)
    * GPIO Declarations (GPIO Configuration)
    * Voltage Loop Controller Declarations 
    * Current Loop Controller Declarations (ACMC only, one controller per phase required)
<br> 
* Status and Control Bit Declarations
    
<br> 
* Read-Only Data and Status Information
    * State Machine State Monitoring
    * Runtime Data 

Before the state machine can be used, at least one boost converter data object has to be defined and initialized in the application layer of the user project.

```c
struct BOOST_POWER_CONTROLLER_s
{ 
    volatile struct BOOST_CONVERTER_STATUS_s status;     // BOOST operation status bits 
    volatile struct BOOST_STATE_ID_s state_id;           // BOOST state machine operating state ID
    volatile struct BOOST_CONVERTER_STARTUP_s startup;   // BOOST startup timing settings 
    volatile struct BOOST_CONVERTER_SETTINGS_s set_values; // Control field for global access to references
    volatile struct BOOST_CONVERTER_DATA_s data;         // BOOST runtime data
    volatile struct BOOST_FEEDBACK_SETTINGS_s feedback;  // BOOST converter feedback settings

    volatile struct BOOST_SWITCH_NODE_SETTINGS_s sw_node[BOOST_MPHASE_COUNT]; // BOOST converter switch node settings
    volatile struct BOOST_GPIO_SETTINGS_s gpio;          // BOOST converter additional GPIO specification
    
    volatile struct BOOST_LOOP_SETTINGS_s v_loop;        // BOOST voltage control loop object
    volatile struct BOOST_LOOP_SETTINGS_s i_loop[BOOST_MPHASE_COUNT]; // BOOST Current control loop objects
    
}; // BOOST control & monitoring data structure
typedef struct BOOST_POWER_CONTROLLER_s BOOST_POWER_CONTROLLER_t; // BOOST control & monitoring data structure
```
<br>&nbsp;
##### Sub Structure  `struct BOOST_CONVERTER_STATUS_s`

The boost converter status bit contains eight read-only, auto-set/clear status bits and eight control bits:
```c
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
    
};
typedef struct BOOST_CONVERTER_STATUS_s BOOST_CONVERTER_STATUS_t;
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_STATE_ID_s`

The boost converter State ID is controlled by the state machine and holds the most recent operating state and subsequent sub-state in two separated 16-bit wide variables. While the state machine is executing sequences of operating- and/or sub-states, the busy flag (bit <7> in the status word) will be set.

```c
struct BOOST_STATE_ID_s 
{
    union {
    struct { 
        volatile enum BOOST_OPSTATES_e opstate_id;   ///< Most recent operating state of main state machine
        volatile enum BOOST_SUBSTATES_e substate_id; ///< Most recent operating state of active sub state machine
    } bits;
    volatile uint32_t value; // full state ID value access to main and sub-state machine state
    };
    
};
typedef struct BOOST_STATE_ID_s BOOST_STATE_ID_t;
```

<br>&nbsp;

##### Sub Structures  `struct BOOST_STARTUP_PERIOD_HANDLER_s` and `struct BOOST_CONVERTER_STARTUP_s`

The boost converter startup declaration consists of multiple delay and ramp-up period, which are defined in the `BOOST_CONVERTER_STARTUP_s` data structure. 

```c
struct BOOST_CONVERTER_STARTUP_s {
    
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s power_on_delay;   ///< Startup POWER ON DELAY in state machine ticks
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s power_good_delay; ///< Startup POWER GOOD DELAY in state machine ticks
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s i_ramp;           ///< Startup Current Ramp-Up period in state machine ticks
    volatile struct BOOST_STARTUP_PERIOD_HANDLER_s v_ramp;           ///< Startup Voltage Ramp-Up period in state machine ticks
    volatile struct BOOST_STARTUP_VCAP_PRECHARGE_s vcap_monitor;    ///< Output Capacitor Charging Time period in state machine ticks
    
}; // Power converter start-up settings and variables
typedef struct BOOST_CONVERTER_STARTUP_s BOOST_CONVERTER_STARTUP_t; // Power converter start-up settings and variables
```
Each delay is defined by a delay management data structure of type `BOOST_STARTUP_PERIOD_HANDLER_t`, defining a period value and a independent counter variable allowing the state machine to count down the specified period. For the Voltage and Current Ramp-Up Periods the control reference will be incremented by the specified reference increment in each counter step until the nominal reference specified in `BOOST_CONVERTER_SETTINGS_s` is met.
```c
struct BOOST_STARTUP_PERIOD_HANDLER_s {
    
    volatile uint16_t counter;      ///< Soft-Start Execution Counter (read only)
    volatile uint16_t period;       ///< Soft-Start Period (POD, RAMP PERIOD, PGD, etc.)
    volatile uint16_t reference;    ///< Internal dummy reference used to increment/decrement controller reference
    volatile uint16_t ref_inc_step; ///< Size/value of one reference increment/decrement or this period
    
}; // Power converter soft-start auxiliary variables
typedef struct BOOST_STARTUP_PERIOD_HANDLER_s BOOST_STARTUP_PERIOD_HANDLER_t; // Power converter soft-start auxiliary variables
```
This delay is defined by a delay management data structure of type `BOOST_STARTUP_VCAP_PRECHARGE_s`, defining a period value and a independent counter variable allowing the state machine to count down the specified period which needs to expire while the output voltage is settling in a defined range. The required voltage range is defined by comparing the most recent output voltage with the most recent value of the input voltage minus a user-defined voltage drop (e.g. VIN - 1V).
The total duration of this period may vary based on the real charging time of the output capacitor. To prevent the state machine from stalling in this state, an additional timeout period can be specified. If this period expires, the state machine will return an error and reset, effectively initiating a restart attempt.
```c
struct BOOST_STARTUP_VCAP_PRECHARGE_s {
    
    volatile uint16_t counter;      ///< Soft-Start VCAP Charge-Up Period Counter
    volatile uint16_t period;       ///< Soft-Start VCAP Charge-Up Period (minimum time to wait when voltage has settled)
    volatile uint16_t timeout_counter; ///< Soft-Start VCAP Charge-Up Timeout Counter
    volatile uint16_t timeout;      ///< Soft-Start VCAP Charge-Up Monitor Period Counter Timeout (state machine fault state trigger)
    volatile uint16_t v_drop;       ///< Acceptable voltage drop between input and output voltage when output capacitor is charging up
    
}; // Power converter soft-start Vcap auxiliary variables
typedef struct BOOST_STARTUP_VCAP_PRECHARGE_s BOOST_STARTUP_VCAP_PRECHARGE_t; // Power converter Vcap pre-charge auxiliary variables data types
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_CONVERTER_SETTINGS_s`

The basic converter settings, such as control mode, number of converter phases, voltage and current reference, are specified in the `BOOST_CONVERTER_SETTINGS_s` data structure. The current reference will only be valid if the control mode is set to Average Current Mode Control (ACMC) and will be ignored in VOltage Mode Control (VMC)

```c
struct BOOST_CONVERTER_SETTINGS_s {
    
    volatile BOOST_CONTROL_MODE_e control_mode;  ///< Fundamental control mode 
    volatile uint16_t no_of_phases;             ///< number of converter phases
    volatile uint16_t v_ref;                    ///< User reference setting used to control the power converter controller
    volatile uint16_t i_ref;                    ///< User reference setting used to control the power converter controller
    
};  ///> Boost converter main settings
typedef struct BOOST_CONVERTER_SETTINGS_s  BOOST_CONVERTER_SETTINGS_t;  ///> Boost converter main settings
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_CONVERTER_DATA_s`

The basic converter data buffer `BOOST_CONVERTER_DATA_s` data structure is used to publish most recent runtime data across the firmware. During operation, control loops and state machine will continuously update this public data buffer. When the boost converter is turned off using the *dev_BoostConverter_Stop()* function, the data buffer will be cleared and won't get updated anymore.

```c
struct BOOST_LOOP_SETTINGS_s {
    
    volatile uint16_t i_sns[BOOST_MPHASE_COUNT];     ///< BOOST output current
    volatile uint16_t i_out;                        ///< BOOST common output current
    volatile uint16_t v_in;                         ///< BOOST input voltage
    volatile uint16_t v_out;                        ///< BOOST output voltage
    volatile uint16_t temp;                         ///< BOOST board temperature
    
    volatile uint16_t control_input;                ///< BOOST most recent control input value (raw input)
    volatile uint16_t control_error;                ///< BOOST most recent control error value
    volatile uint16_t control_output;               ///< BOOST most recent control output value
    
}; // BOOST runtime data 
typedef struct BOOST_LOOP_SETTINGS_s BOOST_CONVERTER_DATA_t; // BOOST runtime data
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_LOOP_SETTINGS_s`

Boost converter control loop settings specify default values for control reference, feedback offset, ADC trigger offset and anti-windup minimum and maximum values, which are used during initialization. Further a pointer to a control loop object of type `NPNZ16b_t` is declared, which holds all the detailed information of the specific control loop, such as filter coefficients, feedback input and control output scaling, pointers to data provider targets and further parameters for advanced control options. 

```c
struct BOOST_LOOP_SETTINGS_s {
    
    // Properties (user settings)
    volatile uint16_t reference;            ///< Control loop reference variable
    volatile uint16_t feedback_offset;      ///< Feedback offset value for calibration or bi-direction feedback signals
    volatile uint16_t trigger_offset;       ///< ADC trigger offset value for trigger fine-tuning
    volatile uint16_t minimum;              ///< output clamping value (minimum)
    volatile uint16_t maximum;              ///< output clamping value (maximum)
    // Control Loop Object
    volatile struct NPNZ16b_s* controller;  ///< pointer to control loop object data structure
    // Function pointers
    volatile uint16_t (*ctrl_Initialize)(volatile struct NPNZ16b_s*); ///< Function pointer to INIT routine
    void (*ctrl_Reset)(volatile struct NPNZ16b_s*); ///< Function pointer to RESET routine
    void (*ctrl_Update)(volatile struct NPNZ16b_s*); ///< Function pointer to UPDATE routine
    void (*ctrl_Precharge)(volatile struct NPNZ16b_s*, volatile fractional, volatile fractional); ///< Function pointer to PRECHARGE routine
    
}; ///< User defined settings for control loops; 
typedef struct BOOST_LOOP_SETTINGS_s BOOST_LOOP_SETTINGS_t;  ///< User defined settings for control loops;
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_SWITCH_NODE_SETTINGS_s`

The switch node settings of the boost converter data object specify the user parameters of the PWM configuration supporting a synchronous or asynchronous boost converter switching signal generator. Each converter phase requires its independent switch node definition. The synchronization of multiple PWM generators is automatically configured during the peripheral configuration by the initialization driver `dev_boost_pconfig.c` of the boost converter device driver. This driver will first load the default peripheral configuration from the built-in boost converter peripheral templates overwriting user parameters with the settings found in this data structure.

```c
struct BOOST_SWITCH_NODE_SETTINGS_s {
    
    volatile uint16_t pwm_instance;         ///< number of the PWM channel used
    volatile uint16_t gpio_instance;        ///< GPIO instance of the selected PWM generator
    volatile uint16_t gpio_high;            ///< GPIO port pin-number of PWMxH of the selected PWM generator
    volatile uint16_t gpio_low;             ///< GPIO port pin-number of PWMxL of the selected PWM generator
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
typedef struct BOOST_SWITCH_NODE_SETTINGS_s BOOST_SWITCH_NODE_SETTINGS_t; ///< Switching signal timing settings
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_ADC_INPUT_SETTINGS_s` and `BOOST_FEEDBACK_SETTINGS_s`

ADC input configuration of feedback channels is set by the `BOOST_ADC_INPUT_SETTINGS_s` data structure. Each converter offers the following standard feedback input channels in its `BOOST_FEEDBACK_SETTINGS_s` data structure:

* Output Voltage
* Input Voltage
* Inductor Current (one for each converter phase)
* Temperature

```c
struct BOOST_FEEDBACK_SETTINGS_s {
    
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_vin;                       ///< ADC input sampling input voltage
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_vout;                      ///< ADC input sampling output voltage
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_isns[BOOST_MPHASE_COUNT];   ///< ADC input sampling phase current
    volatile struct BOOST_ADC_INPUT_SETTINGS_s ad_temp;                      ///< ADC input sampling temperature
    
}; ///< Boost converter feedback declarations
typedef struct BOOST_FEEDBACK_SETTINGS_s BOOST_FEEDBACK_SETTINGS_t;  ///< Boost converter feedback declarations
```

Each feedback channel can be enabled or disabled. Disabled channels will be ignored during initialization and will remain inactive during operation. The peripheral configuration is performed by the initialization driver `dev_boost_pconfig.c` of the boost converter device driver. This driver will first load the default peripheral configuration from the built-in boost converter peripheral templates overwriting user parameters with the settings found in this data structure.

```c
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
typedef struct BOOST_ADC_INPUT_SETTINGS_s BOOST_ADC_INPUT_SETTINGS_t; ///< ADC input channel configuration
```

Supporting calculations of power, voltage ratios, gains or Root Mean Square (RMS) values feedback channels may have to be scaled/normalized. For this purpose the `BOOST_ADC_INPUT_SCALING_s` data structure was added allowing users to specify the feedback value scaling information in form of a fast floating point slope and integer offset value.

```c
struct BOOST_ADC_INPUT_SCALING_s {
    
    volatile int16_t factor; ///< Fractional scaling factor (range -1 ... 0.99969)
    volatile int16_t scaler; ///< Feedback bit-shift scaler used for number normalization
    volatile int16_t offset; ///< Signal offset as signed integer to be subtracted from ADC input

}; ///< ADC input signal scaling = (ADCBUF - <offset>) * <factor> >> 2^<scaler>
typedef struct BOOST_ADC_INPUT_SCALING_s BOOST_ADC_INPUT_SCALING_t; ///< ADC input signal scaling = (ADCBUF - <offset>) * <factor> >> 2^<scaler>
```

<br>&nbsp;

##### Sub Structure  `struct BOOST_GPIO_INSTANCE_s` and `BOOST_GPIO_SETTINGS_s`

The boost converter device driver supports one Enable input (EN) and one Power Good output (PG) as two basic general purpose input/outputs (GPIO) for low-level hardware sequencing of converter stages.

```c
struct BOOST_GPIO_SETTINGS_s {
    
    volatile struct BOOST_GPIO_INSTANCE_s EnableInput; ///< External ENABLE input
    volatile struct BOOST_GPIO_INSTANCE_s PowerGood; ///< Power Good Output

}; ///< GPIO instance of the converter control GPIO
typedef struct BOOST_GPIO_SETTINGS_s BOOST_GPIO_SETTINGS_t; ///< GPIO instance of the converter control GPIO
```

Each GPIO can be configured by the settings specified in the `BOOST_GPIO_INSTANCE_s` data structure. The Input/Output type can be set to 

* Input (=1, max. input voltage = 3.3 V)
* Push-Pull Output (=0, max. sink-/source-current = 4 mA, max. output voltage = 3.3 V)
* Open-Drain Output (=0, max. sink-current = 4 mA, max. output voltage = 3.3/5.0 V)

```c
struct BOOST_GPIO_INSTANCE_s {
    
    volatile bool enabled;      ///< Specifies, if this IO is used or not
    volatile uint16_t port;     ///< GPIO port instance number (0=Port RA, 0=Port RB, 0=Port RC, etc.)
    volatile uint16_t pin;      ///< GPIO port pin number
    volatile uint16_t polarity; ///< Output polarity, where 0=ACTIVE HIGH, 1=ACTIVE_LOW
    volatile uint16_t io_type;  ///< Input/Output definition (0=push-pull output, 1=input, 2=open-drain output)

}; ///< GPIO instance of the converter control GPIO
typedef struct BOOST_GPIO_INSTANCE_s BOOST_GPIO_INSTANCE_t; ///< GPIO instance of the converter control GPIO
```


[[back](#startDoc)]

<span id="state_machine"> </span>
### Boost Converter State Machine

The Boost Converter State Machine is broken down into two major segments, Default Operating States (opstate) and Sub-States (substate)

* **Default Operating States**<br>&nbsp;

    * *State_Initialize*
    Initializes the pre-configured chip peripherals enabling the PWM and ADC to start the continuous acquisition of data allowing the analysis of the system status.<br>&nbsp;
    * *State_Reset*
    Disables the PWM outputs while keeping the PWM itself running as trigger generator of the ADC module, and clears dynamic control parameters such as error and control histories to ensure a deterministic state at startup.<br>&nbsp;
    * *State_Standby*
    Waits for all status bits to be set, fault and suspend bits to be cleared and the GO bit to be set.<br>&nbsp;
    * *State_RampUp*
    The Ramp-Up state splits up into converter-specific startup sub-states, managing the specific startup procedure of a synchronous or asynchronous single- or multiphase boost converter topology. This topology-specific startup procedure also includes the startup timing specified by the `BOOST_CONVERTER_STARTUP_s` data structure parameters.<br>&nbsp;
    * *State_Online*
    Once the start procedure has been completed successfully, the converter state machine drops into constant regulation mode, where it will remain until the converter is shut-down or suspended. During constant regulation the control reference is monitored. If the value of the control reference is changed, the state machine will tune into the new reference by generating a defined defined transition ramp using the ramp slope specified in the startup voltage ramp timing.<br>&nbsp;
    * *State_Error*
    Should any of the states ever return an error, the converter will be shut down and the state machine will fall back into an error state, from which is will recover automatically with the fault_active flag (bit <5> of the status word) being set.<br>&nbsp;


* **Topology-Specific Startup Sub-States**<br>&nbsp;

The boost converter startup sub-state machine manages the power topology-specific startup procedure of a boost converter, tailored to its configuration, control and operating mode. It also incorporates the user definition of the startup timing specified in the `BOOST_CONVERTER_STARTUP_s` data structure.


* *Substate_VCapMonitor*
This state is a special state for the boost converter topology. As in a boost converter the output capacitor is automatically charging up when power is applied to its input, this state is monitoring the output voltage (VCap) waiting for it to settle before the start-up procedure is continued. This state allows users to specify a waiting period which has to expire before the voltage is considered to be stable. In addition, this waiting period is backed up by a timeout counter, defining the maximum time period it should take the output voltage to settle. If the timeout period is expired, the state machine will return an error and reset, effectively initiating a restart attempt.<br>&nbsp;
The voltage level at which the output capacitor is considered to be charged is determined by the most recent input voltage minus the expected voltage drop across the rectifier diode under no-load conditions..<br>&nbsp;
Charging period, timeout and voltage drop threshold are specified in the `BOOST_STARTUP_VCAP_PRECHARGE_s` sub-structure extension of the `BOOST_CONVERTER_STARTUP_s` data structure.<br>&nbsp;
Users can disable this additional state by setting the period setting to zero (=0)<br>&nbsp;
* *SubState_PowerOnDelay*
Waiting period while the converter is kept in a disabled state until the Power-On Delay (POD) specified in the `BOOST_CONVERTER_STARTUP_s` data structure has expired.<br>&nbsp;
* *SubState_PrepareVRampUp*
In this state the most recent voltage ratio between the inductor terminals is measured and the expected duty ratio at the startup frequency is calculated to ensure a smooth startup without accidental reverse current or forward current spikes at startup against a pre-biased output. The estimated startup duty ratio value is then programmed into PWM registers and the control loop histories get pre-charged and the startup control reference is set to match the output voltage.<br>&nbsp;
* *SubState_VRampUp*
In this state the PWM outputs and control loops are enabled and the converter starts to operate. Due to the ramp-up pre-charge of the previous state, the expected output power is close to zero. With every execution cycle of the state machine the control reference is linearly incremented by the given amount of ticks until the ramp-up reference value matches desired value specified by the user by `v_ref` in the `BOOST_CONVERTER_SETTINGS_s` data structure.<br>&nbsp;
* *SubState_IRampUp*
This state is only executed in Average Current Mode Control (ACMC) and only if the voltage loop hist an output saturation limit during the execution of the previous voltage ramp-up state. This additional output current ramp-up procedure has been introduced as controlled constant-current ramp-up control when ramping up the output against large capacitive loads or when this boost converter device driver is used in a constant current source application.<br>&nbsp;
* *SubState_PowerGoodDelay*
Waiting period while the converter is kept in a enabled state at constant output regulation until the Power Good Delay (PGD) specified in the `BOOST_CONVERTER_STARTUP_s` data structure has expired.<br>&nbsp;

[[back](#startDoc)]

---
<span id="history"> </span>
##### History:
* 03/13/2020 v1.0 (M91406) Initial release
* 11/02/2020 v2.0 (M91406) Modular state machine with startup sub-states
* 12/21/2020 v2.1 (M91406) Added current sense calibration function extensions to state machine
* 02/12/2021 v2.2 (M91406) Added VCap Monitor to startup data structure


---
© 2021, Microchip Technology Inc.
