#include "MCAL/RCC/RCC.h"
#include "MCAL/stm32f401.h"
#include <stdio.h>
#include "assertparam.h"

void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}

int main()
{
    RCC_selectSystemClock(RCC_SYSTEMCLOCK_HSI);
    volatile int x;
    volatile int y;
    x = y = 0;
    while(1)
    {
        x = y;
        y++;
        x++;
        if(x > y)
        {
            x++;
        }
        else if (y > x)
        {
            x++;
        }
        y = x + y;

    }
    return 0;
}