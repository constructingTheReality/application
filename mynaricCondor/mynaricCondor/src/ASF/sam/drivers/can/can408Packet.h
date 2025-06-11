/**
* @file			can408Packet.h
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
#ifndef CAN408PACKET_H_
#define CAN408PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */



#define X1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( 0.0)
#define Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( -50.0)
#define X2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( 255.0)
#define Y2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( -20.0)


#define X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( 0.0)
#define Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( -50.0)
#define X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( 255.0)
#define Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( -20.0)


#define X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( 0.0)
#define Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( -16.0)
#define X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( 255.0)
#define Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( 1.0)


#define X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( 0.0)
#define Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( -16.0)
#define X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( 255.0)
#define Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( 1.0)

#define X1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( 0.0)
#define Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( -10.0)
#define X2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( 255.0)
#define Y2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( 6.0 )

#define X1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( 0.0)
#define Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( -10.0)
#define X2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( 255.0)
#define Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( 6.0 )

#define X1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 0.0)
#define Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 15.0)
#define X2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 255.0 )
#define Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 38.5)


#define X1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 0.0)
#define Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 15.0)
#define X2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 255.0 )
#define Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 38.5)


#define DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_INPUT_LNA            0
#define DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_INPUT_LNA           8
#define DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_OUTPUT_LNA           16
#define DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_OUTPUT_LNA          24
#define DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER        32
#define DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER       40
#define DEF_CAN_0408_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER       48
#define DEF_CAN_0408_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER       56

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */


typedef struct
{
	float						fLnaSetStatusAlarmLowLimitForPowerInput;			/* Bit 0-7: status value alarm low limit for power input on LNA section*/
	float						fLnaSetStatusAlarmHighLimitForPowerInput;			/*Bit 8-15: status value alarm high limit for power input on LNA section */
	float						fLnaSetStatusAlarmLowLimitForPowerOutput;			/*Bit 16-23: status value alarm low limit for power output on LNA section */
	float						fLnaSetStatusAlarmHighLimitForPowerOutput;			/*Bit 24-31: status value alarm high limit for power output on LNA */
	float						fBoosterSetStatusAlarmLowLimitForPowerInput;		/*Bit 32-39: status value alarm low limit for power input on Booster section */
	float						fBoosterSetStatusAlarmHighLimitForPowerInput;	    /* Bit 40-47: status value alarm high limit for power input on Booster section */
	float						fBoosterSetStatusAlarmLowLimitForPowerOutput;		/*Bit 48-55: status value alarm low limit for power output on Booster */
	float						fBoosterSetStatusAlarmHighLimitForPowerOutput;		/* Bit 56-63: status value alarm high limit for power output on Booster  */
}c408StatusDefinition_t;



/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit408CanImage( void );



/**
* @brief		get the 408 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan408( CAN_FRAME *pCan);


/**
* @brief		set the 408 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan408( CAN_FRAME *pCan);


/**
* @brief		encode the 408 CAN message
* @param[in]	c408Status1Definition_t: pointer to the 408 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan408Encode( c408StatusDefinition_t *c408StatusDefinition );

/**
* @brief		encode the 408 CAN message
* @param[in]	c408Status1Definition_t: pointer to the 408 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan408Decode( c408StatusDefinition_t *c408StatusDefinition );




#endif /* CAN408PACKET_H_ */