/*
 * File:   init_fosc.c
 * Author: M91406
 *
 * Created on July 8, 2019, 1:55 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "rtos_fosc.h" // include RTOS oscillator initialization header file
#include "common/p33c_pral/xc16_pral.h" // include common peripheral abstraction layer driver header file

#define TIMEOUT_LIMIT   5000    // timeout counter maximum

/***********************************************************************************
 * @fn uint16_t osFosc_Initialize(void)
 * @ingroup clock-initialization
 * @brief  System oscillator initialization
 * @return unsigned integer 
 * 0=failure
 * 1=success
 * 
 * @details
 * This function initializes the internal 8 MHz RC oscillator as the main
 * oscillator and initializes the PLL to operate the CPU at maximum performance 
 * of 100 MHz instruction cycle.
 * 
 **********************************************************************************/
volatile uint16_t osFosc_Initialize(void) 
{
    volatile uint16_t retval=1;
    
    #if defined (__P33SMPS_CK__) || defined (__P33SMPS_CH_SEC__)
    retval = p33c_OscFrc_DefaultInitialize(CPU_SPEED_100_MIPS);
    #elif defined (__P33SMPS_CH_MAIN__)
    retval = p33c_OscFrc_DefaultInitialize(CPU_SPEED_90_MIPS);
    #endif
    retval &= p33c_Osc_GetFrequencies();
    
    return(retval);

}

/***********************************************************************************
 * @fn uint16_t osAclk_Initialize(void)
 * @ingroup clock-initialization
 * @brief  Initializes the auxiliary clock of the device
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This function initializes the auxiliary PLL for operating ADC and PWM module
 * at maximum performance at an input clock of 500 MHz. Each peripheral module
 * may use additional frequency scalers and multipliers to further convert this
 * frequency.
 *
 **********************************************************************************/
volatile uint16_t osAclk_Initialize(void) {

    volatile uint16_t retval=1;

    retval &= p33c_OscAuxClk_DefaultInitialize(AFPLLO_500_MHZ);

    return(retval);
}

// end of file

