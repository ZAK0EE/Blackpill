/**
 * @file LCDAPP.C
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LCDAPP.h"
#include "HAL/LCD/LCD.h"


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
uint32_t MyTime = 0;

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


/* Called every 100MS*/
void LCDAPP_task(void)
{
    static uint32_t states = 0;
    switch(states)
    {
        case 0:
        {
            LCD_setCursorPositionAsync(LCD1, 0, 5);
            LCD_setCursorPositionAsync(LCD2, 1, 0);
            MyTime = 0;            
            states++;

            break;
        }
        case 1:
        {
            if((LCD_getState(LCD1) == LCD_STATE_READY) && (LCD_getState(LCD2) == LCD_STATE_READY))
            {
                MyTime = 0;
                states++;
            }
            
            break;
        }
        case 2:
        {
            LCD_writeStringAsync(LCD1, "Test", 4);
            LCD_writeStringAsync(LCD2, "Noway", 5);
            states++;
            MyTime = 0;
            break;
        }
        case 3:
        {

            if((LCD_getState(LCD1) == LCD_STATE_READY) && (LCD_getState(LCD2) == LCD_STATE_READY) && (MyTime >= 50))
            {
                states = 0;
                MyTime = 0;
            }
            break;
        }
    
    }

    MyTime++;
}