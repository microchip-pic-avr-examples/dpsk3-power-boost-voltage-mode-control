/*
 * File:   p33c_uart.c
 * Author: M91406
 *
 * Created on May 29, 2021, 4:23 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "uart.h"

#if defined (U8MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX, DMATRG_UART3_RX, DMATRG_UART4_RX,
    DMATRG_UART5_RX, DMATRG_UART6_RX, DMATRG_UART7_RX, DMATRG_UART8_RX    
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX, DMATRG_UART3_TX, DMATRG_UART4_TX,
    DMATRG_UART5_TX, DMATRG_UART6_TX, DMATRG_UART7_TX, DMATRG_UART8_TX    
};
#elif defined (U7MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX, DMATRG_UART3_RX, DMATRG_UART4_RX,
    DMATRG_UART5_RX, DMATRG_UART6_RX, DMATRG_UART7_RX
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX, DMATRG_UART3_TX, DMATRG_UART4_TX,
    DMATRG_UART5_TX, DMATRG_UART6_TX, DMATRG_UART7_TX
};
#elif defined (U6MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX, DMATRG_UART3_RX, DMATRG_UART4_RX,
    DMATRG_UART5_RX, DMATRG_UART6_RX
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX, DMATRG_UART3_TX, DMATRG_UART4_TX,
    DMATRG_UART5_TX, DMATRG_UART6_TX
};
#elif defined (U5MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX, DMATRG_UART3_RX, DMATRG_UART4_RX,
    DMATRG_UART5_RX 
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX, DMATRG_UART3_TX, DMATRG_UART4_TX,
    DMATRG_UART5_TX
};
#elif defined (U4MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX, DMATRG_UART3_RX, DMATRG_UART4_RX
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX, DMATRG_UART3_TX, DMATRG_UART4_TX
};
#elif defined (U3MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX, DMATRG_UART3_RX
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX, DMATRG_UART3_TX
};
#elif defined (U2MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX, DMATRG_UART2_RX
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX, DMATRG_UART2_TX
};
#elif defined (U1MODE)
volatile uint16_t UartDmaTrg_Rx [] = {
    DMATRG_UART1_RX
};
volatile uint16_t UartDmaTrg_Tx [] = {
    DMATRG_UART1_TX
};
#endif

#define UartInterfase_GetDmaTriggerRx(x) (volatile uint16_t)UartDmaTrg_Rx[x-1]
#define UartInterfase_GetDmaTriggerTx(x) (volatile uint16_t)UartDmaTrg_Tx[x-1]

#define UART_RXREG_ADDR_OFFSET  (uint16_t)(&U1RXREG - &U1MODE)
#define UART_TXREG_ADDR_OFFSET  (uint16_t)(&U1TXREG - &U1MODE)

/*********************************************************************************
 * @ingroup dev-layer-uart-properties-public
 * @var     rx_buffer
 * @brief   UART receive byte-data buffer
 * @details
 *  UART receive data buffer to which the UART interface is writing to when
 *  new data is received.
 **********************************************************************************/
//volatile uint8_t __attribute__((near)) rx_buffer[UART_RX_BUFFER_SIZE];

/*********************************************************************************
 * @ingroup dev-layer-uart-properties-public
 * @var     rx_buffer_size
 * @brief   UART receive data buffer size
 * @details
 *  Size of the UART receiver data buffer in bytes
 **********************************************************************************/
//volatile uint16_t rx_buffer_size = (sizeof(rx_buffer)/sizeof(rx_buffer[0])); 

/*********************************************************************************
 * @ingroup dev-layer-uart-properties-public
 * @var     tx_buffer
 * @brief   UART transmit byte-data buffer
 * @details
 *  UART transmit data buffer from which the UART interface is reading new 
 *  data to be transmitted
 **********************************************************************************/
//volatile uint8_t __attribute__((near)) tx_buffer[UART_TX_BUFFER_SIZE];

