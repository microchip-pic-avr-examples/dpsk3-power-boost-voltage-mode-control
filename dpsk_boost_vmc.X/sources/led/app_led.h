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

/* 
 * File:   app_led.h
 * Author: M91406
 * Comments: LED application layer
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APPLICATION_LAYER_DEBUGGING_LED_H
#define	APPLICATION_LAYER_DEBUGGING_LED_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types


// CUSTOM DECLARATIONS
#define DBGLED_PERIOD_FAST      2499
#define DBGLED_PERIOD_DEFAULT   4999
#define DBGLED_PERIOD_STANDBY   9999

/***********************************************************************************
 * @ingroup app-layer-debug-led-properties-public
 * @struct DEBUGGING_LED_s
 * @brief Debugging LED settings data object
 * @details
 *  This data structure holds all adjustable parameters used by the debugging 
 *  LED driver required to tailor the driver functions to specific application
 *  requirements. 
 **********************************************************************************/

struct DEBUGGING_LED_STATUS_s{
        union {
    struct{

        unsigned on : 1;    // Bit #0:  Flag bit, set and cleared by software driver, indicating the debugging LED is currently on (read only)
        unsigned : 1;       // Bit #1:  (reserved)
        unsigned : 1;       // Bit #2:  (reserved)
        unsigned : 1;       // Bit #3:  (reserved)
        unsigned : 1;       // Bit #4:  (reserved)
        unsigned : 1;       // Bit #5:  (reserved)
        unsigned : 1;       // Bit #6:  (reserved)
        unsigned : 1;       // Bit #7:  (reserved)

        unsigned : 1;       // Bit #8:  (reserved)
        unsigned : 1;       // Bit #9:  (reserved)
        unsigned : 1;       // Bit #10: (reserved)
        unsigned : 1;       // Bit #11: (reserved)
        unsigned : 1;       // Bit #12: (reserved)
        unsigned : 1;       // Bit #13: (reserved)
        unsigned : 1;       // Bit #14: (reserved)
        unsigned enabled;   // Bit #15: Control bit enabling and disabling the Debugging LED function
    } __attribute__((packed)) bits; ///< data structure for single bit addressing operations

	volatile uint16_t value; // buffer for 16-bit word read/write operations
    };
};    
typedef struct DEBUGGING_LED_STATUS_s DEBUGGING_LED_STATUS_t;

struct DEBUGGING_LED_s{
    volatile struct DEBUGGING_LED_STATUS_s status; ///< Status word of the Debugging LED driver
    volatile uint16_t period; //< Period setting of the Debugging LED driver
};    
typedef struct DEBUGGING_LED_s DEBUGGING_LED_t;

// PUBLIC VARIABLE DECLARATION
extern volatile DEBUGGING_LED_t debug_led;

// PUBLIC FUNCTION PROTOTYPE DECLARATION
extern volatile uint16_t appLED_Initialize(void);
extern volatile uint16_t appLED_Execute(void);
extern volatile uint16_t appLED_Start(void);
extern volatile uint16_t appLED_Dispose(void);

#endif	/* APPLICATION_LAYER_DEBUGGING_LED_H */

