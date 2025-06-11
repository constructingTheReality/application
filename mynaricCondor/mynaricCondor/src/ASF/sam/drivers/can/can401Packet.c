
#include "can401Packet.h"
#include "dictionaryUtils.h"

//#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_401;

/*---------------------------------------------------------------------------*/

void vInit401CanImage( void )
{
		cRPDO_401.data.value = 0;
		cRPDO_401.id = 0x401;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan401( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_401, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan401( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_401, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/

/*-------------------------------------------------------------*/

eMpbError_t eMpbCan401Decode( c401StatusDefinition_t *c401Status1Definition )
{
	
	BytesUnion cxLaserPump1CurrentOfBooster;
	BytesUnion cxLaserPump2CurrentOfBooster;
	BytesUnion cxLaserPump3CurrentOfBooster;
	BytesUnion cxLaserPump4CurrentOfLna;

	
	eMpbError_t eMpbError = eSuccess;
	uint8_t cTempValue =0;
	
	mpb_coerced_t coerce = coerced;
//	floatUnion	fxBoosterOutputOpticalPower;
	floatUnion fxValue;
	float fRecoveredFrom255 = 0.0f;
	fValue_t fValue;
	
	
	if(c401Status1Definition != NULL)
	{	
				
		/*Bit 0..15: value laser pump1 current of the Booster section.	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA */
		cxLaserPump1CurrentOfBooster.value						= ( cRPDO_401.data.value >> DEF_CAN_0401_PUMP1_CURRENT_IN_BOOSTER) & 0x000000000000FFFF;  /* bits 0-15 */

		c401Status1Definition->fLaserPump1BoosterCurrent		= (float)cxLaserPump1CurrentOfBooster.s0;
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							c401Status1Definition->fLaserPump1BoosterCurrent,  coerce );
	
		c401Status1Definition->fLaserPump1BoosterCurrent = fxValue.fValue;	
	
		/*Bit 16-31: value laser pump2 current (if such hardware is present).	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA.*/
		cxLaserPump2CurrentOfBooster.value						= ( cRPDO_401.data.value >> DEF_CAN_0401_PUMP2_CURRENT_IN_BOOSTER) & 0x000000000000FFFF; //& 0x00000000000FF600; /* bits 10-19 */		
		c401Status1Definition->fLaserPump2BoosterCurrent		= (float)cxLaserPump2CurrentOfBooster.s0;
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							c401Status1Definition->fLaserPump2BoosterCurrent,  coerce );
	
		c401Status1Definition->fLaserPump2BoosterCurrent		= fxValue.fValue;
	
		/*	Bit 32-47: value laser pump3 current (if such hardware is present).The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA. */
		cxLaserPump3CurrentOfBooster.value						= ( cRPDO_401.data.value >> DEF_CAN_0401_PUMP3_CURRENT_IN_BOOSTER) & 0x000000000000FFFF; //& 0x000000003FF00000; /* bits 20-29 */
		c401Status1Definition->fLaserPump3BoosterCurrent		= (float)cxLaserPump3CurrentOfBooster.s0;
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							c401Status1Definition->fLaserPump3BoosterCurrent,  coerce );
		c401Status1Definition->fLaserPump3BoosterCurrent		= fxValue.fValue;
	
		/*	Bit 48-63: value laser pump4 current of the LNA section.	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA. */
		cxLaserPump4CurrentOfLna.value							= ( cRPDO_401.data.value >> DEF_CAN_0401_PUMP4_CURRENT_IN_LNA ) & 0x000000000000FFFF; //& 0x000000FF60000000; 		
		c401Status1Definition->fLaserPump4LnaCurrent			= (float)cxLaserPump4CurrentOfLna.s0;
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(Y1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																							(float)(X1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																							(float)(Y2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																							(float)(X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																							c401Status1Definition->fLaserPump4LnaCurrent ,  coerce );

		c401Status1Definition->fLaserPump4LnaCurrent			= fxValue.fValue;
						
		/*
		
		
		//Bit 40-47:  for the selected input channel, the value of the booster optical input power. The resolution is determined by the specified input dBm range and the bit range 0...255.
		cxBoosterOpticalInputPower.value						= ( cRPDO_401.data.value >> DEF_CAN_0401_BOOSTER_OPTICAL_INPUT_POWER ) & 0x00000000000000FF;// & 0x0000FF0000000000; // bits 40-47 
		c401Status1Definition->fBoosterOpticalInputPower		= (float)(cxBoosterOpticalInputPower.byte[0]);
		

		fxValue.fValue										= mpb_math_flinear_approx(  (float)(Y1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							(float)(X1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							(float)(Y2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							(float)(X2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							c401Status1Definition->fBoosterOpticalInputPower,  coerce );
	
	
	   c401Status1Definition->fBoosterOpticalInputPower 		= fxValue.fValue;
	
		//Bit 48-55:  for the selected output channel, the value of the LNA optical output power. The resolution is determined by the specified output dBm range and the bit range 0...255.
		cxLnaOpticalOutputPower.value										= ( cRPDO_401.data.value >> DEF_CAN_0401_LNA_OPTICAL_OUTPUT_POWER ) & 0x00000000000000FF;// & 0x00FF000000000000; // bits 48-55 
		c401Status1Definition->fLnaOpticalOutputPower						= (float)( cxLnaOpticalOutputPower.byte[0] );
		
		fxValue.fValue													= mpb_math_flinear_approx(  (float)(Y1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																										(float)(X1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																										(float)(Y2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																										(float)(X2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																										c401Status1Definition->fLnaOpticalOutputPower,  coerce );		
	
		c401Status1Definition->fLnaOpticalOutputPower						= fxValue.fValue ;
	
	   // Bit 56-63: value of the Booster output optical power : 		Value 0..255  allocated to the range -30 dBm to +19 dBm 

		cxBoosterOutputOpticalPower.value									= ( cRPDO_401.data.value >> DEF_CAN_0401_BOOSTER_OPTICAL_OUTPUT_POWER ) & 0x00000000000000FF;// & 0xFF00000000000000; // bits 56-63 
		cTempValue															= cxBoosterOutputOpticalPower.byte[0];
		fxBoosterOutputOpticalPower.fValue									= (float)(cxBoosterOutputOpticalPower.byte[0]);
	
		

			fRecoveredFrom255												= mpb_math_flinear_approx(  (float)(Y1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																										(float)(X1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																										(float)(Y2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																										(float)(X2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																										fxBoosterOutputOpticalPower.fValue,  coerce );
		
		c401Status1Definition->fBoosterOutputOpticalPower = fRecoveredFrom255;			*/
	}
	else
	{
		eMpbError = eOutOfMemory;		
	}
	return eMpbError;
	
	
}
/*-------------------------------------------------------------*/

eMpbError_t eMpbCan401Encode( c401StatusDefinition_t *c401Status1Definition)
{
//	BytesUnion	cxInternalMountingSurfaceTemperature;
	BytesUnion	cxLaserPump1CurrentOfBooster;
	BytesUnion	cxLaserPump2CurrentOfBooster;
	BytesUnion	cxLaserPump3CurrentOfBooster;
	BytesUnion	cxLaserPump4CurrentOfLna;
	//BytesUnion	cxBoosterOpticalInputPower;
	//BytesUnion	cxLnaOpticalOutputPower;
	//BytesUnion	cxBoosterOutputOpticalPower;
	//float		fdBbmCoertedTofloat255 = 0.0f;
	//uint8_t		cBoosterValue = 0;
	//floatUnion	fxBoosterOutputOpticalPower;
	floatUnion  fxValue;
	float fCoertedTofloat255 = 0.0f;
	mpb_coerced_t coerce = coerced;
	eMpbError_t eMpbError = eSuccess;
	//uint8_t    cTempValue = SECOND_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER ;
	//eBool_t  compareforRange2 = eFalse;
	//eBool_t  compareforRange2a = eFalse;
	//eBool_t  compareforRange2b = eFalse;
	//eBool_t  compareForRange1 = eFalse;
	//eBool_t  compareforRange3 = eFalse;
	
	//compareforRange2 = mpb_float1_minor_than_float2(c401Status1Definition->fInternalMountingSurfaceTemperature, X1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE, DEF_PRECITION); // if temp < -40 -> out
//	compareforRange2a = mpb_float1_minor_than_float2(c401Status1Definition->fBoosterOutputOpticalPower, X1_RANGE_1_BOOSTER_OUTPUT_OPTICAL_POWER, DEF_PRECITION); // if powerApc < -30  -> out
//	compareforRange2b = mpb_float1_minor_than_float2(THIRD_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER, c401Status1Definition->fBoosterOutputOpticalPower, DEF_PRECITION); // if powerApc > THIRD_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER  -> out
	
//	if( (compareforRange2 == eTrue) || (compareforRange2a == eTrue) || (compareforRange2b == eTrue) )
//	{
//		return eInvalidParameter;
//	}
	
	
	if(c401Status1Definition != NULL)
	{
		
		cRPDO_401.data.value =0;
		/* Bit 0-7: value internal unit mounting surface temperature, detection range from -40°C to +90°C.	The resolution is determined by the bit range 0..255.
		if(c401Status1Definition->fInternalMountingSurfaceTemperature > X2_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fInternalMountingSurfaceTemperature = X2_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE;
		}
				
		if(c401Status1Definition->fInternalMountingSurfaceTemperature < X1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE )
		{
					c401Status1Definition->fInternalMountingSurfaceTemperature = X1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE;
		}
					
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE),
																						(float)(Y1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE),
																						(float)(X2_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE),
																						(float)(Y2_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE),
																						c401Status1Definition->fInternalMountingSurfaceTemperature ,  coerce );																																												
		cxInternalMountingSurfaceTemperature.byte[0]			= (uint8_t)(fxValue.fValue);			
		cxInternalMountingSurfaceTemperature.value				= ( cxInternalMountingSurfaceTemperature.value << DEF_CAN_0401_INTERNAL_MOUNTING_TEMPERATURE) & 0x00000000000000FF; // bits 0-7 
		//cRPDO_401.data.bytes[0]									= cxInternalMountingSurfaceTemperature.value;	*/	
	//	cRPDO_401.data.value									= cRPDO_401.data.value |  cxInternalMountingSurfaceTemperature.value;
		
	
	
		/*Bit 0..15: value laser pump1 current of the Booster section.	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA */
		if(c401Status1Definition->fLaserPump1BoosterCurrent > X2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump1BoosterCurrent = X2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(c401Status1Definition->fLaserPump1BoosterCurrent < X1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump1BoosterCurrent = X1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																								(float)(Y1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							c401Status1Definition->fLaserPump1BoosterCurrent,  coerce );
		cxLaserPump1CurrentOfBooster.value							= 0;																				
		cxLaserPump1CurrentOfBooster.s0							= (uint16_t)(fxValue.fValue );//+ FLOAT_ADJUST);	
		cxLaserPump1CurrentOfBooster.value						= ( cxLaserPump1CurrentOfBooster.value << DEF_CAN_0401_PUMP1_CURRENT_IN_BOOSTER) & 0x000000000000FFFF; /* bits 0..15 */
	//	cRPDO_401.data.value									= cRPDO_401.data.value |  cxLaserPump1CurrentOfBooster.value;
		cRPDO_401.data.value  									= cxLaserPump1CurrentOfBooster.value ; 
		
	
		/*Bit 16-31: value laser pump2 current (if such hardware is present).	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA.*/
		if(c401Status1Definition->fLaserPump2BoosterCurrent > X2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump2BoosterCurrent = X2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(c401Status1Definition->fLaserPump2BoosterCurrent < X1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump2BoosterCurrent = X1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}		
		
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(X2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							(float)(Y2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																							c401Status1Definition->fLaserPump2BoosterCurrent,  coerce );
		cxLaserPump2CurrentOfBooster.value						= 0;
		cxLaserPump2CurrentOfBooster.s0							= (uint16_t)(fxValue.fValue  );	
		cxLaserPump2CurrentOfBooster.value						= ( cxLaserPump2CurrentOfBooster.value << DEF_CAN_0401_PUMP2_CURRENT_IN_BOOSTER) & 0x00000000FFFF0000; /* bits 16..31 */		
		cRPDO_401.data.value									= cRPDO_401.data.value |  cxLaserPump2CurrentOfBooster.value;
	
	
	
		/*	Bit 32-47: value laser pump3 current (if such hardware is present).The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA. */
		if(c401Status1Definition->fLaserPump3BoosterCurrent > X2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump3BoosterCurrent = X2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
		
		if(c401Status1Definition->fLaserPump3BoosterCurrent < X1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump3BoosterCurrent = X1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE;
		}
				
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(Y1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(X2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						(float)(Y2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE),
																						c401Status1Definition->fLaserPump3BoosterCurrent,  coerce );
		cxLaserPump3CurrentOfBooster.value						= 0;
		cxLaserPump3CurrentOfBooster.s0							= (uint16_t)(fxValue.fValue );	
		cxLaserPump3CurrentOfBooster.value						= ( cxLaserPump3CurrentOfBooster.value << DEF_CAN_0401_PUMP3_CURRENT_IN_BOOSTER) & 0x0000FFFF00000000; /* bits 32-47 */		
		cRPDO_401.data.value									= cRPDO_401.data.value |  cxLaserPump3CurrentOfBooster.value;
	
	
		/*	Bit 48-63: value laser pump4 current of the LNA section.	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA. */
		if(c401Status1Definition->fLaserPump4LnaCurrent > X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump4LnaCurrent = X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE;
		}
		
		if(c401Status1Definition->fLaserPump4LnaCurrent < X1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE )
		{
			c401Status1Definition->fLaserPump4LnaCurrent = X1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE;
		}
				
		fxValue.fValue											= mpb_math_flinear_approx(  (float)(X1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																						(float)(Y1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																						(float)(X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																						(float)(Y2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE),
																						c401Status1Definition->fLaserPump4LnaCurrent ,  coerce );

		cxLaserPump4CurrentOfLna.value								= 0;
		cxLaserPump4CurrentOfLna.s0								= (uint16_t)(fxValue.fValue  );
		cxLaserPump4CurrentOfLna.value							= ( cxLaserPump4CurrentOfLna.value << DEF_CAN_0401_PUMP4_CURRENT_IN_LNA ) & 0xFFFF000000000000; /* bits 48-63 */
		cRPDO_401.data.value									= cRPDO_401.data.value | cxLaserPump4CurrentOfLna.value;

	
	
	
	/*
		//	Bit 48-63: value laser pump4 current of the LNA section.	The resolution is determined by the bit range 0..65536 , 0ma to 32768 mA. 
		if(c401Status1Definition->fBoosterOpticalInputPower > X2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE )
		{
			c401Status1Definition->fBoosterOpticalInputPower = X2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE;
		}
			
		if(c401Status1Definition->fBoosterOpticalInputPower < X1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE )
		{
			c401Status1Definition->fBoosterOpticalInputPower = X1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE;
		}
						
		fxValue.fValue										= mpb_math_flinear_approx(  (float)(X1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							(float)(Y1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							(float)(X2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							(float)(Y2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE),
																							c401Status1Definition->fBoosterOpticalInputPower,  coerce );	
		//}
																						
		//cxBoosterOpticalInputPower.byte[0]									= (uint8_t)(fxValue.fValue);
		//cxBoosterOpticalInputPower.value									= ( cxBoosterOpticalInputPower.value << DEF_CAN_0401_BOOSTER_OPTICAL_INPUT_POWER ) & 0x0000FF0000000000; // bits 40-47 
	//	cRPDO_401.data.value												= cRPDO_401.data.value | cxBoosterOpticalInputPower.value;
		cRPDO_401.data.bytes[5]									            = (uint8_t)(fxValue.fValue + FLOAT_ADJUST );
	
		//Bit 48-55:  for the selected output channel, the value of the LNA optical output power. The resolution is determined by the specified output dBm range and the bit range 0...255.
		
		if(c401Status1Definition->fLnaOpticalOutputPower > X2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE )
		{
			c401Status1Definition->fLnaOpticalOutputPower = X2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE;
		}
			
		if(c401Status1Definition->fLnaOpticalOutputPower < X1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE )
		{
				c401Status1Definition->fLnaOpticalOutputPower = X1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE;
		}			
		
		fxValue.fValue													= mpb_math_flinear_approx(  (float)(X1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																									(float)(Y1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																									(float)(X2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																									(float)(Y2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE),
																									c401Status1Definition->fLnaOpticalOutputPower,  coerce );
		
	//	}
		//cxLnaOpticalOutputPower.byte[0]										= (uint8_t)(fxValue.fValue);
		//cxLnaOpticalOutputPower.value										= ( cxLnaOpticalOutputPower.value << DEF_CAN_0401_LNA_OPTICAL_OUTPUT_POWER ) & 0x00FF000000000000; // bits 48-55 
		//cRPDO_401.data.value												= cRPDO_401.data.value | cxLnaOpticalOutputPower.value;
		cRPDO_401.data.bytes[6]												= (uint8_t)(fxValue.fValue + FLOAT_ADJUST);
	
	
	
	   // Bit 56-63: value of the Booster output optical power : 		Value 0..255  allocated to the range -30 dBm to +19 dBm 

		if(c401Status1Definition->fBoosterOutputOpticalPower > X2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER )
		{
			c401Status1Definition->fBoosterOutputOpticalPower = X2_RANGE_1_BOOSTER_OUTPUT_OPTICAL_POWER;
		}
			
		if(c401Status1Definition->fBoosterOutputOpticalPower < X1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER )
		{
			c401Status1Definition->fBoosterOutputOpticalPower = X1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER;
		}
						
		fCoertedTofloat255										= mpb_math_flinear_approx(  (float)(X1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																							(float)(Y1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																							(float)(X2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																							(float)(Y2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER),
																							c401Status1Definition->fBoosterOutputOpticalPower,  coerce );																				 
																									 
		//cxBoosterOutputOpticalPower.byte[0]									= fCoertedTofloat255;
		//cxBoosterOutputOpticalPower.value									= ( cxBoosterOutputOpticalPower.value << DEF_CAN_0401_BOOSTER_OPTICAL_OUTPUT_POWER ) & 0xFF00000000000000; // bits 56-63 
	//	cRPDO_401.data.value												= cRPDO_401.data.value | cxBoosterOutputOpticalPower.value;
		cRPDO_401.data.bytes[7]												=(uint8_t) ( fCoertedTofloat255 + FLOAT_ADJUST );*/
	}
	else
	{		
		eMpbError = eOutOfMemory;
	}
	return eMpbError;
	
}
