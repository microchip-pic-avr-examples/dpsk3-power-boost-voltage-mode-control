/*
 * File:   task_execute.c
 * Author: M91406
 *
 * Created on May 27, 2021, 2:44 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stdlib.h> // include C standard library

#include "config/apps.h"    // include applicaiton layer abstraction header file
#include "config/os.h"      // include the operating system user configuration header file
#include "config/mcal.h"    // include the microcontroller abstraction layer header file

#include "rtos_typedef.h"   // include private data type defiitions
#include "boot/rtos_timer.h" // include operating system timer configuration driver header file

/*********************************************************************************
 * @ingroup operating-system-objects
 * @var     OS_TASK_MANAGER_t task_manager
 * @brief   The task manager object provides a global scope to task list execution status
 * @details
 *  ADD_DESCRIPTION_HERE
 **********************************************************************************/
volatile struct OS_TASK_MANAGER_s task_manager;

#define OSTMR_TIMEOUT  30000   // Timeout protection for OS-Timer interrupt flag bit

/***********************************************************************************
 * @ingroup GROUP_NAME
 * @enum    TASK_QUEUE_TYPE_e
 * @brief   ADD_SHORT_DESCRIPTION
 * @details
 *  DETAILED_DESCRIPTION
 ***********************************************************************************/
enum TASK_QUEUE_TYPE_e {
    
    QUEUE_INITIALIZE = 0,   ///<  Initialization function execution queue
	QUEUE_START = 1,        ///<  Start sequence function execution queue
	QUEUE_EXECUTE = 2,      ///<  Low-priority function execution queue
	QUEUE_STOP = 3          ///<  Stop sequence function execution queue
        
};
typedef enum TASK_QUEUE_TYPE_e TASK_QUEUE_TYPE_t; ///< DESCRIPTION

/***********************************************************************************
 * @ingroup GROUP_NAME
 * @enum    ENUMERATION_NAMESPACE_e
 * @brief   ADD_SHORT_DESCRIPTION
 * @details
 *  DETAILED_DESCRIPTION
 ***********************************************************************************/
enum TASK_QUEUE_EXECUTE_OPTION_e {
    
	QUEUE_EXEC_ALL = 0, ///<  Execute all listed tasks
	QUEUE_EXEC_LP = 1,  ///<  Only execute low priority tasks
	QUEUE_EXEC_HP = 2   ///<  Only execute high priority tasks
        
};
typedef enum TASK_QUEUE_EXECUTE_OPTION_e TASK_QUEUE_EXECUTE_OPTION_t; ///< DESCRIPTION

typedef uint16_t (*FUNCPTR_t)(void);    // Definition of data type of a standard function pointer

// APPLICATION LAYER PRIORITY TASK LISTS (externally defined in apps.c)

#define NO_OF_TASK_QUEUES   4

// OS Task Queue objects and their contents are declared externally by the user.
// These defined lists are imported here and grouped into a "List of Queues" 
// allowing the OS to efficiently access their members

extern volatile struct APPLICATION_TASK_s* Queue_InitializeSequence[];
extern volatile uint16_t Queue_InitializeSequence_Size; 

extern volatile struct APPLICATION_TASK_s* Queue_StartSequence[];
extern volatile uint16_t Queue_StartSequence_Size; 

extern volatile struct APPLICATION_TASK_s* Queue_ExecuteSequence[];
extern volatile uint16_t Queue_ExecuteSequence_Size; 

extern volatile struct APPLICATION_TASK_s* Queue_StopSequence[];
extern volatile uint16_t Queue_StopSequence_Size; 

// The "List of Queues" is organizing the data of all user tasks for
//  theOS to be processed efficiently in the task execution function
static volatile struct APPLICATION_TASK_s** exec_queues[] = {
    (volatile struct APPLICATION_TASK_s**)&Queue_InitializeSequence, 
    (volatile struct APPLICATION_TASK_s**)&Queue_StartSequence,
    (volatile struct APPLICATION_TASK_s**)&Queue_ExecuteSequence,
    (volatile struct APPLICATION_TASK_s**)&Queue_StopSequence
};

// Array holding the individual sizes of the task queues
static volatile uint16_t* exec_queues_sizes[] = {
    &Queue_InitializeSequence_Size, 
    &Queue_StartSequence_Size,
    &Queue_ExecuteSequence_Size,
    &Queue_StopSequence_Size
};

