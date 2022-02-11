/*
 * File:   app_fault_monitor_config.c
 * Author: M91406
 *
 * Created on July 15, 2021, 4:06 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "config/hal.h" // include hardware abstraction layer header file
#include "config/apps.h" // include application layer abstraction layer header file

/********************************************************************
 * @var struct FAULT_OBJECT_s fltobj_BoostUVLO  
 * @ingroup app-layer-fault-monitor-properties-public
 * @brief Under Voltage Lock Out Fault Object
 * @details
 * This fault object monitors the input voltage of the power supply
 * scanning for conditions violating the minimum required input
 * voltage level for the specified amount of time.
 *******************************************************************/

volatile struct FAULT_OBJECT_s fltobj_BoostUVLO = 
{
    .Status.bits.FaultActive = true,                        // Set fault condition flag (must be cleared by fault check)
    .Status.bits.FaultStatus = true,                        // Set fault flag (must be cleared by fault check)
    .Status.bits.CompareType = FLTCMP_LESS_THAN,            // Select Compare-Type
    .Status.bits.Enabled = true,                            // Enable fault checks

    .SourceObject.ptrObject = &boost.data.v_in,              // Set pointer to variable to monitor
    .SourceObject.bitMask = 0xFFFF,                         // Compare all bits of SOURCE (no bit filter)
    .ReferenceObject.ptrObject = NULL,                      // Clear pointer to "compare against" variable 
    .ReferenceObject.bitMask = 0xFFFF,                      // Clear pointer to "compare against" variable 

    .TripResponse.compareThreshold = BOOST_VIN_UVLO_TRIP,    // Set fault trip level
    .TripResponse.eventThreshold = BOOST_UVLO_TDLY,          // Set counter level at which a FAULT condition will be tripped
    .TripResponse.ptrResponseFunction = &appPowerSupply_Suspend, // Set pointer to user-function which should be called when a FAULT is tripped

    .RecoveryResponse.compareThreshold = BOOST_VIN_UVLO_RELEASE, // Set fault recovery level
    .RecoveryResponse.eventThreshold = BOOST_UVLO_RDLY,      // Set counter level at which a FAULT condition will be cleared
    .RecoveryResponse.ptrResponseFunction = NULL            // Clear recovery function pointer
};

/********************************************************************
 * @var struct FAULT_OBJECT_s fltobj_BoostOVLO  
 * @ingroup app-layer-fault-monitor-properties-public
 * @brief Over Voltage Lock Out Fault Object
 * @details
 * This fault object monitors the input voltage of the power supply
 * scanning for conditions exceeding the maximum allowed input
 * voltage level for the specified amount of time.
 *******************************************************************/
volatile struct FAULT_OBJECT_s fltobj_BoostOVLO = {

    .SourceObject.ptrObject = &boost.data.v_in,              // Set pointer to variable to monitor
    .SourceObject.bitMask = 0xFFFF,                         // Compare all bits of SOURCE (no bit filter)
    .ReferenceObject.ptrObject = NULL,                      // Clear pointer to "compare against" variable 
    .ReferenceObject.bitMask = 0xFFFF,                      // Compare all bits of SOURCE (no bit filter)
    .Status.bits.CompareType = FLTCMP_GREATER_THAN,         // Select Compare-Type

    .TripResponse.compareThreshold = BOOST_VIN_OVLO_TRIP,    // Set fault trip level
    .TripResponse.eventThreshold = BOOST_OVLO_TDLY,          // Set counter level at which a FAULT condition will be tripped
    .TripResponse.ptrResponseFunction = &appPowerSupply_Suspend, // Set pointer to user-function which should be called when a FAULT is tripped

    .RecoveryResponse.compareThreshold = BOOST_VIN_OVLO_RELEASE,   // Set fault recovery level
    .RecoveryResponse.eventThreshold = BOOST_OVLO_RDLY,      // Set counter level at which a FAULT condition will be cleared
    .RecoveryResponse.ptrResponseFunction = NULL,           // Clear recovery function pointer
    
    .Counter = 0,                                           // Clear fault event counter
    .Status.bits.FaultActive = true,                        // Set fault condition flag (must be cleared by fault check)
    .Status.bits.FaultStatus = true,                        // Set fault flag (must be cleared by fault check)

    .Status.bits.Enabled = true                             // Enable fault checks

};

/********************************************************************
 * @var struct FAULT_OBJECT_s fltobj_BoostOCP  
 * @ingroup app-layer-fault-monitor-properties-public
 * @brief Over Current Protection Fault Object
 * @details
 * This fault object monitors the average output current of the
 * power supply scanning for conditions exceeding the maximum
 * allowed output current level for the specified amount of time.
 *******************************************************************/
