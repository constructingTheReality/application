/**
* @file			can407Packet.h
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
#ifndef CAN407PACKET_H_
#define CAN407PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

#define X1_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT					( 0.0)
#define Y1_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT					( 0.0)
#define X2_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT					( 1023.0)
#define Y2_407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT					( 100.0)

#define X1_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT				( 0.0)
#define Y1_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT				( 0.0)
#define X2_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT				( 1023.0)
#define Y2_407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT				( 100.0)

#define X1_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT					( 0.0)
#define Y1_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT					( 0.0)
#define X2_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT					( 1023.0)
#define Y2_407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT					( 100.0)

#define X1_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT				( 0.0)
#define Y1_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT				( 0.0)
#define X2_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT				( 1023.0)
#define Y2_407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT				( 100.0)

#define X1_407_LNA_POWER_APC									( 0.0)
#define Y1_407_LNA_POWER_APC									( -15.0)
#define X2_407_LNA_POWER_APC									( 1023.0)
#define Y2_407_LNA_POWER_APC									( 0.0)


#define DEF_407_MAX_VALUE										( 1023.0)
#define DEF_CAN_0407_SET_NVM						            ( 0 )
#define DEF_CAN_0407_BOOSTER_CURRENT2_LOW_ALARM_LIMIT			( 1 )
#define DEF_CAN_0407_BOOSTER_CURRENT2_HIGH_ALARM_LIMIT			( 11 )
#define DEF_CAN_0407_BOOSTER_CURRENT3_LOW_ALARM_LIMIT			( 21 )
#define DEF_CAN_0407_BOOSTER_CURRENT3_HIGH_ALARM_LIMIT			( 31 )
#define DEF_CAN_0407_LNA_POWER_IN_APC							( 41 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */


typedef struct
{
	eBool_t 				bSaveSettingsInNvm;						/*bit 0. 1 (1): save * 0: no action */
	float					fBoosterCurrent2LowAlarmLimit;			/*bit 1..10 (10). Value 0 1023 = 0% to 100% 	resolution is 0,1% */
	float					fBoosterCurrent2HighAlarmLimit;			/*bit 11..20 (10). Value 0 1023 = 0% to 100% 	resolution is 0,1% */
	float					fBoosterCurrent3LowAlarmLimit;			/*bit 21..30 (10) Value 0 1023 = 0% to 100% 	resolution is 0,1% */
	float					fBoosterCurrent3HighAlarmLimit;			/*bit 31..40 (10) Value 0 1023 = 0% to 100% 	resolution is 0,1% */
	float					fLnaSetPowerInApcMode;					/*bit 41..50 Value 0 1023 = -15 dBm to 0 dBm 	resolution 0.015 dB   */
}c407PacketControlDefinition_t;




/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit407CanImage( void );


/**
* @brief		get the 407 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan407( CAN_FRAME *pCan);

/**
* @brief		set the 407 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan407( CAN_FRAME *pCan);

/**
* @brief		decode the 407 CAN message and set the image (control message)
* @param[in]	c407Status2Definition_t: pointer to the 406 mesage
* @return       Success or library error message
*/

eMpbError_t eMpbCan407Decode( c407PacketControlDefinition_t *c407PacketControlDefinition );
/**
* @brief		encode the 407 CAN message to be sent (control message)
* @param[in]	c402Status2Definition_t: pointer to the 406 mesage
* @return       Success or library error message
*/

eMpbError_t eMpbCan407Encode( c407PacketControlDefinition_t *c407PacketControlDefinition );



#endif /* CAN407PACKET_H_ */