// Size of the "List Of Queues"
static volatile uint16_t exec_queues_size = (sizeof(exec_queues)/sizeof(exec_queues[0]));

// A user task is embedded in a data structure allowing to attach
// additional information about its type, size, execution time and
// an object identifier label
struct OS_TASK_QUEUE_s {
    volatile struct APPLICATION_TASK_s** ptrQueue;  ///< Pointer to task queue
    volatile enum TASK_QUEUE_TYPE_e queueType;      ///< Type of task queue
    volatile uint16_t size;                         ///< Size of the task queue
    volatile uint32_t exec_time;                    ///< Execution time of the task queue
    volatile uint16_t id;                           ///< Identifier of this task queue
};
typedef struct OS_TASK_QUEUE_s OS_TASK_QUEUE_t;

// The "List of Queues" is wrapped into a data structure to attach
// additional information about the "List of Queues" such as its
// size
struct OS_TASK_QUEUES_s {
    volatile uint16_t size;
    volatile struct OS_TASK_QUEUE_s queues[NO_OF_TASK_QUEUES];
};
typedef struct OS_TASK_QUEUES_s OS_TASK_QUEUES_t;

// The "List of Queues" object is made available through
// the my_queues variable of type OS_TASK_QUEUES_s 
static volatile struct OS_TASK_QUEUES_s os_queues;

// Private high-/low-priority code profiling auxiliary variables
static volatile bool LowPriorityWait = true; 

// Debugging array for task execution tracking
#if __DEBUG
volatile uint16_t ptrTaskProfileArray;
volatile uint16_t arrTaskProfile[2][TASK_PROFILE_ARR_SIZE];
#endif

// Private function prototypes of task list execution functions
static volatile uint16_t rtos_Initialize(void);
static volatile uint16_t rtos_Start(void);
static volatile uint16_t rtos_Queue_Execute(TASK_QUEUE_TYPE_t type, TASK_QUEUE_EXECUTE_OPTION_t priority);
static volatile uint16_t rtos_Task_Execute(volatile FUNCPTR_t fptr, volatile int32_t* exec_loops, volatile int32_t* exec_time);

static volatile uint16_t __attribute__((always_inline))rtos_TaskExecCounter_Update(void);

/*********************************************************************************
 * @ingroup operating-system-functions-public
 * @fn      uint16_t rtos_Stop(void)
 * @brief   Stops the execution of user tasks and halts the execution timer
 * @return  unsigned integer (0=failure, 1=success)
 *
 * @details
 *  
 **********************************************************************************/

volatile uint16_t rtos_Stop(void)
{
    volatile uint16_t retval=1;
    
    // Execute function list covering user-task start-up functions
    retval &= rtos_Queue_Execute(QUEUE_STOP, QUEUE_EXEC_ALL);
    
    // Set SCheduler Disable bit exits the continuous main() loop 
    // forcing a CPU reset.
    task_manager.Status.bits.disable = true;
   
    return(retval);
}

/*********************************************************************************
 * @ingroup operating-system-functions-public
 * @fn      uint16_t rtos_End(void)
 * @brief   Ends the execution of the main() loop enforcing a CPU reset.
 * @return  unsigned integer (0=failure, 1=success)
 *
 * @details
 *  
 **********************************************************************************/

volatile uint16_t rtos_End(void)
{
    volatile uint16_t retval=1;
    
    // Execute function list covering user-task start-up functions
    retval &= rtos_Queue_Execute(QUEUE_STOP, QUEUE_EXEC_ALL);
    
    // Set SCheduler Disable bit exits the continuous main() loop 
    // forcing a CPU reset.
    task_manager.Status.bits.disable = true;
   
    return(retval);
}

/*********************************************************************************
 * @ingroup operating-system-functions-public
 * @fn      uint16_t rtos_Execute(void)
 * @brief   Application main loop
 * @return  unsigned integer (0=failure, 1=success)
 * @details
 * This function replaces the common main()-loop of a C-program, which would 
 * commonly be placed in file main.c. This function will only be called once 
 * from main() and remain to be executed on the lowest CPU priority of #0.
 * Within the main()-loop of this function, the execution of the low-priority 
 * task sequence is called, triggered by the interrupt-driven, real-time high-
 * priority task layer function. Thus low-priority layer tasks are always called
 * at a moment of potentially lowest CPU load, with the highest likelihood of
 * completing the execution.
 * 
 * Some low-priority tasks, however, might always take multiple task-manager
 * cycles to be executed, during which period they will get frequently interrupted
 * by high-priority tasks. 
 *
 **********************************************************************************/

