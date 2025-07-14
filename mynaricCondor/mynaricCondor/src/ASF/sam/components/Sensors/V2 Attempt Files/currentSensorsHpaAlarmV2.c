/*
 * currentSensorsHpaAlarm.c
 *
 * Created: 6/17/2024 3:09:27 PM
 *  Author: j.castano
 */ 
#include "currentSensorsHpaAlarm.h"


eMpbError_t eCurrentSensorsHpaAlarmRun( float fBoosterAlarmLowCurrentLimitPump1, float fBoosterAlarmHighCurrentLimitPump1, float fCurrentReaded1, float fCurrentReaded2, float fCurrentReaded3, AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister, eBool_t *pbCurrentCriticalAlarm)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bLowLimitAlarm = eFalse;
	eBool_t bHighLimitAlarm = eFalse;	
	eBool_t bValidLimits = eFalse;
	
	uint8_t ucTemporalLogic = 0;
	
	unsigned int precision = 100;
	
	bValidLimits =  mpb_float1_minor_than_float2(fBoosterAlarmLowCurrentLimitPump1 , fBoosterAlarmHighCurrentLimitPump1, precision);
	bValidLimits =  (pxAlarmRegister != NULL) && (bValidLimits==eTrue) && (pbCurrentCriticalAlarm != NULL);
	

	if (bValidLimits == eTrue )
	{
		eMpbError = eSuccess;

		*pbCurrentCriticalAlarm = eFalse;

		/* check first pump */
		bLowLimitAlarm = mpb_float1_minor_than_float2(fCurrentReaded1, fBoosterAlarmLowCurrentLimitPump1, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(fBoosterAlarmHighCurrentLimitPump1,fCurrentReaded1, precision);	

		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm);	
		*pbCurrentCriticalAlarm	 = (eBool_t)( ucTemporalLogic & 0x01);
			 
		pxAlarmRegister->bBoosterCurrentLimitAlarmStatus = ucTemporalLogic & 0x01 ; 
	
		/* check second pump */
		bLowLimitAlarm = mpb_float1_minor_than_float2(fCurrentReaded2, fBoosterAlarmLowCurrentLimitPump1, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(fBoosterAlarmHighCurrentLimitPump1,fCurrentReaded2, precision);
	
		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm); 
		*pbCurrentCriticalAlarm	 = (eBool_t)( ucTemporalLogic & 0x01) || *pbCurrentCriticalAlarm;
		
		pxAlarmRegister->bCurrentBoosterDriver2AlarmFlag = ucTemporalLogic & 0x01 ; 
	
		/* check third pump */
		bLowLimitAlarm = mpb_float1_minor_than_float2(fCurrentReaded3, fBoosterAlarmLowCurrentLimitPump1, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(fBoosterAlarmHighCurrentLimitPump1,fCurrentReaded3, precision);
	
		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm); 
		*pbCurrentCriticalAlarm	 = (eBool_t)( ucTemporalLogic & 0x01) || *pbCurrentCriticalAlarm;
		pxAlarmRegister->bCurrentBoosterDriver3AlarmFlag = ucTemporalLogic & 0x01 ; 
	}
	
	return eMpbError;
	
}