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