volatile uint16_t rtos_Execute(void)
{
    volatile uint16_t retval = 1;
    volatile uint16_t timeout = 0;

    // Initialize User Tasks and OS Timer
    retval &= rtos_Initialize();
    
    // Launch RTOS scheduler
    retval &= rtos_Start();
    
    // Main program execution
    while (!task_manager.Status.bits.disable) {

        // wait while low-priority wait semaphore is set or a 'go' timeout occurs
        while ((LowPriorityWait) && (timeout++ < OSTMR_TIMEOUT));   // Wait until semaphore is cleared
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Execute non-time critical, low-priority tasks
        
        retval &= rtos_Queue_Execute(QUEUE_EXECUTE, QUEUE_EXEC_LP);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // After all code has been executed, reset counters to capture "free" CPU cycles
        timeout = 0;                // Reset timeout counter
        LowPriorityWait = true;     // Set Low-Priority Queue Wait
    }

    CPU_RESET();    // if the firmware ever ends up here, reset the CPU
    
    return(0);      // Return "false" signaling OS has exited execution
}

/**********************************************************************************
 * @ingroup operating-system-functions-private
 * @fn      void _OsTimerInterrupt(void)
 * @brief   High priority, interrupt-driven task sequence execution
 * 
 * @details
 * This interrupt is used to call the high priority task sequence at a fixed
 * repetition frequency (default of 10 kHz/100 us period). All tasks listed
 * in the high priority task list will get executed one after another. The total
 * execution time of the sequence therefore has to fit in the given repetition 
 * period to ensure reliable real-time resolution of each task of the sequence.
 * 
 * ********************************************************************************/

void __attribute__((__interrupt__, context, no_auto_psv)) _OsTimerInterrupt(void)
{
	volatile uint16_t retval=1;
    
    // Increment execution period counter
    task_manager.Status.bits.hp_active = true;  // Set High-Priority Task Execution flag bit
    task_manager.Timebase.Counter++;            // Increment task manager OS time-base counter
    _OSTIMER_IF = 0;                            // Clear the interrupt flag bit
    
    // Update task execution counter
    rtos_TaskExecCounter_Update();  // Increment all task execution time-base counter
        
    // Execute high priority task queue
    retval &= rtos_Queue_Execute(QUEUE_EXECUTE, QUEUE_EXEC_HP); // execute the high priority task queue

    // Clear low-priority semaphore allowing to execute low-priority tasks
    LowPriorityWait = false;    // Clear WAIT trigger allowing execution of low priority tasks
//    _OSTIMER_IF = 0;            // Clear the interrupt flag bit

    return;
}

/*********************************************************************************
 * @ingroup operating-system-functions-private
 * @fn      uint16_t rtos_Initialize(void)
 * @brief   Initializes the task manager object and user-task execution lists
 * @return  unsigned integer (0=failure, 1=success)
 *
 * @details
 *  
 **********************************************************************************/

static volatile uint16_t rtos_Initialize(void)
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t _j=0;
    
    // Reset task manager status word
    task_manager.Status.value = 0;

    // Set size of "List of Queues" object
    os_queues.size = exec_queues_size;
    
    // Initialize all queue objects
    for (_i=0; _i<exec_queues_size; _i++)
    {
        os_queues.queues[_i].ptrQueue = (volatile struct APPLICATION_TASK_s**)exec_queues[_i];
        os_queues.queues[_i].size = *exec_queues_sizes[_i];
        os_queues.queues[_i].queueType = _i;
        os_queues.queues[_i].id = 100 * (os_queues.queues[_i].queueType + 1);
        os_queues.queues[_i].exec_time = 0;

        // Assign task IDs to task objects
        for (_j=0; _j<os_queues.queues[_i].size; _j++)
        {
            os_queues.queues[_i].ptrQueue[_j]->TaskID = 
                ((100 * os_queues.queues[_i].ptrQueue[_j]->Settings.execClass) + _j);
            
            os_queues.queues[_i].ptrQueue[_j]->Status.busy = false;
            os_queues.queues[_i].ptrQueue[_j]->Status.retval = false;

        }
        
    }

    // Configure Operating System Timer
    retval &= osTimer_Initialize(); 

    return(retval);
}

/*********************************************************************************
 * @ingroup operating-system-functions-private
 * @fn      uint16_t rtos_Start(void)
 * @brief   Initializes the task manager object and user-task execution lists
 * @return  unsigned integer (0=failure, 1=success)
 *
 * @details
 *  
 **********************************************************************************/

