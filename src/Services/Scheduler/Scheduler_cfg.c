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
extern void ToggleGreenLed1MS(void);
extern void switchapp(void);
extern void Switch_Task_CheckState(void);
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

Sched_Runnable_Config_t Sched_Runnables[_NUM_OF_RUNNABLES] = 
{
    [SCHED_REDLEDTOG1MS]=
    {
        .CallBack = ToggleRedLed1MS,
        .DelayMS = 0,
        .PeriodicityMS = 1000,
    },
    [SCHED_YELLOWLEDTOG1MS]=
    {
        .CallBack = ToggleYellowLed1MS,
        .DelayMS = 0,
        .PeriodicityMS = 500,
    },
    [SCHED_GREENLEDTOG1MS]=
    {
        .CallBack = switchapp,
        .DelayMS = 0,
        .PeriodicityMS = 50,
    }, 
    [SCHED_SWITCH15MS]=
    {
        .CallBack = Switch_Task_CheckState,
        .DelayMS = 0,
        .PeriodicityMS = 5,
    },            
};