/*********************************************************************************
 * @ingroup dev-layer-uart-properties-public
 * @var     tx_buffer_size
 * @brief   UART transmit data buffer size
 * @details
 *  Size of the UART transmit data buffer in bytes
 **********************************************************************************/
//volatile uint16_t tx_buffer_size = (sizeof(tx_buffer)/sizeof(tx_buffer[0])); 

/*********************************************************************************
 * @ingroup lib-layer-pral-functions-public-uart
 * @fn      uint16_t p33c_UartPort_Initialize(volatile struct UART_INTERFACE_s* port)
 * @brief   Initializes a UART interface with predefined user settings
 * @param   port Pointer to UART interface object of type UART_INTERFACE_s
 * @return 0 = failure, Initializing UART interface was not successful
 * @return 1 = success, Initializing UART interface was successful
 * @details
 *  This function can be used to initialize a UART interface by handing over
 *  a predefined user-UART interface object.  
 *
 **********************************************************************************/

volatile uint16_t p33c_UartPort_Initialize(volatile struct UART_INTERFACE_s* port) {

    volatile uint16_t retval=1;
    volatile struct P33C_GPIO_INSTANCE_s* gpio;
    volatile struct P33C_DMA_MODULE_s* dmac;
    volatile struct P33C_DMA_INSTANCE_s* dma;
    volatile struct P33C_UART_INSTANCE_s* uart;
	
    // Check if object exists
    if (port == NULL)
        return(0);
    
    // Initialize device port pins assigning RX/TX
    p33c_PPS_UnlockIO();
    p33c_PPS_RemapInput(port->RxD.io.rpid, PPSIN_U1RX);
    p33c_PPS_RemapOutput(port->TxD.io.rpid, PPSOUT_U1TX);
    p33c_PPS_LockIO();

    // Set TRIS registers of RX/TX
    gpio = p33c_GpioInstance_GetHandle(port->TxD.io.port);
    if(gpio != NULL) {
        gpio->TRISx.value &= ~(0x0001 << port->TxD.io.pin);
    }
    else { return(0); }

    gpio = p33c_GpioInstance_GetHandle(port->RxD.io.port);
    if(gpio != NULL) {
        gpio->TRISx.value |= (0x0001 << port->RxD.io.pin);
    }
    else { return(0); }

    // Initialize selected UART
    uart = p33c_MpUartPort_GetHandle(port->uart);
    if (uart != NULL)
    {
        retval &= p33c_MpUartPort_ConfigWrite(port->uart, uartConfigClear);

        uart->UxSTA.bits.TXMTIE = true; // Enable TX interrupt
        uart->UxSTA.bits.RXBKIE = true; // Enable RX interrupt
        uart->UxSTAH.bits.UTXISEL = 0;  // Generate trigger when complete buffer is empty
        uart->UxSTAH.bits.URXISEL = 0;  // Generate trigger receive interrupt when there is 1 word or more in the buffer
    }
    
    // Enable DMA support
    if ((port->status.rx_use_dma) || (port->status.tx_use_dma))
    {
        // Check DMA module is used, enable if not
        dmac = p33c_DmaModule_GetHandle();
        if (dmac != NULL) {
            if (!dmac->DmaCon.bits.DMAEN) {
                p33c_DmaModule_ConfigWrite(dmaModuleConfigClear);
            }
            dmac->DmaCon.bits.DMAEN = true; // Enable DMA controller first
        }
        else { return(0); }

        // Initialize RxD DMA channel
        if (port->status.rx_use_dma) {
            
        dma = p33c_DmaInstance_GetHandle(port->RxD.dma);
            
        if (dma != NULL) {
            retval &= p33c_DmaInstance_ConfigWrite(port->RxD.dma, dmaInstanceConfigRxD);
            dma->DMASRCx.value = (uint16_t)&(uart->UxRXREG); // Set fixed source address for Receive channel
            dma->DMAINTx.bits.CHSEL = UartInterfase_GetDmaTriggerRx(port->uart); // DMA Channel Trigger Selection: UARTx Receiver
        }
        else { return(0); }
        }
        else { /* do nothing */ }

        // Initialize TxD DMA channel
        if (port->status.tx_use_dma) {
            
        dma = p33c_DmaInstance_GetHandle(port->TxD.dma);
            
        if (dma != NULL) {
            retval &= p33c_DmaInstance_ConfigWrite(port->TxD.dma, dmaInstanceConfigTxD);
            dma->DMADSTx.value = (uint16_t)&(uart->UxTXREG); // Set fixed destination address for Transmit channel
            dma->DMAINTx.bits.CHSEL = UartInterfase_GetDmaTriggerTx(port->uart); // DMA Channel Trigger Selection: UARTx Transmitter
        }
        else { return(0); }
        }
        else { /* do nothing */ }

    }

    // Set READY bit indicating successful configuration
    port->status.ready = true;
    
	return(retval);

}


