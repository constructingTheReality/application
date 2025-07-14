/*
 * powerSensorsLnaAlarm.c
 *
 * Created: 6/12/2024 1:01:37 PM
 *  Author: j.castano
 */ 
#include "powerSensorsLnaAlarm.h"


	
eMpbError_t ePowerSensorLnaAlarmRun( MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition_t c408StatusDefinition, float fInputPowerReaded , float fOutputPowerReaded ,xAlarmAndStatusRegister_t *pxAlarmRegister, eBool_t*bLnaPowerCriticalAlarm)
{
		eMpbError_t eMpbError = eInvalidParameter;
		eBool_t bInputLowLimitAlarm = eFalse;
		eBool_t bInputHighLimitAlarm = eFalse;
		eBool_t bOutputLowLimitAlarm = eFalse;
		eBool_t bOutputHighLimitAlarm = eFalse;

		eBool_t bAddition = eFalse;
		eBool_t bCheckC408 = eFalse;
		eBool_t bInputCheckC408 = eFalse;
		eBool_t bOutputCheckC408 = eFalse;
				
		unsigned int precision = 100;
		
		bAddition = ( pxAlarmRegister != NULL) && ( bLnaPowerCriticalAlarm != NULL) && (pMpbAlarmsAndStatusRegisterBitAssignment != NULL);
		
		
		if(bAddition == eTrue)
		{
			ePowerSensorValidateOutputLimits(&bOutputCheckC408, c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput, c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput, eFalse);
						

			ePowerSensorValidateInputLimits(&bInputCheckC408, c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput, c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput, eFalse);
						

			bCheckC408 = bOutputCheckC408 && bInputCheckC408;
			eMpbError = eSuccess;			
			
			bInputLowLimitAlarm = mpb_float1_minor_than_float2(fInputPowerReaded, c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput, precision);
			bInputHighLimitAlarm = mpb_float1_minor_than_float2(c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput ,fInputPowerReaded, precision);
		
			bOutputLowLimitAlarm = mpb_float1_minor_than_float2(fOutputPowerReaded, c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput , precision);
			bOutputHighLimitAlarm = mpb_float1_minor_than_float2(c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput, fOutputPowerReaded, precision);
		
			bAddition = (bInputLowLimitAlarm == eTrue) || ( bInputHighLimitAlarm == eTrue )	;
			pxAlarmRegister->AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = (uint8_t)(bAddition) ; 
		
			bAddition = ( bOutputLowLimitAlarm == eTrue) ||  ( bOutputHighLimitAlarm== eTrue)	;
			pxAlarmRegister->AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = (uint8_t)(bAddition)  ; 
		
			bAddition = ( bOutputHighLimitAlarm== eTrue) || ( bInputHighLimitAlarm== eTrue)	;
			if( bAddition == eTrue && bCheckC408 == eTrue)
			{
				pxAlarmRegister->AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 1;
				*bLnaPowerCriticalAlarm = eTrue;
				//pxAlarmRegister->AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag = 1;
			
			}
			*bLnaPowerCriticalAlarm = (eBool_t)( pxAlarmRegister->AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag) ;

		//	pMpbAlarmsAndStatusRegisterBitAssignment->bLnaObLnaOutput PowerIsLow = (uint8_t)( bInputLowLimitAlarm );
			pMpbAlarmsAndStatusRegisterBitAssignment->bLnaInputPowerIsTooHigh = (uint8_t)( bInputHighLimitAlarm ) ;
			pMpbAlarmsAndStatusRegisterBitAssignment->bLnaOutputPowerIsTooHigh = (uint8_t)( bOutputHighLimitAlarm );
		
		
		}

	
	return eMpbError;
}