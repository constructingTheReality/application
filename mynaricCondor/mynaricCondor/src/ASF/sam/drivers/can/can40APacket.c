#include "can40APacket.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_40A;

/*---------------------------------------------------------------------------*/

void vInit40ACanImage( void )
{
	cRPDO_40A.data.value = 0;
	cRPDO_40A.id = 0x40A;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan40A( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_40A, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan40A( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_40A, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan40AEncode( c40AStatusDefinition_t *c40AStatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxBoosterDriver2CurrentLowAlarmLimit;
	BytesUnion	cxBoosterDriver2CurrentHighAlarmLimit;
	BytesUnion	cxBoosterDriver3CurrentLowAlarmLimit;
	BytesUnion	cxBoosterDriver3CurrentHighAlarmLimit;
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c40AStatusDefinition != NULL)
	{
		
		/* Bit 0-15 */
		if(c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit > X2_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit = X2_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		if(c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit < X1_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit = X1_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																							c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit ,  coerce );				
		cxBoosterDriver2CurrentLowAlarmLimit.value			= 0;
		cxBoosterDriver2CurrentLowAlarmLimit.s0				= (uint16_t)(fxValue.fValue);
		cxBoosterDriver2CurrentLowAlarmLimit.value			= ( cxBoosterDriver2CurrentLowAlarmLimit.value << DEF_CAN_40A_BOOSTER_DRIVER2_CURRENT_LOW_ALARM ) & 0x000000000000FFFF; 
		cRPDO_40A.data.bytes[0]								= cxBoosterDriver2CurrentLowAlarmLimit.byte[0];
		cRPDO_40A.data.bytes[1]								= cxBoosterDriver2CurrentLowAlarmLimit.byte[1];
		
		/* Bit 16-31 */
		if(c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit > X2_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit = X2_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		if(c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit < X1_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit = X1_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																							c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit ,  coerce );				
		cxBoosterDriver2CurrentHighAlarmLimit.value			= 0;
		cxBoosterDriver2CurrentHighAlarmLimit.s0			= (uint16_t)(fxValue.fValue);
		cxBoosterDriver2CurrentHighAlarmLimit.value			= ( cxBoosterDriver2CurrentHighAlarmLimit.value << DEF_CAN_40A_BOOSTER_DRIVER2_CURRENT_HIGH_ALARM ) & 0x00000000FFFF0000; 
		cRPDO_40A.data.bytes[2]								= cxBoosterDriver2CurrentHighAlarmLimit.byte[2];
		cRPDO_40A.data.bytes[3]								= cxBoosterDriver2CurrentHighAlarmLimit.byte[3];
		
		/* Bit 32-47 */
		if(c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit > X2_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit = X2_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		if(c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit < X1_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit = X1_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																							c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit ,  coerce );
		cxBoosterDriver3CurrentLowAlarmLimit.value			= 0;
		cxBoosterDriver3CurrentLowAlarmLimit.s0			= (uint16_t)(fxValue.fValue);
		cxBoosterDriver3CurrentLowAlarmLimit.value			= ( cxBoosterDriver3CurrentLowAlarmLimit.value << DEF_CAN_40A_BOOSTER_DRIVER3_CURRENT_LOW_ALARM ) & 0x0000FFFF00000000;
		cRPDO_40A.data.bytes[4]								= cxBoosterDriver3CurrentLowAlarmLimit.byte[4];
		cRPDO_40A.data.bytes[5]								= cxBoosterDriver3CurrentLowAlarmLimit.byte[5];		

		/* Bit 48-63 */
		if(c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit > X2_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit = X2_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		if(c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit < X1_BOOSTERM_40A_LIMIT_CURRENT )
		{
			c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit = X1_BOOSTERM_40A_LIMIT_CURRENT;
		}
		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																							(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																							c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit ,  coerce );
		cxBoosterDriver3CurrentHighAlarmLimit.value			= 0;
		cxBoosterDriver3CurrentHighAlarmLimit.s0			= (uint16_t)(fxValue.fValue);
		cxBoosterDriver3CurrentHighAlarmLimit.value			= ( cxBoosterDriver3CurrentHighAlarmLimit.value << DEF_CAN_40A_BOOSTER_DRIVER3_CURRENT_HIGH_ALARM ) & 0xFFFF000000000000;
		cRPDO_40A.data.bytes[6]								= cxBoosterDriver3CurrentHighAlarmLimit.byte[6];
		cRPDO_40A.data.bytes[7]								= cxBoosterDriver3CurrentHighAlarmLimit.byte[7];
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}




eMpbError_t eMpbCan40ADecode( c40AStatusDefinition_t *c40AStatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxBoosterDriver2CurrentLowAlarmLimit;
	BytesUnion	cxBoosterDriver2CurrentHighAlarmLimit;
	BytesUnion	cxBoosterDriver3CurrentLowAlarmLimit;
	BytesUnion	cxBoosterDriver3CurrentHighAlarmLimit;
	
	
	
	floatUnion  fxValue;
	mpb_coerced_t coerce = coerced;


	if(c40AStatusDefinition != NULL)
	{
		
		/* Bit 0-15 */
		cxBoosterDriver2CurrentLowAlarmLimit.value							= ( cRPDO_40A.data.value >> DEF_CAN_40A_BOOSTER_DRIVER2_CURRENT_LOW_ALARM) & 0x000000000000FFFF; 
		c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit			= (float)(cxBoosterDriver2CurrentLowAlarmLimit.s0);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																										c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit ,  coerce );
		
		c40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit				= fxValue.fValue;
		
		/* Bit 16-31 */
		cxBoosterDriver2CurrentHighAlarmLimit.value							= ( cRPDO_40A.data.value >> DEF_CAN_40A_BOOSTER_DRIVER2_CURRENT_HIGH_ALARM) & 0x000000000000FFFF;
		c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit			= (float)(cxBoosterDriver2CurrentHighAlarmLimit.s0);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																										c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit ,  coerce );
		
		c40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit				= fxValue.fValue;

		/* Bit 32-47 */
		cxBoosterDriver3CurrentLowAlarmLimit.value							= ( cRPDO_40A.data.value >> DEF_CAN_40A_BOOSTER_DRIVER3_CURRENT_LOW_ALARM) & 0x000000000000FFFF;
		c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit			= (float)(cxBoosterDriver3CurrentLowAlarmLimit.s0);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																										c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit ,  coerce );
		
		c40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit				= fxValue.fValue;


		/* Bit 48-63 */
		cxBoosterDriver3CurrentHighAlarmLimit.value							= ( cRPDO_40A.data.value >> DEF_CAN_40A_BOOSTER_DRIVER3_CURRENT_HIGH_ALARM) & 0x000000000000FFFF;
		c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit			= (float)(cxBoosterDriver3CurrentHighAlarmLimit.s0);
		
		fxValue.fValue														= mpb_math_flinear_approx(  (float)(Y1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X1_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(Y2_BOOSTERM_40A_LIMIT_CURRENT),
																										(float)(X2_BOOSTERM_40A_LIMIT_CURRENT),
																										c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit ,  coerce );
		
		c40AStatusDefinition->fBoosterDriver3CurrentHighAlarmLimit			= fxValue.fValue;

		
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	


	
	


	
}

