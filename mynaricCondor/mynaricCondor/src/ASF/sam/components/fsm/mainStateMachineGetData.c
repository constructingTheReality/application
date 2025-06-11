/*
 * mainStateMachineGetData.c
 *
 * Created: 8/23/2024 10:10:57 AM
 *  Author: j.castano
 */ 
#include "mainStateMachineGetData.h"


eMpbError_t eMainStateMachineGetDataGetUnitTemperatureAlarm( eBool_t *bUniTemperatureAlarm )	
{
	eMpbError_t eMpbError = eSuccess;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	

	*bUniTemperatureAlarm = (pxLaserBeamDescriptor->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bUnitBaseTemperatureAlarmStatus == 1)? eTrue: eFalse;

	return eMpbError;
}
/*-----------------------------------*/
eMpbError_t eMainStateMachineGetDataGetMpbAlarms( MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment )	
{
	eMpbError_t eMpbError = eSuccess;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	*pMpbAlarmsAndStatusRegisterBitAssignment = pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment;
	
	return eMpbError;
	
}
void vClearResetFromStartupFlag(void)
{
	vClearResetStartup();		
	
}
/*-----------------------------------*/
eResetRequest_t eGetActualResetCommand(void)
{
	eResetRequest_t eResetRequest;
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	eResetRequest = pxLaserBeamDescriptor->c406PacketControlDefinition.ucResetRequest ;
	return eResetRequest;
}
/*-----------------------------------*/
eMpbError_t eMainStateMachineGetDataSetResetFromStartup( eBool_t bResetFromStartup )
{
	eMpbError_t eMpbError = eSuccess;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bResetFromStartupState = (bResetFromStartup == eTrue)? 1 : 0 ;
	
	
	return eMpbError;
}
/*-----------------------------------*/
eMpbError_t eGetLnaEnableStatus( eBool_t *bIsEnabled)
{
	eMpbError_t eMpbError = eSuccess;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	 *bIsEnabled = (pxLaserBeamDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 == 1)? eTrue : eFalse ;
	
	
	return eMpbError;
	
}
/*-----------------------------------*/
void vClearResetMessage( void)
{
	
		xAmplifierDescriptor_t *pxLaserBeamDescriptor;
		pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
		
		pxLaserBeamDescriptor->c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
	
}
/*-----------------------------------*/
eMpbError_t eUpdateFsmStates( 	uint8_t	ucLnaState, uint8_t ucHpaState, uint8_t ucHpaApcState, uint8_t ucMainLoopState)
{
	eMpbError_t eMpbError = eSuccess;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	
	pxLaserBeamDescriptor->eLnaState = ucLnaState;
	pxLaserBeamDescriptor->eHpaState = ucHpaState;
	pxLaserBeamDescriptor->eHpaApcState = ucHpaApcState;
	pxLaserBeamDescriptor->eMainLoopState = ucMainLoopState;
	
	
	
	
	
	
}