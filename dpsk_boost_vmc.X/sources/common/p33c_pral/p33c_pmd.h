/*************************************************************************************************
 * @file   p33c_pmd.h
 * @author I62419
 * @date   Created on October 12, 2020, 5:41 PM
 ************************************************************************************************/

/*************************************************************************************************
 * @brief Generic Peripheral Module Disable Module Access (header file)
 * @details
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 ************************************************************************************************/

#ifndef P33C_PMD_SFR_ABSTRACTION_H
#define	P33C_PMD_SFR_ABSTRACTION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#ifndef P33C_PMD_MODULE_s     

/***********************************************************************************
 * @ingroup lib-layer-pral-properties-public-pmd
 * @struct P33C_PMD_INSTANCE_SFRSET_s
 * @brief Abstracted set of Peripheral Module Disable Special Function Registers 
 * @details
 * This structure defines an abstracted set of Special Function Registers of the 
 * Peripheral Module Disable module. Users can use this abstracted set of registers 
 * to capture register settings from or write generic register settings to the PMD
 * module.
 * 
 **********************************************************************************/

    struct P33C_PMD_MODULE_s {

		#ifdef PMDCON
        union {
            struct tagPMDCONBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmdcon; // PMDCON: PERIPHERAL MODULE DISABLE CONTROL REGISTER
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
        unsigned  : 16;     // reserved/unused memory space

        #ifdef PMD1
        union {
            struct tagPMD1BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd1; // PMD1: PERIPHERAL MODULE DISABLE 1 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif

		#ifdef PMD2
        union {
            struct tagPMD2BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd2; // PMD2: PERIPHERAL MODULE DISABLE 2 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD3
        union {
            struct tagPMD3BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd3; // PMD2: PERIPHERAL MODULE DISABLE 3 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD4
        union {
            struct tagPMD4BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd4; // PMD4: PERIPHERAL MODULE DISABLE 4 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD5
        union {
            struct tagPMD5BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd5; // PMD2: PERIPHERAL MODULE DISABLE 5 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD6
        union {
            struct tagPMD6BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd6; // PMD2: PERIPHERAL MODULE DISABLE 6 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD7
        union {
            struct tagPMD7BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd7; // PMD2: PERIPHERAL MODULE DISABLE 7 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD8
        union {
            struct tagPMD8BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd8; // PMD2: PERIPHERAL MODULE DISABLE 8 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
		#ifdef PMD9
        union {
            struct tagPMD9BITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } pmd9; // PMD2: PERIPHERAL MODULE DISABLE 9 CONTROL REGISTER LOW
        #else
        unsigned  : 16;     // reserved/unused memory space
		#endif
        
    } __attribute__((packed));
    
    typedef struct P33C_PMD_MODULE_s P33C_PMD_MODULE_t;  ///< Peripheral Module Disable module Special Function Register set data type


/*********************************************************************************
 * @def    p33c_Pmd_GetHandle()
 * @ingroup lib-layer-pral-functions-public-pmd
 * @brief  Gets pointer to Peripheral Module Disable SFR set
 * @return Pointer to Peripheral Module Disable special function register data object of type struct P33C_PMD_INSTANCE_s 
 *  
 * @details
 *      This macro returns the pointer to the Peripheral Module Disable 
 *    Special Function Register memory space. This pointer can be used to 
 *    directly write to/read from the Special Function Registers of the 
 *    Peripheral Module Disable configuration.
 * 
 *********************************************************************************/
    #define p33c_Pmd_GetHandle() (struct P33C_PMD_MODULE_s*)&PMD1
    
    
#endif /* P33C_PMD_MODULE_s */
    
/* GLOBAL DATA OBJECTS */
extern volatile struct P33C_PMD_MODULE_s pmdConfigDefault;

/* GLOBAL FUNCTION CALL PROTOTYPES */
extern volatile struct P33C_PMD_MODULE_s  p33c_Pmd_ConfigRead(void);
extern volatile uint16_t p33c_Pmd_ConfigWrite(volatile struct P33C_PMD_MODULE_s ccpConfig);

#endif	/* P33C_PMD_SFR_ABSTRACTION_H */

// end of file
