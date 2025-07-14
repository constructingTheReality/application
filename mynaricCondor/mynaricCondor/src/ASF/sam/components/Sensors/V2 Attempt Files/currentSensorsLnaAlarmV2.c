/*
 * currentSensorsLnaAlarm.c
 *
 * Created: 6/14/2024 5:04:38 PM
 *  Author: j.castano
 */ 

#include "currentSensorsLnaAlarm.h"


eMpbError_t eCurrentSensorsLnaAlarmRun(float fCurrentReaded, float fLowLnaLimit, float fHighLnaLimit, MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment, AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister, eBool_t *pLnaCurrentCriticalAlarm)
{
	eMpbError_t eMpbError = eInvalidParameter;

	eBool_t bLowLimitAlarm = eFalse;
	eBool_t bHighLimitAlarm = eFalse;

	float fLowLnaLimit = 0.0f;
	float fHighLnaLimit = 0.0f;

	unsigned int precision = 100;

	eBool_t bValidLimits = eFalse;
		
	uint8_t ucTemporalLogic = 0;

	/* pointer check */
	if (pMpbAlarmsAndStatusRegisterBitAssignment == NULL || pxAlarmRegister == NULL || pLnaCurrentCriticalAlarm == NULL)
	{
		return eInvalidParameter;
	}

	/* check for 409 limits */
	bValidLimits =  mpb_float1_minor_than_float2(fLowLnaLimit, fHighLnaLimit);

	if (bValidLimits == eTrue)
	{
		eMpbError = eSuccess;

		bLowLimitAlarm = mpb_float1_minor_than_float2( fCurrentReaded, fLowLnaLimit, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(fHighLnaLimit ,fCurrentReaded, precision);

		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm); 
		pxAlarmRegister->bLnaCurrentLimitAlarmStatus = ucTemporalLogic & 0x01; // +( (bLowLimitAlarm==eTrue) || (bHighLimitAlarm==eTrue) )? 1:0;

		pMpbAlarmsAndStatusRegisterBitAssignment->bLnaCurrentHighAlarmStatus = (bHighLimitAlarm == eTrue)? 1: 0;

		*pLnaCurrentCriticalAlarm = (eBool_t)( pxAlarmRegister->bLnaCurrentLimitAlarmStatus) ;
	}
	
	return eMpbError;
}