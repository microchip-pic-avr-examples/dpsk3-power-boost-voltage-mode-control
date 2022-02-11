/*
 * File:   apps.c
 * Author: M91406
 *
 * Created on June 10, 2021, 1:06 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "apps.h" // include application layer header file
#include "os/apptask_typedef.h" // include task object data structure declarations

/****************************************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var appTask_LED
 * @brief LED User Task declaration and configuration
 *****************************************************************************************************/
volatile struct APPLICATION_TASK_s appLed = 
{
    .Functions.Initialize = &appLED_Initialize, ///< Pointer to user task INITIALIZATION function
    .Functions.Start      = &appLED_Start,      ///< Pointer to user task INITIALIZATION function
    .Functions.Execute    = &appLED_Execute,    ///< Pointer to user task INITIALIZATION function
    .Functions.Dispose    = &appLED_Dispose,    ///< Pointer to user task INITIALIZATION function
    
    .Settings.execClass   = APP_CLASS_LOW_PRIORITY, ///< Application task lass (high- or low-priority)
    .Settings.Period      = 1000,               ///< Task execution period in OS task manager call ticks
    .Settings.Offset      = 0,                  ///< Task execution offset in OS task manager call ticks
    
    .Status.enabled       = true                ///< Enable this task right after startup
};

/****************************************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var appPushButtonConfig
 * @brief Task configuration of the Push Button User Task
 *****************************************************************************************************/
volatile struct APPLICATION_TASK_s appPushButton = 
{
    .Functions.Initialize = &appPushButton_Initialize,  ///< Pointer to user task INITIALIZATION function
    .Functions.Start      = &appPushButton_Start,       ///< Pointer to user task START function
    .Functions.Execute    = &appPushButton_Execute,     ///< Pointer to user task EXECUTE function
    .Functions.Dispose    = &appPushButton_Dispose,     ///< Pointer to user task DISPOSE function

    .Settings.execClass   = APP_CLASS_LOW_PRIORITY,     ///< Application task lass (high- or low-priority)
    .Settings.Period      = 200,                        ///< Task execution period in OS task manager call ticks
    .Settings.Offset      = 20,                         ///< Task execution offset in OS task manager call ticks
    
    .Status.enabled       = true                        ///< Enable this task right after startup
};

/****************************************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var appLcdConfig
 * @brief Task configuration of the LCD User Task
 *****************************************************************************************************/
volatile struct APPLICATION_TASK_s appLcd = 
{
    .Functions.Initialize = &appLCD_Initialize,         ///< Pointer to user task INITIALIZATION function
    .Functions.Start      = &appLCD_Start,              ///< Pointer to user task START function
    .Functions.Execute    = &appLCD_Execute,            ///< Pointer to user task EXECUTE function
    .Functions.Dispose    = &appLCD_Dispose,            ///< Pointer to user task DISPOSE function

    .Settings.execClass   = APP_CLASS_LOW_PRIORITY,     ///< Application task lass (high- or low-priority)
    .Settings.Period      = 2000,                       ///< Task execution period in OS task manager call ticks
    .Settings.Offset      = 40,                         ///< Task execution offset in OS task manager call ticks
    
    .Status.enabled       = true                        ///< Enable this task right after startup
};

/****************************************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var appTask_GUI
 * @brief GUI User Task declaration and configuration
 *****************************************************************************************************/
//volatile struct APPLICATION_TASK_s appGui = 
//{
//    .Functions.Initialize = &appGUI_Initialize,         ///< Pointer to user task INITIALIZATION function
//    .Functions.Start      = &appGUI_Start,              ///< Pointer to user task START function
//    .Functions.Execute    = &appGUI_Execute,            ///< Pointer to user task EXECUTE function
//    .Functions.Dispose    = &appGUI_Dispose,            ///< Pointer to user task DISPOSE function
//
//    .Settings.execClass   = APP_CLASS_LOW_PRIORITY,     ///< Application task lass (high- or low-priority)
//    .Settings.Period      = 1000,                       ///< Task execution period in OS task manager call ticks
//    .Settings.Offset      = 40,                         ///< Task execution offset in OS task manager call ticks
//    
//    .Status.enabled       = true                        ///< Enable this task right after startup
//};

/****************************************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var appPowerSupplyConfig
 * @brief Task configuration of the Power Supply User Task
 *****************************************************************************************************/