/*********************************************************************************
 * @ingroup lib-layer-pral-functions-public-uart
 * @fn      volatile uint16_t p33c_MpUartPort_OpenPort(volatile uint16_t port, volatile enum UART_BAUDRATE_e baud, volatile enum UART_DATA_BITS_e data_bits, volatile enum UART_PARITY_e parity, volatile enum UART_STOP_BITS_e stop_bits, volatile enum UART_FLOWCONRTOL_e flow_control)
 * @brief  Opens the specified UART port with the specified settings in standard RS232 mode
 * @param 0 = port_no      Index of UART instance of type unsigned integer
 * @param 1 = baud         Baud Rate in signal segments per second of type unsigned integer of the UART instance Baud Rate generator
 * @param 2 = data_bits    Data bit length
 * @param 3 = parity       Data parity type
 * @param 4 = stop_bits    Data bit length
 * @param 5 = flow_control Flow control option
 * @return 0 = failure, disabling UART port was not successful
 * @return 1 = success, disabling UART port was successful
 * 
 * @details
 *  This function opens a UART interface port with the respective settings 
 *  specified by in the function parameters. No data send and receive function
 *  will be enabled by default.
 *
 **********************************************************************************/

volatile uint16_t p33c_UartPort_OpenPort(
    volatile uint16_t port_no, volatile enum UART_BAUDRATE_e baud, 
    volatile enum UART_DATA_BITS_e data_bits, volatile enum UART_PARITY_e parity, 
    volatile enum UART_STOP_BITS_e stop_bits, volatile enum UART_FLOWCONRTOL_e flow_control) 
{
    
    volatile uint16_t retval=1;
	volatile struct P33C_UART_INSTANCE_s* uart;
    
    // Check port number specified by user
    if (port_no > P33C_UART_COUNT)
        return(0);

    // Capture UART instance SFR block
    uart = p33c_MpUartPort_GetHandle(port_no);
    
    // Check system oscillator settings
    if (SystemFrequencies.fosc == 0)
        return(0);

    // Selecting the data bits
    switch(data_bits) {
        
        case UART_DATABITS_7:
            uart->UxMODE.bits.MOD = 0b0001; // Enable 7-bit UART mode
            break;
        
        case UART_DATABITS_8:
            
            // Selecting the data parity
            switch(parity) {
                
                case UART_PARITY_NONE:
                    uart->UxMODE.bits.MOD = 0b0000; // Enable 8-bit UART mode, no parity
                    break;
                case UART_PARITY_ODD:
                    uart->UxMODE.bits.MOD = 0b0010; // Enable 8-bit UART mode, odd parity
                    break;
                case UART_PARITY_EVEN:
                    uart->UxMODE.bits.MOD = 0b0011; // Enable 8-bit UART mode, even parity
                    break;
                default:
                    return(0);
            }
            
            break;
            
        default:
            return(0);
    }
    

    // Selecting the data bits
    switch(stop_bits) {
        case UART_STOPBITS_1:
            uart->UxMODEH.bits.STSEL = 0b00;    // 1 Stop bit sent, 1 checked at receive
            break;
        case UART_STOPBITS_15:
            uart->UxMODEH.bits.STSEL = 0b01;    // 1.5 Stop bits sent, 1.5 checked at receive
            break;
        case UART_STOPBITS_2:
            uart->UxMODEH.bits.STSEL = 0b10;    // 2 Stop bits sent, 2 checked at receive
            break;
        default:
            return(0);
    }
    
    // Selecting the data parity
    switch(flow_control) {
        case UART_FLOWCONRTOL_NONE:
            uart->UxMODEH.bits.FLO = 0b00;  // Flow control off
            break;
        case UART_FLOWCONRTOL_HARDWARE:
            uart->UxMODEH.bits.FLO = 0b10;  // RTS-DSR (for TX side)/CTS-DTR (for RX side) hardware flow control
            break;
        case UART_FLOWCONRTOL_XON_XOFF:
            uart->UxMODEH.bits.FLO = 0b01;  // XON/XOFF software flow control
            break;
        default:
            return(0);
    }

    // Set Baud Rate Generator Divider Mode to Fractional Divider
    uart->UxMODEH.bits.BCLKSEL = 0b00; // Baud Clock Source Selection: FOSC/2 (=FP)
    uart->UxMODEH.bits.BCLKMOD = 1; // Use fractional baud rate divider mode (highest resolution)
    
    // Calculate baud rate generator divider
    
    retval &= p33c_UartPort_SetBaudrate (port_no, baud);

    // Clear pending TX error flags
    uart->UxSTA.bits.TXCIF = 0; // Clear Transmit Collision Interrupt Flag bit
    uart->UxSTAH.bits.TXWRE = 0; // Clear TX Write Transmit Error Status bit

    uart->UxSTA.bits.OERR = 0;      // Clear Receive Buffer Overflow Interrupt Flag bit
    uart->UxSTA.bits.RXBKIF = 0;
    
    // Enable RX, TX and UART port instance
    uart->UxSTAH.bits.UTXBE  = 1;    // Reset TX FIFO
    uart->UxSTAH.bits.URXBE  = 1;    // Reset RX FIFO
    uart->UxMODE.bits.UTXEN  = true; // Enable Transmitter
    uart->UxMODE.bits.URXEN  = true; // Enable Receiver
    uart->UxMODE.bits.UARTEN = true; // Enable UART Instance
    
	return(retval);

}

