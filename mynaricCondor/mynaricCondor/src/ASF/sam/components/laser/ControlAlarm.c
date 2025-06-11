/**
* @file 		ControlAlarm.c
* @brief		ControlAlarm.c source file
* @author		juan andres
* @date			Created on 2023-03-11
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "ControlAlarm.h"
#include "projectDef.h"
#include "dictionaryUtils.h"

/* Private define ----------------------------------------------------------- */
#define DEF_PRECITION											( 100 )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
//static	xAlarmRegister_t		 					xAlarmRegister ; 
//static	xAlarmsThresholdsValues_t					xAlarmsThresholdsValues;


/*---------------------------------------------------------------------------------------*/
/*void vControlAlarmClear(xAlarmRegister_t *pxAlarmRegister)
{
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalInputIsTooHigh		= DEF_NO;
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalInputIsTooLow		= DEF_NO;
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalOutputIsTooHigh		= DEF_NO;
    pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalOutputIsTooLow		= DEF_NO;
}*/
/*---------------------------------------------------------------------------------*/
void vControlAlarmSetCriticalAlarms( void) // float fRead , xAlarmRegister_t *pxAlarmRegister, xAlarmsThresholdsValues_t *pxAlarmsThresholdsValues)
{
	//eBool_t  compareValues = eFalse;
	//	c402StatusDefinition_t  *c402StatusDefinition = NULL;
	//	c406PacketControlDefinition_t  *c406StatusDefinition= NULL;
		
		//xAmplifierDescriptor_t *pxLaserBeamDescriptor;
		//pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
		
	//	vLaserDataGetCan402Info( c402StatusDefinition );
	//	vLaserDataGetCan406Info( c406StatusDefinition );
		

/*	compareValues = mpb_float1_minor_than_float2( pxAlarmsThresholdsValues->xAlarmsThresholdsForPowerValues.fThresholdForAlarmHighInputBooster, fRead, DEF_PRECITION); 
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalInputIsTooHigh	= 	( compareValues == eTrue   )? DEF_YES:DEF_NO;
	
	compareValues = mpb_float1_minor_than_float2(fRead, pxAlarmsThresholdsValues->xAlarmsThresholdsForPowerValues.fThresholdForAlarmLowInputBooster, DEF_PRECITION); 
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalInputIsTooLow	= 	( compareValues == eTrue  )? DEF_YES:DEF_NO;
	
	compareValues = mpb_float1_minor_than_float2(  pxAlarmsThresholdsValues->xAlarmsThresholdsForPowerValues.fThresholdForAlarmHighOutputBooster, fRead, DEF_PRECITION); 
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalOutputIsTooHigh  =	( compareValues == eTrue  )? DEF_YES:DEF_NO;
	
	compareValues = mpb_float1_minor_than_float2(fRead, pxAlarmsThresholdsValues->xAlarmsThresholdsForPowerValues.fThresholdForAlarmLowOutputBooster, DEF_PRECITION); 
	pxAlarmRegister->AlarmsRegisterBitAssignment.bBosterOpticalOutputIsTooLow	=	( compareValues == eTrue  )? DEF_YES:DEF_NO;
	
	compareValues = mpb_float1_minor_than_float2(  pxAlarmsThresholdsValues->xAlarmsThresholdsForPowerValues.fThresholdForAlarmHighOutputLna, fRead, DEF_PRECITION); 
	pxAlarmRegister->AlarmsRegisterBitAssignment.bLnaOpticalInputIsTooHigh		=	( compareValues == eTrue )? DEF_YES:DEF_NO;
	
	compareValues = mpb_float1_minor_than_float2(fRead, pxAlarmsThresholdsValues->xAlarmsThresholdsForPowerValues.fThresholdForAlarmLowOutputLna, DEF_PRECITION); 
	pxAlarmRegister->AlarmsRegisterBitAssignment.bLnaOpticalInputIsTooLow		=	( compareValues == eTrue  )? DEF_YES:DEF_NO;
*/

	/*
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserDriver1Status =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1;
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterMode =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetBoosterControlMode;
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode;
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetRxChannelOnLna;
	c402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection =
	c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetTxChannelOnBooster;*/
}
/*---------------------------------------------------------------------------------*/

