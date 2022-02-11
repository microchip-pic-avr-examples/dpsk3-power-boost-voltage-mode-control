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

#include "p33c_mpuart.h"

#if defined (U8MODE)
volatile uint16_t* p33c_MpUartPort_Handles[8]={
    &U1MODE, &U2MODE, &U3MODE, &U4MODE, 
    &U5MODE, &U6MODE, &U7MODE, &U8MODE 
};
#elif defined (U7MODE)
volatile uint16_t* p33c_MpUartPort_Handles[7]={
    &U1MODE, &U2MODE, &U3MODE, &U4MODE, 
    &U5MODE, &U6MODE, &U7MODE
};
#elif defined (U6MODE)
volatile uint16_t* p33c_MpUartPort_Handles[6]={
    &U1MODE, &U2MODE, &U3MODE, &U4MODE, 
    &U5MODE, &U6MODE
};
#elif defined (U5MODE)
volatile uint16_t* p33c_MpUartPort_Handles[5]={
    &U1MODE, &U2MODE, &U3MODE, &U4MODE, 
    &U5MODE
};
#elif defined (U4MODE)
volatile uint16_t* p33c_MpUartPort_Handles[4]={
    &U1MODE, &U2MODE, &U3MODE, &U4MODE
};
#elif defined (U3MODE)
volatile uint16_t* p33c_MpUartPort_Handles[3]={
    &U1MODE, &U2MODE, &U3MODE
};
#elif defined (U2MODE)
volatile uint16_t* p33c_MpUartPort_Handles[2]={
    &U1MODE, &U2MODE
};
#elif defined (U1MODE)
volatile uint16_t* p33c_MpUartPort_Handles[1]={
    &U1MODE
};
#else
#pragma message "selected device has no supported UART ports"
#endif


/*********************************************************************************
 * @fn struct P33C_UART_PORT_s p33c_MpUartPort_ConfigRead(volatile uint16_t uartInstance)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Disposes a given UART port by resetting all its registers to default
 * @param  uartInstance Instance of the UART port (e.g. 1 = UART1, 2=UART2, etc.) of type unsigned integer
 * @return Generic UART port Special Function Register set of type struct P33C_UART_PORT_s
 * 
 * @details
 *     This function copies the contents of all UART ports registers of the 
 *     specified generator instance (e.g. UART2) to a user variable of type 
 *     P33C_UART_PORT_t. This 'virtual' UART configuration can then, for  
 *     example, be analyzed and/or modified in user code and applied to another 
 *     UART port using function p33c_MpUartPort_ConfigWrite(...). 
 * 
 *********************************************************************************/

volatile struct P33C_UART_INSTANCE_s p33c_MpUartPort_ConfigRead(volatile uint16_t uartInstance)
{
    volatile struct P33C_UART_INSTANCE_s* uart;    

    // Set pointer to memory address of desired UART instance
    uart = p33c_MpUartPort_GetHandle(uartInstance);

    return(*uart);
    
}

/*********************************************************************************
 * @fn uint16_t p33c_MpUartPort_ConfigWrite(
        volatile uint16_t uartInstance, 
        volatile struct P33C_UART_PORT_s uartConfig)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief Disposes the specified UART port by resetting all its registers to default
 * @param uartInstance Instance of the UART port of type unsigned integer (e.g. 1=UART1, 2=UART2, etc.)
 * @param uartConfig   Generic UART port Special Function Register set of type struct P33C_UART_PORT_s
 * @return 0 = failure, disposing UART port was not successful
 * @return 1 = success, disposing UART port was successful
 * 
 * @details
 *     This function writes a user-defined UART port configuration of type 
 *     P33C_UART_PORT_t to the given UART port peripheral instance (e.g. UART2). 
 * 
 *********************************************************************************/

volatile uint16_t p33c_MpUartPort_ConfigWrite(
        volatile uint16_t uartInstance, 
        volatile struct P33C_UART_INSTANCE_s uartConfig
)
{
    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart;    

    // Set pointer to memory address of desired PWM instance
    uart = p33c_MpUartPort_GetHandle(uartInstance);
    *uart = uartConfig;
    
    // Verifying configuration process
    retval &= (bool)(uart->UxMODE.value == uartConfig.UxMODE.value);
    
    return(retval);
    
}

