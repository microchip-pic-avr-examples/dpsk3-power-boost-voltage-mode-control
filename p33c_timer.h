/*************************************************************************************************
 * @file   p33c_ccp.h
 * @author I62419
 * @date   Created on October 12, 2020, 5:41 PM
 ************************************************************************************************/

/*************************************************************************************************
 * @brief Generic Capture Compare Driver Module (header file)
 * @details
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 ************************************************************************************************/

#ifndef P33C_TIMER16_SFR_ABSTRACTION_H
#define	P33C_TIMER16_SFR_ABSTRACTION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types


#ifndef P33C_TIMER_MODULE_s     

/***********************************************************************************
 * @ingroup lib-layer-pral-properties-public-timer
 * @struct P33C_TIMER_MODULE_s
 * @brief Abstracted set of Special Function Registers of the 16-bit timer peripheral module
 * @details
 * This structure defines an abstracted set of Special Function Registers of the 
 * single 16-bit general purpose timer peripheral. Users can use this abstracted
 * set of registers to capture register settings from or write generic register 
 * settings to a specific instance of this peripheral.
 * 
 **********************************************************************************/

    struct P33C_TIMER_MODULE_s {

        union {
            struct tagT1CONBITS bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } TxCON; // TxCON: Timer X CONTROL REGISTER

        volatile unsigned :16; // (reserved)
        
        union {
            struct {
                uint16_t CNT;
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } TMRx; // TMRx TIMER COUNTER REGISTER
    
        volatile unsigned :16; // (reserved)

        union {
            struct {
                uint16_t PER;
            } bits; // Register bit-field
            uint16_t value; // 16-bit wide register value
        } PRx; // PRx TIMER PERIOD REGISTER
        
    } __attribute__((packed)); ///< 16-BIT TIMER INSTANCE SPECIAL FUNCTION REGISTER SET
    
    typedef struct P33C_TIMER_MODULE_s P33C_TIMER_MODULE_t;  ///< 16-BIT TIMER INSTANCE SPECIAL FUNCTION REGISTER SET DATA TYPE
    

/*********************************************************************************
 * @def    p33c_TimerModule_GetHandle(x)
 * @ingroup lib-layer-pral-functions-public-timer
 * @brief  Returns a pointer to the start address of the Timer SFR block
 * @return Pointer address to Timer SFR block of type struct P33C_TIMER_MODULE_s
 *  
 * @details
 * This macro returns the address pointer (tmrHandle) of the Timer Special
 * Function Register. The handle can be used to assign a global variable 
 * in user code, which allows to directly read from/write to Timer registers 
 * with zero API overhead.
 * 
 *********************************************************************************/
    #define p33c_TimerModule_GetHandle()    (struct P33C_TIMER_MODULE_s*)&T1CON;
    
#endif
    
/* GLOBAL FUNCTION CALL PROTOTYPES */
extern volatile struct P33C_TIMER_MODULE_s p33c_Timer_ConfigRead(void);
extern volatile uint16_t p33c_Timer_ConfigWrite(volatile struct P33C_TIMER_MODULE_s tmrConfig);

#endif	/* P33C_TIMER16_SFR_ABSTRACTION_H */

// end of file
