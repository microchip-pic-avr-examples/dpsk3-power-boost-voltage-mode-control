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
 * File:   apps.h
 * Author: M91406
 * Comments: global defines of this application
 * Revision history: 
 * v1.0 initial version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APPLICATION_GLOBALS_HEADER_H
#define	APPLICATION_GLOBALS_HEADER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

// APPLICATION LAYER HEADER FILES
#include "fault_handler/app_fault_monitor.h"
#include "power_control/app_power_control.h"
#include "led/app_led.h"
#include "lcd/app_lcd.h"
#include "push_button/app_push_button.h"

/** @} */ // end of group application-tasks

/*********************************************************************************
 * @ingroup application-version-macro
 * @def     FIRMWARE_VERSION
 * @brief   32-bit wide, Integer encoded firmware version number
 * @details
 *  This macro returns the most recent firmware version as integer encoded 
 *  value of format 
 * 
 *      [MAJOR][MINOR][REVISION]
 * 
 *  with 
 *    - MAJOR    being one to three digits wide (without leading zeros)
 *    - MINOR    being two digits wide (with leading zeros)
 *    - REVISION being three digits wide (with leading zeros)
 *  
 *  Version 1.2.23 will be encoded as 1.02.023 and shown as integer value of 102023.
 *  The largest firmware version number supported is 999.99.999.
 * 
 *  Firmware modules can use this integer encoded firmware version to conditional
 *  select code sections depending on the availability of firmware version-specific
 *  features or limitations.
 **********************************************************************************/
#define FIRMWARE_VERSION (uint32_t) 103001 ///< from right to left: digits 0-2: Revision, digits 3-4: Minor, digits 5-n: Major

/*********************************************************************************
 * @ingroup application-version-macro
 * @def     FIRMWARE_VERSION_STRING
 * @brief   Clear-test string of firmware version
 * @details
 *  This macro returns the most recent firmware version as clear-text string of
 *  fixed length of 10 characters of which the first three are reserved for MAJOR.
 *  followed by a separating dot, followed by two characters for MINOR, followed 
 *  by a separating dot and finally three characters reserved for the revision 
 *  number REV.
 *  This string may be used to be displayed in terminal windows or LC displays.
 **********************************************************************************/
#define FIRMWARE_VERSION_STRING "001.03.001"   ///< Clear text version number

/*********************************************************************************
 * @ingroup application-version-macro
 * @def     FIRMWARE_TITLE
 * @brief   Clear-test string of firmware title
 * @details
 *  This macro returns the most recent firmware title as clear-text string of
 *  fixed length of 16 characters. This string is displayed on the LC display
 *  at power-up or after a CPU reset (splash-screen).
 **********************************************************************************/
#define FIRMWARE_TITLE "==== DPSK-3 ===="

/*********************************************************************************
 * @ingroup application-version-macro
 * @def     FIRMWARE_NAME
 * @brief   Clear-test string of firmware name
 * @details
 *  This macro returns the most recent firmware name as clear-text string of
 *  fixed length of 16 characters. This string is displayed on the LC display
 *  at power-up or after a CPU reset (splash-screen).
 **********************************************************************************/
#define FIRMWARE_NAME  "BOOST VMC EXAMPLE"

#endif	/* APPLICATION_GLOBALS_HEADER_H */

