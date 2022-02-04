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
 * @file p33c_gpio.h
 * @see  p33c_gpio.c
 * @brief Generic Digital Signal Processor Driver Module (header file)
 * @details
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 * 
 *************************************************************************************************/
/* Revision history: 
 * 12/10/20     1.0     initial release
 *************************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef P33C_GPIO_SFR_ABSTRACTION_H
#define	P33C_GPIO_SFR_ABSTRACTION_H

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

// GENERIC GPIO INSTANCE SPECIAL FUNCTION REGISTER SET
// DO NOT REORDER ELEMENTS AS THEY MAP ONTO DEVICE REGISTER MEMORY !!!
#ifndef P33C_GPIO_INSTANCE_s

    struct ANSELx_s {
      uint16_t ANSELx0:1;     // Bit 0:  Device Port Analog Select Register bit 
      uint16_t ANSELx1:1;     // Bit 1:  Device Port Analog Select Register bit 
      uint16_t ANSELx2:1;     // Bit 2:  Device Port Analog Select Register bit 
      uint16_t ANSELx3:1;     // Bit 3:  Device Port Analog Select Register bit 
      uint16_t ANSELx4:1;     // Bit 4:  Device Port Analog Select Register bit 
      uint16_t ANSELx5:1;     // Bit 5:  Device Port Analog Select Register bit 
      uint16_t ANSELx6:1;     // Bit 6:  Device Port Analog Select Register bit 
      uint16_t ANSELx7:1;     // Bit 7:  Device Port Analog Select Register bit 
      uint16_t ANSELx8:1;     // Bit 8:  Device Port Analog Select Register bit 
      uint16_t ANSELx9:1;     // Bit 9:  Device Port Analog Select Register bit 
      uint16_t ANSELx10:1;    // Bit 10: Device Port Analog Select Register bit 
      uint16_t ANSELx11:1;    // Bit 11: Device Port Analog Select Register bit 
      uint16_t ANSELx12:1;    // Bit 12: Device Port Analog Select Register bit 
      uint16_t ANSELx13:1;    // Bit 13: Device Port Analog Select Register bit 
      uint16_t ANSELx14:1;    // Bit 14: Device Port Analog Select Register bit 
      uint16_t ANSELx15:1;    // Bit 15: Device Port Analog Select Register bit 
    }__attribute__((packed)); //ANSELx: ANALOG SELECT FOR PORTx REGISTER 
    typedef struct ANSELx_s ANSELx_t; //ANSELx: ANALOG SELECT FOR PORTx REGISTER DATA TYPE
    
    struct TRISx_s {
      uint16_t TRISx0:1;     // Bit 0:  Device Port Output Enable Register bit 
      uint16_t TRISx1:1;     // Bit 1:  Device Port Output Enable Register bit 
      uint16_t TRISx2:1;     // Bit 2:  Device Port Output Enable Register bit 
      uint16_t TRISx3:1;     // Bit 3:  Device Port Output Enable Register bit 
      uint16_t TRISx4:1;     // Bit 4:  Device Port Output Enable Register bit 
      uint16_t TRISx5:1;     // Bit 5:  Device Port Output Enable Register bit 
      uint16_t TRISx6:1;     // Bit 6:  Device Port Output Enable Register bit 
      uint16_t TRISx7:1;     // Bit 7:  Device Port Output Enable Register bit 
      uint16_t TRISx8:1;     // Bit 8:  Device Port Output Enable Register bit 
      uint16_t TRISx9:1;     // Bit 9:  Device Port Output Enable Register bit 
      uint16_t TRISx10:1;    // Bit 10: Device Port Output Enable Register bit 
      uint16_t TRISx11:1;    // Bit 11: Device Port Output Enable Register bit 
      uint16_t TRISx12:1;    // Bit 12: Device Port Output Enable Register bit 
      uint16_t TRISx13:1;    // Bit 13: Device Port Output Enable Register bit 
      uint16_t TRISx14:1;    // Bit 14: Device Port Output Enable Register bit 
      uint16_t TRISx15:1;    // Bit 15: Device Port Output Enable Register bit 
    }__attribute__((packed)); //TRISx: OUTPUT ENABLE FOR PORTx REGISTER 
    typedef struct TRISx_s TRISx_t; //TRISx: OUTPUT ENABLE FOR PORTx REGISTER DATA TYPE
    
    struct PORTx_s {
      uint16_t PORTx0:1;     // Bit 0:  Device Port Data Input Value Register bit 
      uint16_t PORTx1:1;     // Bit 1:  Device Port Data Input Value Register bit 
      uint16_t PORTx2:1;     // Bit 2:  Device Port Data Input Value Register bit 
      uint16_t PORTx3:1;     // Bit 3:  Device Port Data Input Value Register bit 
      uint16_t PORTx4:1;     // Bit 4:  Device Port Data Input Value Register bit 
      uint16_t PORTx5:1;     // Bit 5:  Device Port Data Input Value Register bit 
      uint16_t PORTx6:1;     // Bit 6:  Device Port Data Input Value Register bit 
      uint16_t PORTx7:1;     // Bit 7:  Device Port Data Input Value Register bit 
      uint16_t PORTx8:1;     // Bit 8:  Device Port Data Input Value Register bit 
      uint16_t PORTx9:1;     // Bit 9:  Device Port Data Input Value Register bit 
      uint16_t PORTx10:1;    // Bit 10: Device Port Data Input Value Register bit 
      uint16_t PORTx11:1;    // Bit 11: Device Port Data Input Value Register bit 
      uint16_t PORTx12:1;    // Bit 12: Device Port Data Input Value Register bit 
      uint16_t PORTx13:1;    // Bit 13: Device Port Data Input Value Register bit 
      uint16_t PORTx14:1;    // Bit 14: Device Port Data Input Value Register bit 
      uint16_t PORTx15:1;    // Bit 15: Device Port Data Input Value Register bit 
    }__attribute__((packed)); // PORTx: INPUT DATA FOR PORTx REGISTER
    typedef struct PORTx_s PORTx_t; // PORTx: INPUT DATA FOR PORTx REGISTER DATA TYPE

    struct LATx_s {
      uint16_t LATx0:1;     // Bit 0:  Device Port Latch Register bit 
      uint16_t LATx1:1;     // Bit 1:  Device Port Latch Register bit 
      uint16_t LATx2:1;     // Bit 2:  Device Port Latch Register bit 
      uint16_t LATx3:1;     // Bit 3:  Device Port Latch Register bit 
      uint16_t LATx4:1;     // Bit 4:  Device Port Latch Register bit 
      uint16_t LATx5:1;     // Bit 5:  Device Port Latch Register bit 
      uint16_t LATx6:1;     // Bit 6:  Device Port Latch Register bit 
      uint16_t LATx7:1;     // Bit 7:  Device Port Latch Register bit 
      uint16_t LATx8:1;     // Bit 8:  Device Port Latch Register bit 
      uint16_t LATx9:1;     // Bit 9:  Device Port Latch Register bit 
      uint16_t LATx10:1;    // Bit 10: Device Port Latch Register bit 
      uint16_t LATx11:1;    // Bit 11: Device Port Latch Register bit 
      uint16_t LATx12:1;    // Bit 12: Device Port Latch Register bit 
      uint16_t LATx13:1;    // Bit 13: Device Port Latch Register bit 
      uint16_t LATx14:1;    // Bit 14: Device Port Latch Register bit 
      uint16_t LATx15:1;    // Bit 15: Device Port Latch Register bit 
    }__attribute__((packed)); // LATx: OUTPUT PORT LATCH DATA FOR PORTx REGISTER
    typedef struct LATx_s LATx_t; // LATx: OUTPUT PORT LATCH DATA FOR PORTx REGISTER DATA TYPE

    struct ODCx_s {
      uint16_t ODCx0:1;     // Bit 0:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx1:1;     // Bit 1:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx2:1;     // Bit 2:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx3:1;     // Bit 3:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx4:1;     // Bit 4:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx5:1;     // Bit 5:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx6:1;     // Bit 6:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx7:1;     // Bit 7:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx8:1;     // Bit 8:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx9:1;     // Bit 9:  Device Port Open-Drain Enable Register bit 
      uint16_t ODCx10:1;    // Bit 10: Device Port Open-Drain Enable Register bit 
      uint16_t ODCx11:1;    // Bit 11: Device Port Open-Drain Enable Register bit 
      uint16_t ODCx12:1;    // Bit 12: Device Port Open-Drain Enable Register bit 
      uint16_t ODCx13:1;    // Bit 13: Device Port Open-Drain Enable Register bit 
      uint16_t ODCx14:1;    // Bit 14: Device Port Open-Drain Enable Register bit 
      uint16_t ODCx15:1;    // Bit 15: Device Port Open-Drain Enable Register bit 
    }__attribute__((packed)); // ODCx: OPEN-DRAIN ENABLE FOR PORTx REGISTER
    typedef struct ODCx_s ODCx_t; // ODCx: OPEN-DRAIN ENABLE FOR PORTx REGISTER DATA TYPE

    struct CNPUx_s {
      uint16_t CNPUx0:1;     // Bit 0:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx1:1;     // Bit 1:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx2:1;     // Bit 2:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx3:1;     // Bit 3:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx4:1;     // Bit 4:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx5:1;     // Bit 5:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx6:1;     // Bit 6:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx7:1;     // Bit 7:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx8:1;     // Bit 8:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx9:1;     // Bit 9:  Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx10:1;    // Bit 10: Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx11:1;    // Bit 11: Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx12:1;    // Bit 12: Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx13:1;    // Bit 13: Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx14:1;    // Bit 14: Device Port Change Notification Pull-Up Enable Register bit 
      uint16_t CNPUx15:1;    // Bit 15: Device Port Change Notification Pull-Up Enable Register bit 
    }__attribute__((packed)); // CNPUx: CHANGE NOTIFICATION PULL-UP ENABLE FOR PORTx REGISTER
    typedef struct CNPUx_s CNPUx_t; // CNPUx: CHANGE NOTIFICATION PULL-UP ENABLE FOR PORTx REGISTER DATA TYPE

    struct CNPDx_s {
      uint16_t CNPDx0:1;     // Bit 0:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx1:1;     // Bit 1:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx2:1;     // Bit 2:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx3:1;     // Bit 3:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx4:1;     // Bit 4:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx5:1;     // Bit 5:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx6:1;     // Bit 6:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx7:1;     // Bit 7:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx8:1;     // Bit 8:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx9:1;     // Bit 9:  Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx10:1;    // Bit 10: Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx11:1;    // Bit 11: Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx12:1;    // Bit 12: Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx13:1;    // Bit 13: Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx14:1;    // Bit 14: Device Port Change Notification Pull-Down Enable Register bit 
      uint16_t CNPDx15:1;    // Bit 15: Device Port Change Notification Pull-Down Enable Register bit 
    }__attribute__((packed)); // CNPDx: CHANGE NOTIFICATION PULL-DOWN ENABLE FOR PORTx REGISTER
    typedef struct CNPDx_s CNPDx_t; // CNPDx: CHANGE NOTIFICATION PULL-DOWN ENABLE FOR PORTx REGISTER DATA TYPE

    struct CNEN0x_s {
      uint16_t CNEN0x0:1;     // Bit 0:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x1:1;     // Bit 1:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x2:1;     // Bit 2:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x3:1;     // Bit 3:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x4:1;     // Bit 4:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x5:1;     // Bit 5:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x6:1;     // Bit 6:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x7:1;     // Bit 7:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x8:1;     // Bit 8:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x9:1;     // Bit 9:  Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x10:1;    // Bit 10: Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x11:1;    // Bit 11: Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x12:1;    // Bit 12: Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x13:1;    // Bit 13: Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x14:1;    // Bit 14: Device Port Change Notification Interrupt Enable Register bit 
      uint16_t CNEN0x15:1;    // Bit 15: Device Port Change Notification Interrupt Enable Register bit 
    }__attribute__((packed)); // CNEN0x: CHANGE NOTIFICATION INTERRUPT ENABLE FOR PORTx REGISTER
    typedef struct CNEN0x_s CNCEN0x_t; // CNEN0x: CHANGE NOTIFICATION INTERRUPT ENABLE FOR PORTx REGISTER DATA TYPE

    struct CNSTATx_s {
      uint16_t CNSTATx0:1;     // Bit 0:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx1:1;     // Bit 1:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx2:1;     // Bit 2:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx3:1;     // Bit 3:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx4:1;     // Bit 4:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx5:1;     // Bit 5:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx6:1;     // Bit 6:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx7:1;     // Bit 7:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx8:1;     // Bit 8:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx9:1;     // Bit 9:  Device Port Change Notification Status Register bit 
      uint16_t CNSTATx10:1;    // Bit 10: Device Port Change Notification Status Register bit 
      uint16_t CNSTATx11:1;    // Bit 11: Device Port Change Notification Status Register bit 
      uint16_t CNSTATx12:1;    // Bit 12: Device Port Change Notification Status Register bit 
      uint16_t CNSTATx13:1;    // Bit 13: Device Port Change Notification Status Register bit 
      uint16_t CNSTATx14:1;    // Bit 14: Device Port Change Notification Status Register bit 
      uint16_t CNSTATx15:1;    // Bit 15: Device Port Change Notification Status Register bit 
    }__attribute__((packed)); // CNSTATx: CHANGE NOTIFICATION STATUS FOR PORTx REGISTER
    typedef struct CNSTATx_s CNSTATx_t; // CNSTATx: CHANGE NOTIFICATION STATUS FOR PORTx REGISTER DATA TYPE

    struct CNEN1x_s {
      uint16_t CNEN1x0:1;     // Bit 0:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x1:1;     // Bit 1:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x2:1;     // Bit 2:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x3:1;     // Bit 3:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x4:1;     // Bit 4:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x5:1;     // Bit 5:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x6:1;     // Bit 6:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x7:1;     // Bit 7:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x8:1;     // Bit 8:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x9:1;     // Bit 9:  Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x10:1;    // Bit 10: Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x11:1;    // Bit 11: Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x12:1;    // Bit 12: Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x13:1;    // Bit 13: Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x14:1;    // Bit 14: Device Port Change Notification Edge Select Register bit 
      uint16_t CNEN1x15:1;    // Bit 15: Device Port Change Notification Edge Select Register bit 
    }__attribute__((packed)); // CNEN1x: CHANGE NOTIFICATION EDGE SELECT FOR PORTx REGISTER
    typedef struct CNEN1x_s CNCEN1x_t; // CNEN1x: CHANGE NOTIFICATION EDGE SELECT FOR PORTx REGISTER DATA TYPE

    struct CNFx_s {
      uint16_t CNFx0:1;     // Bit 0:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx1:1;     // Bit 1:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx2:1;     // Bit 2:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx3:1;     // Bit 3:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx4:1;     // Bit 4:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx5:1;     // Bit 5:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx6:1;     // Bit 6:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx7:1;     // Bit 7:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx8:1;     // Bit 8:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx9:1;     // Bit 9:  Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx10:1;    // Bit 10: Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx11:1;    // Bit 11: Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx12:1;    // Bit 12: Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx13:1;    // Bit 13: Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx14:1;    // Bit 14: Device Port Change Notification Interrupt Flag Register bit 
      uint16_t CNFx15:1;    // Bit 15: Device Port Change Notification Interrupt Flag Register bit 
    }__attribute__((packed)); // CNFx: CHANGE NOTIFICATION INTERRUPT FLAG FOR PORTx REGISTER
    typedef struct CNFx_s CNCFx_t; // CNFx: CHANGE NOTIFICATION INTERRUPT FLAG FOR PORTx REGISTER DATA TYPE

    struct P33C_GPIO_INSTANCE_s {
        union {   
            volatile struct ANSELx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }ANSELx; // ANSELx: ANALOG SELECT FOR PORTx REGISTER
        union {   
            volatile struct TRISx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }TRISx; // TRISx: OUTPUT ENABLE FOR PORTx REGISTER
        union {   
            volatile struct PORTx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }PORTx; // PORTx: INPUT DATA FOR PORTx REGISTER
        union {   
            volatile struct LATx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }LATx; // LATx: OUTPUT DATA FOR PORTx REGISTER
        union {   
            volatile struct ODCx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }ODCx; // ODCx: OPEN-DRAIN ENABLE FOR PORTx REGISTER
        union {   
            volatile struct CNPUx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNPUx; // CNPUx: CHANGE NOTIFICATION PULL-UP ENABLE FOR PORTx REGISTER
        union {   
            volatile struct CNPDx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNPDx; // CNPDx: CHANGE NOTIFICATION PULL-DOWN ENABLE FOR PORTx REGISTER
        union {   
            volatile struct tagCNCONABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNCONx; // CNCONx: CHANGE NOTIFICATION CONTROL FOR PORTx REGISTER
        union {   
            volatile struct CNEN0x_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNEN0x; // CNEN0x: CHANGE NOTIFICATION INTERRUPT ENABLE FOR PORTx REGISTER
        union {   
            volatile struct CNSTATx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNSTATx; // CNSTATx: CHANGE NOTIFICATION STATUS FOR PORTx REGISTER
        union {   
            volatile struct CNEN1x_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNEN1x; // CNEN1x: CHANGE NOTIFICATION EDGE SELECT FOR PORTx REGISTER
        union {   
            volatile struct CNFx_s bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNFx; // CNFx: CHANGE NOTIFICATION INTERRUPT FLAG FOR PORTx REGISTER
    } __attribute__((packed)); // GPIO REGISTER SET
	typedef struct P33C_GPIO_INSTANCE_s P33C_GPIO_INSTANCE_t;
	
    #define P33C_GPIO_SFR_OFFSET  ((volatile uint16_t)&ANSELB - (volatile uint16_t)&ANSELA)

    #if defined (TRISE)
        #define P33C_PORT_COUNT 5    
		
    #elif defined (TRISD)
        #define P33C_PORT_COUNT 4    
		
    #elif defined (TRISC)
        #define P33C_PORT_COUNT 3    
		
    #elif defined (TRISB)
        #define P33C_PORT_COUNT 2    
		
    #elif defined (TRISA)
        #define P33C_PORT_COUNT 1
		
    #endif

/*********************************************************************************
 * @fn struct P33C_GPIO_INSTANCE_s* p33c_GpioInstance_GetHandle(volatile uint16_t gpioInstance)
 * @ingroup lib-layer-pral-functions-public-gpio
 * @brief Gets pointer to GPIO Instance SFR set
 * @param gpioInstance Index of the selected GPIO Instance (1=Port A, 2=Port B, etc.)
 * @return Pointer to GPIO instance object of type struct P33C_GPIO_INSTANCE_s of the selected GPIO instance
 *  
 * @details
 *    This function returns the pointer to a GPIO instance register set in 
 *    Special Function Register memory space. This pointer can be used to directly
 *    write to/read from the Special Function Registers of a given peripheral
 *    instance.
 * 
 *********************************************************************************/

	extern volatile uint16_t* p33c_GpioInstance_Handles[];
	#define p33c_GpioInstance_GetHandle(x) (struct P33C_GPIO_INSTANCE_s*)p33c_GpioInstance_Handles[(x)]
    
