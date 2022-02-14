#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "p33c_ccp.h"

// Private arrays of register set start addresses
#if defined (CCP9CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[9]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L, &CCP4CON1L, 
    &CCP5CON1L, &CCP6CON1L, &CCP7CON1L, &CCP8CON1L, 
    &CCP9CON1L
};
#elif defined (CCP8CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[8]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L, &CCP4CON1L, 
    &CCP5CON1L, &CCP6CON1L, &CCP7CON1L, &CCP8CON1L 
};
#elif defined (CCP7CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[7]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L, &CCP4CON1L, 
    &CCP5CON1L, &CCP6CON1L, &CCP7CON1L
};
#elif defined (CCP6CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[6]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L, &CCP4CON1L, 
    &CCP5CON1L, &CCP6CON1L
};
#elif defined (CCP5CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[5]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L, &CCP4CON1L, 
    &CCP5CON1L
};
#elif defined (CCP4CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[4]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L, &CCP4CON1L
};
#elif defined (CCP3CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[3]={
    &CCP1CON1L, &CCP2CON1L, &CCP3CON1L
};
#elif defined (CCP2CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[2]={
    &CCP1CON1L, &CCP2CON1L
};
#elif defined (CCP1CON1L)
volatile uint16_t* p33c_CcpInstance_Handles[1]={
    &CCP1CON1L
};
#else
#pragma message "selected device has no supported PWM generators"
#endif



/*********************************************************************************
 * @ingroup lib-layer-pral-properties-private-ccp
 * @var ccpConfigDefault
 * @brief CCP Register Set reset state template
 * 
 * @details
 *     This P33C_CCP_MODULE_SFRSET_s data object provides a template of register 
 *     configuration values for a CCP peripheral instance. 
 * 
 *     Default configuration:
 *         - all options are reset to their default state
 * 
 *********************************************************************************/
/**@ingroup lib-layer-pral-properties-private-ccp */

volatile struct P33C_CCP_INSTANCE_s ccpConfigDefault = { 
    
    .CCPxTMRL.value = 0,
    .CCPxTMRH.value = 0,
    .CCPxBUFH.value = 0,
    .CCPxBUFL.value = 0,
    .CCPxPRH.value  = 0,
    .CCPxPRL.value = 0,
    .CCPxRAL.value = 0,
    .CCPxRBL.value = 0,
    .CCPxCON1H.value= 0,
    .CCPxCON1L.value = 0x0000,
    .CCPxCON2H.value = 0,
    .CCPxCON2L.value = 0,
    .CCPxCON3H.value= 0,
    .CCPxSTATL.value= 0
    
   };

/* PRIVATE FUNCTION CALL PROTOTYPES*/
//    (none)


/*********************************************************************************
 * @fn     volatile struct P33C_CCP_INSTANCE_s p33c_CcpInstance_ConfigRead(volatile uint16_t ccpInstance)
 * @ingroup lib-layer-pral-functions-public-ccp
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

volatile struct P33C_CCP_INSTANCE_s p33c_CcpInstance_ConfigRead(volatile uint16_t ccpInstance){

 volatile struct P33C_CCP_INSTANCE_s* ccp;
    
    // Capture Handle: set pointer to memory address of desired PWM instance
    ccp = p33c_CcpInstance_GetHandle(ccpInstance); 
    
    return(*ccp);
}

/********************************************************************************
 * @fn     volatile uint16_t p33c_CcpInstance_ConfigWrite(volatile uint16_t ccpInstance, volatile struct P33C_CCP_INSTANCE_s ccpConfig)
 * @ingroup lib-layer-pral-functions-public-ccp
 * @brief  Writes a user-defined configuration to the CCP instance registers
 * @param  ccpInstance Index of the Capture/Compare peripheral instance of type unsinged integer
 * @param  ccpConfig SCCP/MCCP instance special function register data object of type struct P33C_CCP_INSTANCE_s
 * @return 0 = failure, writing to CCP instance was not successful
 * @return 1 = success, writing to CCP instance was successful
 * 
 * @details
 *     This function writes a user-defined CCP instance configuration of type 
 *     P33C_CCP_MODULE_SFRSET_s to the CCP instance registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly 
 * 
 *********************************************************************************/

volatile uint16_t p33c_CcpInstance_ConfigWrite(volatile uint16_t ccpInstance, 
                                volatile struct P33C_CCP_INSTANCE_s ccpConfig)
{
    volatile uint16_t retval=1;
    volatile struct P33C_CCP_INSTANCE_s* ccp;    

    // Set pointer to memory address of desired CCP instance
    ccp = p33c_CcpInstance_GetHandle(ccpInstance); 
    *ccp = ccpConfig;
    
    return(retval);
    
}

// end of file