/*********************************************************************************
 * @ingroup lib-layer-pral-functions-public-uart
 * @fn      volatile uint16_t p33c_UartPort_Open(volatile uint16_t port_no)
 * @brief   Opens a previously configured port
 * @param   port_no Index of UART peripheral instance of type unsigned integer
 * @return 0 = failure, Opening UART port was not successful
 * @return 1 = success, Opening UART port was successful
 * 
 * @details
 *  Opens a previously configured UART peripheral instance by enabling the UART 
 *  instance including receive and transmit channels. 
 *  No further settings will be set. When you try to open a port for the first 
 *  time, please use function 'p33c_UartPort_OpenPort(...)' specifying Baud Rate, 
 *  Data Bits, Stop Bits, Parity and Flow Control.
 *
 **********************************************************************************/

volatile uint16_t p33c_UartPort_Open(volatile uint16_t port_no) {

    volatile uint16_t retval=1;
	volatile struct P33C_UART_INSTANCE_s* uart;
    
    // Check port number specified by user
    if (port_no > P33C_UART_COUNT)
        return(0);
    
    // Capture UART instance SFR block
    uart = p33c_MpUartPort_GetHandle(port_no);
    if (uart != NULL) {
    
        // Enable RX, TX and UART instance
        uart->UxMODE.bits.UTXEN = true;
        uart->UxMODE.bits.URXEN = true;
        uart->UxMODE.bits.UARTEN = true;

        // Check if port opened successfully
        retval = (bool) (
                uart->UxMODE.bits.UTXEN &
                uart->UxMODE.bits.URXEN &
                uart->UxMODE.bits.URXEN
            );
    }
    else { retval = 0; } // return error
        
	return(retval);

}

