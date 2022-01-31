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
 * @file p33c_dma.h
 * @see  p33c_dma.c
 * @brief Generic DIrect Memory Access Driver Module (header file)
 * @details
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 * 
 *************************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef P33C_DMA_SFR_ABSTRACTION_H
#define	P33C_DMA_SFR_ABSTRACTION_H

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types


// GENERIC PDM DMA MODULE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_DMA_MODULE_s

/***********************************************************************************
 * @ingroup lib-layer-pral-properties-public-dma
 * @struct P33C_DMA_MODULE_s
 * @brief Abstracted set of Special Function Registers of the Direct Memory Access module 
 * @details
 * This structure defines an abstracted set of Special Function Registers of 
 * Direct Memory Access peripheral module base registers. Users can use this 
 * abstracted set of registers to capture register settings from or write  
 * generic register settings to these peripheral base registers.
 * 
 **********************************************************************************/

    struct P33C_DMA_MODULE_s {
        union {
            volatile struct tagDMACONBITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        } DmaCon;    // DMACON: DMA Engine Control Register
        union {
            struct {
                uint16_t DBUF : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } DmaBuf;    // DMABUF: DMA Data Buffer Register
        union {
            struct {
                uint16_t LADDR : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } DmaL;    // DMAL: DMA Low Address Limit Register
        union {
            struct {
                uint16_t HADDR : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } DmaH;    // DMAH: DMA High Address Limit Register
    } __attribute__((packed));
    typedef struct P33C_DMA_MODULE_s P33C_DMA_MODULE_t; // DMA MODULE REGISTER SET
    
/*********************************************************************************
 * @fn      volatile struct P33C_DMA_MODULE_s* p33c_DmaModule_GetHandle(void)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Gets pointer to DMA Module SFR set
 * @param   void
 * @return  struct P33C_DMA_MODULE_s Pointer to DMA module special function register set object 
 *  
 * @details
 *      This function returns the pointer to a DMA module register set in
 *    Special Function Register memory space. This pointer can be used to 
 *    directly write to/read from the Special Function Registers of the 
 *    DMA peripheral module configuration.
 *********************************************************************************/
    #define p33c_DmaModule_GetHandle() (struct P33C_DMA_MODULE_s*)&DMACON
    
#endif // end of P33C_DMA_MODULE_s

// GENERIC DMA INSTANCE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_DMA_INSTANCE_s

/***********************************************************************************
 * @ingroup lib-layer-pral-properties-public-dma
 * @struct P33C_DMA_INSTANCE_s
 * @brief Abstracted set of Special Function Registers of a Direct MEmory Access peripheral instance
 * @details
 * This structure defines an abstracted set of Special Function Registers of
 * Direct Memory Access peripheral instance registers. It provides an 
 * abstracted set of registers to capture register settings from or write   
 * generic register settings to this peripheral instance.
 * 
 **********************************************************************************/
    
    struct P33C_DMA_INSTANCE_s{
        union {
            volatile struct tagDMACH0BITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        } DMACHx; // DMACHx: DMA Channel x Control Register
        union {
            volatile struct tagDMAINT0BITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        } DMAINTx; // DMAINTn: DMA Channel n Interrupt Control Register
        union {
            struct {
                uint16_t SADDR : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } DMASRCx; // DMASRCx: DMA Channel x Source Address Register
        union {
            struct {
                uint16_t DADDR : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } DMADSTx; // DDMADSTx: DMA Channel x Destination Address Register
        union {
            struct {
                uint16_t CNT : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } DMACNTx; // DMACNTn: DMA Channel n Count Register
    } __attribute__((packed));
    typedef struct P33C_DMA_INSTANCE_s P33C_DMA_INSTANCE_t; // DMA INSTANCE REGISTER SET

/*********************************************************************************
 * @ingroup lib-layer-pral-properties-public-dma
 * @def     P33C_DMA_COUNT
 * @brief   Derives the number of available DMA channel instances
 * @details
 * This macro derives the number of available DMA channel instances. 
 * This value is required to verify and limit user access to available 
 * instances only.
 **********************************************************************************/
#if defined (DMACH7)
    #define P33C_DMA_COUNT   8
#elif defined (DMACH6)
    #define P33C_DMA_COUNT   7
#elif defined (DMACH5)
    #define P33C_DMA_COUNT   6
#elif defined (DMACH4)
    #define P33C_DMA_COUNT   5
#elif defined (DMACH3)
    #define P33C_DMA_COUNT   4
#elif defined (DMACH2)
    #define P33C_DMA_COUNT   3
#elif defined (DMACH1)
    #define P33C_DMA_COUNT   2
#else
    #pragma message "selected device has no supported DMA channels"
#endif
    
/*********************************************************************************
 * @ingroup lib-layer-pral-properties-public-dma
 * @def     P33C_DMA_SFR_OFFSET
 * @brief   Derives the address offset between two peripheral instances
 * @details
 * This macro derives the address offset between two peripheral instances. 
 * Users can use this address offset to derive the start address to/from which
 * the register set should be written or read.
 **********************************************************************************/
#ifndef P33C_DMA_SFR_OFFSET
  #define P33C_DMA_SFR_OFFSET  ((volatile uint16_t)&DMACH1 - (volatile uint16_t)&DMACH0)
#endif 

/*********************************************************************************
 * @ingroup lib-layer-pral-properties-public-dma
 * @def     P33C_DACL_DEFAULT
 * @brief   Derives the address offset between two peripheral instances
 * @details
 *   This macro derives the minimum memory address of the total memory range 
 *   addressable by the DMA peripheral instances. Users can use this address 
 *   to restore the default memory range addressable by the DMA peripheral.
 **********************************************************************************/

#define P33C_DACL_DEFAULT   0x0000  // Default DMA address range minimum address

/*********************************************************************************
 * @ingroup lib-layer-pral-properties-public-dma
 * @def     P33C_DACH_DEFAULT
 * @brief   Derives the maximum address of the DMA addressable range
 * @details
 *   This macro derives the maximum memory address of the total memory range 
 *   addressable by the DMA peripheral instances. Users can use this address 
 *   to restore the default memory range addressable by the DMA peripheral.
 **********************************************************************************/

#define P33C_DACH_DEFAULT   0x4FFF  // Default DMA address range maximum address

/*********************************************************************************
 * @fn      volatile struct P33C_DMA_MODULE_s* p33c_DmaModule_GetHandle(void)
 * @ingroup lib-layer-pral-functions-public-dma
 * @brief   Gets pointer to DMA Module SFR set
 * @param   void
 * @return  struct P33C_DMA_MODULE_s Pointer to DMA module special function register set object 
 *  
 * @details
 *      This function returns the pointer to a DMA module register set in
 *    Special Function Register memory space. This pointer can be used to 
 *    directly write to/read from the Special Function Registers of the 
 *    DMA peripheral module configuration.
 *********************************************************************************/

    extern volatile uint16_t* p33c_DmaChannel_Handles[];
    #define p33c_DmaInstance_GetHandle(x) (struct P33C_DMA_INSTANCE_s*)p33c_DmaChannel_Handles[(x)]

    
#endif // end of P33C_DMA_INSTANCE_s

#define DMATRG_INT0         0x00    // External Interrupt 0
#define DMATRG_SCCP1        0x01    // SCCP1 Interrupt
#define DMATRG_SPI1_RX      0x02    // SPI1 Receiver
#define DMATRG_SPI1_TX      0x03    // SPI1 Transmitter
#define DMATRG_UART1_RX     0x04    // UART1 Receiver
#define DMATRG_UART1_TX     0x05    // UART1 Transmitter
#define DMATRG_ECC_BERR     0x06    // ECC Single Bit Error
#define DMATRG_NVM_WRITE    0x07    // NVM Write Complete
#define DMATRG_INT1         0x08    // External Interrupt 1
#define DMATRG_SI2C1        0x09    // I2C1 Device Event
#define DMATRG_MI2C1        0x0A    // I2C1 Host Event
#define DMATRG_INT2         0x0B    // External Interrupt 2
#define DMATRG_SCCP2        0x0C    // SCCP2 Interrupt
#define DMATRG_INT3         0x0D    // External Interrupt 3
#define DMATRG_UART2_RX     0x0E    // UART2 Receiver
#define DMATRG_UART2_TX     0x0F    // UART2 Transmitter
#define DMATRG_SPI2_RX      0x10    // SPI2 Receiver
#define DMATRG_SPI2_TX      0x11    // SPI2 Transmitter
#define DMATRG_SCCP3        0x12    // SCCP3 Interrupt
#define DMATRG_SI2C2        0x13    // I2C2 Device Event
#define DMATRG_MI2C2        0x14    // I2C2 Host Event
#define DMATRG_SCCP4        0x15    // SCCP4 Interrupt
#define DMATRG_SCCP5        0x16    // SCCP5 Interrupt
#define DMATRG_SCCP6        0x17    // SCCP6 Interrupt
#define DMATRG_CRC          0x18    // CRC Generator Interrupt
#define DMATRG_PWM_EVTA     0x19    // PWM Event A
#define DMATRG_PWM_EVTB     0x1B    // PWM Event B
#define DMATRG_PG1EVT       0x1C    // PWM Generator 1
#define DMATRG_PG2EVT       0x1D    // PWM Generator 2
#define DMATRG_PG3EVT       0x1E    // PWM Generator 3
#define DMATRG_PG4EVT       0x1F    // PWM Generator 4
#define DMATRG_PG5EVT       0x20    // PWM Generator 5
#define DMATRG_PG6EVT       0x21    // PWM Generator 6
#define DMATRG_PG7EVT       0x22    // PWM Generator 7
#define DMATRG_PG8EVT       0x23    // PWM Generator 8
#define DMATRG_PWM_EVTC     0x24    // PWM Event C
#define DMATRG_SENT1        0x25    // SENT1 TX/RX
#define DMATRG_SENT2        0x26    // SENT2 TX/RX
#define DMATRG_ADC_DONE     0x27    // ADC1 Group Convert Done
#define DMATRG_AN0_DONE     0x28    // ADC Done AN0
#define DMATRG_AN1_DONE     0x29    // ADC Done AN1
#define DMATRG_AN2_DONE     0x2A    // ADC Done AN2
#define DMATRG_AN3_DONE     0x2B    // ADC Done AN3
#define DMATRG_AN4_DONE     0x2C    // ADC Done AN4
#define DMATRG_AN5_DONE     0x2D    // ADC Done AN5
#define DMATRG_AN6_DONE     0x2E    // ADC Done AN6
#define DMATRG_AN7_DONE     0x2F    // ADC Done AN7
#define DMATRG_AN8_DONE     0x30    // ADC Done AN8
#define DMATRG_AN9_DONE     0x31    // ADC Done AN9
#define DMATRG_AN10_DONE    0x32    // ADC Done AN10
#define DMATRG_AN11_DONE    0x33    // ADC Done AN11
#define DMATRG_AN12_DONE    0x34    // ADC Done AN12
#define DMATRG_AN13_DONE    0x35    // ADC Done AN13
#define DMATRG_AN14_DONE    0x36    // ADC Done AN14
#define DMATRG_AN15_DONE    0x37    // ADC Done AN15
#define DMATRG_AN16_DONE    0x38    // ADC Done AN16
#define DMATRG_AN17_DONE    0x39    // ADC Done AN17
#define DMATRG_AN18_DONE    0x3A    // ADC Done AN18
#define DMATRG_AN19_DONE    0x3B    // ADC Done AN19
#define DMATRG_AN20_DONE    0x3C    // ADC Done AN20
#define DMATRG_AN21_DONE    0x3D    // ADC Done AN21
#define DMATRG_AN22_DONE    0x3E    // ADC Done AN22
#define DMATRG_AN23_DONE    0x3F    // ADC Done AN23
#define DMATRG_AD1FLTR1     0x40    // Oversample Filter 1
#define DMATRG_AD1FLTR2     0x41    // Oversample Filter 2
#define DMATRG_AD1FLTR3     0x42    // Oversample Filter 3
#define DMATRG_AD1FLTR4     0x43    // Oversample Filter 4
#define DMATRG_CLC1         0x44    // CPC1 Positive Edge Interrupt
#define DMATRG_CLC2         0x45    // CPC2 Positive Edge Interrupt
#define DMATRG_SPI1_FLT     0x46    // SPI1 Fault Interrupt
#define DMATRG_SPI2_FLT     0x47    // SPI2 Fault Interrupt
#define DMATRG_PWM_EVTD     0x57    // PWM Event D
#define DMATRG_PWM_EVTE     0x58    // PWM Event E
#define DMATRG_PWM_EVTF     0x59    // PWM Event F
#define DMATRG_SCCP7        0x5C    // SCCP7 Interrupt
#define DMATRG_SCCP8        0x5D    // SCCP8 Interrupt
#define DMATRG_CLC3         0x60    // CPC1 Positive Edge Interrupt
#define DMATRG_CLC4         0x61    // CPC2 Positive Edge Interrupt
#define DMATRG_SPI3_RX      0x62    // SPI3 Receiver
#define DMATRG_SPI3_TX      0x63    // SPI3 Transmitter
#define DMATRG_SI2C3        0x64    // I2C3 Device Event
#define DMATRG_MI2C3        0x65    // I2C3 Host Event
#define DMATRG_SPI3_FLT     0x66    // SPI3 Fault Interrupt
#define DMATRG_MCCP9        0x67    // MCCP9 Interrupt
#define DMATRG_UART3_RX     0x68    // UART3 Receiver
#define DMATRG_UART3_TX     0x69    // UART3 Transmitter
#define DMATRG_AN24_DONE    0x6A    // ADC Done AN24
#define DMATRG_AN25_DONE    0x6B    // ADC Done AN25
#define DMATRG_PMP_EVT      0x6C    // PMP Event
#define DMATRG_PMP_ERR      0x6D    // PMP Error Event

    
/* ********************************************************************************************* * 
 * API FUNCTION PROTOTYPES
 * ********************************************************************************************* */

extern volatile uint16_t p33c_DmaModule_Dispose(void);
extern volatile struct P33C_DMA_MODULE_s p33c_DmaModule_ConfigRead(void);
extern volatile uint16_t p33c_DmaModule_ConfigWrite(
                    volatile struct P33C_DMA_MODULE_s dmaConfig
                );


extern volatile uint16_t p33c_DmaInstance_Dispose(volatile uint16_t dmaInstance);
extern volatile struct P33C_DMA_INSTANCE_s p33c_DmaInstance_ConfigRead(volatile uint16_t dmaInstance);
extern volatile uint16_t p33c_DmaInstance_ConfigWrite(
                    volatile uint16_t dmaInstance,
                    volatile struct P33C_DMA_INSTANCE_s dmaConfig
                );

/* ********************************************************************************************* * 
 * DMA INSTANCE CONFIGURATION TEMPLATES
 * ********************************************************************************************* */
extern volatile struct P33C_DMA_MODULE_s dmaModuleConfigClear;
extern volatile struct P33C_DMA_INSTANCE_s dmaInstanceConfigClear;

#endif	/* P33C_DMA_SFR_ABSTRACTION_H */

// end of file
