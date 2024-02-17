/**
 * @file RCC.h
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief This file is interface for RCC peripheral
 * @version 0.1
 * @date 2024-02-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef RCC_RCC_H_
#define RCC_RCC_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/stm32f401.h"
#include <stdint.h>
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Enumeration defining clock sources for the RCC (Reset and Clock Control) module.
 */
typedef enum 
{
    RCC_CLOCK_HSI    = (1UL << 0),   /**< High-Speed Internal (HSI) clock source. */
    RCC_CLOCK_HSE    = (1UL << 16),  /**< High-Speed External (HSE) clock source. */
    RCC_CLOCK_PLL    = (1UL << 24),  /**< Phase-Locked Loop (PLL) clock source. */
    RCC_CLOCK_PLLI2S = (1UL << 26),  /**< PLLI2S clock source. */

} RCC_ClockTypeDef;

/**
 * @brief Enumeration of the available system clock sources
 */
typedef enum
{
    RCC_SYSTEMCLOCK_HSI = 0x00,	/**< High Speed Internal Clock Selected as System Clock (HSI) */
    RCC_SYSTEMCLOCK_HSE = 0x01,	/**< High Speed External Clock Selected as System Clock (HSE) */
    RCC_SYSTEMCLOCK_PLL = 0x02	/**< PLL Clock Selected as System Clock (PLL) */
} RCC_SystemClockTypeDef;


/**
 * @brief Enumeration of the available AHB1 peripherals
 * 
 */
typedef enum
{
    RCC_AHB1PERIPHERAL_GPIOA = (1UL <<  0),	    /**< GPIO port A */
    RCC_AHB1PERIPHERAL_GPIOB = (1UL <<  1),	    /**< GPIO port B */
    RCC_AHB1PERIPHERAL_GPIOC = (1UL <<  2),	    /**< GPIO port C */
    RCC_AHB1PERIPHERAL_GPIOD = (1UL <<  3),	    /**< GPIO port D */
    RCC_AHB1PERIPHERAL_GPIOE = (1UL <<  4),	    /**< GPIO port E */
    RCC_AHB1PERIPHERAL_GPIOH = (1UL <<  7),	    /**< GPIO port H */
    RCC_AHB1PERIPHERAL_CRC   = (1UL <<  12),    /**< CRC calculation unit */
    RCC_AHB1PERIPHERAL_DMA1  = (1UL <<  21),    /**< DMA1 */
    RCC_AHB1PERIPHERAL_DMA2  = (1UL <<  22)	    /**< DMA2 */
} RCC_AHB1PeripeheralTypeDef;


/**
 * @brief Enumeration of the available AHB2 peripherals
 */
typedef enum
{
    RCC_AHB2PERIPHERAL_OTGFS = ((uint32_t)1 <<  7),	    /**< USB OTG FS */

} RCC_AHB2PeripeheralTypeDef;


/**
 * @brief Enumeration of the available APB1 peripherals
 */
typedef enum
{
    RCC_APB1PERIPHERAL_TIM2     = (1UL <<  0),	/**< TIM2 - 14-bit timer */ 
    RCC_APB1PERIPHERAL_TIM3     = (1UL <<  1),	/**< TIM3 - 16-bit timer */
    RCC_APB1PERIPHERAL_TIM4     = (1UL <<  2),	/**< TIM4 - 16-bit timer */
    RCC_APB1PERIPHERAL_TIM5     = (1UL <<  3),	/**< TIM5 - 32-bit timer */
    RCC_APB1PERIPHERAL_WWDG     = (1UL <<  11),	/**< Window Watchdog */
    RCC_APB1PERIPHERAL_SPI2     = (1UL <<  14),	/**< SPI2 */
    RCC_APB1PERIPHERAL_SPI3     = (1UL <<  15),	/**< SPI3 */
    RCC_APB1PERIPHERAL_USART2   = (1UL <<  17),	/**< USART2 */
    RCC_APB1PERIPHERAL_I2C1     = (1UL <<  21),	/**< I2C1 - Inter-Integrated Circuit */
    RCC_APB1PERIPHERAL_I2C2     = (1UL <<  22),	/**< I2C2 - Inter-Integrated Circuit */
    RCC_APB1PERIPHERAL_I2C3     = (1UL <<  23),	/**< I2C3 - Inter-Integrated Circuit */
    RCC_APB1PERIPHERAL_PWR      = (1UL <<  28),	/**< Power interface */
}
RCC_APB1PeripeheralTypeDef;


/**
 * @brief Enumeration of the available APB2 peripherals
 */
