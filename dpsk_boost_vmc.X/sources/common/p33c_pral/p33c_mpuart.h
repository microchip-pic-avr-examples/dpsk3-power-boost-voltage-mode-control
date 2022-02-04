/*
    (c) 2021 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**************************************************************************************************
 * @file:  p33c_mpuart.h
 * @brief: Generic Universal Asynchronous Receiver/Transmitter (UART) Driver Module & Generator Instances (header file)
 * @detail
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 * 
 * See Also:
 *	p33c_mpuart.c
 * 
 * ***********************************************************************************************#
 * Revision history: 
 * 06/22/20     1.0     initial release
 * 09/16/20     1.1     Simplified uart instance addressing
 *************************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef P33C_MPUART_SFR_ABSTRACTION_H
#define	P33C_MPUART_SFR_ABSTRACTION_H

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types


//#ifndef __dsPIC33C__
//   #error "peripheral driver p33c_uart.h does not support the selected device"
//#endif

    
/* GENERIC SPECIAL FUNCTION REGISTER (SFR) SETS
 * ============================================
 * 
 * Direct addressing of Special Function Registers (SFR) in user code is good 
 * enough for a specific application but makes it harder to maintain the code 
 * or migrate the code across devices and applications. 
 * 
 * Especially with complex configurations with multiple dependencies across various 
 * peripherals, migrating configurations can become very challenging to review, 
 * debug and migrate. 
 * 
 * Therefore this UART configuration example uses a 'virtual UART port' to set up 
 * the required UART configuration but provides a function allowing users to write this 
 * configuration to any UART port of choice. Hence, pre-defined configurations 
 * can be mapped on specific peripheral instance by using their index defined by the 
 * data sheet (e.g. uartInstance = 1 maps pre-defined configuration to UART1)
 * 
 * The data types used for each SFR in the P33C_UART_PORT_t data structure below,
 * are data types declared in the common C-header file of the device (e.g. <d33CK256MP506.h>). 
 * These header files are provided with the XC16 C-Compiler installation and don't have to be 
 * written nor changed manually. 
 * 
 */

// GENERIC PWM GENERATOR SPECIAL FUNCTION REGISTER SET
    
