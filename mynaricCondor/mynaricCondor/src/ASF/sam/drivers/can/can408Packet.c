
#include "can408Packet.h"

#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_408;

/*---------------------------------------------------------------------------*/

void vInit408CanImage( void )
{
	cRPDO_408.data.value = 0;
	cRPDO_408.id = 0x408;
}
/*------------------------------------------------------*/
eMpbError_t getCan408( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_408, size );
	return eSuccess;
}

/*------------------------------------------------------*/



eMpbError_t setCan408( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_408, pCan, size );
	return eSuccess;
}
/*------------------------------------------------------------*/


eMpbError_t eMpbCan408Encode( c408StatusDefinition_t *c408StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForPowerInputLna;
	BytesUnion	cxStatusAlarmHighLimitForPowerInputLna;
	BytesUnion	cxStatusAlarmLowLimitForPowerOutputLna;
	BytesUnion	cxStatusAlarmHighLimitForPowerOutputLna;
	BytesUnion	cxStatusAlarmLowLimitForPowerInputBooster;
	BytesUnion	cxStatusAlarmHighLimitForPowerInputBooster;
	BytesUnion	cxStatusAlarmLowLimitForPowerOutputBooster;
	BytesUnion	cxStatusAlarmHighLimitForPowerOutputBooster;
	floatUnion  fxValue;
	//mpb_coerced_t coerce = not_coerced;
	

	if(c408StatusDefinition != NULL)
	{
		
		
		/* Bit 0-7: status value alarm low limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		if(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput > X2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput = X2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
		}
		
		if(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput < X1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput = X1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
		}
		
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
		(float)(Y1_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
		(float)(X2_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
		(float)(Y2_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
		c408StatusDefinition->fSetStatusAlarmLowLimitForPowerInputLna ,  coerce );*/
		cxStatusAlarmLowLimitForPowerInputLna.value				= 0;
		cxStatusAlarmLowLimitForPowerInputLna.byte[0]			= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput);
		
		cxStatusAlarmLowLimitForPowerInputLna.value				= ( cxStatusAlarmLowLimitForPowerInputLna.value << DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_INPUT_LNA ) & 0x00000000000000FF; /* bits 0-7 */
		cRPDO_408.data.bytes[0]									= cxStatusAlarmLowLimitForPowerInputLna.value;

		/*Bit 8-15: status value alarm high limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		if(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput > X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput = X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
		}
		
		if(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput < X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput = X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
		}
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
		(float)(Y1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
		(float)(X2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
		(float)(Y2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
		c408StatusDefinition->fSetStatusAlarmHighLimitForPowerInputLna ,  coerce );*/
		cxStatusAlarmHighLimitForPowerInputLna.value			= 0;
		cxStatusAlarmHighLimitForPowerInputLna.byte[0]			= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput);
		cxStatusAlarmHighLimitForPowerInputLna.value			= ( cxStatusAlarmHighLimitForPowerInputLna.value << DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_INPUT_LNA ) & 0x000000000000FF00; /* bits  8-15*/
		cRPDO_408.data.bytes[1]									= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput);
		
		/* Bit 16-23: status value alarm low limit for power output on LNA section, within the range of -10 dBm to 0 dBm, the resolution is determined by the bit range 0..255. */
		if(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput > X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput = X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
		}
		
		if(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput < X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput = X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
		}
		
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
		(float)(Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
		(float)(X2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
		(float)(Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
		c408StatusDefinition->fSetStatusAlarmLowLimitForPowerOutputLna ,  coerce );*/
		cxStatusAlarmLowLimitForPowerOutputLna.value			= 0;
		cxStatusAlarmLowLimitForPowerOutputLna.byte[0]			= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput);
		cxStatusAlarmLowLimitForPowerOutputLna.value			= ( cxStatusAlarmLowLimitForPowerOutputLna.value << DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_OUTPUT_LNA ) & 0x0000000000FF0000; /* 16-23 */
		cRPDO_408.data.bytes[2]									= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput);
		
		

		/* Bit 24-31: status value alarm high limit for power output on LNA section, within the range of -10 dBm to 0 dBm, the resolution is determined by the bit range 0..255 */
		if(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput > X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput = X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
		}
		
		if(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput < X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA )
		{
			c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput = X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
		}
		
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
		(float)(Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
		(float)(X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
		(float)(Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
		c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput ,  coerce );*/
		cxStatusAlarmHighLimitForPowerOutputLna.value			= 0;
		cxStatusAlarmHighLimitForPowerOutputLna.byte[0]			= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput);
		cxStatusAlarmHighLimitForPowerOutputLna.value			= ( cxStatusAlarmHighLimitForPowerOutputLna.value << DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_OUTPUT_LNA ) & 0x00000000FF000000; /*24-31*/
		cRPDO_408.data.bytes[3]									= (uint8_t)(c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput);
		
		/* Bit 32-39: status value alarm low limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		if(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput > X2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput = X2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		if(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput < X1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput = X1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
		(float)(Y1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
		(float)(X2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
		(float)(Y2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
		c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput ,  coerce );*/
		cxStatusAlarmLowLimitForPowerInputBooster.value			= 0;
		cxStatusAlarmLowLimitForPowerInputBooster.byte[0]		= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput);
		cxStatusAlarmLowLimitForPowerInputBooster.value			= ( cxStatusAlarmLowLimitForPowerInputBooster.value << DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER ) & 0x000000FF00000000; /*32-39*/
		cRPDO_408.data.bytes[4]									= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput);
		
		/*Bit 40-47: status value alarm high limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		if(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput > X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput = X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		if(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput < X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput = X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
		(float)(Y1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
		(float)(X2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
		(float)(Y2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
		c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput ,  coerce );*/
		cxStatusAlarmHighLimitForPowerInputBooster.value		= 0;
		cxStatusAlarmHighLimitForPowerInputBooster.byte[0]		= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput);
		cxStatusAlarmHighLimitForPowerInputBooster.value		= ( cxStatusAlarmHighLimitForPowerInputBooster.value << DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER ) & 0x0000FF0000000000; /*40-47*/
		cRPDO_408.data.bytes[5]									= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput);
		
		/*Bit 48-55: status value alarm low limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255.  */
		if(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput > X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput = X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		if(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput < X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput = X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
		(float)(Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
		(float)(X2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
		(float)(Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
		c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput ,  coerce );*/
		cxStatusAlarmLowLimitForPowerOutputBooster.value		= 0;
		cxStatusAlarmLowLimitForPowerOutputBooster.byte[0]		= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput);
		cxStatusAlarmLowLimitForPowerOutputBooster.value		= ( cxStatusAlarmLowLimitForPowerOutputBooster.value << DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER ) & 0x00FF000000000000; /*48-55*/
		cRPDO_408.data.bytes[6]									= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput);


		/*Bit 56-63: status value alarm high limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255. */
		if(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput > X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput = X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		if(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput < X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput = X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
		(float)(Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
		(float)(X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
		(float)(Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
		c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput ,  coerce );*/
		cxStatusAlarmHighLimitForPowerOutputBooster.value		= 0;
		cxStatusAlarmHighLimitForPowerOutputBooster.byte[0]		= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput);
		cxStatusAlarmHighLimitForPowerOutputBooster.value		= ( cxStatusAlarmHighLimitForPowerOutputBooster.value << DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER ) & 0x00FF000000000000; /*Bit 56-63*/
		cRPDO_408.data.bytes[7]									= (uint8_t)(c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput);
		
		


	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	
	return eMpbError;
	
}

eMpbError_t eMpbCan408Decode( c408StatusDefinition_t *c408StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxStatusAlarmLowLimitForPowerInputLna;
	BytesUnion	cxStatusAlarmHighLimitForPowerInputLna;
	BytesUnion	cxStatusAlarmLowLimitForPowerOutputLna;
	BytesUnion	cxStatusAlarmHighLimitForPowerOutputLna;
	BytesUnion	cxStatusAlarmLowLimitForPowerInputBooster;
	BytesUnion	cxStatusAlarmHighLimitForPowerInputBooster;
	BytesUnion	cxStatusAlarmLowLimitForPowerOutputBooster;
	BytesUnion	cxStatusAlarmHighLimitForPowerOutputBooster;
	floatUnion  fxValue;
	mpb_coerced_t coerce = not_coerced;
	
	if(c408StatusDefinition != NULL)
	{
		
		
		/* Bit 0-7: status value alarm low limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		cxStatusAlarmLowLimitForPowerInputLna.value							= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_INPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput		= (float)(cxStatusAlarmLowLimitForPowerInputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA ),
																										(float)(Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																										(float)(X2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA ),
																										(float)(Y2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																										c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput ,  coerce );
		
		fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST ;//- FLOAT_ADJUST_408;
				
		c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput			= fxValue.fValue;
																							
		
		/*Bit 8-15: status value alarm high limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		cxStatusAlarmHighLimitForPowerInputLna.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_INPUT_LNA) & 0x00000000000000FF; /* bits 8..15 */
		c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput		= (float)(cxStatusAlarmHighLimitForPowerInputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA ),
																										(float)(Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																										(float)(X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA ),
																										(float)(Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																										c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput ,  coerce );
		fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST;// - FLOAT_ADJUST_408;
		
		c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput			= fxValue.fValue;
		
		/* Bit 16-23: status value alarm low limit for power output on LNA section, within the range of -15 dBm to 0 dBm, the resolution is determined by the bit range 0..255. */
		cxStatusAlarmLowLimitForPowerOutputLna.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_OUTPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput		= (float)(cxStatusAlarmLowLimitForPowerOutputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA ),
																										(float)(Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																										(float)(X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA ),
																										(float)(Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),																										
																										c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput ,  coerce );
																										
		fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST;// - FLOAT_ADJUST_408;
		
		c408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput			= fxValue.fValue;		
		
		/* Bit 24-31: status value alarm high limit for power output on LNA section, within the range of -15 dBm to 0 dBm, the resolution is determined by the bit range 0..255 */
		cxStatusAlarmHighLimitForPowerOutputLna.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_OUTPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput		= (float)(cxStatusAlarmHighLimitForPowerOutputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA ),
																										(float)(Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																										(float)(X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA ),
																										(float)(Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																										c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput ,  coerce );
		fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST;//- FLOAT_ADJUST_408;
		
		c408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput			= fxValue.fValue;
		
		/* Bit 32-39: status value alarm low limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		cxStatusAlarmLowLimitForPowerInputBooster.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput	= (float)(cxStatusAlarmLowLimitForPowerInputBooster.byte[0]);
		fxValue.fValue														=	0;
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(X1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER ),
																										(float)(Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																										(float)(X2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER ),
																										(float)(Y2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																											c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput ,  coerce );
		fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST;//- FLOAT_ADJUST_408 - 0.03;
		
		
		c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput			= fxValue.fValue;
				
		/*Bit 40-47: status value alarm high limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		cxStatusAlarmHighLimitForPowerInputBooster.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput			= (float)(cxStatusAlarmHighLimitForPowerInputBooster.byte[0]);
		
		fxValue.fValue															= mpb_math_flinear_approx(  (float)(X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER ),
																											(float)(Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																											(float)(X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER ),
																											(float)(Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																											c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput ,  coerce );
	   	fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST;//- FLOAT_ADJUST_408;

		c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput			= fxValue.fValue;		
		
		/*Bit 48-55: status value alarm low limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255.  */
		cxStatusAlarmLowLimitForPowerOutputBooster.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput			= (float)(cxStatusAlarmLowLimitForPowerOutputBooster.byte[0]);
		
		fxValue.fValue															= mpb_math_flinear_approx(  (float)(X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER ),
																											(float)(Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER ),
																											(float)(Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																											c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput ,  coerce );
		fxValue.fValue															= fxValue.fValue- FLOAT_ADJUST;// - FLOAT_ADJUST_408;

		c408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput			= fxValue.fValue;
		
		/*Bit 56-63: status value alarm high limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255. */
		cxStatusAlarmHighLimitForPowerOutputBooster.value						= ( cRPDO_408.data.value >> DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput			= (float)(cxStatusAlarmHighLimitForPowerOutputBooster.byte[0]);

		fxValue.fValue															= mpb_math_flinear_approx(  (float)(X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER ),
																											(float)(Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER ),
																											(float)(Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																											c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput ,  coerce );
		fxValue.fValue															= fxValue.fValue - FLOAT_ADJUST;// - FLOAT_ADJUST_408;
																											
		c408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput			= fxValue.fValue;		
		
		
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	return eMpbError;
	
}