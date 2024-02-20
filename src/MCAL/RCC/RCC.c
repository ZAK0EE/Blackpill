/**
 * @file RCC.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief This file is implementation of the RCC peripheral
 * @version 0.1
 * @date 2024-02-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/RCC/RCC.h"
#include "assertparam.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define RCC_CFGR_SW_MASK  ((uint32_t)0x3 << 0)
#define RCC_CFGR_SWS_MASK ((uint32_t)0x3 << 2)

#define RCC_PLLCFGR_PLLSRC_OFFSET (22)
#define RCC_PLLCFGR_PLLSRC_MASK ((uint32_t)1 << RCC_PLLCFGR_PLLSRC_OFFSET)

#define RCC_PLLCFGR_PLLM_OFFSET (0)
#define RCC_PLLCFGR_PLLM_MASK ((uint32_t)0x3F << RCC_PLLCFGR_PLLM_OFFSET)

#define RCC_PLLCFGR_PLLN_OFFSET (6)
#define RCC_PLLCFGR_PLLN_MASK ((uint32_t)0x1FF << RCC_PLLCFGR_PLLN_OFFSET)

#define RCC_PLLCFGR_PLLP_OFFSET (16)
#define RCC_PLLCFGR_PLLP_MASK ((uint32_t)0x3 << RCC_PLLCFGR_PLLP_OFFSET)

#define RCC_PLLCFGR_PLLQ_OFFSET (24)
#define RCC_PLLCFGR_PLLQ_MASK ((uint32_t)0xF << RCC_PLLCFGR_PLLQ_OFFSET)

#define RCC_CFGR_HPRE_OFFSET (4)
#define RCC_CFGR_HPRE_MASK ((uint32_t)0xF << RCC_CFGR_HPRE_OFFSET)

#define RCC_CFGR_PPRE1_OFFSET (10)
#define RCC_CFGR_PPRE1_MASK ((uint32_t)0x7 << RCC_CFGR_PPRE1_OFFSET)

#define RCC_CFGR_PPRE2_OFFSET (13)
#define RCC_CFGR_PPRE2_MASK ((uint32_t)0x7 << RCC_CFGR_PPRE2_OFFSET)

#define RCC_TIMEOUT_VAL     (600)
/************************************/
/***************Registers************/
/************************************/
#define RCC_BASE (0x40023800UL)


#define RCC ((RCC_TypeDef* const)(RCC_BASE))

/************************************/
/***************Validators************/
/************************************/

#define IS_RCC_CLOCK(TYPE) (((TYPE) == RCC_CLOCK_HSI) || \
                                 ((TYPE) == RCC_CLOCK_HSE) || \
                                 ((TYPE) == RCC_CLOCK_PLL) || \
                                 ((TYPE) == RCC_CLOCK_PLLI2S))

#define IS_RCC_SYSTEMCLOCK(CLOCK) (((CLOCK) == RCC_SYSTEMCLOCK_HSI) || \
                                    ((CLOCK) == RCC_SYSTEMCLOCK_HSE) || \
                                    ((CLOCK) == RCC_SYSTEMCLOCK_PLL))

#define IS_RCC_AHB1PERIPHERAL(PERIPHERAL) (((PERIPHERAL) == RCC_AHB1PERIPHERAL_GPIOA) || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_GPIOB) || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_GPIOC) || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_GPIOD) || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_GPIOE) || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_GPIOH) || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_CRC)   || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_DMA1)  || \
                                           ((PERIPHERAL) == RCC_AHB1PERIPHERAL_DMA2))

#define IS_RCC_AHB2PERIPHERAL(PERIPHERAL) ((PERIPHERAL) == RCC_AHB2PERIPHERAL_OTGFS)

#define IS_RCC_APB1PERIPHERAL(PERIPHERAL) (((PERIPHERAL) == RCC_APB1PERIPHERAL_TIM2)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_TIM3)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_TIM4)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_TIM5)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_WWDG)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_SPI2)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_SPI3)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_USART2) || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_I2C1)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_I2C2)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_I2C3)   || \
                                           ((PERIPHERAL) == RCC_APB1PERIPHERAL_PWR))

#define IS_RCC_APB2PERIPHERAL(PERIPHERAL) (((PERIPHERAL) == RCC_APB2PERIPHERAL_TIM1)   || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_USART1) || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_USART6) || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_ADC1)   || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_SDI0)   || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_SPI1)   || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_SPI4)   || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_SYSCFG) || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_TMI9)   || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_TIM10)  || \
                                           ((PERIPHERAL) == RCC_APB2PERIPHERAL_TIM11))

