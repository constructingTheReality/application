
#include "can402Packet.h"
#include "dictionaryUtils.h"

//#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_402;

/*---------------------------------------------------------------------------*/

void vInit402CanImage( void )
{
		cRPDO_402.data.value = 0;
		cRPDO_402.id = 0x402;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan402( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_402, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan402( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_402, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/

/*-------------------------------------------------------------*/
eMpbError_t eMpbCan402Decode( c402StatusDefinition_t *c402StatusDefinition )
{
	BytesUnion ValueOfPowerSupplyVoltage;
	BytesUnion ValueOfLaserPump1TemperatureBooster;
	BytesUnion ValueOfLaserPump2TemperatureBooster;
	BytesUnion ValueOfLaserPump3TemperatureBooster;
	BytesUnion ValueOfLaserTemperatureLna;
	BytesUnion ValueBackFacetCurrentLaserPump1Booster;
	BytesUnion ValueBackFacetCurrentLaserPumpLna;
	mpb_coerced_t coerce = not_coerced;
	eMpbError_t eMpbError = eSuccess;
	//float fTempRecuperatedFromFloatTo127 = 0.0f;
	floatUnion fTempFromFloatTo127 ;
	

	if(c402StatusDefinition != NULL)
	{
		/* Bit 0-19: alarms and status */
		c402StatusDefinition->xAlarmAndStatusRegister.AlarmStatusGlobalValue	= cRPDO_402.data.low			 ;


		
		/* Bit 20-26:  Value of laser pump 1 temperature in Booster section, within the detection range of -40°C to +90°C, resolution determined by the bit value range 0..127. */
		ValueOfLaserPump1TemperatureBooster.value						= ( cRPDO_402.data.value >> DEF_CAN_0402_LASER_PUMP1_TEMPERATURE) & 0x000000000000007F; // bits 20-26
		fTempFromFloatTo127.fValue										= (float)(ValueOfLaserPump1TemperatureBooster.low);
		
		c402StatusDefinition->fTemperatureValueSensor1		= mpb_math_flinear_approx(  (float)(Y1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(X1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(X2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						fTempFromFloatTo127.fValue, coerce );

		/*Bit 27-33:  Value of laser pump 2 temperature in Booster section, if such hardware is present, within the detection range of -40°C to +90VDC, resolution determined by the bit value range 0..127.   */
		ValueOfLaserPump2TemperatureBooster.value						= ( cRPDO_402.data.value >> DEF_CAN_0402_LASER_PUMP2_TEMPERATURE) & 0x000000000000007F; // bits 27-33 //3f8
		fTempFromFloatTo127.fValue										= (float)(ValueOfLaserPump2TemperatureBooster.low);
		c402StatusDefinition->fTemperatureValueSensor2					= mpb_math_flinear_approx(  (float)(Y1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									(float)(X1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									(float)(Y2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									(float)(X2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									fTempFromFloatTo127.fValue,  coerce );
		
		/*Bit 34-40:  Value of laser pump 3 temperature in Booster section, if such hardware is present, within the detection range of -40°C to +90°C, resolution determined by the bit value range 0..127. */
		ValueOfLaserPump3TemperatureBooster.value						= ( cRPDO_402.data.value >> DEF_CAN_0402_LASER_PUMP3_TEMPERATURE) & 0x000000000000007F; // bits 34-40 1fc
		fTempFromFloatTo127.fValue										= (float)(ValueOfLaserPump3TemperatureBooster.low);
		c402StatusDefinition->fTemperatureValueSensor3					= mpb_math_flinear_approx(  (float)(Y1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									(float)(X1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									(float)(Y2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									(float)(X2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																									fTempFromFloatTo127.fValue,  coerce );
		
		
		/*Bit 41-47:  Value of the laser pump temperature in the LNA section, within the detection range of -40°C to +90VDC, resolution determined by the bit value range 0..127.*/
		ValueOfLaserTemperatureLna.value								= ( cRPDO_402.data.value >> DEF_CAN_0402_LASER_PUMP_TEMPERATURE_LNA) & 0x000000000000007F; // bits 41-47  f7
		fTempFromFloatTo127.fValue										= (float)(ValueOfLaserTemperatureLna.low);
		c402StatusDefinition->fTemperatureValueSensor4					= mpb_math_flinear_approx(  (float)(Y1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																									(float)(X1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																									(float)(Y2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																									(float)(X2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																									fTempFromFloatTo127.fValue,  coerce );
		
		/* bit 48 . Temperature Sensor 1 Is Present;					 0: sensor not present 	1: sensor present   */
		c402StatusDefinition->bTemperatureSensor1IsPresent				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_TEMP_SENSOR1_PRESENT) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		/* bit 49 . Temperature Sensor 2 Is Present;					 0: sensor not present 	1: sensor present   */
		c402StatusDefinition->bTemperatureSensor2IsPresent				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_TEMP_SENSOR2_PRESENT) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		/* bit 50 . Temperature Sensor 3 Is Present;					 0: sensor not present 	1: sensor present   */
		c402StatusDefinition->bTemperatureSensor3IsPresent				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_TEMP_SENSOR3_PRESENT) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		/* bit 51 . Temperature Sensor 4 Is Present;					 0: sensor not present 	1: sensor present   */
		c402StatusDefinition->bTemperatureSensor4IsPresent				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_TEMP_SENSOR4_PRESENT) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		
		/* bit 52 . Booster Laser Driver 2 Is Present;					 0: sensor not present 	1: sensor present   */
		c402StatusDefinition->bBoosterLaserDriver2IsPresent				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_BOOST_DRIVER2_PRESENT) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		/* bit 53 . Booster Enable status					 0: laser driver 2 not enabled 	1: laser driver 2 enabled  */
		c402StatusDefinition->bBoosterLaserDriver2IsEnabled				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_BOOST_ENABLE2_STATUS) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		/* bit 54 . Booster laser driver 3 presence  0: laser driver 3 not present 		1: laser driver 3 present */		
		c402StatusDefinition->bBoosterLaserDriver3IsPresent				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_BOOST_DRIVER3_PRESENT) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		
		/* bit 55 . Booster laser driver 3 enable status	0: laser driver 3 not enabled 	1: laser driver 3 enabled    */		
		c402StatusDefinition->bBoosterLaserDriver3IsEnabled				= ( ( ( cRPDO_402.data.value >> DEF_CAN_0402_BOOST_ENABLE3_STATUS) & 0x0000000000000001) == 1)? eTrue: eFalse;
		
		
		/* Bit 56-63:  LNA optical input power status  ,.Value 0 255 = -50 dBm to -40 dBm  
		ValueBackFacetCurrentLaserPumpLna.value							= ( cRPDO_402.data.value >> DEF_CAN_0402_LNA_OPTICAL_INPUT) & 0x00000000000000FF; // bits 56-63
		fTempFromFloatTo127.fValue										= (float)(ValueBackFacetCurrentLaserPumpLna.byte[0]);
		
		
		c402StatusDefinition->fLnaOpticalInputPowerValue		= mpb_math_flinear_approx(  (float)(Y1_LNA_OPTICAL_INPUT_POWER),
																							(float)(X1_LNA_OPTICAL_INPUT_POWER),
																							(float)(Y2_LNA_OPTICAL_INPUT_POWER),
																							(float)(X2_LNA_OPTICAL_INPUT_POWER),
																							fTempFromFloatTo127.fValue,  coerce );*/
		
				/* Bit 15-19:  Value of power supply voltage within the detection range of 0VDC to +28VDC, resolution determined by the bit value range 0..31.
				ValueOfPowerSupplyVoltage.value									= ( cRPDO_402.data.value >> DEF_CAN_0402_POWER_SUPPLY_VOLTAGE) & 0x000000000000001F; // bits 15-19
				c402Status2Definition->fValueOfPowerSupplyVoltage				= (float)(ValueOfPowerSupplyVoltage.byte[0]);*/
		
		
		
		
		
		
		/*Bit 48-55:  Value back facet current of laser pump1 in the Booster section, within the applicable operational back facet current range, resolution determined by the bit value range 0..255. 
		ValueBackFacetCurrentLaserPump1Booster.value					= ( cRPDO_402.data.value >> DEF_CAN_0402_BACKFACER_CURRENT_PUMP1_BOOSTER) & 0x00000000000000FF; // bits 48-55
		fTempFromFloatTo127.fValue										= (float)(ValueBackFacetCurrentLaserPump1Booster.low);
		c402Status2Definition->fValueBackFacetCurrentLaserPump1Booster	= mpb_math_flinear_approx(  (float)(Y1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(Y2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		fTempFromFloatTo127.fValue,  coerce );*/

		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	
	return eMpbError;
	
	
}
/*-----------------------------------------------------------------------------*/


eMpbError_t eMpbCan402Encode( c402StatusDefinition_t *c402StatusDefinition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion ValueOfPowerSupplyVoltage;
	BytesUnion ValueOfLaserPump1TemperatureBooster;
	BytesUnion ValueOfLaserPump2TemperatureBooster;
	BytesUnion ValueOfLaserPump3TemperatureBooster;
	BytesUnion ValueOfLaserTemperatureLna;
	BytesUnion ValueBackFacetCurrentLaserPump1Booster;
	BytesUnion ValueBackFacetCurrentLaserPumpLna;
	
	
	BytesUnion ValueOfTempStatus;
	
	mpb_coerced_t coerce = not_coerced;
	float fTempCoertedTofloat127 = 0.0f;
	float fTempCoertedTofloat255 = 0.0f;
	
	cRPDO_402.data.value = 0;
	
	if(c402StatusDefinition != NULL)
	{
		/* Bit 0-19: alarms and status */
		cRPDO_402.data.low									=  c402StatusDefinition->xAlarmAndStatusRegister.AlarmStatusGlobalValue;
		
		/* Bit 20-26:  TemperatureValueSensor1:  -40 to 90 degrees ->  0..127 .  bit 20..26*/
		/* Bit 20-26:  Value of laser pump 1 temperature in Booster section, within the detection range of -40°C to +90°C, resolution determined by the bit value range 0..127. */
		if(c402StatusDefinition->fTemperatureValueSensor1 > X2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor1 = X2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		if(c402StatusDefinition->fTemperatureValueSensor1 < X1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor1 = X1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		
		fTempCoertedTofloat127								= mpb_math_flinear_approx(  (float)(X1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(X2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						c402StatusDefinition->fTemperatureValueSensor1,  coerce );

		ValueOfLaserPump1TemperatureBooster.value = 0;
		ValueOfLaserPump1TemperatureBooster.byte[0]			= (uint8_t)(fTempCoertedTofloat127) ;//+ DEF_PRECISION; ;
		ValueOfLaserPump1TemperatureBooster.value			= ( ValueOfLaserPump1TemperatureBooster.value << DEF_CAN_0402_LASER_PUMP1_TEMPERATURE) & 0x0000000007F00000; // bits 20-26
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFFFFFFF80FFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfLaserPump1TemperatureBooster.value;
		
		/*Bit 27-33:  Value of laser pump 2 temperature in Booster section, if such hardware is present, within the detection range of -40°C to +90VDC, resolution determined by the bit value range 0..127.   */
		if(c402StatusDefinition->fTemperatureValueSensor2 > X2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor2 = X2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		if(c402StatusDefinition->fTemperatureValueSensor2 < X1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor2 = X1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		fTempCoertedTofloat127								= mpb_math_flinear_approx(  (float)(X1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(X2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						c402StatusDefinition->fTemperatureValueSensor2,  coerce );
		ValueOfLaserPump2TemperatureBooster.value			= 0;
		ValueOfLaserPump2TemperatureBooster.byte[0]			=  (uint8_t)(fTempCoertedTofloat127);// + DEF_PRECISION;
		ValueOfLaserPump2TemperatureBooster.value			= ( ValueOfLaserPump2TemperatureBooster.value << DEF_CAN_0402_LASER_PUMP2_TEMPERATURE) & 0x00000003F8000000; // bits 27-33
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFFFFFC07FFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfLaserPump2TemperatureBooster.value;
		
		
		/*Bit 34-40:  Value of laser pump 3 temperature in Booster section, if such hardware is present, within the detection range of -40°C to +90°C, resolution determined by the bit value range 0..127. */
		if(c402StatusDefinition->fTemperatureValueSensor3 > X2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor3 = X2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		if(c402StatusDefinition->fTemperatureValueSensor3 < X1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor3 = X1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		fTempCoertedTofloat127								= mpb_math_flinear_approx(  (float)(X1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(X2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE),
																						c402StatusDefinition->fTemperatureValueSensor3,  coerce );
		ValueOfLaserPump3TemperatureBooster.value			= 0;
		ValueOfLaserPump3TemperatureBooster.byte[0]			=  (uint8_t)(fTempCoertedTofloat127) ;//+ DEF_PRECISION;
		ValueOfLaserPump3TemperatureBooster.value			= ( ValueOfLaserPump3TemperatureBooster.value << DEF_CAN_0402_LASER_PUMP3_TEMPERATURE) & 0x000001FC00000000; // bits 34-40
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFFFE03FFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfLaserPump3TemperatureBooster.value;
		
		
		/*Bit 41-47:  Value of the laser pump temperature in the LNA section, within the detection range of -40°C to +90VDC, resolution determined by the bit value range 0..127.*/
		if(c402StatusDefinition->fTemperatureValueSensor4 > X2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor4 = X2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE;
		}
		
		if(c402StatusDefinition->fTemperatureValueSensor4 < X1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE )
		{
			c402StatusDefinition->fTemperatureValueSensor4 = X1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE;
		}
		
		fTempCoertedTofloat127								= mpb_math_flinear_approx(  (float)(X1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																						(float)(X2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																						(float)(Y2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE),
																						c402StatusDefinition->fTemperatureValueSensor4,  coerce );
		ValueOfLaserTemperatureLna.value					= 0;
		ValueOfLaserTemperatureLna.byte[0]					= (uint8_t)(fTempCoertedTofloat127);//+ DEF_PRECISION;
		ValueOfLaserTemperatureLna.value					= ( ValueOfLaserTemperatureLna.value << DEF_CAN_0402_LASER_PUMP_TEMPERATURE_LNA) & 0x0000FE0000000000; // bits 41-47
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFF01FFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfLaserTemperatureLna.value;
		
		
		
		/* bit 48 . Temperature Sensor 1 Is Present;					 0: sensor not present 	1: sensor present   */		
		ValueOfTempStatus.value								= (c402StatusDefinition->bTemperatureSensor1IsPresent == eTrue)? 1: 0; 
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_TEMP_SENSOR1_PRESENT) & 0x0001000000000000; // bit 48		
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFEFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;

		/* bit 49 . Temperature Sensor 2 Is Present;					 0: sensor not present 	1: sensor present   */
		ValueOfTempStatus.value								= (c402StatusDefinition->bTemperatureSensor2IsPresent == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_TEMP_SENSOR2_PRESENT) & 0x0002000000000000; // bit 49				
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFDFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;

		/* bit 50 . Temperature Sensor 3 Is Present;					 0: sensor not present 	1: sensor present   */
		ValueOfTempStatus.value								= (c402StatusDefinition->bTemperatureSensor3IsPresent == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_TEMP_SENSOR3_PRESENT) & 0x0004000000000000; // bit 50
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFFBFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;

		/* bit 51 . Temperature Sensor 4 Is Present;					 0: sensor not present 	1: sensor present   */
		ValueOfTempStatus.value								= (c402StatusDefinition->bTemperatureSensor4IsPresent == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_TEMP_SENSOR4_PRESENT) & 0x0008000000000000; // bit 51
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFF7FFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;


		/* bit 52 . Booster Laser Driver 2 Is Present;					 0: sensor not present 	1: sensor present   */
		ValueOfTempStatus.value								= (c402StatusDefinition->bBoosterLaserDriver2IsPresent == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_BOOST_DRIVER2_PRESENT) & 0x0010000000000000; // bit 52
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFEFFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;		

		/* bit 53 . Booster Enable status					 0: laser driver 2 not enabled 	1: laser driver 2 enabled  */
		ValueOfTempStatus.value								= (c402StatusDefinition->bBoosterLaserDriver2IsEnabled == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_BOOST_ENABLE2_STATUS) & 0x0020000000000000; // bit 53
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFDFFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;
		
		/* bit 54 . Booster laser driver 3 presence  0: laser driver 3 not present 		1: laser driver 3 present */
		ValueOfTempStatus.value								= (c402StatusDefinition->bBoosterLaserDriver3IsPresent == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_BOOST_DRIVER3_PRESENT) & 0x0040000000000000; // bit 54
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFFBFFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;				
		
		
		/* bit 55 . Booster laser driver 3 enable status	0: laser driver 3 not enabled 	1: laser driver 3 enabled    */
		ValueOfTempStatus.value								= (c402StatusDefinition->bBoosterLaserDriver3IsEnabled == eTrue)? 1: 0;
		ValueOfTempStatus.value								= ( ValueOfTempStatus.value << DEF_CAN_0402_BOOST_ENABLE3_STATUS) & 0x0080000000000000; // bit 55
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFF7FFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueOfTempStatus.value;		
		
		
		/* Bit 56-63:  LNA optical input power status  ,.Value 0 255 = -50 dBm to -40 dBm  
		if(c402StatusDefinition->fLnaOpticalInputPowerValue > X2_LNA_OPTICAL_INPUT_POWER )
		{
			c402StatusDefinition->fLnaOpticalInputPowerValue = X2_LNA_OPTICAL_INPUT_POWER;
		}
		
		if(c402StatusDefinition->fLnaOpticalInputPowerValue < X1_LNA_OPTICAL_INPUT_POWER )
		{
			c402StatusDefinition->fLnaOpticalInputPowerValue = X1_LNA_OPTICAL_INPUT_POWER;
		}
		
		fTempCoertedTofloat255								= mpb_math_flinear_approx(  (float)(X1_LNA_OPTICAL_INPUT_POWER),
																						(float)(Y1_LNA_OPTICAL_INPUT_POWER),
																						(float)(X2_LNA_OPTICAL_INPUT_POWER),
																						(float)(Y2_LNA_OPTICAL_INPUT_POWER),
																						c402StatusDefinition->fLnaOpticalInputPowerValue,  coerce );
		ValueBackFacetCurrentLaserPumpLna.value				= 0;
		ValueBackFacetCurrentLaserPumpLna.byte[0]			= (uint8_t)(fTempCoertedTofloat255);//+ DEF_PRECISION;
		ValueBackFacetCurrentLaserPumpLna.value				= ( ValueBackFacetCurrentLaserPumpLna.value << DEF_CAN_0402_LNA_OPTICAL_INPUT) & 0xFF00000000000000; // bits 56-63
		cRPDO_402.data.value								= cRPDO_402.data.value & 0x00FFFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueBackFacetCurrentLaserPumpLna.value;*/
		
		
		
		
		
		
		/*Bit 48-55:  Value back facet current of laser pump1 in the Booster section, within the applicable operational back facet current range, resolution determined by the bit value range 0..255. 
		if(c402Status2Definition->fValueBackFacetCurrentLaserPump1Booster > X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402Status2Definition->fValueBackFacetCurrentLaserPump1Booster = X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		if(c402Status2Definition->fValueBackFacetCurrentLaserPump1Booster < X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402Status2Definition->fValueBackFacetCurrentLaserPump1Booster = X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		fTempCoertedTofloat255								= mpb_math_flinear_approx(  (float)(X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(Y1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(Y2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		c402Status2Definition->fValueBackFacetCurrentLaserPump1Booster,  coerce );
		ValueBackFacetCurrentLaserPump1Booster.value		= 0;
		ValueBackFacetCurrentLaserPump1Booster.byte[0]		= (uint8_t)(fTempCoertedTofloat255)+ DEF_ADJUST;
		ValueBackFacetCurrentLaserPump1Booster.value		= ( ValueBackFacetCurrentLaserPump1Booster.value << DEF_CAN_0402_BACKFACER_CURRENT_PUMP1_BOOSTER) & 0x00FF000000000000; // bits 48-55
		cRPDO_402.data.value								= cRPDO_402.data.value & 0xFF00FFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueBackFacetCurrentLaserPump1Booster.value;*/
		
		/* Bit 56-63:  Value back facet current of laser pump in the LNA section, within the applicable operational back facet current range, resolution determined by the bit value range 0..255.
		if(c402Status2Definition->fValueBackFacetCurrentLaserPumpLna > X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402Status2Definition->fValueBackFacetCurrentLaserPumpLna = X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		if(c402Status2Definition->fValueBackFacetCurrentLaserPumpLna < X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE )
		{
			c402Status2Definition->fValueBackFacetCurrentLaserPumpLna = X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE;
		}
		
		fTempCoertedTofloat255								= mpb_math_flinear_approx(  (float)(X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(Y1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		(float)(Y2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE),
		c402Status2Definition->fValueBackFacetCurrentLaserPumpLna,  coerce );
		ValueBackFacetCurrentLaserPumpLna.value				= 0;
		ValueBackFacetCurrentLaserPumpLna.byte[0]			= (uint8_t)(fTempCoertedTofloat255)+ DEF_ADJUST;
		ValueBackFacetCurrentLaserPumpLna.value				= ( ValueBackFacetCurrentLaserPumpLna.value << DEF_CAN_0402_BACKFACER_CURRENT_PUMP_LNA) & 0xFF00000000000000; // bits 56-63
		cRPDO_402.data.value								= cRPDO_402.data.value & 0x00FFFFFFFFFFFFFF;
		cRPDO_402.data.value								= cRPDO_402.data.value |  ValueBackFacetCurrentLaserPumpLna.value;*/
	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	return eMpbError;
	
}