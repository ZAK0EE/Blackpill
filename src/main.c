#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include <stdio.h>
#include "assertparam.h"
#include "HAL/Led/Led.h"
#include "HAL/Led/Led_cfg.h"
#include "HAL/Switch/Switch.h"
#include "HAL/Switch/Switch_cfg.h"
#include "Services/Scheduler/Scheduler.h"
void assert_failed(uint8_t* file, uint32_t line)
{
    volatile int x;
    while(1){x++;}
}
#include "MCAL/NVIC/NVIC.h"
void EXTI0_IRQHandler()
{
    volatile int x;

    NVIC_IsActive_t y;
    y = NVIC_getActiveStatus(NVIC_IRQ_EXTI0);    
    while(1){x++;}
}

#include "MCAL/SysTick/SysTick.h"

void ToggleRedLed1MS(void)
{
    static int tog = 1;
    if(tog)
          LED_setLedState(LED_RED, LED_ON);
    else
          LED_setLedState(LED_RED, LED_OFF);

    tog ^= 1;
   
}
void ToggleYellowLed1MS(void)
{
    static int tog = 1;
    if(tog)
          LED_setLedState(LED_YELLOW, LED_ON);
    else
          LED_setLedState(LED_YELLOW, LED_OFF);

    tog ^= 1;
   
}
void ToggleGreenLed1MS(void)
{
    static int tog = 1;
    if(tog)
          LED_setLedState(LED_GREEN, LED_ON);
    else
          LED_setLedState(LED_GREEN, LED_OFF);

    tog ^= 1;
   
}
int main()
{
    RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOA);
    LED_Init();
    //LED_setLedState(LED_RED, LED_ON);
    Sched_init();
    Sched_start();

    
    while(1);


    return 0;
}