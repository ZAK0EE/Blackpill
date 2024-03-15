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
int main()
{
    NVIC_IsActive_t volatile x = NVIC_N_ACTIVE;
    x = NVIC_getActiveStatus(NVIC_IRQ_EXTI0);
    NVIC_enableIRQ(NVIC_IRQ_EXTI0);
  //  NVIC_setPendingIRQ(NVIC_IRQ_EXTI0);
    NVIC_generateSWInterrupt(NVIC_IRQ_EXTI0);
    // RCC_enableAHB1Peripheral(RCC_AHB1PERIPHERAL_GPIOA);
    // LED_Init();
    // Switch_init();


    return 0;
}