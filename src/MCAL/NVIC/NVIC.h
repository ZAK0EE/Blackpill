/**
 * @file NVIC.h
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Header file for NVIC (Nested vectored interrupt controller)
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/stm32f401.h"
#include <stdint.h>
#include "NVIC_Cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Enumeration for NVIC Interrupt Numbers of the vector table.
 * 
 * The enumerators represent the NVIC interrupt numbers for the Black Pill STM32 board.
 */
typedef enum {
    NVIC_IRQ_WWDG = 0,                  /* Window Watchdog interrupt */
    NVIC_IRQ_EXTI16_PVD,                /* EXTI Line 16 interrupt / PVD through EXTI line detection interrupt */
    NVIC_IRQ_EXTI21_TAMP_STAMP,         /* EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through the EXTI line */
    NVIC_IRQ_EXTI22_RTC_WKUP,           /* EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line */
    NVIC_IRQ_FLASH,                     /* Flash global interrupt */
    NVIC_IRQ_RCC,                       /* RCC global interrupt */
    NVIC_IRQ_EXTI0,                     /* EXTI Line0 interrupt */
    NVIC_IRQ_EXTI1,                     /* EXTI Line1 interrupt */
    NVIC_IRQ_EXTI2,                     /* EXTI Line2 interrupt */
    NVIC_IRQ_EXTI3,                     /* EXTI Line3 interrupt */
    NVIC_IRQ_EXTI4,                     /* EXTI Line4 interrupt */
    NVIC_IRQ_DMA1_STREAM0,              /* DMA1 Stream0 global interrupt */
    NVIC_IRQ_DMA1_STREAM1,              /* DMA1 Stream1 global interrupt */
    NVIC_IRQ_DMA1_STREAM2,              /* DMA1 Stream2 global interrupt */
    NVIC_IRQ_DMA1_STREAM3,              /* DMA1 Stream3 global interrupt */
    NVIC_IRQ_DMA1_STREAM4,              /* DMA1 Stream4 global interrupt */
    NVIC_IRQ_DMA1_STREAM5,              /* DMA1 Stream5 global interrupt */
    NVIC_IRQ_DMA1_STREAM6,              /* DMA1 Stream6 global interrupt */
    NVIC_IRQ_ADC1,                      /* ADC1 global interrupts */
    NVIC_IRQ_EXTI9_5 = 23,              /* EXTI Line[9:5] interrupts */
    NVIC_IRQ_TIM1_BRK_TIM9,             /* TIM1 Break interrupt and TIM9 global interrupt */
    NVIC_IRQ_TIM1_UP_TIM10,             /* TIM1 Update interrupt and TIM10 global interrupt */
    NVIC_IRQ_TIM1_TRG_COM_TIM11,        /* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
    NVIC_IRQ_TIM1_CC,                   /* TIM1 Capture Compare interrupt */
    NVIC_IRQ_TIM2,                      /* TIM2 global interrupt */
    NVIC_IRQ_TIM3,                      /* TIM3 global interrupt */
    NVIC_IRQ_TIM4,                      /* TIM4 global interrupt */
    NVIC_IRQ_I2C1_EV,                   /* I2C1 event interrupt */
    NVIC_IRQ_I2C1_ER,                   /* I2C1 error interrupt */
    NVIC_IRQ_I2C2_EV,                   /* I2C2 event interrupt */
    NVIC_IRQ_I2C2_ER,                   /* I2C2 error interrupt */
    NVIC_IRQ_SPI1,                      /* SPI1 global interrupt */
    NVIC_IRQ_SPI2,                      /* SPI2 global interrupt */
    NVIC_IRQ_USART1,                    /* USART1 global interrupt */
    NVIC_IRQ_USART2,                    /* USART2 global interrupt */
    NVIC_IRQ_EXTI15_10 = 40,            /* EXTI Line[15:10] interrupts */
    NVIC_IRQ_EXTI17_RTC_ALARM,          /* EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt */
    NVIC_IRQ_EXTI18_OTG_FS_WKUP,        /* EXTI Line 18 interrupt / USB On-The-Go FS Wakeup through EXTI line interrupt */
    NVIC_IRQ_DMA1_STREAM7 = 47,         /* DMA1 Stream7 global interrupt */
    NVIC_IRQ_SDIO,                      /* SDIO global interrupt */
    NVIC_IRQ_TIM5,                      /* TIM5 global interrupt */
    NVIC_IRQ_SPI3,                      /* SPI3 global interrupt */
    NVIC_IRQ_DMA2_STREAM0 = 56,         /* DMA2 Stream0 global interrupt */
    NVIC_IRQ_DMA2_STREAM1,              /* DMA2 Stream1 global interrupt */
    NVIC_IRQ_DMA2_STREAM2,              /* DMA2 Stream2 global interrupt */
    NVIC_IRQ_DMA2_STREAM3,              /* DMA2 Stream3 global interrupt */
    NVIC_IRQ_DMA2_STREAM4,              /* DMA2 Stream4 global interrupt */
    NVIC_IRQ_OTG_FS = 67,               /* USB On The Go FS global interrupt */
    NVIC_IRQ_DMA2_STREAM5,              /* DMA2 Stream5 global interrupt */
    NVIC_IRQ_DMA2_STREAM6,              /* DMA2 Stream6 global interrupt */
    NVIC_IRQ_DMA2_STREAM7,              /* DMA2 Stream7 global interrupt */
    NVIC_IRQ_USART6,                    /* USART6 global interrupt */
    NVIC_IRQ_I2C3_EV,                   /* I2C3 event interrupt */
    NVIC_IRQ_I2C3_ER,                   /* I2C3 error interrupt */
    NVIC_IRQ_FPU = 81,                  /* FPU global interrupt */
    NVIC_IRQ_SPI4 = 84,                 /* SPI4 global interrupt */
} NVIC_IRQ_t;


