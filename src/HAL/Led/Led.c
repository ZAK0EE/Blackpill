/**
 * @file Led.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Implementation file for LED module.
 * @version 0.1
 * @date 2024-02-23
 * @copyright Copyright (c) 2024
 */

#include "LED.h"
#include "Led_cfg.h"
#include "MCAL/GPIO/GPIO.h"


LED_Error_t LED_Init(void)
{
    LED_Error_t RetErrorStatus = LED_OK;

    GPIO_PinConfigTypeDef CurrentLed;
    for (uint32_t LedCounter = 0; LedCounter < (uint32_t) _NUM_OF_LEDS; LedCounter++)
    {
        LED_Config_t *CurrentLedConfig = &LED_Configs[LedCounter];

        CurrentLed.Port = (GPIO_PortTypeDef)CurrentLedConfig->PortID;
        CurrentLed.PinNumber = (GPIO_PinTypeDef)CurrentLedConfig->PinNum;
        CurrentLed.PinSpeed = GPIO_SPEED_MEDIUM;
        CurrentLed.PinMode = (CurrentLedConfig->ActiveType == LED_ACTIVEHIGH ) ?
                             GPIO_MODE_OUTPUT_PUSHPULL_PULLDOWN : GPIO_MODE_OUTPUT_PUSHPULL_PULLUP;

        GPIO_initPin(&CurrentLed);
    }

    return RetErrorStatus;
}

LED_Error_t LED_setLedState(uint8_t LedID, LED_State_t LedState)
{
    uint8_t PortID = LED_Configs[LedID].PortID;
    uint8_t PinNum = LED_Configs[LedID].PinNum;
    LED_ActiveType_t ActiveType = LED_Configs[LedID].ActiveType;

    GPIO_PinStateTypeDef PinState = (GPIO_PinStateTypeDef)(LedState ^ (LED_State_t)ActiveType);

    GPIO_setPinValue((GPIO_PortTypeDef)PortID, (GPIO_PinTypeDef)PinNum, PinState);

    return LED_OK;
}

LED_State_t LED_getLedState(uint8_t LedID)
{
    uint8_t PortID = LED_Configs[LedID].PortID;
    uint8_t PinNum = LED_Configs[LedID].PinNum;
    LED_ActiveType_t ActiveType = LED_Configs[LedID].ActiveType;

    LED_State_t LedState = GPIO_getPinValue((GPIO_PortTypeDef)PortID, (GPIO_PinTypeDef)PinNum ^ ActiveType);


    return LedState;
}
