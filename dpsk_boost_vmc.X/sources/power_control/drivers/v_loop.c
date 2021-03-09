/* *********************************************************************************
 * PowerSmart™ Digital Control Library Designer, Version 0.9.12.672
 * *********************************************************************************
 * 3p3z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * *********************************************************************************
 *
 *  Controller Type:    3P3Z - Basic Voltage Mode Compensator
 *  Sampling Frequency: 500000 Hz
 *  Fixed Point Format: Q15
 *  Scaling Mode:       4 - Fast Floating Point Coefficient Scaling
 *  Input Gain:         0.12531328320802
 *
 * *********************************************************************************
 * CGS Version:         3.0.7
 * CGS Date:            03/07/2021
 * *********************************************************************************
 * User:                M91406
 * Date/Time:           03/08/2021 16:08:18
 * ********************************************************************************/

#include "v_loop.h"

/* *********************************************************************************
 * Data Arrays:
 * ============
 *
 * This source file declares the default parameters of the z-domain compensation
 * filter. The NPNZ16b_s data structure contains two pointers to A- and B-
 * coefficient arrays and two pointers to control and error history arrays.
 *
 * For optimized data processing during DSP computations, these arrays must be
 * located in specific memory locations (X-space for coefficient arrays and
 * Y-space for control and error history arrays).
 *
 * The following declarations are used to define the array data contents, their
 * length and memory location. These declarations are made publicly accessible
 * through extern declarations in header file v_loop.h
 * ********************************************************************************/

volatile struct V_LOOP_CONTROL_LOOP_COEFFICIENTS_s __attribute__((space(xmemory), near)) v_loop_coefficients; // A/B-Coefficients
volatile uint16_t v_loop_ACoefficients_size = (sizeof(v_loop_coefficients.ACoefficients)/sizeof(v_loop_coefficients.ACoefficients[0])); // A-coefficient array size
volatile uint16_t v_loop_BCoefficients_size = (sizeof(v_loop_coefficients.BCoefficients)/sizeof(v_loop_coefficients.BCoefficients[0])); // B-coefficient array size

volatile struct V_LOOP_CONTROL_LOOP_HISTORIES_s __attribute__((space(ymemory), far)) v_loop_histories; // Control/Error Histories
volatile uint16_t v_loop_ControlHistory_size = (sizeof(v_loop_histories.ControlHistory)/sizeof(v_loop_histories.ControlHistory[0])); // Control history array size
volatile uint16_t v_loop_ErrorHistory_size = (sizeof(v_loop_histories.ErrorHistory)/sizeof(v_loop_histories.ErrorHistory[0])); // Error history array size

/* *********************************************************************************
 * Pole&Zero Placement:
 * *********************************************************************************
 *
 *    fP0:    360 Hz
 *    fP1:    40000 Hz
 *    fP2:    160000 Hz
 *    fZ1:    1810 Hz
 *    fZ2:    3833 Hz
 *
 * *********************************************************************************
 * Filter Coefficients and Parameters:
 * ********************************************************************************/

volatile int32_t v_loop_ACoefficients [3] =
{
    0x6620FFFF, // Coefficient A1 will be multiplied with controller output u(n-1)
    0xB3F60000, // Coefficient A2 will be multiplied with controller output u(n-2)
    0x982E0009  // Coefficient A3 will be multiplied with controller output u(n-3)
};

volatile int32_t v_loop_BCoefficients [4] =
{
    0x6DFEFFFD, // Coefficient B0 will be multiplied with error input e(n-0)
    0x99A9FFFD, // Coefficient B1 will be multiplied with error input e(n-1)
    0x9221FFFD, // Coefficient B2 will be multiplied with error input e(n-2)
    0x6676FFFD  // Coefficient B3 will be multiplied with error input e(n-3)
};

// Coefficient normalization factors
volatile int16_t v_loop_pre_scaler = 3;           // Bit-shift value used to perform input value normalization
volatile int16_t v_loop_post_shift_A = 0;         // Bit-shift value A used to perform control output value backward normalization
volatile int16_t v_loop_post_shift_B = 0;         // Bit-shift value B used to perform control output value backward normalization
volatile fractional v_loop_post_scaler = 0x0000;  // Q15 fractional factor used to perform control output value backward normalization

