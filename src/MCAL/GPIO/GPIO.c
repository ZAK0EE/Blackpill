/**
 * @file GPIO.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Implementation of the GPIO interface
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/GPIO/GPIO.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define MASK_1BIT  (0x1UL)
#define MASK_2BITS (0X3UL)
/************************************/
/***************Registers************/
/************************************/
#define GPIOA_BASE (0x40020000UL)
#define GPIOB_BASE (0x40020400UL)
#define GPIOC_BASE (0x40020800UL)
#define GPIOD_BASE (0x40020C00UL)
#define GPIOE_BASE (0x40021000UL)
#define GPIOH_BASE (0x40021C00UL)


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/***********************************************************/
/******************Peripheral Register GPIO******************/
/***********************************************************/

/**
 * @brief Structure representing the GPIO peripheral registers.
 *
 * This structure encapsulates the various registers associated with a GPIO port.
 */
typedef struct {
    uint32_t MODER;     /**< GPIO port mode register. */
    uint32_t OTYPER;    /**< GPIO port output type register. */
    uint32_t OSPEEDR;   /**< GPIO port output speed register. */
    uint32_t PUPDR;     /**< GPIO port pull-up/pull-down register. */
    uint32_t IDR;       /**< GPIO port input data register. */
    uint32_t ODR;       /**< GPIO port output data register. */
    uint32_t BSRR;      /**< GPIO port bit set/reset register. */
    uint32_t LCKR;      /**< GPIO port lock register. */
    uint32_t AFRL;      /**< GPIO port alternate function low register. */
    uint32_t AFRH;      /**< GPIO port alternate function high register. */
} GPIO_TypeDef;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
GPIO_TypeDef* GPIOS[] = {GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE, GPIOH_BASE};
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

MCAL_StatusTypeDef GPIO_initPin(GPIO_PinConfigTypeDef *PinConfig)
{
    GPIO_TypeDef* GPIO = GPIOS[PinConfig->Port];

    uint32_t PinMode = PinConfig->PinMode & 0x00FUL;
    uint32_t PinPull = (PinConfig->PinMode & 0x0F0UL) >> 4;
    uint32_t PinOutputType = (PinConfig->PinMode & 0xF00UL) >> 8;

    /* Set Pin Mode */
    GPIO->MODER = GPIO->MODER & ~(MASK_2BITS << (PinConfig->PinNumber * 2)) | (PinMode << (PinConfig->PinNumber * 2));

    GPIO->PUPDR = GPIO->PUPDR & ~(MASK_2BITS << (PinConfig->PinNumber * 2)) | (PinPull << (PinConfig->PinNumber * 2));

    GPIO->OTYPER = GPIO->OTYPER & ~(MASK_1BIT << PinConfig->PinNumber) | (PinOutputType << PinConfig->PinNumber);

    /* Set Pin Speed */
    GPIO->OSPEEDR = GPIO->OSPEEDR & ~(MASK_2BITS << (PinConfig->PinNumber * 2)) | (PinConfig->PinSpeed << (PinConfig->PinNumber * 2));

    return MCAL_OK;
}

MCAL_StatusTypeDef GPIO_setPinValue(GPIO_PortTypeDef Port, GPIO_PinTypeDef PinNumber, GPIO_PinStateTypeDef PinState)
{

}

GPIO_PinStateTypeDef GPIO_getPinValue(GPIO_PortTypeDef Port, GPIO_PinTypeDef PinNumber)
{

}
