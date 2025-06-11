/**
* @file			can402Packet.h
* @brief
* @author		juan andres castano
* @date			Created on 2023-01-19
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef CAN402PACKET_H_
#define CAN402PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

#define DEF_PRECITION											( 100 )

#define DEF_PRECISION 0.5
#define DEF_CAN_0402_POWER_SUPPLY_VOLTAGE			             15
#define DEF_CAN_0402_LASER_PUMP1_TEMPERATURE		             20
#define DEF_CAN_0402_LASER_PUMP2_TEMPERATURE		             27
#define DEF_CAN_0402_LASER_PUMP3_TEMPERATURE		             34
#define DEF_CAN_0402_LASER_PUMP_TEMPERATURE_LNA		             41
#define DEF_CAN_0402_TEMP_SENSOR1_PRESENT			             48
#define DEF_CAN_0402_TEMP_SENSOR2_PRESENT			             49
#define DEF_CAN_0402_TEMP_SENSOR3_PRESENT			             50
#define DEF_CAN_0402_TEMP_SENSOR4_PRESENT			             51

#define DEF_CAN_0402_BOOST_DRIVER2_PRESENT			             52
#define DEF_CAN_0402_BOOST_ENABLE2_STATUS			             53
#define DEF_CAN_0402_BOOST_DRIVER3_PRESENT			             54
#define DEF_CAN_0402_BOOST_ENABLE3_STATUS			             55

#define DEF_CAN_0402_LNA_OPTICAL_INPUT				             56


#define X1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( -40.0)
#define Y1_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 0.0)
#define X2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 90.0)
#define Y2_PUMP1_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 127.0)

#define X1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( -40.0)
#define Y1_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 0.0)
#define X2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 90.0)
#define Y2_PUMP2_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 127.0)


#define X1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( -40.0)
#define Y1_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 0.0)
#define X2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 90.0)
#define Y2_PUMP3_TEMP_BOOSTER_LINEAR_APROXIMATION_ENCODE		( 127.0)

#define X1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE		( -40.0)
#define Y1_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE		( 0.0)
#define X2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE		( 90.0)
#define Y2_PUMP_TEMP_LNA_LINEAR_APROXIMATION_ENCODE		( 127.0)

#define X1_LNA_OPTICAL_INPUT_POWER	( -50.0)
#define Y1_LNA_OPTICAL_INPUT_POWER	( 0.0)
#define X2_LNA_OPTICAL_INPUT_POWER	( -40.0)
#define Y2_LNA_OPTICAL_INPUT_POWER	( 255.0)


#define FLOAT_ADJUST  0.5

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */



typedef struct
{
	uint32_t bBoosterEnableLaserSingleModeStatus			: 1;     /* bit 0  0:disabled, 1:enabled */	
	uint32_t bLnaInputPhotodiodeIsPresent					: 1;     /* bit 1  0: absent 1:present  */
	uint32_t bLnaInputPowerLimitAlarmStatus					: 1;     /* bit 2  0: input optical power is within limits 	1: output optical power out of limits */
	uint32_t bLnaEnableLaserDriverStatus					: 1;     /* bit 3  0:disabled, 1:enabled */
	uint32_t bBoosterMode		 							: 1;     /* bit 4 - (0: ACC, 1: APC) */
	uint32_t bLnaMode			 							: 1;     /* bit 5 - (0: ACC, 1: APC) */
	uint32_t bRxLnaChannelSelection							: 1;     /* bit 6 - (0: RX Amplify CH30-1553.33 nm, 1: RX Amplify CH51-1536.61 nm) */
	uint32_t bTxBoostChannelSelection						: 1;     /* bit 7 - (0: TX boost CH30-1553.33nm,    1: TX Boost CH51-1536.61 nm) */
	uint32_t bLnaOpticalPowerOutputLimitAlarmStatus			: 1;     /* bit 8 - (0: within limits, 1: out of limits) */
	uint32_t bLnaCurrentLimitAlarmStatus					: 1;     /* bit 9 - (0: within limits, 1: out of limits) */
	uint32_t bBoosterOpticalOutPowerLimitAlarmStatus		: 1;     /* bit 10 - (0: within limits, 1: out of limits) */
	uint32_t bBoosterCurrentLimitAlarmStatus				: 1;     /* bit 11 - (0: within limits, 1: out of limits) */
	uint32_t bBoosterInputPowerLimitAlarmStatus				: 1;     /* bit 12 - (0: within limits, 1: out of limits) */
	uint32_t bUnitBaseTemperatureAlarmStatus				: 1;     /* bit 13 - (0: within limits, 1: out of limits) */
	uint32_t bTemporaryDisableFunction						: 1;     /* bit 14 - (0: Booster and LNA can be enabled 1: Booster or LNA disabled temporarily) */
	uint32_t bInternalCriticalErrorFlag						: 1;     /* bit 15 - (0: normal operation, 1: critical error) */
	uint32_t bCurrentBoosterDriver2AlarmFlag				: 1;     /* bit 16 - (0: within limits, 1: out of limits) */
	uint32_t bCurrentBoosterDriver3AlarmFlag				: 1;     /* bit 17 - (0: within limits, 1: out of limits) */
	uint32_t bBoosterEnableLaserMultiMode1Status			: 1;     /* bit 18  0:disabled, 1:enabled */	
	uint32_t bBoosterEnableLaserMultiMode2Status			: 1;     /* bit 19  0:disabled, 1:enabled */	
	uint32_t bBoosterInternalCriticalErrorInPowerFlag		: 1;     /* bit 20 - (0: normal operation, 1: critical error) */
	uint32_t bLnaInternalCriticalErrorInPowerFlag			: 1;     /* bit 21 - (0: normal operation, 1: critical error) */
	uint32_t bLnaBackfacetCurrentErrorFlag					: 1;     /* bit 22 - (0: normal operation, 1: critical error) */
	uint32_t bHpaBackfacetCurrentErrorFlag					: 1;     /* bit 23 - (0: normal operation, 1: critical error) */
	
	
} AlarmsAndStatusRegisterBitAssignment_t;




typedef union
{
	AlarmsAndStatusRegisterBitAssignment_t	AlarmsAndStatusRegisterBitAssignment;
	uint8_t									AlarmsStatusRegisterBytes[4];
	uint32_t 								AlarmStatusGlobalValue;
	
}xAlarmAndStatusRegister_t;


typedef struct
{
	xAlarmAndStatusRegister_t	xAlarmAndStatusRegister;
	float						fTemperatureValueSensor1;						/* -40 to 90degres ->  0..127 .  bit 20..26*/
	float						fTemperatureValueSensor2;						/* -40 to 90degres ->  0..127 .  bit 27..33*/
	float						fTemperatureValueSensor3;						/* -40 to 90degres ->  0..127 .  bit 34..40*/
	float						fTemperatureValueSensor4; 						/* -40 to 90degres ->  0..127 .  bit 41..47*/
	eBool_t						bTemperatureSensor1IsPresent;					/* 0: sensor not present 	1: sensor present  */
	eBool_t						bTemperatureSensor2IsPresent;					/* 0: sensor not present 	1: sensor present  */
	eBool_t						bTemperatureSensor3IsPresent;					/* 0: sensor not present 	1: sensor present  */
	eBool_t						bTemperatureSensor4IsPresent;					/* 0: sensor not present 	1: sensor present  */
	
	eBool_t						bBoosterLaserDriver2IsPresent;					/* 0: sensor not present 	1: sensor present  */	
	eBool_t						bBoosterLaserDriver2IsEnabled;					/* 0: sensor not enabled	1: sensor enabled  */
	
	eBool_t						bBoosterLaserDriver3IsPresent;					/* 0: sensor not present 	1: sensor present  */
	
	eBool_t						bBoosterLaserDriver3IsEnabled;					/* 0: sensor not enabled	1: sensor enabled  */
//	float						fLnaOpticalInputPowerValue; 					/* Value 0 255 = -50 dBm to -40 dBm*/
	
}c402StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit402CanImage( void );

/**
* @brief		get the 402 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan402( CAN_FRAME *pCan);

/**
* @brief		set the 402 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan402( CAN_FRAME *pCan);



/**
* @brief		encode the 402 CAN message
* @param[in]	c402Status1Definition_t: pointer to the 402 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan402Encode( c402StatusDefinition_t *c402StatusDefinition );


/**
* @brief		decode the 402 CAN message
* @param[in]	c402Status2Definition_t: pointer to the 402 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan402Decode( c402StatusDefinition_t *c402StatusDefinition );




#endif /* CAN402PACKET_H_ */