#endif

/* ********************************************************************************************* * 
 * DEVICE PIN DECLARATIONS FOR INDIRECT PORT PIN ADDRESSING
 * ********************************************************************************************* */
    
struct GPIO_PORT_PIN_s {
    volatile uint16_t port; // Integer index of device port 
    volatile uint16_t pin;  // integer index of device pin within port group 
    volatile uint16_t rpid; // Remappable Pin ID
}; // generic device port ID structure
typedef struct GPIO_PORT_PIN_s GPIO_PORT_PIN_t; // Generic device port ID structure data type

// Device Pin Declarations
    
// Port A
#if defined (_TRISA0)
    extern volatile struct GPIO_PORT_PIN_s PIN_RA0;
    #define PIN_RA0 PIN_RA0
#endif
#if defined (_TRISA1)
    extern volatile struct GPIO_PORT_PIN_s PIN_RA1;
    #define PIN_RA1 PIN_RA1
#endif
#if defined (_TRISA2)
    extern volatile struct GPIO_PORT_PIN_s PIN_RA2;
    #define PIN_RA2 PIN_RA2
#endif
#if defined (_TRISA3)
    extern volatile struct GPIO_PORT_PIN_s PIN_RA3;
    #define PIN_RA3 PIN_RA3
#endif
#if defined (_TRISA4)
    extern volatile struct GPIO_PORT_PIN_s PIN_RA4;
    #define PIN_RA4 PIN_RA4
