/**
* @file 		lnaStateMachine.c
* @brief		lnaStateMachine.c source file
* @author		juan andres
* @date			Created on 2023-07-12
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "trajectoryCalculator.h"



/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */





/* Exported functions ------------------------------------------------------- */

void vTrajectoryCalculatorRun( eBool_t bIsStep50mA, uint16_t usSetpoint, uint16_t usCurrentRead,  uint16_t *pNumberOfSteps, eBool_t *pbIncrease)
{
	
	uint16_t usDeltaRange = 0;
	uint16_t usStepSize =0;
	
	
	usStepSize = ( bIsStep50mA == eTrue )? MAX_CURRENT_INCREASE_BY_STEP : MAX_CURRENT_INCREASE_BY_STEP_500;
	
	
	
	if( usSetpoint - usCurrentRead > 0)
	{
		usDeltaRange = usSetpoint - usCurrentRead ;
		*pbIncrease = eTrue;
	}
	else
	{
		usDeltaRange =  usCurrentRead - usSetpoint  ;
		*pbIncrease = eFalse;
	}
	
	/*---*/		
	if(  usDeltaRange < usStepSize)
	{
		*pNumberOfSteps = 1;
	}
	else
	{
		*pNumberOfSteps = (uint16_t)((usDeltaRange / usStepSize)+0.5);	
	}
	
}
/*------------------------------------------------------------------------------*/
/*
void vTrajectoryCalculatorApcRun( eBool_t bIsInApcMode, float fInitialError,  uint16_t *pNumberOfSteps) 
{
	
	if( bIsInApcMode == eTrue )
	{
		
		if(  fInitialError < CURRENT_INCREASE_BY_STEP_IN_W)
		{
			*pNumberOfSteps = 1;
		}
		else
		{
			*pNumberOfSteps = (uint16_t)((fInitialError / CURRENT_INCREASE_BY_STEP_IN_W)+0.5);
		}
	}
	
	


}*/

/*------------------------------------------------------------------------------*/