static volatile uint16_t rtos_Start(void)
{
    volatile uint16_t retval=1;
    
    // Start Operating System Timer without interrupts (no high priority execution)
    retval &= osTimer_Enable(false, 0);

    // Execute function list covering user-task initialization functions
    retval &= rtos_Queue_Execute(QUEUE_INITIALIZE, QUEUE_EXEC_ALL);

    // Execute function list covering user-task start-up functions
    retval &= rtos_Queue_Execute(QUEUE_START, QUEUE_EXEC_ALL);

    // Start Operating System Timer with interrupts (starts high priority task execution)
    retval &= osTimer_Enable(true, _OSTIMER_PRIORITY);
   
    return(retval);
}

/**********************************************************************************
 * @ingroup operating-system-functions-private
 * @fn      uint16_t OsLowPriorityTasks_Execute(void)
 * @brief   Low priority task sequence executed after the high priority task sequence execution is complete
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This function executes different task lists of which some are time 
 * critical while others are insensitive to execution time jitter. Each
 * task list handed into this function will be executed from task #0 to
 * task #n in ascending order. Hence, tasks with a lower list index will
 * encounter less task execution jitter than others with a higher list
 * index.
 * 
 * This function can also be interrupted by the high-priority execution 
 * call, in which case the high-priority task will be executed before the 
 * previously started low-priority task sequence has completed. 
 * 
 * ********************************************************************************/

static volatile uint16_t rtos_Queue_Execute(TASK_QUEUE_TYPE_t type, TASK_QUEUE_EXECUTE_OPTION_t priority)
{
    volatile uint16_t retval=1;         // common return variable
    volatile int32_t _tretval=0;        // task execution time return variable
    volatile int32_t* _tloops=0;        // pointer to task execution loop counter
    
    // Execution runtime variables
    volatile uint16_t _i=0;             // common runtime index
    volatile uint16_t _size=0;          // buffer variable holding the size of the queue
    volatile uint16_t _ptr_offset=0;    // pointer offset for calculation of the address of the most recent queue function to be executed
    volatile uint16_t* _ptr;            // function pointer to the most recent queue function
    
    // Execution trigger variables
    volatile bool _exec=false;          // flag indicating if task is due to be executed
    volatile int32_t _tdiff=0;          // execution time difference buffer variable

DBGPIN2_Clear();
Nop();
Nop();
Nop();
DBGPIN2_Set();
    
    // Execute queue task
    _size = os_queues.queues[type].size;        // copy of queue size in local variable
    _ptr_offset = sizeof(exec_queues[type]);    // copy pointer address offset into local variable

    // Track if all execution layers are executed
    if (priority == QUEUE_EXEC_HP) task_manager.Status.bits.hp_active = true;
    if (priority == QUEUE_EXEC_LP) task_manager.Status.bits.lp_active = true;
    
    // Roll through queue executing due tasks
    for (_i=0; _i<_size; _i++) {
        
        // Check if task is due to be executed
        if (priority == QUEUE_EXEC_ALL) 
        { _exec  = true; }
        else {
            if (os_queues.queues[type].ptrQueue[_i]->Status.enabled)
            {
                if ((int)os_queues.queues[type].ptrQueue[_i]->Settings.execClass == (int)priority)
                {
                    _tdiff = (os_queues.queues[type].ptrQueue[_i]->Settings.Period + 
                              os_queues.queues[type].ptrQueue[_i]->Settings.Offset);
                    _exec = (bool)(os_queues.queues[type].ptrQueue[_i]->Settings.Counter >= _tdiff);
                }
            }
        }

        // IF task is due to be executed
        if (_exec)
        {
            // Capture pointer to first function of queue
            _ptr = (uint16_t *)&os_queues.queues[type].ptrQueue[_i]->Functions.Initialize;
            _ptr += type; // Add queue offset to dereference correct function pointer of most recent queue
            _tloops = &os_queues.queues[type].ptrQueue[_i]->Settings.Counter; // Capturing pointer to task counter

            os_queues.queues[type].ptrQueue[_i]->Status.busy = true;     // Set BUSY status

            retval = rtos_Task_Execute((FUNCPTR_t)(*_ptr), _tloops, &_tretval);   // Call task function, get execution time

            os_queues.queues[type].ptrQueue[_i]->Status.retval = retval; // log last function result
            os_queues.queues[type].ptrQueue[_i]->Status.busy = false;    // Clear BUSY status

            // Check if OS timer has overflown
            if (_OSTIMER_IF) {
                task_manager.Timebase.Counter += _OSTIMER_IF;            
                rtos_TaskExecCounter_Update();  // Increment all task execution time-base counter
            }
            
            // Set up task counter for next execution
            _tdiff  = os_queues.queues[type].ptrQueue[_i]->Settings.Counter;
            _tdiff -= os_queues.queues[type].ptrQueue[_i]->Settings.Offset;
            _tdiff -= os_queues.queues[type].ptrQueue[_i]->Settings.Period;
            _tdiff += os_queues.queues[type].ptrQueue[_i]->Settings.Offset;
            os_queues.queues[type].ptrQueue[_i]->Settings.Counter = _tdiff; // Set execution counter
            
        }
    }

DBGPIN2_Clear();    
    
    // Return result (0=failure, 1=success)
    return(retval);
}

