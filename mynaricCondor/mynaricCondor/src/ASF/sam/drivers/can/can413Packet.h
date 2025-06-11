/**
* @file			can413Packet.h
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

#ifndef CAN413PACKET_H_
#define CAN413PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

/* Define ------------------------------------------------------------------- */
#define DEF_CAN_413_PASSWORD_10							         ( 0 )
#define DEF_CAN_413_PASSWORD_11							         ( 7 )
#define DEF_CAN_413_PASSWORD_12							         ( 14 )
#define DEF_CAN_413_PASSWORD_13							         ( 21 )
#define DEF_CAN_413_PASSWORD_14							         ( 28 )
#define DEF_CAN_413_PASSWORD_15							         ( 35 )
#define DEF_CAN_413_PASSWORD_16							         ( 42 )
#define DEF_CAN_413_PASSWORD_17							         ( 49 )
#define DEF_CAN_413_PASSWORD_18							         ( 56 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	uint8_t			ucPassword10;		/*Bit 0-6   */
	uint8_t			ucPassword11;		/*Bit 7-13  */
	uint8_t			ucPassword12;		/*Bit 14-20  */
	uint8_t			ucPassword13;		/*Bit 21-27  */
	uint8_t			ucPassword14;		/*Bit 28-34  */
	uint8_t			ucPassword15;		/*Bit 35-41  */
	uint8_t			ucPassword16;		/*Bit 42-48  */
	uint8_t			ucPassword17;		/*Bit 49-55  */
	uint8_t			ucPassword18;		/*Bit 56-62  */
	
}c413StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit413CanImage( void );

/**
* @brief		get the 413 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan413( CAN_FRAME *pCan);

/**
* @brief		set the 413 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan413( CAN_FRAME *pCan);


/**
* @brief		encode the 413 CAN message
* @param[in]	c413Status1Definition_t: pointer to the 412 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan413Encode( c413StatusDefinition_t *c413StatusDefinition  );

/**
* @brief		encode the 413 CAN message
* @param[in]	c413Status1Definition_t: pointer to the 413 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan413Decode( c413StatusDefinition_t *c413StatusDefinition );


#endif /* CAN413PACKET_H_ */