
#include "can404Packet.h"
//#include "can409Packet.h"

#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_404;

/*---------------------------------------------------------------------------*/

void vInit404CanImage( void )
{
		cRPDO_404.data.value = 0;
		cRPDO_404.id = 0x404;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan404( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_404, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan404( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_404, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan404Encode( c404StatusDefinition_t *c404StatusDefinition )
{
	


	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmHighLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForUnitBaseTemperature;
	
	
	BytesUnion	cxStatusAlarmHighLimitForUnitBaseTemperature;
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = not_coerced;
	uint32_t   usValue;

	if(c404StatusDefinition != NULL)
	{
		
		
		/* Bit 0-15: status value alarm low limit for current laser pump on LNA section, within the applicable operation laser current range, resolution determined by the bit range value 0..255. */
		if(c404StatusDefinition->fLnaLowLimitCurrentAlarm > X2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA )
		{
			c404StatusDefinition->fLnaLowLimitCurrentAlarm = X2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA;
		}
		
		if(c404StatusDefinition->fLnaLowLimitCurrentAlarm < X1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA )
		{
			c404StatusDefinition->fLnaLowLimitCurrentAlarm = X1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																							(float)(Y1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																							(float)(X2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																							(float)(Y2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																							c404StatusDefinition->fLnaLowLimitCurrentAlarm ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value			= 0;
		usValue													= (uint32_t)fxValue.fValue;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.low				= usValue;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value			= ( cxStatusAlarmLowLimitForCurrentPumpOnLna.value << DEF_CAN_404_STATUS_LOW_LIMIT_POWER_INPUT_LNA ) & 0x000000000000FFFF; /* bits 0-15 */
		cRPDO_404.data.bytes[0]									= cxStatusAlarmLowLimitForCurrentPumpOnLna.byte[0];
		cRPDO_404.data.bytes[1]									= cxStatusAlarmLowLimitForCurrentPumpOnLna.byte[1];


		/*Bit 16-31: status value alarm high limit for current laser pump on LNA section, within the applicable operation laser current range, resolution determined by the bit range value 0..255 */
		if(c404StatusDefinition->fLnaHighLimitCurrentAlarm > X2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA )
		{
			c404StatusDefinition->fLnaHighLimitCurrentAlarm = X2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA;
		}
		
		if(c404StatusDefinition->fLnaHighLimitCurrentAlarm < X1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA )
		{
			c404StatusDefinition->fLnaHighLimitCurrentAlarm = X1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							(float)(Y1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							(float)(X2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							(float)(Y2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							c404StatusDefinition->fLnaHighLimitCurrentAlarm ,  coerce );
		
		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value			= 0;
		usValue													= (uint32_t)fxValue.fValue;
		cxStatusAlarmHighLimitForCurrentPumpOnLna.low			= usValue;
		
				
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value			= ( cxStatusAlarmHighLimitForCurrentPumpOnLna.value << DEF_CAN_404_STATUS_HIGH_LIMIT_POWER_INPUT_LNA ) & 0x00000000FFFF0000; /* bits  16-31*/
		cRPDO_404.data.bytes[2]									= cxStatusAlarmHighLimitForCurrentPumpOnLna.byte[2];
		cRPDO_404.data.bytes[3]									= cxStatusAlarmHighLimitForCurrentPumpOnLna.byte[3];
		
		
		

		/* Bit 32-47: status value alarm low limit for current first laser pump on Boost section, within the applicable operation laser current range, resolution is determined by the bit range 0..255 */
		if(c404StatusDefinition->fBoostLowLimitCurrentAlarm > X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c404StatusDefinition->fBoostLowLimitCurrentAlarm = X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		
		if(c404StatusDefinition->fBoostLowLimitCurrentAlarm < X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c404StatusDefinition->fBoostLowLimitCurrentAlarm = X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							(float)(Y1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							(float)(X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							(float)(Y2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							c404StatusDefinition->fBoostLowLimitCurrentAlarm ,  coerce );
		
		fxValue.fValue													= fxValue.fValue;// + FLOAT_ADJUST ;		
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value			= 0;
		usValue													= (uint32_t)fxValue.fValue;		
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.low				= usValue;
		
				
				
				
		
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value			= ( cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value << DEF_CAN_404_STATUS_LOW_LIMIT_CURRENT_BOOSTER ) & 0x0000FFFF00000000; /* 32-47 */
		cRPDO_404.data.bytes[4]											= cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.byte[4];
		cRPDO_404.data.bytes[5]											= cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.byte[5];
		
		
		

		/*Bit 48-63: status value alarm high limit for current first laser pump on Boost section, within the applicable operation laser current range, the resolution is determined by the bit range 0..255. */
		if(c404StatusDefinition->fBoostHighLimitCurrentAlarm > X2_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c404StatusDefinition->fBoostHighLimitCurrentAlarm = X2_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		
		if(c404StatusDefinition->fBoostHighLimitCurrentAlarm < X1_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST )
		{
			c404StatusDefinition->fBoostHighLimitCurrentAlarm = X1_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							(float)(Y1_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							(float)(X2_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							(float)(Y2_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST),
																							c404StatusDefinition->fBoostHighLimitCurrentAlarm ,  coerce );
		fxValue.fValue													= fxValue.fValue ;//+ FLOAT_ADJUST ;				
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value			= 0;
		usValue															= (uint32_t)fxValue.fValue;
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.low			= usValue;
		
				
				
				
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value			= ( cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value << DEF_CAN_404_STATUS_HIGH_LIMIT_CURRENT_BOOSTER ) & 0xFFFF000000000000; /*48-63*/
		cRPDO_404.data.bytes[6]											= cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.byte[6];
		cRPDO_404.data.bytes[7]											= cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.byte[7];
	
		
		
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
		/*Bit 48-55: status value alarm low limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255 
		if(c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature > X2_ALARM_LOW_LIMIT_UNIT_TEMPERATURE )
		{
			c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature = X2_ALARM_LOW_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature < X1_ALARM_LOW_LIMIT_UNIT_TEMPERATURE )
		{
			c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature = X1_ALARM_LOW_LIMIT_UNIT_TEMPERATURE;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
																							c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature ,  coerce );

				
		cxStatusAlarmLowLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmLowLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForUnitBaseTemperature.value		= ( cxStatusAlarmLowLimitForUnitBaseTemperature.value << DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER ) & 0x00FF000000000000; //48-55
		cRPDO_404.data.bytes[6]									= (uint8_t)(fxValue.fValue);

		*/
		/*Bit 56-63: status value alarm high limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. 
		if(c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature > X2_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature = X2_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		if(c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature < X1_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE )
		{
			c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature = X1_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y1_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(X2_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
																							(float)(Y2_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
																							c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature ,  coerce );
		
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= 0;
		cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForUnitBaseTemperature.value		= ( cxStatusAlarmHighLimitForUnitBaseTemperature.value << DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER ) & 0x00FF000000000000; //Bit 56-63
		cRPDO_404.data.bytes[7]									= (uint8_t)(fxValue.fValue);
		
		*/


	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}




eMpbError_t eMpbCan404Decode( c404StatusDefinition_t *c404StatusDefinition )
{
	
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmHighLimitForCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost;
	BytesUnion	cxStatusAlarmLowLimitForBackfacetCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmHighLimitForBackfacetCurrentPumpOnLna;
	BytesUnion	cxStatusAlarmLowLimitForUnitBaseTemperature;
	
	
	BytesUnion	cxStatusAlarmHighLimitForUnitBaseTemperature;
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c404StatusDefinition != NULL)
	{
		// Bit 0-15: status value alarm low limit for current laser pump on LNA section, within the applicable operation laser current range, resolution determined by the bit range value 0..255. 
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value						= 0;
		cxStatusAlarmLowLimitForCurrentPumpOnLna.value						= ( cRPDO_404.data.value >> DEF_CAN_404_STATUS_LOW_LIMIT_POWER_INPUT_LNA) & 0x000000000000FFFF; // bits 0-15
		c404StatusDefinition->fLnaLowLimitCurrentAlarm						= (float)(cxStatusAlarmLowLimitForCurrentPumpOnLna.value  );
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																										(float)(X1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																										(float)(Y2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																										(float)(X2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA),
																										c404StatusDefinition->fLnaLowLimitCurrentAlarm ,  coerce );
		
		c404StatusDefinition->fLnaLowLimitCurrentAlarm						= fxValue.fValue;
		
		
		//Bit 16-31: status value alarm high limit for current laser pump on LNA section, within the applicable operation laser current range, resolution determined by the bit range value 0..255 
		cxStatusAlarmHighLimitForCurrentPumpOnLna.value			= ( cRPDO_404.data.value >> DEF_CAN_404_STATUS_HIGH_LIMIT_POWER_INPUT_LNA) & 0x000000000000FFFF; // bits  16-31
		c404StatusDefinition->fLnaHighLimitCurrentAlarm			= (float)(cxStatusAlarmHighLimitForCurrentPumpOnLna.value );
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							(float)(X1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							(float)(Y2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),
																							(float)(X2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA),	
																							c404StatusDefinition->fLnaHighLimitCurrentAlarm ,  coerce );
		
		c404StatusDefinition->fLnaHighLimitCurrentAlarm			= fxValue.fValue;
		

		// Bit 32-47: status value alarm low limit for current first laser pump on Boost section, within the applicable operation laser current range, resolution is determined by the bit range 0..255 
		cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value		= ( cRPDO_404.data.value >> DEF_CAN_404_STATUS_LOW_LIMIT_CURRENT_BOOSTER) & 0x000000000000FFFF; //32-47 
		c404StatusDefinition->fBoostLowLimitCurrentAlarm			= (float)(cxStatusAlarmLowLimitForCurrenFirstPumpOnBoost.value );
		
		fxValue.fValue												= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								(float)(X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								(float)(Y2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								(float)(X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								c404StatusDefinition->fBoostLowLimitCurrentAlarm ,  coerce );
		
		c404StatusDefinition->fBoostLowLimitCurrentAlarm			= fxValue.fValue;
		
		

		//Bit 48-63: status value alarm high limit for current first laser pump on Boost section, within the applicable operation laser current range, the resolution is determined by the bit range 0..255. 
		cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value		= ( cRPDO_404.data.value >> DEF_CAN_404_STATUS_HIGH_LIMIT_CURRENT_BOOSTER) & 0x000000000000FFFF; //48-63
		c404StatusDefinition->fBoostHighLimitCurrentAlarm			= (float)(cxStatusAlarmHighLimitForCurrentFirstPumpOnBoost.value  )  ;
		
		fxValue.fValue												= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								(float)(X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								(float)(Y2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								(float)(X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST),
																								c404StatusDefinition->fBoostHighLimitCurrentAlarm ,  coerce );
		
		c404StatusDefinition->fBoostHighLimitCurrentAlarm			= fxValue.fValue;
		
		
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
		
		
		//Bit 48-55: status value alarm low limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255  
		cxStatusAlarmLowLimitForUnitBaseTemperature.value							= ( cRPDO_404.data.value >> DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER) & 0x00000000000000FF; //48-55
		c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature			= (float)(cxStatusAlarmLowLimitForUnitBaseTemperature.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
		(float)(X1_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
		(float)(Y2_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
		(float)(X2_ALARM_LOW_LIMIT_UNIT_TEMPERATURE),
		c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature ,  coerce );
		
		c404StatusDefinition->fStatusAlarmLowLimitForUnitBaseTemperature			= fxValue.fValue;
		

		//Bit 56-63: status value alarm high limit for unit base temperature, within the range of -40°C to +90°C, the resolution is determined by the bit range 0..255. 
		cxStatusAlarmHighLimitForUnitBaseTemperature.value							= ( cRPDO_404.data.value >> DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER) & 0x00000000000000FF; //Bit 56-63
		c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature			= (float)(cxStatusAlarmHighLimitForUnitBaseTemperature.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
		(float)(X1_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
		(float)(Y2_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
		(float)(X2_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE),
		c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature ,  coerce );
		
		c404StatusDefinition->fStatusAlarmHighLimitForUnitBaseTemperature			= fxValue.fValue;
		*/
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	


	
	


	
}