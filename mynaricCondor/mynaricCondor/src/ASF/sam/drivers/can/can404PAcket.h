/**
* @file			can404Packet.h
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

#ifndef CAN404PACKET_H_
#define CAN404PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define X1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 0.0)
#define Y1_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 0.0)
#define X2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 16383.0)
#define Y2_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 65535.0)

#define X1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 0.0)
#define Y1_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 0.0)
#define X2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 16383.0)
#define Y2_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 65535.0)

#define X1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define Y1_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define X2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 16383.0)
#define Y2_ALARM_LOW_LIMIT_CURRENT_1ST_PUMP_BOOST				( 65535.0)

#define X1_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define Y1_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 0.0)
#define X2_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 16383.0)
#define Y2_ALARM_HIGH_LIMIT_CURRENT_1ST_PUMP_BOOST				( 65535.0)

#define DEF_CAN_404_STATUS_LOW_LIMIT_POWER_INPUT_LNA            0
#define DEF_CAN_404_STATUS_HIGH_LIMIT_POWER_INPUT_LNA           16
#define DEF_CAN_404_STATUS_LOW_LIMIT_CURRENT_BOOSTER			32
#define DEF_CAN_404_STATUS_HIGH_LIMIT_CURRENT_BOOSTER			48


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float						fLnaLowLimitCurrentAlarm;			/*Bit 0-15: status value alarm low limit for current laser pump on LNA section */
	float						fLnaHighLimitCurrentAlarm;			/*Bit 16-31: status value alarm high limit for current laser pump on LNA section */
	float						fBoostLowLimitCurrentAlarm; 		/*Bit 32-47: status value alarm low limit for current laser pump on Boost section */
	float						fBoostHighLimitCurrentAlarm;		/*Bit 47-63: status value alarm high limit for current laser pump on Boost section, */
	
	
//	float						fStatusAlarmLowLimitForBackfacetCurrentPumpOnLna; 	/*Bit 32-39: status value alarm low limit for backfacet current pump laser on LNA section  */
//	float						fStatusAlarmHighLimitForBackfacetCurrentPumpOnLna;	/*Bit 40-47: status value alarm high limit for back facet current pump laser on LNA */
//	float						fStatusAlarmLowLimitForUnitBaseTemperature;			/* Bit 48-55: status value alarm low limit for unit base temperature */
//	float						fStatusAlarmHighLimitForUnitBaseTemperature;		/*Bit 56-63: status value alarm high limit for unit base temperature*/
}c404StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit404CanImage( void );

/**
* @brief		get the 404 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan404( CAN_FRAME *pCan);

/**
* @brief		set the 404 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan404( CAN_FRAME *pCan);


/**
* @brief		decode the 404 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
//eMpbError_t eMpbCan404Decode( c404StatusDefinition_t *c404StatusDefinition );

/**
* @brief		encode the 404 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan404Encode( c404StatusDefinition_t *c403StatusDefinition );


#endif /* CAN404PACKET_H_ */