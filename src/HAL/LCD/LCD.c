/**
 * @file LCD.c
 * @author Ziad Gamalelden (ziad.gamalelden@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LCD.h"
#include "LCD_Cfg.h"
#include "MCAL/GPIO/GPIO.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define LCD_TIMEMS_WAKEUP 31UL
#define LCD_TIMEMS_SEND   1UL
#define LCD_TIMEMS_FUNCTIONSET 1UL
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum
{
    LCD_PHS_INIT,
    LCD_PHS_OPERATION,
}
PhaseState_t;

typedef enum
{
    LCD_OPERATION_NONE,
    
}
OperationState_t;

typedef enum
{
    LCD_INIT_PINS,
    LCD_INIT_FUNCTION_SET,
    LCD_INIT_DISPLAY_CONTROL,
    LCD_INIT_DISPLAY_CLEAR,
    LCD_INIT_ENTRYMODE_SET,
}
InitStep_t;

typedef enum
{
    LCD_WRITECMD_READY,
    LCD_WRITECMD_WRITEPINS_4BIT,
    LCD_WRITECMD_TRIGGER,
    LCD_WRITECMD_TRIGGER_4BIT,
}WriteCommandState_t;

typedef enum
{
    GENERALSTATE_DONE,
    GENERALSTATE_N_DONE,
}GeneralState_t;
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
static LCD_State_t UserState = LCD_STATE_BUSY;
static PhaseState_t CurrentPhase = LCD_PHS_INIT;
static OperationState_t CurrentOperation = LCD_OPERATION_NONE;
static InitStep_t CurrentInitStep = LCD_INIT_PINS;
static WriteCommandState_t CurrentWriteCommandState[_NUM_OF_LCDS] = {LCD_WRITECMD_READY};
static uint32_t elapsedTimeMS = 0;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/**
 * @brief Initializes the LCD.
 */
static void Init(void);
static void Operate(void);

/* Initialization functions */
static void PinsInit(void);

static void WriteCommand(LCD_ID LCD_ID, uint8_t Command);
static void WritePins(LCD_ID LCD_ID, uint8_t value);
/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

static void WritePins(LCD_ID LCD_ID, uint8_t value)
{
 	LCD_Config_t const *CurrentLCD = &(LCD_Config[LCD_ID]);

	GPIO_Port_t		    PortID;
	GPIO_Pin_t		    PinNum;
	GPIO_PinState_t    PinState;

	uint8_t LCDPinCounter = 0;
	uint8_t NumOfPins = (CurrentLCD->DataLength == LCD_DL_8BIT) ? 8 : 4;

	for(LCDPinCounter = 0; LCDPinCounter < NumOfPins; LCDPinCounter++)
	{
		PortID		= CurrentLCD->Pins[LCDPinCounter].PortID;
		PinNum		= (GPIO_Pin_t)CurrentLCD->Pins[LCDPinCounter].PinNum;
		PinState = (((value  >> LCDPinCounter) & 1 ) == 1) ? GPIO_PINSTATE_SET : GPIO_PINSTATE_RESET;

		GPIO_setPinValue(PortID, PinNum, PinState);	
	}
   
}
static void WriteCommand(LCD_ID LCD_ID, uint8_t Command)
{
    LCD_Config_t const *CurrentLCD = &(LCD_Config[LCD_ID]);

    GPIO_Port_t		RSPortID  = (GPIO_Port_t)CurrentLCD->RSPin.PortID;
    GPIO_Pin_t		RSPinNum  = (GPIO_Pin_t)CurrentLCD->RSPin.PinNum;
    GPIO_PinState_t RSPinState =  GPIO_PINSTATE_RESET; 

	GPIO_Port_t		ENPortID  = (GPIO_Port_t)CurrentLCD->EnablePin.PortID;
	GPIO_Pin_t		ENPinNum  = (GPIO_Pin_t)CurrentLCD->EnablePin.PinNum;
    switch(CurrentWriteCommandState[LCD_ID])
    {        
        case LCD_WRITECMD_READY:
        {
            /* R/W is low for command */
            GPIO_setPinValue(RSPortID, RSPinNum, RSPinState);
            
            if(CurrentLCD->DataLength == LCD_DL_8BIT)
            {
                WritePins(LCD_ID, Command);

            }
            else
            {
                WritePins(LCD_ID, Command >> 4);
                
            }

            /* Start Send */
            GPIO_setPinValue(ENPortID, ENPinNum, GPIO_PINSTATE_SET);
            
            CurrentWriteCommandState[LCD_ID] = LCD_WRITECMD_TRIGGER;      
            break;
        }
        case LCD_WRITECMD_TRIGGER:
        {
            if(CurrentLCD->DataLength == LCD_DL_4BIT)
            {
                CurrentWriteCommandState[LCD_ID] = LCD_WRITECMD_WRITEPINS_4BIT;
            }
            else
            {
                /* Send is done*/
                GPIO_setPinValue(ENPortID, ENPinNum, GPIO_PINSTATE_RESET);
                CurrentWriteCommandState[LCD_ID] = LCD_WRITECMD_READY;
            }
            break;
        }        
        case LCD_WRITECMD_WRITEPINS_4BIT:
        {
            WritePins(LCD_ID, Command);
            GPIO_setPinValue(ENPortID, ENPinNum, GPIO_PINSTATE_SET);

            break;
        }

        case LCD_WRITECMD_TRIGGER_4BIT:
        {
            /* Send is done*/
            GPIO_setPinValue(ENPortID, ENPinNum, GPIO_PINSTATE_RESET);            
            CurrentWriteCommandState[LCD_ID] = LCD_WRITECMD_READY;
            break;
        }

    }

}


