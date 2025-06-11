
#include "can407Packet.h"

#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_407;

/*---------------------------------------------------------------------------*/

void vInit407CanImage( void )
{
	cRPDO_407.data.value = 0;
	cRPDO_407.id = 0x407;
}
/*------------------------------------------------------*/
eMpbError_t getCan407( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_407, size );
	return eSuccess;
}
/*------------------------------------------------------*/
eMpbError_t setCan407( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_407, pCan, size );
	return eSuccess;
}


/*------------------------------------------------------------*/
eMpbError_t eMpbCan407Decode( c407PacketControlDefinition_t *c407PacketControlDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion      ValueSetNvm;
	floatUnion  fxValue;
	mpb_coerced_t coerce = not_coerced;
	BytesUnion BoosterCurrent2LowAlarmLimit;
	BytesUnion BoosterCurrent2HighAlarmLimit;
	BytesUnion BoosterCurrent3LowAlarmLimit;
	BytesUnion BoosterCurrent3HighAlarmLimit;
	BytesUnion LnaSetPowerInApcMode;


	
	if(c407PacketControlDefinition != NULL)
	{
		
		/* bit 0. 1 (1): save * 0: no action */
		ValueSetNvm.value									= 0;
		ValueSetNvm.value									= ( cRPDO_407.data.value >> DEF_CAN_0407_SET_NVM) & 0x0000000000000001; // bit 0		
		c407PacketControlDefinition->bSaveSettingsInNvm		= ( ValueSetNvm.byte[0] == 1 )? eTrue : eFalse;
		
		/*bit 1..10 (10). Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		BoosterCurrent2LowAlarmLimit.value					= 0;
		BoosterCurrent2LowAlarmLimit.value					= ( cRPDO_407.data.value >> DEF_CAN_0407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT) & 0x00000000000003FF; // bits 1-10
		
		if(BoosterCurrent2LowAlarmLimit.s0 > DEF_407_MAX_VALUE)
		{
			BoosterCurrent2LowAlarmLimit.s0 = DEF_407_MAX_VALUE;
		}
		
		c407PacketControlDefinition->fBoosterCurrent2LowAlarmLimit  = (float)BoosterCurrent2LowAlarmLimit.low;
				
		fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT ),
																						(float)(Y1_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT),
																						(float)(X2_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT ),
																						(float)(Y2_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT),
																						c407PacketControlDefinition->fBoosterCurrent2LowAlarmLimit ,  coerce );
					
		c407PacketControlDefinition->fBoosterCurrent2LowAlarmLimit	= fxValue.fValue - FLOAT_ADJUST;
		
		
		/*bit 11..20 (10). Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		BoosterCurrent2HighAlarmLimit.value					= 0;
		BoosterCurrent2HighAlarmLimit.value					= ( cRPDO_407.data.value >> DEF_CAN_0407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT) & 0x00000000000003FF; // bits 11-20
		
		if(BoosterCurrent2HighAlarmLimit.s0 > DEF_407_MAX_VALUE)
		{
			BoosterCurrent2HighAlarmLimit.s0 = DEF_407_MAX_VALUE;
		}		
		
		c407PacketControlDefinition->fBoosterCurrent2HighAlarmLimit  = (float)BoosterCurrent2HighAlarmLimit.low;

		fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT ),
																						(float)(Y1_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT),
																						(float)(X2_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT ),
																						(float)(Y2_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT),
																						c407PacketControlDefinition->fBoosterCurrent2HighAlarmLimit ,  coerce );
		
		c407PacketControlDefinition->fBoosterCurrent2HighAlarmLimit	= fxValue.fValue- FLOAT_ADJUST;
		
				
		
		/*bit 21..30 (10) Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		BoosterCurrent3LowAlarmLimit.value					= 0;
		BoosterCurrent3LowAlarmLimit.value					= ( cRPDO_407.data.value >> DEF_CAN_0407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT) & 0x00000000000003FF; // bits 21-30
		
		if(BoosterCurrent3LowAlarmLimit.s0 > DEF_407_MAX_VALUE)
		{
			BoosterCurrent3LowAlarmLimit.s0 = DEF_407_MAX_VALUE;
		}
		
		c407PacketControlDefinition->fBoosterCurrent3LowAlarmLimit  = (float)BoosterCurrent3LowAlarmLimit.low;		
		
		fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT ),
																						(float)(Y1_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT),
																						(float)(X2_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT ),
																						(float)(Y2_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT),
																						c407PacketControlDefinition->fBoosterCurrent3LowAlarmLimit ,  coerce );
		
		c407PacketControlDefinition->fBoosterCurrent3LowAlarmLimit	= fxValue.fValue- FLOAT_ADJUST;
		
				
		/*bit 31..40 (10) Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		
		BoosterCurrent3HighAlarmLimit.value					= 0;
		BoosterCurrent3HighAlarmLimit.value					= ( cRPDO_407.data.value >> DEF_CAN_0407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT) & 0x00000000000003FF; // bits 31-40
		
		if(BoosterCurrent3HighAlarmLimit.s0 > DEF_407_MAX_VALUE)
		{
			BoosterCurrent3HighAlarmLimit.s0 = DEF_407_MAX_VALUE;
		}
		
		c407PacketControlDefinition->fBoosterCurrent3HighAlarmLimit  = (float)BoosterCurrent3HighAlarmLimit.low;

		fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT ),
																						(float)(Y1_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT),
																						(float)(X2_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT ),
																						(float)(Y2_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT),
																					c407PacketControlDefinition->fBoosterCurrent3HighAlarmLimit ,  coerce );
		
		c407PacketControlDefinition->fBoosterCurrent3HighAlarmLimit	= fxValue.fValue- FLOAT_ADJUST;
		
		
		/*bit 41..50 Value 0 1023 = -15 dBm to 0 dBm 	resolution 0.015 dB   */
		
		LnaSetPowerInApcMode.value					= 0;
		LnaSetPowerInApcMode.value					= ( cRPDO_407.data.value >> DEF_CAN_0407_LNA_POWER_IN_APC) & 0x00000000000003FF; // bits 41-50
		
		if(LnaSetPowerInApcMode.s0 > DEF_407_MAX_VALUE)
		{
			LnaSetPowerInApcMode.s0 = DEF_407_MAX_VALUE;
		}
		
		c407PacketControlDefinition->fLnaSetPowerInApcMode  = (float)LnaSetPowerInApcMode.low;

		fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_407_LNA_POWER_APC ),
																						(float)(Y1_407_LNA_POWER_APC),
																						(float)(X2_407_LNA_POWER_APC ),
																						(float)(Y2_407_LNA_POWER_APC),
																					c407PacketControlDefinition->fLnaSetPowerInApcMode ,  coerce );
		
		c407PacketControlDefinition->fLnaSetPowerInApcMode	= fxValue.fValue- FLOAT_ADJUST;
				
	}
	else
	{
		eMpbError = eOutOfMemory;
		
	}
	
	return eMpbError;
	
	
	
}
/*-------------------------------------------------------------*/

