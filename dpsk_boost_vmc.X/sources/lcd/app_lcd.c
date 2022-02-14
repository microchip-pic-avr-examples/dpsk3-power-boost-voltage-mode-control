/*
 * File:   app_lcd.c
 * Author: M91406
 *
 * Created on March 12, 2020, 12:10 PM
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types header file
#include <stdbool.h> // include standard boolean types header file
#include <stddef.h> // include standard definition types header file
#include <math.h> // include standard math library header file

#include "lcd/app_lcd.h"

// Additional header files required by this task
#include "config/apps.h"
#include "config/hal.h"

// PRIVATE VARIABLE DELARATIONS

volatile struct LCD_s lcd;      // declare one LCD data object

/***********************************************************************************
 * @ingroup app-layer-lcd-properties-private
 * @{
 * @var lcd_cnt
 * @brief  LCD driver time-base counter 
 * @details
 *  The LCD driver screen update is performed with a fixed frequency generated 
 *  by counting task scheduler ticks. The time-base counter 'lcd_cnt' is 
 *  incremented with every task scheduler call of function appLCD_Execute().
 *  If the time-base counter value matches or exceeds the constant user value
 *  defined by LCD_STARTUP, the startup screen will be switched to the first
 *  default LCD screen and regular screen updates will be performed.
 *  If the time-base counter value matches or exceeds the constant user value
 *  defined by LCD_STARTUP, the screen update will be performed.
 * 
 **********************************************************************************/
volatile uint16_t lcd_cnt = 0;  ///< Local counter used to trigger LCD refresh event

/** @} */ // end of group app-layer-lcd-properties-private

/***********************************************************************************
 * @ingroup app-layer-lcd-properties-private
 * @{
 * @def LCD_STARTUP
 * @brief Startup screen delay compare value
 * @details
 *  Period counter compare value determining how long the startup screen will be shown
 ***********************************************************************************/
#define LCD_STARTUP   14     ///< Value of 14 scheduler call ticks equals a period of 3 seconds

/** @} */ // end of group app-layer-lcd-properties-private

/***********************************************************************************
 * @ingroup app-layer-lcd-properties-private
 * @{
 * @def LCD_REFRESH
 * @brief Screen refresh delay compare value
 * @details
 *  Period counter compare value determining the LCD refresh rate
 ***********************************************************************************/
#define LCD_REFRESH   0      ///< Value of 0 scheduler call ticks equals a period of 200 milliseconds

/** @} */ // end of group app-layer-lcd-properties-private

/***********************************************************************************
 * @ingroup app-layer-lcd-properties-private
 * @{
 * @def LCD_NO_OF_SCREENS
 * @brief Number of screens which can be selected
 * @details
 *  This application supports multiple different screens which can be selected by
 *  the user to display different runtime data fields.
 ***********************************************************************************/
#define LCD_NO_OF_SCREENS   4   ///< Number of screens which can be selected

/** @} */ // end of group app-layer-lcd-properties-private

/*********************************************************************************
 * @ingroup app-layer-lcd-functions-public
 * @fn volatile uint16_t appLCD_Initialize(void)
 * @brief  Initializes the LC display
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This function initializes the LC display driver data object and 
 *  loads the startup screen.
 *
 **********************************************************************************/

volatile uint16_t appLCD_Initialize(void) 
{
    volatile uint16_t retval = 1;
    
    if (lcd.refresh == 0)
        lcd.refresh = LCD_STARTUP;
    
    lcd.screens = LCD_NO_OF_SCREENS;
    
    dev_Lcd_Initialize();
    PrintLcd(0, "%s", FIRMWARE_TITLE);
    PrintLcd(1, "%s", FIRMWARE_NAME);

    lcd_cnt = 0;
    lcd.enabled = false;
    
    return(retval);
}

/*********************************************************************************
 * @ingroup app-layer-lcd-functions-public
 * @fn volatile uint16_t appLCD_Execute(void)
 * @brief  Refreshes the LC display
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This function is frequently called by the task scheduler automatically
 *  updating currently displayed data and/or loading the most recent screen
 *  if a screen switch has been triggered by externally.
 *
 **********************************************************************************/