/*********************************************************************************
 * @ingroup lib-layer-pral-functions-public-uart
 * @fn      volatile uint16_t p33c_UartPort_Close(volatile uint16_t port_no)
 * @brief   Closes a previously configured port
 * @param   port_no Index of UART peripheral instance of type unsigned integer
 * @return 0 = failure, Closing UART port was not successful
 * @return 1 = success, Closing UART port was successful
 * 
 * @details
 *  Closes a previously opened UART peripheral instance by disabling the UART 
 *  instance including receive and transmit channels. To reopen a closed port, 
 *  please use function 'p33c_UartPort_Open', if no changes to settings have to 
 *  be made, or function 'p33c_UartPort_OpenPort(...)' specifying Baud Rate, 
 *  Data Bits, Stop Bits, Parity and Flow Control.
 *
 **********************************************************************************/

volatile uint16_t p33c_UartPort_Close(volatile uint16_t port_no) {

    volatile uint16_t retval=1;
	volatile struct P33C_UART_INSTANCE_s* uart;
    
    // Check port number specified by user
    if (port_no > P33C_UART_COUNT)
        return(0);
    
    // Capture UART instance SFR block
    uart = p33c_MpUartPort_GetHandle(port_no);
    if (uart != NULL) {
    
        // Enable RX, TX and UART instance
        uart->UxMODE.bits.UTXEN = false;
        uart->UxMODE.bits.URXEN = false;
        uart->UxMODE.bits.UARTEN = false;

        // Clear status flag bits
        uart->UxSTA.value &= 0x00FF; // Clear interrupt flag bits
        uart->UxSTAH.bits.TXWRE = false; // Clear TX Write Transmit Error Status bit

        // Check if port closed successfully
        retval = (1 - (bool)(
                uart->UxMODE.bits.UTXEN &
                uart->UxMODE.bits.URXEN &
                uart->UxMODE.bits.URXEN
            ));

    }
    else { retval = 0; } // return error
    
	return(retval);

}

/*********************************************************************************
 * @fn uint16_t p33c_UartPort_SetBaudrate(volatile uinat16_t port_no, volatile uint16_t baud)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Sets the Baud Rate of the specified UART instance
 * @param  port_no Index of UART peripheral instance of type unsigned integer
 * @param  baud  Baud Rate in signal segments per second of type unsigned integer of the UART peripheral instance Baud Rate generator
 * @return 0 = failure, setting UART Baud Rate was not successful
 * @return 1 = success, setting UART Baud Rate was successful
 * 
 * @details
 *     This function writes the value specified by 'baud' to the Baud Rate 
 *     register of the specified UART peripheral instance.
 * 
 *********************************************************************************/

volatile uint16_t p33c_UartPort_SetBaudrate(
            volatile uint16_t port_no, 
            volatile uint32_t baud
    )
{
    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart;
    volatile uint32_t _brg=0;

    // Check port number specified by user
    if (port_no > P33C_UART_COUNT)
        return(0);
    
    // Capture UART instance SFR block
    uart = p33c_MpUartPort_GetHandle(port_no);
    if (uart != NULL) {
    
        // Update oscillator setting
        retval &= p33c_Osc_GetFrequencies();

        // Check which baud rate option is set
        _brg = (uint32_t)(SystemFrequencies.fp / baud);

        // IF legacy mode of baud clock generation is selected, divide baud clock setting by x,  
        // where x = 4 or 16 depending on the BRGH bit
        if (!uart->UxMODEH.bits.BCLKMOD) { 

            if (uart->UxMODE.bits.BRGH) { // If High Speed Baud Rate Clock Divider 4 is selected 
                _brg = ((_brg >> 2)-1); // divide by 4, subtract 1
            }
            else { // If Low Speed Baud Rate Clock Divider 16 is selected 
                _brg = ((_brg >> 4)-1); // divide by 16, subtract 1
            }
        }

        // Set UART port Baud Rate divisor bits
        uart->UxBRG.value = (uint16_t)(_brg & 0x0000FFFF);
        uart->UxBRGH.value = (uint16_t)((_brg & 0x00FF0000) >> 16);
    
    }
    else { retval = 0; } // return error

    
    return(retval);       
    
}

