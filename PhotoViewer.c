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
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                       // CMSIS RTOS header file
#include <stdio.h>
#include "RTE_Components.h"            		 // Component selection
#include "GLCD.h"      
#include "KBD.h"

#include "flower.c"
#include "landscape.c"
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

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Display image
*******************************************************************************/
void DisplayImage (int PhotoIndex)
{
	switch(PhotoIndex)
	{
		case 0:
			GLCD_DisplayString(0, 6, 0, (unsigned char*)"<      Flower       >");
			GLCD_Bitmap(0, 10, 320, 240, (unsigned char*)FLOWER_pixel_data);
			break;
		case 1:
			GLCD_DisplayString(0, 6, 0, (unsigned char*)"<     Landscape     >");
			GLCD_Bitmap(0, 10, 320, 240, (unsigned char*)AUTUMNLANDSCAPE_pixel_data);
			break;
	}
}
/******************************************************************************
* Photo viewer program
*******************************************************************************/
void StartPhotoViewer ()
{
	int joystick = 0;
	int photoIndex = 0;
	
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	
	GLCD_DisplayString(0, 4, 1, (unsigned char*)"Gallery");
	GLCD_DisplayString(0, 5, 0, (unsigned char*)"Push joystic to exit.");
	GLCD_DisplayString(0, 6, 0, (unsigned char*)"<                   >");
	
	while(1)
	{
		joystick = get_button();
		
		if(joystick == KBD_UP || joystick == KBD_DOWN)
		{
			photoIndex = !photoIndex; //only have 2 images because of storage limitations
		}
		else if(joystick == KBD_SELECT)
		{
			break;
		}
	}
	
}
