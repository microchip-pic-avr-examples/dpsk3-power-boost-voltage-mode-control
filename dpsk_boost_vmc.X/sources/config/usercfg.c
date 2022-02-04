/*
 * File:   system_initialize.c
 * Author: M91406
 *
 * Created on November 12, 2020, 10:33 AM
 */

#include "hal.h"
#include "mcal.h"
#include "usercfg.h"

/***********************************************************************************
 * @fn uint16_t sysUserPeriperhals_Initialize(void)
 * @ingroup system-user-peripherals-initialization
 * @brief  Initializes static, application-specific chip resources
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 * The Digital Power Starter Kit 3 supports Test Points allowing users to observe
 * the DAC output of the dsPIC33C device as well as digital status signals of 
 * internal software processes. Using these features requires the configuration 
 * of further on-chip resources. These configurations are static and not related 
 * to any other task or function of the application and therefore need to be added 
 * manually. 
 * 
 * For this kind of Special Features, the startup procedure offers the following 
 * default function call allowing to place proprietary user code for individual
 * device configurations beyond the default setup. 
 * 
 **********************************************************************************/
//volatile uint16_t sysUserPeriperhals_Initialize(void) {
//
//    volatile uint16_t retval=1;
//    
//    // Reset the operation amplifier module to a disabled default state.
////    retval &= sysOpAmp_ModuleReset();
////    
////    // Initialize op-amp
////    retval &= sysOpAmp_Initialize(DAC_BUFFER_OPA_INSTANCE, true); // Initialize op-amp #2 used to drive the reference voltage for current sense amplifiers
////    
////    // Initialize DAC
////    retval &= sysDacModule_Initialize();  // Initialize DAC module
////    retval &= sysDacOutput_Initialize(DAC_OUTPUT_INSTANCE, DAC_OUTPUT_INIT_VALUE); // Initialize DAC #1 used to generate the reference voltage for current sense amplifiers
////    retval &= sysDacOutput_Enable(DAC_OUTPUT_INSTANCE); // Enable DAC providing reference to current sense amplifiers
////
////    // Enable op-amp
////    retval &= sysOpAmp_ModuleEnable(); // Enable the operational amplifier module
////    
//    // Initialize debugging Pins
//    #ifdef DBGPIN1_PIN
//    DBGPIN1_Init(); ///< Device pin #1  (not routed)
//    DBGPIN1_Clear(); // Clear debug pin #1
//    #endif
//    #ifdef DBGPIN2_PIN
//    DBGPIN2_Init(); ///< Device pin #2  (not routed)
//    DBGPIN2_Clear(); // Clear debug pin #2
//    #endif
//    
//	return(retval);
//
//}


// end of file
