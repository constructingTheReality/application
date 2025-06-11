#include "can415Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_415;

/*---------------------------------------------------------------------------*/

void vInit415CanImage( void )
{
		cRPDO_415.data.value = 0;
		cRPDO_415.id = 0x415;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan415( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_415, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan415( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_415, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan415Encode( c415StatusDefinition_t *c415StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForUnitBaseTemperature;
	BytesUnion	cxStatusAlarmHighLimitForUnitBaseTemperature;
	
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c415StatusDefinition != NULL)
	{
		
		/* Bit 0-7: status value alarm low limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255 */
		if(c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit > X2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit = X2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit < X1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit = X1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																							c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit ,  coerce );

				
		cxStatusAlarmLowLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmLowLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForUnitBaseTemperature.value		= ( cxStatusAlarmLowLimitForUnitBaseTemperature.value << DEF_CAN_0415_ALARM_LOW_LIMIT_UNIT_TEMPERATURE ) & 0x00000000000000FF; //0-7
		cRPDO_415.data.bytes[0]									= (uint8_t)(fxValue.fValue);

		
		/*Bit 8-15: status value alarm high limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. */
		if(c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit > X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit = X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit < X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit = X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit ,  coerce );
		
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0415_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE ) & 0x000000000000FF00; 
		cRPDO_415.data.bytes[1]									= (uint8_t)(fxValue.fValue);
		
		/*Bit 16-23: status value alarm low limit for pump temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. */
		if(c415StatusDefinition->fPumpTemperatureLowAlarmLimit > X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureLowAlarmLimit = X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c415StatusDefinition->fPumpTemperatureLowAlarmLimit < X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureLowAlarmLimit = X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							c415StatusDefinition->fPumpTemperatureLowAlarmLimit ,  coerce );
		
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0415_ALARM_LOW_LIMIT_PUMP_TEMPERATURE ) & 0x0000000000FF0000;
		cRPDO_415.data.bytes[2]									= (uint8_t)(fxValue.fValue);
		
		/*Bit 24-31: status value alarm high limit for pump temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. */
		if(c415StatusDefinition->fPumpTemperatureHighAlarmLimit > X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureHighAlarmLimit = X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c415StatusDefinition->fPumpTemperatureHighAlarmLimit < X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureHighAlarmLimit = X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							c415StatusDefinition->fPumpTemperatureHighAlarmLimit ,  coerce );
		
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0415_ALARM_HIGH_LIMIT_PUMP_TEMPERATURE ) & 0x00000000FF000000;
		cRPDO_415.data.bytes[3]									= (uint8_t)(fxValue.fValue);
		
				
		/*Bit 32-39: status value alarm very low limit for pump temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. */
		if(c415StatusDefinition->fPumpTemperatureVeryLowAlarmLimit > X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureVeryLowAlarmLimit = X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c415StatusDefinition->fPumpTemperatureVeryLowAlarmLimit < X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureVeryLowAlarmLimit = X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							c415StatusDefinition->fPumpTemperatureVeryLowAlarmLimit ,  coerce );
		
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0415_ALARM_VERY_LOW_LIMIT_PUMP_TEMPERATURE ) & 0x000000FF00000000;
		cRPDO_415.data.bytes[4]									= (uint8_t)(fxValue.fValue);
		
		
		/*Bit 40-47: status value alarm very high limit for pump temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. */
		if(c415StatusDefinition->fPumpTemperatureVeryHighAlarmLimit > X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureVeryHighAlarmLimit = X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c415StatusDefinition->fPumpTemperatureVeryHighAlarmLimit < X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c415StatusDefinition->fPumpTemperatureVeryHighAlarmLimit = X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																							c415StatusDefinition->fPumpTemperatureVeryHighAlarmLimit ,  coerce );
		
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0415_ALARM_VERY_HIGH_LIMIT_PUMP_TEMPERATURE ) & 0x0000FF0000000000;
		cRPDO_415.data.bytes[5]									= (uint8_t)(fxValue.fValue);
		
		
		/* Bit 32-39: status value alarm low limit for backfacet current pump laser on LNA section, within the applicable operational back facet current range, resolution determined by the bit range value 0..255. (Note: The backfacet monitor is used for tracking aging of LNA pump laser) 
		if(c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna > X2_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA )
		{
			c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna = X2_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA;
		}
		
		if(c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna < X1_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA )
		{
			c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna = X1_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA),
																							(float)(Y1_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA),
																							(float)(X2_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA),
																							(float)(Y2_ALARM_LOW_LIMIT_BACKFACET_PUMP_LNA),
																							c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna ,  coerce );
				
		cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna.value			= 0;
		cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna.value			= ( cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna.value << DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER ) & 0x000000FF00000000; 
		cRPDO_404.data.bytes[4]									= (uint8_t)(fxValue.fValue);
		
		
		*/
		/*Bit 40-47: status value alarm high limit for back facet current pump laser on LNA section, within the applicable operational back facet current range, resolution determined by the bit range value 0..255  
		if(c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna > X2_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA )
		{
			c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna = X2_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA;
		}
		
		if(c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna < X1_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA )
		{
			c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna = X1_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
																							(float)(Y1_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
																							(float)(X2_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
																							(float)(Y2_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
																							c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna ,  coerce );
		
		fxValue.fValue                                          = fxValue.fValue;
		cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna.value		= 0;
		cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna.value		= ( cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna.value << DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER ) & 0x0000FF0000000000; 
		cRPDO_404.data.bytes[5]									= (uint8_t)(fxValue.fValue);
		
		*/
		
		


	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}




