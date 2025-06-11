/**
* @file 		initMemory.c
* @brief		initMemory.c source file
* @author		juan andres
* @date			Created on 2024-9-9
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2024 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "initMemory.h"
#include "lnaStateMachine.h"
#include "controlLaserPID.h"
#include "boosterStateMachine.h"
#include "mainStateMachineGetData.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
/*------------------------------------------------------------------------------*/
void vInitLnaRun(void)
{
	vLnaStateMachineInit();

	if( eFalse == bInitLnaMemoryImageFromNvm() )
	{
		vCurrentSensorsFactoryInitLnaChannels();		
		ePowerSensorsFactoryInitLnaChannels();
					//vLnaThermistorFactoryInitChannels();
		vLnaCurrentControlInit( );
		vSetLnaPidDefaultValues();
	}

	vLaserInitLna();
	vCopyImageLnaNvm();
	vClearResetMessage();
}
/*------------------------------------------------------------------------------*/
void vInitHpaRun(void)
{
	vSetDisableHpa();
	
	if( eFalse == bInitBoostMemoryImageFromNvm() )
	{
		vCurrentSensorsFactoryInitBoosterChannels();
		
		ePowerSensorsFactoryInitBoosterChannels();
					//vBoosterThermistorFactoryInitChannels();
		vBoosterCurrentControlInit(  );
		vSetHpaPidDefaultValues();

	}
	
	vLaserInitBooster();
	vCopyImageBoosterNvm();
	vClearResetMessage();
}

/*------------------------------------------------------------------------------*/