#endif

    
// Port B
#if defined (_TRISB0)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB0;
    #define PIN_RB0  PIN_RB0
#endif
#if defined (_TRISB1)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB1;
    #define PIN_RB1  PIN_RB1
#endif
#if defined (_TRISB2)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB2;
    #define PIN_RB2  PIN_RB2
#endif
#if defined (_TRISB3)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB3;
    #define PIN_RB3  PIN_RB3
#endif
#if defined (_TRISB4)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB4;
    #define PIN_RB4  PIN_RB4
#endif
#if defined (_TRISB5)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB5; 
    #define PIN_RB5  PIN_RB5
#endif
#if defined (_TRISB6)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB6; 
    #define PIN_RB6  PIN_RB6
#endif
#if defined (_TRISB7)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB7; 
    #define PIN_RB7  PIN_RB7
#endif
#if defined (_TRISB8)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB8; 
    #define PIN_RB8  PIN_RB8
#endif
#if defined (_TRISB9)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB9; 
    #define PIN_RB9  PIN_RB9
#endif
#if defined (_TRISB10)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB10;
    #define PIN_RB10 PIN_RB10
#endif
#if defined (_TRISB11)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB11;
    #define PIN_RB11 PIN_RB11
#endif
#if defined (_TRISB12)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB12;
    #define PIN_RB12 PIN_RB12
