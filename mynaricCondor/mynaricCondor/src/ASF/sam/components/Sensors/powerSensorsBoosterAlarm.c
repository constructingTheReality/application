/*
 * powerSensorsBoosterAlarm.c
 *
 * Created: 6/12/2024 12:21:46 PM
 *  Author: j.castano
 */ 

#include "powerSensorsBoosterAlarm.h"


eMpbError_t ePowerSensorBoosterAlarmRun( xLosValues_t *xpLosValues, xLosStates_t *pxLosStates, eBool_t *bHpaPowerLosAlarm, MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition_t c408StatusDefinition, float fInputPowerReaded , float fOutputPowerReaded ,xAlarmAndStatusRegister_t *pxAlarmRegister_402, eBool_t *pbBoosterPowerCriticalAlarm)
{
	eMpbError_t eMpbError = eInvalidParameter;
	unsigned int precision = 100;
	eBool_t bInputLowLimitAlarm = eFalse;
	eBool_t bInputHighLimitAlarm = eFalse;
	eBool_t bOutputLowLimitAlarm = eFalse;
	eBool_t bOutputHighLimitAlarm = eFalse;
	eBool_t bAddition = 0;
	eBool_t bCriticalAlarm = eFalse;
	
	eBool_t bInputCheckC408 = eFalse;
	eBool_t bOutputCheckC408 = eFalse;
		
	bAddition = ( (xpLosValues != NULL) && (pxLosStates != NULL) && (bHpaPowerLosAlarm != NULL) && (pMpbAlarmsAndStatusRegisterBitAssignment_428 != NULL) && (pxAlarmRegister_402 != NULL) && (pbBoosterPowerCriticalAlarm != NULL)  );
		
		
	if (bAddition == eTrue)
	{
	//	ePowerSensorValidateOutputLimits(&bOutputCheckC408, c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput, c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput, eTrue);
		

	//	ePowerSensorValidateInputLimits(&bInputCheckC408, c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput, c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput, eTrue);
		

		//bCheckC408 = bOutputCheckC408 && bInputCheckC408;
		
		//pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = (bCheckC408 != eTrue)? eTrue:eFalse;
		
		//	pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = !bCheckC408;
		
		eMpbError = eMpbLosDetectorExecute( fInputPowerReaded, *xpLosValues, bHpaPowerLosAlarm, pxLosStates  );
			
	
		if(*bHpaPowerLosAlarm==eTrue)
		{
			*bHpaPowerLosAlarm=eTrue;
		}
	
		bInputLowLimitAlarm			= mpb_float1_minor_than_float2(fInputPowerReaded, c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput, precision);
		bInputHighLimitAlarm		= mpb_float1_minor_than_float2(c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput ,fInputPowerReaded, precision);
	
		bOutputLowLimitAlarm = eFalse;
	//	bOutputLowLimitAlarm		= mpb_float1_minor_than_float2(fOutputPowerReaded, c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput, precision);
		bOutputHighLimitAlarm		= mpb_float1_minor_than_float2(c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput, fOutputPowerReaded, precision);
	
		bAddition = ( *bHpaPowerLosAlarm == eTrue)  || (  bInputHighLimitAlarm == eTrue)	;
		//pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus =  (uint8_t)(bAddition) && 0x01 ; //	( bAddition == eTrue )? 1: 0;
		if(bAddition == eTrue)
		{
			pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus =  1;	
		}
		
	
		bAddition = ( bOutputHighLimitAlarm == eTrue );// || ( bOutputLowLimitAlarm == eTrue)	;
		pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = (uint8_t)(bAddition) && 0x01 ; // (bAddition == eTrue )? 1 : 0;
	
		pMpbAlarmsAndStatusRegisterBitAssignment_428->bBoosterOutputPowerIsTooHigh = (uint8_t)(bOutputHighLimitAlarm);
		pMpbAlarmsAndStatusRegisterBitAssignment_428->bBoosterInputPowerIsTooHigh =  (uint8_t)( bInputHighLimitAlarm);
	
		#ifdef DEMO_VERSION
		#else
	
		bCriticalAlarm = (*bHpaPowerLosAlarm == eTrue) || (bOutputHighLimitAlarm == eTrue) ||  ( bInputHighLimitAlarm == eTrue) ;
	
		pMpbAlarmsAndStatusRegisterBitAssignment_428->bBoosterInputPowerLOSAlarm = (uint8_t)(*bHpaPowerLosAlarm) && 0x01 ;
	
		if(bCriticalAlarm == eTrue)
		{	  
			pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 1;
		}
	
	
		*pbBoosterPowerCriticalAlarm = (eBool_t)( pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag ) ;
	
		#endif
	}
	
	return eMpbError;
}
