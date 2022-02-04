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

#include "p33c_crc.h"

/*********************************************************************************
 * @fn      volatile uint16_t p33c_CrcModule_Dispose(void)
 * @ingroup lib-layer-pral-functions-public-crc
 * @brief   Resets all Crc Module registers to their RESET default values
 * @param   void
 * @return  0 = failure, disposing CRC module was not successful
 * @return  1 = success, disposing CRC module was successful
 * 
 * @details
 *     This function clears all CRC module registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - stop operation in IDLE mode
 *         - polynomial and seed are clear
 *         - polynomial length and data width are clear
 * 
 *********************************************************************************/

volatile uint16_t p33c_CrcModule_Dispose(void)
{
    volatile uint16_t retval=1;
    
    retval = p33c_CrcModule_ConfigWrite(crcModuleConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @fn      volatile struct P33C_CRC_MODULE_s p33c_CrcModule_ConfigRead(void)
 * @ingroup lib-layer-pral-functions-public-crc
 * @brief   Read the current configuration from the CRC module base registers
 * @param   void
 * @return  0 = failure, reading CRC module was not successful (returns NULL)
 * @return  n = success, reading CRC module was successful (returns result of type P33C_CRC_MODULE_s)
 * 
 * @details
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_CRC_MODULE_s. Users can read and 
 *     verify or modify the configuration to write it back to the CRC module  
 *     registers.
 * 
 *********************************************************************************/

volatile struct P33C_CRC_MODULE_s p33c_CrcModule_ConfigRead(void)
{
    volatile struct P33C_CRC_MODULE_s* crc;

    // Set pointer to memory address of DMA base register set
    crc = p33c_CrcModule_GetHandle();

    return(*crc);
    
}

/*********************************************************************************
 * @fn      volatile uint16_t p33c_CrcModule_ConfigWrite(volatile struct P33C_CRC_MODULE_s crcModuleConfig)
 * @ingroup lib-layer-pral-functions-public-crc
 * @brief   Writes a user-defined configuration to the CRC module base registers
 * @param   crcModuleConfig Cyclic Redundancy Check module configuration of type struct P33C_CRC_MODULE_s
 * @return  0 = failure, writing CRC module was not successful
 * @return  1 = success, writing CRC module was successful
 * 
 * @details
 *     This function writes a user-defined CRC module configuration of  
 *     type P33C_CRC_MODULE_s to the CRC module base registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 *********************************************************************************/

volatile uint16_t p33c_CrcModule_ConfigWrite(
        volatile struct P33C_CRC_MODULE_s crcModuleConfig)
{
    volatile uint16_t retval=1;
    volatile struct P33C_CRC_MODULE_s* crc;    

    // Set pointer to memory address of the CRC module base registers
    crc = p33c_CrcModule_GetHandle();
    *crc = crcModuleConfig;
    
    return(retval);
    
}


volatile uint16_t p33c_CrcModule_Initialize(void){
    
    volatile uint16_t retval=1;
    volatile struct P33C_CRC_MODULE_s* crc;    
    
    // Set pointer to memory address of the CRC module base registers
    crc = p33c_CrcModule_GetHandle();
	
	// Clear all CRC registers
	retval &= p33c_CrcModule_ConfigWrite(crcModuleConfigClear);
    
    return(retval);
}

/*********************************************************************************
 * @ingroup lib-layer-pral-properties-public-crc
 * @fn      volatile uint16_t p33c_CrcModule_Polynomial_Config(volatile uint8_t lendian, volatile uint8_t data_width,
            volatile uint8_t poly_lrngth, volatile enum CRC_POLYNOMIAL_e poly, volatile uint16_t seed)
 * @brief   Initializes a CRC module with user-defined settings
 * @param 0 = lendian     Data Word Little Endian Configuration
 * @param 1 = data_width  Configures the width of the data word
 * @param 2 = poly_length Configures the length of the polynomial
 * @param 3 = poly        XOR of Polynomial Term x^n
 * @param 4 = seed        CRC Shift value
 * @return 0 = failure, CRC configuration was not successful
 * @return 1 = success, CRC configuration was successful
 * @details
 *  User-define configuration of the CRC module when used to calculate the 
 *  8-bit or 16-bit wide Cyclic Redundancy Check in the specified protocol
 *  applications.
 ********************************************************************************/
volatile uint16_t p33c_CrcModule_Polynomial_Config(volatile uint8_t lendian, volatile uint8_t data_width,
        volatile uint8_t poly_length, volatile enum CRC_POLYNOMIAL_e poly, volatile uint16_t seed){
    
    volatile uint16_t retval=1;
    volatile struct P33C_CRC_MODULE_s* crc;    
    
    // Set pointer to memory address of the CRC module base registers
    crc = p33c_CrcModule_GetHandle();
	
	// Clear all CRC registers
	retval &= p33c_CrcModule_ConfigWrite(crcModuleConfigClear);
    
    // Initialize configuration registers for standard CRC calculation
    crc->CrcConl.bits.CRCEN = 1;            // enable CRC
    crc->CrcConl.bits.MOD = 1;              // 0=Legacy Mode, 1=Alternate Mode
    crc->CrcConl.bits.CRCISEL = 0;          // interrupt when all shifts are done
    crc->CrcConl.bits.LENDIAN = lendian;    // 1=little endian, 0=big endian

    crc->CrcConh.bits.DWIDTH = (data_width-1);      // 16-bit data width (even if 8-bit data is used)
    crc->CrcConh.bits.PLEN = (poly_length-1);         // 16-bit polynomial order
    
    // Set polynomial and seed
    crc->CrcConl.bits.CRCGO = 0;            // disable CRC calculation 
    crc->CrcXorl.value = poly;              // set polynomial
    crc->CrcXorh.value = 0;
    crc->CrcWdatl.value= seed;              // set initial value
    crc->CrcDath.value = 0;

    return(retval);
}

/*********************************************************************************
 * @ingroup lib-layer-pral-functions-public-crc
 * @fn      uint16_t p33c_CrcModule_Get_Data8_CRC16(volatile uint8_t *data, volatile uint8_t start, volatile uint8_t size)
 * @brief   Calculates a 16-bit CRC out of 8-bit data stream
 * @param   data  Pointer to 8-bit data stream (array)
 * @param   start Value of the array index at which the CRC calculation should start
 * @param   size  Number of bytes across which the CRC should be calculated
 * @return  16-bit unsigned integer result of the CRC calculation 
 * @details
 *  Calculates a 16-bit CRC out of 8-bit data stream by using a pre-configured 
 *  CRC logic configuration. 
 *
 * @note
 *  Users must set up the CRC registers before calling this function.
 *
 **********************************************************************************/

volatile uint16_t p33c_CrcModule_Get_Data8_CRC16(
       volatile uint8_t *data, volatile uint8_t start, volatile uint8_t size)
{   
    volatile uint16_t i=0;
    volatile uint16_t fifo_buf=0;
    volatile uint16_t crc_buf=0;
    volatile uint16_t data_size=0;
    volatile uint16_t is_odd=false;
    volatile uint16_t rev_poly=0;
    volatile struct P33C_CRC_MODULE_s* crc;   
    
    // Set pointer to memory address of the CRC module base registers
    crc = p33c_CrcModule_GetHandle();    
    
    crc->CrcConl.bits.CRCGO = 1;        // start CRC calculation 
    
     // Check if data length is odd or even
    is_odd = (bool) (size & 0x01); // data length is even if least significant bit = 0
                                   // data length is odd if least significant bit = 1
    if(is_odd) 
        data_size = (size & 0xFE); // capture largest even length
    else
        data_size = size; // copy data length as is
    
    // Calculate CRC16 across defined data array by always 
    // loading two bytes into 16-bit wide FIFO buffer
   
    for(i=start; i < (start + data_size); i+=2)
    {
        //merge two data bytes 
        fifo_buf = ((data[i + 1]) << 8 | data[i]);
       
        while(crc->CrcConl.bits.CRCFUL);            // wait if FIFO is full
        _CRCIF = 0;                                 // clear the interrupt flag
        crc->CrcDatl.value = fifo_buf;              // load 16-bit word data into FIFO
        while(!_CRCIF);                             // Wait until all shifts have been completed
    
    }
    
     // Read CRC result of even number of bytes
    crc->CrcConl.bits.CRCGO = 0;
    crc_buf = crc->CrcWdatl.value;

    // Processing a standard polynomial produces a reversed 
    // bit order of the result. The following macro reverses
    // the bit order of the 16-bit wide CRC result
    crc_buf = ReverseBitOrder16b(crc_buf);
        
    // If data length was odd, process last byte manually
    // in reverse order to finish up CRC result
    if(is_odd){

//        rev_poly = CRC16_PVIZ_REV_POLYNOMIAL;
        rev_poly = ReverseBitOrder16b(crc->CrcXorl.value);
        crc_buf ^= data[start + size - 1];
        
        for (i = 0; i < 8; ++i) // Process last 8-bit of last, odd data byte
        {
            if (crc_buf & 0x0001)
                crc_buf = (crc_buf >> 1) ^ rev_poly;
            else
                crc_buf = (crc_buf >> 1);
        }
    }
    
    return(crc_buf);
}

/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */

/*********************************************************************************
 * @var crcModuleConfigClear
 * @ingroup lib-layer-pral-properties-private-crc
 * @brief Default RESET configuration of CRC module 
 *
 * @details
 *  Default configuration of the CRC module SFRs with all its registers 
 *  being reset to their default state when the device comes out of RESET.
 *  The minimum and maximum addresses specifying the memory range addressable
 *  by the CRC module affects/limits all CRC channels. 
 *  (Please read the device data sheet for details)
 * 
 *  Programmers can use this template to reset a previously used
 *  CRC module when it's not used anymore or to ensure a known startup
 *  condition before writing individual configurations to its SFRs.
 * 
 ********************************************************************************/

volatile struct P33C_CRC_MODULE_s crcModuleConfigClear = {
	
    .CrcConl.value = 0x0000,
    .CrcConh.value = 0x0000,
    .CrcDath.value = 0x0000,
    .CrcDatl.value = 0x0000,
    .CrcWdath.value= 0x0000,
    .CrcWdatl.value= 0x0000,
    .CrcXorh.value = 0x0000,
    .CrcXorl.value = 0x0000,
};

/*********************************************************************************
 * @var crcModuleConfigPviz
 * @ingroup lib-layer-pral-properties-private-crc
 * @brief Default configuration for PVIZ communication protocol of CRC module 
 *
 * @details
 *  Default configuration of the CRC module when used to calculate the 
 *  16-bit wide Cyclic Redundancy Check in Power Board Visualizer protocol
 *  applications.
 ********************************************************************************/

volatile struct P33C_CRC_MODULE_s crcModuleConfigPviz = {

    // Initialize configuration registers for standard CRC calculation
    .CrcConl.bits.CRCEN = 1,            // enable CRC
    .CrcConl.bits.MOD = 1,              // 0=Legacy Mode, 1=Alternate Mode
    .CrcConl.bits.CRCISEL = 0,          // interrupt when all shifts are done
    .CrcConl.bits.LENDIAN = 1,          // 1=little endian, 0=big endian
    
    .CrcConh.bits.DWIDTH = (16-1),      // 16-bit data width (even if 8-bit data is used)
    .CrcConh.bits.PLEN = (16-1),        // 16-bit polynomial order
    
    // Set polynomial and seed
    .CrcConl.bits.CRCGO = 0,            // disable CRC calculation 
    .CrcXorl.value = CRC16_PVIZ_POLYNOMIAL, // set polynomial
    .CrcXorh.value = 0,
    .CrcWdatl.value= CRC16_PVIZ_SEED_VALUE, // set initial value
    .CrcDath.value = 0
};


// end of file
