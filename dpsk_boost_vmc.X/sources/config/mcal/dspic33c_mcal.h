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
 * @file   dppic33c_mcal.h
 * Author: M91406
 * @brief  DPSK3 Hardware Descriptor header file
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DSPIC33C_MCU_ABSTRACTION_DESCRIPTOR_H
#define	DSPIC33C_MCU_ABSTRACTION_DESCRIPTOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types
#include <math.h> // include standard math functions library


/**************************************************************************************************
 * @ingroup device-abstraction-settings
 * @{
 * @brief Fundamental microcontroller device settings
 * 
 * @details
 * This section is used to define device specific parameters like ADC reference and
 * resolution, main execution clock frequency and peripheral time base settings. 
 * All parameters are defined using physical quantities. 
 * 
 **************************************************************************************************/
#define EXTOSC_FREQUENCY        (float)8000000.0    ///< External Oscillator frequency in [Hz]
#define FRCC_FREQUENCY          (float)8000000.0    ///< Internal FRC Oscillator frequency in [Hz]
#define USE_EXTERNAL_CLOCK      false               ///< flag to be set by user if an external crystal whould be used

#define CPU_FREQUENCY           (float)100000000.0  ///< CPU frequency in [Hz]
#define AUX_FREQUENCY           (float)500000000.0  ///< Auxiliary PLL frequency in [Hz]

/*********************************************************************************
 * @ingroup device-abstraction-settings
 * @def     FOSC_FREQUENCY
 * @brief   Macro selecting the main clock frequency value based on user selection of oscillator type
 * @details
 *  This macro selects the main clock frequency value based on user selection 
 *  of the oscillator type. 
 **********************************************************************************/
#if (USE_EXTERNAL_CLOCK == true)
  #define FOSC_FREQUENCY        EXTOSC_FREQUENCY    ///< Main Oscillator frequency in [Hz]
#else
  #define FOSC_FREQUENCY        FRCC_FREQUENCY      ///< Main Oscillator frequency in [Hz]
#endif 

// ADC Reference and Resolution Settings    
#define ADC_REFERENCE           (float)3.300 ///< ADC reference voltage in [V]
#define ADC_RESOLUTION          (float)12.00 ///< ADC resolution in [bit]

// ADC Reference and Resolution Settings    
#define DAC_REFERENCE           (float)3.300 ///< DAC reference voltage in [V] (usually AVDD)
#define DAC_RESOLUTION          (float)12.00 ///< DAC resolution in [bit] DA02 taken from data sheet

#define DAC_MINIMUM             (float)0.165 ///< DAC minimum output voltage in [V]
#define DAC_MAXIMUM             (float)3.135 ///< DAC maximum output voltage in [V]
#define DAC_TRANSITION_TIME     (float)340.0e-9 ///< PDM DAC ramp generator transition time setting DA09 from data sheet in [s]
#define DAC_STEADY_STATE_TIME   (float)550.0e-9 ///< PDM DAC ramp generator steady-stte time setting DA10 from data sheet in [s]
#define DAC_LEADING_EDGE_PERIOD (float)120.0e-9 ///< DACx Leading-Edge Blanking in [s]

// PWM/ADC Clock Settings   
#define PWM_CLOCK_HIGH_RESOLUTION   true ///< Enables/disables the PWM generator high resolution mode of 250 ps versus 2 ns

#if (PWM_CLOCK_HIGH_RESOLUTION)
#define PWM_CLOCK_FREQUENCY     (float)4.0e+9 ///< PWM Clock Frequency in [Hz]
#else
#define PWM_CLOCK_FREQUENCY     (float)500.0e+6 ///< PWM Clock Frequency in [Hz]
#endif

#define AUX_PLL_CLOCK           (float)(1.0 / AUX_FREQUENCY)

/** @} */ // end of group device-abstraction-settings

/**
 * @ingroup device-abstraction-macros
 * @{
 * @brief Conversion macros of fundamental microcontroller device settings
 * 
 * @details
 * This section is used to convert device specific parameters like ADC reference and
 * resolution, main execution clock frequency and peripheral time base settings, declared 
 * in physical quantities, into binary (integer) numbers to be written to variables and SFRs.
 */

#define CPU_TCY             (float)(1.0 / CPU_FREQUENCY) ///< Instruction period
#define ADC_VALUE_MAX       (uint16_t)((0x0001 << (uint16_t)ADC_RESOLUTION) - 1.0) // DO NOT CHANGE
#define DAC_VALUE_MAX       (uint16_t)((0x0001 << (uint16_t)ADC_RESOLUTION) - 1.0) // DO NOT CHANGE
#define ADC_GRANULARITY     (float)(ADC_REFERENCE / (float)(ADC_VALUE_MAX + 1)) ///< ADC granularity in [V/tick]
#define DAC_GRANULARITY     (float)(DAC_REFERENCE / (float)(DAC_VALUE_MAX + 1)) ///< DAC granularity in [V/tick]
#define PWM_CLOCK_PERIOD    (float)(1.0 / PWM_CLOCK_FREQUENCY) ///< PWM Clock Period in [sec]
#define DAC_CLOCK_PERIOD    (float)(2.0 / AUX_FREQUENCY) ///< DAC Clock Period in [sec]

