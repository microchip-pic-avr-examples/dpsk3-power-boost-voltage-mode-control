#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "p33c_pmd.h"


/*********************************************************************************
 * @ingroup lib-layer-pral-properties-private-pmd
 * @var 	pmdConfigDefault
 * @brief 	PMD Register Set reset state template
 * 
 * @details
 *     This P33C_PMD_s data object provides a template of register 
 *     configuration values for the Peripheral Module Disable module. 
 * 
 *     Default configuration:
 *         - all options are reset to their default state (on)
 * 
 *********************************************************************************/
/**@ingroup lib-layer-pral-properties-private-pmd */

volatile struct P33C_PMD_MODULE_s pmdConfigDefault = { 
    
	#ifdef PMD1
	.pmd1.value = 0xffff,
	#endif
	#ifdef PMD2
	.pmd2.value = 0xffff,
	#endif
	#ifdef PMD3
	.pmd3.value = 0xffff,
	#endif
	#ifdef PMD4
	.pmd4.value = 0xffff,
	#endif
	#ifdef PMD5
	.pmd5.value = 0xffff,
	#endif
	#ifdef PMD6
	.pmd6.value = 0xffff,
	#endif
	#ifdef PMD7
	.pmd7.value = 0xffff,
	#endif
	#ifdef PMD8
	.pmd8.value = 0xffff,
	#endif
	#ifdef PMD9
	.pmd9.value = 0xffff,
	#endif
    
   };

/* PRIVATE FUNCTION CALL PROTOTYPES*/
//    (none)


/*********************************************************************************
 * @fn     volatile struct P33C_CCP_INSTANCE_s p33c_CcpInstance_ConfigRead(volatile uint16_t ccpInstance)
 * @ingroup lib-layer-pral-functions-public-pmd
 * @brief  Read the current configuration from the CCP instance registers
 * @param  ccpInstance Index of the Capture/Compare peripheral instance of type unsinged integer
 * @return SCCP/MCCP instance special function register data object of type struct P33C_CCP_INSTANCE_s
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_CCP_MODULE_SFRSET_s. Users can read and 
 *     verify of modify the configuration to write it back to any other CCP 
 *     peripheral instance.
 * 
 *********************************************************************************/

volatile struct P33C_PMD_MODULE_s p33c_PmdInstance_ConfigRead(void){

 volatile struct P33C_PMD_MODULE_s* pmd;
    
    // Capture Handle: set pointer to memory address of the Peripheral Module Disable module
    pmd = p33c_Pmd_GetHandle(); 
    
    return(*pmd);
}

/********************************************************************************
 * @fn     volatile uint16_t p33c_CcpInstance_ConfigWrite(volatile uint16_t ccpInstance, volatile struct P33C_CCP_INSTANCE_s ccpConfig)
 * @ingroup lib-layer-pral-functions-public-pmd
 * @brief  Writes a user-defined configuration to the Peripheral Module Disable registers
 * @param  pmdConfig Peripheral Module Disable special function register data object of type struct P33C_PMD_s
 * @return 0 = failure, writing to PMD module was not successful
 * @return 1 = success, writing to PMD module was successful
 * 
 * @details
 *     This function writes a user-defined PMD module configuration of type 
 *     P33C_PMD_s to the Peripheral Module Disable module registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly 
 * 
 *********************************************************************************/

volatile uint16_t p33c_Pmd_ConfigWrite(volatile struct P33C_PMD_MODULE_s pmdConfig)
{
    volatile uint16_t retval=1;
    volatile struct P33C_PMD_MODULE_s* pmd;    

    // Set pointer to memory address of the Peripheral Module Disable module
    pmd = p33c_Pmd_GetHandle(); 

    // Disable all peripheral modules
    #ifdef PMDCON
    pmd->pmdcon.bits.PMDLOCK = 0; // Unlock writes to PMD registers
    #endif    
    
    // Load user configuration into PDM register set
    *pmd = pmdConfig;

    #ifdef PMDCON
    pmd->pmdcon.bits.PMDLOCK = 1; // Lock writes to PMD registers 
    #endif    
    
    return(retval);
    
}

// end of file
