/**
 * @file Switch.h
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Header file for switch driver
 * @version 0.1
 * @date 2024-02-23
 * @copyright Copyright (c) 2024
 */

#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_



/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <stdint.h>
#include "Switch_cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/* Enumeration for Switch-related errors */
typedef enum {
    SWITCH_OK,      /**< Operation successful */
    SWITCH_NOK      /**< Operation not successful */
} Switch_Error_t;

/* Enumeration for Switch active types (active high/low) */
typedef enum {
    SWITCH_ACTIVEHIGH, /**< Active high configuration */
    SWITCH_ACTIVELOW   /**< Active low configuration */
} Switch_ActiveType_t;

/* Enumeration for Switch states (pressed/released) */
typedef enum {
    SWITCH_RELEASED,  /**< Switch is released */
    SWITCH_PRESSED,   /**< Switch is pressed */
} Switch_StateType_t;

typedef enum {
    SWITCH_ENABLE_INTERNALPU,   /**< Enable internal pull-up for the Switch */
    SWITCH_DISABLE_INTERNALPU   /**< Disable internal pull-up for the Switch */
} Switch_InternalPullupConfig_t;


/* Structure to hold Switch configurations */
typedef struct {
    uint32_t PortID;              /**< Port ID associated with the Switch */
    uint32_t PinNum;              /**< Pin number associated with the Switch */
    Switch_InternalPullupConfig_t PUConfig; /**< Configuration for internal pull-up */
    Switch_ActiveType_t ActiveType; /**< Active type of the Switch (high/low) */
} Switch_Config_t;

extern Switch_Config_t Switch_Configs[_NUM_OF_SWITCHES];


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Initialize Switch configurations based on Switch_Configs array.
 * @note The Switch_Configs array must be properly configured before calling this function.
 * @return Switch_Error_t Error status after initialization.
 */
Switch_Error_t Switch_init(void);

/**
 * @brief Get the state of the specified Switch.
 * @param SwitchID ID of the Switch to get the state.
 * @note You must call Switch_init first
 * @return Switch_StateType_t State of the Switch.
 */
Switch_StateType_t Switch_getSwitchState(uint32_t SwitchID);

/**
 * @brief Task function to check the state of switches.
 * 
 * This function is responsible for periodically checking the state of switches
 * and performing any necessary actions based on the switch state. It should be
 * called periodically by the scheduler to ensure timely switch state updates.
 */
void Switch_Task_CheckState(void);

/**
 * @brief Asynchronously retrieves the state of a switch.
 * 
 * This function asynchronously retrieves the state of the specified switch
 * without waiting for the switch state to be polled or updated. It returns
 * the current state of the switch.
 * 
 * @param SwitchID The ID of the switch to retrieve its state.
 * @note Switch_Task_CheckState must be functioning for this function
 * to be working right
 * @return Switch_StateType_t The current state of the switch (pressed or released).
 */
Switch_StateType_t Switch_getSwitchStateAsync(uint32_t SwitchID);


#endif /* HAL_SWITCH_SWITCH_H_ */