/*********************************************************************************
 * @fn volatile uint16_t p33c_UartPort_GetBaudrate(volatile uint16_t port_no)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Gets the most recent Baud Rate of the specified UART interface
 * @param  port_no Index of UART peripheral instance of type unsigned integer
 * @return Baud Rate in signal segments per second of type unsigned integer of the UART interface Baud Rate generator
 * 
 * @details
 *     This function returns the value of the Baud Rate register of the 
 *     specified UART peripheral instance in [Baud Per Second]
 * 
 *********************************************************************************/

volatile uint32_t p33c_UartPort_GetBaudrate(volatile uint16_t port_no)
{
    volatile uint32_t retval=1;
    volatile uint32_t _brg=0;
    volatile uint32_t _baud=0;
	volatile struct P33C_UART_INSTANCE_s* uart;
    
    // Check port number specified by user
    if (port_no > P33C_UART_COUNT)
        return(0);
    
    // Capture UART instance SFR block
    uart = p33c_MpUartPort_GetHandle(port_no);

    // Update oscillator setting
    retval &= p33c_Osc_GetFrequencies();

    // Read Baud Rate Register
    _brg = (uart->UxBRGH.value);
    _brg <<= 16;
    _brg |= uart->UxBRG.value;
    
    // IF legacy mode of baud clock generation is selected, divide baud clock setting by x,  
    // where x = 4 or 16 depending on the BRGH bit
    if (!uart->UxMODEH.bits.BCLKMOD) { 

        if (uart->UxMODE.bits.BRGH) { // If High Speed Baud Rate Clock Divider 4 is selected 
            _brg = ((_brg+1) << 2); // add 1, multiply by 4
        }
        else { // If Low Speed Baud Rate Clock Divider 16 is selected 
            _brg = ((_brg+1) << 4); // add 1, multiply by 16
        }
    }

    // Check which baud rate option is set
    if (_brg > 0) { // Uses fractional Baud Rate Generation
        _baud = (uint32_t)(SystemFrequencies.fp / _brg);
        retval = _baud;
    }
    else {
        retval = 0;
    }
    
    return(retval);       
    
}

/*********************************************************************************
 * volatile volatile uint16_t p33c_UartPort_WriteByte(volatile uint16_t port_no, volatile char byte)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief   Sends a single via an opened UART interface
 * @param   port_no Index of UART peripheral instance of type unsigned integer
 * @param   byte    Single data byte to be sent via specified UART interface object
 * @return 0 = failure, setting UART Baud Rate was not successful
 * @return 1 = success, setting UART Baud Rate was successful
 *  
 * @details
 *     This function sends a single byte via the specified UART peripheral 
 *     instance. 
 * 
 *********************************************************************************/
volatile uint16_t p33c_UartPort_WriteByte(volatile uint16_t port_no, volatile char byte)
{
    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart;

    // Null-pointer protection
    uart = p33c_MpUartPort_GetHandle(port_no);
    if (uart != NULL) {
        uart->UxSTAH.bits.TXWRE = 0;     // Clear transmit error
        uart->UxTXREG.bits.TXREG = byte; // write byte to buffer
    }
    else { retval = 0; }

    return(retval);
}

/*********************************************************************************
 * volatile volatile uint16_t p33c_UartPort_ReadByte(volatile uint16_t port_no, volatile char byte)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief   Reads a single byte from an opened UART interface 
 * @param   port_no Pointer to UART peripheral instance of type unsigned integer
 * @return  Single data byte read from the specified UART interface
 *  
 * @details
 *     This function reads a single byte from the specified UART interface. 
 * 
 *********************************************************************************/