#endif
#if defined (_TRISB13)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB13;
    #define PIN_RB13 PIN_RB13
#endif
#if defined (_TRISB14)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB14;
    #define PIN_RB14 PIN_RB14
#endif
#if defined (_TRISB15)
    extern volatile struct GPIO_PORT_PIN_s PIN_RB15;
    #define PIN_RB15 PIN_RB15
#endif
    
// Port C
#if defined (_TRISC0)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC0;
    #define PIN_RC0  PIN_RC0
#endif
#if defined (_TRISC1)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC1;
    #define PIN_RC1  PIN_RC1
#endif
#if defined (_TRISC2)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC2;
    #define PIN_RC2  PIN_RC2
#endif
#if defined (_TRISC3)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC3;
    #define PIN_RC3  PIN_RC3
#endif
#if defined (_TRISC4)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC4;
    #define PIN_RC4  PIN_RC4
#endif
#if defined (_TRISC5)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC5; 
    #define PIN_RC5  PIN_RC5
#endif
#if defined (_TRISC6)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC6; 
    #define PIN_RC6  PIN_RC6
#endif
#if defined (_TRISC7)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC7; 
    #define PIN_RC7  PIN_RC7
#endif
#if defined (_TRISC8)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC8; 
    #define PIN_RC8  PIN_RC8
