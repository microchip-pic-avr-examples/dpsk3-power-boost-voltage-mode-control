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
 * File:   dev_boost_pconfig.h
 * Author: M91406
 * Comments: Peripheral configuration template header file for generic boost converter driver
 * Revision history: 
 * 1.0  initial release
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BOOST_CONVERTER_PERIPHERAL_CONFIGURATION_H
#define	BOOST_CONVERTER_PERIPHERAL_CONFIGURATION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "dev_boost_typedef.h"

/* ********************************************************************************
 * DEVICE GPIO INSTANCE CONFIGURATION
 * *******************************************************************************/

extern volatile uint16_t boostGPIO_Initialize(volatile struct BOOST_CONVERTER_s* boostInstance);
extern volatile uint16_t boostGPIO_Set(volatile struct BOOST_GPIO_INSTANCE_s* boostGPIOInstance);
extern volatile uint16_t boostGPIO_Clear(volatile struct BOOST_GPIO_INSTANCE_s* boostGPIOInstance);
extern volatile bool     boostGPIO_GetPinState(volatile struct BOOST_GPIO_INSTANCE_s* boostGPIOInstance);

/* ********************************************************************************
 * HIGH SPEED PWM MODULE CONFIGURATION
 * *******************************************************************************/
    
extern volatile uint16_t boostPWM_ModuleInitialize(volatile struct BOOST_CONVERTER_s* boostInstance);
extern volatile uint16_t boostPWM_ChannelInitialize(volatile struct BOOST_CONVERTER_s* boostInstance);
extern volatile uint16_t boostPWM_Start(volatile struct BOOST_CONVERTER_s* boostInstance);
extern volatile uint16_t boostPWM_Stop(volatile struct BOOST_CONVERTER_s* boostInstance);
extern volatile uint16_t boostPWM_Suspend(volatile struct BOOST_CONVERTER_s* boostInstance);
extern volatile uint16_t boostPWM_Resume(volatile struct BOOST_CONVERTER_s* boostInstance);

extern volatile struct P33C_PWM_MODULE_s boostPwmModuleConfig;
extern volatile struct P33C_PWM_GENERATOR_s boostPwmGeneratorConfig;

/* ********************************************************************************
 * HIGH SPEED ADC MODULE CONFIGURATION
 * *******************************************************************************/

extern volatile uint16_t boostADC_ModuleInitialize(void);
extern volatile uint16_t boostADC_ChannelInitialize(volatile BOOST_ADC_INPUT_SETTINGS_t* adcInstance);
extern volatile uint16_t boostADC_Start(void);

/* ********************************************************************************
 * HIGH ANALOG COMPARATOR INSTANCE CONFIGURATION
 * *******************************************************************************/

// (not supported yet)

#endif	/* BOOST_CONVERTER_PERIPHERAL_CONFIGURATION_H */

