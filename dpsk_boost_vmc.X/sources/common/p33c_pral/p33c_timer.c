/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "p33c_timer.h"

/*********************************************************************************
 * @ingroup lib-layer-pral-properties-private-timer
 * @var tmrConfigDefault
 * @brief Timer Register Set reset state template
 * 
 * @details
 *     This P33C_TIMER_MODULE_s data object provides a template of register 
 *     configuration values for the 16-bit Timer peripheral. 
 * 
 *     Default configuration:
 *         - all options are reset to their default state
 * 
 *********************************************************************************/
/**@ingroup lib-layer-pral-properties-private-ccp */

volatile struct P33C_TIMER_MODULE_s tmrConfigDefault = { 
    .TxCON.value = 0x0000, // Clear time configuration register
    .PRx.value = 0xFFFF, // Set period register to maximum
   };

/*********************************************************************************
 * @fn     volatile struct P33C_TIMER_MODULE_s p33c_Timer_ConfigRead(void)
 * @ingroup lib-layer-pral-functions-public-timer
 * @brief  Read the current configuration from the Timer special function registers
 * @return Timer special function register data object of type struct P33C_TIMER_MODULE_s
 * 
 * @details
 *     This function reads all Timer registers with their current configuration 
 *     into a data structure of type P33C_TIMER_MODULE_s. Users can verify or 
 *     modify the configuration of the Timer peripheral.
 * 
 *********************************************************************************/

volatile struct P33C_TIMER_MODULE_s p33c_Timer_ConfigRead(void)
{
    volatile struct P33C_TIMER_MODULE_s* tmr;
 
    // Capture Handle: set pointer to memory address of desired PWM instance
    tmr = p33c_TimerModule_GetHandle();

    return(*tmr);
}

/********************************************************************************
 * @fn     volatile uint16_t p33c_Timer_ConfigWrite(volatile struct P33C_TIMER_MODULE_s ccpConfig)
 * @ingroup lib-layer-pral-functions-public-timer
 * @brief  Writes a user-defined configuration to the Timer registers
 * @param  tmrConfig Timer special function register data object of type struct P33C_TIMER_MODULE_s
 * @return 0 = failure, writing to Timer registers was not successful
 * @return 1 = success, writing to Timer registers was successful
 * 
 * @details
 *     This function writes a user-defined Timer configuration of type 
 *     P33C_TIMER_MODULE_s to the Timer registers. The individual register 
 *     configurations have to be set in user-code before calling this function. 
 *     To simplify the configuration process of standard functions, this driver 
 *     provides templates, which can be loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_Timer_ConfigWrite(volatile struct P33C_TIMER_MODULE_s tmrConfig)
{
    volatile uint16_t retval=1;
    volatile struct P33C_TIMER_MODULE_s* tmr;    

    // Set pointer to memory address of desired Timer 
    tmr = p33c_TimerModule_GetHandle();
    *tmr = tmrConfig;
    
    return(retval);
    
}

// end of file