volatile struct FAULT_OBJECT_s fltobj_BoostOCP = {

    .SourceObject.ptrObject = &boost.data.i_out,             // Set pointer to variable to monitor
    .SourceObject.bitMask = 0xFFFF,                         // Compare all bits of SOURCE (no bit filter)
    .ReferenceObject.ptrObject = NULL,                      // Clear pointer to "compare against" variable 
    .ReferenceObject.bitMask = 0xFFFF,                      // Compare all bits of SOURCE (no bit filter)
    .Status.bits.CompareType = FLTCMP_GREATER_THAN,         // Select Compare-Type

    .TripResponse.compareThreshold = BOOST_ISNS_OCL,         // Set fault trip level
    .TripResponse.eventThreshold = BOOST_OCP_TDLY,           // Set counter level at which a FAULT condition will be tripped
    .TripResponse.ptrResponseFunction = &appPowerSupply_Suspend, // Set pointer to user-function which should be called when a FAULT is tripped

    .RecoveryResponse.compareThreshold = BOOST_ISNS_OCL_RELEASE, // Set fault recovery level
    .RecoveryResponse.eventThreshold = BOOST_OCP_RDLY,       // Set counter level at which a FAULT condition will be cleared
    .RecoveryResponse.ptrResponseFunction = NULL,           // Clear recovery function pointer
    
    .Counter = 0,                                           // Clear fault event counter
    .Status.bits.FaultActive = false,                       // Set fault condition flag (must be cleared by fault check)
    .Status.bits.FaultStatus = false,                       // Set fault flag (must be cleared by fault check)
    
    .Status.bits.Enabled = false                            // Enable fault checks    

};

/********************************************************************
 * @var struct FAULT_OBJECT_s fltobj_BoostRegErr  
 * @ingroup app-layer-fault-monitor-properties-public
 * @brief Regulation Error Fault Object
 * @details
 * This fault object monitors the deviation between voltage reference
 * and most recent output voltage of the power supply scanning for
 * conditions where a maximum allowed deviation is exceeded for the
 * specified amount of time.
 *******************************************************************/ 
volatile struct FAULT_OBJECT_s fltobj_BoostRegErr = {

    .SourceObject.ptrObject = &boost.data.v_out,             // Set pointer to variable to monitor
    .SourceObject.bitMask = 0xFFFF,                         // Compare all bits of SOURCE (no bit filter)
    .ReferenceObject.ptrObject = &boost.set_values.v_ref,    // Set pointer to "compare against" variable 
    .ReferenceObject.bitMask = 0xFFFF,                      // Compare all bits of Reference (no bit filter)
    .Status.bits.CompareType = FLTCMP_GREATER_THAN,         // Select Compare-Type

    .TripResponse.compareThreshold = BOOST_VOUT_DEV_TRIP,    // Set fault trip level
    .TripResponse.eventThreshold = BOOST_REGERR_TDLY,        // Set counter level at which a FAULT condition will be tripped
    .TripResponse.ptrResponseFunction = &appPowerSupply_Suspend, // Set pointer to user-function which should be called when a FAULT is tripped

    .RecoveryResponse.compareThreshold = BOOST_VOUT_DEV_RELEASE, // Set fault recovery level
    .RecoveryResponse.eventThreshold = BOOST_REGERR_RDLY,    // Set counter level at which a FAULT condition will be cleared
    .RecoveryResponse.ptrResponseFunction = NULL,           // Clear recovery function pointer
    
    .Counter = 0,                                           // Clear fault event counter
    .Status.bits.FaultActive = false,                       // Set fault condition flag (must be cleared by fault check)
    .Status.bits.FaultStatus = false,                       // Set fault flag (must be cleared by fault check)

    .Status.bits.Enabled = false                            // Disable fault checks at startup

};

/*********************************************************************************
 * @ingroup app-layer-fault-monitor-properties-public
 * @var     FaultObjectList
 * @brief   Fault object list
 * @details
 *  This list is grouping all user defined fault objects in one list, which
 *  is used by the fault handler for initialization, disposal and scan for 
 *  fault conditions.
 **********************************************************************************/

volatile struct FAULT_OBJECT_s* FaultObjectList[] = {
    &fltobj_BoostUVLO,
    &fltobj_BoostOVLO,
    &fltobj_BoostOCP,
    &fltobj_BoostRegErr
};

/*********************************************************************************
 * @ingroup app-layer-fault-monitor-properties-public
 * @var     FaultObjectList_size
 * @brief   Fault object list size
 * @details
 *  This variable is used to determine the number of user specified fault objects.
 *  The size of the fault object list is required for all fault monitor function 
 *  calls.
 **********************************************************************************/

volatile uint16_t FaultObjectList_size = (sizeof(FaultObjectList)/sizeof(FaultObjectList[0]));


// end of file