#ifndef P33C_UART_INSTANCE_s     

    struct P33C_UART_INSTANCE_s {
        union {
            struct tagU1MODEBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxMODE; // UxMODE: UARTx CONFIGURATION REGISTER
        union {
            struct tagU1MODEHBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxMODEH; // UxMODE: UARTx CONFIGURATION REGISTER HIGH
        union {
            struct tagU1STABITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxSTA; // UxSTA: UARTx STATUS REGISTER
        union {
            struct tagU1STAHBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxSTAH; // UxSTAH: UARTx STATUS REGISTER HIGH
        union {
            struct {
                uint16_t BRG : 16; // Register bit-field
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxBRG;   // UxBRG: UARTx BAUD RATE REGISTER
        union {
            struct {
                uint16_t BRGH : 4; 	// Register bit-field
                unsigned : 12; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxBRGH;   // UxBRG: UARTx BAUD RATE REGISTER HIGH
        union {
            struct {
                uint16_t RXREG : 8; // Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxRXREG;   // UxRXREG: UARTx RECEIVE BUFFER REGISTER
        unsigned : 16;   // (reserved/unused memory section)
        union {
            struct {
                uint16_t TXREG : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxTXREG;   // UxTXREG: UARTx TRANSMIT BUFFER REGISTER
        unsigned : 16;   // (reserved/unused memory section)
        union {
            struct {
                uint16_t P1 : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxP1;   // UxP1: UARTx TIMING PARAMETER 1 REGISTER
        union {
            struct {
                uint16_t P2 : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxP2;   // UxP2: UARTx TIMING PARAMETER 2 REGISTER
        union {
            struct {
                uint16_t P3 : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxP3;   // UxP3: UARTx TIMING PARAMETER 3 REGISTER
        union {
            struct {
                uint16_t P3H : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxP3H;   // UxP3H: UARTx TIMING PARAMETER 3H REGISTER
        union {
            struct {
                uint16_t TXCHK : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxTXCHK;   // UxTXCHK: UARTx TRANSMIT CHECKSUM REGISTER
        union {
            struct {
                uint16_t RXCHK : 8;	// Register bit-field
                unsigned : 8; 		// (reserved)
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        }UxRXCHK;   // UxRXCHK: UARTx RECEIVE CHECKSUM REGISTER
        union {
            struct tagU1SCCONBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxSCCON; // UxSCCON: UARTx SMART CARD CONFIGURATION REGISTER
        union {
            struct tagU1SCINTBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxSCINT; // UxSCINT: UARTx SMART CARD INTERRUPT REGISTER
        union {
            struct tagU1INTBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } UxINT; // UxINT: UARTx INTERRUPT REGISTER

    } __attribute__((packed)); // PWM GENERATOR INSTANCE SPECIAL FUNCTION REGISTER SET
    typedef struct P33C_UART_INSTANCE_s P33C_UART_PORT_t; // PWM GENERATOR INSTANCE SPECIAL FUNCTION REGISTER SET DATA TYPE
		
    // PWM generator instance Special Function Register set address offset
    #define P33C_UART_SFR_START_ADDR  (volatile uint16_t)&U1MODE
    #define P33C_UARTPORT_SFR_OFFSET  ((volatile uint16_t)&U2MODE - (volatile uint16_t)&U1MODE)

    // Determine number of available PWM generators on the selected device
    #if defined (U8MODE)
        #define P33C_UART_COUNT 8
		
    #elif defined (U7MODE)
        #define P33C_UART_COUNT   7
		
    #elif defined (U6MODE)
        #define P33C_UART_COUNT   6    
		
    #elif defined (U5MODE)
        #define P33C_UART_COUNT   5    
		
    #elif defined (U4MODE)
        #define P33C_UART_COUNT   4    
		
    #elif defined (U3MODE)
        #define P33C_UART_COUNT   3    
		
    #elif defined (U2MODE)
        #define P33C_UART_COUNT   2    
		
    #elif defined (U1MODE)
        #define P33C_UART_COUNT   1
		
    #endif

	// Public macro to derive pointer address to UART port register block
	extern volatile uint16_t* p33c_MpUartPort_Handles[];
	#define p33c_MpUartPort_GetHandle(x) (struct P33C_UART_INSTANCE_s*)p33c_MpUartPort_Handles[(x-1)]

    
#endif



/* ********************************************************************************************* * 
 * API FUNCTION PROTOTYPES
 * ********************************************************************************************* */

// UART port essential functions
extern volatile uint16_t p33c_MpUartPort_GetInstance(volatile struct P33C_UART_INSTANCE_s* uart);
extern volatile struct P33C_UART_INSTANCE_s p33c_MpUartPortConfigRead(volatile uint16_t uartInstance);
extern volatile uint16_t p33c_MpUartPort_ConfigWrite(volatile uint16_t uartInstance, 
                            volatile struct P33C_UART_INSTANCE_s uartConfig);

// Standard Generator Functions API
extern volatile uint16_t p33c_MpUartPort_Initialize(volatile uint16_t uartInstance);
extern volatile uint16_t p33c_MpUartPort_Dispose(volatile uint16_t uartInstance);

extern volatile uint16_t p33c_MpUartPort_Enable(volatile struct P33C_UART_INSTANCE_s* uart);
extern volatile uint16_t p33c_MpUartPort_Disable(volatile struct P33C_UART_INSTANCE_s* uart);


/* ********************************************************************************************* * 
 * UART INSTANCE CONFIGURATION TEMPLATES
 * ********************************************************************************************* */
extern volatile struct P33C_UART_INSTANCE_s uartConfigClear;
extern volatile struct P33C_UART_INSTANCE_s uartConfigSerialRxTx;

#endif	/* P33C_MPUART_SFR_ABSTRACTION_H */

// end of file
