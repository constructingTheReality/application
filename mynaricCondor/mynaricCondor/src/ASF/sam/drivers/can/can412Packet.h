/**
* @file			can412Packet.h
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

#ifndef CAN412PACKET_H_
#define CAN412PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

/* Define ------------------------------------------------------------------- */
#define DEF_CAN_412_PASSWORD_1							         ( 0 )
#define DEF_CAN_412_PASSWORD_2							         ( 7 )
#define DEF_CAN_412_PASSWORD_3							         ( 14 )
#define DEF_CAN_412_PASSWORD_4							         ( 21 )
#define DEF_CAN_412_PASSWORD_5							         ( 28 )
#define DEF_CAN_412_PASSWORD_6							         ( 35 )
#define DEF_CAN_412_PASSWORD_7							         ( 42 )
#define DEF_CAN_412_PASSWORD_8							         ( 49 )
#define DEF_CAN_412_PASSWORD_9							         ( 56 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	uint8_t			ucPassword1;		/*Bit 0-6   */
	uint8_t			ucPassword2;		/*Bit 7-13  */
	uint8_t			ucPassword3;		/*Bit 14-20  */
	uint8_t			ucPassword4;		/*Bit 21-27  */
	uint8_t			ucPassword5;		/*Bit 28-34  */
	uint8_t			ucPassword6;		/*Bit 35-41  */
	uint8_t			ucPassword7;		/*Bit 42-48  */
	uint8_t			ucPassword8;		/*Bit 49-55  */
	uint8_t			ucPassword9;		/*Bit 56-62  */
	
}c412StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit412CanImage( void );

/**
* @brief		get the 412 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan412( CAN_FRAME *pCan);

/**
* @brief		set the 412 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan412( CAN_FRAME *pCan);


/**
* @brief		encode the 412 CAN message
* @param[in]	c412Status1Definition_t: pointer to the 412 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan412Encode( c412StatusDefinition_t *c412StatusDefinition  );

/**
* @brief		encode the 412 CAN message
* @param[in]	c412Status1Definition_t: pointer to the 412 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan412Decode( c412StatusDefinition_t *c412StatusDefinition );


#endif /* CAN412PACKET_H_ */