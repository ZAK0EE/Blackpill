/**
 * @file Scheduler.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "Scheduler.h"
#include "Scheduler_cfg.h"
#include "MCAL/SysTick/SysTick.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define SCHED_TICK_TIMEMS 1


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


typedef struct
{
	Sched_Runnable_Config_t *Runnable;
	uint32_t RemainingTimeMS;
}RunnableInfo_t;




/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
extern Sched_Runnable_Config_t Sched_Runnables[_NUM_OF_RUNNABLES];

static uint32_t PendingTicks = 0;
static RunnableInfo_t rinfo[_NUM_OF_RUNNABLES];


/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void TickCallBack(void)
{
	PendingTicks++;
}

static void Scheduler(void)
{
	uint32_t idx;
	for(idx = 0; idx < _NUM_OF_RUNNABLES; idx++)
	{

		if(rinfo[idx].Runnable && rinfo[idx].Runnable->CallBack && rinfo[idx].RemainingTimeMS == 0)
		{

			rinfo[idx].Runnable->CallBack();

			rinfo[idx].RemainingTimeMS = rinfo[idx].Runnable->PeriodicityMS;
		}

		rinfo[idx].RemainingTimeMS -= SCHED_TICK_TIMEMS;

	}    
}
/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


void Sched_init(void)
{
    PendingTicks = 0;

    /* Initializing Systick */
    SysTick_Config_t config = 
    {
        .CallbackFunction = TickCallBack,
        .ClockSource = SYSTICK_CLK_AHB,
        .ExceptionState = SYSTICK_EXCEPTION_ENABLED,
    };
    SysTick_init(&config);

    /* Initializing runnables states */
    uint32_t idx;
	for(idx = 0; idx < _NUM_OF_RUNNABLES; idx++)
    {
        rinfo[idx].Runnable = &Sched_Runnables[idx];
		rinfo[idx].RemainingTimeMS = rinfo[idx].Runnable->DelayMS;
		      
    }
}


void Sched_start(void)
{
    SysTick_startTimerMS(SCHED_TICK_TIMEMS);
	while(1)
	{
		if(PendingTicks)
		{
			PendingTicks--;
			Scheduler();
		}
	}
}