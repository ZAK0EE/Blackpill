/**
 * @file Led.h
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Header file for LED module.
 * @version 0.1
 * @date 2024-02-23
 * @copyright Copyright (c) 2024
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <stdint.h>
#include "Led_cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Enumeration for LED-related errors.
 */
typedef enum {
    LED_OK,      /**< Operation successful */
    LED_NOK      /**< Operation not successful */
} LED_Error_t;

/**
 * @brief Enumeration for LED active types (active high/low).
 */
typedef enum {
    LED_ACTIVEHIGH, /**< Active high configuration */
    LED_ACTIVELOW   /**< Active low configuration */
} LED_ActiveType_t;

/**
 * @brief Enumeration for LED states (on/off).
 */
typedef enum {
    LED_OFF, /**< LED is OFF */
    LED_ON,  /**< LED is ON */
} LED_State_t;

/**
 * @brief Structure to hold LED configurations.
 */
typedef struct {
    uint8_t PortID;               /**< Port ID associated with the LED */
    uint8_t PinNum;               /**< Pin number associated with the LED */
    LED_ActiveType_t ActiveType;  /**< Active type of the LED (high/low) */
    LED_State_t LedInitState;     /**< Initial state of the LED(ON/OFF) */
} LED_Config_t;

/** Array to store LED configurations. Configurations should be set before calling LED_Init. */
extern LED_Config_t LED_Configs[_NUM_OF_LEDS];

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Initialize LEDs using the configurations in LED_Configs.
 * @return LED_Error_t Error status after initializing the LEDs.
 */
LED_Error_t LED_Init(void);

/**
 * @brief Turn on/off the specified LED.
 * @param LedID ID of the LED to control.
 * @param LedState State to be applied (LED_ON or LED_OFF).
 * @return LED_Error_t Error status after setting the LED state.
 */
LED_Error_t LED_setLedState(uint8_t LedID, LED_State_t LedState);

/**
 * @brief Get the state of the specified LED.
 * @param LedID ID of the LED to query.
 * @return LED_State_t State of the LED
 */
LED_State_t LED_getLedState(uint8_t LedID);

#endif // HAL_LED_LED_H_