volatile struct APPLICATION_TASK_s appPowerSupply = 
{
    .Functions.Initialize = &appPowerSupply_Initialize, ///< Pointer to user task INITIALIZATION function
    .Functions.Start      = &appPowerSupply_Start,      ///< Pointer to user task START function
    .Functions.Execute    = &appPowerSupply_Execute,    ///< Pointer to user task EXECUTE function
    .Functions.Dispose    = &appPowerSupply_Stop,       ///< Pointer to user task DISPOSE/STOP function

    .Settings.execClass   = APP_CLASS_HIGH_PRIORITY,    ///< Application task lass (high- or low-priority)
    .Settings.Period      = 0,                          ///< Task execution period in (n-1) OS task manager call ticks 
    .Settings.Offset      = 0,                          ///< Task execution offset in (n-1) OS task manager call ticks
    
    .Status.enabled       = true                        ///< Enable this task right after startup
};

/****************************************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var appFaultMonitorConfig
 * @brief Task configuration of the Power Supply User Task
 *****************************************************************************************************/
volatile struct APPLICATION_TASK_s appFaultMonitor = 
{
    .Functions.Initialize = &appFaultMonitor_Initialize, ///< Pointer to user task INITIALIZATION function
    .Functions.Start      = &appFaultMonitor_Start,      ///< Pointer to user task START function
    .Functions.Execute    = &appFaultMonitor_Execute,    ///< Pointer to user task EXECUTE function
    .Functions.Dispose    = &appFaultMonitor_Dispose,    ///< Pointer to user task DISPOSE function

    .Settings.execClass   = APP_CLASS_HIGH_PRIORITY,    ///< Application task lass (high- or low-priority)
    .Settings.Period      = 0,                          ///< Task execution period in (n-1) OS task manager call ticks 
    .Settings.Offset      = 0,                          ///< Task execution offset in (n-1) OS task manager call ticks

    .Status.enabled       = true                        ///< Enable this task right after startup
};

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     Queue_Execute
 * @brief   Function pointer array listing all user-tasks of this application
 * @details
 *  The task list is an array capturing all static tasks of the application. 
 * Each task is an independent, functional entity serving a specific purpose,
 * and is performing a specific function respectively. The order in which tasks
 * are added to this list does not reflect their importance/priority and only
 * serves the purpose of exposing them to the operating system, which will then
 * group and execute them in priority queues.
 * 
 * The specific settings of each task can be configured in their respective
 * settings data structure, where execution period, execution offset and 
 * priority can be defined.
 * 
 **********************************************************************************/
volatile struct APPLICATION_TASK_s* Queue_ExecuteSequence[] =
{
    &appLed,          ///< Application Task #1: LED Task
//    &appGui,          ///< Application Task #0: GUI Task
    &appLcd,          ///< Application Task #2: LCD Task
    &appPushButton,   ///< Application Task #3: Push-Button Task
    &appPowerSupply,  ///< Application Task #4: Power Supply Control Task
    &appFaultMonitor  ///< Application Task #5: Fault Monitor Task
};

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     TaskList_Size
 * @brief   Size of the task list covering all user-task managed by the OS
 * @details
 *  The size of the application task array TaskList needs to be known by the 
 * operating system for runtime control. This variable does not have to be 
 * updated by users. The size of the array will be automatically updated at 
 * compile time.
 **********************************************************************************/
volatile uint16_t Queue_ExecuteSequence_Size = (sizeof(Queue_ExecuteSequence)/sizeof(Queue_ExecuteSequence[0])); 

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     TaskList_StartSequence
 * @brief   Function pointer array listing all user-task start-up functions
 * @details
 *  The Start Sequence task list covers all user-task Start functions. These
 * tasks will be called after the user-task Initialize functions have been
 * executed. It is recommended to structure the code of user-tasks in a way
 * that the Start function puts the task and all related global variables and
 * data objects into a defined, initial condition and enables all required
 * features.
 * 
 * The list will be executed by the operating system in order of appearance. 
 * Hence, lower indices will be called before higher indices. This allows 
 * programmers to define a deterministic startup sequence of the user application
 * firmware.
 **********************************************************************************/
