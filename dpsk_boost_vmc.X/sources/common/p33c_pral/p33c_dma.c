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

#include "p33c_dma.h"

#if defined (DMACH7)
volatile uint16_t* p33c_DmaChannel_Handles[8]={
    &DMACH0, &DMACH1, &DMACH2, &DMACH3,
    &DMACH4, &DMACH5, &DMACH6, &DMACH7
};
#elif defined (DMACH6)
volatile uint16_t* p33c_DmaChannel_Handles[7]={
    &DMACH0, &DMACH1, &DMACH2, &DMACH3
    &DMACH4, &DMACH5, &DMACH6
};
#elif defined (DMACH5)
volatile uint16_t* p33c_DmaChannel_Handles[6]={
    &DMACH0, &DMACH1, &DMACH2, &DMACH3
    &DMACH4, &DMACH5
};
#elif defined (DMACH4)
volatile uint16_t* p33c_DmaChannel_Handles[5]={
    &DMACH0, &DMACH1, &DMACH2, &DMACH3
    &DMACH4
};
#elif defined (DMACH3)
volatile uint16_t* p33c_DmaChannel_Handles[4]={
    &DMACH0, &DMACH1, &DMACH2, &DMACH3
};
#elif defined (DMACH2)
volatile uint16_t* p33c_DmaChannel_Handles[3]={
    &DMACH0, &DMACH1, &DMACH2
};
#elif defined (DMACH1)
volatile uint16_t* p33c_DmaChannel_Handles[2]={
    &DMACH0, &DMACH1
};
#elif defined (DMACH0)
volatile uint16_t* p33c_DmaChannel_Handles[1]={
    &DMACH0
};
#else
#pragma message "selected device has no supported DMA channels"
#endif

/*********************************************************************************
 * @fn      volatile uint16_t p33c_DmaModule_Dispose(void)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Resets all DMA Module registers to their RESET default values
 * @param   void
 * @return  0 = failure, disposing DMA module was not successful
 * @return  1 = success, disposing DMA module was successful
 * 
 * @details
 *     This function clears all DMA module registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - addressable memory range is reset to default (maximum range)
 *         - stop operation in IDLE mode
 *         - channel priority scheme is set to Fixed Priority Scheme
 * 
 *********************************************************************************/

