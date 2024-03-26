/**
 * @file LCD_fg.h
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/**
 * @brief Periodicity of the LCD task in milliseconds.
 */
#define LCD_TASK_PERIODICITYMS 1UL



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Enumeration representing LCD identifiers.
 */
typedef enum
{
    LCD1,            /**< Identifier for the first LCD */
    LCD2,
    _NUM_OF_LCDS,     /**< Total number of LCDs ^^DO NOT MODIFY^^ */
} LCD_ID;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/




























#endif // HAL_LCD_LCD_CFG_H_