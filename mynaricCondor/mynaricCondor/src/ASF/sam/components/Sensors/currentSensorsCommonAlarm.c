/*
 * currentSensorsCommonAlarm.c
 *
 * Created: 6/18/2024 10:45:05 AM
 *  Author: j.castano
 */ 
#include "currentSensorsCommonAlarm.h"

eMpbError_t eCurrentSensorsCommonAlarmRun( c423StatusDefinition_t *c423StatusDefinition, c428StatusDefinition_t * c428StatusDefinition , eBool_t *bInternalAlarm )
{
	
	eMpbError_t eMpbError = eInvalidParameter;

	uint64_t ulTempValue = 0;
		eBool_t validParams = eFalse;
		unsigned int precision = 100;

		validParams = (c423StatusDefinition != NULL && c428StatusDefinition != NULL &&bInternalAlarm != NULL);

		if (validParams)
		{
			//uint64_t ulTempValue = 0;
			
			//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow =  (uint8_t)(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1 < LEVEL_28V);
			c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow =  mpb_float1_minor_than_float2(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1, LEVEL_28V, precision);
			//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow = (uint8_t) ((c423StatusDefinition->f3_3V_PwrVoltageMonitor < LEVEL_3V ) || (c423StatusDefinition->f3V_ld_PwrVoltageMonitor < LEVEL_3V ));
			c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow = (mpb_float1_minor_than_float2(c423StatusDefinition->f3_3V_PwrVoltageMonitor, LEVEL_3V, precision ) || mpb_float1_minor_than_float2(c423StatusDefinition->f3V_ld_PwrVoltageMonitor, LEVEL_3V, precision ));
			//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow = (uint8_t)((c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1 < LEVEL_7V ) ||	(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2 < LEVEL_7V));
			c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow = (mpb_float1_minor_than_float2(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1, LEVEL_7V, precision ) ||	mpb_float1_minor_than_float2(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2, LEVEL_7V, precision));
			//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow = (uint8_t)(c423StatusDefinition->fAdcPwrCurrentMonitor < LEVEL_ADC );
			c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow = mpb_float1_minor_than_float2(c423StatusDefinition->fAdcPwrCurrentMonitor, LEVEL_ADC, precision );
			//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow = ( uint8_t)((c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1 < LEVEL_28_CURRENT) || (c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2 < LEVEL_28_CURRENT));
			//		c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow = ( mpb_float1_minor_than_float2(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1, LEVEL_28_CURRENT, precision) || mpb_float1_minor_than_float2(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2, LEVEL_28_CURRENT, precision));
			//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow = (uint8_t)((c423StatusDefinition->fCanPwrCurrentMonitor1 < LEVEL_ADC ) || (c423StatusDefinition->fCanPwrCurrentMonitor2 < LEVEL_ADC ));
			//		c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow = (mpb_float1_minor_than_float2(c423StatusDefinition->fCanPwrCurrentMonitor1, LEVEL_ADC, precision ) || mpb_float1_minor_than_float2(c423StatusDefinition->fCanPwrCurrentMonitor2, LEVEL_ADC, precision ));
			
			ulTempValue  = (c428StatusDefinition->ulMpbAlarmsValue & 0x00000000000FC000 ) >> DEF_428_COMMON_ALARMS_POSITION; /*  BITS 14..19 OF THE REGISTER */
			*bInternalAlarm = (ulTempValue>0)? 1 : 0;

			eMpbError = eSuccess;
		}
		return eMpbError;
		
		
	
	
	//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow =  (uint8_t)(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1 < LEVEL_28V);
	//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow = (uint8_t) ((c423StatusDefinition->f3_3V_PwrVoltageMonitor > LEVEL_3V ) || (c423StatusDefinition->f3V_ld_PwrVoltageMonitor > LEVEL_3V ));
	//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow = (uint8_t)((c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1 > LEVEL_7V ) ||	(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2 > LEVEL_7V));
	//c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow = (uint8_t)(c423StatusDefinition->fAdcPwrCurrentMonitor > LEVEL_ADC );
		
										   
	//ulTempValue  = (c428StatusDefinition->ulMpbAlarmsValue & 0x00000000000FC000 ) >> DEF_428_COMMON_ALARMS_POSITION; /*  BITS 14..19 OF THE REGISTER */
	
	//*bInternalAlarm = (ulTempValue>0)? 1 : 0;
	
	return eMpbError;
}