/*******************************************************************************
* Filename              :   main.c
* Author                :   Thomas Pazhaidam
* Origin Date           :   11/17/2023
* Version               :   0.0.1
* Compiler              :   uVision5 
* Notes                 :   None
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                       // CMSIS RTOS header file
#include <stdio.h>
#include "RTE_Components.h"            		 // Component selection
#include "GLCD.h"      
#include "KBD.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
enum DIR
{
	UP = 0, DOWN = 1, LEFT = 2, RIGHT =3
};
/******************************************************************************
* Function Prototypes
*******************************************************************************/
/******************************************************************************
* Function Externs
*******************************************************************************/
extern int UpdateItemSelection(int ItemIndex, int JoystickVal, int MaxIndex);
/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* update what is displayed in main menu based on item index
*******************************************************************************/
void UpdateDifficultyGlcdSelection(int ItemIndex) 
{
	
	unsigned char itemNames[4][256] = {"       EASY         ", "       MEDIUM       ", "       HARD         ", "        RETURN       "};
	int i = 0;
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	
	for(i = 0; i<4; i++)
	{
		if(i == ItemIndex)
		{
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(White);
		}
		else
		{
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Black);
		}
		GLCD_DisplayString(i+4, 0, 1, itemNames[i]);
	}
}
/******************************************************************************
* main.c
*******************************************************************************/
void InitializeSnakeGame()
{
	int joystick = 0;
	int menuIndex = 0;
	int snakeDirection = LEFT;
	int prevSnakeDirection = LEFT;
	int snakeLen = 2;
	int snakePosX = 4;
	int snakePosY = 9;
	int speed = 0;
	
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, 1, (unsigned char*)"     Snake Game     ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	
	while(1)
	{
		joystick = get_button();
		menuIndex = UpdateItemSelection(menuIndex, joystick, 3);
		UpdateDifficultyGlcdSelection(menuIndex);
		if(joystick == KBD_SELECT)
		{
			switch(menuIndex)
			{
				case 0:
					speed = 2;
					break;
				case 1:
					speed = 4;
					break;
				case 2:
					speed = 6;
					break;
				case 3:
					return;
			}
		}
	}
	
}
