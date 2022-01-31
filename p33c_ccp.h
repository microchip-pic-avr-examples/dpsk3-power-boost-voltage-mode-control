/*************************************************************************************************
 * @file   p33c_ccp.h
 * @author I62419
 * @date   Created on October 12, 2020, 5:41 PM
 ************************************************************************************************/

/*************************************************************************************************
 * @brief Generic Capture Compare Driver Module (header file)
 * @details
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 ************************************************************************************************/

#ifndef P33C_CCP_SFR_ABSTRACTION_H
#define	P33C_CCP_SFR_ABSTRACTION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types


#ifndef P33C_CCP_INSTANCE_s     

/***********************************************************************************
 * @ingroup lib-layer-pral-properties-public-ccp
 * @struct P33C_CCP_INSTANCE_SFRSET_s
 * @brief Abstracted set of Special Function Registers of a Capture Compare peripheral instance
 * @details
 * This structure defines an abstracted set of Special Function Registers of a 
 * Input Capture/Output Compare peripheral instance. Users can use this abstracted
 * set of registers to capture register settings from or write generic register 
 * settings to a specific instance of this peripheral.
 * 
 **********************************************************************************/

    struct P33C_CCP_INSTANCE_s {

        union {
            struct tagCCP1CON1LBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxCON1L; // CCPxCON1L: CCPx CONTROL 1 LOW REGISTERS

        union {
            struct tagCCP1CON1HBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxCON1H; // CCPxCON1H: CCPx CONTROL 1 HIGH REGISTERS

        union {
            struct tagCCP1CON2LBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxCON2L; // CCPxCON2L: CCPx CONTROL 2 LOW REGISTERS

        union {
            struct tagCCP1CON2HBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxCON2H; // CCPxCON2H: CCPx CONTROL 2 HIGH REGISTERS

        #if defined (CCP9CON3L)
        union {
            struct tagCCP9CON3LBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxCON3L; // CCPxCON3L: CCPx CONTROL 3 LOW REGISTERS (implemented in MCCP9 module only)
        #else
        volatile unsigned :16;  // (reserved) Memory gap between CCPxCON2H and CCPxCON3H
        #endif
        
        union {
            struct tagCCP1CON3HBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxCON3H; // CCPxCON3H: CCPx CONTROL 3 HIGH REGISTERS

        union {
            struct tagCCP1STATLBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxSTATL; // CCPxSTATL: CCPx STATUS REGISTER

        volatile unsigned :16; // (reserved)
        
        union {
            struct {
                volatile uint16_t CCPTMRL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxTMRL; // CCPxTMRL: CCPx TIMER COUTER REGISTER LOW 

        union {
            struct {
                volatile uint16_t CCPTMRH : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxTMRH; // CCPxTMRH: CCPx TIMER COUTER REGISTER HIGH

        union {
            struct {
                volatile uint16_t CCPPRL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxPRL; // CCPx TIMER PERIOD REGISTER LOW

        union {
            struct {
                volatile uint16_t CCPPRH : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxPRH; // CCPx TIMER PERIOD REGISTER HIGH

        union {
            struct {
                volatile uint16_t CCPRAL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxRAL; // CCPxRAL: CCPx PRIMARY OUTPUT COMPARE DATA BUFFER LOW

        volatile unsigned :16;
        
        union {
            struct {
                volatile uint16_t CCPRBL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxRBL; // CCPxRBL: CCPx SECONDARY OUTPUT COMPARE DATA BUFFER LOW

        volatile unsigned :16;
        
        union {
            struct {
                volatile uint16_t CCPBUFL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxBUFL; // CCPxBUFL: CCPx INPUT CAPTURE BUFFER LOW

        union {
            struct {
                volatile uint16_t CCPBUFH : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CCPxBUFH; // CCPxBUFH: CCPx INPUT CAPTURE BUFFER HIGH
        
    } __attribute__((packed));
    
    typedef struct P33C_CCP_INSTANCE_s P33C_CCP_INSTANCE_t;  ///< CCP INSTANCE SPECIAL FUNCTION REGISTER SET
    
/*********************************************************************************
 * @ingroup lib-layer-pral-properties-public-ccp
 * @def     P33C_CCP_SFR_OFFSET
 * @brief   Derives the address offset between two peripheral instances
 * @details
 * This macro derives the address offset between two peripheral instances. 
 * Users can use this address offset to derive the start address to/from which
 * the register set should be written or read.
 **********************************************************************************/
    #define P33C_CCP_SFR_OFFSET  ((volatile uint16_t)&CCP2CON1L - (volatile uint16_t)&CCP1CON1L) ///< CCPx SFR set instance offset

	// Determine number of available PWM generators on the selected device
	#if defined (CCP9CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      9
		#define DAC_INSTANCE_COUNT	9
	#elif defined (CCP8CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      8    
		#define DAC_INSTANCE_COUNT	8
	#elif defined (CCP7CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      7    
		#define DAC_INSTANCE_COUNT	7
	#elif defined (CCP6CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      6    
		#define DAC_INSTANCE_COUNT	6
	#elif defined (CCP5CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      5    
		#define DAC_INSTANCE_COUNT	5
	#elif defined (CCP4CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      4    
		#define DAC_INSTANCE_COUNT	4
	#elif defined (CCP3CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      3    
		#define DAC_INSTANCE_COUNT	3
	#elif defined (CCP2CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      2    
		#define DAC_INSTANCE_COUNT	2
	#elif defined (CCP1CON1L)
		// Array of pointers to first registers of DAC instances on this device
		#define P33C_DAC_COUNT      1    
		#define DAC_INSTANCE_COUNT	1
	#endif


/*********************************************************************************
 * @def    p33c_CcpInstance_GetHandle(x)
 * @ingroup lib-layer-pral-functions-public-ccp
 * @brief  Gets pointer to CCP instance SFR set
 * @param  x  Index of the Capture/Compare peripheral instance of type unsigned integer
 * @return Pointer to SCCP/MCCP instance special function register data object of type struct P33C_CCP_INSTANCE_s 
 *  
 * @details
 *      This macro returns the pointer to a CCP module register set
 *    Special Function Register memory space. This pointer can be used to 
 *    directly write to/read from the Special Function Registers of the 
 *    CCP peripheral module configuration.
 * 
 *********************************************************************************/
    extern volatile uint16_t* p33c_CcpInstance_Handles[];
    #define p33c_CcpInstance_GetHandle(x) (struct P33C_CCP_INSTANCE_s*)p33c_CcpInstance_Handles[(x-1)]
    
    
#endif
    
/* GLOBAL FUNCTION CALL PROTOTYPES */

extern volatile struct P33C_CCP_INSTANCE_s  p33c_CcpInstance_ConfigRead(volatile uint16_t ccpInstance);
extern volatile uint16_t p33c_CcpInstance_ConfigWrite(
                volatile uint16_t ccpInstance, 
                volatile struct P33C_CCP_INSTANCE_s ccpConfig
            );


#endif	/* P33C_CCP_SFR_ABSTRACTION_H */
// END OF FILE