/**
 * @brief Enumeration for NVIC priority grouping options.
 *
 * This enumeration provides options for configuring the priority grouping in the Nested Vectored Interrupt Controller (NVIC).
 * The priority grouping affects the distribution of priority bits between preemption and subpriority levels.
 * It can be configured to have different numbers of priority groups and subpriority bits.
 *
 * The values in this enumeration represent different priority grouping options:
 * - NVIC_PG_16GROUPS_0SUBGROUPS: 16 priority groups, 0 subpriority bits.
 * - NVIC_PG_8GROUPS_2SUBGROUPS: 8 priority groups, 2 subpriority bits.
 * - NVIC_PG_4GROUPS_4SUBGROUPS: 4 priority groups, 4 subpriority bits.
 * - NVIC_PG_2GROUPS_8SUBGROUPS: 2 priority groups, 8 subpriority bits.
 * - NVIC_PG_0GROUPS_16SUBGROUPS: 0 priority groups, 16 subpriority bits.
 *
 * These options are used to configure the NVIC priority grouping via the NVIC_SetPriorityGrouping() function.
 */
typedef enum
{
    NVIC_PG_16GROUPS_0SUBGROUPS  = (0x05FA0000UL), /**< 16 priority groups, 0 subpriority bits. */
    NVIC_PG_8GROUPS_2SUBGROUPS   = (0x05FA0400UL), /**< 8 priority groups, 2 subpriority bits. */
    NVIC_PG_4GROUPS_4SUBGROUPS   = (0x05FA0500UL), /**< 4 priority groups, 4 subpriority bits. */
    NVIC_PG_2GROUPS_8SUBGROUPS   = (0x05FA0600UL), /**< 2 priority groups, 8 subpriority bits. */
    NVIC_PG_0GROUPS_16SUBGROUPS  = (0x05FA0700UL)  /**< 0 priority groups, 16 subpriority bits. */
} NVIC_PG_t;

/**
 * @brief Enumeration for NVIC Pending Status.
 * 
 * The enumerators represent the NVIC pending status.
 */
typedef enum 
{
    NVIC_N_PENDING,   /**< NVIC interrupt is not pending */
    NVIC_PENDING,    /**< NVIC interrupt is pending */    
} NVIC_IsPending_t;