#endif
#if defined (_TRISC9)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC9; 
    #define PIN_RC9  PIN_RC9
#endif
#if defined (_TRISC10)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC10;
    #define PIN_RC10 PIN_RC10
#endif
#if defined (_TRISC11)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC11;
    #define PIN_RC11 PIN_RC11
#endif
#if defined (_TRISC12)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC12;
    #define PIN_RC12 PIN_RC12
#endif
#if defined (_TRISC13)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC13;
    #define PIN_RC13 PIN_RC13
#endif
#if defined (_TRISC14)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC14;
    #define PIN_RC14 PIN_RC14
#endif
#if defined (_TRISC15)
    extern volatile struct GPIO_PORT_PIN_s PIN_RC15;
    #define PIN_RC15 PIN_RC15
#endif

// Port D
#if defined (_TRISD0)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD0;
    #define PIN_RD0  PIN_RD0
#endif
#if defined (_TRISD1)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD1;
    #define PIN_RD1  PIN_RD1
#endif
#if defined (_TRISD2)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD2;
    #define PIN_RD2  PIN_RD2
#endif
#if defined (_TRISD3)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD3;
    #define PIN_RD3  PIN_RD3
#endif
#if defined (_TRISD4)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD4;
    #define PIN_RD4  PIN_RD4
