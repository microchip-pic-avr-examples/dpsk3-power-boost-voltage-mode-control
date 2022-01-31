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
 * File:   rtos_typedef.h
 * Author: M91406
 * Comments: 
 * Revision history: 
 *   1.0    initial release
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RTOS_TYPE_DEFINITION_HEADER_H
#define	RTOS_TYPE_DEFINITION_HEADER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <dsp.h> // include DSP data types

/***********************************************************************************
 * @ingroup operating-system-properties
 * @struct OS_TASKMGR_STATUS_s
 * @extends OS_TASK_MANAGER_s
 * @brief Task manager status word
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct OS_TASKMGR_STATUS_s {
    union {
        struct {
            unsigned lp_active   : 1; ///< Bit 0: Flag indicating that high-priority task queue is executed frequently
            unsigned hp_active   : 1; ///< Bit 1: Flag indicating that low-priority task queue is executed frequently
            unsigned lp_timeout  : 1; ///< Bit 2: Flag indicating that a low-priority queue timeout occured
            unsigned isr_timeout : 1; ///< Bit 3: Flag indicating that OS timer interrupt has timed out
            unsigned : 1; ///< Bit 4:  (reserved)
            unsigned : 1; ///< Bit 5:  (reserved)
            unsigned : 1; ///< Bit 6:  (reserved)
            unsigned : 1; ///< Bit 7:  (reserved)

            unsigned : 1; ///< Bit 8:  (reserved)
            unsigned : 1; ///< Bit 9:  (reserved)
            unsigned : 1; ///< Bit 10: (reserved)
            unsigned : 1; ///< Bit 11: (reserved)
            unsigned : 1; ///< Bit 12: (reserved)
            unsigned : 1; ///< Bit 13: (reserved)
            unsigned : 1; ///< Bit 14: (reserved)
            unsigned disable : 1; ///< When set, causes the execution of main() to be terminated resulting in a CPU reset
        } __attribute__((packed)) bits; ///< Status word bitfield
        volatile uint16_t value; ///< Status word value
    };
}; ///< Task manager data status
typedef struct OS_TASKMGR_STATUS_s OS_TASKMGR_STATUS_t; ///< Task manager data status data type

/***********************************************************************************
 * @ingroup operating-system-properties
 * @struct OS_TASKMGR_TIMEBASE_s
 * @extends OS_TASK_MANAGER_s
 * @brief Task scheduler time-base parameters
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct OS_TASKMGR_TIMEBASE_s {
    
	volatile int32_t Counter;  ///<  Operating system task execution tick counter
	volatile int32_t period;   ///<  Operating system task execution period
        
}; ///<  DESCRIPTION
typedef struct OS_TASKMGR_TIMEBASE_s OS_TASKMGR_TIMEBASE_t; ///<  DESCRIPTION

/***********************************************************************************
 * @ingroup operating-system-properties
 * @struct OS_TASKMGR_CPU_LOAD_s
 * @extends OS_TASK_MANAGER_s
 * @brief Data structure holding CPU load runtime information
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct OS_TASKMGR_CPU_LOAD_s {
    
	volatile fractional cpu_load; ///<  Operating system task execution tick counter
        
}; ///<  DESCRIPTION
typedef struct OS_TASKMGR_CPU_LOAD_s OS_TASKMGR_CPU_LOAD_t; ///<  DESCRIPTION

/***********************************************************************************
 * @ingroup operating-system-properties
 * @struct OS_TASK_MANAGER_s
 * @brief Data structure wrapping up tasks list of different priorities
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct OS_TASK_MANAGER_s {
    volatile struct OS_TASKMGR_STATUS_s Status;     ///< Task manager status word
    volatile struct OS_TASKMGR_TIMEBASE_s Timebase; ///< Task manager time base monitor
    volatile struct OS_TASKMGR_CPU_LOAD_s CpuLoad;  ///< Task manager CPU load metering result
};
typedef struct OS_TASK_MANAGER_s OS_TASK_MANAGER_t;



#endif	/* RTOS_TYPE_DEFINITION_HEADER_H */

// end of file
