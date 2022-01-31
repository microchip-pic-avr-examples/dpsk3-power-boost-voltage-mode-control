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

/* 
 * File:   p33c_uart.h
 * Author: M91406
 * Comments: device driver library providing basic UART features
 * Revision history: 
 *  1.0 initial release
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef P33C_UART_DRIVER_INTERFACE_H
#define	P33C_UART_DRIVER_INTERFACE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "p33c_mpuart.h" // include UART SFR abstraction layer driver for flexible port access
#include "p33c_osc.h"  // Include system oscillator driver for timing calculation
#include "p33c_dma.h"  // Include DMA peripheral driver for hardware data transfer
#include "p33c_gpio.h" // Include GPIO instance SFR abstraction header file
#include "p33c_pps.h"  // Inlcude peripheral pin select driver header file

/* ********************************************************************************************* * 
 * DRIVER PROPRIETARY DEFINES OF DRIVER FUNCTIONS
 * ********************************************************************************************* */

enum UART_DATA_BITS_e {
    UART_DATABITS_7 = 7,    // Asynchronous 7-bit UART
    UART_DATABITS_8 = 8,    // Asynchronous 8-bit UART
}; // UART data bit length
typedef enum UART_DATA_BITS_e UART_DATA_BITS_t; // UART data bit length data type
    
enum UART_PARITY_e {
    UART_PARITY_NONE = 0,   // No data parity mode
    UART_PARITY_ODD  = 1,   // Odd data parity mode
    UART_PARITY_EVEN = 2    // Even data parity mode
}; // UART data parity mode
typedef enum UART_PARITY_e UART_PARITY_t; // UART data parity mode data type

enum UART_STOP_BITS_e {
    UART_STOPBITS_1  = 1,   // Single stop bit mode
    UART_STOPBITS_15 = 2,   // 1 1/2 stop bit mode
    UART_STOPBITS_2  = 3    // Dual stop bit mode
}; // UART number of stop bits
typedef enum UART_STOP_BITS_e UART_STOP_BITS_t; // UART number of stop bits data type

enum UART_FLOWCONRTOL_e {
    UART_FLOWCONRTOL_NONE     = 0,  // No Flow control mechanism is used
    UART_FLOWCONRTOL_HARDWARE = 1,  // Flow control mode using RTS/CTS
    UART_FLOWCONRTOL_XON_XOFF = 2   // FLow control mode using XOn/XOff
}; // UART flow control selection
typedef enum UART_FLOWCONRTOL_e UART_FLOWCONRTOL_t; // UART flow control selection data type

enum UART_BAUDRATE_e {
    UART_BAUDRATE_75     = 75,      // Baud rate = 75 of signal units per second
    UART_BAUDRATE_150    = 150,     // Baud rate = 150 of signal units per second
    UART_BAUDRATE_300    = 300,     // Baud rate = 300 of signal units per second
    UART_BAUDRATE_600    = 600,     // Baud rate = 600 of signal units per second
    UART_BAUDRATE_1200   = 1200,    // Baud rate = 1200 of signal units per second
    UART_BAUDRATE_2400   = 2400,    // Baud rate = 2400 of signal units per second
    UART_BAUDRATE_4800   = 4800,    // Baud rate = 4800 of signal units per second
    UART_BAUDRATE_7200   = 7200,    // Baud rate = 7200 of signal units per second
    UART_BAUDRATE_9600   = 9600,    // Baud rate = 9800 of signal units per second
    UART_BAUDRATE_14400  = 14400,   // Baud rate = 14400 of signal units per second
    UART_BAUDRATE_19200  = 19200,   // Baud rate = 19200 of signal units per second
    UART_BAUDRATE_38400  = 38400,   // Baud rate = 38400 of signal units per second
    UART_BAUDRATE_56000  = 56000,   // Baud rate = 56000 of signal units per second
    UART_BAUDRATE_57600  = 57600,   // Baud rate = 57600 of signal units per second
    UART_BAUDRATE_115200 = 115200,  // Baud rate = 115200 of signal units per second
    UART_BAUDRATE_128000 = 128000   // Baud rate = 128000 of signal units per second
}; // UART baud rate selection
typedef enum UART_BAUDRATE_e UART_BAUDRATE_t; // UART baud rate selection data type

struct UART_INSTANCE_STATUS_s {
    unsigned ready : 1;   // Bit 0: READY bit indicating that interface has been configured
    unsigned busy  : 1;   // Bit 1: BUSY bit indicating that interface is occupied by internal procedure
    unsigned port_open : 1; // Bit 2:  PORT_OPEN bit indicating if UART port is open or closed
    unsigned : 1;   // Bit 3:  (reserved)
    unsigned : 1;   // Bit 4:  (reserved)
    unsigned : 1;   // Bit 5:  (reserved)
    unsigned : 1;   // Bit 6:  (reserved)
    unsigned : 1;   // Bit 7:  (reserved)

    unsigned : 1;   // Bit 8:  (reserved)
    unsigned : 1;   // Bit 9:  (reserved)
    unsigned : 1;   // Bit 10: (reserved)
    unsigned : 1;   // Bit 11: (reserved)
    unsigned : 1;   // Bit 12: (reserved)
    unsigned rx_use_dma: 1;   // Bit 13: Flag identifying if DMA support should be used for the receive channel
    unsigned tx_use_dma: 1;   // Bit 14: Flag identifying if DMA support should be used for the transmit channel
    unsigned : 1;   // Bit 15: (reserved)
};
typedef struct UART_INSTANCE_STATUS_s UART_INSTANCE_STATUS_t;

