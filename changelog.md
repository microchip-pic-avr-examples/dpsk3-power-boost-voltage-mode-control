# dpsk3-power-boost-voltage-mode-control, release v1.3.1

### Features Added\Updated

- **Operating System RTOS 6G2**
This version introduces an updated RTOS 6G2 task scheduler implementation. This slim operating system provides two preemtive task priorities. Each priority layer schedules tasks coorporatively. The high priority task layer includes time critical tasks, such as power supply state machine and fault handler, executing both at a fixed 10 kHz interval. The low priority layer schedules all HMI background tasks such as switch buttons, LCD and on-board LEDs. All tasks on both priority layers can be configured to run at their own interval. Task execution time offsets allow users to interleave execution periods preventing conflicts and task execution jitter, increasing the overall robustness and perceived performance while making the firmware more deterministic and predictable. Please read the firmware documentation for more details.
<br>
- **[MPLAB&reg; PowerSmart&trade; Development Suite](https://www.microchip.com/powersmart)**
This project release has been upgraded to support the new MPLAB&reg; PowerSmart&trade; Development Suite for control loop configuration and code generation. MPLAB&reg; PowerSmart&trade; Development Suite is now available for download for free on the Microchip Technology website.
<br>
- **MPLAB&reg; PowerSmart&trade; Migration**
The control loop configuration of previous versions of this project were supported by the preliminary stand-alone version of MPLAB&reg; PowerSmart&trade; Digital Control Library Designer (PS-DCLD). With the introduction of version 1.0 of the MPLAB&reg; PowerSmart&trade; Development Suite, this preliminary beta version is being replaced.<br>
DCLD controller configuration files of the type (*.dcld) can be seamlessly imported in the Development Suite as well as new configurations created in the Development Suite can be exported to previous versions of DCLD to ensure compatibility with existing projects. Please refer to the [MPLAB&reg; PowerSmart&trade; Development Suite Quick Start Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/UG20220108) for more information.<br>
**The previous version is still available [here on Github](https://microchip-pic-avr-tools.github.io/powersmart-dcld/) but support will be discontinued on 1st of April 2022.**

# dpsk3-power-boost-voltage-mode-control, release v1.2.1

### Features Added\Updated

In MPLAB&reg; PowerSmart&trade; Digital Control Library Designer, release 0.9.14.676 labels of user extension function hooks changed, causing the compiler to fail when new control code is generated. This firmware release ensures compatibility with the latest version of this code generating tool.

When you download this version of the firmware, please also update your version of PowerSmart&trade; Digital Control Library Designer to version 0.9.14 or higher:
[MPLAB&reg; PowerSmart&trade; Digital Control Library Designer v0.9.14](https://microchip-pic-avr-tools.github.io/powersmart-dcld/)


# dpsk3-power-boost-voltage-mode-control, release v1.2.0

### Release Highlights

##### Fault Handler

In this release the fault handler device driver got optimized and fault indication got improved. The improved fault handler now supports the declaration
of a maximum number of restart attempts after the power supply has been shut down during fault conditions. This setting will put the power supply into 
a safe state after 'n' unsuccessful restart attempts. If any of the restart procedures passes the POWER GOOD state and reaches state ONLINE, the restart
counter is reset. The default number has been set to 10. This setting can be changed by editing `#define BOOST_FAULT_RESTART_CYCLES` in file dpsk3_hwrdescr.h

This new feature prevents the power supply from ending up in an endless hiccup condition where the power supply is continuously driven into fault conditions 
with the potential risk of over stressing components, connected sources or loads. The 'safe state' is OFF, where the controller still acquires ADC data but 
keeps the power supply turned off and PWM outputs disabled. The on-board LED flashes at a higher frequency and the error code "(LA)" is displayed on the LCD to 
indicate the latched fault condition.

In this condition a CPU reset or power cycle is required to restart the power supply.

##### Boost Converter Control Loop

The latest release of PowerSmart Digital Control Loop Designer introduced a new/revised Anti-Windup Limiter feature allowing to clamp the PWM output to zero 
when the control output drops below a defined minimum. Â second Anti-Windup Limiter feature allows the digital loop controller to 'saturate' the control history, 
resulting in a delayed soft recovery. By enabling both features, the no-load cycle skipping of the asynchronous boost converter improved significantly and also solved 
the issue of drifting output voltage when the input voltage is close to the nominal output voltage.

### Features Added\Updated

- Boost converter control loop was revised for achieving better behaving cycle-skipping in no load conditions
- Improved cycle skipping now results in tight and drift-less output voltage in no load conditions
- Fault object management bugfix: a sloppy if-statement accidentally disabled regulation error in Online mode
- Limitation of restart-attempts after fault shut-down with latched safe-state fault condition
- On-Board LED changes blinking frequency in fault conditions
- LC display got 4th screen showing most recent firmware version
- Fault indication on LC display is now visible on all screens (except firmware version view)
- Updated online documentation

### Supported Hardware Revisions:

- Digital Power Starter Kit 3, Revision 3.0 (Part-No. 330017-3)
Visit [www.microchip.com/330017-3](https://www.microchip.com/330017-3) for more information


# dpsk3-power-boost-voltage-mode-control, release v1.1.0

### Release Highlights
This code example is demonstrating the implementation of a simple digital voltage mode control loop regulating the output voltage of an asynchronous boost converter.
This example is part of a series of code examples for the Digital Power Starter Kit 3 demonstrating the implementation of specific control modes and features.

### Features Added\Updated
- Boost converter device driver update reversion the execution order of output capacitor charge-up time and power-on delay for a more robust startup when powered from slow DC sources.
- Improved fault handler over current protection management: over current protection is turned off when the converter is inactive to prevent erroneous over current detections
- Updated online documentation

### Supported Hardware Revisions:

- Digital Power Starter Kit 3, Revision 3.0 (Part-No. 330017-3)
Visit [www.microchip.com/330017-3](https://www.microchip.com/330017-3) for more information


# dpsk3-power-boost-voltage-mode-control, release v1.0.0
### Release Highlights
This is the initial release demonstrating the basic control loop implementation of a simple digital voltage mode control loop regulating the output voltage of an asynchronous boost converter.
This example is part of a series of code examples for the Digital Power Starter Kit 3 demonstrating the implementation of specific control modes and features.

### Features Added\Updated
This code example runs automatically after power has been applied to the development board. In this initial version the on-board LED of the dsPIC33CK Digital Power Plug-In Module is toggled with a interval period of 300 ms, when the controller is running at maximum speed of 100 MIPS. After startup, PWM generator #1 is generating a 500 kHz complementary waveform at the PWM1H/PWM1L outputs. The output voltage feedback is read through ADC input #13 and processed through the digital control loop in the respective interrupt service routine. At the end of the control loop execution the result is written to the PWM duty cycle register, eventually regulating the output voltage to the nominal 3.3 V output voltage.

During operation the most recent values of input voltage, output voltage, output current and temperature are displayed on the on-board LCD. The screens can be switched by pressing the User button for more than 1 second.

### Supported Hardware Revisions:
Digital Power Starter Kit 3, Revision 3.0 (Part-No. 330017-3)
Visit [www.microchip.com/330017-3](https://www.microchip.com/330017-3) for more information
