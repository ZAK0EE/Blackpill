/**
 * @file TrafficLight.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "TrafficLight.h"
#include "HAL/Led/Led.h"





/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/



void TrafficLight_task(void)
{
    static int state = 0;
    static int prev = 0;
    
    switch(state)
    {
        case 0:
            LED_setLedState(LED_GREEN, LED_ON);
            LED_setLedState(LED_YELLOW, LED_OFF);
            LED_setLedState(LED_RED, LED_OFF);
            prev = state;
            state++;
            break;

        case 1:

            LED_setLedState(LED_GREEN, LED_OFF);
            LED_setLedState(LED_YELLOW, LED_ON);
            LED_setLedState(LED_RED, LED_OFF);
            if(prev == 0)
            {
                state++;  
            }
            else
            {
                prev = state;
                state--;
            }
            break;        
        case 2:
            LED_setLedState(LED_GREEN, LED_OFF);
            LED_setLedState(LED_YELLOW, LED_OFF);
            LED_setLedState(LED_RED, LED_ON);
            prev = state;
            state--; 
            break; 
    }
    


}