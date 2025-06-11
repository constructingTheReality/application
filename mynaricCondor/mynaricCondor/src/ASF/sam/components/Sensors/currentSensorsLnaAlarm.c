/*
 * currentSensorsLnaAlarm.c
 *
 * Created: 6/14/2024 5:04:38 PM
 *  Author: j.castano
 */ 

#include "currentSensorsLnaAlarm.h"


eMpbError_t eCurrentSensorsLnaAlarmRun( MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment ,c409StatusDefinition_t c409StatusDefinition, float fCurrentReaded  ,AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister, eBool_t *pLnaCurrentCriticalAlarm)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bLowLimitAlarm = eFalse;
	eBool_t bHighLimitAlarm = eFalse;
	float fLowLnaLimit = 0.0f;
	float fHighLnaLimit = 0.0f;
	unsigned int precision = 100;
	eBool_t bValidc409 = eFalse;
		
	uint8_t ucTemporalLogic = 0;
	
	/* pointer check */
	if (pMpbAlarmsAndStatusRegisterBitAssignment == NULL || pxAlarmRegister == NULL || pLnaCurrentCriticalAlarm == NULL)
	{
			return eInvalidParameter;
	}
		
	/* check for 409 limits */
	bValidc409 =  mpb_float1_minor_than_float2(c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump , c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump, precision);
	//bValidc409 =  (pxAlarmRegister != NULL) && (bValidc409==eTrue) ;
		
	if (bValidc409 == eTrue )
	{
		eMpbError = eSuccess;
		fLowLnaLimit = (c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump );//* X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE) / 100;
		fHighLnaLimit = (c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump );// * X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE) / 100;
	
		bLowLimitAlarm = mpb_float1_minor_than_float2( fCurrentReaded, fLowLnaLimit, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(fHighLnaLimit ,fCurrentReaded, precision);

		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm); 
		pxAlarmRegister->bLnaCurrentLimitAlarmStatus = ucTemporalLogic & 0x01; // +( (bLowLimitAlarm==eTrue) || (bHighLimitAlarm==eTrue) )? 1:0;
	
	
		//pMpbAlarmsAndStatusRegisterBitAssignment->bLnaCurrentLowAlarmStatus = (bLowLimitAlarm == eTrue)? 1: 0;
		pMpbAlarmsAndStatusRegisterBitAssignment->bLnaCurrentHighAlarmStatus = (bHighLimitAlarm == eTrue)? 1: 0;
		
		
		*pLnaCurrentCriticalAlarm = (eBool_t)( pxAlarmRegister->bLnaCurrentLimitAlarmStatus) ;
			
	}
	return eMpbError;
}
