
#include "can403Packet.h"
#include "dictionaryUtils.h"

//#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51

static CAN_FRAME cRPDO_403;


/*---------------------------------------------------------------------------*/

void vInit403CanImage( void )
{
	cRPDO_403.data.value = 0;
	cRPDO_403.id = 0x403;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan403( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_403, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan403( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_403, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/

/*-------------------------------------------------------------*/
eMpbError_t eMpbCan403Encode( c403StatusDefinition_t *c403StatusDefinition )
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
	

	if(c403StatusDefinition != NULL)
	{
		
		
		/* Bit 0-7: status value alarm low limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		if(c403StatusDefinition->fLnaPowerInputAlarmLowLimit > X2_ALARM_LOW_LIMIT_POWER_INPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerInputAlarmLowLimit = X2_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
		}
		
		if(c403StatusDefinition->fLnaPowerInputAlarmLowLimit < X1_ALARM_LOW_LIMIT_POWER_INPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerInputAlarmLowLimit = X1_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																							(float)(Y1_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																							(float)(X2_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																							(float)(Y2_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																							c403StatusDefinition->fLnaPowerInputAlarmLowLimit ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue;// + FLOAT_ADJUST ;//- FLOAT_ADJUST_ENCODE ;
		cxStatusAlarmLowLimitForPowerInputLna.value				= 0;
		cxStatusAlarmLowLimitForPowerInputLna.byte[0]			= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForPowerInputLna.value				= ( cxStatusAlarmLowLimitForPowerInputLna.value << DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_LNA ) & 0x00000000000000FF; /* bits 0-7 */
		cRPDO_403.data.bytes[0]									= cxStatusAlarmLowLimitForPowerInputLna.value;

		/*Bit 8-15: status value alarm high limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		if(c403StatusDefinition->fLnaPowerInputAlarmHighLimit > X2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerInputAlarmHighLimit = X2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
		}
		
		if(c403StatusDefinition->fLnaPowerInputAlarmHighLimit < X1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerInputAlarmHighLimit = X1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																							(float)(Y1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																							(float)(X2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																							(float)(Y2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																							c403StatusDefinition->fLnaPowerInputAlarmHighLimit ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue;// + FLOAT_ADJUST ;
		cxStatusAlarmHighLimitForPowerInputLna.value			= 0;
		cxStatusAlarmHighLimitForPowerInputLna.byte[0]			= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForPowerInputLna.value			= ( cxStatusAlarmHighLimitForPowerInputLna.value << DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_LNA ) & 0x000000000000FF00; /* bits  8-15*/
		cRPDO_403.data.bytes[1]									= (uint8_t)(fxValue.fValue);
		
		/* Bit 16-23: status value alarm low limit for power output on LNA section, within the range of -10 dBm to 0 dBm, the resolution is determined by the bit range 0..255. */
		if(c403StatusDefinition->fLnaPowerOutputAlarmLowLimit > X2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerOutputAlarmLowLimit = X2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
		}
		
		if(c403StatusDefinition->fLnaPowerOutputAlarmLowLimit < X1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerOutputAlarmLowLimit = X1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																							(float)(Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																							(float)(X2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																							(float)(Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																							c403StatusDefinition->fLnaPowerOutputAlarmLowLimit ,  coerce );
		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmLowLimitForPowerOutputLna.value			= 0;
		cxStatusAlarmLowLimitForPowerOutputLna.byte[0]			= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForPowerOutputLna.value			= ( cxStatusAlarmLowLimitForPowerOutputLna.value << DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_LNA ) & 0x0000000000FF0000; /* 16-23 */
		cRPDO_403.data.bytes[2]									= (uint8_t)(fxValue.fValue);
		
		

		/* Bit 24-31: status value alarm high limit for power output on LNA section, within the range of -10 dBm to 0 dBm, the resolution is determined by the bit range 0..255 */
		if(c403StatusDefinition->fLnaPowerOutputAlarmHighLimit > X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerOutputAlarmHighLimit = X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
		}
		
		if(c403StatusDefinition->fLnaPowerOutputAlarmHighLimit < X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA )
		{
			c403StatusDefinition->fLnaPowerOutputAlarmHighLimit = X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																							(float)(Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																							(float)(X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																							(float)(Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																							c403StatusDefinition->fLnaPowerOutputAlarmHighLimit ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmHighLimitForPowerOutputLna.value			= 0;
		cxStatusAlarmHighLimitForPowerOutputLna.byte[0]			= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForPowerOutputLna.value			= ( cxStatusAlarmHighLimitForPowerOutputLna.value << DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_LNA ) & 0x00000000FF000000; /*24-31*/
		cRPDO_403.data.bytes[3]									= (uint8_t)(fxValue.fValue);
		
		/* Bit 32-39: status value alarm low limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		if(c403StatusDefinition->fBoosterPowerInputAlarmLowLimit > X2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerInputAlarmLowLimit = X2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		if(c403StatusDefinition->fBoosterPowerInputAlarmLowLimit < X1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerInputAlarmLowLimit = X1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																							(float)(Y1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																							(float)(X2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																							(float)(Y2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																							c403StatusDefinition->fBoosterPowerInputAlarmLowLimit ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmLowLimitForPowerInputBooster.value			= 0;
		cxStatusAlarmLowLimitForPowerInputBooster.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForPowerInputBooster.value			= ( cxStatusAlarmLowLimitForPowerInputBooster.value << DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER ) & 0x000000FF00000000; /*32-39*/
		cRPDO_403.data.bytes[4]									= (uint8_t)(fxValue.fValue);
		
		/*Bit 40-47: status value alarm high limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		if(c403StatusDefinition->fBoosterPowerInputAlarmHighLimit > X2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerInputAlarmHighLimit = X2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		if(c403StatusDefinition->fBoosterPowerInputAlarmHighLimit < X1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerInputAlarmHighLimit = X1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																							(float)(Y1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																							(float)(X2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																							(float)(Y2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																							c403StatusDefinition->fBoosterPowerInputAlarmHighLimit ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue;// + FLOAT_ADJUST ;
		cxStatusAlarmHighLimitForPowerInputBooster.value		= 0;
		cxStatusAlarmHighLimitForPowerInputBooster.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForPowerInputBooster.value		= ( cxStatusAlarmHighLimitForPowerInputBooster.value << DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER ) & 0x0000FF0000000000; /*40-47*/
		cRPDO_403.data.bytes[5]									= (uint8_t)(fxValue.fValue);
		
		/*Bit 48-55: status value alarm low limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255.  */
		if(c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit > X2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit = X2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		if(c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit < X1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit = X1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																							(float)(Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																							(float)(X2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																							(float)(Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																							c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit ,  coerce );

		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmLowLimitForPowerOutputBooster.value		= 0;
		cxStatusAlarmLowLimitForPowerOutputBooster.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmLowLimitForPowerOutputBooster.value		= ( cxStatusAlarmLowLimitForPowerOutputBooster.value << DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER ) & 0x00FF000000000000; /*48-55*/
		cRPDO_403.data.bytes[6]									= (uint8_t)(fxValue.fValue);


		/*Bit 56-63: status value alarm high limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255. */
		if(c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit > X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit = X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		if(c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit < X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER )
		{
			c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit = X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
		}
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																							(float)(Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																							(float)(X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																							(float)(Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																							c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit ,  coerce );
																							
		fxValue.fValue                                          = fxValue.fValue ;//+ FLOAT_ADJUST ;
		cxStatusAlarmHighLimitForPowerOutputBooster.value		= 0;
		cxStatusAlarmHighLimitForPowerOutputBooster.byte[0]		= (uint8_t)(fxValue.fValue);
		cxStatusAlarmHighLimitForPowerOutputBooster.value		= ( cxStatusAlarmHighLimitForPowerOutputBooster.value << DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER ) & 0x00FF000000000000; /*Bit 56-63*/
		cRPDO_403.data.bytes[7]									= (uint8_t)(fxValue.fValue);
		
		


	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	
	return eMpbError;
	
	
}
/*-----------------------------------------------------------------------------*/


eMpbError_t eMpbCan403Decode( c403StatusDefinition_t *c403StatusDefinition )
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
	mpb_coerced_t coerce = coerced;
	
	if(c403StatusDefinition != NULL)
	{
		
		
		/* Bit 0-7: status value alarm low limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		cxStatusAlarmLowLimitForPowerInputLna.value							= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fLnaPowerInputAlarmLowLimit					= (float)(cxStatusAlarmLowLimitForPowerInputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																										(float)(X1_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																										(float)(Y2_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																										(float)(X2_ALARM_LOW_LIMIT_POWER_INPUT_LNA),
																										c403StatusDefinition->fLnaPowerInputAlarmLowLimit ,  coerce );
		
		fxValue.fValue														= fxValue.fValue + 0.5;
		c403StatusDefinition->fLnaPowerInputAlarmLowLimit					= fxValue.fValue;
		
		/*Bit 8-15: status value alarm high limit for power input on LNA section, within the range of -50 dBm to -40 dBm, resolution determined by the bit range value 0..255 */
		cxStatusAlarmHighLimitForPowerInputLna.value				= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fLnaPowerInputAlarmHighLimit			= (float)(cxStatusAlarmHighLimitForPowerInputLna.byte[0]);
		
		fxValue.fValue												= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																								(float)(X1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																								(float)(Y2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																								(float)(X2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA),
																								c403StatusDefinition->fLnaPowerInputAlarmHighLimit ,  coerce );
		
		fxValue.fValue												= fxValue.fValue + 0.5;
		c403StatusDefinition->fLnaPowerInputAlarmHighLimit			= fxValue.fValue;
		
		/* Bit 16-23: status value alarm low limit for power output on LNA section, within the range of -10 dBm to 0 dBm, the resolution is determined by the bit range 0..255. */
		cxStatusAlarmLowLimitForPowerOutputLna.value						= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fLnaPowerOutputAlarmLowLimit			= (float)(cxStatusAlarmLowLimitForPowerOutputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																										(float)(X1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																										(float)(Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																										(float)(X2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA),
																										c403StatusDefinition->fLnaPowerOutputAlarmLowLimit ,  coerce );
		
		fxValue.fValue												= fxValue.fValue + 0.5;
		c403StatusDefinition->fLnaPowerOutputAlarmLowLimit			= fxValue.fValue;
		
		/* Bit 24-31: status value alarm high limit for power output on LNA section, within the range of -10 dBm to 0 dBm, the resolution is determined by the bit range 0..255 */
		cxStatusAlarmHighLimitForPowerOutputLna.value						= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_LNA) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fLnaPowerOutputAlarmHighLimit					= (float)(cxStatusAlarmHighLimitForPowerOutputLna.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																										(float)(X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																										(float)(Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																										(float)(X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA),
																										c403StatusDefinition->fLnaPowerOutputAlarmHighLimit ,  coerce );
		fxValue.fValue														= fxValue.fValue + 0.5;
		c403StatusDefinition->fLnaPowerOutputAlarmHighLimit					= fxValue.fValue;
		
		
		/* Bit 32-39: status value alarm low limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		cxStatusAlarmLowLimitForPowerInputBooster.value						= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fBoosterPowerInputAlarmLowLimit   			= (float)(cxStatusAlarmLowLimitForPowerInputBooster.byte[0]);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																										(float)(X1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																										(float)(Y2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																										(float)(X2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER),
																										c403StatusDefinition->fBoosterPowerInputAlarmLowLimit ,  coerce );
		fxValue.fValue														= fxValue.fValue + 0.5;
		c403StatusDefinition->fBoosterPowerInputAlarmLowLimit				= fxValue.fValue;
		
		/*Bit 40-47: status value alarm high limit for power input on Booster section, within the range of -10 dBm to +6 dBm, resolution determined by the bit range value 0..255. (to inform 1st supplier) */
		cxStatusAlarmHighLimitForPowerInputBooster.value						= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fBoosterPowerInputAlarmHighLimit			= (float)(cxStatusAlarmHighLimitForPowerInputBooster.byte[0]);
		
		fxValue.fValue															= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																											(float)(X1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																											(float)(Y2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																											(float)(X2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER),
																											c403StatusDefinition->fBoosterPowerInputAlarmHighLimit ,  coerce );
		fxValue.fValue													= fxValue.fValue + 0.5;
		c403StatusDefinition->fBoosterPowerInputAlarmHighLimit			= fxValue.fValue;
		
		/*Bit 48-55: status value alarm low limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255.  */
		cxStatusAlarmLowLimitForPowerOutputBooster.value						= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit					= (float)(cxStatusAlarmLowLimitForPowerOutputBooster.byte[0]);
		
		fxValue.fValue															= mpb_math_flinear_approx(  (float)(Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(X1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(X2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER),
																											c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit ,  coerce );
																											
		fxValue.fValue														= fxValue.fValue + 0.5;
		c403StatusDefinition->fBoosterPowerOutputAlarmLowLimit			= fxValue.fValue;
		
		
		
		/*Bit 56-63: status value alarm high limit for power output on Booster section, within the range of -30 dBm to +36 dBm, the resolution is determined by the bit range 0..255. */
		cxStatusAlarmHighLimitForPowerOutputBooster.value						= ( cRPDO_403.data.value >> DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER) & 0x00000000000000FF; /* bits 0-7 */
		c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit			= (float)(cxStatusAlarmHighLimitForPowerOutputBooster.byte[0]);

		fxValue.fValue															= mpb_math_flinear_approx(  (float)(Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																											(float)(X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER),
																											c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit ,  coerce );
		fxValue.fValue													= fxValue.fValue + 0.5;
		c403StatusDefinition->fBoosterPowerOutputAlarmHighLimit			= fxValue.fValue;
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	return eMpbError;
	
}
/*------------------------------------------------------------*/



