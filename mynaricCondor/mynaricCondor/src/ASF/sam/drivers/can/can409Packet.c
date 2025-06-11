
#include "can409Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51

static CAN_FRAME cRPDO_409;

/*---------------------------------------------------------------------------*/

void vInit409CanImage( void )
{
		cRPDO_409.data.value = 0;
		cRPDO_409.id = 0x409;
}

/*---------------------------------------------------------------------------*/
eMpbError_t getCan409( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_409, size );
	return eSuccess;
}
/*-----------------------------------------------------------------------------*/
eMpbError_t setCan409( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_409, pCan, size );
	return eSuccess;
}
/*-----------------------------------------------------------------------------*/


eMpbError_t eMpbCan409Decode( c409StatusDefinition_t *c409StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmHighLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost;
	//BytesUnion	cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna;
	//BytesUnion	cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForUnitBaseTemperature;	
	BytesUnion	cxStatusAlarmHighLimitForUnitBaseTemperature;
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = not_coerced;


	if(c409StatusDefinition != NULL)
	{
		/*Bit 0-9: set low alarm limit status value alarm low limit for current laser pump on LNA section */
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value					= 0;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value					= ( cRPDO_409.data.value >> DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_LNA) & 0x00000000000003FF; /* bits 0-9 */
		c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump		= (float)(cxStatusAlarmLowLimitForCurrentPumpOnLna.low);
					
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA ),
																										(float)(Y1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																										(float)(X2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA ),
																										(float)(Y2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																										c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump ,  coerce );
		
		c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump			= fxValue.fValue - FLOAT_ADJUST;
		
		/*Bit 10-19: set alarm high limit for current laser pump on LNA section */
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value						= ( cRPDO_409.data.value >> DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_LNA) & 0x00000000000003FF; /* bits  10-19 */
		c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump			= (float)(cxStatusAlarmHighLimitForCurrentPumpOnLna.low ) ;
		
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA ),
																										(float)(Y1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																										(float)(X2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA ),
																										(float)(Y2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																										c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump ,  coerce );
	
		c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump			= fxValue.fValue- FLOAT_ADJUST ;
		
		/*Bit 20-29: set alarm low limit for current first laser pump on Boost section */
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value							= ( cRPDO_409.data.value >> DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000003FF; /* 20-29 */
		c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump				= (float)(cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.low) ;
		
		
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST ),
																										(float)(Y1_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST),
																										(float)(X2_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST ),
																										(float)(Y2_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST),
																										c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump ,  coerce );
		
		c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump			= fxValue.fValue - FLOAT_ADJUST;

		/*Bit 30-39: status value alarm high limit for current first laser pump on Boost section, */			
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value							= ( cRPDO_409.data.value >> DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000003FF; /*30-39*/
		c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump				= (float)(cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.low);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST ),
																										(float)(Y1_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																										(float)(X2_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																										(float)(Y2_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																										c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump ,  coerce );
		
		c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump			= fxValue.fValue- FLOAT_ADJUST;
		
		/* Bit 48-55: status value alarm low limit for unit base temperature */
		cxStatusAlarmLowLimitForUnitBaseTemperature.value							= ( cRPDO_409.data.value >> DEF_CAN_0409_UNIT_TEMP_LOW_LIMIT) & 0x00000000000000FF; //48-55
		c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase				= (float)(cxStatusAlarmLowLimitForUnitBaseTemperature.byte[0]);
		
		
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_UNIT_TEMP_LOW),
																										(float)(Y1_409_UNIT_TEMP_LOW),
																										(float)(X2_409_UNIT_TEMP_LOW),
																										(float)(Y2_409_UNIT_TEMP_LOW),
																										c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase ,  coerce );
		
		c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase			= fxValue.fValue- FLOAT_ADJUST ;
		
		/*Bit 56-63: status value alarm high limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. */
		cxStatusAlarmHighLimitForUnitBaseTemperature.value							= ( cRPDO_409.data.value >> DEF_CAN_0409_UNIT_TEMP_HIGH_LIMIT) & 0x00000000000000FF; //Bit 56-63
		c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase				= (float)(cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]) ;
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_409_UNIT_TEMP_HIGH),
																										(float)(Y1_409_UNIT_TEMP_HIGH),
																										(float)(X2_409_UNIT_TEMP_HIGH),
																										(float)(Y2_409_UNIT_TEMP_HIGH),
																										c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase ,  coerce );
		
		c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase			= fxValue.fValue - FLOAT_ADJUST;
		
		if( c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump > c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump)
		{
			c409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump =  c409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump;
		}
		
	
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}




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
	//mpb_coerced_t coerce = coerced;


	if(c409StatusDefinition != NULL)
	{				
		/*Bit 0-9: set low alarm limit status value alarm low limit for current laser pump on LNA section */
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


		/*Bit 10-19: set alarm high limit for current laser pump on LNA section */
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
		
		/*Bit 20-29: set alarm low limit for current first laser pump on Boost section */
		if(c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump > X2_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump = X2_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		
		if(c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump < X1_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump = X1_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value			= 0;
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.s0				= (uint16_t)c409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump;
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value			= ( cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value << DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER ) & 0x000000003FF00000; // bits  20-29
		cRPDO_409.data.value											= cRPDO_409.data.value  & 0xFFFFFFFFC00FFFFF ;
		cRPDO_409.data.value											= cRPDO_409.data.value |  cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value;
		
		/*Bit 30-39: status value alarm high limit for current first laser pump on Boost section, */		
		if(c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump > X2_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump = X2_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		
		if(c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump < X1_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump = X1_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value			= 0;
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.s0				= (uint16_t)c409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump;
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value			= ( cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value << DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER ) & 0x000000FFC0000000; // bits  30-39
		cRPDO_409.data.value											= cRPDO_409.data.value  & 0xFFFFFF003FFFFFFF ;
		cRPDO_409.data.value											= cRPDO_409.data.value |  cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value;
		
		/*Bit 48-55: status value alarm low limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255  */
		if(c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase > X2_409_UNIT_TEMP_LOW )
		{
			c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase = X2_409_UNIT_TEMP_LOW;
		}
		
		if(c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase < X1_409_UNIT_TEMP_LOW )
		{
			c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase = X1_409_UNIT_TEMP_LOW;
		}
		
		cxStatusAlarmLowLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmLowLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase);
		cxStatusAlarmLowLimitForUnitBaseTemperature.value		= ( cxStatusAlarmLowLimitForUnitBaseTemperature.value << DEF_CAN_0409_UNIT_TEMP_LOW_LIMIT ) & 0x00FF000000000000; //48-55
		cRPDO_409.data.bytes[6]									= (uint8_t)(c409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase);


		//Bit 56-63: status value alarm high limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. 
		if(c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase > X2_409_UNIT_TEMP_HIGH )
		{
			c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase = X2_409_UNIT_TEMP_HIGH;
		}
		
		if(c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase < X1_409_UNIT_TEMP_HIGH )
		{
			c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase = X1_409_UNIT_TEMP_HIGH;
		}
		

		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0409_UNIT_TEMP_HIGH_LIMIT ) & 0xFF00000000000000; //Bit 56-63
		cRPDO_409.data.bytes[7]									= (uint8_t)(c409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase);
		
		


	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
}

