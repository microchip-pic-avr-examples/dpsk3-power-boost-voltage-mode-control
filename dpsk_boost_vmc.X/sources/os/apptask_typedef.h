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
 * File:   app_typedef.h
 * Author: M91406
 * Comments: Header file providing type declarations of a user task object
 * Revision history: 
 *  1.0     initial release
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RTOS_APPTASK_TYPE_DEFINITION_HEADER_H
#define	RTOS_APPTASK_TYPE_DEFINITION_HEADER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types

/***********************************************************************************
 * @ingroup application-task-object-properties
 * @enum    APPTASK_CLASS_s
 * @brief   ADD_SHORT_DESCRIPTION
 * @details
 *  DETAILED_DESCRIPTION
 ***********************************************************************************/
enum APPTASK_CLASS_e {
    
	APP_CLASS_NONE = 0,         ///<  DESCRIPTION
    APP_CLASS_LOW_PRIORITY = 1, ///<  DESCRIPTION
	APP_CLASS_HIGH_PRIORITY = 2 ///<  DESCRIPTION
        
};
typedef enum APPTASK_CLASS_e APPTASK_CLASS_t;  ///< DESCRIPTION

/***********************************************************************************
 * @ingroup application-task-object-properties
 * @struct APPTASK_STATUS_s
 * @extends APPLICATION_TASK_s
 * @brief ADD_SHORT_DESCRIPTION
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct APPTASK_STATUS_s {
    
	volatile bool retval  : 1; ///< Bit 0:  Status bit indicating a failed execution of the user task
	volatile unsigned     : 1; ///< Bit 1:  (reserved)
	volatile unsigned     : 1; ///< Bit 2:  (reserved)
	volatile unsigned     : 1; ///< Bit 3:  (reserved)
	volatile unsigned     : 1; ///< Bit 4:  (reserved)
	volatile unsigned     : 1; ///< Bit 5:  (reserved)
	volatile unsigned     : 1; ///< Bit 6:  (reserved)
	volatile bool busy    : 1; ///< Bit 7:  Status bit indicating the task is busy

	volatile unsigned     : 1; ///< Bit 8:  (reserved)
	volatile unsigned     : 1; ///< Bit 9:  (reserved)
	volatile unsigned     : 1; ///< Bit 10: (reserved)
	volatile unsigned     : 1; ///< Bit 11: (reserved)
	volatile unsigned     : 1; ///< Bit 12: (reserved)
	volatile unsigned     : 1; ///< Bit 13: (reserved)
	volatile unsigned     : 1; ///< Bit 14: (reserved)
	volatile bool enabled : 1; ///< Bit 15: Control bit enabling the execution of the task execute function
        
}; ///<  DESCRIPTION
typedef struct APPTASK_STATUS_s APPTASK_STATUS_t; ///<  DESCRIPTION

/***********************************************************************************
 * @ingroup application-task-object-properties
 * @struct APPTASK_EXECUTION_s
 * @extends APPLICATION_TASK_s
 * @brief ADD_SHORT_DESCRIPTION
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct APPTASK_EXECUTION_s {
    
    volatile enum APPTASK_CLASS_e execClass;    ///< Execution class of the task object (low priority, high priority)
	volatile int32_t Counter;   ///< Execution period counter (read only)
	volatile int32_t Period;    ///< Task execution period defined in multiples of OS task execution base clock ticks (e.g. 100us)
	volatile int32_t Offset;    ///< Task execution period offset defined in multiples of OS task execution base clock ticks (e.g. 100us)
        
}; ///<  DESCRIPTION
typedef struct APPTASK_EXECUTION_s APPTASK_EXECUTION_t; ///<  DESCRIPTION

/***********************************************************************************
 * @ingroup application-task-object-properties
 * @struct APPTASK_EXECUTION_s
 * @extends APPLICATION_TASK_s
 * @brief ADD_SHORT_DESCRIPTION
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct APPTASK_TASKLINK_s {
    
    volatile uint16_t (*Initialize)(void);  ///< Function pointer to INITIALIZATION routine
    volatile uint16_t (*Start)(void);       ///< Function pointer to START routine
    volatile uint16_t (*Execute)(void);     ///< Function pointer to EXECUTE routine
    volatile uint16_t (*Dispose)(void);     ///< Function pointer to DISPOSE routine
        
}; ///<  DESCRIPTION
typedef struct APPTASK_TASKLINK_s APPTASK_TASKLINK_t; ///<  DESCRIPTION


/***********************************************************************************
 * @ingroup application-task-object-properties
 * @struct APPTASK_STATISTICS_s
 * @extends APPLICATION_TASK_s
 * @brief ADD_SHORT_DESCRIPTION
 * @details
 *  ADD_DETAILED_DESCRIPTION
 **********************************************************************************/
struct APPTASK_STATISTICS_s {
    
    volatile uint32_t exec_time; ///< Execution time in CPU ticks of the most recent task execution (read only)
	volatile uint32_t avg_time;  ///< Moving average execution time of the task object (read only)
	volatile uint32_t max_time;  ///< Maximum execution time of the task object (latched tracking, reset in software)
        
}; ///<  DESCRIPTION
typedef struct APPTASK_STATISTICS_s APPTASK_STATISTICS_t; ///<  DESCRIPTION

/***********************************************************************************
 * @ingroup application-task-object-properties
 * @struct APPLICATION_TASK_s
 * @brief Application task object
 * @details
 *  The application task object is wrapped around a user task added to the project
 * as building block and which execution is managed by the task scheduler of the 
 * operating system.
 **********************************************************************************/
struct APPLICATION_TASK_s {
    
	volatile struct APPTASK_STATUS_s     Status;     ///< Status word of the task object
    volatile struct APPTASK_EXECUTION_s  Settings;   ///< Execution time settings of the task object
    volatile struct APPTASK_TASKLINK_s   Functions;  ///< Function pointer to main API user task functions
    volatile struct APPTASK_STATISTICS_s Statistics; ///< Task execution statistics data
    volatile uint16_t TaskID;                        ///< Task identifier encoding task execution list and list index (read only)
        
}; ///<  DESCRIPTION
typedef struct APPLICATION_TASK_s  APPLICATION_TASK_t; ///< Application Task Control Object

#endif	/* RTOS_APPTASK_TYPE_DEFINITION_HEADER_H */

// end of file
