/*
 * File:   init_dsp.c
 * Author: M91406
 *
 * Created on October 16, 2018, 12:00 PM
 */


#include <xc.h>
#include "xc16_pral.h"

/***********************************************************************************
 * @fn uint16_t osDsp_Initialize(void)
 * @ingroup dsp-initialization
 * @brief  Digital Signal Processor initialization
 * @return unsigned integer 
 * 0=failure
 * 1=success
 * 
 * @details
 *   This routine initializes the default configuration of the 
 *   DSP core for performing SMPS control loop libraries.
 *   If any other section of the firmware needs to use the DSP 
 *   with different settings, this code module would have to 
 *   make sure the core configuration is reset to these defaults
 *   when the SMPS control library is executed.
 *  
 *   @note: 
 *   The configuration of the control library allows to add its own 
 *   core configuration save & restore cycle in the control code.
 *   Please enable this function in the control loop configuration
 *   if conflicts between different DSP configurations cannot be 
 *   resolved differently within the firmware.
 *   This routine initializes the default configuration of the 
 *   DSP core for performing SMPS control loop libraries.
 *   If any other section of the firmware needs to use the DSP 
 *   with different settings, this code module would have to 
 *   make sure the core configuration is reset to these defaults
 *   when the SMPS control library is executed.
 *  
 *   The configuration of the control library allows to add its own 
 *   core configuration save & restore cycle in the control code.
 *   Please enable this function in the control loop configuration
 *   if conflicts between different DSP configurations cannot be 
 *   resolved differently within the firmware.
 *    
 **********************************************************************************/
volatile uint16_t osDsp_Initialize(void) {
    
    volatile struct P33C_DSP_CONFIG_s* dsp;
	
    dsp = p33c_DspConfig_GetHandle();
    
    dsp->CORCON.bits.ACCSAT = CORCON_ACCSAT_131;  // Accumulator Saturation Mode Selection: 9.31 saturation (super saturation)
    dsp->CORCON.bits.IF = CORCON_IF_FRACTIONAL;   // Integer or Fractional Multiplier Mode Selection: Fractional mode is enabled for DSP multiply
    dsp->CORCON.bits.RND = CORCON_RND_UNBIASED;   // Rounding Mode Selection: Unbiased (convergent) rounding is enabled
    dsp->CORCON.bits.SATA = CORCON_SATA_ON;       // ACCA Saturation Enable: Accumulator A saturation is enabled
    dsp->CORCON.bits.SATB = CORCON_SATB_ON;       // ACCB Saturation Enable: Accumulator B saturation is enabled
    dsp->CORCON.bits.SATDW = CORCON_SATDW_OFF;    // Data Space Write from DSP Engine Saturation Enable: Data Space write saturation is enabled
    dsp->CORCON.bits.US = CORCON_US_SIGNED;       // DSP Multiply Unsigned/Signed Control: DSP engine multiplies are signed
    dsp->CORCON.bits.VAR = CORCON_VAR_FIXED;      // Variable Exception Processing Latency Control: Fixed exception processing is enabled

//    dsp->CORCON.bits.DL = CORCON_DL_0;              // (read only)
//    dsp->CORCON.bits.EDT = CORCON_EDT_RUN;          // control bit => do not set during configuration
//    dsp->CORCON.bits.SFA = CORCON_SFA_ACTIVE;       // (read only)
//    dsp->CORCON.bits.IPL3 = CORCON_IPL3_STAT_LT7;   // (read only)
    
    Nop();
    Nop();
    Nop();
    
    return(1);
}

