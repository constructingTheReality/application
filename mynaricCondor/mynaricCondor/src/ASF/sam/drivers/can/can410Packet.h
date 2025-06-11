/**
* @file			can410Packet.h
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

#ifndef CAN410PACKET_H_
#define CAN410PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define DEF_CAN_410_COEFFICIENT_OPERATION				         ( 0 )
#define DEF_CAN_410_WRITE_VALUE_COEFFICIENT				         ( 10 )
#define DEF_CAN_410_NUMBER_COEFFICIENT				             ( 42 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef enum{
	DO_OPERATION_NOTHING = 0,
	WRITE_COEFFICIENT_TO_RAM = 1,
	READ_COEFFICIENT_TO_RAM = 2,
	READ_COEFFICIENT_TO_NVM = 3
	
}CoeficientOperation_t;
typedef struct
{
	CoeficientOperation_t		CoeficientOperation;		/*Bit 0-1:   */
	float						fWriteValueCoefficient;    /* 10..41 */
	uint16_t					usNumberCoefficient;	  /* 42..53 0..4095*/	
}c410StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit410CanImage( void );

/**
* @brief		get the 40A CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan410( CAN_FRAME *pCan);

/**
* @brief		set the 410 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan410( CAN_FRAME *pCan);


/**
* @brief		encode the 410 CAN message
* @param[in]	c410StatusDefinition_t: pointer to the 410 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan410Encode( c410StatusDefinition_t *c410StatusDefinition  );

/**
* @brief		encode the 410 CAN message
* @param[in]	c410StatusDefinition_t: pointer to the 410 message
* @return       Success or library error message
*/
eMpbError_t eMpbCan410Decode( c410StatusDefinition_t *c410StatusDefinition );


#endif /* CAN410PACKET_H_ */