/**
* @file 		GlueBinary.c
* @brief		GlueBinary source file.
* @author		juan
* @date			Created on 2023-04-07
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2022 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "glue.h"
#include "BSPGpio.h"
//#include "ProjectDef.h"
//#include "main.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
/*
eMpbError_t eMpblibsBinaryToggle( handle_t xBINARYx )
{
    BSPGpioMap_t	xGpio_Map;
    
    //get gpio port and pin info 
    vBSPGpioGetMap ( xBINARYx, &xGpio_Map );
	
    HAL_GPIO_TogglePin( xGpio_Map.pxPort, xGpio_Map.usPin );
    
    return eSuccess;
}*/
/*----------------------------------------------------------------------------*/

eMpbError_t eMpblibsBinaryWrite( handle_t xBINARYx, eBool_t bState )
{
	BSPGpioMap_t	xGpio_Map;
	uint32_t val =0;
    
  /* get gpio port and pin info */
  vBSPGpioGetMap ( xBINARYx, &xGpio_Map );
	
	if( bState == eTrue )
	{		
		 val = xGpio_Map.usPin;		
	}
	
	 GPIO_SetOutput( xGpio_Map.usPin, xGpio_Map.pxPort, bState );
	
    
    return eSuccess;
}

/*----------------------------------------------------------------------------*/

