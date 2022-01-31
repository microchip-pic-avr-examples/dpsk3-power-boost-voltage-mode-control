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

#include "p33c_dac.h"

// Determine number of available DAC instances on the selected device
#if defined (DAC8CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[8]={ 
		&DAC1CONL, &DAC2CONL, &DAC3CONL, &DAC4CONL, 
		&DAC5CONL, &DAC6CONL, &DAC7CONL, &DAC8CONL 
	};
	#define P33C_DAC_COUNT   8
#elif defined (DAC7CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[7]={ 
		&DAC1CONL, &DAC2CONL, &DAC3CONL, &DAC4CONL, 
		&DAC5CONL, &DAC6CONL, &DAC7CONL 
	};
	#define P33C_DAC_COUNT   7
#elif defined (DAC6CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[6]={ 
		&DAC1CONL, &DAC2CONL, &DAC3CONL, &DAC4CONL, 
		&DAC5CONL, &DAC6CONL
	};
	#define P33C_DAC_COUNT   6
#elif defined (DAC5CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[5]={ 
		&DAC1CONL, &DAC2CONL, &DAC3CONL, &DAC4CONL, 
		&DAC5CONL
	};
	#define P33C_DAC_COUNT   5
#elif defined (DAC4CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[4]={ 
		&DAC1CONL, &DAC2CONL, &DAC3CONL, &DAC4CONL
	};
	#define P33C_DAC_COUNT   4
#elif defined (DAC3CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[3]={ 
		&DAC1CONL, &DAC2CONL, &DAC3CONL
	};
	#define P33C_DAC_COUNT   3
#elif defined (DAC2CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[2]={ 
		&DAC1CONL, &DAC2CONL
	};
	#define P33C_DAC_COUNT   2
#elif defined (DAC1CONL)
	// Array of pointers to first register of DAC instances on this device
	volatile uint16_t* p33cDacInstanceHandles[2]={ 
		&DAC1CONL
	};
	#define P33C_DAC_COUNT   1
#endif


/*********************************************************************************
 * @fn      volatile uint16_t p33c_DacModule_Dispose(void)
 * @ingroup lib-layer-pral-functions-public-dac
 * @brief   Resets all DAC Module registers to their RESET default values
 * @param   void
 * @return  0 = failure, disposing DAC module was not successful
 * @return  1 = success, disposing DAC module was successful
 * 
 * @details
 *     This function clears all DAC module registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - all outputs are set to logic functions
 *         - all analog functions are disabled
 *         - all pull-up and pull-down resistors are disabled
 *         - all DACs are operating in push-pull mode (open drain disabled)
 *         - all DACs are configured as input with their signal level HIGH
 * 
 *********************************************************************************/

