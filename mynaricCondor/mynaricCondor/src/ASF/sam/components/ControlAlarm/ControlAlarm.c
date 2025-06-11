///**
//* @file 	    ControlAlarm.c
//* @brief		controlAlarm source file.
//* @author		juan
//* @date			Created on 2021-03-3
//* @copyright MPB, Montreal, Qc
//* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
//* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
//* <center>This document contains confidential and proprietary information
//* of MPB (subject to a non-disclosure agreement) and shall</center>
//* <center>not be disclosed, distributed, or reproduced in whole or in
//* part, without the prior written authorization of MPB.</center>
//*
//**/
///* Includes ----------------------------------------------------------------- */
#include "ControlAlarm.h"
#include "TimeBaseManagement.h"
#include "LaserData.h"
#include "mainStateMachine.h"
/* Private define ----------------------------------------------------------- */

#define CONTROL_ALARM_LEVEL_TIME_MS      		                ( 300000 )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
//static AlarmsRegisterBitAssignment_t AlarmsRegisterBitAssignment ;
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/* Private functions -------------------------------------------------------- */


/* Exported functions ------------------------------------------------------- */

void vUpdateStatusAndAlarm( void )
{
	c402StatusDefinition_t  *c402StatusDefinition;
	c406PacketControlDefinition_t  *c406StatusDefinition;
	
	//xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	//pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	vLaserDataGetCan402Info( c402StatusDefinition );
	vLaserDataGetCan406Info( c406StatusDefinition );
	
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
																				c406StatusDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetTxChannelOnBooster;
}
/*----------------------------------------------------------------------------*/
