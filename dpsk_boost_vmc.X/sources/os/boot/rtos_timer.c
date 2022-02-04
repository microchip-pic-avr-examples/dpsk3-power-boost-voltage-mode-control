/*
 * File:   init_timer1.c
 * Author: M91406
 *
 * Created on July 8, 2019, 2:47 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "config/hal.h"
#include "rtos_timer.h"
#include "p33c_timer.h"   

/***********************************************************************************
 * @ingroup os-timer-initialization
 * @fn     uint16_t osTimer_Initialize(void)
 * @brief  Initializes the timer used as time-base for the task scheduler
 * @return unsigned integer
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * The internal PLL is set up to operate the CPU at maximum speed of 100 MIPS 
 * (100 MHz instruction cycle). The task scheduler runs on a specific, usually 
 * fixed time base specified in the state machine section of the microcontroller
 * abstraction layer (e.g. 100us). 
 * 
 * This routine initializes a device timer exclusively used for that purpose
 * which is not shared with other tasks/peripherals to ensure stable, deterministic
 * behavior of the firmware. The timer does not use interrupts. The scheduler 
 * task execution period is controlled by polling on the timer overrun bit, allowing
 * some more relaxed timing while not putting additional burden on the CPU.
 *
 **********************************************************************************/

volatile uint16_t osTimer_Initialize (void)
{
    volatile uint16_t retval=1;
    volatile struct P33C_TIMER_MODULE_s* tmr;
    
    tmr = p33c_TimerModule_GetHandle();
    
    tmr->TxCON.bits.TON = 0;  // Timer1 On: Stops 16-bit Timer1 during configuration
    tmr->TxCON.bits.TSIDL = 0; // Timer1 Stop in Idle Mode: Continues module operation in Idle mode
    tmr->TxCON.bits.TMWDIS = 0; // Asynchronous Timer1 Write Disable: Back-to-back writes are enabled in Asynchronous mode
    tmr->TxCON.bits.TMWIP = 0; // Asynchronous Timer1 Write in Progress: Write to the timer in Asynchronous mode is complete
    tmr->TxCON.bits.PRWIP = 0; // Asynchronous Period Write in Progress: Write to the Period register in Asynchronous mode is complete
    tmr->TxCON.bits.TECS = 0b11; // Timer1 Extended Clock Select: FRC clock
    tmr->TxCON.bits.TGATE = 0; // Timer1 Gated Time Accumulation Enable: Gated time accumulation is disabled when TCS = 0
    tmr->TxCON.bits.TCKPS = 0; // Timer1 Input Clock Prescale Select: 1:1
    tmr->TxCON.bits.TSYNC = 0; // Timer1 External Clock Input Synchronization Select: Does not synchronize the External Clock input
    tmr->TxCON.bits.TCS = 0; // Timer1 Clock Source Select: Internal peripheral clock
    
    // Reset Timer Counter Register TMR to Zero; 
    tmr->TMRx.value = 0x0000;
    
    //Period = 0.0001 s; Frequency = 100000000 Hz; PR 9999; 
    tmr->PRx.value = MAIN_EXEC_PER;
    
    // Reset interrupt and interrupt flag bit
    _OSTIMER_IP = _OSTIMER_PRIORITY;  // Set interrupt priority to DEFAULT
    _OSTIMER_IF = 0;  // Reset interrupt flag bit
    _OSTIMER_IE = 0;  // Disable Timer1 interrupt
   
    return(retval);
}
 
/***********************************************************************************
 * @fn     uint16_t osTimer_Enable(volatile bool interrupt_enable, volatile uint8_t interrupt_priority)
 * @brief  Enables the timer used as time-base for the task scheduler
 * @param  interrupt_enable: Control flag of type boolean enabling or disabling the timer interrupt
 * @param  interrupt_priority: Interrupt Service Routine priority level of the timer interrupt (if enabled) between level 0 and 6
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 * Once the task scheduler time base has been initialized, this function can be 
 * used to enable the timer and start the scheduled task execution.
 *
 **********************************************************************************/

volatile uint16_t osTimer_Enable (volatile bool interrupt_enable, volatile uint8_t interrupt_priority)
{
    volatile uint16_t retval=1;
    volatile struct P33C_TIMER_MODULE_s* tmr;

    // Enable Timer1
    _OSTIMER_IP = interrupt_priority;  // Set interrupt priority to zero
    _OSTIMER_IF = 0;  // Reset interrupt flag bit
    _OSTIMER_IE = interrupt_enable;  // Enable/Disable Timer1 interrupt

    // Capture timer module
    tmr = p33c_TimerModule_GetHandle();
    
    tmr->TxCON.bits.TON = 1;  // Timer1 On: Starts 16-bit Timer 
    retval &= tmr->TxCON.bits.TON; // Check timer enable bit for verification
    
    return(retval);
}

// end of file