/*********************************************************************************
 * @ingroup operating-system-functions-private
 * @fn      uint16_t rtos_Task_Execute(volatile FUNCPTR_t fptr, volatile int32_t* exec_time)
 * @brief   Executes a single task of the most recent task queue measuring its execution time
 * @param   fptr: Function pointer to task function
 * @param   exec_time: Pointer to external task execution time variable of type unsigned long integer
 * @return  unsigned integer (0=failure, 1=success)
 * @details
 *  ADD_DESCRIPTION_HERE
 *
 *
 **********************************************************************************/

static volatile uint16_t rtos_Task_Execute(volatile FUNCPTR_t fptr, volatile int32_t* exec_loops, volatile int32_t* exec_time)
{
    volatile uint16_t retval=1;

    // Auxiliary variables for execution time calculation
    volatile uint16_t _start=0, _stop=0;
    volatile uint32_t _pre_loop_cnt=0, _loops=0;
    volatile uint32_t _texec=0;

    if(fptr == NULL){ // If function pointer is invalid, return failure
        *exec_time = 0; // Clear execution time
        return(0);  // Return failure value = 0 indicating unsuccessful action
    }
    
    // Capture effective execution time of task queue
    // by capturing timer period counter register value
    _pre_loop_cnt = *exec_loops; // capture loop counter value
    _start = _OSTIMER_TMRCAP; // capture time-base count
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    retval &= fptr();   // Execute queue function

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Capture effective execution time of task sequence
    // by capturing timer period counter register value
    _stop = _OSTIMER_TMRCAP;
    _loops = (*exec_loops - _pre_loop_cnt); // capture number of execution cycles

    // Calculate effective execution time of low priority task sequence
    switch(_loops) 
    {
        case 0: // Timer has not overflown during task list execution
            _texec = (uint32_t)(_stop - _start);
            break;

        case 1: // Timer has overflown once during task list execution
            _texec = (uint32_t)(MAIN_EXEC_PER - _start);
            _texec += (uint32_t)_stop;
            break;

        default: // Timer has overflown multiple times during task list execution
            _texec = __builtin_muluu(_loops, MAIN_EXEC_PER);
            _texec -= (uint32_t)(MAIN_EXEC_PER - _start);
            _texec += (uint32_t)_stop;
            break;
    }

    // Copy measured execution time to function parameter "exec_time"
    *exec_time = _texec;
    
    // Return function result success=1, failure=0
    return(retval);
    
}

/*********************************************************************************
 * @ingroup operating-system-functions-private
 * @fn      uint16_t rtos_TaskExecCounter_Update(void)
 * @brief   ADD_SHORT_DESCRIPTION
 * @return  unsigned integer (0=failure, 1=success)
 * @details
 *  ADD_DESCRIPTION_HERE
 *
 **********************************************************************************/

static volatile uint16_t rtos_TaskExecCounter_Update(void)
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t _toff=0;

    // Capture most recent time base counter to prevent drift across tasks
    _toff = task_manager.Timebase.Counter;  
    
    // Increment all task execution counters
    for (_i=0; _i<Queue_ExecuteSequence_Size; _i++) {
        Queue_ExecuteSequence[_i]->Settings.Counter += _toff;
    }
    
    // Reset common time base counter
    task_manager.Timebase.Counter = 0;  // Clear the task scheduler tick counter
    _OSTIMER_IF = 0;                    // Clear Timer interrupt flag bit

    return(retval);
}

// end of file
