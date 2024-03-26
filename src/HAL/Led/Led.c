/**
 * @file Led.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Implementation file for LED module.
 * @version 0.1
 * @date 2024-02-23
 * @copyright Copyright (c) 2024
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LED.h"
#include "Led_cfg.h"
#include "MCAL/GPIO/GPIO.h"
#include "assertparam.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/**
 * @brief Check if the LED ID is valid.
 */
#define IS_LED_ID_VALID(ID)    ((ID) < _NUM_OF_LEDS)

/**
 * @brief Check if the LED active type is valid.
 */
#define IS_LED_ACTIVE_TYPE(TYPE)    (((TYPE) == LED_ACTIVEHIGH) || ((TYPE) == LED_ACTIVELOW))

/**
 * @brief Check if the LED state is valid.
 */
#define IS_LED_STATE(STATE)    (((STATE) == LED_OFF) || ((STATE) == LED_ON))

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

LED_Error_t LED_Init(void)
{
    LED_Error_t RetErrorStatus = LED_OK;

    /* Initialize each LED based on the configuration */
    GPIO_PinConfig_t CurrentPin;
    for (uint32_t LedCounter = 0; LedCounter < (uint32_t) _NUM_OF_LEDS; LedCounter++)
    {
        LED_Config_t *CurrentLedConfig = &LED_Configs[LedCounter];
        
        /* Parameters validation */
        assert_param(IS_LED_ACTIVE_TYPE(CurrentLedConfig->ActiveType));
        assert_param(IS_LED_STATE(CurrentLedConfig->LedInitState));

        /* Each pin initialization */
        CurrentPin.Port = (GPIO_Port_t)CurrentLedConfig->PortID;
        CurrentPin.PinNumber = (GPIO_Pin_t)CurrentLedConfig->PinNum;
        CurrentPin.PinSpeed = GPIO_SPEED_MEDIUM;
        CurrentPin.PinMode = (CurrentLedConfig->ActiveType == LED_ACTIVEHIGH ) ?
                     GPIO_MODE_OUTPUT_PUSHPULL_NOPULL : GPIO_MODE_OUTPUT_PUSHPULL_PULLUP;

        GPIO_initPin(&CurrentPin);

        /* Determine Pin is high or low based on the active type of the LED*/
        GPIO_PinState_t PinState = (GPIO_PinState_t)(CurrentLedConfig->LedInitState ^ (LED_State_t)CurrentLedConfig->ActiveType);

        GPIO_setPinValue(CurrentPin.Port, CurrentPin.PinNumber, PinState);
    }

    return RetErrorStatus;
}

LED_Error_t LED_setLedState(uint8_t LedID, LED_State_t LedState)
{
    /* Parameters validation */
    assert_param(IS_LED_ID_VALID(LedID));
    assert_param(IS_LED_STATE(LedState));


    uint8_t PortID = LED_Configs[LedID].PortID;
    uint8_t PinNum = LED_Configs[LedID].PinNum;
    LED_ActiveType_t ActiveType = LED_Configs[LedID].ActiveType;

    GPIO_PinState_t PinState = (GPIO_PinState_t)(LedState ^ (LED_State_t)ActiveType);

    GPIO_setPinValue((GPIO_Port_t)PortID, (GPIO_Pin_t)PinNum, PinState);

    return LED_OK;
}

LED_State_t LED_getLedState(uint8_t LedID)
{
    /* Parameters validation */
    assert_param(IS_LED_ID_VALID(LedID));

    uint8_t PortID = LED_Configs[LedID].PortID;
    uint8_t PinNum = LED_Configs[LedID].PinNum;
    LED_ActiveType_t ActiveType = LED_Configs[LedID].ActiveType;

    LED_State_t LedState = GPIO_getPinValue((GPIO_Port_t)PortID, (GPIO_Pin_t)PinNum ^ ActiveType);


    return LedState;
}
