/**
 * @file SwitchToggle.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "HAL/Switch/Switch.h"
#include  "HAL/Led/Led.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

static void ToggleGreenLed(void)
{
    static int tog = 1;
    if(tog)
          LED_setLedState(LED_GREEN, LED_ON);
    else
          LED_setLedState(LED_GREEN, LED_OFF);

    tog ^= 1;
   
}
void SwitchToggle_task(void)
{
    static Switch_StateType_t prevState = SWITCH_RELEASED;

    Switch_StateType_t state;
    state = Switch_getSwitchStateAsync(SWITCH_LEDTOGGLE);
    if(state != prevState && state == SWITCH_PRESSED)
    {
        ToggleGreenLed();
    }
    prevState = state;

}