#endif
#if defined (_TRISD5)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD5; 
    #define PIN_RD5  PIN_RD5
#endif
#if defined (_TRISD6)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD6; 
    #define PIN_RD6  PIN_RD6
#endif
#if defined (_TRISD7)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD7; 
    #define PIN_RD7  PIN_RD7
#endif
#if defined (_TRISD8)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD8; 
    #define PIN_RD8  PIN_RD8
#endif
#if defined (_TRISD9)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD9; 
    #define PIN_RD9  PIN_RD9
#endif
#if defined (_TRISD10)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD10;
    #define PIN_RD10 PIN_RD10
#endif
#if defined (_TRISD11)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD11;
    #define PIN_RD11 PIN_RD11
#endif
#if defined (_TRISD12)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD12;
    #define PIN_RD12 PIN_RD12
#endif
#if defined (_TRISD13)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD13;
    #define PIN_RD13 PIN_RD13
#endif
#if defined (_TRISD14)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD14;
    #define PIN_RD14 PIN_RD14
#endif
#if defined (_TRISD15)
    extern volatile struct GPIO_PORT_PIN_s PIN_RD15;
    #define PIN_RD15 PIN_RD15
#endif

// Port E
#if defined (_TRISE0)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE0;
    #define PIN_RE0  PIN_RE0
