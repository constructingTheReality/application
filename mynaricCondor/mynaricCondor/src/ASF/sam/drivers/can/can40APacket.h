/**
* @file			can40aPacket.h
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

#ifndef CAN40APACKET_H_
#define CAN40APACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define X1_BOOSTERM_40A_LIMIT_CURRENT						( 0 )
#define Y1_BOOSTERM_40A_LIMIT_CURRENT						( 0 )
#define X2_BOOSTERM_40A_LIMIT_CURRENT						( 16383 )
#define Y2_BOOSTERM_40A_LIMIT_CURRENT						( 65535)


#define DEF_CAN_40A_BOOSTER_DRIVER2_CURRENT_LOW_ALARM            ( 0 )
#define DEF_CAN_40A_BOOSTER_DRIVER2_CURRENT_HIGH_ALARM           ( 16 )
#define DEF_CAN_40A_BOOSTER_DRIVER3_CURRENT_LOW_ALARM            ( 32 )
#define DEF_CAN_40A_BOOSTER_DRIVER3_CURRENT_HIGH_ALARM           ( 48 )


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float		fBoosterDriver2CurrentLowAlarmLimit;		/*Bit 0-15:   */
	float		fBoosterDriver2CurrentHighAlarmLimit;		/*Bit 16-31   */
	float		fBoosterDriver3CurrentLowAlarmLimit;		/*Bit 32-47   */
	float		fBoosterDriver3CurrentHighAlarmLimit;		/*Bit 48-63   */
	
}c40AStatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit40ACanImage( void );

/**
* @brief		get the 40A CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan40A( CAN_FRAME *pCan);

/**
* @brief		set the 40A CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan40A( CAN_FRAME *pCan);


/**
* @brief		encode the 40A CAN message
* @param[in]	c408Status1Definition_t: pointer to the 40A message
* @return       Success or library error message
*/
eMpbError_t eMpbCan40AEncode( c40AStatusDefinition_t *c40AStatusDefinition  );

/**
* @brief		encode the 40A CAN message
* @param[in]	c408Status1Definition_t: pointer to the 40A message
* @return       Success or library error message
*/
eMpbError_t eMpbCan40ADecode( c40AStatusDefinition_t *c40AStatusDefinition );



#endif /* CAN40APACKET_H_ */