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

#include "p33c_gpio.h"

#if defined (ANSELE)
volatile uint16_t* p33c_GpioInstance_Handles[5]={
    &ANSELA, &ANSELB, &ANSELC, &ANSELD, 
    &ANSELE
};
#elif defined (ANSELD)
volatile uint16_t* p33c_GpioInstance_Handles[4]={
    &ANSELA, &ANSELB, &ANSELC, &ANSELD
};
#elif defined (ANSELC)
volatile uint16_t* p33c_GpioInstance_Handles[3]={
    &ANSELA, &ANSELB, &ANSELC
};
#elif defined (ANSELB)
volatile uint16_t* p33c_GpioInstance_Handles[2]={
    &ANSELA, &ANSELB
};
#elif defined (ANSELA)
volatile uint16_t* p33c_GpioInstance_Handles[1]={
    &ANSELA
};
#else
#pragma message "selected device has no supported ports"
#endif

/*********************************************************************************
 * @fn uint16_t p33c_GpioInstance_Dispose(volatile uint16_t gpioInstance)
 * @ingroup lib-layer-pral-functions-public-gpio
 * @brief Resets all GPIO Instance registers to their RESET default values
 * @param  gpioInstance Index of the selected GPIO Instance (1=Port A, 2=Port B, etc.)
 * @return 0 = failure, disposing GPIO instance was not successful
 * @return 1 = success, disposing GPIO instance was successful
 * 
 * @details
 *     This function clears all GPIO Instance registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - all outputs are set to logic functions
 *         - all analog functions are disabled
 *         - all pull-up and pull-down resistors are disabled
 *         - all GPIOs are operating in push-pull mode (open drain disabled)
 *         - all GPIOs are configured as input with their signal level HIGH
 * 
 *********************************************************************************/

