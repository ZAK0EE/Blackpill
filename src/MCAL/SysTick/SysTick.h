#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <stdint.h>
#include "SysTick_Cfg.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Enumeration for SysTick clock sources.
 */
typedef enum {
    SYSTICK_CLK_AHB_DIV_8,   /**< SysTick clock source: AHB divided by 8 */
    SYSTICK_CLK_AHB          /**< SysTick clock source: AHB */
} SysTick_ClockSource_t;

/**
 * @brief Enumeration for SysTick exception states.
 */
typedef enum {
    SYSTICK_EXCEPTION_ENABLED,    /**< SysTick exception is enabled */
    SYSTICK_EXCEPTION_DISABLED    /**< SysTick exception is disabled */
} SysTick_ExceptionState_t;

/**
 * @brief Structure for SysTick configuration.
 */
typedef struct {
    SysTick_ClockSource_t ClockSource;          /**< SysTick clock source */
    SysTick_ExceptionState_t ExceptionState;    /**< SysTick exception state */
} SysTick_Config_t;




/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Initializes the SysTick timer with the specified configuration.
 * 
 * @param config Configuration for SysTick initialization.
 */
void SysTick_init(SysTick_Config_t config);

/**
 * @brief Starts the SysTick timer with a specified duration in milliseconds.
 * 
 * @param timeMS Time duration in milliseconds.
 */
void SysTick_startTimerMS(uint32_t timeMS);

/**
 * @brief Starts the SysTick timer with a specified number of ticks.
 * 
 * @param ticks Number of ticks to start the SysTick timer with.
 * 
 * @note The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF. 
 * @note A start value of 0 is possible, but has no effect because the SysTick exception request and COUNTFLAG are
 * activated when counting from 1 to 0.
 */
void SysTick_startTickCounter(uint32_t ticks);


























#endif // MCAL_SYSTICK_SYSTICK_H_