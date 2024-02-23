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
 * @brief Validate Switch_InternalPullupConfig_t enum values.
 */
#define IS_SWITCH_INTERNAL_PULLUP_CONFIG(config) (((config) == SWITCH_ENABLE_INTERNALPU) || ((config) == SWITCH_DISABLE_INTERNALPU))

/**
 * @brief Validate Switch_ActiveType_t enum values.
 */
#define IS_SWITCH_ACTIVE_TYPE(activeType) (((activeType) == SWITCH_ACTIVEHIGH) || ((activeType) == SWITCH_ACTIVELOW))


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



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

        GPIO_initPin(&CurrentPin);        

    }
	
	return SWITCH_OK;
}

Switch_StateType_t Switch_getSwitchState(uint32_t SwitchID)
{
	GPIO_PortTypeDef	PortID		= (GPIO_PortTypeDef)Switch_Configs[SwitchID].PortID;
	GPIO_PinTypeDef		PinNum		= (GPIO_PinTypeDef)Switch_Configs[SwitchID].PinNum;
	Switch_ActiveType_t	ActiveType	= Switch_Configs[SwitchID].ActiveType;

	GPIO_PinStateTypeDef PinRead = GPIO_getPinValue(PortID, PinNum);

    Switch_StateType_t SwitchState = (Switch_StateType_t)PinRead ^ (Switch_StateType_t)ActiveType;

	return SwitchState;
}