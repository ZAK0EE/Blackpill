#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include <stdio.h>
#include "assertparam.h"
#include "HAL/Led/Led.h"


void assert_failed(uint8_t* file, uint32_t line)
{
    volatile int x;
    while(1){x++;}
}

int main()
{


    RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOA);
    LED_Init();

    volatile int x;
      while (1)
    {
        LED_setLedState(0, LED_ON);
        LED_setLedState(0, LED_OFF);

        LED_setLedState(1, LED_ON);
        LED_setLedState(1, LED_OFF);        

    } 
    return 0;
}