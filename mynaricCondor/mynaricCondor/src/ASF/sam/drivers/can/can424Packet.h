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
#ifndef CANPACKET424_H_
#define CANPACKET424_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

#define X1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 0.0)
#define Y1_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 0.0)
#define X2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 1023.0)
#define Y2_409_ALARM_LOW_LIMIT_CURRENT_PUMP_LNA						( 100.0)


#define X1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 0.0)
#define Y1_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 0.0)
#define X2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 1023.0)
#define Y2_409_ALARM_HIGH_LIMIT_CURRENT_PUMP_LNA					( 100.0)

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


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float						fSetTemperatureAlarmLowLimitForLNA_SMThermistor;					/*Bit 0-9: set low alarm limit*/
	float						fSetTemperatureAlarmHighimitForLNA_SMThermistor;				/*Bit 10-19: set alarm high limit */
	
}c424StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit424CanImage( void );

/**
* @brief		get the 424 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan424( CAN_FRAME *pCan);

/**
* @brief		set the 424 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan424( CAN_FRAME *pCan);


/**
* @brief		encode the 424 CAN message
* @param[in]	c424Status1Definition_t: pointer to the 424 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan424Encode( c424StatusDefinition_t *c424StatusDefinition );

/**
* @brief		encode the 424 CAN message
* @param[in]	c408Status1Definition_t: pointer to the 424 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan424Decode( c424StatusDefinition_t *c424StatusDefinition );





#endif /* CANPACKET424_H_ */