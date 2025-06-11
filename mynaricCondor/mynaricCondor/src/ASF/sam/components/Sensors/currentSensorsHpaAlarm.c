/*
 * currentSensorsHpaAlarm.c
 *
 * Created: 6/17/2024 3:09:27 PM
 *  Author: j.castano
 */ 
#include "currentSensorsHpaAlarm.h"


eMpbError_t eCurrentSensorsHpaAlarmRun( c409StatusDefinition_t c409StatusDefinition, float fCurrentReaded1, float fCurrentReaded2, float fCurrentReaded3, AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister, eBool_t *pbCurrentCriticalAlarm)
{
	eMpbError_t eMpbError = eInvalidParameter;
	eBool_t bLowLimitAlarm = eFalse;
	eBool_t bHighLimitAlarm = eFalse;	
	eBool_t bValidc409 = eFalse;
	
	uint8_t ucTemporalLogic = 0;
	//*pbCurrentCriticalAlarm = eFalse;
	
	unsigned int precision = 100;
	
	bValidc409 =  mpb_float1_minor_than_float2(c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump , c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump, precision);
	//bValidc409 =  (pxAlarmRegister != NULL) && (bValidc409==eTrue) ;
	bValidc409 =  (pxAlarmRegister != NULL) && (bValidc409==eTrue) && (pbCurrentCriticalAlarm != NULL);
	
	
	if (bValidc409 == eTrue )
	{
		eMpbError = eSuccess;
		*pbCurrentCriticalAlarm = eFalse;

		/* check first pump */
		bLowLimitAlarm = mpb_float1_minor_than_float2(fCurrentReaded1, c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump,fCurrentReaded1, precision);	

		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm);	
		*pbCurrentCriticalAlarm	 = (eBool_t)( ucTemporalLogic & 0x01);
			 
		pxAlarmRegister->bBoosterCurrentLimitAlarmStatus = ucTemporalLogic & 0x01 ; 
	
		/* check second pump */
		bLowLimitAlarm = mpb_float1_minor_than_float2(fCurrentReaded2, c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump,fCurrentReaded2, precision);
	
		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm); 
		*pbCurrentCriticalAlarm	 = (eBool_t)( ucTemporalLogic & 0x01) || *pbCurrentCriticalAlarm;
		
		pxAlarmRegister->bCurrentBoosterDriver2AlarmFlag = ucTemporalLogic & 0x01 ; 
	
		/* check third pump */
		bLowLimitAlarm = mpb_float1_minor_than_float2(fCurrentReaded3, c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump, precision);
		bHighLimitAlarm = mpb_float1_minor_than_float2(c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump,fCurrentReaded3, precision);
	
		ucTemporalLogic = (uint8_t)(bLowLimitAlarm) + (uint8_t)(bHighLimitAlarm); 
		*pbCurrentCriticalAlarm	 = (eBool_t)( ucTemporalLogic & 0x01) || *pbCurrentCriticalAlarm;
		pxAlarmRegister->bCurrentBoosterDriver3AlarmFlag = ucTemporalLogic & 0x01 ; 
	}
	
	return eMpbError;
	
}