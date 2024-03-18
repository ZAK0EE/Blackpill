#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include <stdio.h>
#include "assertparam.h"
#include "HAL/Led/Led.h"
#include "HAL/Led/Led_cfg.h"
#include "HAL/Switch/Switch.h"
#include "HAL/Switch/Switch_cfg.h"
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

void ToggleLed1MS(void)
{
    static int tog = 1;
    if(tog)
          LED_setLedState(LED_RED, LED_ON);
    else
            LED_setLedState(LED_RED, LED_OFF);

    tog ^= 1;
    volatile int x;
   // while(1){x++;}    
}
int main()
{
     RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOA);
    LED_Init();
      LED_setLedState(LED_RED, LED_ON);
    SysTick_Config_t config = 
    {
        .CallbackFunction = ToggleLed1MS,
        .ClockSource = SYSTICK_CLK_AHB,
        .ExceptionState = SYSTICK_EXCEPTION_ENABLED,
    };
    SysTick_init(&config);
    SysTick_startTimerMS(1000);
    
    while(1);


    return 0;
}