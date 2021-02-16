# dpsk3-power-boost-voltage-mode-control, release v1.1.0

### Release Highlights
This is the initial release demonstrating the basic control loop implementation of a simple digital voltage mode control loop regulating the output voltage of an asynchronous boost converter.
This example is part of a series of code examples for the Digital Power Starter Kit 3 demonstrating the implementation of specific control modes and features.

### Features Added\Updated
- Boost converter device driver update reversion the execution order of output capacitor charge-up time and power-on delay for a more robust startup when powered from slow DC sources.
- Improved fault handler over current protection management: over current protection is turned off when the converter is inactive to prevent erroneous over current detections
- Updated online documentation

### Supported Hardware Revisions:

- Digital Power Starter Kit 3, Revision 3.0 (Part-No. 330017-3)
Visit [www.microchip.com/330017-3](https://www.microchip.com/330017-3) for more information
