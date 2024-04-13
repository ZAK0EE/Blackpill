#include <stdio.h>

#include "MCAL/RCC/RCC.h"
#include "assertparam.h"
#include "HAL/Led/Led.h"
#include "HAL/Switch/Switch.h"
#include "Services/Scheduler/Scheduler.h"
void assert_failed(uint8_t* file, uint32_t line)
{
    volatile int x;
    while(1){x++;}
}

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
#include "MCAL/GPIO/GPIO.h"
#include "HAL/LCD/LCD.h"
int main()
{
    RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOA);
    RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOB);



    //LCD_writeStringAsync(LCD1, "Anas", 4);
    LCD_init(0);

    Sched_init();
    Sched_start();

    
    while(1);

    return 0;
}