/*********************************************************************************
 * @fn uint16_t p33c_MpUartPort_Initialize(volatile uint16_t uartInstance)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Initializes a given UART port by resetting all its registers to default
 * @param  uartInstance Instance of the UART port of type unsigned integer (e.g. 1=UART1, 2=UART2, etc.)
 * @return 0 = failure, disposing UART port was not successful
 * @return 1 = success, disposing UART port was successful
 * 
 * @details
 *     This function initializes the specified UART port with default
 *     input clock settings and high resolution mode enabled. All other
 *     Special Function Registers (SFR) are reset to their RESET default 
 *     values.
 * 
 *********************************************************************************/

volatile uint16_t p33c_MpUartPort_Initialize(volatile uint16_t uartInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart;    
    
    // Set pointer to memory address of desired PWM instance
    uart = p33c_MpUartPort_GetHandle(uartInstance);

    // Disable the UART port
    retval &= p33c_MpUartPort_Disable(uart);

    // Reset all SFRs to default
    retval &= p33c_MpUartPort_ConfigWrite(uartInstance, uartConfigClear);
    
    // Verifying configuration process
    retval &= (bool)(uart->UxMODE.value == 0);

    return(retval);
}


/*********************************************************************************
 * @fn uint16_t p33c_MpUartPort_Dispose(volatile uint16_t uartInstance)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Disposes the specified UART port by resetting all its registers to default
 * @param  uartInstance Instance of the UART port of type unsigned integer (e.g. 1=UART1, 2=UART2, etc.)
 * @return 0 = failure, disposing UART port was not successful
 * @return 1 = success, disposing UART port was successful
 * 
 * @details
 *     This function disables the specified UART port and clears all
 *     its Special Function Registers (SFR) to their RESET default values.
 * 
 * ********************************************************************************/

volatile uint16_t p33c_MpUartPort_Dispose(volatile uint16_t uartInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_UART_INSTANCE_s* uart;
    
    // Set pointer to memory address of desired PWM instance
    uart = p33c_MpUartPort_GetHandle(uartInstance);
    
    // Clear all registers of uartInstance
    retval &= p33c_MpUartPort_ConfigWrite(uartInstance, uartConfigClear);
    
    // Verifying configuration process
    retval &= (bool)(uart->UxMODE.value == 0);
    
    return(retval);
}

/*********************************************************************************
 * @fn uint16_t p33c_MpUartPort_Enable(volatile struct P33C_UART_PORT_s* uart)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Enables the specified UART port
 * @param  uart Pointer to UART peripheral instance register set of type struct P33C_UART_PORT_s
 * @return 0 = failure, enabling UART port was not successful
 * @return 1 = success, enabling UART port was successful
 * 
 * @details
 *     This function enables the UART port. It is expected that RX and/or TX
 *     have been enabled previously as part of the peripheral configuration.
 *     
 * @note:
 *     if RX and TX are not enabled, this function will still enable the 
 *     specified UART instance but will return an error to indicate that 
 *     no communication will be possible.
 * 
 *********************************************************************************/

volatile uint16_t p33c_MpUartPort_Enable(volatile struct P33C_UART_INSTANCE_s* uart)
{
    volatile uint16_t retval=1;
    
    // Set UART port enable bit (expecting RX and/or TX to be set previously)
    uart->UxMODE.bits.UARTEN = true;
    retval &= (bool)((uart->UxMODE.bits.UARTEN) && 
                    ((uart->UxMODE.bits.UTXEN) || (uart->UxMODE.bits.URXEN)));
    
    return(retval);       
    
}
 
/*********************************************************************************
 * @fn uint16_t p33c_MpUartPort_Disable(volatile struct P33C_UART_PORT_s* uartInstance)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief  Disables the specified UART port 
 * @param  uartInstance Pointer to UART peripheral instance register set of type struct P33C_UART_PORT_s
 * @return 0 = failure, disabling UART port was not successful
 * @return 1 = success, disabling UART port was successful
 * 
 * @details
 *     This function disables the UART port. All communication will stop immediately.
 * 
 *********************************************************************************/

