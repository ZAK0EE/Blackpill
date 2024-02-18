/**
 * @file GPIO.h
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Header file for General Purpose Input Output
 * @version 0.1
 * @date 2024-02-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/stm32f401.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Enumeration defining GPIO ports.
 *
 * This enumeration provides individual constants for GPIO ports from GPIOA to GPIOH.
 */
typedef enum
{
    GPIO_GPIOA, /**< GPIO port A. */
    GPIO_GPIOB, /**< GPIO port B. */
    GPIO_GPIOC, /**< GPIO port C. */
    GPIO_GPIOD, /**< GPIO port D. */
    GPIO_GPIOE, /**< GPIO port E. */
    GPIO_GPIOF, /**< GPIO port F. */
    GPIO_GPIOG, /**< GPIO port G. */
    GPIO_GPIOH  /**< GPIO port H. */
} GPIO_PortTypeDef;

/**
 * @brief Enumeration defining GPIO pin numbers.
 *
 * This enumeration provides individual constants for GPIO pin numbers from GPIO_PIN0 to GPIO_PIN15.
 *
 */
typedef enum
{
    GPIO_PIN0,   /**< GPIO pin number 0. */
    GPIO_PIN1,   /**< GPIO pin number 1. */
    GPIO_PIN2,   /**< GPIO pin number 2. */
    GPIO_PIN3,   /**< GPIO pin number 3. */
    GPIO_PIN4,   /**< GPIO pin number 4. */
    GPIO_PIN5,   /**< GPIO pin number 5. */
    GPIO_PIN6,   /**< GPIO pin number 6. */
    GPIO_PIN7,   /**< GPIO pin number 7. */
    GPIO_PIN8,   /**< GPIO pin number 8. */
    GPIO_PIN9,   /**< GPIO pin number 9. */
    GPIO_PIN10,  /**< GPIO pin number 10. */
    GPIO_PIN11,  /**< GPIO pin number 11. */
    GPIO_PIN12,  /**< GPIO pin number 12. */
    GPIO_PIN13,  /**< GPIO pin number 13. */
    GPIO_PIN14,  /**< GPIO pin number 14. */
    GPIO_PIN15   /**< GPIO pin number 15. */
} GPIO_PinTypeDef;

/**
 * @brief Enumeration defining GPIO pin modes, pull configurations, and output types.
 *
 * This enumeration provides constants for configuring GPIO pin modes, pull configurations, and output types.
 * The encoding is as follows:
 * - First Nibble: GPIO pin mode (Input, Output, or Alternate Function).
 * - Second Nibble: Pull configuration (No pull, Pull-up, or Pull-down).
 * - Third Nibble: Output type (Push-pull or Open-drain).
 *
 */
typedef enum
{
    /* Input Modes */
    GPIO_MODE_INPUT_NOPULL                    = 0x000UL, /**< Input mode with no pull-up or pull-down. */
    GPIO_MODE_INPUT_PULLUP                    = 0x010UL, /**< Input mode with pull-up resistor. */
    GPIO_MODE_INPUT_PULLDOWN                  = 0x020UL, /**< Input mode with pull-down resistor. */
    GPIO_MODE_INPUT_ANALOG                    = 0x003UL, /**< Analog input mode. */

    /* Output Modes - Push-pull */
    GPIO_MODE_OUTPUT_PUSHPULL_NOPULL          = 0x001UL, /**< Output mode, push-pull, no pull configuration. */
    GPIO_MODE_OUTPUT_PUSHPULL_PULLUP          = 0x011UL, /**< Output mode, push-pull, with pull-up resistor. */
    GPIO_MODE_OUTPUT_PUSHPULL_PULLDOWN        = 0x021UL, /**< Output mode, push-pull, with pull-down resistor. */
      
    /* Output Modes - Open-drain */       
    GPIO_MODE_OUTPUT_OPENDRAIN_NOPULL         = 0x101UL, /**< Output mode, open-drain, no pull configuration. */
    GPIO_MODE_OUTPUT_OPENDRAIN_PULLUP         = 0x111UL, /**< Output mode, open-drain, with pull-up resistor. */
    GPIO_MODE_OUTPUT_OPENDRAIN_PULLDOWN       = 0x121UL, /**< Output mode, open-drain, with pull-down resistor. */

    /* Alternate Function Modes - Push-pull */
    GPIO_MODE_ALTERNATE_PUSHPULL_NOPULL       = 0x002UL, /**< Alternate function mode, push-pull, no pull configuration. */
    GPIO_MODE_ALTERNATE_PUSHPULL_PULLUP       = 0x012UL, /**< Alternate function mode, push-pull, with pull-up resistor. */
    GPIO_MODE_ALTERNATE_PUSHPULL_PULLDOWN     = 0x022UL, /**< Alternate function mode, push-pull, with pull-down resistor. */

    /* Alternate Function Modes - Open-drain */
    GPIO_MODE_ALTERNATE_OPENDRAIN_NOPULL      = 0x102UL, /**< Alternate function mode, open-drain, no pull configuration. */
    GPIO_MODE_ALTERNATE_OPENDRAIN_PULLUP      = 0x112UL, /**< Alternate function mode, open-drain, with pull-up resistor. */
    GPIO_MODE_ALTERNATE_OPENDRAIN_PULLDOWN    = 0x122UL  /**< Alternate function mode, open-drain, with pull-down resistor. */

} GPIO_PinModeTypeDef;


/**
 * @brief Enumeration defining GPIO pin speeds.
 *
 * This enumeration provides constants for GPIO pin speed configuration.
 */
typedef enum
{
    GPIO_SPEED_LOW,         /**< Low speed. */
    GPIO_SPEED_MEDIUM,      /**< Medium speed. */
    GPIO_SPEED_HIGH,        /**< High speed. */
    GPIO_SPEED_VERY_HIGH    /**< Very high speed. */
} GPIO_PinSpeedTypeDef;

/**
 * @brief Structure to configure GPIO pin settings.
 *
 * This structure encapsulates the configuration parameters for a GPIO pin, including the GPIO port,
 * pin number, pin mode, and pin speed.
 *
 */
typedef struct
{
    GPIO_PortTypeDef       Port;        /**< GPIO port to which the pin belongs. */
    GPIO_PinTypeDef        PinNumber;   /**< Specific GPIO pin number. */
    GPIO_PinModeTypeDef    PinMode;     /**< Configuration for pin mode. */
    GPIO_PinSpeedTypeDef   PinSpeed;    /**< Speed setting for the GPIO pin. */
} GPIO_PinConfigTypeDef;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Initializes a GPIO pin based on the provided configuration.
 *
 * This function configures a GPIO pin based on the parameters specified in the provided `GPIO_PinConfigTypeDef`.
 *
 * @param[in] PinConfig Configuration structure for the GPIO pin.
 * @return Status indicating the success or failure of the initialization @ref MCAL_StatusTypeDef.
 */
MCAL_StatusTypeDef GPIO_initPin(GPIO_PinConfigTypeDef PinConfig);

/*GPIO_setPinValue()*/
/*GPIO_getPinValue()*/
#endif /* GPIO_GPIO_H_ */