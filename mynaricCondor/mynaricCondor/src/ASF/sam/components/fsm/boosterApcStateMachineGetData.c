/*
 * boosterApcStateMachineGetData.c
 *
 * Created: 6/19/2024 12:43:19 PM
 *  Author: j.castano
 */

#include "boosterApcStateMachineGetData.h"
#include "laserData.h"
#include "math.h"
#include "apcControlLaser.h"

eMpbError_t eBoosterApcStateGetDataGetConditionsOnPumpSm1( cPumpSm1StatusDefinition_t *pcPumpSm1StatusDefinition)	
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	bValidPointers = (pcPumpSm1StatusDefinition !=NULL) && (pxAmplifierDescriptor != NULL);
	
	if( bValidPointers == eTrue)
	{
		eMpbError = eSuccess;
		pcPumpSm1StatusDefinition->cPumpSm1StatusFlags.PumpSm1BitAssignment.bSm1IsStucked = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bSm_DriverStucked == 1)? eTrue : eFalse;
		pcPumpSm1StatusDefinition->cPumpSm1StatusFlags.PumpSm1BitAssignment.bSm1OverHeat = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmWayTooHighTemperature == 1)? eTrue : eFalse;
		pcPumpSm1StatusDefinition->cPumpSm1StatusFlags.PumpSm1BitAssignment.bSm1UnderHeat = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmLowTemperature == 1)? eTrue : eFalse;
		pcPumpSm1StatusDefinition->cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1 == 1)? eTrue : eFalse;
				
		pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserSingleModeStatus = ( pcPumpSm1StatusDefinition->cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 );//== eFalse)? 0 :  1;
		
		pcPumpSm1StatusDefinition->fLaserPump1BoosterCurrent = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent;
		
		pcPumpSm1StatusDefinition->usLaserPump1AccSetpoint = pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump1OnBoosterInAcc ;
		
		pcPumpSm1StatusDefinition->bSm1WavelengthIs1536 = (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetTxChannelOnBooster == 1 )? eTrue : eFalse ;
		
		pcPumpSm1StatusDefinition->bCriticalStuckDetected = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bSm_DriverStucked == 1 ) ||
															( ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bMm1_DriverStucked == 1) && 
															  ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bMm2_DriverStucked == 1  )  )? 1 : 0; 
		
				
	}
	
	return eMpbError;	
}

/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataGetConditionsOnPumpMm1(  cPumpMm1StatusDefinition_t *pcPumpMm1StatusDefinition)	
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	bValidPointers = (pcPumpMm1StatusDefinition !=NULL) && (pxAmplifierDescriptor != NULL);
	
	if( bValidPointers == eTrue)
	{
		eMpbError = eSuccess;
		pcPumpMm1StatusDefinition->cPumpMm1StatusFlags.PumpMm1BitAssignment.bMm1IsStucked = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bMm1_DriverStucked == 1)? eTrue : eFalse;
		pcPumpMm1StatusDefinition->cPumpMm1StatusFlags.PumpMm1BitAssignment.bMm1OverHeat = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmWayTooHighTemperature == 1)? eTrue : eFalse;
		pcPumpMm1StatusDefinition->cPumpMm1StatusFlags.PumpMm1BitAssignment.bMm1UnderHeat = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmLowTemperature == 1)? eTrue : eFalse;		
		
		pcPumpMm1StatusDefinition->cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2 == 1)? eTrue : eFalse;
		pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode1Status = ( pcPumpMm1StatusDefinition->cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == eFalse)? 0 : 1;
		pcPumpMm1StatusDefinition->usLaserPumpMm1AccSetpoint = pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump2OnBoosterInAcc ;
		pcPumpMm1StatusDefinition->fLaserPumpMm1BoosterCurrent = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent;
	}
	return eMpbError;	
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataGetConditionsOnPumpMm2(  cPumpMm2StatusDefinition_t *pcPumpMm2StatusDefinition)	
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	bValidPointers = (pcPumpMm2StatusDefinition !=NULL) && (pxAmplifierDescriptor != NULL);
	
	if( bValidPointers == eTrue)
	{
		eMpbError = eSuccess;
		pcPumpMm2StatusDefinition->cPumpMm2StatusFlags.Pump2BitAssignment.bMm2IsStucked = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bMm2_DriverStucked);// == 1)? eTrue : eFalse;	
		pcPumpMm2StatusDefinition->cPumpMm2StatusFlags.Pump2BitAssignment.bMm2OverHeat = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmWayTooHighTemperature);// == 1)? eTrue : eFalse;
		pcPumpMm2StatusDefinition->cPumpMm2StatusFlags.Pump2BitAssignment.bMm2UnderHeat = ( pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmLowTemperature);// == 1)? eTrue : eFalse;		
		
		pcPumpMm2StatusDefinition->cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3);// == 1)? eTrue : eFalse;
				
		pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode2Status = (pcPumpMm2StatusDefinition->cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2);//  == eFalse)?  0 : 1 ;
		
		pcPumpMm2StatusDefinition->fLaserPumpMm2BoosterCurrent = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent;
		pcPumpMm2StatusDefinition->usLaserPumpMm2AccSetpoint = pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump3OnBoosterInAcc ;
	}
	return eMpbError;	
	
}

