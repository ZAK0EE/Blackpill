/**
 * @file Scheduler_cfg.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Scheduler.h"
#include "Scheduler_cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
extern void ToggleRedLed1MS(void);
extern void ToggleYellowLed1MS(void);
extern void SwitchToggle_task(void);
extern void Switch_Task_CheckState(void);
extern void TrafficLight_task(void);

extern void LCD_task(void);
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

Sched_Runnable_Config_t Sched_Runnables[_NUM_OF_RUNNABLES] = 
{


    // [SCHED_TRAFFICLIGHT]=
    // {
    //     .CallBack = TrafficLight_task,
    //     .DelayMS = 0,
    //     .PeriodicityMS = 1000,
    // },    
    [SCHED_LCD]=
    {
        .CallBack = LCD_task,
        .DelayMS = 0,
        .PeriodicityMS = 1,
    }             
};