volatile char p33c_UartPort_ReadByte(volatile uint16_t port_no)
{
    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart;
    
    // Null-pointer protection
    uart = p33c_MpUartPort_GetHandle(port_no);
    if (uart != NULL) {
        retval = (char)(uart->UxRXREG.bits.RXREG);
    }
    else { retval = 0; }

    return(retval);
}

/*********************************************************************************
 * @fn      uint16_t p33c_UartPort_SendBufferDma(volatile struct UART_INTERFACE_s* port)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief   Sends complete user buffer via an opened UART interface using MDA
 * @param   port        Pointer to UART interface object of type struct UART_INTERFACE_s
 * @param   start_addr  Data buffer start address of type unsigned integer
 * @param   length      Length of data buffer to be sent
 * @return  DMA buffer write to the specified UART interface
 *  
 * @details
 *     This function reads a single byte from the specified UART interface. 
 *
 **********************************************************************************/

volatile uint16_t p33c_UartPort_SendBufferDma(
        volatile struct UART_INTERFACE_s* port, 
        volatile uint16_t start_addr, 
        volatile uint16_t length
    ) 
{

    volatile uint16_t retval=1;
    volatile uint16_t timeout=0;
    volatile struct P33C_UART_INSTANCE_s* uart; 
    volatile struct P33C_DMA_INSTANCE_s* dma; 
    
    // Exit if DMA usage is disabled by user
    if (!port->status.tx_use_dma)
        return(0);
    
    
    // Capture UART and DMA object addresses
    uart = p33c_MpUartPort_GetHandle(port->uart);
    dma  = p33c_DmaInstance_GetHandle(port->TxD.dma);
    
    if ((uart != NULL) && (dma != NULL)) {

        // Set BUSY bit
        port->status.busy = true;
        
        // Wait while previous process is ongoing
        while((dma->DMACNTx.value > 0) && (timeout++<50000));   // Wait until DMA has transferred all data to destination
        if (timeout >= 50000) return(0);                        // Timeout Error
        timeout = 0;                                            // Clear timeout counter
        while((!uart->UxSTA.bits.TRMT) && (timeout++<50000));   // Wait until last TX buffer shifter activity has seized
        if (timeout >= 50000) return(0);                        // Timeout Error
        timeout = 0;                                            // Clear timeout counter
        while((!uart->UxSTAH.bits.UTXBE) && (timeout++<50000)); // Wait until UART signals empty buffer
        if (timeout >= 50000) return(0);                        // Timeout Error
        timeout = 0;                                            // Clear timeout counter
        
        // Reset TX FIFO
        uart->UxMODE.bits.UTXEN = 0;    // Disable Transmitter
        uart->UxSTAH.bits.UTXBE = 1;    // Reset TX FIFO
        uart->UxMODE.bits.UTXEN = 1;    // Enable Transmitter

        // Clear pending TX error flags
        uart->UxSTA.bits.TXCIF = 0; // Clear Transmit Collision Interrupt Flag bit
        uart->UxSTAH.bits.TXWRE = 0; // Clear TX Write Transmit Error Status bit

        dma->DMASRCx.value = start_addr; // Set DMA start address
        dma->DMACNTx.value = length; // Set DMA data set length
        dma->DMACHx.bits.CHREQ = 1; // Trigger DMA request by software
        dma->DMACHx.bits.CHEN = true; // DMA Channel Enable: enabled

        port->status.busy = false;   // clear BUSY bit
        
    }
    else { retval = 0; }
    
    return(retval);
}

/*********************************************************************************
 * @fn      uint16_t p33c_UartPort_SendBufferDma(volatile struct UART_INTERFACE_s* port)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief   Sends complete user buffer via an opened UART interface using MDA
 * @param   port        Pointer to UART interface object of type struct UART_INTERFACE_s
 * @param   start_addr  Data buffer start address of type unsigned integer
 * @param   length      Length of data buffer to be sent
 * @return  DMA buffer write to the specified UART interface
 *  
 * @details
 *     This function reads a single byte from the specified UART interface. 
 *
 **********************************************************************************/