eMpbError_t eMpbCan407Encode( c407PacketControlDefinition_t *c407PacketControlDefinition )
{
	eMpbError_t		eMpbError = eSuccess;
	BytesUnion		BoosterCurrent2LowAlarmLimit;
	BytesUnion		BoosterCurrent2HighAlarmLimit;
	BytesUnion		BoosterCurrent3LowAlarmLimit;
	BytesUnion		BoosterCurrent3HighAlarmLimit;	
	BytesUnion		LnaSetPowerInApcMode;	
	

	
	if(c407PacketControlDefinition != NULL)
	{ 
		cRPDO_407.data.value = 0;
		/* bit 0. 1 (1): save * 0: no action */
		if( c407PacketControlDefinition->bSaveSettingsInNvm == eTrue )
		{			
			cRPDO_407.data.byte[0] = 0x01;
		}
				
		/*bit 1..10 (10). Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		if( c407PacketControlDefinition->fBoosterCurrent2LowAlarmLimit > DEF_407_MAX_VALUE)
		{
			c407PacketControlDefinition->fBoosterCurrent2LowAlarmLimit = DEF_407_MAX_VALUE;
		}
		BoosterCurrent2LowAlarmLimit.low	= (uint32_t)c407PacketControlDefinition->fBoosterCurrent2LowAlarmLimit;
		
		BoosterCurrent2LowAlarmLimit.value			= ( BoosterCurrent2LowAlarmLimit.value << DEF_CAN_0407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT) & 0x00000000000007FE; //bit 1..10 
		cRPDO_407.data.value						=  cRPDO_407.data.value & 0xFFFFFFFFFFFFF801;
		cRPDO_407.data.value						= cRPDO_407.data.value |  BoosterCurrent2LowAlarmLimit.value;
		
		/*bit 11..20 (10). Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		if( c407PacketControlDefinition->fBoosterCurrent2HighAlarmLimit > DEF_407_MAX_VALUE)
		{
			c407PacketControlDefinition->fBoosterCurrent2HighAlarmLimit = DEF_407_MAX_VALUE;
		}
		BoosterCurrent2HighAlarmLimit.low	= (uint32_t)c407PacketControlDefinition->fBoosterCurrent2HighAlarmLimit;
		
		BoosterCurrent2HighAlarmLimit.value			= ( BoosterCurrent2HighAlarmLimit.value << DEF_CAN_0407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT) & 0x00000000001FF800; //bit 11..20
		cRPDO_407.data.value						=  cRPDO_407.data.value & 0xFFFFFFFFFFE007FF;
		cRPDO_407.data.value						= cRPDO_407.data.value |  BoosterCurrent2HighAlarmLimit.value;		
		
		/*bit 21..30 (10) Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		if( c407PacketControlDefinition->fBoosterCurrent3LowAlarmLimit > DEF_407_MAX_VALUE)
		{
			c407PacketControlDefinition->fBoosterCurrent3LowAlarmLimit = DEF_407_MAX_VALUE;
		}
		BoosterCurrent3LowAlarmLimit.low	= (uint32_t)c407PacketControlDefinition->fBoosterCurrent3LowAlarmLimit;
		
		BoosterCurrent3LowAlarmLimit.value			= ( BoosterCurrent3LowAlarmLimit.value << DEF_CAN_0407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT) & 0x000000007FE00000; //bit 21..30
		cRPDO_407.data.value						=  cRPDO_407.data.value & 0xFFFFFFFF801FFFFF;
		cRPDO_407.data.value						= cRPDO_407.data.value |  BoosterCurrent3LowAlarmLimit.value;
		
		/*bit 31..40 (10) Value 0 1023 = 0% to 100% 	resolution is 0,1% */
		if( c407PacketControlDefinition->fBoosterCurrent3HighAlarmLimit > DEF_407_MAX_VALUE)
		{
			c407PacketControlDefinition->fBoosterCurrent3HighAlarmLimit = DEF_407_MAX_VALUE;
		}
		BoosterCurrent3HighAlarmLimit.low	= (uint32_t)c407PacketControlDefinition->fBoosterCurrent3HighAlarmLimit;
		
		BoosterCurrent3HighAlarmLimit.value			= ( BoosterCurrent3HighAlarmLimit.value << DEF_CAN_0407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT) & 0x000001FF80000000; //bit 31..40
		cRPDO_407.data.value						=  cRPDO_407.data.value & 0xFFFFFE007FFFFFFF;
		cRPDO_407.data.value						= cRPDO_407.data.value |  BoosterCurrent3HighAlarmLimit.value;
		
		/*bit 41..50 Value 0 1023 = -15 dBm to 0 dBm 	resolution 0.015 dB   */
		if( c407PacketControlDefinition->fLnaSetPowerInApcMode > DEF_407_MAX_VALUE)
		{
			c407PacketControlDefinition->fLnaSetPowerInApcMode = DEF_407_MAX_VALUE;
		}
		LnaSetPowerInApcMode.low					= (uint32_t)c407PacketControlDefinition->fLnaSetPowerInApcMode;
		
		LnaSetPowerInApcMode.value					= ( LnaSetPowerInApcMode.value << DEF_CAN_0407_LNA_POWER_IN_APC) & 0x0007FE0000000000; //bit 41..50
		cRPDO_407.data.value						=  cRPDO_407.data.value & 0xFFF801FFFFFFFFFF;
		cRPDO_407.data.value						= cRPDO_407.data.value |  LnaSetPowerInApcMode.value;

		
	}
	else
	{
		eMpbError = eOutOfMemory;
		
	}
	
	return eMpbError;
	
	
}