#define DAC_MIN             (uint16_t)(DAC_MINIMUM / DAC_GRANULARITY) ///< Integer value of minimum DAC reference  
#define DAC_MAX             (uint16_t)(DAC_MAXIMUM / DAC_GRANULARITY) ///< Integer value of maximum DAC reference 
#define DAC_TMODTIME        (uint16_t)((DAC_TRANSITION_TIME / AUX_PLL_CLOCK) / 2.0) ///< Integer value of transition time period based on most recent auxiliary clock settings
#define DAC_SSTIME          (uint16_t)((DAC_STEADY_STATE_TIME / AUX_PLL_CLOCK) / 2.0) ///< Integer value of Steady-State time period based on most recent auxiliary clock settings
#define DAC_TMCB            (uint16_t)((DAC_LEADING_EDGE_PERIOD / AUX_PLL_CLOCK) / 2.0) ///< Integer value of Steady-State time period based on most recent auxiliary clock settings

/** @} */ // end of group device-abstraction-macros

/**************************************************************************************************
 * @ingroup state-machine-settings
 * @{
 * @brief Global state-machine user-settings
 * 
 * @details
 * This section is used to set, modify, enable or disable common state machine parameters
 * and features. 
 * 
 * (Please see individual settings description for detail) 
 * 
 **************************************************************************************************/

#define MAIN_EXECUTION_PERIOD   (float)100.0e-6 ///< main state machine function call period in [sec]

/** @} */ // end of group state-machine-settings ~~~~~~~~~~

/**
 * @ingroup state-machine-macros
 * @{
 * @brief Global state-machine user-settings conversion macros
 * 
 * @details
 * Conversion macros are used to convert user settings defined in physical quantities into 
 * binary (integer) numbers, which will be written to registers and variables and/or used in 
 * calculations throughout the firmware.
 */

#define MAIN_EXEC_PER           (uint16_t)((CPU_FREQUENCY * MAIN_EXECUTION_PERIOD)-1) // DO NOT CHANGE

/** @} */ // end of group state-machine-macros ~~~~~~~~~~

/**
 * @ingroup state-machine-mcal
 * @{
 * @brief Global state-machine peripheral assignments
 * 
 * @details
 * The main task scheduler time base required a timer interrupt to separate high-priority
 * from low-priority tasks. The high priority task timer interrupt is configured here.
 */

#define _OsTimerInterrupt      _T1Interrupt ///< Interrupt serivce routine label 
#define _OSTIMER_IP            _T1IP ///< interrupt priority register
#define _OSTIMER_IE            _T1IE ///< interrupt enable bit
#define _OSTIMER_IF            _T1IF ///< interrupt flag bit
#define _OSTIMER_PRIORITY      2     ///< interrupt priority (1 ... 7, default = 2)
#define _OSTIMER_PER           PR1   ///< Timer period register
#define _OSTIMER_TMRCAP        TMR1  ///< Timer period counter register

#define _UartRxInterrupt    _U1RXInterrupt ///< Interrupt serivce routine label 
#define _UartRx_IP          _U1RXIP ///< interrupt priority register
#define _UartRx_IE          _U1RXIE ///< interrupt enable bit
#define _UartRx_IF          _U1RXIF ///< interrupt flag bit

#define _UartTxInterrupt    _U1TXInterrupt ///< Interrupt serivce routine label 
#define _UartTx_IP          _U1TXIP ///< interrupt priority register
#define _UartTx_IE          _U1TXIE ///< interrupt enable bit
#define _UartTx_IF          _U1TXIF ///< interrupt flag bit

#define _UartRxDmaInterrupt _DMA1Interrupt///< Interrupt serivce routine label 
#define _UartRxDma_IP       _DMA1IP ///< interrupt priority register
#define _UartRxDma_IE       _DMA1IE ///< interrupt enable bit
#define _UartRxDma_IF       _DMA1IF ///< interrupt flag bit

#define _UartTxDmaInterrupt _DMA0Interrupt///< Interrupt serivce routine label 
#define _UartTxDma_IP       _DMA0IP ///< interrupt priority register
#define _UartTxDma_IE       _DMA0IE ///< interrupt enable bit
#define _UartTxDma_IF       _DMA0IF ///< interrupt flag bit

#define _CRCxInterrupt      _CRCInterrupt ///< Interrupt serivce routine label 
#define _CRC_IP             _CRCIP ///< interrupt priority register
#define _CRC_IE             _CRCIE ///< interrupt enable bit
#define _CRC_IF             _CRCIF ///< interrupt flag bit
#define _CRCFIFO_FULL       _CRCFUL ///< Flag for FIFO Full bit

#define UART_RX_ISR_PRIORITY    1 ///< Voltage loop interrupt vector priority (valid settings between 0...6 with 6 being the highest priority)
#define UART_TX_ISR_PRIORITY    1 ///< Voltage loop interrupt vector priority (valid settings between 0...6 with 6 being the highest priority)

/** @} */ // end of group state-machine-mcal ~~~~~~~~~~


#endif // end of DSPIC33C_MCU_ABSTRACTION_DESCRIPTOR_H