volatile uint16_t p33c_UartPort_RecieveBufferDma(
        volatile struct UART_INTERFACE_s* port, 
        volatile uint16_t start_addr, 
        volatile uint16_t length
    ) 
{

    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart; 
    volatile struct P33C_DMA_INSTANCE_s* dma; 
    
    // Exit if DMA usage is disabled by user
    if (!port->status.rx_use_dma)
        return(0);
    
    // Capture UART and DMA object addresses
    uart = p33c_MpUartPort_GetHandle(port->uart);
    dma  = p33c_DmaInstance_GetHandle(port->RxD.dma);
    
    if ((uart != NULL) && (dma != NULL)) {

        // Set BUSY bit
        port->status.busy = true;

        // Clear pending RX error flags
        uart->UxSTA.bits.OERR = 0; // Clear Receive Buffer Overflow Interrupt Flag bit
        
        dma->DMADSTx.value = start_addr; // Set DMA start address
        dma->DMACNTx.value = length; // Set DMA data set length
        dma->DMACHx.bits.CHREQ = 0; // Trigger DMA 
        dma->DMACHx.bits.CHEN = true; // DMA Channel Enable: enabled

        port->status.busy = false;   // clear BUSY bit
        
    }
    else { retval = 0; }
    
    
    return(retval);
}

/***********************************************************************************
 * PRIVATE DMA CONFIGURATION TEMPLATES
 **********************************************************************************/

volatile struct P33C_DMA_INSTANCE_s dmaInstanceConfigRxD = {

        .DMACHx.bits.NULLW  = 0,    // No dummy write is initiated
        .DMACHx.bits.TRMODE = 0b00, // Transfer Mode Selection: One-Shot
        .DMACHx.bits.SIZE   = 1,    // Data Size Selection: Byte (8-bit)
        .DMACHx.bits.SAMODE = 0b00, // Source Address Mode Selection: DMASRCn remains unchanged after a transfer completion
        .DMACHx.bits.DAMODE = 0b01, // Destination Address Mode Selection: DMADSTn is incremented based on the SIZE bit after a transfer completion
        .DMACHx.bits.RELOAD = 0,    // Registers are not reloaded to their previous values upon the start of the next operation
        .DMACHx.bits.CHREQ  = 0,    // No DMA request is pending
    
//        .DMACHx.value  = 0x0000,    // Clear DMA Channel n Control Register
        .DMAINTx.value = 0x0000,    // Clear DMA Channel n Interrupt Control Register
        .DMASRCx.value = 0x0000,    // Clear DMA Channel n Source Address Register
        .DMADSTx.value = 0x0000,    // DMA Channel n Destination Address Register
        .DMACNTx.value = 0x0000     // DMA Channel n Count Register
    };

volatile struct P33C_DMA_INSTANCE_s dmaInstanceConfigTxD = {

        .DMACHx.bits.NULLW  = 0,    // No dummy write is initiated
        .DMACHx.bits.TRMODE = 0b00, // Transfer Mode Selection: One-Shot
        .DMACHx.bits.SIZE   = 1,    // Data Size Selection: Byte (8-bit)
        .DMACHx.bits.SAMODE = 0b01, // Source Address Mode Selection: DMASRCn is incremented based on the SIZE bit after a transfer completion
        .DMACHx.bits.DAMODE = 0b00, // Destination Address Mode Selection: DMADSTn remains unchanged after a transfer completion
        .DMACHx.bits.RELOAD = 0,    // Registers are not reloaded to their previous values upon the start of the next operation
        .DMACHx.bits.CHREQ  = 0,    // No DMA request is pending
    
        .DMAINTx.value = 0x0000,    // Clear DMA Channel n Interrupt Control Register
        .DMASRCx.value = 0x0000,    // Clear DMA Channel n Source Address Register
        .DMADSTx.value = 0x0000,    // DMA Channel n Destination Address Register
        .DMACNTx.value = 0x0000     // DMA Channel n Count Register
    };


// end of file