/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataGetHpaActualConditionsOnPumps( xBoosterCurrents_t *pxBoosterCurrents)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;
		
	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	bValidPointers = (pxBoosterCurrents !=NULL) && (pxAmplifierDescriptor != NULL);
	
	if( bValidPointers == eTrue)
	{
		eMpbError = eSuccess;
	
		
		pxBoosterCurrents->fCurrentHpaSm1					= pxAmplifierDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent;
		pxBoosterCurrents->fCurrentHpaMm1					= pxAmplifierDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent;
		pxBoosterCurrents->fCurrentHpaMm2					= pxAmplifierDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent;

		
		
		
	}
	
	return eMpbError;
		
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataGetResetRequest( eResetRequest_t *peResetRequest, eBool_t *pbConditionsToResetBooster, eBool_t *pConditionsToResetLna)
{
	eMpbError_t eMpbError = eInvalidParameter;
		
	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	*peResetRequest = pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest;
	
	*pbConditionsToResetBooster  = ( ( *peResetRequest == RESET_BOOSTER) ||  ( *peResetRequest == RESET_ALL) )? eTrue : eFalse;
	*pConditionsToResetLna  = ( ( *peResetRequest == RESET_LNA) ||  ( *peResetRequest == RESET_ALL) )? eTrue : eFalse;
		
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataSetResetRequest( eResetRequest_t eResetRequest)
{
	eMpbError_t eMpbError = eInvalidParameter;

	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );

	pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest = eResetRequest;

	
	
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataPowersAndOperationMode( xBoosterPowers_t *pxBoosterPowers, eBool_t *bEnable1Booster, eBool_t *bEnable2Booster, eBool_t *bEnable3Booster )		
{	
	eMpbError_t eMpbError = eInvalidParameter;

	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
		
	pxBoosterPowers->fActualOutputPowerInMiliWatts		= pxAmplifierDescriptor->xPowersInMiliWats.fInternalHpaOpticalOutputMonitor;
	pxBoosterPowers->fActualPowerInDbm					= pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower;
	pxBoosterPowers->bHpaInAccmode						= !(eBool_t)(pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetBoosterControlMode);
	pxBoosterPowers->fActualInputPowerInDbm			= pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalInputPower;
	pxBoosterPowers->fActualOutputPowerInMiliWatts	= pxAmplifierDescriptor->xPowersInMiliWats.fInternalHpaOpticalOutputMonitor;
	pxBoosterPowers->fSetPointInDbm					= pxAmplifierDescriptor->c406PacketControlDefinition.fSetSetPointPowerForBoosterInApc;
	pxBoosterPowers->fValueConverted					= DIVIDE_BY_TEN * pxAmplifierDescriptor->c406PacketControlDefinition.fSetSetPointPowerForBoosterInApc;
	
	pxBoosterPowers->fSetPointInMiliWatts				= pow(10, pxBoosterPowers->fValueConverted  ) ;
	
	
	
	pxAmplifierDescriptor->xPowersIndBM.fhpa1SetpointInApcIndbm = pxBoosterPowers->fSetPointInDbm;
	
	*bEnable1Booster = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1;
	*bEnable2Booster = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2;
	*bEnable3Booster = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3;
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/

eMpbError_t eBoosterApcStateGetDataHpaSmParameters( uint16_t *pusMaxHpaCurrentSM_mA,  uint16_t *pusNominalCurrentPourcentage_sM)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;

	xBoosterParameters_t *pxBoosterParameters = NULL;
	pxBoosterParameters 	= vGetpxBoosterParameters( );
	
	bValidPointers = (pusMaxHpaCurrentSM_mA != NULL) && (pusNominalCurrentPourcentage_sM != NULL) ;
		
	if( bValidPointers == eTrue )
	{
		eMpbError= eSuccess;
		
		*pusMaxHpaCurrentSM_mA =  pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentSM_mA;
		*pusNominalCurrentPourcentage_sM = pxBoosterParameters->xHpaLimitsConfig.usNominalCurrentPourcentage_sM;
			
	}
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataHpaMm1Parameters( uint16_t *pusMaxHpaCurrentStageMM1_mA,  uint16_t *pusMaxHpaCurrentMM1_mA)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;

	xBoosterParameters_t *pxBoosterParameters = NULL;
	pxBoosterParameters 	= vGetpxBoosterParameters( );
	
	bValidPointers = ( pusMaxHpaCurrentStageMM1_mA != NULL) && ( pusMaxHpaCurrentMM1_mA != NULL) ;
	
	if( bValidPointers == eTrue )
	{
		eMpbError= eSuccess;
		
		*pusMaxHpaCurrentStageMM1_mA =  pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA;
		*pusMaxHpaCurrentMM1_mA = pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentMM1_mA;
		
	}
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataHpaMm2Parameters( uint16_t *pusMaxHpaCurrentStageMM2_mA,  uint16_t *pusMaxHpaCurrentMM2_mA)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bValidPointers = eFalse;

	xBoosterParameters_t *pxBoosterParameters = NULL;
	pxBoosterParameters 	= vGetpxBoosterParameters( );
	
	bValidPointers = ( pusMaxHpaCurrentStageMM2_mA != NULL) && ( pusMaxHpaCurrentMM2_mA != NULL) ;
	
	if( bValidPointers == eTrue )
	{
		eMpbError= eSuccess;
		
		*pusMaxHpaCurrentStageMM2_mA =  pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA;
		*pusMaxHpaCurrentMM2_mA = pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentMM2_mA;
		
	}
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataUpdateControlMm1(xBoosterPowers_t xBoosterPowers, float *pfCurrentControlHpaMm1 )   
{
	uint32_t				uUsDelta = 50;
	eMpbError_t eMpbError = eInvalidParameter;
	
	
	xBoosterParameters_t *pxBoosterParameters = NULL;
	pxBoosterParameters 	= vGetpxBoosterParameters( );
		
	if(pxBoosterParameters != NULL)
	{
		eMpbError = eSuccess;
		vApcMm1ControlLaserUpdate(  pxBoosterParameters, uUsDelta, xBoosterPowers.fSetPointInMiliWatts,
									xBoosterPowers.fActualOutputPowerInMiliWatts, pfCurrentControlHpaMm1 );
		
	}	
								
	return eMpbError;							
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataUpdateControlMm2(xBoosterPowers_t xBoosterPowers, float *pfCurrentControlHpaMm2 )
{
	uint32_t				uUsDelta = 50;
	eMpbError_t eMpbError = eInvalidParameter;
	
	xBoosterParameters_t *pxBoosterParameters = NULL;
	pxBoosterParameters 	= vGetpxBoosterParameters( );

	if(pxBoosterParameters != NULL)
	{
		eMpbError = eSuccess;	
		vApcMm2ControlLaserUpdate(  pxBoosterParameters, uUsDelta, xBoosterPowers.fSetPointInMiliWatts, xBoosterPowers.fActualOutputPowerInMiliWatts, pfCurrentControlHpaMm2); // inside the zone
	}
	return eMpbError;	
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataUpdateControlMm1AndMm2(xBoosterPowers_t xBoosterPowers, float *pfCurrentControlHpaMm2 )
{
	uint32_t				uUsDelta = 50;
	eMpbError_t eMpbError = eInvalidParameter;
	
	
	xBoosterParameters_t *pxBoosterParameters = NULL;
	pxBoosterParameters 	= vGetpxBoosterParameters( );
	
	if(pxBoosterParameters != NULL)
	{
		eMpbError = eSuccess;	
		vApcMm1and2ControlLaserUpdate(  pxBoosterParameters, uUsDelta, xBoosterPowers.fSetPointInMiliWatts, xBoosterPowers.fActualOutputPowerInMiliWatts, pfCurrentControlHpaMm2 ); // inside the zone
	}
	return eMpbError;	
}
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDatasetControlcurrents(float fControlCurrentSm1, float fCurrentControlHpaMm1, float fCurrentControlHpaMm2 )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor();
	
	
	if(pxAmplifierDescriptor != NULL)
	{
		eMpbError = eSuccess;	
		pxAmplifierDescriptor->xCurrentControlValues.fLaserPump1BoosterControlCurrent = fControlCurrentSm1;
		pxAmplifierDescriptor->xCurrentControlValues.fLaserPump2BoosterControlCurrent = fCurrentControlHpaMm1;
		pxAmplifierDescriptor->xCurrentControlValues.fLaserPump3BoosterControlCurrent = fCurrentControlHpaMm2;
	}
	
	return eMpbError;
}
	
/*----------------------------------------------------------------------------*/
eMpbError_t eBoosterApcStateGetDataResetHpaAlarms( void)
{
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	//3. move to reset alarms function
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bBoosterOutputPowerIsTooHigh = 0;
	

	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerIsTooHigh = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLOSAlarm = 0;

	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = 0;
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = 0;

	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag  = 0;
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bUnitBaseTemperatureAlarmStatus  = 0;

	
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bMm1_DriverStucked = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bMm2_DriverStucked = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bSm_DriverStucked = 0;
	
	//pxLaserBeamDescriptor->xHpaStuckStatusMm1.eHpaStuckState = eStuckSample_1;
	//pxLaserBeamDescriptor->xHpaStuckStatusMm2.eHpaStuckState = eStuckSample_1;
	//pxLaserBeamDescriptor->xHpaStuckStatusSm1.eHpaStuckState = eStuckSample_1;
	
	//pxLaserBeamDescriptor->xHpaStuckStatusSm1.bStuckDetected = eFalse;
	//pxLaserBeamDescriptor->xHpaStuckStatusMm1.bStuckDetected = eFalse;
	//pxLaserBeamDescriptor->xHpaStuckStatusMm2.bStuckDetected = eFalse;
	
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bCaseAlarmHighTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bCaseAlarmWayTooHighTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bCaseAlarmLowTemperature = 0;
	
	
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmHighTemperature = 0;	
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmWayTooHighTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmLowTemperature = 0;
	
	//pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmTooHighTemperature = 0;
	//pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmTooLowTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmWayTooHighTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmLowTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmHighTemperature = 0;
	
	
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmHighTemperature = 0;
	//pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmTooLowTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmWayTooHighTemperature = 0;
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmLowTemperature = 0;
	
	
	return eSuccess;
	//vResetLosPowerSensor();

}	