volatile uint16_t p33c_MpUartPort_Disable(volatile struct P33C_UART_INSTANCE_s* uartInstance)
{
    volatile uint16_t retval=1;
    
    // Set UART port enable bit (allowing RX and/or TX to remain set)
    uartInstance->UxMODE.bits.UARTEN = false;
    retval &= (bool)(!uartInstance->UxMODE.bits.UARTEN);
    
    return(retval);       
    
}

/*********************************************************************************
 * volatile uint16_t p33c_MpUartPort_GetInstance(volatile struct P33C_UART_PORT_s* uart)
 * @ingroup lib-layer-pral-functions-public-uart
 * @brief   Get the UART port instance index of a known PWM object pointer address
 * @param   uart  Pointer to UART port peripheral instance register set of type struct P33C_UART_PORT_s
 * @return  index of UART instance of type unsigned integer
 *  
 * @details
 * This function returns the non-zero UART instance index of the UART port of
 * the UART Special Function Register set referenced by the pointer address of 
 * function parameter uart. If the memory address does not match any available 
 * UART instance start address, this function returns '0'.
 * 
 *********************************************************************************/
volatile uint16_t p33c_MpUartPort_GetInstance(volatile struct P33C_UART_INSTANCE_s* uart)
{
    volatile uint16_t retval=1;

    // Null-pointer protection
    if (uart == NULL)
        return(0);

    // Capture Instance: set pointer to memory address of desired PWM instance
    retval = (volatile uint16_t)
        (((volatile uint16_t)&uart->UxMODE - (volatile uint16_t)P33C_UART_SFR_START_ADDR) / P33C_UARTPORT_SFR_OFFSET) + 1;
            
    if (retval > P33C_UART_COUNT)
        return(0); // UART port not member of a valid group 

    return(retval);
}

/* ********************************************************************************************* * 
 * UART PORT CONFIGURATION TEMPLATES
 * ********************************************************************************************* */

/*********************************************************************************
 * @var struct P33C_UART_PORT_s uartConfigClear
 * @ingroup lib-layer-pral-properties-private-uart
 * @brief Default RESET configuration of one UART instance SFRs
 *
 * @details
 *   Default configuration of the UART port SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   UART port when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 ********************************************************************************/

volatile struct P33C_UART_INSTANCE_s uartConfigClear = {
    
        .UxMODE.value   = 0x0000,   // UARTEN=0, USIDL=0, WAKE=0, RXBIMD=0, BRKOVR=0, UTXBRK=0, BRGH=0, ABAUD=0, UTXEN=0, URXEN=0, MOD=0
        .UxMODEH.value  = 0x0000,   // SLPEN=0, ACTIVE=0, BCLKMOD=0, BCLKSEL=0, HALFDPLX=0, RUNOVF=0, URXINV=0, STSEL=0, C0EN=0, UTXINV=0, FLO=0
        .UxSTA.value    = 0x0000,   // TXMTIE=0, PERIE=0, ABDOVE=0, CERIE=0, FERIE=0, RXBKIE=0, OERIE=0, TXCIE=0, TRMT=0, PERR=0, ABDOVF=0, CERIF=0, FERR=0, RXBKIF=0, OERR=0, TXCIF=0
        .UxSTAH.value   = 0x0000,   // UTXISEL2=0, UTXISEL1=0, UTXISEL0=0, URXISEL2=0, URXISEL1=0, URXISEL0=0, TXWRE=0, STPMD=0, UTXBE=0, UTXBF=0, RIDLE=0, XON=0, URXBE=0, URXBF=0
        .UxBRG.value    = 0x0000,   // BRG=0
        .UxBRGH.value   = 0x0000,   // BRG[19:16]=0
        .UxRXREG.value  = 0x0000,   // RXREG[7:0]=0
        .UxTXREG.value  = 0x0000,   // TXREG[7:0]=0
        .UxP1.value     = 0x0000,   // P1[7:0]=0
        .UxP2.value     = 0x0000,   // P2[7:0]=0
        .UxP3.value     = 0x0000,   // P3[7:0]=0
        .UxP3H.value    = 0x0000,   // P3[7:0]=0
        .UxTXCHK.value  = 0x0000,   // TXCHK[7:0]=0
        .UxRXCHK.value  = 0x0000,   // RXCHK[7:0]=0
        .UxSCCON.value  = 0x0000,   // TXRPT1=0, TXRPT0=0, CONV=0, T0PD=0, PRTCL=0,
        .UxSCINT.value  = 0x0000,   // RXRPTIF=0, TXRPTIF=0, BTCIF=0, WTCIF=0, GTCIF=0, RXRPTIE=0, TXRPTIE=0, BTCIE=0, WTCIE=0, GTCIE=0,
        .UxINT.value    = 0x0000    // WUIF=0, ABDIF=0, ABDIE=0,
    };

