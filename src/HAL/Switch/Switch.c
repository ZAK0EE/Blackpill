/**
 * @file Switch.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief Source file for switch driver
 * @version 0.1
 * @date 2024-02-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Switch.h"
#include "MCAL/GPIO/GPIO.h"
#include "assertparam.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/**
 * @brief Validate Switch ID.
 */
#define IS_SWITCH_ID(switchID) ((switchID) < _NUM_OF_SWITCHES)

/**
 * @brief Validate Switch_InternalPullupConfig_t enum values.
 */
#define IS_SWITCH_INTERNAL_PULLUP_CONFIG(config) (((config) == SWITCH_ENABLE_INTERNALPU) || ((config) == SWITCH_DISABLE_INTERNALPU))

/**
 * @brief Validate Switch_ActiveType_t enum values.
 */
#define IS_SWITCH_ACTIVE_TYPE(activeType) (((activeType) == SWITCH_ACTIVEHIGH) || ((activeType) == SWITCH_ACTIVELOW))

/**
 * @brief Threshold for consecutive same states of a switch.
 * 
 */
#define SWITCH_CONSECUTIVE_SAME_STATE_THRESHOLD 3

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Structure representing the state of a task related to switch handling.
 * 
 * This structure holds information about the press state of a switch and a counter
 * used to track repeated reads of the same state. It is typically used within tasks
 * that involve monitoring switch states and performing actions based on those states.
 */
typedef struct
{
    Switch_StateType_t PressState;           /**< The current state of the switch (pressed or released). */
    uint32_t ConsecutiveSameStateCount;      /**< Counter for tracking repeated reads of the same switch state that's different to current state. */
} Task_State;

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

/**
 * @brief Array holding the state information for each switch task.
 * 
 * This array stores the state information for each switch task.
 */
static Task_State SwitchesStates[_NUM_OF_SWITCHES];

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

Switch_Error_t Switch_init(void)
{
	Switch_Config_t  *CurrentSwitch;
    GPIO_PinConfigTypeDef CurrentPin;

    /* Initializing all Switches pins' direction */
    uint32_t SwitchCounter = 0;
    for(SwitchCounter = 0; SwitchCounter < (uint32_t)_NUM_OF_SWITCHES; SwitchCounter++)
    {
        CurrentSwitch = &(Switch_Configs[SwitchCounter]);

        /* Validating Switch parameters*/
        assert_param(IS_SWITCH_ACTIVE_TYPE(CurrentSwitch->ActiveType));
        assert_param(IS_SWITCH_INTERNAL_PULLUP_CONFIG(CurrentSwitch->PUConfig));

        /* Set the switch pin configuration */ 
        CurrentPin.Port		    = (GPIO_PortTypeDef)CurrentSwitch->PortID;
        CurrentPin.PinNumber	= (GPIO_PinTypeDef)CurrentSwitch->PinNum;
        CurrentPin.PinSpeed     = GPIO_SPEED_MEDIUM;
        CurrentPin.PinMode	    = (CurrentSwitch->PUConfig == SWITCH_ENABLE_INTERNALPU) ?
                                    GPIO_MODE_INPUT_PULLUP : GPIO_MODE_INPUT_NOPULL; 

        /* Initialize task states */
        SwitchesStates[SwitchCounter].PressState = SWITCH_RELEASED;
        SwitchesStates[SwitchCounter].ConsecutiveSameStateCount = 0;

        GPIO_initPin(&CurrentPin);
    }
	
	return SWITCH_OK;
}

Switch_StateType_t Switch_getSwitchState(uint32_t SwitchID)
{
    assert_param(IS_SWITCH_ID(SwitchID));
    
	GPIO_PortTypeDef	PortID		= (GPIO_PortTypeDef)Switch_Configs[SwitchID].PortID;
	GPIO_PinTypeDef		PinNum		= (GPIO_PinTypeDef)Switch_Configs[SwitchID].PinNum;
	Switch_ActiveType_t	ActiveType	= Switch_Configs[SwitchID].ActiveType;

	GPIO_PinStateTypeDef PinRead = GPIO_getPinValue(PortID, PinNum);

    Switch_StateType_t SwitchState = (Switch_StateType_t)PinRead ^ (Switch_StateType_t)ActiveType;

	return SwitchState;
}

void Switch_Task_CheckState(void)
{
    for(uint8_t SwitchCounter = 0; SwitchCounter <  (uint32_t)_NUM_OF_SWITCHES; SwitchCounter++)
    {
        Switch_StateType_t CurrentSwitchState = Switch_getSwitchState(SwitchCounter);

        if(CurrentSwitchState != SwitchesStates[SwitchCounter].PressState)
        {
            SwitchesStates[SwitchCounter].ConsecutiveSameStateCount++;
        }
        else
        {
            SwitchesStates[SwitchCounter].ConsecutiveSameStateCount = 0;
        }

        if(SwitchesStates[SwitchCounter].ConsecutiveSameStateCount == SWITCH_CONSECUTIVE_SAME_STATE_THRESHOLD)
        {
            SwitchesStates[SwitchCounter].PressState = CurrentSwitchState;
        }

        
    }
}

Switch_StateType_t Switch_getSwitchStateAsync(uint32_t SwitchID)
{
    assert_param(IS_SWITCH_ID(SwitchID));
	return SwitchesStates[SwitchID].PressState;
}