volatile uint16_t appLCD_Execute(void) 
{
    volatile uint16_t retval = 1;
    volatile float vi=0.0, vo=0.0, isns=0.0, temp=0.0;

    DBGPIN1_Set();
    
    // IF LCD output is disabled, exit here
    if(!lcd.enabled)
        return(retval);
    
    // If REFRESH period has expired, update LCD contents
    if(++lcd_cnt >= lcd.refresh) {
        
        // Calculate output values
        vi = ((boost.data.v_in << 3) * ADC_GRANULARITY); // Scale ADC value to physical unit
        vi = (float)(int)(100.0 * vi);      // Rounding operation required to prevent display
        vi /= 100.0;                        // rounding issues around 9.99 and 10.0 � C

        // Input voltage display
        if((double)vi < 10.000)
            PrintLcd(0, "VIN     = %2.2f V", (double)vi);
        else
            PrintLcd(0, "VIN     = %2.1f V", (double)vi);

        switch (lcd.screen)
        {
            case 1:     // Show Temperature Output

				temp = ((float)(boost.data.temp - TEMP_FB_ZERO) / TEMP_FB_SLOPE); // Scale ADC value to physical unit
				temp = (float)(int)(100.0 * temp);  // Rounding operation required to prevent display 
				temp /= 100.0;                      // rounding issues around 9.99 and 10.0 V

                if((double)temp < 10.000)
                    PrintLcd(1, "TEMP    = %2.2f C", (double)temp);
                else
                    PrintLcd(1, "TEMP    = %2.1f C", (double)temp);
                break;
            
            case 2:     // Show Current Output

				isns = ((boost.data.i_out * ADC_GRANULARITY) /  BOOST_ISNS_FEEDBACK_GAIN); // Scale ADC value to physical unit

                if((double)isns < 1.000)
                {
                    isns *= 1000.0;
                    PrintLcd(1, "ISNS    = %3d mA", (int)isns);
                }
                else
                {
                    PrintLcd(1, "ISNS    = %1.2f A", (double)isns);
                }
                break;

            case 3:     // Firmware Version Number
                PrintLcd(1, "FW:  v%s", FIRMWARE_VERSION_STRING);
                break;

            default:    // Output voltage display
                
                vo = ((boost.data.v_out << 3) * ADC_GRANULARITY); // Scale ADC value to physical unit

                if((double)vo < 10.000)
                    PrintLcd(1, "VOUT    = %2.2f V", (double)vo);
                else
                    PrintLcd(1, "VOUT    = %2.1f V", (double)vo);

                break;
        }
        
        // Add Error Indicators
        if ((lcd.screen<lcd.screens) && (boost.status.bits.fault_active))
        {
            if (fltobj_BoostUVLO.Status.bits.FaultStatus)
                dev_Lcd_WriteStringXY(4, 1, "(UV)");
            else if (fltobj_BoostOVLO.Status.bits.FaultStatus)
                dev_Lcd_WriteStringXY(4, 1, "(OV)");
            else if (fltobj_BoostRegErr.Status.bits.FaultStatus)
                dev_Lcd_WriteStringXY(4, 1, "(RE)");
            else if (fltobj_BoostOCP.Status.bits.FaultStatus)
                dev_Lcd_WriteStringXY(4, 1, "(OC)");
            else 
                dev_Lcd_WriteStringXY(4, 1, "(LA)");
        }

        // Trigger LCD Refresh
        lcd.refresh = LCD_REFRESH;
        lcd_cnt = 0; // Reset internal interval counter
    }

    DBGPIN1_Clear();
    
    return(retval);
}

/*********************************************************************************
 * @ingroup app-layer-lcd-functions-public
 * @fn volatile uint16_t appLCD_Start(void)
 * @brief  Enables the periodic refresh of the LC display content
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This function is enables the periodic display refresh executed by function
 *  'appLCD_Execute'. Until the LCD driver is enabled, the startup screen will
 *  set by function 'appLCD_Initialize' be shown.
 *
 **********************************************************************************/

volatile uint16_t appLCD_Start(void) 
{
    volatile uint16_t retval = 1;
    
    lcd.enabled = true;
    retval &= (uint16_t)(lcd.enabled);
    
    return(retval);
}

/*********************************************************************************
 * @ingroup app-layer-lcd-functions-public
 * @fn volatile uint16_t appLCD_Dispose(void)
 * @brief  Unloads the LC display data object and resources
 * @param  void
 * @return unsigned int (0=failure, 1=success)
 * @details
 *  This function unloads the LC display data object and frees its resources.
 *  The LCD_s data object of this display needs to be reinitialized before 
 *  the LC display can be used again.
 *
 **********************************************************************************/

volatile uint16_t appLCD_Dispose(void) 
{
    volatile uint16_t retval = 1;
    
    /* PLACE DISPOSE CODE HERE */

    return(retval);
}

// end of file
