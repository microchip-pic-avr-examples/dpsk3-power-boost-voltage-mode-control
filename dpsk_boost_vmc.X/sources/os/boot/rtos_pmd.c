/*
 * File:   init_pmd.c
 * Author: M91406
 *
 * Created on July 8, 2019, 6:26 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "common/p33c_pral/xc16_pral.h" // include common peripheral abstraction layer driver header file
#include "rtos_pmd.h" // include RTOS peripheral module disable initialization header file

/***********************************************************************************
 * @fn uint16_t osPmd_Initialize(void)
 * @ingroup pmd-initialization
 * @brief  Powers down all device peripherals
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 *  When the device is coming out of RESET, all peripheral modules are powered
 *  and active, ready to be initialized and used. However, each active peripheral
 *  consumes power and accidental writes to any of its special function registers
 *  may be a potential source for undesired behavior. Hence, in this application 
 *  all power supply to all peripheral modules are disabled, minimizing the device 
 *  power consumption and preventing potential misbehavior of unused peripheral 
 *  modules.
 *
 * @note
 *  Unpowered peripherals cannot be initialized and reads from/write to the 
 *  respective special function registers will fail until the power supply to 
 *  the peripheral has been enabled. Hence, power to peripheral modules has to
 *  be enabled before any initialization of its register can take place.
 * 
 *  Depending on the peripheral a short delay period may be required for the 
 *  peripheral functions to become available after power up. 
 *
 *  Please refer to the device data sheet for details.
 *
 **********************************************************************************/

volatile uint16_t osPmd_Initialize(void) {
    
    volatile uint16_t retval=1;
    
    // Enable all peripherals
    retval &= p33c_Pmd_ConfigWrite(pmdConfigDefault);

    return(retval);
}

// end of file