volatile struct APPLICATION_TASK_s* Queue_StartSequence[] =
{
    &appLed,            ///< Task Startup Sequence Function #1: Start LED Task
//    &appGui,            ///< Task Startup Sequence Function #0: Start GUI Task
    &appLcd,            ///< Task Startup Sequence Function #2: Start LCD Task
    &appPushButton,     ///< Task Startup Sequence Function #3: Start Push-Button Task
    &appPowerSupply,    ///< Task Startup Sequence Function #4: Start Power Supply Control Task
    &appFaultMonitor    ///< Task Startup Sequence Function #5: Start Fault Monitor Task
};

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     Queue_StartSequence_Size
 * @brief   Size of the task list covering all user-task managed by the OS
 * @details
 *  The size of the application task array TaskList needs to be known by the 
 * operating system for runtime control. This variable does not have to be 
 * updated by users. The size of the array will be automatically updated at 
 * compile time.
 **********************************************************************************/
volatile uint16_t Queue_StartSequence_Size = (sizeof(Queue_StartSequence)/sizeof(Queue_StartSequence[0])); 


/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     Queue_Initialize
 * @brief   Function pointer array listing all user-task start-up functions
 * @details
 *  The Start Sequence task list covers all user-task Start functions. These
 * tasks will be called after the user-task Initialize functions have been
 * executed. It is recommended to structure the code of user-tasks in a way
 * that the Start function puts the task and all related global variables and
 * data objects into a defined, initial condition and enables all required
 * features.
 * 
 * The list will be executed by the operating system in order of appearance. 
 * Hence, lower indices will be called before higher indices. This allows 
 * programmers to define a deterministic startup sequence of the user application
 * firmware.
 **********************************************************************************/
volatile struct APPLICATION_TASK_s* Queue_InitializeSequence[] =
{
    &appLed,            ///< Task Startup Sequence Function #1: Start LED Task
//    &appGui,            ///< Task Startup Sequence Function #0: Start GUI Task
    &appLcd,            ///< Task Startup Sequence Function #2: Start LCD Task
    &appPushButton,     ///< Task Startup Sequence Function #3: Start Push-Button Task
    &appPowerSupply,    ///< Task Startup Sequence Function #4: Start Power Supply Control Task
    &appFaultMonitor    ///< Task Startup Sequence Function #5: Start Fault Monitor Task
};

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     Queue_StartSequence_Size
 * @brief   Size of the task list covering all user-task managed by the OS
 * @details
 *  The size of the application task array TaskList needs to be known by the 
 * operating system for runtime control. This variable does not have to be 
 * updated by users. The size of the array will be automatically updated at 
 * compile time.
 **********************************************************************************/
volatile uint16_t Queue_InitializeSequence_Size = (sizeof(Queue_InitializeSequence)/sizeof(Queue_InitializeSequence[0])); 

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     Queue_StopSequence
 * @brief   Function pointer array listing all user-task start-up functions
 * @details
 *  The Start Sequence task list covers all user-task Start functions. These
 * tasks will be called after the user-task Initialize functions have been
 * executed. It is recommended to structure the code of user-tasks in a way
 * that the Start function puts the task and all related global variables and
 * data objects into a defined, initial condition and enables all required
 * features.
 * 
 * The list will be executed by the operating system in order of appearance. 
 * Hence, lower indices will be called before higher indices. This allows 
 * programmers to define a deterministic startup sequence of the user application
 * firmware.
 **********************************************************************************/
volatile struct APPLICATION_TASK_s* Queue_StopSequence[] =
{
    &appPowerSupply,    ///< Task Startup Sequence Function #0: Stop Power Supply Control Task
    &appFaultMonitor,   ///< Task Startup Sequence Function #1: Stop Fault Monitor Task
//    &appGui,             ///< Task Startup Sequence Function #5: Start GUI Task
    &appPushButton,     ///< Task Startup Sequence Function #2: Stop Push-Button Task
    &appLcd,            ///< Task Startup Sequence Function #3: Stop LCD Task
    &appLed            ///< Task Startup Sequence Function #4: Stop LED Task
    
};

/***********************************************************************************
 * @ingroup application-layer-user-tasks-configuration
 * @var     Queue_StartSequence_Size
 * @brief   Size of the task list covering all user-task managed by the OS
 * @details
 *  The size of the application task array TaskList needs to be known by the 
 * operating system for runtime control. This variable does not have to be 
 * updated by users. The size of the array will be automatically updated at 
 * compile time.
 **********************************************************************************/
volatile uint16_t Queue_StopSequence_Size = (sizeof(Queue_StopSequence)/sizeof(Queue_StopSequence[0])); 



// end of file
