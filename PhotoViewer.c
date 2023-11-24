/*******************************************************************************
* Filename              :   PhotoViewer.c
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
#include "giorno.c"
#include "anos.c"
#include "goku.c"
#include "kaido.c"
#include "saitama.c"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define IMAGEX 115
#define IMAGEY 50
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
extern void Delay(int multiplier);
/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Display image
*******************************************************************************/
void DisplayImage (int PhotoIndex)
{
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	switch(PhotoIndex)
	{
		case 0:
			GLCD_DisplayString(9, 0, 1, (unsigned char*)"<       Anos       >");
			GLCD_Bitmap(IMAGEX, IMAGEY, 100, 100, (unsigned char*)ANOS_pixel_data);
			break;
		case 1:
			GLCD_DisplayString(9, 0, 1, (unsigned char*)"<      Giorno      >");
			GLCD_Bitmap(IMAGEX, IMAGEY, 100, 100, (unsigned char*)GIORNO_pixel_data);
			break;
		case 2:
			GLCD_DisplayString(9, 0, 1, (unsigned char*)"<       Goku       >");
			GLCD_Bitmap(IMAGEX, IMAGEY, 100, 100, (unsigned char*)goku);
			break;
		case 3:
			GLCD_DisplayString(9, 0, 1, (unsigned char*)"<       Kaido      >");
			GLCD_Bitmap(IMAGEX, IMAGEY, 100, 100, (unsigned char*)kaido);
			break;
		case 4:
			GLCD_DisplayString(9, 0, 1, (unsigned char*)"<     Saitama      >");
			GLCD_Bitmap(IMAGEX, IMAGEY, 100, 100, (unsigned char*)SAITAMA_pixel_data);
			break;
	}
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
}
/******************************************************************************
* Photo viewer program
*******************************************************************************/
void StartPhotoViewer (void)
{
	int joystick = 0;
	int photoIndex = 0;
	
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	
	GLCD_DisplayString(0, 0, 1, (unsigned char*)"       Gallery       ");
	GLCD_DisplayString(8, 0, 1, (unsigned char*)"Push select to exit");
	DisplayImage(photoIndex);
	while(1)
	{
		joystick = get_button();
		
		if(joystick == KBD_LEFT)
		{
			photoIndex == 0?(photoIndex = 4):(photoIndex--);
			DisplayImage(photoIndex);
		}
		else if(joystick == KBD_RIGHT)
		{
			photoIndex == 4?(photoIndex = 0):(photoIndex++);
			DisplayImage(photoIndex);
		}
		else if(joystick == KBD_SELECT)
		{
			break;
		}
		
		Delay(7000);
	}
	
}