volatile uint16_t p33c_DmaModule_Dispose(void)
{
    volatile uint16_t retval=1;
    
    retval = p33c_DmaModule_ConfigWrite(dmaModuleConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @fn      volatile struct P33C_DMA_MODULE_s p33c_DmaModule_ConfigRead(void)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Read the current configuration from the DMA module base registers
 * @param   void
 * @return  0 = failure, reading DMA module was not successful (returns NULL)
 * @return  n = success, reading DMA module was successful (returns result of type P33C_DMA_MODULE_s)
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_DMA_MODULE_s. Users can read and 
 *     verify or modify the configuration to write it back to the DMA module  
 *     registers.
 * 
 *********************************************************************************/

volatile struct P33C_DMA_MODULE_s p33c_DmaModule_ConfigRead(void)
{
    volatile struct P33C_DMA_MODULE_s* dmac;

    // Set pointer to memory address of DMA base register set
    dmac = p33c_DmaModule_GetHandle();

    return(*dmac);
    
}

/*********************************************************************************
 * @fn      volatile uint16_t p33c_DmaModule_ConfigWrite(volatile struct P33C_DMA_MODULE_s dmaModuleConfig)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Writes a user-defined configuration to the DMA module base registers
 * @param   dmaModuleConfig DIrect Memory Access module configuration of type struct P33C_DMA_MODULE_s
 * @return  0 = failure, writing DMA module was not successful
 * @return  1 = success, writing DMA module was successful
 * 
 * @details
 *     This function writes a user-defined DMA module configuration of  
 *     type P33C_DMA_MODULE_s to the DMA module base registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_DmaModule_ConfigWrite(
        volatile struct P33C_DMA_MODULE_s dmaModuleConfig
)
{
    volatile uint16_t retval=1;
    volatile struct P33C_DMA_MODULE_s* dmac;    

    // Set pointer to memory address of the DMA module base registers
    dmac = p33c_DmaModule_GetHandle();
    *dmac = dmaModuleConfig;
    
    return(retval);
    
}


/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */


/*********************************************************************************
 * @fn      volatile uint16_t p33c_DmaInstance_Dispose(volatile uint16_t dmaInstance)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Resets all DMA Instance registers to their RESET default values
 * @param   dmaInstance  Index of the selected DMA Instance (1=DMA1, 2=DMA2, etc.)
 * @return  0 = failure, disposing DMA instance was not successful
 * @return  1 = success, disposing DMA instance was successful
 * 
 * @details
 *     This function clears all DMA instance registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - all outputs are set to logic functions
 *         - all analog functions are disabled
 *         - all pull-up and pull-down resistors are disabled
 *         - all DMAs are operating in push-pull mode (open drain disabled)
 *         - all DMAs are configured as input with their signal level HIGH
 * 
 *********************************************************************************/

volatile uint16_t p33c_DmaInstance_Dispose(volatile uint16_t dmaInstance)
{
    volatile uint16_t retval=1;

    retval = p33c_DmaInstance_ConfigWrite(dmaInstance, dmaInstanceConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @fn      volatile struct P33C_DMA_INSTANCE_s p33c_DmaInstance_ConfigRead(volatile uint16_t dmaInstance)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Read the current configuration from the DMA instance registers
 * @param   dmaInstance  Index of the selected DMA Instance (1=DMA1, 2=DMA2, etc.)
 * @return  DMA instance object of type struct P33C_DMA_INSTANCE_s of the selected DMA instance
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_DMA_INSTANCE_s. Users can read and 
 *     verify or modify the configuration to write it back to the DMA instance  
 *     registers or copy configurations to other instances of the same type.
 * 
 *********************************************************************************/

volatile struct P33C_DMA_INSTANCE_s p33c_DmaInstance_ConfigRead(volatile uint16_t dmaInstance)
{
    volatile struct P33C_DMA_INSTANCE_s* dma;

    // Set pointer to memory address of desired DMA instance
    dma = p33c_DmaInstance_GetHandle(dmaInstance);

    return(*dma);
    
}

/*********************************************************************************
 * @fn      volatile uint16_t p33c_DmaInstance_ConfigWrite(volatile uint16_t dmaInstance, volatile struct P33C_DMA_INSTANCE_s dmaConfig)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Writes a user-defined configuration to the DMA instance registers
 * @param   dmaInstance Index of the selected DMA Instance (1=DMA1, 2=DMA2, etc.)
 * @param   dmaConfig DMA instance object of type struct P33C_DMA_INSTANCE_s of the selected DMA instance
 * @return  0 = failure, writing DMA instance was not successful
 * @return  1 = success, writing DMA instance was successful
 * 
 * @details
 *     This function writes a user-defined DMA instance configuration of type 
 *     P33C_DMA_INSTANCE_s to the DMA instance registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_DmaInstance_ConfigWrite(
            volatile uint16_t dmaInstance, 
            volatile struct P33C_DMA_INSTANCE_s dmaConfig)
{
    volatile uint16_t retval=1;
    volatile struct P33C_DMA_INSTANCE_s* dma;    

    // Set pointer to memory address of desired DMA instance
    dma = p33c_DmaInstance_GetHandle(dmaInstance);
    *dma = dmaConfig;
    
    return(retval);
    
}


/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */

/*********************************************************************************
 * @var dmaModuleConfigClear
 * @ingroup lib-layer-pral-properties-private-dma
 * @brief Default RESET configuration of DMA module 
 *
 * @details
 *  Default configuration of the DMA module SFRs with all its registers 
 *  being reset to their default state when the device comes out of RESET.
 *  The minimum and maximum addresses specifying the memory range addressable
 *  by the DMA module affects/limits all DMA channels. 
 *  (Please read the device data sheet for details)
 * 
 *  Programmers can use this template to reset a previously used
 *  DMA module when it's not used anymore or to ensure a known startup
 *  condition before writing individual configurations to its SFRs.
 * 
 ********************************************************************************/

volatile struct P33C_DMA_MODULE_s dmaModuleConfigClear = {
    
    .DmaCon.value = 0x0000, ///< DMA Module disabled, DMA Stop In Idle Mode, Channel FIxed Priority Scheme Selection
    .DmaBuf.value = 0x0000, ///< DMA buffer is Read Only (Writes are performed with zeros)
    .DmaL.value   = P33C_DACL_DEFAULT, ///< DMA address range minimum is reset to Default
    .DmaH.value   = P33C_DACH_DEFAULT, ///< DMA address range maximum is reset to Default
};

/*********************************************************************************
 * @var dmaInstanceConfigClear
 * @ingroup lib-layer-pral-properties-private-dma
 * @brief Default RESET configuration of one DMA instance SFRs
 * @param dmaConfigClear DMA instance Special Function Register (SFR) set
 *
 * @details
 *   Default configuration of the DMA instance SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   DMA instance when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 * *******************************************************************************/

volatile struct P33C_DMA_INSTANCE_s dmaInstanceConfigClear = {
    
        .DMACHx.value  = 0x0000,    // Clear DMA Channel n Control Register
        .DMAINTx.value = 0x0000,    // Clear DMA Channel n Interrupt Control Register
        .DMASRCx.value = 0x0000,    // Clear DMA Channel n Source Address Register
        .DMADSTx.value = 0x0000,    // DMA Channel n Destination Address Register
        .DMACNTx.value = 0x0000     // DMA Channel n Count Register
    };


// end of file
