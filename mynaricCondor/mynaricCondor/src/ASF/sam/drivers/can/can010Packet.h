/**
* @file			can010Packet.h
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

#ifndef CAN010PACKET_H_
#define CAN010PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */



/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	eBool_t 				   bPortSelector;					/*Bit 7  */
	
}c010Definition_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit010CanImage( void );

/**
* @brief		get the 010 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan010( CAN_FRAME *pCan);

/**
* @brief		set the 010 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan010( CAN_FRAME *pCan);


/**
* @brief		decode the 010 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan010Decode( c010Definition_t *c010Definition );

/**
* @brief		encode the 010 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan010Encode( c010Definition_t *c010Definition );

#endif /* CAN010PACKET_H_ */