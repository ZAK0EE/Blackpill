#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include <stdio.h>
#include "assertparam.h"


void assert_failed(uint8_t* file, uint32_t line)
{
    volatile int x;
    while(1){x++;}
}

int main()
{
    GPIO_PinConfigTypeDef Pin0 =
    {
        .PinMode = GPIO_MODE_OUTPUT_PUSHPULL_PULLDOWN,
        .PinNumber = GPIO_PIN5,
        .Port = GPIO_GPIOC,
        .PinSpeed = GPIO_SPEED_MEDIUM,
    };

        GPIO_initPin(&Pin0);

    RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOC);
    for(int i = GPIO_PIN0; i <= GPIO_PIN15; i++)
    {
        Pin0.PinNumber = i;
        GPIO_initPin(&Pin0);
        GPIO_setPinValue(Pin0.Port, i, GPIO_PINSTATE_SET);


    }


    int x = 0;
      while (1)
    {
        GPIO_setPinValue(GPIO_GPIOA, GPIO_PIN0, GPIO_PINSTATE_SET);

        GPIO_setPinValue(GPIO_GPIOA, GPIO_PIN0, GPIO_PINSTATE_RESET);
    }  return 0;
}