static void PinsInit(void)
{
    /* Initializing all LCDs */
    LCD_ID LCD_ID = 0;
    for(LCD_ID = 0; LCD_ID < _NUM_OF_LCDS; LCD_ID++)        
    {
        LCD_Config_t const *CurrentLCD = &(LCD_Config[LCD_ID]);

        /* Initializing current LCD pins' direction */
        uint8_t LCDPinCounter = 0;
        uint8_t NumOfPins = (CurrentLCD->DataLength == LCD_DL_8BIT) ? 8 : 4;
        GPIO_PinConfig_t PinConfig;
        for(LCDPinCounter = 0; LCDPinCounter < NumOfPins; LCDPinCounter++)
        {
            PinConfig.Port	        = (GPIO_Port_t)CurrentLCD->Pins[LCDPinCounter].PortID;
            PinConfig.PinNumber		= (GPIO_Pin_t)CurrentLCD->Pins[LCDPinCounter].PinNum;
            PinConfig.PinSpeed      = GPIO_SPEED_MEDIUM;
            PinConfig.PinMode       = GPIO_MODE_OUTPUT_PUSHPULL_NOPULL;
            GPIO_initPin(&PinConfig);
        }

        /* Initializing current RS pin direction */
        PinConfig.Port		    = (GPIO_Port_t)CurrentLCD->RSPin.PortID;
        PinConfig.PinNumber		= (GPIO_Pin_t)CurrentLCD->RSPin.PinNum;
        GPIO_initPin(&PinConfig);


        /* Initializing current Enable pin direction */
        PinConfig.Port		    = (GPIO_Port_t)CurrentLCD->EnablePin.PortID;
        PinConfig.PinNumber		= (GPIO_Pin_t)CurrentLCD->EnablePin.PinNum;
        GPIO_initPin(&PinConfig);
    }
}

void LCD_task(void)
{
    switch(CurrentPhase)
    {
        case LCD_PHS_INIT:
            Init();
            break;
        
        case LCD_PHS_OPERATION:
            Operate();
            break;
    }
    elapsedTimeMS++;
}
void Init(void)
{

    switch(CurrentInitStep)
    {
        case LCD_INIT_PINS:
        {

            PinsInit();
            elapsedTimeMS = 0;
            CurrentInitStep++;

            break;
        }
        case LCD_INIT_FUNCTION_SET:
        {
            if(elapsedTimeMS >= LCD_TIMEMS_WAKEUP)
            { 
                
                LCD_ID LCD_ID = 0;
                for(LCD_ID = 0; LCD_ID < _NUM_OF_LCDS; LCD_ID++)        
                {
                    LCD_Config_t const *CurrentLCD = &(LCD_Config[LCD_ID]);        
                    uint8_t FunctionSetCommand = 0;

                    FunctionSetCommand = (1 << 5) | (CurrentLCD->DataLength << 4) | (1 << 3) | (CurrentLCD->Font << 2);

                    if(CurrentLCD->DataLength == LCD_DL_4BIT)
                    {
                        WriteCommand(LCD_ID, 0b0010);
                    }
                    WriteCommand(LCD_ID, FunctionSetCommand);
                    
                }
                if(CurrentWriteCommandState[0] == LCD_WRITECMD_READY && elapsedTimeMS > 8)
                {
                    CurrentInitStep++;
                    elapsedTimeMS = 0;

                }                        

            }

            break;
        }

        case LCD_INIT_DISPLAY_CONTROL:
        {
            /* Display ON/OFF Control */
            LCD_ID LCD_ID = 0;
            for(LCD_ID = 0; LCD_ID < _NUM_OF_LCDS; LCD_ID++)
            {
                LCD_Config_t const *CurrentLCD = &(LCD_Config[LCD_ID]);

                uint8_t cmd = 0;
                cmd = (1 << 3) | (1 << 2) | (CurrentLCD->CursorState << 1) | (CurrentLCD->CursorBlinkingState >> 0);
                WriteCommand(LCD_ID, cmd);                
            }        
            if(CurrentWriteCommandState[0] == LCD_WRITECMD_READY && elapsedTimeMS > 8)
            {
                CurrentInitStep++;
                elapsedTimeMS = 0;

            }

            break;
        }
        case LCD_INIT_DISPLAY_CLEAR:
        {
             /* Display Clear */
            LCD_ID LCD_ID = 0;
            for(LCD_ID = 0; LCD_ID < _NUM_OF_LCDS; LCD_ID++)
            {
                uint8_t cmd = 0;
                cmd = 1;
                WriteCommand(LCD_ID, cmd);                
            }        
            
            if(CurrentWriteCommandState[0] == LCD_WRITECMD_READY && elapsedTimeMS > 8)
            {
                CurrentInitStep++;
                elapsedTimeMS = 0;

            }           
            break;
        }
        case LCD_INIT_ENTRYMODE_SET:
        {
             /* Display Clear */
            LCD_ID LCD_ID = 0;
            for(LCD_ID = 0; LCD_ID < _NUM_OF_LCDS; LCD_ID++)
            {
                uint8_t cmd = 0;
                cmd |= (1 << 2) | (1 << 1) | (0 << 0);
                WriteCommand(LCD_ID, cmd);                
            }        
            
            if(CurrentWriteCommandState[0] == LCD_WRITECMD_READY && elapsedTimeMS > 5)
            {
                CurrentPhase = LCD_PHS_OPERATION;
                elapsedTimeMS = 0;

            }           
            break;
        }
    }

 
}

static void Operate(void)
{

}
LCD_State_t LCD_getState(void){return LCD_STATE_READY;}
void LCD_clearScreenAsync(LCD_ID ID){}
void LCD_setCursorPositionAsync(LCD_ID ID){}
void LCD_writeStringAsync(LCD_ID ID, char* str, uint32_t len){}