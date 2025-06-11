
#include "can406Packet.h"

#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_406;

/*---------------------------------------------------------------------------*/

void vInit406CanImage( void )
{
	cRPDO_406.data.value = 0;
	cRPDO_406.id = 0x406;
	

}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan406( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_406, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan406( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_406, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
/*------------------------------------------------------------*/
eMpbError_t eMpbCan406Decode( c406PacketControlDefinition_t *c406PacketControlDefinition )
{
	
	BytesUnion ValueSetCurrentOnLaserPump1OnBooster;
	BytesUnion ValueSetCurrentOnLaserPump2OnBooster;
	BytesUnion ValueSetCurrentOnLaserPump3OnBooster;
	BytesUnion ValueSetCurrentOnLaserPumpOnLNA;
	BytesUnion ValueForRangeBoosterOpticalPowerOutput;
	eMpbError_t eMpbError = eSuccess;
	floatUnion  fxValue;
	//mpb_coerced_t coerce = not_coerced;
	BytesUnion ValueReset;
	
	
	if(c406PacketControlDefinition != NULL)
	{
		
		/* BIT 0..7  Settings */
		c406PacketControlDefinition->Status_406_Register.ucStatus_406_RegisterGlobalValue	= cRPDO_406.data.byte[0] ;
		
		
		/*Bit 8-17: Booster CURRENT control driver 1, Bit 8-17: Value 0 1023 = 0% to 100% */
		ValueSetCurrentOnLaserPump1OnBooster.value							= 0;
		ValueSetCurrentOnLaserPump1OnBooster.value							= ( cRPDO_406.data.value >> DEF_CAN_0406_LASER_PUMP1_IN_BOOSTER) & 0x00000000000003FF; // bits 8-17
		
		
		if(ValueSetCurrentOnLaserPump1OnBooster.s0 > X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump1OnBooster.s0 = X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(ValueSetCurrentOnLaserPump1OnBooster.s0 < X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump1OnBooster.s0 = X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		c406PacketControlDefinition->fSetCurrentOnLaserPump1OnBoosterInAcc	=  (float)(ValueSetCurrentOnLaserPump1OnBooster.s0);
		
		/*fxValue.fValue													= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE ),
																									(float)(Y1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																									(float)(X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE ),
																									(float)(Y2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																									c406PacketControlDefinition->fSetCurrentOnLaserPump1OnBoosterInAcc,  coerce );
		
		c406PacketControlDefinition->fSetCurrentOnLaserPump1OnBoosterInAcc	= fxValue.fValue - FLOAT_ADJUST;*/
		

		/*Bit 18-27 Booster CURRENT control driver 2, Bit 18-27: Value 0 1023 = 0% to 100%*/
		ValueSetCurrentOnLaserPump2OnBooster.value						= ( cRPDO_406.data.value >> DEF_CAN_0406_LASER_PUMP2_IN_BOOSTER) & 0x00000000000003FF; // bits 18-27
		
		
		if(ValueSetCurrentOnLaserPump2OnBooster.s0 > X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump2OnBooster.s0 = X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if( ValueSetCurrentOnLaserPump2OnBooster.s0 < X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump2OnBooster.s0 = X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		c406PacketControlDefinition->fSetCurrentOnLaserPump2OnBoosterInAcc  = (float)(ValueSetCurrentOnLaserPump2OnBooster.s0);
		
	/*	fxValue.fValue													= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE ),
																									(float)(Y1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																									(float)(X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE ),
																									(float)(Y2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																									c406PacketControlDefinition->fSetCurrentOnLaserPump2OnBoosterInAcc,  coerce );
		c406PacketControlDefinition->fSetCurrentOnLaserPump2OnBoosterInAcc	= fxValue.fValue- FLOAT_ADJUST;*/
		
		
		
		/* Booster CURRENT control driver 3, Bit 28-37: Value 0 1023 = 0% to 100%*/
		ValueSetCurrentOnLaserPump3OnBooster.value						= ( cRPDO_406.data.value >> DEF_CAN_0406_LASER_PUMP3_IN_BOOSTER) & 0x00000000000003FF; // bits 28-37
		
		
		if(ValueSetCurrentOnLaserPump3OnBooster.s0 > X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump3OnBooster.s0 = X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(ValueSetCurrentOnLaserPump3OnBooster.s0 < X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump3OnBooster.s0 = X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc  = (float)(ValueSetCurrentOnLaserPump3OnBooster.s0);
		
		/*fxValue.fValue													= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE ),
																									(float)(Y1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																									(float)(X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE ),
																									(float)(Y2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																									c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc,  coerce );
		
		

		c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc	= fxValue.fValue- FLOAT_ADJUST;*/
		
		
		
		
		/* Lna CURRENT control, Bit 38-47: Value 0 1023 = 0% to 100%*/
		ValueSetCurrentOnLaserPumpOnLNA.value						= ( cRPDO_406.data.value >> DEF_CAN_0406_LASER_PUMP_IN_LNA) & 0x00000000000003FF; // bits 38-47
		
		
		
		if(ValueSetCurrentOnLaserPumpOnLNA.s0 > X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPumpOnLNA.s0 = X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
			
		if(ValueSetCurrentOnLaserPumpOnLNA.s0 < X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPumpOnLNA.s0 = X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		c406PacketControlDefinition->fSetGeneralSetpointOnLNA		= (float)( ValueSetCurrentOnLaserPumpOnLNA.s0);
		
		/*	fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE ),
																							(float)(Y1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																							(float)(X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE ),
																							(float)(Y2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																							c406PacketControlDefinition->fSetGeneralSetpointOnLNA ,  coerce );
		
		c406PacketControlDefinition->fSetGeneralSetpointOnLNA			= fxValue.fValue- FLOAT_ADJUST;*/
		
		
		
		
		/*Bit 48-57: Set Booster Power in APC mode,  Value 0 1023 = +16 dBm to 37.5 dBm  */
		ValueForRangeBoosterOpticalPowerOutput.value					= ( cRPDO_406.data.value >> DEF_CAN_0406_OPTICAL_POWER_RANGE_BOOSTER) & 0x00000000000003FF; // bits 48-57
		
		
		
		
			if(ValueForRangeBoosterOpticalPowerOutput.s0 > X2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE )
			{
				ValueForRangeBoosterOpticalPowerOutput.s0 = X2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE;
			}
			
			if( ValueForRangeBoosterOpticalPowerOutput.s0 < X1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE )
			{
				ValueForRangeBoosterOpticalPowerOutput.s0 = X1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE;
			}
			
			c406PacketControlDefinition->fSetSetPointPowerForBoosterInApc		= (float)(ValueForRangeBoosterOpticalPowerOutput.s0);
				//	range for setpoint : 39.8107170553 mW (16dbm)   .. 5623.4132519035 mW (37.5)
				// 
				// 0 ..1023   -> 16..37.5     y ? 0.021x + 16
				
			c406PacketControlDefinition->fSetSetPointPowerForBoosterInApc		= 0.021 * c406PacketControlDefinition->fSetSetPointPowerForBoosterInApc  + 16 ;
			 
			
		/*	fxValue.fValue												= mpb_math_flinear_approx(  (float)(X1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE ),
																									(float)(Y1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE),
																									(float)(X2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE ),
																									(float)(Y2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE),
																									c406PacketControlDefinition->fSetSetPointPowerForBoosterInApc ,  coerce );
		
		c406PacketControlDefinition->fSetSetPointPowerForBoosterInApc = fxValue.fValue- FLOAT_ADJUST;*/
		
		/* Bit 58-61: Set LNA Power in APC mode,  Value 0 15 = -15 dBm to 0 dBm  */	
	/*	ValueForRangeBoosterOpticalPowerOutput.value					= 0;		
		ValueForRangeBoosterOpticalPowerOutput.byte[0]						= ( cRPDO_406.data.value >> DEF_CAN_0406_OPTICAL_POWER_RANGE_LNA) & 0x000000000000000F; // bits 58-61
		c406PacketControlDefinition->fSetSetPointPowerForLnaInApc		= (float)(ValueForRangeBoosterOpticalPowerOutput.byte[0]);
		
		
		
			if(c406PacketControlDefinition->fSetSetPointPowerForLnaInApc > X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE )
			{
				c406PacketControlDefinition->fSetSetPointPowerForLnaInApc = X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE;
			}
			
			if(c406PacketControlDefinition->fSetSetPointPowerForLnaInApc < X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE )
			{
				c406PacketControlDefinition->fSetSetPointPowerForLnaInApc = X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE;
			}*/
			
		/*	fxValue.fValue												= mpb_math_flinear_approx(  (float)(Y1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																									(float)(X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																									(float)(Y2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																									(float)(X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																									c406PacketControlDefinition->fSetSetPointPowerForLnaInApc ,  coerce );*/
																									
	//	   c406PacketControlDefinition->fSetSetPointPowerForLnaInApc = c406PacketControlDefinition->fSetSetPointPowerForLnaInApc - X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE;
		
		//c406PacketControlDefinition->fSetSetPointPowerForLnaInApc = fxValue.fValue;


		/* Bit 62-63: 0: Reset all (electronics, Booster and LNA) 	1: Reset LNA 	2: Reset booster 	3: do nothing */	
		
		ValueReset.value										= 0;
		ValueReset.value										=  ( cRPDO_406.data.value >> DEF_CAN_0406_RESET) & 0x0000000000000003; // bits 62-63
		c406PacketControlDefinition->ucResetRequest				= ValueReset.byte[0];
	}
	else
	{
		eMpbError = eOutOfMemory;
		
	}
	
	return eMpbError;
	
	
	
}
/*-------------------------------------------------------------*/

eMpbError_t eMpbCan406Encode( c406PacketControlDefinition_t *c406PacketControlDefinition )
{
	BytesUnion		ValueSetCurrentOnLaserPump1OnBooster;
	BytesUnion		ValueSetCurrentOnLaserPump2OnBooster;
	BytesUnion		ValueSetCurrentOnLaserPump3OnBooster;
	BytesUnion		ValueReset;
	BytesUnion		ValueSetCurrentOnLaserPumpOnLNA;
	BytesUnion		ValueForRangeBoosterOpticalPowerOutput;
	eMpbError_t		eMpbError = eSuccess;
	//mpb_coerced_t	coerce = coerced;
	floatUnion		fxValue;
	//eBool_t			compare = eFalse;
	uint8_t			cResetValue = 0;
	uint8_t			ucValue = 0;
	
	if(c406PacketControlDefinition != NULL)
	{
		/* BIT 0..7  Settings */
		cRPDO_406.data.byte[0]									=  c406PacketControlDefinition->Status_406_Register.ucStatus_406_RegisterGlobalValue;

		/*Bit 8-17: Booster CURRENT control driver 1, Bit 8-17: Value 0 1023 = 0% to 100% */
		
		ValueSetCurrentOnLaserPump1OnBooster.low	= (uint32_t)c406PacketControlDefinition->fSetCurrentOnLaserPump1OnBoosterInAcc;
		
		if(ValueSetCurrentOnLaserPump1OnBooster.low > X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump1OnBooster.low = X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
				
		if(ValueSetCurrentOnLaserPump1OnBooster.low < X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump1OnBooster.low = X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		/*fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							c406PacketControlDefinition->fSetCurrentOnLaserPump1OnBoosterInAcc,  coerce );
		
		*/
		
		//ValueSetCurrentOnLaserPump1OnBooster.s0				= (uint16_t)(fxValue.fValue);
		ValueSetCurrentOnLaserPump1OnBooster.value			= ( ValueSetCurrentOnLaserPump1OnBooster.value << DEF_CAN_0406_LASER_PUMP1_IN_BOOSTER) & 0x000000000003FF00; // bits 8-17
		cRPDO_406.data.value								=  cRPDO_406.data.value & 0xFFFFFFFFFFFC00FF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueSetCurrentOnLaserPump1OnBooster.value;
		
		/*Bit 18-27 Booster CURRENT control driver 2, Bit 18-27: Value 0 1023 = 0% to 100%*/
		ValueSetCurrentOnLaserPump2OnBooster.low	= (uint32_t)c406PacketControlDefinition->fSetCurrentOnLaserPump2OnBoosterInAcc;
		
		if(ValueSetCurrentOnLaserPump2OnBooster.low > X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump2OnBooster.low = X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(ValueSetCurrentOnLaserPump2OnBooster.low < X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump2OnBooster.low = X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		/*fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(Y1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(Y2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						c406PacketControlDefinition->fSetCurrentOnLaserPump2OnBoosterInAcc,  coerce );
		*/
		//ValueSetCurrentOnLaserPump2OnBooster.s0				= (uint16_t)(fxValue.fValue);
		ValueSetCurrentOnLaserPump2OnBooster.value			= ( ValueSetCurrentOnLaserPump2OnBooster.value << DEF_CAN_0406_LASER_PUMP2_IN_BOOSTER) & 0x000000000FFC0000; // bits 18-27
		
		cRPDO_406.data.value								=  cRPDO_406.data.value & 0xFFFFFFFFF003FFFF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueSetCurrentOnLaserPump2OnBooster.value;
		
		
		
		
		
		/* Booster CURRENT control driver 3, Bit 28-37: Value 0 1023 = 0% to 100%*/
		ValueSetCurrentOnLaserPump3OnBooster.low	= (uint32_t)c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc;
		
		if(ValueSetCurrentOnLaserPump3OnBooster.low > X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump3OnBooster.low = X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(ValueSetCurrentOnLaserPump3OnBooster.low < X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPump3OnBooster.low = X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		/*fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(Y1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(Y2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc,  coerce );
		
		ValueSetCurrentOnLaserPump3OnBooster.s0				= (uint16_t)(fxValue.fValue);*/
		ValueSetCurrentOnLaserPump3OnBooster.value			= ( ValueSetCurrentOnLaserPump3OnBooster.value << DEF_CAN_0406_LASER_PUMP3_IN_BOOSTER) & 0x0000003FF0000000; // bits 28-37
		cRPDO_406.data.value								=  cRPDO_406.data.value & 0xFFFFFFC00FFFFFFF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueSetCurrentOnLaserPump3OnBooster.value;
		




		/* Lna CURRENT control, Bit 38-47: Value 0 1023 = 0% to 100%*/
		ValueSetCurrentOnLaserPumpOnLNA.low	= (uint32_t)c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc;
		
		if(ValueSetCurrentOnLaserPumpOnLNA.low > X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPumpOnLNA.low = X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE;
		}
		
		if(ValueSetCurrentOnLaserPumpOnLNA.low < X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPumpOnLNA.low = X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE;
		}
				
	/*	fxValue.fValue									= mpb_math_flinear_approx(  (float)(X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																					(float)(Y1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																					(float)(X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																					(float)(Y2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																					c406PacketControlDefinition->fSetGeneralSetpointOnLNA ,  coerce );				
		ValueSetCurrentOnLaserPumpOnLNA.value = 0;
		ValueSetCurrentOnLaserPumpOnLNA.s0					= (uint16_t)(fxValue.fValue);*/
		ValueSetCurrentOnLaserPumpOnLNA.value				= ( ValueSetCurrentOnLaserPumpOnLNA.value << DEF_CAN_0406_LASER_PUMP_IN_LNA) & 0x0000FFC000000000 ;// bits 38-47;
		
		
		cRPDO_406.data.value								= cRPDO_406.data.value  & 0xFFFF003FFFFFFFFF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueSetCurrentOnLaserPumpOnLNA.value;
		
		
		
		
		/*Bit 48-57: Set Booster Power in APC mode,  Value 0 1023 = +16 dBm to 37.5 dBm  */
		ValueForRangeBoosterOpticalPowerOutput.low	= (uint32_t)c406PacketControlDefinition->fSetCurrentOnLaserPump3OnBoosterInAcc;
		
		if(ValueSetCurrentOnLaserPumpOnLNA.low > X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPumpOnLNA.low = X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE;
		}
		
		if(ValueSetCurrentOnLaserPumpOnLNA.low < X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE )
		{
			ValueSetCurrentOnLaserPumpOnLNA.low = X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE;
		}
		/*fxValue.fValue								= mpb_math_flinear_approx(  (float)(X1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE),
																				(float)(Y1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE),
																				(float)(X2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE),
																				(float)(Y2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE),
																				c406PacketControlDefinition->fSetSetPointPowerForBoosterInApc ,  coerce );

		
		ValueForRangeBoosterOpticalPowerOutput.value = 0;
		ValueForRangeBoosterOpticalPowerOutput.s0			=  (uint16_t)(fxValue.fValue);*/
		
		ValueForRangeBoosterOpticalPowerOutput.value		= ( ValueForRangeBoosterOpticalPowerOutput.value << DEF_CAN_0406_OPTICAL_POWER_RANGE_BOOSTER)  & 0x03FF000000000000; // bits 48-57		
		cRPDO_406.data.value								= cRPDO_406.data.value  & 0xFC00FFFFFFFFFFFF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueForRangeBoosterOpticalPowerOutput.value;
		
		/* Bit 58-61: Set LNA Power in APC mode,  Value 0 15 = -15 dBm to 0 dBm  */	
		/*fxValue.fValue								= mpb_math_flinear_approx(  (float)(X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																				(float)(Y1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																				(float)(X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																				(float)(Y2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE),
																				c406PacketControlDefinition->fSetSetPointPowerForLnaInApc ,  coerce );
								*/												
			
		
		/*if(c406PacketControlDefinition->fSetSetPointPowerForLnaInApc < X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE)																			
		{
			c406PacketControlDefinition->fSetSetPointPowerForLnaInApc = X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE;																	
		}
		
		if(c406PacketControlDefinition->fSetSetPointPowerForLnaInApc > X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE)
		{
			c406PacketControlDefinition->fSetSetPointPowerForLnaInApc = X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE;
		}

		ucValue =										(uint8_t)c406PacketControlDefinition->fSetSetPointPowerForLnaInApc;
		
		ValueForRangeBoosterOpticalPowerOutput.value = 0;
		ValueForRangeBoosterOpticalPowerOutput.byte[0]		= ucValue; // (uint16_t)(fxValue.fValue);
		
		ValueForRangeBoosterOpticalPowerOutput.value		= ( ValueForRangeBoosterOpticalPowerOutput.value << DEF_CAN_0406_OPTICAL_POWER_RANGE_LNA)  & 0x3C00000000000000; // bits 58-61
		cRPDO_406.data.value								= cRPDO_406.data.value  & 0xC3FFFFFFFFFFFFFF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueForRangeBoosterOpticalPowerOutput.value;*/
		
		/* Bit 62-63: 0: Reset all (electronics, Booster and LNA) 	1: Reset LNA 	2: Reset booster 	3: do nothing */	
		ValueReset.value									= 0;
		ValueReset.byte[0]									= c406PacketControlDefinition->ucResetRequest;
		ValueReset.value									= ( ValueReset.value << DEF_CAN_0406_RESET ) & 0xC000000000000000; // bits 32-35
		cRPDO_406.data.value								=  cRPDO_406.data.value & 0x3FFFFFFFFFFFFFFF;
		cRPDO_406.data.value								= cRPDO_406.data.value |  ValueReset.value;
	}
	else
	{
		eMpbError = eOutOfMemory;
		
	}
	
	return eMpbError;
	
	
}