// P-Term Coefficient for Plant Measurements
volatile int16_t v_loop_pterm_factor = 0x6188;    // Q15 fractional of the P-Term factor
volatile int16_t v_loop_pterm_scaler = 0xFFFF;    // Bit-shift scaler of the P-Term factor


// User-defined NPNZ16b_s controller data object
volatile struct NPNZ16b_s v_loop;                 // user-controller data object

/* ********************************************************************************/

/* *********************************************************************************
 * Controller Initialization:
 * ==========================
  *
 * Public controller initialization function loading known default settings
 * into the NPNZ16b data structure.
 *
 * ********************************************************************************/

volatile uint16_t v_loop_Initialize(volatile struct NPNZ16b_s* controller)
{
    volatile uint16_t i=0;

    // Initialize controller data structure at runtime with pre-defined default values
    controller->status.value = NPNZ_STATUS_CLEAR; // clear all status flag bits (will turn off execution))

    controller->Filter.ptrACoefficients = &v_loop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
    controller->Filter.ptrBCoefficients = &v_loop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
    controller->Filter.ptrControlHistory = &v_loop_histories.ControlHistory[0]; // initialize pointer to control history array
    controller->Filter.ptrErrorHistory = &v_loop_histories.ErrorHistory[0]; // initialize pointer to error history array
    controller->Filter.normPostShiftA = v_loop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
    controller->Filter.normPostShiftB = v_loop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
    controller->Filter.normPostScaler = v_loop_post_scaler; // initialize control output value normalization scaling factor
    controller->Filter.normPreShift = v_loop_pre_scaler; // initialize A-coefficients/single bit-shift scaler
    
    controller->Filter.ACoefficientsArraySize = v_loop_ACoefficients_size; // initialize A-coefficients array size
    controller->Filter.BCoefficientsArraySize = v_loop_BCoefficients_size; // initialize A-coefficients array size
    controller->Filter.ControlHistoryArraySize = v_loop_ControlHistory_size; // initialize control history array size
    controller->Filter.ErrorHistoryArraySize = v_loop_ErrorHistory_size; // initialize error history array size

    // Load default set of A-coefficients from user RAM into controller A-array located in X-Space
    for(i=0; i<controller->Filter.ACoefficientsArraySize; i++)
    {
        v_loop_coefficients.ACoefficients[i] = v_loop_ACoefficients[i]; // Load coefficient A1 value into v_loop coefficient data space
        v_loop_coefficients.ACoefficients[i] = v_loop_ACoefficients[i]; // Load coefficient A2 value into v_loop coefficient data space
        v_loop_coefficients.ACoefficients[i] = v_loop_ACoefficients[i]; // Load coefficient A3 value into v_loop coefficient data space
    }

    // Load default set of B-coefficients from user RAM into controller B-array located in X-Space
    for(i=0; i<controller->Filter.BCoefficientsArraySize; i++)
    {
        v_loop_coefficients.BCoefficients[i] = v_loop_BCoefficients[i]; // Load coefficient B0 value into v_loop coefficient data space
        v_loop_coefficients.BCoefficients[i] = v_loop_BCoefficients[i]; // Load coefficient B1 value into v_loop coefficient data space
        v_loop_coefficients.BCoefficients[i] = v_loop_BCoefficients[i]; // Load coefficient B2 value into v_loop coefficient data space
        v_loop_coefficients.BCoefficients[i] = v_loop_BCoefficients[i]; // Load coefficient B3 value into v_loop coefficient data space
    }

    // Clear error and control histories of the 3P3Z controller
    v_loop_Reset(&v_loop);
    
    // Load P-Term factor and scaler into data structure
    controller->Filter.PTermFactor = v_loop_pterm_factor;
    controller->Filter.PTermScaler = v_loop_pterm_scaler;
    
    return(1);
}


//**********************************************************************************
// Download latest version of this tool here: https://areiter128.github.io/DCLD
//**********************************************************************************

