/**
* @file			can403Packet.h
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
#ifndef CAN403PACKET_H_
#define CAN403PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

#define DEF_COMP_PRECITION											( 100 )

#define DEF_PRECISION 0.5



#define DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_LNA            0
#define DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_LNA           8
#define DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_LNA           16
#define DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_LNA          24
#define DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_INPUT_BOOSTER        32
#define DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_INPUT_BOOSTER       40
#define DEF_CAN_0403_STATUS_LOW_LIMIT_POWER_OUTPUT_BOOSTER       48
#define DEF_CAN_0403_STATUS_HIGH_LIMIT_POWER_OUTPUT_BOOSTER       56


#define X1_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( -50.0)
#define Y1_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( 0.0)
#define X2_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( -20.0)
#define Y2_ALARM_LOW_LIMIT_POWER_INPUT_LNA						( 255.0)

#define X1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( -50.0)
#define Y1_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( 0.0)
#define X2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( -40.0)
#define Y2_ALARM_HIGH_LIMIT_POWER_INPUT_LNA						( 255.0)

#define X1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( -16.0)
#define Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( 0.0)
#define X2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( 1.0)
#define Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA						( 255.0)



#define X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( -16.0)
#define Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( 0.0)
#define X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( 1.0)
#define Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA					( 255.0)


#define X1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( -10.0)
#define Y1_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( 0.0)
#define X2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( 6.0)
#define Y2_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER					( 255.0)


#define X1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( -10.0)
#define Y1_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( 0.0)
#define X2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( 6.0)
#define Y2_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER					( 255.0)



#define X1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 15.5)
#define Y1_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 0.0)
#define X2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 38.5 )
#define Y2_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER					( 255.0)


#define X1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 15.5 )
#define Y1_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 0.0)
#define X2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 38.5 )
#define Y2_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER					( 255.0)


#define FLOAT_ADJUST  0.5

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float						fLnaPowerInputAlarmLowLimit;			/* Bit 0-7: status value alarm low limit for power input on LNA section*/
	float						fLnaPowerInputAlarmHighLimit;			/*Bit 8-15: status value alarm high limit for power input on LNA section */
	float						fLnaPowerOutputAlarmLowLimit;			/*Bit 16-23: status value alarm low limit for power output on LNA section */
	float						fLnaPowerOutputAlarmHighLimit;			/*Bit 24-31: status value alarm high limit for power output on LNA */
	float						fBoosterPowerInputAlarmLowLimit;		/*Bit 32-39: status value alarm low limit for power input on Booster section */
	float						fBoosterPowerInputAlarmHighLimit;	    /* Bit 40-47: status value alarm high limit for power input on Booster section */
	float						fBoosterPowerOutputAlarmLowLimit;		/*Bit 48-55: status value alarm low limit for power output on Booster */
	float						fBoosterPowerOutputAlarmHighLimit;		/* Bit 56-63: status value alarm high limit for power output on Booster  */
}c403StatusDefinition_t;





/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit403CanImage( void );

/**
* @brief		get the 403 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan403( CAN_FRAME *pCan);

/**
* @brief		set the 403 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan403( CAN_FRAME *pCan);



/**
* @brief		encode the 403 CAN message
* @param[in]	c402Status1Definition_t: pointer to the 402 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan403Encode( c403StatusDefinition_t *c403StatusDefinition );


/**
* @brief		decode the 403 CAN message
* @param[in]	c403Status2Definition_t: pointer to the 403 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan403Decode( c403StatusDefinition_t *c403StatusDefinition );






#endif /* CAN403PACKET_H_ */