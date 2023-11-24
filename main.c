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
/*
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                       // CMSIS RTOS header file
*/
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

/******************************************************************************
* Function Prototypes
*******************************************************************************/
/******************************************************************************
* Function Externs
*******************************************************************************/
extern void LaunchMusicPlayer (void);
extern void StartPhotoViewer (void);
extern void InitializeSnakeGame(void);
/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Initialize device modules
*******************************************************************************/
int Initialize_LPC1768()
{
	KBD_Init();
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0, 4, 1, (unsigned char*)"  Main Menu");
	
	return 0;
}

/******************************************************************************
* Delay function
*******************************************************************************/
void Delay(int multiplier) 
{
	int c = 0;
	while( c++ < (multiplier*100)){}
}
/******************************************************************************
* update main menu item index
*******************************************************************************/
int UpdateItemSelection(int ItemIndex, int JoystickVal, int MaxIndex) 
{
	int newItemIndex = 0;
	switch(JoystickVal){
		case KBD_UP:
			if(ItemIndex == 0)
			{
				newItemIndex = 2;
			}
			else
			{
				newItemIndex = ItemIndex - 1;
			}
			break;
		case KBD_DOWN:
			if(ItemIndex == MaxIndex)
			{
				newItemIndex = 0;
			}
			else
			{
				newItemIndex = ItemIndex + 1;
			}			
			break;
		default:
			newItemIndex = ItemIndex;
		}	

		return newItemIndex;
}

/******************************************************************************
* update what is displayed in main menu based on item index
*******************************************************************************/
void UpdateGlcdItemSelection(int ItemIndex) 
{
	
	unsigned char itemNames[3][256] = {"Gallery", "Music Player", "Snake"};
	int i = 0;
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	
	for(i = 0; i<3; i++)
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
* Launch selected application
*******************************************************************************/
void OpenSelectedItem(int ItemIndex) 
{
	switch (ItemIndex)
	{
	case 0:
		StartPhotoViewer();
		break;
	case 1:
		LaunchMusicPlayer();
		break;
	case 2:
		InitializeSnakeGame();
		break;
	}
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0, 4, 1, (unsigned char*)"  Main Menu");
}
/******************************************************************************
* main.c
*******************************************************************************/
int main( void )
{
	int joystickVal = 0;
	int itemIndex = 0;
	Initialize_LPC1768();
	
	while(1)
	{
		joystickVal = get_button();
		itemIndex = UpdateItemSelection(itemIndex, joystickVal, 2);
		UpdateGlcdItemSelection(itemIndex);
		if(joystickVal == KBD_SELECT)
		{
			OpenSelectedItem(itemIndex);
		}
		Delay(7000);
	}
}
