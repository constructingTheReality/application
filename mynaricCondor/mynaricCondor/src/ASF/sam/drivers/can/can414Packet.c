
#include "can414Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_414;

/*---------------------------------------------------------------------------*/

void vInit414CanImage( void )
{
		cRPDO_414.data.value = 0;
		cRPDO_414.id = 0x414;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan414( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_414, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan414( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_414, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan414Encode( c414StatusDefinition_t *c414StatusDefinition, eBool_t bBoosterIsDisable, eBool_t bLnaIsDisable )
{
	


	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxBoosterOpticalInputPower;
	BytesUnion	cxBoosterOpticalOutputPower;
	BytesUnion	cxLnaOpticalOutputPower;
	BytesUnion	cxLnaOpticalInputPower;
	BytesUnion	cxUnitBaseTemperature;
	
	BytesUnion	cxPowerSupplyMonitor;
	
	
	
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = not_coerced;


	if(c414StatusDefinition != NULL)
	{
		
		/*Bit 0-9  Booster Optical Input Power -10 to 6dBm*/		
		if(c414StatusDefinition->fBoostOpticalInputPower > X2_414_BOOSTER_OPTICAL_INPUT_POWER )
		{
			c414StatusDefinition->fBoostOpticalInputPower = X2_414_BOOSTER_OPTICAL_INPUT_POWER;
		}
		
		if(c414StatusDefinition->fBoostOpticalInputPower < X1_414_BOOSTER_OPTICAL_INPUT_POWER )
		{
			c414StatusDefinition->fBoostOpticalInputPower = X1_414_BOOSTER_OPTICAL_INPUT_POWER;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_414_BOOSTER_OPTICAL_INPUT_POWER),
																							(float)(Y1_414_BOOSTER_OPTICAL_INPUT_POWER),
																							(float)(X2_414_BOOSTER_OPTICAL_INPUT_POWER),
																							(float)(Y2_414_BOOSTER_OPTICAL_INPUT_POWER),
																							c414StatusDefinition->fBoostOpticalInputPower ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//- FLOAT_ADJUST ;
		cxBoosterOpticalInputPower.value			= 0;
		cxBoosterOpticalInputPower.s0				= (uint16_t)(fxValue.fValue);
		cxBoosterOpticalInputPower.value			= ( cxBoosterOpticalInputPower.value << DEF_CAN_414_BOOSTER_OPTICAL_INPUT_POWER ) & 0x00000000000003FF; /* bits 0-9 */		
		cRPDO_414.data.value						= cRPDO_414.data.value & 0xFFFFFFFFFFFFFC00 ;
		cRPDO_414.data.value						= cRPDO_414.data.value |  cxBoosterOpticalInputPower.value;
		



		/*  bits 10-19 */
		if(c414StatusDefinition->fBoostOpticalOutputPower > X2_414_BOOSTER_OPTICAL_OUTPUT_POWER )
		{
			c414StatusDefinition->fBoostOpticalOutputPower = X2_414_BOOSTER_OPTICAL_OUTPUT_POWER;
		}
		
		if(c414StatusDefinition->fBoostOpticalOutputPower < X1_414_BOOSTER_OPTICAL_OUTPUT_POWER )
		{
			c414StatusDefinition->fBoostOpticalOutputPower = X1_414_BOOSTER_OPTICAL_OUTPUT_POWER;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							(float)(Y1_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							(float)(X2_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							(float)(Y2_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							c414StatusDefinition->fBoostOpticalOutputPower ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//- FLOAT_ADJUST ;
		
		if(bBoosterIsDisable == eTrue )
		{
			fxValue.fValue = 0;
		}
		
		
		cxBoosterOpticalOutputPower.value						= 0;
		cxBoosterOpticalOutputPower.s0							= (uint16_t)(fxValue.fValue);
		cxBoosterOpticalOutputPower.value						= ( cxBoosterOpticalOutputPower.value << DEF_CAN_414_BOOSTER_OPTICAL_OUTPUT_POWER ) & 0x00000000000FFC00; /* bits 10-19 */

		cRPDO_414.data.value									= cRPDO_414.data.value & 0xFFFFFFFFFFF003FF ;
		cRPDO_414.data.value									= cRPDO_414.data.value |  cxBoosterOpticalOutputPower.value;
		
		
		
		/*  bits 20-29 */
		if(c414StatusDefinition->fLnaOpticalInputtPower > X2_414_LNA_OPTICAL_INPUT_POWER )
		{
			c414StatusDefinition->fLnaOpticalInputtPower = X2_414_LNA_OPTICAL_INPUT_POWER;
		}
		
		if(c414StatusDefinition->fLnaOpticalInputtPower < X1_414_LNA_OPTICAL_INPUT_POWER )
		{
			c414StatusDefinition->fLnaOpticalInputtPower = X1_414_LNA_OPTICAL_INPUT_POWER;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_414_LNA_OPTICAL_INPUT_POWER),
																							(float)(Y1_414_LNA_OPTICAL_INPUT_POWER),
																							(float)(X2_414_LNA_OPTICAL_INPUT_POWER),
																							(float)(Y2_414_LNA_OPTICAL_INPUT_POWER),
																						c414StatusDefinition->fLnaOpticalInputtPower ,  coerce );
		
		fxValue.fValue                                          = fxValue.fValue ;//- FLOAT_ADJUST ;
		cxLnaOpticalInputPower.value							= 0;
		cxLnaOpticalInputPower.s0								= (uint16_t)(fxValue.fValue);
		cxLnaOpticalInputPower.value							= ( cxLnaOpticalInputPower.value << DEF_CAN_414_LNA_OPTICAL_INPUT_POWER ) & 0x000000003FF00000; /*20-29*/
		
		cRPDO_414.data.value									= cRPDO_414.data.value & 0xFFFFFFFFC00FFFFF ;
		cRPDO_414.data.value									= cRPDO_414.data.value |  cxLnaOpticalInputPower.value;
		
			
		
		/*  bits 30-39 */
		if(c414StatusDefinition->fLnaOpticalOutputPower > X2_414_LNA_OPTICAL_OUTPUT_POWER )
		{
			c414StatusDefinition->fLnaOpticalOutputPower = X2_414_LNA_OPTICAL_OUTPUT_POWER;
		}
		
		if(c414StatusDefinition->fLnaOpticalOutputPower < X1_414_LNA_OPTICAL_OUTPUT_POWER )
		{
			c414StatusDefinition->fLnaOpticalOutputPower = X1_414_LNA_OPTICAL_OUTPUT_POWER;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_414_LNA_OPTICAL_OUTPUT_POWER),
																							(float)(Y1_414_LNA_OPTICAL_OUTPUT_POWER),
																							(float)(X2_414_LNA_OPTICAL_OUTPUT_POWER),
																							(float)(Y2_414_LNA_OPTICAL_OUTPUT_POWER),
																							c414StatusDefinition->fLnaOpticalOutputPower ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//- FLOAT_ADJUST ;
		cxLnaOpticalOutputPower.value							= 0;
		
		if( bLnaIsDisable == eTrue)
		{			
			fxValue.fValue = 0;
		}
		cxLnaOpticalOutputPower.s0								= (uint16_t)(fxValue.fValue);
		cxLnaOpticalOutputPower.value							= ( cxLnaOpticalOutputPower.value << DEF_CAN_414_LNA_OPTICAL_OUTPUT_POWER ) & 0x000000FFC0000000; /*30-39*/ 
		
		cRPDO_414.data.value									= cRPDO_414.data.value & 0xFFFFFF003FFFFFFF ;
		cRPDO_414.data.value									= cRPDO_414.data.value |  cxLnaOpticalOutputPower.value;		

		
		/*  bits 40..47 */
		if(c414StatusDefinition->fUnitBaseTemperature > X2_414_UNIT_BASE_TEMPERATURE )
		{
			c414StatusDefinition->fUnitBaseTemperature = X2_414_UNIT_BASE_TEMPERATURE;
		}
		
		if(c414StatusDefinition->fUnitBaseTemperature < X1_414_UNIT_BASE_TEMPERATURE )
		{
			c414StatusDefinition->fUnitBaseTemperature = X1_414_UNIT_BASE_TEMPERATURE;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_414_UNIT_BASE_TEMPERATURE),
																							(float)(Y1_414_UNIT_BASE_TEMPERATURE),
																							(float)(X2_414_UNIT_BASE_TEMPERATURE),
																							(float)(Y2_414_UNIT_BASE_TEMPERATURE),
																							c414StatusDefinition->fUnitBaseTemperature ,  coerce );
		
		fxValue.fValue                                          = fxValue.fValue;// - FLOAT_ADJUST ;
		cxUnitBaseTemperature.value								= 0;
		cxUnitBaseTemperature.byte[0]							= (uint8_t)(fxValue.fValue);
		cxUnitBaseTemperature.value								= ( cxUnitBaseTemperature.value << DEF_CAN_414_UNIT_BASE_TEMPERATURE )  & 0x0000FF0000000000; /*40-47*/ 
		
		cRPDO_414.data.value									= cRPDO_414.data.value & 0xFFFF00FFFFFFFFFF ;
		cRPDO_414.data.value									= cRPDO_414.data.value |  cxUnitBaseTemperature.value;		

				

		/*  bits 48-55 */
		if(c414StatusDefinition->fPowerSupplyMonitor > X2_414_POWER_SUPPLY_MONITOR )
		{
			c414StatusDefinition->fPowerSupplyMonitor = X2_414_POWER_SUPPLY_MONITOR;
		}
		
		if(c414StatusDefinition->fPowerSupplyMonitor < X1_414_POWER_SUPPLY_MONITOR )
		{
			c414StatusDefinition->fPowerSupplyMonitor = X1_414_POWER_SUPPLY_MONITOR;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_414_POWER_SUPPLY_MONITOR),
																							(float)(Y1_414_POWER_SUPPLY_MONITOR),
																							(float)(X2_414_POWER_SUPPLY_MONITOR),
																							(float)(Y2_414_POWER_SUPPLY_MONITOR),
																							c414StatusDefinition->fPowerSupplyMonitor ,  coerce );
		
		fxValue.fValue                                          = fxValue.fValue ;//- FLOAT_ADJUST ;
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(fxValue.fValue);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_414_POWER_SUPPLY_MONITOR ) & 0x00FF000000000000; /*48-55*/
		
		cRPDO_414.data.value									= cRPDO_414.data.value & 0xFF00FFFFFFFFFFFF ;
		cRPDO_414.data.value									= cRPDO_414.data.value |  cxPowerSupplyMonitor.value;
				
		//cRPDO_414.data.bytes[4]									= cxPowerSupplyMonitor.byte[4];
		//cRPDO_414.data.bytes[9]									= cxPowerSupplyMonitor.byte[9];
				
		
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




eMpbError_t eMpbCan414Decode( c414StatusDefinition_t *c414StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxBoosterOpticalInputPower;
	BytesUnion	cxBoosterOpticalOutputPower;
	BytesUnion	cxLnaOpticalOutputPower;
	BytesUnion	cxLnaOpticalInputPower;
	BytesUnion	cxUnitBaseTemperature;
	BytesUnion	cxPowerSupplyMonitor;
	
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c414StatusDefinition != NULL)
	{
		/*Bit 0-9  Booster Optical Input Power -10 to 6dBm*/
		cxBoosterOpticalInputPower.value						= 0;
		cxBoosterOpticalInputPower.value						= ( cRPDO_414.data.value >> DEF_CAN_414_BOOSTER_OPTICAL_INPUT_POWER) & 0x00000000000003FF; // bits 0-9
		
		c414StatusDefinition->fBoostOpticalInputPower			= (float)(cxBoosterOpticalInputPower.s0 );
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_414_BOOSTER_OPTICAL_INPUT_POWER),
																										(float)(X1_414_BOOSTER_OPTICAL_INPUT_POWER),
																										(float)(Y2_414_BOOSTER_OPTICAL_INPUT_POWER),
																										(float)(X2_414_BOOSTER_OPTICAL_INPUT_POWER),
																										c414StatusDefinition->fBoostOpticalInputPower ,  coerce );
		
		c414StatusDefinition->fBoostOpticalInputPower			= fxValue.fValue;
		
		/*Bit bits 10-19  Booster Optical Output Power */
		cxBoosterOpticalOutputPower.value						= 0;
		cxBoosterOpticalOutputPower.value						= ( cRPDO_414.data.value >> DEF_CAN_414_BOOSTER_OPTICAL_OUTPUT_POWER) & 0x00000000000003FF; // bits 10-19
		c414StatusDefinition->fBoostOpticalOutputPower			= (float)(cxBoosterOpticalOutputPower.s0 );
	
		if(cxBoosterOpticalOutputPower.value == 0)
		{
			c414StatusDefinition->fBoostOpticalOutputPower = 0.0f;
		}
		else
		{
		
			c414StatusDefinition->fBoostOpticalOutputPower			= mpb_math_flinear_approx(  (float)(Y1_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							(float)(X1_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							(float)(Y2_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							(float)(X2_414_BOOSTER_OPTICAL_OUTPUT_POWER),
																							c414StatusDefinition->fBoostOpticalOutputPower ,  coerce );		
		}
			
		/*Bit 20-29 */
		cxLnaOpticalInputPower.value							= 0;
		cxLnaOpticalInputPower.value							= ( cRPDO_414.data.value >> DEF_CAN_414_LNA_OPTICAL_INPUT_POWER) & 0x00000000000003FF; 
		c414StatusDefinition->fLnaOpticalInputtPower			= (float)(cxLnaOpticalInputPower.s0 );
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_414_LNA_OPTICAL_INPUT_POWER),
																							(float)(X1_414_LNA_OPTICAL_INPUT_POWER),
																							(float)(Y2_414_LNA_OPTICAL_INPUT_POWER),
																							(float)(X2_414_LNA_OPTICAL_INPUT_POWER),
																							c414StatusDefinition->fLnaOpticalInputtPower ,  coerce );
		
		c414StatusDefinition->fLnaOpticalInputtPower			= fxValue.fValue;

		/*Bit 30-39 */
		cxLnaOpticalOutputPower.value							= 0;
		cxLnaOpticalOutputPower.value							= ( cRPDO_414.data.value >> DEF_CAN_414_LNA_OPTICAL_OUTPUT_POWER) & 0x00000000000003FF; 
		c414StatusDefinition->fLnaOpticalOutputPower			= (float)(cxLnaOpticalOutputPower.s0 );
		
		

		if(cxLnaOpticalOutputPower.value == 0)
		{
			c414StatusDefinition->fLnaOpticalOutputPower			= 0.0f;
		}
		else
		{
			
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_414_LNA_OPTICAL_OUTPUT_POWER),
																							(float)(X1_414_LNA_OPTICAL_OUTPUT_POWER),
																							(float)(Y2_414_LNA_OPTICAL_OUTPUT_POWER),
																							(float)(X2_414_LNA_OPTICAL_OUTPUT_POWER),
																							c414StatusDefinition->fLnaOpticalOutputPower ,  coerce );
		
		c414StatusDefinition->fLnaOpticalOutputPower			= fxValue.fValue;
		}

		/*Bit 40-47 */
		cxUnitBaseTemperature.value							= 0;
		cxUnitBaseTemperature.value							= ( cRPDO_414.data.value >> DEF_CAN_414_UNIT_BASE_TEMPERATURE) & 0x00000000000000FF;
		c414StatusDefinition->fUnitBaseTemperature			= (float)(cxUnitBaseTemperature.byte[0] );
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_414_UNIT_BASE_TEMPERATURE),
																							(float)(X1_414_UNIT_BASE_TEMPERATURE),
																							(float)(Y2_414_UNIT_BASE_TEMPERATURE),
																							(float)(X2_414_UNIT_BASE_TEMPERATURE),
																							c414StatusDefinition->fUnitBaseTemperature ,  coerce );
		
		c414StatusDefinition->fUnitBaseTemperature			= fxValue.fValue;


		/*Bit 48-55 */
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_414.data.value >> DEF_CAN_414_POWER_SUPPLY_MONITOR) & 0x00000000000000FF;
		c414StatusDefinition->fPowerSupplyMonitor			= (float)(cxPowerSupplyMonitor.byte[0] );
		
		fxValue.fValue										= mpb_math_flinear_approx(  (float)(Y1_414_POWER_SUPPLY_MONITOR),
																						(float)(X1_414_POWER_SUPPLY_MONITOR),
																						(float)(Y2_414_POWER_SUPPLY_MONITOR),
																						(float)(X2_414_POWER_SUPPLY_MONITOR),
																						c414StatusDefinition->fPowerSupplyMonitor ,  coerce );
		
		c414StatusDefinition->fPowerSupplyMonitor			= fxValue.fValue;



		
		
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