struct UART_INTERFACE_CHANNEL_s {
    volatile uint16_t dma;                  ///< DMA instance of interface
    volatile struct GPIO_PORT_PIN_s io;     ///< GPIO configuration 
};
typedef struct UART_INTERFACE_CHANNEL_s UART_INTERFACE_CHANNEL_t;

struct UART_INTERFACE_s {
    volatile struct UART_INSTANCE_STATUS_s status;  ///< Status word of the UART object
    volatile struct UART_INTERFACE_CHANNEL_s RxD;   ///< UART Receive Channel Configuration
    volatile struct UART_INTERFACE_CHANNEL_s TxD;   ///< UART Receive Channel Configuration
    volatile uint16_t uart;                         ///< UART instance of interface
}; // UART interface data object
typedef struct UART_INTERFACE_s UART_INTERFACE_t;   // UART interface data object


struct UART_DATBUF_STATUS_s 
 {
    union {
    struct{
        volatile bool buffer_empty : 1; // Bit 0: Buffer empty status bit
        volatile bool buffer_full  : 1; // Bit 1: Buffer full status bit
        volatile unsigned          : 6; // Bit 7-2: (reserved)
        volatile bool buffer_overun: 1; // Bit 8: Buffer Overrun status bit
        volatile unsigned          : 6; // Bit 14-9: (reserved)
        volatile bool msg_complete : 1; // Bit 15: Message Complete
    } __attribute__((packed)) bits;
    volatile uint16_t value;
    };
}; 
typedef struct UART_DATBUF_STATUS_s UART_DATBUF_STATUS_t;

struct UART_DATA_BUFFER_s {
        volatile struct UART_DATBUF_STATUS_s status; // Status word of user buffer
        volatile uint8_t* buffer;    // Pointer to user RECEIVE buffer
        volatile uint16_t size;      // Absolute size of buffer array in <byte>
        volatile uint16_t data_size; // size of recently loaded data array in <byte>
        volatile uint16_t pointer;   // Pointer to next free cell of buffer array
        volatile uint16_t package_size; // User-defined data package size sent at a time (Tx only, 0=single byte transmission)
    };
typedef struct UART_DATA_BUFFER_s UART_DATA_BUFFER_t;
    
struct UART_DATA_BUFFER_PROPERTY_s {
        volatile struct UART_DATA_BUFFER_s rx_buffer;     // User RECEIVE buffer
        volatile struct UART_DATA_BUFFER_s tx_buffer;     // User TRANSMIT buffer
    };
typedef struct UART_DATA_BUFFER_PROPERTY_s UART_DATA_BUFFER_PROPERTY_t;    

//#define UART_RX_BUFFER_SIZE     64
//extern volatile uint8_t __attribute__((near)) rx_buffer[];
//extern volatile uint16_t rx_buffer_size;

//#define UART_TX_BUFFER_SIZE     500
//extern volatile uint8_t __attribute__((near)) tx_buffer[];
//extern volatile uint16_t tx_buffer_size;


/* ********************************************************************************************* * 
 * API FUNCTION PROTOTYPES
 * ********************************************************************************************* */
extern volatile uint16_t p33c_UartPort_Initialize(volatile struct UART_INTERFACE_s* port);


extern volatile uint16_t p33c_UartPort_OpenPort(
    volatile uint16_t port_no, volatile enum UART_BAUDRATE_e baud, 
    volatile enum UART_DATA_BITS_e data_bits, volatile enum UART_PARITY_e parity, 
    volatile enum UART_STOP_BITS_e stop_bits, volatile enum UART_FLOWCONRTOL_e flow_control);

extern volatile uint16_t p33c_UartPort_Open(volatile uint16_t port_no);
extern volatile uint16_t p33c_UartPort_Close(volatile uint16_t port_no);

extern volatile uint16_t p33c_UartPort_SetBaudrate(
            volatile uint16_t port_no, 
            volatile uint32_t baud
    );
extern volatile uint32_t p33c_UartPort_GetBaudrate(volatile uint16_t port_no);

extern volatile char p33c_UartPort_ReadByte(volatile uint16_t port_no);
extern volatile uint16_t p33c_UartPort_WriteByte(volatile uint16_t port_no, volatile char byte);
extern volatile uint16_t p33c_UartPort_ClearDMAFlags(volatile struct UART_INTERFACE_s* port);

/***********************************************************************************
 * DMA DATA TRANSFER FUNCTIONS
 **********************************************************************************/
extern volatile uint16_t p33c_UartPort_SendBufferDma(
            volatile struct UART_INTERFACE_s* port, volatile uint16_t start_addr, 
            volatile uint16_t length
        );

extern volatile uint16_t p33c_UartPort_RecieveBufferDma(
        volatile struct UART_INTERFACE_s* port, volatile uint16_t start_addr, 
        volatile uint16_t length
    );

extern volatile struct P33C_DMA_INSTANCE_s dmaInstanceConfigRxD;
extern volatile struct P33C_DMA_INSTANCE_s dmaInstanceConfigTxD;
extern volatile struct P33C_UART_INSTANCE_s uart_instance;
#endif	/* P33C_UART_DRIVER_INTERFACE_H */

// end of file