typedef enum
{
    RCC_APB2PERIPHERAL_TIM1     = (1UL <<  0),   /**< TIM1 peripheral  */
    RCC_APB2PERIPHERAL_USART1   = (1UL <<  4),   /**< USART1 peripheral */
    RCC_APB2PERIPHERAL_USART6   = (1UL <<  5),   /**< USART6 peripheral */
    RCC_APB2PERIPHERAL_ADC1     = (1UL <<  8),   /**< ADC1 peripheral */
    RCC_APB2PERIPHERAL_SDI0     = (1UL << 11),   /**< SDIO peripheral */
    RCC_APB2PERIPHERAL_SPI1     = (1UL << 12),   /**< SPI1 peripheral */
    RCC_APB2PERIPHERAL_SPI4     = (1UL << 13),   /**< SPI4 peripheral */
    RCC_APB2PERIPHERAL_SYSCFG   = (1UL << 14),   /**< System Configuration */
    RCC_APB2PERIPHERAL_TMI9     = (1UL << 16),   /**< TIM9 peripheral */
    RCC_APB2PERIPHERAL_TIM10    = (1UL << 17),   /**< TIM10 peripheral */
    RCC_APB2PERIPHERAL_TIM11    = (1UL << 18),   /**< TIM11 peripheral */
} RCC_APB2PeripeheralTypeDef;

/**
 * @brief Enumeration of the available PLL clock sources
 */
typedef enum
{
    RCC_PLLSRC_HSI = 0x00,	/**< High Speed Internal Clock Selected as PLL Clock (HSI) */
    RCC_PLLSRC_HSE = 0x01,	/**< High Speed External Clock Selected as PLL Clock (HSE) */
} RCC_PLLSrcTypeDef;


/**
 * @brief Structure to configure the PLL (Phase-Locked Loop) in the RCC (Reset and Clock Control) module.
 */
typedef struct 
{
    RCC_PLLSrcTypeDef PLLSrc;                  /**< PLL Source: The source of the PLL clock. */
    uint8_t PLLM;                              /**< PLL Division Factor M: Division factor for the main PLL input clock. */
    uint16_t PLLN;                             /**< PLL Multiplication Factor N: PLL multiplication factor for VCO (Voltage-Controlled Oscillator). */
    uint8_t PLLP;                              /**< PLL Division Factor P: Division factor for the main system clock. */
    uint8_t PLLQ;                              /**< Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks */

} RCC_PLLConfigTypeDef;

/**
 * @brief Enumeration defining AHB1 prescaler values for the RCC (Reset and Clock Control) module.
 */
typedef enum 
{
    RCC_AHB1PRESCALER_0   = 0x0,  /**< System clock not divided. */
    RCC_AHB1PRESCALER_2   = 0x8,  /**< System clock divided by 2. */
    RCC_AHB1PRESCALER_4   = 0x9,  /**< System clock divided by 4. */
    RCC_AHB1PRESCALER_8   = 0xA,  /**< System clock divided by 8. */
    RCC_AHB1PRESCALER_16  = 0xB,  /**< System clock divided by 16. */
    RCC_AHB1PRESCALER_64  = 0xC,  /**< System clock divided by 64. */
    RCC_AHB1PRESCALER_128 = 0xD,  /**< System clock divided by 128. */
    RCC_AHB1PRESCALER_256 = 0xE,  /**< System clock divided by 256. */
    RCC_AHB1PRESCALER_512 = 0xF   /**< System clock divided by 512. */

} RCC_AHB1PrescalerTypeDef;


/**
 * @brief Enumeration defining APB1 prescaler values for the RCC (Reset and Clock Control) module.
 */
typedef enum 
{
    RCC_APB1PRESCALER_0   = 0x0,  /**< AHB clock not divided. */
    RCC_APB1PRESCALER_2   = 0x4,  /**< AHB clock divided by 2. */
    RCC_APB1PRESCALER_4   = 0x5,  /**< AHB clock divided by 4. */
    RCC_APB1PRESCALER_8   = 0x6,  /**< AHB clock divided by 8. */
    RCC_APB1PRESCALER_16  = 0x7   /**< AHB clock divided by 16. */

} RCC_APB1PrescalerTypeDef;

/**
 * @brief Enumeration defining APB2 prescaler values for the RCC (Reset and Clock Control) module.
 */
typedef enum 
{
    RCC_APB2PRESCALER_0   = 0x0,  /**< AHB clock not divided. */
    RCC_APB2PRESCALER_2   = 0x4,  /**< AHB clock divided by 2. */
    RCC_APB2PRESCALER_4   = 0x5,  /**< AHB clock divided by 4. */
    RCC_APB2PRESCALER_8   = 0x6,  /**< AHB clock divided by 8. */
    RCC_APB2PRESCALER_16  = 0x7   /**< AHB clock divided by 16. */

} RCC_APB2PrescalerTypeDef;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Enable a specific clock source given as a parameter
 *
 * @param Clock The system component for which the clock needs to be enabled.
 * @return Status of the operation. See @ref MCAL_StatusTypeDef for possible values.
 *
 * @note Ensure that the necessary PLL configurations are set before enabling the clock.
 * @note Clock will be enabled only if it is ready
 */
MCAL_StatusTypeDef RCC_enableClock(RCC_SystemClockTypeDef Clock);

