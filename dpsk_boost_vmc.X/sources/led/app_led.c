/*
 * File:   lcd.c
 * Author: M91406
 *
 * Created on March 12, 2020, 12:10 PM
 */


#include "config/apps.h"
#include "config/hal.h"

// PRIVATE VARIABLE DELARATIONS
static volatile uint16_t tgl_cnt = 0;  // local counter of LED toggle loops
#define TGL_INTERVAL      4     // LED toggle interval of 5 x 100 ms = 500 ms
#define TGL_INTERVAL_ERR  0     // LED toggle interval of 1 x 100 ms = 100 ms

volatile DEBUGGING_LED_t debug_led;

/*********************************************************************************
 * @ingroup app-layer-debug-led-functions-public
 * @fn volatile uint16_t appLED_Initialize(void)
 * @brief  Initializes the LED driving GPIO
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This routine configures the driving GPIO as output and sets the initial
 *  toggle interval of the debugging LED.
 **********************************************************************************/

volatile uint16_t appLED_Initialize(void) 
{
    volatile uint16_t retval = 1;
    
    if(debug_led.period == 0)
        debug_led.period = TGL_INTERVAL;
    
    DBGLED_Init();

    return(retval);
}

/*********************************************************************************
 * @ingroup app-layer-debug-led-functions-public
 * @fn volatile uint16_t appLED_Execute(void)
 * @brief  Executes the debugging LED driver
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This routine executes the debugging LED driver controlling the toggling 
 *  interval of the debugging LED.
 **********************************************************************************/

volatile uint16_t appLED_Execute(void) 
{
    volatile uint16_t retval = 1;

    DBGPIN1_Set();
    
    // Exit early if debugging LED is disabled
    if (!debug_led.status.bits.enabled)
        return(1);

    // Change LED toggle frequency when power supply is in fault state
    if (boost.status.bits.fault_active)
        debug_led.period = TGL_INTERVAL_ERR;
    else
        debug_led.period = TGL_INTERVAL;
    
	// Toggle LED, refresh LCD and reset toggle counter
	if (++tgl_cnt > debug_led.period) { // Count n loops until LED toggle interval is exceeded
		DBGLED_Toggle();
        debug_led.status.bits.on = (bool)(DBGLED_Get() == DBGLED_ON);
		tgl_cnt = 0;
	} 

    DBGPIN1_Clear();
    
    return(retval);
}

/*********************************************************************************
 * @ingroup app-layer-debug-led-functions-public
 * @fn volatile uint16_t appLED_Start(void)
 * @brief  Enables the periodic refresh of the debugging LED status
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This routine is used to allow function 'appLED_Execute' to periodically 
 *  refresh the debugging LED status.
 **********************************************************************************/

volatile uint16_t appLED_Start(void) 
{
    volatile uint16_t retval = 1;
    
    debug_led.status.bits.enabled = true;
    retval &= (uint16_t)(debug_led.status.bits.enabled);

    return(retval);
}

/*********************************************************************************
 * @ingroup app-layer-debug-led-functions-public
 * @fn volatile uint16_t appLED_Dispose(void)
 * @brief  Frees the resources of the debugging LED driver
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This routine is used to end the debugging LED driver task and frees
 *  its resources.
 **********************************************************************************/

volatile uint16_t appLED_Dispose(void) 
{
    volatile uint16_t retval = 1;
    
    debug_led.period = 0;
    DBGLED_Dispose();

    return(retval);
}

// end of file