#endif
#if defined (_TRISE1)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE1;
    #define PIN_RE1  PIN_RE1
#endif
#if defined (_TRISE2)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE2;
    #define PIN_RE2  PIN_RE2
#endif
#if defined (_TRISE3)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE3;
    #define PIN_RE3  PIN_RE3
#endif
#if defined (_TRISE4)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE4;
    #define PIN_RE4  PIN_RE4
#endif
#if defined (_TRISE5)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE5; 
    #define PIN_RE5  PIN_RE5
#endif
#if defined (_TRISE6)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE6; 
    #define PIN_RE6  PIN_RE6
#endif
#if defined (_TRISE7)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE7; 
    #define PIN_RE7  PIN_RE7
#endif
#if defined (_TRISE8)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE8; 
    #define PIN_RE8  PIN_RE8
#endif
#if defined (_TRISE9)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE9; 
    #define PIN_RE9  PIN_RE9
#endif
#if defined (_TRISE10)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE10;
    #define PIN_RE10 PIN_RE10
#endif
#if defined (_TRISE11)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE11;
    #define PIN_RE11 PIN_RE11
#endif
#if defined (_TRISE12)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE12;
    #define PIN_RE12 PIN_RE12
#endif
#if defined (_TRISE13)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE13;
    #define PIN_RE13 PIN_RE13
#endif
#if defined (_TRISE14)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE14;
    #define PIN_RE14 PIN_RE14
#endif
#if defined (_TRISE15)
    extern volatile struct GPIO_PORT_PIN_s PIN_RE15;
    #define PIN_RE15 PIN_RE15
#endif
    
/* ********************************************************************************************* * 
 * API FUNCTION PROTOTYPES
 * ********************************************************************************************* */
    
extern volatile uint16_t p33c_GpioInstance_Dispose(
            volatile uint16_t gpioInstance
        );    
    
extern volatile struct P33C_GPIO_INSTANCE_s p33c_GpioInstance_ConfigRead(
            volatile uint16_t gpioInstance
        );

extern volatile uint16_t p33c_GpioInstance_ConfigWrite(
            volatile uint16_t gpioInstance, 
            volatile struct P33C_GPIO_INSTANCE_s gpioConfig
        );
    
/* ********************************************************************************************* * 
 * GPIO INSTANCE CONFIGURATION TEMPLATES
 * ********************************************************************************************* */
extern volatile struct P33C_GPIO_INSTANCE_s gpioConfigClear;
    
#endif	/* P33C_GPIO_SFR_ABSTRACTION_H */