/**
 * @brief Disable a specific clock source given as a parameter
 *
 * @param Clock The system component for which the clock needs to be disabled (see @ref RCC_SystemClockTypeDef).
 * @return Status of the operation. See @ref MCAL_StatusTypeDef for possible values.
 */
MCAL_StatusTypeDef RCC_disableClock(RCC_SystemClockTypeDef Clock);

/**
 * @brief Selects the system clock source
 * @param SystemClock specifies the system clock source.
 *                    This parameter can be a value of @ref RCC_SystemClockTypeDef
 * @retval MCAL_OK if the system clock was successfully selected
 */
MCAL_StatusTypeDef RCC_selectSystemClock(RCC_SystemClockTypeDef SystemClock);

/**
 * @brief Get the system clock source
 * @param[out] SystemClock Pointer to a variable that will receive the system clock source
 * 		                   This parameter can be a value of @ref RCC_SystemClockTypeDef
 * @return MCAL_OK if the system clock source was read successfully
 */
MCAL_StatusTypeDef RCC_getSystemClock(RCC_SystemClockTypeDef *SystemClock);


MCAL_StatusTypeDef RCC_selectSystemClockPrescalers(RCC_AHB1PrescalerTypeDef AHB1Prescaler, RCC_APB1PrescalerTypeDef APB1Prescaler, RCC_APB2PrescalerTypeDef APB2Prescaler);

/**
 * @brief Configures the PLL clock.
 * @param PLLConfig pointer to a @ref RCC_PLLConfigTypeDef structure that contains the configuration information for the PLL.
 * @retval MCAL_OK if the PLL clock was successfully configured.
 */
MCAL_StatusTypeDef RCC_configurePLLClock(RCC_PLLConfigTypeDef *PLLConfig);

/**
 * @brief Enables the clock for a specific AHB1 peripheral
 * @param AHB1Peripheral specifies the AHB1 peripheral to be enabled
 *   		             This parameter can be a value of @ref RCC_AHB1PeripheralTypeDef
 * @retval MCAL_OK if the peripheral clock was successfully enabled
 */
MCAL_StatusTypeDef RCC_enableAHB1Peripheral(RCC_AHB1PeripeheralTypeDef AHB1Peripheral);

/**
 * @brief Enables the clock for a specific AHB2 peripheral
 * @param AHB2Peripheral specifies the AHB2 peripheral to be enabled
 *   		             This parameter can be a value of @ref RCC_AHB2PeripheralTypeDef
 * @retval MCAL_OK if the peripheral clock was successfully enabled
 */
MCAL_StatusTypeDef RCC_enableAHB2Peripheral(RCC_AHB2PeripeheralTypeDef AHB2Peripheral);

/**
 * @brief Enables the clock for a specific APB1 peripheral
 * @param APB1Peripheral specifies the APB1 peripheral to be enabled
 *                        This parameter can be a value of @ref RCC_APB1PeripheralTypeDef
 * @retval MCAL_OK if the peripheral clock was successfully enabled
 */
MCAL_StatusTypeDef RCC_enableAPB1Peripheral(RCC_APB1PeripeheralTypeDef APB1Peripheral);

/**
 * @brief Enables the clock for a specific APB2 peripheral
 * @param APB2Peripheral specifies the APB2 peripheral to be enabled
 *                        This parameter can be a value of @ref RCC_APB2PeripheralTypeDef
 * @retval MCAL_OK if the peripheral clock was successfully enabled
 */
MCAL_StatusTypeDef RCC_enableAPB2Peripheral(RCC_APB2PeripeheralTypeDef APB2Peripheral);


/**
 * @brief Disable the specified AHB1 peripheral.
 *
 * @param AHB1Peripheral: AHB1 peripheral to be disabled.
 * @return MCAL_OK if the operation is successful, otherwise an error code.
 */
MCAL_StatusTypeDef RCC_disableAHB1Peripheral(RCC_AHB1PeripeheralTypeDef AHB1Peripheral);

/**
 * @brief Disable the specified AHB2 peripheral.
 *
 * @param AHB2Peripheral: AHB2 peripheral to be disabled.
 * @return MCAL_OK if the operation is successful, otherwise an error code.
 */
MCAL_StatusTypeDef RCC_disableAHB2Peripheral(RCC_AHB2PeripeheralTypeDef AHB2Peripheral);

/**
 * @brief Disable the specified APB1 peripheral.
 *
 * @param APB1Peripheral: APB1 peripheral to be disabled.
 * @return MCAL_OK if the operation is successful, otherwise an error code.
 */
MCAL_StatusTypeDef RCC_disableAPB1Peripheral(RCC_APB1PeripeheralTypeDef APB1Peripheral);

/**
 * @brief Disable the specified APB2 peripheral.
 *
 * @param APB2Peripheral: APB2 peripheral to be disabled.
 * @return MCAL_OK if the operation is successful, otherwise an error code.
 */
MCAL_StatusTypeDef RCC_disableAPB2Peripheral(RCC_APB2PeripeheralTypeDef APB2Peripheral);

#endif /* RCC_RCC_H_ */
