/**
* @file			can411Packet.h
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

#ifndef CAN411PACKET_H_
#define CAN411PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

/* Define ------------------------------------------------------------------- */
#define DEF_CAN_411_COEFFICIENT							         ( 0 )
#define DEF_CAN_411_INDEX_COEFFICIENT							 ( 32 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float		fReadValueCalibrationCoefficient;		/*Bit 0-31   */	
	uint16_t	usNumberCoefStatus;						/* bits 32..43*/
}c411StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit411CanImage( void );

/**
* @brief		get the 40A CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan411( CAN_FRAME *pCan);

/**
* @brief		set the 40A CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan411( CAN_FRAME *pCan);


/**
* @brief		encode the 40A CAN message
* @param[in]	c408Status1Definition_t: pointer to the 40A message
* @return       Success or library error message
*/
eMpbError_t eMpbCan411Encode( c411StatusDefinition_t *c411StatusDefinition  );

/**
* @brief		encode the 40A CAN message
* @param[in]	c408Status1Definition_t: pointer to the 40A message
* @return       Success or library error message
*/
eMpbError_t eMpbCan411Decode( c411StatusDefinition_t *c411StatusDefinition );





#endif /* CAN411PACKET_H_ */