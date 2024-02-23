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

int main()
{


    RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOA);
    LED_Init();
    Switch_init();

    volatile int x;
      while (1)
    {

        if(Switch_getSwitchState(SwWITCH_LEDTOGGLE) == SWITCH_PRESSED)
        {
            LED_setLedState(LED_RED, LED_ON);
        }
        else
        {
            LED_setLedState(LED_RED, LED_OFF);
        }
        for(int i=0;i<100000;i++)
        {
            x++;
        }
    } 
    return 0;
}