volatile uint16_t p33c_DacModule_Dispose(void)
{
    volatile uint16_t retval=1;
    
    retval = p33c_DacModule_ConfigWrite(dacModuleConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @fn      volatile struct P33C_DAC_MODULE_s p33c_DacModule_ConfigRead(void)
 * @ingroup lib-layer-pral-functions-public-dac
 * @brief   Read the current configuration from the DAC module base registers
 * @param   void
 * @return  0 = failure, reading DAC module was not successful (returns NULL)
 * @return  n = success, reading DAC module was successful (returns 16-bit wide pointer)
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_DAC_MODULE_s. Users can read and 
 *     verify or modify the configuration to write it back to the DAC module  
 *     registers.
 * 
 *********************************************************************************/

volatile struct P33C_DAC_MODULE_s p33c_DacModule_ConfigRead(void)
{
    volatile struct P33C_DAC_MODULE_s* dac;

    // Set pointer to memory address of desired DAC instance
    dac = p33c_DacModule_GetHandle();

    return(*dac);
    
}

/*********************************************************************************
 * @fn      volatile uint16_t p33c_DacModule_ConfigWrite(volatile struct P33C_DAC_MODULE_s dacModuleConfig)
 * @ingroup lib-layer-pral-functions-public-dac
 * @brief   Writes a user-defined configuration to the DAC module base registers
 * @param   dacModuleConfig Digital-to-Analog converter module configuration of type struct P33C_DAC_MODULE_s
 * @return  0 = failure, writing DAC module was not successful
 * @return  1 = success, writing DAC module was successful
 * 
 * @details
 *     This function writes a user-defined DAC module configuration of type 
 *     P33C_DAC_MODULE_s to the DAC module base registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_DacModule_ConfigWrite(
        volatile struct P33C_DAC_MODULE_s dacModuleConfig
)
{
    volatile uint16_t retval=1;
    volatile struct P33C_DAC_MODULE_s* dac;    

    // Set pointer to memory address of the DAC module base registers
    dac = p33c_DacModule_GetHandle();
    *dac = dacModuleConfig;
    
    return(retval);
    
}


/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */

/*********************************************************************************
 * @fn      volatile uint16_t p33c_DacInstance_Dispose(volatile uint16_t dacInstance)
 * @ingroup lib-layer-pral-functions-public-dac
 * @brief   Resets all DAC Instance registers to their RESET default values
 * @param   dacInstance  Index of the selected DAC Instance (1=DAC1, 2=DAC2, etc.)
 * @return  0 = failure, disposing DAC instance was not successful
 * @return  1 = success, disposing DAC instance was successful
 * 
 * @details
 *     This function clears all DAC instance registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - all outputs are set to logic functions
 *         - all analog functions are disabled
 *         - all pull-up and pull-down resistors are disabled
 *         - all DACs are operating in push-pull mode (open drain disabled)
 *         - all DACs are configured as input with their signal level HIGH
 * 
 *********************************************************************************/

volatile uint16_t p33c_DacInstance_Dispose(volatile uint16_t dacInstance)
{
    volatile uint16_t retval=1;
    
    retval = p33c_DacInstance_ConfigWrite(dacInstance, dacConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @fn      volatile struct P33C_DAC_INSTANCE_s p33c_DacInstance_ConfigRead(volatile uint16_t dacInstance)
 * @ingroup lib-layer-pral-functions-public-dac
 * @brief   Read the current configuration from the DAC instance registers
 * @param   dacInstance  Index of the selected DAC Instance (1=DAC1, 2=DAC2, etc.)
 * @return  DAC instance object of type struct P33C_DAC_INSTANCE_s of the selected DAC instance
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_DAC_INSTANCE_s. Users can read and 
 *     verify or modify the configuration to write it back to the DAC instance  
 *     registers or copy configurations to other instances of the same type.
 * 
 *********************************************************************************/

volatile struct P33C_DAC_INSTANCE_s p33c_DacInstance_ConfigRead(volatile uint16_t dacInstance)
{
    volatile struct P33C_DAC_INSTANCE_s* dac;

    // Set pointer to memory address of desired DAC instance
    dac = p33c_DacInstance_GetHandle(dacInstance);

    return(*dac);
    
}

/*********************************************************************************
 * @fn      volatile uint16_t p33c_DacInstance_ConfigWrite(volatile uint16_t dacInstance, volatile struct P33C_DAC_INSTANCE_s dacConfig)
 * @ingroup lib-layer-pral-functions-public-dac
 * @brief   Writes a user-defined configuration to the DAC instance registers
 * @param   dacInstance Index of the selected DAC Instance (1=DAC1, 2=DAC2, etc.)
 * @param   dacConfig DAC instance object of type struct P33C_DAC_INSTANCE_s of the selected DAC instance
 * @return  0 = failure, writing DAC instance was not successful
 * @return  1 = success, writing DAC instance was successful
 * 
 * @details
 *     This function writes a user-defined DAC instance configuration of type 
 *     P33C_DAC_INSTANCE_s to the DAC instance registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_DacInstance_ConfigWrite(
            volatile uint16_t dacInstance, 
            volatile struct P33C_DAC_INSTANCE_s dacConfig)
{
    volatile uint16_t retval=1;
    volatile struct P33C_DAC_INSTANCE_s* dac;    

    // Set pointer to memory address of desired DAC instance
    dac = p33c_DacInstance_GetHandle(dacInstance);
    *dac = dacConfig;
    
    return(retval);
    
}


/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */

/*********************************************************************************
 * @var dacModuleConfigClear
 * @ingroup lib-layer-pral-properties-private-dac
 * @brief Default RESET configuration of the DAC module base SFRs
 *
 * @details
 *   Default configuration of the DAC module SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   DAC module when it's not used anymore or to ensure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 ********************************************************************************/

volatile struct P33C_DAC_MODULE_s dacModuleConfigClear = {

    .DacModuleCtrl1L.value = 0x0000,
    .DacModuleCtrl2L.value = 0x0000,
    .DacModuleCtrl2H.value = 0x0000

    };

/*********************************************************************************
 * @var dacModuleDefault
 * @ingroup lib-layer-pral-properties-private-dac
 * @brief Default configuration of DAC module running from 500 MHz input clock
 *
 * @details
 *  Default configuration of the DAC module SFRs with all its registers 
 *  being reset to their default state when the device comes out of RESET.
 *  The timing settings for settling time and transition mode time of the 
 *  built-in Pulse-Density Modulator ramp generator are reset to their
 *  recommended default values when operated from a 500 MHz clock input.
 *  (Please read the device data sheet for details)
 * 
 *  Programmers can use this template to reset a previously used
 *  DAC module when it's not used anymore or to ensure a known startup
 *  condition before writing individual configurations to its SFRs.
 * 
 ********************************************************************************/

volatile struct P33C_DAC_MODULE_s dacModuleDefault = {
    .DacModuleCtrl1L.value = 0x0080, ///< DAC Module disabled, DAC Stop In Idle Mode=0, DAC Clock Source=AFPLLO, DAC Clock Divider=1:1, Filter Clock Divider=1:1
    .DacModuleCtrl2H.bits.SSTIME = 0x008A, ///< Steady-state setting time is set to default of 0x8A
    .DacModuleCtrl2L.bits.TMODTIME = 0x0055 ///< Transition mode duration is set to default of 0x55
};

/*********************************************************************************
 * @var dacConfigClear
 * @ingroup lib-layer-pral-properties-private-dac
 * @brief Default RESET configuration of one DAC instance channel SFRs
 * @param dacConfigClear DAC instance Special Function Register (SFR) set
 *
 * @details
 *   Default configuration of the DAC instance SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   DAC instance when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 * *******************************************************************************/

volatile struct P33C_DAC_INSTANCE_s dacConfigClear = {
    
    .DACxCONL.value = 0x0000,
    .DACxCONH.value = 0x0000,
    .DACxDATL.value = 0x0000,
    .DACxDATH.value = 0x0000,
    .SLPxCONL.value = 0x0000,
    .SLPxCONH.value = 0x0000,
    .SLPxDAT.value  = 0x0000
        
    };


// end of file