/**
 * @brief Enumeration for NVIC Active Status.
 * 
 * The enumerators represent the NVIC active status.
 */
typedef enum 
{
    NVIC_N_ACTIVE,   /**< NVIC interrupt is not active */
    NVIC_ACTIVE,    /**< NVIC interrupt is active */
} NVIC_IsActive_t;
/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Enable the specified NVIC interrupt.
 * 
 * @param NVIC_IRQ NVIC interrupt to be enabled.
 * @return MCAL_StatusTypeDef Status after enabling the interrupt.
 */
MCAL_StatusTypeDef NVIC_enableIRQ(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Disable the specified NVIC interrupt.
 * 
 * @param NVIC_IRQ NVIC interrupt to be disabled.
 * @return MCAL_StatusTypeDef Status after disabling the interrupt.
 */
MCAL_StatusTypeDef NVIC_disableIRQ(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Set the pending status for the specified NVIC interrupt.
 * 
 * @param NVIC_IRQ NVIC interrupt for which pending status is to be set.
 * @return MCAL_StatusTypeDef Status after setting the pending status.
 */
MCAL_StatusTypeDef NVIC_setPendingIRQ(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Clear the pending status for the specified NVIC interrupt.
 * 
 * @param NVIC_IRQ NVIC interrupt for which pending status is to be cleared.
 * @return MCAL_StatusTypeDef Status after clearing the pending status.
 */
MCAL_StatusTypeDef NVIC_clearPendingIRQ(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Get the pending status of the specified NVIC interrupt.
 * 
 * @param NVIC_IRQ NVIC interrupt to check for pending status.
 * @return NVIC_IsPending_t Pending status of the NVIC interrupt.
 */
NVIC_IsPending_t NVIC_getPendingIRQ(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Get the active status of the specified NVIC interrupt.
 * 
 * @param NVIC_IRQ NVIC interrupt to check for active status.
 * @return NVIC_IsActive_t Active status of the NVIC interrupt.
 */
NVIC_IsActive_t NVIC_getActiveStatus(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Generate a software interrupt for the specified NVIC_IRQ.
 *
 * This function generates a software interrupt for the specified Nested Vectored Interrupt Controller (NVIC) interrupt.
 *
 * @param NVIC_IRQ The NVIC_IRQ_t representing the interrupt for which a software interrupt should be generated.
 * @return MCAL_StatusTypeDef indicating the status of the operation
 *
 * @note When the USERSETMPEND bit in the SCR is set to 1, unprivileged access to this function is allowed
 */
MCAL_StatusTypeDef NVIC_generateSWInterrupt(NVIC_IRQ_t NVIC_IRQ);

/**
 * @brief Set the priority grouping for the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function sets the priority grouping in the NVIC according to the specified priority grouping option.
 * The priority grouping affects the distribution of priority bits between preemption and subpriority levels.
 * Different priority groupings may be suitable for different system configurations and interrupt handling requirements.
 *
 * @param PriorityGrouping The priority grouping option to be set for the NVIC.
 *                         
 *
 * @return MCAL_StatusTypeDef Status of the operation, indicating success or failure.
 */
MCAL_StatusTypeDef NVIC_setPriorityGrouping(NVIC_PG_t PriorityGrouping);


/**
 * @brief Set the priority of a specific interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function sets the priority of the specified interrupt in the NVIC, using the provided preemption and subpriority levels.
 * The priority values are based on the configured priority grouping.
 *
 * @param IRQ            The NVIC IRQ for which the priority is to be set.
 *
 * @param PriorityGrouping  The priority grouping option used to interpret the preemption and subpriority levels.
 *                          
 * @param Preemption     The preemption priority level to be assigned to the interrupt.
 * @param SubGroup       The subpriority level to be assigned to the interrupt.
 *
 * @return MCAL_StatusTypeDef Status of the operation, indicating success or failure.
 */
MCAL_StatusTypeDef NVIC_SetPriority(NVIC_IRQ_t IRQ, NVIC_PG_t PriorityGrouping, uint8_t Preemption, uint8_t SubGroup);










#endif // MCAL_NVIC_NVIC_H_