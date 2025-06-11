/**
* @file			can409Packet.h
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
#ifndef CAN409PACKET_H_
#define CAN409PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

#define X1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 0.0)
#define Y1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 0.0)
#define X2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 1023.0)
#define Y2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 16383.0)


#define X1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 0.0)
#define Y1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 0.0)
#define X2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 1023.0)
#define Y2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 16383.0)

#define X1_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define Y1_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define X2_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 1023.0)
#define Y2_409_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 100.0)

#define X1_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define Y1_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define X2_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 1023.0)
#define Y2_409_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 100.0)

#define X1_409_UNIT_TEMP_LOW										( 0.0)
#define Y1_409_UNIT_TEMP_LOW										( -40.0)
#define X2_409_UNIT_TEMP_LOW										( 255.0)
#define Y2_409_UNIT_TEMP_LOW										( 90.0)

#define X1_409_UNIT_TEMP_HIGH										( 0.0)
#define Y1_409_UNIT_TEMP_HIGH										( -40.0)
#define X2_409_UNIT_TEMP_HIGH										( 255.0)
#define Y2_409_UNIT_TEMP_HIGH										( 90.0)


#define DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_LNA				0
#define DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_LNA				10

#define DEF_CAN_0409_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER			20
#define DEF_CAN_0409_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER			30

#define DEF_CAN_0409_UNIT_TEMP_LOW_LIMIT							48
#define DEF_CAN_0409_UNIT_TEMP_HIGH_LIMIT							56

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float						fSetLnaAlarmLowLimitForCurrentPump;					/*Bit 0-9: set low alarm limit status value alarm low limit for current laser pump on LNA section */
	float						fSetLnaAlarmHighLimitForCurrentPump;				/*Bit 10-19: set alarm high limit for current laser pump on LNA section */
	float						fSetBoosterAlarmLowLimitForCurrenFirstPump; 		/*Bit 20-29: set alarm low limit for current first laser pump on Boost section */
	float						fSetBoosterAlarmHighLimitForCurrentFirstPump;		/*Bit 30-39: status value alarm high limit for current first laser pump on Boost section, */	
	//float						fSetStatusAlarmLowLimitForBackfacetCurrentPumpOnLna; 	/*Bit 32-39: status value alarm low limit for backfacet current pump laser on LNA section  */
	//float						fSetStatusAlarmHighLimitForBackfacetCurrentPumpOnLna;	/*Bit 40-47: status value alarm high limit for back facet current pump laser on LNA */
	float						fSetTemperatureAlarmLowLimitForUnitBase;			/* Bit 48-55: status value alarm low limit for unit base temperature */
	float						fSetTemperatureAlarmHighLimitForUnitBase;			/*Bit 56-63: status value alarm high limit for unit base temperature*/
}c409StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit409CanImage( void );

/**
* @brief		get the 409 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan409( CAN_FRAME *pCan);

/**
* @brief		set the 409 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan409( CAN_FRAME *pCan);


/**
* @brief		encode the 409 CAN message
* @param[in]	c408Status1Definition_t: pointer to the 408 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan409Encode( c409StatusDefinition_t *c409StatusDefinition );

/**
* @brief		encode the 409 CAN message
* @param[in]	c408Status1Definition_t: pointer to the 408 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan409Decode( c409StatusDefinition_t *c409StatusDefinition );


#endif /* CAN409PACKET_H_ */