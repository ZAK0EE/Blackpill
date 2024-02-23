
/*
 * Switch_Cfg.c
 *
 * Created: 12/19/2023 10:41:36 AM
 *  Author: Ziad
 */ 

 
 #include "Switch.h"

 Switch_Config_t Switch_Configs[_NUM_OF_SWITCHES]=
 {
	 [SwWITCH_LEDTOGGLE]=
	 {
        .PortID = 0,
        .PinNum = 2,
        .ActiveType = SWITCH_ACTIVELOW,
        .PUConfig = SWITCH_ENABLE_INTERNALPU
	 },


 };