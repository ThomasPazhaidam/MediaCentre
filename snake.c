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
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
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
int glbFoodx = 0;
int glbFoody = 0;
int glbScore = 0;
struct SnakeProp
{
	int xPos;
	int yPos;
}; 

struct SnakeProp glbSnake[100];

int glbSnakeLen = 0;

int glbPrevJoystickVal = 0;
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
* LCD Refresh Rate
*******************************************************************************/
void LcdDelay (int count){
	int val= 10000000;
	val /= count;
	while(val--);
}
/******************************************************************************
* Generate food position
*******************************************************************************/
void GenerateFood()
{
	glbFoodx = (rand()%8)+1;
	glbFoody = (rand()&19);
	
	GLCD_SetTextColor(Red);
	GLCD_DisplayChar(glbFoodx, glbFoody, 1, 0x81); 
}


/******************************************************************************
* Update snake movement
*******************************************************************************/
void UpdateSnakeDirection(int JoystickPos)
{
	int i = 0;
	
	switch(JoystickPos)
	{
		case KBD_UP:
			if(glbPrevJoystickVal == KBD_LEFT || glbPrevJoystickVal == KBD_RIGHT)
			{
				glbSnake[0].xPos--;
			}
			break;
		case KBD_RIGHT:
			if(glbPrevJoystickVal == KBD_UP || glbPrevJoystickVal == KBD_DOWN)
			{
				glbSnake[0].yPos++;
			}
			break;		
		case KBD_LEFT:
			if(glbPrevJoystickVal == KBD_UP || glbPrevJoystickVal == KBD_DOWN)
			{
				glbSnake[0].yPos--;
			}
			break;		
		case KBD_DOWN:
			if(glbPrevJoystickVal == KBD_LEFT || glbPrevJoystickVal == KBD_RIGHT)
			{
				glbSnake[0].xPos++;
			}
			break;			
		default:
			switch(glbPrevJoystickVal)
			{
				case KBD_UP:
					glbSnake[0].xPos--;
					if(glbSnake[0].xPos <0)
						glbSnake[0].xPos = 9;
					break;
				case KBD_DOWN:
					glbSnake[0].xPos++;
					if(glbSnake[0].xPos >9)
						glbSnake[0].xPos = 0;
					break;
				case KBD_RIGHT:
					glbSnake[0].yPos++;
					if(glbSnake[0].yPos >20)
						glbSnake[0].yPos = 0;
					break;
				case KBD_LEFT:
					glbSnake[0].yPos--;
					if(glbSnake[0].yPos < 0)
						glbSnake[0].yPos = 20;
					break;
			}
			break;
	}
	if(JoystickPos == KBD_UP || JoystickPos == KBD_RIGHT || JoystickPos == KBD_LEFT ||JoystickPos == KBD_DOWN)
	{
		glbPrevJoystickVal = JoystickPos;
	}
	
	for(i = glbSnakeLen-1; i>0; --i)
	{
		GLCD_DisplayChar(glbSnake[i].xPos,glbSnake[i].xPos,1,' ');
		glbSnake[i].xPos = glbSnake[i-1].xPos;
		glbSnake[i].yPos = glbSnake[i-1].yPos;
	}
	GLCD_DisplayChar(glbSnake[0].xPos,glbSnake[0].yPos,1,0x89);
	for(i=1; i<glbSnakeLen; ++i)
	{
		GLCD_DisplayChar(glbSnake[i].xPos,glbSnake[i].yPos,1,0x89);
	}
}

/******************************************************************************
* Update Game State:
*******************************************************************************/
int UpdateState()
{
	int i = 0;
	if(glbFoodx == glbSnake[0].xPos && glbFoodx == glbSnake[0].yPos)
	{
		glbSnakeLen++;
		glbScore++;
		GenerateFood();
	}
	
	for(i=1;i<glbSnakeLen;i++){
		if(glbSnake[i].xPos == glbSnake[0].xPos && glbSnake[i].yPos == glbSnake[0].yPos)
				 return 1;
	}
	
	return 0;
}
/******************************************************************************
* main.c
*******************************************************************************/
void InitializeSnakeGame()
{
	int i = 0;
	int speed = 0;
	int joystick = 0;
	int menuIndex = 0;
	int gameOver = 0;
	glbPrevJoystickVal = KBD_LEFT;
	
	
	glbSnakeLen = 2;
	glbScore=0;
	
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
			break;
		}
	} 
	
	memset(&glbSnake, 0, sizeof(glbSnake));
	
	for(i = 0; i<glbSnakeLen; i++)
	{
		glbSnake[i].xPos = 4-i;
		glbSnake[i].yPos = 9;
	}
	
	GenerateFood();
	while(!gameOver)
	{
		joystick = get_button();
		UpdateSnakeDirection(joystick);
		LcdDelay(speed);
		gameOver = UpdateState();
	}

	GLCD_Clear(White);
	GLCD_SetBackColor(White);

	InitializeSnakeGame();
}
