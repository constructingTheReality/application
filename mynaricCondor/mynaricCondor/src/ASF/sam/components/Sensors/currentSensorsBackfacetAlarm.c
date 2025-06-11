/*
 * currentSensorsBackfacetAlarm.c
 *
 * Created: 6/18/2024 12:20:51 PM
 *  Author: j.castano
 */ 
#include "currentSensorsBackfacetAlarm.h"

eMpbError_t eCurrentSensorsBackfacetAlarmRun( float fLnaBackfacetCurrentReaded, float fHpaBackfacetCurrentReaded, float fLnaBackfacetLimit, float  fBackfacetHpaLimit, AlarmsAndStatusRegisterBitAssignment_t *pAlarmsAndStatusRegisterBitAssignment , eBool_t *pLnaBackfacetCurrentCriticalAlarm, eBool_t *pHpaBackfacetCurrentCriticalAlarm)
{
		eMpbError_t eMpbError = eInvalidParameter;
		unsigned int precision = 100;
		eBool_t bLnaBackfacetError = eFalse;
		eBool_t bHpaBackfacetError = eFalse;
		
		
		//if(pAlarmsAndStatusRegisterBitAssignment != NULL)
		if(pAlarmsAndStatusRegisterBitAssignment != NULL && pLnaBackfacetCurrentCriticalAlarm != NULL && pHpaBackfacetCurrentCriticalAlarm != NULL)
		{
		
			eMpbError = eSuccess;	
		
			bLnaBackfacetError =  mpb_float1_minor_than_float2(fLnaBackfacetCurrentReaded , fLnaBackfacetLimit, precision);
			bHpaBackfacetError =  mpb_float1_minor_than_float2(fHpaBackfacetCurrentReaded , fBackfacetHpaLimit, precision);
			
			pAlarmsAndStatusRegisterBitAssignment->bHpaBackfacetCurrentErrorFlag = (bHpaBackfacetError == eFalse)? 1: 0;
			pAlarmsAndStatusRegisterBitAssignment->bLnaBackfacetCurrentErrorFlag = (bLnaBackfacetError == eFalse)? 1: 0;
			
			*pHpaBackfacetCurrentCriticalAlarm = bHpaBackfacetError;
			*pLnaBackfacetCurrentCriticalAlarm = bLnaBackfacetError;
			
			
		}
		
		return eMpbError;
		

}