#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSRC_HSI) || \
                                   ((SOURCE) == RCC_PLLSRC_HSE))

#define IS_RCC_AHB1PRESCALER(PRESCALER) (((PRESCALER) == RCC_AHB1PRESCALER_0)   || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_2)   || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_4)   || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_8)   || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_16)  || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_64)  || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_128) || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_256) || \
                                          ((PRESCALER) == RCC_AHB1PRESCALER_512))

#define IS_RCC_APB1PRESCALER(PRESCALER) (((PRESCALER) == RCC_APB1PRESCALER_0)   || \
                                          ((PRESCALER) == RCC_APB1PRESCALER_2)   || \
                                          ((PRESCALER) == RCC_APB1PRESCALER_4)   || \
                                          ((PRESCALER) == RCC_APB1PRESCALER_8)   || \
                                          ((PRESCALER) == RCC_APB1PRESCALER_16))

#define IS_RCC_APB2PRESCALER(PRESCALER) (((PRESCALER) == RCC_APB2PRESCALER_0)   || \
                                          ((PRESCALER) == RCC_APB2PRESCALER_2)   || \
                                          ((PRESCALER) == RCC_APB2PRESCALER_4)   || \
                                          ((PRESCALER) == RCC_APB2PRESCALER_8)   || \
                                          ((PRESCALER) == RCC_APB2PRESCALER_16))



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/***********************************************************/
/******************Peripheral Register RCC******************/
/***********************************************************/
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t RESERVED1[2];;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED2[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t RESERVED3[2];
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED4[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t RESERVED5[2];
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t RESERVED6[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t RESERVED7[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t RESERVED8;
    volatile uint32_t DCKCFGR;
}RCC_TypeDef;

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

MCAL_StatusTypeDef RCC_enableClock(RCC_ClockTypeDef Clock)
{
    assert_param(IS_RCC_CLOCK(Clock));

    /* Enable the clock*/
    RCC->CR |= Clock;
    uint32_t clockStatusMask = ((uint32_t)Clock << 1UL);

    uint32_t timeout = RCC_TIMEOUT_VAL;
    while(!(RCC->CR & clockStatusMask) && timeout){timeout--;}

    return (RCC->CR & clockStatusMask)? MCAL_OK : MCAL_TIMEOUT;
}

MCAL_StatusTypeDef RCC_disableClock(RCC_ClockTypeDef Clock)
{
    assert_param(IS_RCC_CLOCK(Clock));

    RCC->CR &= ~Clock;
    return MCAL_OK;
}


MCAL_StatusTypeDef RCC_selectSystemClock(RCC_SystemClockTypeDef SystemClock)
{

    assert_param(IS_RCC_SYSTEMCLOCK(SystemClock));

    uint32_t CFGRtmp = RCC->CFGR;
    CFGRtmp = (CFGRtmp & ~RCC_CFGR_SW_MASK) | (uint32_t)SystemClock;

    RCC->CFGR = CFGRtmp;
    return MCAL_OK;
}


MCAL_StatusTypeDef RCC_getSystemClock(RCC_SystemClockTypeDef *SystemClock)
{
    *SystemClock = (((RCC->CFGR) & RCC_CFGR_SWS_MASK) >> 2);

    return MCAL_OK;
}


MCAL_StatusTypeDef RCC_configurePLLClock(RCC_PLLConfigTypeDef *PLLConfig)
{
    uint32_t PLLCFGRtmp = RCC->PLLCFGR;

    assert_param(IS_RCC_PLL_SOURCE(PLLConfig->PLLSrc));
    PLLCFGRtmp = (PLLCFGRtmp & ~RCC_PLLCFGR_PLLSRC_MASK) | (uint32_t)PLLConfig->PLLSrc;

    /* Trim the prescaler value using its mask */
    uint32_t PLLM_value = ((uint32_t)PLLConfig->PLLM & (RCC_PLLCFGR_PLLM_MASK >> RCC_PLLCFGR_PLLM_OFFSET));
    PLLCFGRtmp = (PLLCFGRtmp & ~RCC_PLLCFGR_PLLM_MASK) | (PLLM_value << RCC_PLLCFGR_PLLM_OFFSET);

    uint32_t PLLN_value = ((uint32_t)PLLConfig->PLLN & (RCC_PLLCFGR_PLLN_MASK >> RCC_PLLCFGR_PLLN_OFFSET));
    PLLCFGRtmp = (PLLCFGRtmp & ~RCC_PLLCFGR_PLLN_MASK) | (PLLN_value << RCC_PLLCFGR_PLLN_OFFSET);

    uint32_t PLLP_value = ((uint32_t)PLLConfig->PLLP & (RCC_PLLCFGR_PLLP_MASK >> RCC_PLLCFGR_PLLP_OFFSET));
    PLLCFGRtmp = (PLLCFGRtmp & ~RCC_PLLCFGR_PLLP_MASK) | (PLLP_value << RCC_PLLCFGR_PLLP_OFFSET);

    uint32_t PLLQ_value = ((uint32_t)PLLConfig->PLLQ & (RCC_PLLCFGR_PLLQ_MASK >> RCC_PLLCFGR_PLLQ_OFFSET));
    PLLCFGRtmp = (PLLCFGRtmp & ~RCC_PLLCFGR_PLLQ_MASK) | (PLLQ_value << RCC_PLLCFGR_PLLQ_OFFSET);   

    RCC->PLLCFGR = PLLCFGRtmp;

    return MCAL_OK;
}


MCAL_StatusTypeDef RCC_enableAHB1Peripheral(RCC_AHB1PeripeheralTypeDef AHB1Peripheral)
{
    assert_param(IS_RCC_AHB1PERIPHERAL(AHB1Peripheral));

    RCC->AHB1ENR |= AHB1Peripheral;
    return MCAL_OK;
}


MCAL_StatusTypeDef RCC_enableAHB2Peripheral(RCC_AHB2PeripeheralTypeDef AHB2Peripheral)
{
    assert_param(IS_RCC_AHB2PERIPHERAL(AHB2Peripheral));

    RCC->AHB2ENR |= AHB2Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_enableAPB1Peripheral(RCC_APB1PeripeheralTypeDef APB1Peripheral)
{
    assert_param(IS_RCC_APB1PERIPHERAL(APB1Peripheral));

    RCC->APB1ENR |= APB1Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_enableAPB2Peripheral(RCC_APB2PeripeheralTypeDef APB2Peripheral)
{
    assert_param(IS_RCC_APB2PERIPHERAL(APB2Peripheral));

    RCC->APB2ENR |= APB2Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_disableAHB1Peripheral(RCC_AHB1PeripeheralTypeDef AHB1Peripheral)
{
    assert_param(IS_RCC_AHB1PERIPHERAL(AHB1Peripheral));

    RCC->AHB1ENR &= ~AHB1Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_disableAHB2Peripheral(RCC_AHB2PeripeheralTypeDef AHB2Peripheral)
{
    assert_param(IS_RCC_AHB2PERIPHERAL(AHB2Peripheral));

    RCC->AHB2ENR &= ~AHB2Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_disableAPB1Peripheral(RCC_APB1PeripeheralTypeDef APB1Peripheral)
{
    assert_param(IS_RCC_APB1PERIPHERAL(APB1Peripheral));

    RCC->APB1ENR &= ~APB1Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_disableAPB2Peripheral(RCC_APB2PeripeheralTypeDef APB2Peripheral)
{
    assert_param(IS_RCC_APB2PERIPHERAL(APB2Peripheral));

    RCC->APB2ENR &= ~APB2Peripheral;
    return MCAL_OK;
}

MCAL_StatusTypeDef RCC_selectSystemClockPrescalers(RCC_AHB1PrescalerTypeDef AHB1Prescaler, RCC_APB1PrescalerTypeDef APB1Prescaler, RCC_APB2PrescalerTypeDef APB2Prescaler)
{
    assert_param(IS_RCC_AHB1PRESCALER(AHB1Prescaler));
    assert_param(IS_RCC_APB1PRESCALER(APB1Prescaler));
    assert_param(IS_RCC_APB2PRESCALER(APB2Prescaler));

    uint32_t CFGRtmp = RCC->CFGR;

    CFGRtmp = (CFGRtmp & ~RCC_CFGR_HPRE_MASK)  | AHB1Prescaler;
    CFGRtmp = (CFGRtmp & ~RCC_CFGR_PPRE1_MASK) | APB1Prescaler;
    CFGRtmp = (CFGRtmp & ~RCC_CFGR_PPRE2_MASK) | APB2Prescaler;

    RCC->CFGR = CFGRtmp;

    return MCAL_OK;
}