volatile uint16_t p33c_GpioInstance_Dispose(volatile uint16_t gpioInstance)
{
    volatile uint16_t retval=1;
    
    retval = p33c_GpioInstance_ConfigWrite(gpioInstance, gpioConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @fn struct P33C_GPIO_INSTANCE_s p33c_GpioInstance_ConfigRead(volatile uint16_t gpioInstance)
 * @ingroup lib-layer-pral-functions-public-gpio
 * @brief Read the current configuration from the GPIO instance registers  
 * @param  gpioInstance Index of the selected GPIO Instance (1=Port A, 2=Port B, etc.)
 * @return 0 = failure, reading GPIO instance was not successful (returns NULL)
 * @return n = success, reading GPIO instance was successful (returns 16-bit wide pointer)
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_GPIO_INSTANCE_s. Users can read and 
 *     verify or modify the configuration to write it back to the GPIO instance  
 *     registers or copy configurations to other instances of the same type.
 * 
 * ********************************************************************************/

volatile struct P33C_GPIO_INSTANCE_s p33c_GpioInstance_ConfigRead(volatile uint16_t gpioInstance)
{
    volatile struct P33C_GPIO_INSTANCE_s* gpio;

    // Set pointer to memory address of desired GPIO instance
    gpio = p33c_GpioInstance_GetHandle(gpioInstance);

    return(*gpio);
    
}

/*********************************************************************************
 * @fn uint16_t p33c_GpioInstance_ConfigWrite(volatile uint16_t gpioInstance,volatile struct P33C_GPIO_INSTANCE_s gpioConfig)
 * @ingroup lib-layer-pral-functions-public-gpio
 * @brief  Writes a user-defined configuration to the GPIO instance registers
 * @param  gpioInstance Index of the selected GPIO Instance (1=Port A, 2=Port B, etc.)
 * @param  gpioConfig GPIO peripheral instance SFR object of type struct P33C_GPIO_INSTANCE_s
 * @return 0 = failure, writing GPIO instance was not successful
 * @return 1 = success, writing GPIO instance was successful
 * 
 * @details
 *     This function writes a user-defined GPIO instance configuration of type 
 *     P33C_GPIO_INSTANCE_s to the GPIO instance registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_GpioInstance_ConfigWrite(
        volatile uint16_t gpioInstance, 
        volatile struct P33C_GPIO_INSTANCE_s gpioConfig
)
{
    volatile uint16_t retval=1;
    volatile struct P33C_GPIO_INSTANCE_s* gpio;    

    // Set pointer to memory address of desired GPIO instance
    gpio = p33c_GpioInstance_GetHandle(gpioInstance);
    *gpio = gpioConfig;
    
    return(retval);
    
}


/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */

/*********************************************************************************
 * @var gpioConfigClear 
 * @ingroup lib-layer-pral-properties-private-gpio
 * @brief Default RESET configuration of one GPIO instance SFRs
 *
 * @details
 *   Default configuration of the GPIO instance SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   GPIO instance when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 ********************************************************************************/

volatile struct P33C_GPIO_INSTANCE_s gpioConfigClear = {
    
        .ANSELx.value  = 0x0000, // Disable all analog functions
        .CNCONx.value  = 0x0000, // Reset all change notification configurations
        .CNEN0x.value  = 0x0000, // Disable all change notification functions
        .CNEN1x.value  = 0x0000, // Disable all change notification functions
        .CNFx.value    = 0x0000, // Clear all change notification interrupt flags
        .CNPDx.value   = 0x0000, // Disable all dull-down resistors
        .CNPUx.value   = 0x0000, // Disable all dull-up resistors
        .CNSTATx.value = 0x0000, // Clear all change notification status notifications
        .LATx.value    = 0x0000, // Set all IOs of selected instance LOW
        .ODCx.value    = 0x0000, // Clear all open-drain configurations of instance
        .PORTx.value   = 0x0000, // CLear port registers of all IOs of instance 
        .TRISx.value   = 0x1111, // Set all IOs of instance to INPUT
        
    };


// Device pin declarations
// Port A
#if defined (_TRISA0)
volatile struct GPIO_PORT_PIN_s PIN_RA0  = { .port=0, .pin=0,  .rpid=0 };
#endif
#if defined (_TRISA1)
volatile struct GPIO_PORT_PIN_s PIN_RA1  = { .port=0, .pin=1,  .rpid=0 };
#endif
#if defined (_TRISA2)
volatile struct GPIO_PORT_PIN_s PIN_RA2  = { .port=0, .pin=2,  .rpid=0 };
#endif
#if defined (_TRISA3)
volatile struct GPIO_PORT_PIN_s PIN_RA3  = { .port=0, .pin=3,  .rpid=0 };
#endif
#if defined (_TRISA4)
volatile struct GPIO_PORT_PIN_s PIN_RA4  = { .port=0, .pin=3,  .rpid=0 };
#endif
#if defined (_TRISA5)
volatile struct GPIO_PORT_PIN_s PIN_RA5  = { .port=0, .pin=5,  .rpid=0 };
#endif
#if defined (_TRISA6)
volatile struct GPIO_PORT_PIN_s PIN_RA6  = { .port=0, .pin=6,  .rpid=0 };
#endif
#if defined (_TRISA7)
volatile struct GPIO_PORT_PIN_s PIN_RA7  = { .port=0, .pin=7,  .rpid=0 };
#endif
#if defined (_TRISA8)
volatile struct GPIO_PORT_PIN_s PIN_RA8  = { .port=0, .pin=8,  .rpid=0 };
#endif
#if defined (_TRISA9)
volatile struct GPIO_PORT_PIN_s PIN_RA9  = { .port=0, .pin=9,  .rpid=0 };
#endif
#if defined (_TRISA10)
volatile struct GPIO_PORT_PIN_s PIN_RA10 = { .port=0, .pin=10, .rpid=0 };
#endif
#if defined (_TRISA12)
volatile struct GPIO_PORT_PIN_s PIN_RA11 = { .port=0, .pin=11, .rpid=0 };
#endif
#if defined (_TRISA12)
volatile struct GPIO_PORT_PIN_s PIN_RA12 = { .port=0, .pin=12, .rpid=0 };
#endif
#if defined (_TRISA13)
volatile struct GPIO_PORT_PIN_s PIN_RA13 = { .port=0, .pin=13, .rpid=0 };
#endif
#if defined (_TRISA14)
volatile struct GPIO_PORT_PIN_s PIN_RA14 = { .port=0, .pin=14, .rpid=0 };
#endif
#if defined (_TRISA15)
volatile struct GPIO_PORT_PIN_s PIN_RA15 = { .port=0, .pin=15, .rpid=0 };
#endif

// Port B
#if defined (_TRISB0)
volatile struct GPIO_PORT_PIN_s PIN_RB0  = { .port=1, .pin=0,  .rpid=32 };
#endif
#if defined (_TRISB1)
volatile struct GPIO_PORT_PIN_s PIN_RB1  = { .port=1, .pin=1,  .rpid=33 };
#endif
#if defined (_TRISB2)
volatile struct GPIO_PORT_PIN_s PIN_RB2  = { .port=1, .pin=2,  .rpid=34 };
#endif
#if defined (_TRISB3)
volatile struct GPIO_PORT_PIN_s PIN_RB3  = { .port=1, .pin=3,  .rpid=35 };
#endif
#if defined (_TRISB4)
volatile struct GPIO_PORT_PIN_s PIN_RB4  = { .port=1, .pin=4,  .rpid=36 };
#endif
#if defined (_TRISB5)
volatile struct GPIO_PORT_PIN_s PIN_RB5  = { .port=1, .pin=5,  .rpid=37 };
#endif
#if defined (_TRISB6)
volatile struct GPIO_PORT_PIN_s PIN_RB6  = { .port=1, .pin=6,  .rpid=38 };
#endif
#if defined (_TRISB7)
volatile struct GPIO_PORT_PIN_s PIN_RB7  = { .port=1, .pin=7,  .rpid=39 };
#endif
#if defined (_TRISB8)
volatile struct GPIO_PORT_PIN_s PIN_RB8  = { .port=1, .pin=8,  .rpid=40 };
#endif
#if defined (_TRISB9)
volatile struct GPIO_PORT_PIN_s PIN_RB9  = { .port=1, .pin=9,  .rpid=41 };
#endif
#if defined (_TRISB10)
volatile struct GPIO_PORT_PIN_s PIN_RB10 = { .port=1, .pin=10, .rpid=42 };
#endif
#if defined (_TRISB11)
volatile struct GPIO_PORT_PIN_s PIN_RB11 = { .port=1, .pin=11, .rpid=43 };
#endif
#if defined (_TRISB12)
volatile struct GPIO_PORT_PIN_s PIN_RB12 = { .port=1, .pin=12, .rpid=44 };
#endif
#if defined (_TRISB13)
volatile struct GPIO_PORT_PIN_s PIN_RB13 = { .port=1, .pin=13, .rpid=45 };
#endif
#if defined (_TRISB14)
volatile struct GPIO_PORT_PIN_s PIN_RB14 = { .port=1, .pin=14, .rpid=46 };
#endif
#if defined (_TRISB15)
volatile struct GPIO_PORT_PIN_s PIN_RB15 = { .port=1, .pin=15, .rpid=47 };
#endif

// Port C
#if defined (_TRISC0)
volatile struct GPIO_PORT_PIN_s PIN_RC0  = { .port=2, .pin=0,  .rpid=48 };
#endif
#if defined (_TRISC1)
volatile struct GPIO_PORT_PIN_s PIN_RC1  = { .port=2, .pin=1,  .rpid=49 };
#endif
#if defined (_TRISC2)
volatile struct GPIO_PORT_PIN_s PIN_RC2  = { .port=2, .pin=2,  .rpid=50 };
#endif
#if defined (_TRISC3)
volatile struct GPIO_PORT_PIN_s PIN_RC3  = { .port=2, .pin=3,  .rpid=51 };
#endif
#if defined (_TRISC4)
volatile struct GPIO_PORT_PIN_s PIN_RC4  = { .port=2, .pin=4,  .rpid=52 };
#endif
#if defined (_TRISC5)
volatile struct GPIO_PORT_PIN_s PIN_RC5  = { .port=2, .pin=5,  .rpid=53 };
#endif
#if defined (_TRISC6)
volatile struct GPIO_PORT_PIN_s PIN_RC6  = { .port=2, .pin=6,  .rpid=54 };
#endif
#if defined (_TRISC7)
volatile struct GPIO_PORT_PIN_s PIN_RC7  = { .port=2, .pin=7,  .rpid=55 };
#endif
#if defined (_TRISC8)
volatile struct GPIO_PORT_PIN_s PIN_RC8  = { .port=2, .pin=8,  .rpid=56 };
#endif
#if defined (_TRISC9)
volatile struct GPIO_PORT_PIN_s PIN_RC9  = { .port=2, .pin=9,  .rpid=57 };
#endif
#if defined (_TRISC10)
volatile struct GPIO_PORT_PIN_s PIN_RC10 = { .port=2, .pin=10, .rpid=58 };
#endif
#if defined (_TRISC11)
volatile struct GPIO_PORT_PIN_s PIN_RC11 = { .port=2, .pin=11, .rpid=59 };
#endif
#if defined (_TRISC12)
volatile struct GPIO_PORT_PIN_s PIN_RC12 = { .port=2, .pin=12, .rpid=60 };
#endif
#if defined (_TRISC13)
volatile struct GPIO_PORT_PIN_s PIN_RC13 = { .port=2, .pin=13, .rpid=61 };
#endif
#if defined (_TRISC14)
volatile struct GPIO_PORT_PIN_s PIN_RC14 = { .port=2, .pin=14, .rpid=62 };
#endif
#if defined (_TRISC15)
volatile struct GPIO_PORT_PIN_s PIN_RC15 = { .port=2, .pin=15, .rpid=63 };
#endif

// Port D
#if defined (_TRISD0)
volatile struct GPIO_PORT_PIN_s PIN_RD0  = { .port=3, .pin=0,  .rpid=64 };
#endif
#if defined (_TRISD1)
volatile struct GPIO_PORT_PIN_s PIN_RD1  = { .port=3, .pin=1,  .rpid=65 };
#endif
#if defined (_TRISD2)
volatile struct GPIO_PORT_PIN_s PIN_RD2  = { .port=3, .pin=2,  .rpid=66 };
#endif
#if defined (_TRISD3)
volatile struct GPIO_PORT_PIN_s PIN_RD3  = { .port=3, .pin=3,  .rpid=67 };
#endif
#if defined (_TRISD4)
volatile struct GPIO_PORT_PIN_s PIN_RD4  = { .port=3, .pin=4,  .rpid=68 };
#endif
#if defined (_TRISD5)
volatile struct GPIO_PORT_PIN_s PIN_RD5  = { .port=3, .pin=5,  .rpid=69 };
#endif
#if defined (_TRISD6)
volatile struct GPIO_PORT_PIN_s PIN_RD6  = { .port=3, .pin=6,  .rpid=70 };
#endif
#if defined (_TRISD7)
volatile struct GPIO_PORT_PIN_s PIN_RD7  = { .port=3, .pin=7,  .rpid=71 };
#endif
#if defined (_TRISD8)
volatile struct GPIO_PORT_PIN_s PIN_RD8  = { .port=3, .pin=8,  .rpid=72 };
#endif
#if defined (_TRISD9)
volatile struct GPIO_PORT_PIN_s PIN_RD9  = { .port=3, .pin=9,  .rpid=73 };
#endif
#if defined (_TRISD10)
volatile struct GPIO_PORT_PIN_s PIN_RD10 = { .port=3, .pin=10, .rpid=74 };
#endif
#if defined (_TRISD11)
volatile struct GPIO_PORT_PIN_s PIN_RD11 = { .port=3, .pin=11, .rpid=75 };
#endif
#if defined (_TRISD12)
volatile struct GPIO_PORT_PIN_s PIN_RD12 = { .port=3, .pin=12, .rpid=76 };
#endif
#if defined (_TRISD13)
volatile struct GPIO_PORT_PIN_s PIN_RD13 = { .port=3, .pin=13, .rpid=77 };
#endif
#if defined (_TRISD14)
volatile struct GPIO_PORT_PIN_s PIN_RD14 = { .port=3, .pin=14, .rpid=78 };
#endif
#if defined (_TRISD15)
volatile struct GPIO_PORT_PIN_s PIN_RD15 = { .port=3, .pin=15, .rpid=79 };
#endif

// Port E
#if defined (_TRISE0)
volatile struct GPIO_PORT_PIN_s PIN_RE0  = { .port=4, .pin=0,  .rpid=0 };
#endif
#if defined (_TRISE1)
volatile struct GPIO_PORT_PIN_s PIN_RE1  = { .port=4, .pin=1,  .rpid=0 };
#endif
#if defined (_TRISE2)
volatile struct GPIO_PORT_PIN_s PIN_RE2  = { .port=4, .pin=2,  .rpid=0 };
#endif
#if defined (_TRISE3)
volatile struct GPIO_PORT_PIN_s PIN_RE3  = { .port=4, .pin=3,  .rpid=0 };
#endif
#if defined (_TRISE4)
volatile struct GPIO_PORT_PIN_s PIN_RE4  = { .port=4, .pin=4,  .rpid=0 };
#endif
#if defined (_TRISE5)
volatile struct GPIO_PORT_PIN_s PIN_RE5  = { .port=4, .pin=5,  .rpid=0 };
#endif
#if defined (_TRISE6)
volatile struct GPIO_PORT_PIN_s PIN_RE6  = { .port=4, .pin=6,  .rpid=0 };
#endif
#if defined (_TRISE7)
volatile struct GPIO_PORT_PIN_s PIN_RE7  = { .port=4, .pin=7,  .rpid=0 };
#endif
#if defined (_TRISE8)
volatile struct GPIO_PORT_PIN_s PIN_RE8  = { .port=4, .pin=8,  .rpid=0 };
#endif
#if defined (_TRISE9)
volatile struct GPIO_PORT_PIN_s PIN_RE9  = { .port=4, .pin=9,  .rpid=0 };
#endif
#if defined (_TRISE10)
volatile struct GPIO_PORT_PIN_s PIN_RE10 = { .port=4, .pin=10, .rpid=0 };
#endif
#if defined (_TRISE11)
volatile struct GPIO_PORT_PIN_s PIN_RE11 = { .port=4, .pin=11, .rpid=0 };
#endif
#if defined (_TRISE12)
volatile struct GPIO_PORT_PIN_s PIN_RE12 = { .port=4, .pin=12, .rpid=0 };
#endif
#if defined (_TRISE13)
volatile struct GPIO_PORT_PIN_s PIN_RE13 = { .port=4, .pin=13, .rpid=0 };
#endif
#if defined (_TRISE14)
volatile struct GPIO_PORT_PIN_s PIN_RE14 = { .port=4, .pin=14, .rpid=0 };
#endif
#if defined (_TRISE15)
volatile struct GPIO_PORT_PIN_s PIN_RE15 = { .port=4, .pin=15, .rpid=0 };
#endif

// end of file
