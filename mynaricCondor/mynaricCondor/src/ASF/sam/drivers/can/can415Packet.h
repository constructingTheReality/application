/**
* @file			can415Packet.h
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

#ifndef CAN415PACKET_H_
#define CAN415PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define X1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE						( -40.0)
#define Y1_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE						( 0.0)
#define X2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE						( 90.0)
#define Y2_ALARM_415_LOW_LIMIT_UNIT_TEMPERATURE						( 255.0)

#define X1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE				( -40.0)
#define Y1_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE				( 0.0)
#define X2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE				( 90.0)
#define Y2_ALARM_415_HIGH_LIMIT_UNIT_TEMPERATURE				( 255.0)

#define DEF_CAN_0415_ALARM_LOW_LIMIT_UNIT_TEMPERATURE            ( 0 )
#define DEF_CAN_0415_ALARM_HIGH_LIMIT_UNIT_TEMPERATURE            ( 8 )


#define DEF_CAN_0415_ALARM_LOW_LIMIT_PUMP_TEMPERATURE            ( 16 )
#define DEF_CAN_0415_ALARM_HIGH_LIMIT_PUMP_TEMPERATURE            ( 24 )

#define DEF_CAN_0415_ALARM_VERY_LOW_LIMIT_PUMP_TEMPERATURE            ( 32 )
#define DEF_CAN_0415_ALARM_VERY_HIGH_LIMIT_PUMP_TEMPERATURE            ( 40 )


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float						fUnitBaseTemperatureLowAlarmLimit;	/*Bit 0-7 */
	float						fUnitBaseTemperatureHighAlarmLimit;	/*Bit 8-15 */
	float						fPumpTemperatureLowAlarmLimit;	    /*Bit 16-23 */
	float						fPumpTemperatureHighAlarmLimit;	    /*Bit 24-31 */
	
	float						fPumpTemperatureVeryLowAlarmLimit;	    /*Bit 32-39 */
	float						fPumpTemperatureVeryHighAlarmLimit;	    /*Bit 40-47 */
	
	
}c415StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit415CanImage( void );

/**
* @brief		get the 415 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan415( CAN_FRAME *pCan);

/**
* @brief		set the 415 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan415( CAN_FRAME *pCan);


/**
* @brief		decode the 415 CAN message
* @param[in]	c415StatusDefinition_t: pointer to the 415 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan415Decode( c415StatusDefinition_t *c415StatusDefinition );

/**
* @brief		encode the 415 CAN message
* @param[in]	c415StatusDefinition_t: pointer to the 415 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan415Encode( c415StatusDefinition_t *c415StatusDefinition );


#endif /* CAN415PACKET_H_ */