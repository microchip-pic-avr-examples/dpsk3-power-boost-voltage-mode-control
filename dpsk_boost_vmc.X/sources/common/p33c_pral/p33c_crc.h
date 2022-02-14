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

/**************************************************************************************************
 * @file p33c_crc.h
 * @see  p33c_crc.c
 * @brief Generic Cyclic Redundancy Check (header file)
 * @details
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 * 
 *************************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef P33C_CRC_SFR_ABSTRACTION_H
#define	P33C_CRC_SFR_ABSTRACTION_H

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "p33c_macros.h" // include inline assembly macro extensions header file 

// GENERIC CRC MODULE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_CRC_MODULE_s

/***********************************************************************************
 * @ingroup lib-layer-pral-properties-public-crc
 * @struct P33C_CRC_MODULE_s
 * @brief Abstracted set of Special Function Registers of the Cyclic Redundancy Check module 
 * @details
 * This structure defines an abstracted set of Special Function Registers of 
 * Cyclic Redundancy Check peripheral module base registers. Users can use this 
 * abstracted set of registers to capture register settings from or write  
 * generic register settings to these peripheral base registers.
 * 
 **********************************************************************************/

    struct P33C_CRC_MODULE_s {
        union {
            volatile struct tagCRCCONLBITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        } CrcConl;    // CRCCON1: CRC Control Register 1
        union {
            volatile struct tagCRCCONHBITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        } CrcConh;    // CRCCON2: CRC Control Register 2
        union {
            struct {
                uint16_t CRCXORL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CrcXorl;    // CRCXORL: CRC XOR Low Register
        union {
            struct {
                uint16_t CRCXORH : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CrcXorh;    // CRCXORH: CRC XOR High Register
        union {
            struct {
                uint16_t CRCDATL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CrcDatl;    // CRCDATL: CRC Data Low Register
        union {
            struct {
                uint16_t CRCDATH : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CrcDath;    // CRCDATH: CRC Data High Register
		union {
            struct {
                uint16_t CRCWDATL : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CrcWdatl;    // CRCWDATL: CRC Shift Low Register
        union {
            struct {
                uint16_t CRCWDATH : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } CrcWdath;    // CRCWDATL: CRC Shift High Register
    } __attribute__((packed));
    typedef struct P33C_CRC_MODULE_s P33C_CRC_MODULE_t; // DMA MODULE REGISTER SET
    
//#define CRC16_PVIZ_POLYNOMIAL ((uint16_t)0x8005) // Standard Polynomial
#define CRC16_PVIZ_REV_POLYNOMIAL ((uint16_t)0xA001) // Standard Polynomial 0x8005
#define CRC16_PVIZ_SEED_VALUE ((uint16_t)0x0000) // non-direct of 0x0000   
   
//#define CRC16_CCITT_POLYNOMIAL ((uint16_t)0x1021) // Standard Polynomial
#define CRC16_CCITT_REV_POLYNOMIAL ((uint16_t)0x8408) // Standard Polynomial
#define CRC16_CCITT_SEED_VALUE ((uint16_t)0x0000) // non-direct of 0x0000       
    
enum CRC_POLYNOMIAL_e {
    CRC8_STANDARD_POLYNOMIAL =  0xD5,
    CRC8_AUTOSAR_POLYNOMIAL =   0x2F,
    CRC8_BLUETOOTH_POLYNOMIAL = 0xA7,
    CRC8_CCITT_POLYNOMIAL =     0x07,
    CRC8_DALLAS_POLYNOMIAL =    0x31,
    CRC8_DARC_POLYNOMIAL =      0x39,
    CRC8_GSMB_POLYNOMIAL =      0x49,
    CRC8_SAEJ1850_POLYNOMIAL =  0x1D,
    CRC8_WCDMA_POLYNOMIAL =     0x9B,
    CRC16_PVIZ_POLYNOMIAL =     0x8005,
    CRC16_CHAKRAVARTY_POLYNOMIAL = 0x2F15,
    CRC16_ARINC_POLYNOMIAL =    0xA02B,
    CRC16_CCITT_POLYNOMIAL =    0x1021,
    CRC16_CDMA_POLYNOMIAL =     0xC867,
    CRC16_DECT_POLYNOMIAL =     0x0589,
    CRC16_DIF_POLYNOMIAL =     	0x8BB7,
    CRC16_DNP_POLYNOMIAL =      0x3D65,
    CRC16_IBM_POLYNOMIAL =      0x8005,
    CRC16_OPENSAFETY_A_POLYNOMIAL =     0x5935,
    CRC16_OPENSAFETY_B_POLYNOMIAL =     0x755B,
    CRC16_PROFIBUS_POLYNOMIAL =         0x1DCF
}; 
typedef enum CRC_POLYNOMIAL_e CRC_POLYNOMIAL_t;  

/*********************************************************************************
 * @fn      volatile struct P33C_CRC_MODULE_s* p33c_CrcModule_GetHandle(void)
 * @ingroup lib-layer-pral-functions-public-crc
 * @brief   Gets pointer to CRC Module SFR set
 * @param   void
 * @return  struct P33C_CRC_MODULE_s Pointer to CRC module special function register set object 
 *  
 * @details
 *      This function returns the pointer to a CRC module register set in
 *    Special Function Register memory space. This pointer can be used to 
 *    directly write to/read from the Special Function Registers of the 
 *    CRC peripheral module configuration.
 *********************************************************************************/
    #define p33c_CrcModule_GetHandle() (struct P33C_CRC_MODULE_s*)&CRCCONL
    
#endif // end of P33C_CRC_MODULE_s

   
/* ********************************************************************************************* * 
 * API FUNCTION PROTOTYPES
 * ********************************************************************************************* */

extern volatile uint16_t p33c_CrcModule_Dispose(void);
extern volatile struct P33C_CRC_MODULE_s p33c_CrcModule_ConfigRead(void);
extern volatile uint16_t p33c_CrcModule_ConfigWrite(
        volatile struct P33C_CRC_MODULE_s crcModuleConfig);
extern volatile uint16_t p33c_CrcModule_Initialize(void);
extern volatile uint16_t p33c_CrcModule_Get_Data8_CRC16(
       volatile uint8_t *data, volatile uint8_t start, volatile uint8_t size);
extern volatile uint16_t p33c_CrcModule_Polynomial_Config(volatile uint8_t lendian, volatile uint8_t data_width,
        volatile uint8_t poly_size, volatile enum CRC_POLYNOMIAL_e poly, volatile uint16_t seed);

/* ********************************************************************************************* * 
 * DMA MODULE CONFIGURATION TEMPLATES
 * ********************************************************************************************* */
extern volatile struct P33C_CRC_MODULE_s crcModuleConfigClear;
extern volatile struct P33C_CRC_MODULE_s crcModuleConfigPviz;

#endif	/* P33C_CRC_SFR_ABSTRACTION_H */

// end of file
