/*
 * File:   boot.c
 * Author: M91406
 *
 * Created on June 18, 2021, 3:41 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

/* INCLUDE DEFAULT SYSTEM COMPONENT INITIALIZATION MODULES */
#include "boot/rtos_dsp.h"
#include "boot/rtos_fosc.h"
#include "boot/rtos_gpio.h"
#include "boot/rtos_pmd.h"

/***********************************************************************************
 * @fn     volatile uint16_t Boot(void)
 * @ingroup system-mcu-initialization
 * @brief  Initializes essential chip resources
 * @return unsigned integer 
 * 0=failure
 * 1=success
 * 
 * @details
 * The Boot function covers the initialization of essential chip 
 * resources such as main oscillator, auxiliary oscillator, watchdog timer and
 * general purpose I/Os (GPIO). All other, design specific peripherals are 
 * initialized in the User Peripheral Initialization or by the respective 
 * User Task Device Drivers included in the firmware project
 * 
 **********************************************************************************/

volatile uint16_t Boot(void)
{
    volatile uint16_t retval=1;

    retval &= osFosc_Initialize(); ///< Set up system oscillator for 100 MIPS operation
    retval &= osAclk_Initialize(); ///< Set up Auxiliary PLL for 500 MHz (source clock to PWM module)
    retval &= osGpio_Initialize(); ///< Initialize common device GPIOs
    retval &= osDsp_Initialize();  ///< Initialize the DSP engine for fractional multiplication with saturation
    
    return(retval);
}

// end of file