/*********************************************************************************
 * @var struct P33C_UART_PORT_s uartConfigSerialRxTx
 * @ingroup lib-layer-pral-properties-private-uart
 * @brief Default UART configuration of one UART instance for standard serial communication without hardware handshake
 *
 * @details
 *   Default configuration of a UART port SFRs with all its registers 
 *   being set for a simple, default UART operation with RX and TX channels 
 *   enabled but without hardware handshake.
 *   Programmers can use this template to quickly set a standard UART port 
 *   up for simple pure RX/TX operation without handshake. If specific, 
 *   additional features are required, these registers must be written after  
 *   this configuration template has been loaded to prevent they are 
 *   accidentally overwritten.
 * 
 * @note
 *   All configuration templates initialize SFRs with ENABLE bits being 
 *   cleared, requiring the user enables the peripheral instance separately.
 * 
 * @note
 *   The UART instance will be configured with RX and TX enabled using the 
 *   high resolution mode with fractional Baud Rate generation. The default 
 *   input clock is FOSC/2 (FP)
 * 
 ********************************************************************************/

volatile struct P33C_UART_INSTANCE_s uartConfigSerialRxTx = {
    
        .UxMODE.value   = 0x00B0,   // UARTEN=0, USIDL=0, WAKE=0, RXBIMD=0, BRKOVR=0, UTXBRK=0, BRGH=1, ABAUD=0, UTXEN=1, URXEN=1, MOD=0
        .UxMODEH.value  = 0x0880,   // SLPEN=0, ACTIVE=0, BCLKMOD=1, BCLKSEL=0, HALFDPLX=0, RUNOVF=1, URXINV=0, STSEL=0, C0EN=0, UTXINV=0, FLO=0
        .UxSTA.value    = 0x0000,   // TXMTIE=0, PERIE=0, ABDOVE=0, CERIE=0, FERIE=0, RXBKIE=0, OERIE=0, TXCIE=0, TRMT=0, PERR=0, ABDOVF=0, CERIF=0, FERR=0, RXBKIF=0, OERR=0, TXCIF=0
        .UxSTAH.value   = 0x0000,   // UTXISEL2=0, UTXISEL1=0, UTXISEL0=0, URXISEL2=0, URXISEL1=0, URXISEL0=0, TXWRE=0, STPMD=0, UTXBE=0, UTXBF=0, RIDLE=0, XON=0, URXBE=0, URXBF=0
        .UxBRG.value    = 0x0000,   // BRG=0
        .UxBRGH.value   = 0x0000,   // BRG[19:16]=0
        .UxRXREG.value  = 0x0000,   // RXREG[7:0]=0
        .UxTXREG.value  = 0x0000,   // TXREG[7:0]=0
        .UxP1.value     = 0x0000,   // P1[7:0]=0
        .UxP2.value     = 0x0000,   // P2[7:0]=0
        .UxP3.value     = 0x0000,   // P3[7:0]=0
        .UxP3H.value    = 0x0000,   // P3[7:0]=0
        .UxTXCHK.value  = 0x0000,   // TXCHK[7:0]=0
        .UxRXCHK.value  = 0x0000,   // RXCHK[7:0]=0
        .UxSCCON.value  = 0x0000,   // TXRPT1=0, TXRPT0=0, CONV=0, T0PD=0, PRTCL=0,
        .UxSCINT.value  = 0x0000,   // RXRPTIF=0, TXRPTIF=0, BTCIF=0, WTCIF=0, GTCIF=0, RXRPTIE=0, TXRPTIE=0, BTCIE=0, WTCIE=0, GTCIE=0,
        .UxINT.value    = 0x0000    // WUIF=0, ABDIF=0, ABDIE=0,
    };




// end of file