eMpbError_t eMpbCan415Decode( c415StatusDefinition_t *c415StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForUnitBaseTemperature;
	BytesUnion	cxStatusAlarmHighLimitForUnitBaseTemperature;
	
	
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c415StatusDefinition != NULL)
	{
		
		/* Bit 0-7: status value alarm low limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255 */
		cxStatusAlarmLowLimitForUnitBaseTemperature.value					= ( cRPDO_415.data.value >> DEF_CAN_0415_ALARM_LOW_LIMIT_UNIT_TEMPERATURE) & 0x00000000000000FF; 
		c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit				= (float)(cxStatusAlarmLowLimitForUnitBaseTemperature.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																										(float)(X1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																										(float)(Y2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																										(float)(X2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE),
																										c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit ,  coerce );
		
		c415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit				= fxValue.fValue;
		

		//Bit 56-63: status value alarm high limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255.
		cxStatusAlarmHighLimitForUnitBaseTemperature.value					= ( cRPDO_415.data.value >> DEF_CAN_0415_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE) & 0x00000000000000FF; 
		c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit			= (float)(cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																										(float)(X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																										(float)(Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																										(float)(X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE),
																										c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit ,  coerce );
		
		c415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit			= fxValue.fValue;
		
		
		
		
		// Bit 32-39: status value alarm low limit for backfacet current pump laser on LNA section, within the applicable operational back facet current range, resolution determined by the bit range value 0..255. (Note: The backfacet monitor is used for tracking aging of LNA pump laser) 
		/*cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna.value							= ( cRPDO_404.data.value >> DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000000FF; //32-39
		c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna			= (float)(cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
		(float)(X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
		(float)(Y2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
		(float)(X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
		c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna ,  coerce );
		
		c404StatusDefinition->fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna			= fxValue.fValue;
		
		
		
		//Bit 40-47: status value alarm high limit for back facet current pump laser on LNA section, within the applicable operational back facet current range, resolution determined by the bit range value 0..255  
		cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna.value							= ( cRPDO_404.data.value >> DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000000FF; //40-47
		c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna			= (float)(cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
		(float)(X1_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
		(float)(Y2_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
		(float)(X2_ALARM_HIGH_LIMIT_BACKFACET_PUMP_LNA),
		c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna ,  coerce );
		
		c404StatusDefinition->fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna			= fxValue.fValue;
		
		
		
		*/
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	


	
	


	
}
