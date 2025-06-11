
#include "can424Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51

static CAN_FRAME cRPDO_424;

/*---------------------------------------------------------------------------*/

void vInit424CanImage( void )
{
	cRPDO_424.data.value = 0;
	cRPDO_424.id = 0x424;
}

/*---------------------------------------------------------------------------*/
eMpbError_t getCan424( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_424, size );
	return eSuccess;
}
/*-----------------------------------------------------------------------------*/
eMpbError_t setCan424( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_424, pCan, size );
	return eSuccess;
}
/*-----------------------------------------------------------------------------*/


eMpbError_t eMpbCan424Decode( c424StatusDefinition_t *c424StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForCurrentPumpOnLna;
	floatUnion  fxValue;
	mpb_coerced_t coerce = not_coerced;


	if(c424StatusDefinition != NULL)
	{
		/*Bit 0-9: set low alarm limit status value alarm low limit for current laser pump on LNA section 
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value					= 0;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value					= ( cRPDO_409.data.value >> DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_LNA) & 0x00000000000003FF; // bits 0-9 
		c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump		= (float)(cxStatusAlarmLowLimitForCurrentPumpOnLna.low);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA ),
		(float)(Y1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
		(float)(X2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA ),
		(float)(Y2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
		c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump ,  coerce );
		
		c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump			= fxValue.fValue - FLOAT_ADJUST; */
		
		/*Bit 10-19: set alarm high limit for current laser pump on LNA section 
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value						= ( cRPDO_409.data.value >> DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_LNA) & 0x00000000000003FF; // bits  10-19 
		c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump			= (float)(cxStatusAlarmHighLimitForCurrentPumpOnLna.low ) ;
		
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA ),
		(float)(Y1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
		(float)(X2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA ),
		(float)(Y2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
		c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump ,  coerce );
		
		c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump			= fxValue.fValue- FLOAT_ADJUST ;*/
		
		
		
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}


/*

eMpbError_t eMpbCan409Encode( c409StatusDefinition_t *c409StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmHighLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmLowLimitForUnitBaseTemperature;
	BytesUnion	cxStatusAlarmHighLimitForUnitBaseTemperature;
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c409StatusDefinition != NULL)
	{
		//Bit 0-9: set low alarm limit status value alarm low limit for current laser pump on LNA section 
		if(c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump > X2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA )
		{
			c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump = X2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA;
		}
		
		if(c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump < X1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA )
		{
			c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump = X1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA;
		}
		
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value			= 0;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.s0			= (uint16_t)c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump;
		
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value		= ( cxStatusAlarmLowLimitForCurrentPumpOnLna.value << DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_LNA)  & 0x00000000000003FF; // bits 0-9
		cRPDO_409.data.value								= cRPDO_409.data.value  & 0xFFFFFFFFFFFFFC00;
		cRPDO_409.data.value								= cRPDO_409.data.value |  cxStatusAlarmLowLimitForCurrentPumpOnLna.value;


		//Bit 10-19: set alarm high limit for current laser pump on LNA section 
		if(c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump > X2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA )
		{
			c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump = X2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA;
		}
		
		if(c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump < X1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA )
		{
			c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump = X1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA;
		}
		
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value			= 0;
		cxStatusAlarmHighLimitForCurrentPumpOnLna.s0			= (uint16_t)c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump;
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value			= ( cxStatusAlarmHighLimitForCurrentPumpOnLna.value << DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_LNA ) & 0x00000000000FFC00 ; // bits  10-19
		cRPDO_409.data.value									= cRPDO_409.data.value  & 0xFFFFFFFFFFF003FF;
		cRPDO_409.data.value									= cRPDO_409.data.value |  cxStatusAlarmHighLimitForCurrentPumpOnLna.value;
		
		

	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
}
*/
