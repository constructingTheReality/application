/**
* @file			can426Packet.h
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


#ifndef CAN426PACKET_H_
#define CAN426PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define DEF_MAX_NUMBER_OF_CHANNELS	            ( 23 )

#define DEF_CAN_426_INDEX		            ( 0 )
#define DEF_CAN_426_RAW_DATA				( 8 )


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	uint8_t			ucIndex;
	float			fRawData;
	uint8_t			usLnaState;
	uint8_t			usCommonState;
	uint8_t			usBoosterState;
	uint8_t			eHpaApcState;
	
}c426StatusDefinition_t;



/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit426CanImage( void );

/**
* @brief		get the 426 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan426( CAN_FRAME *pCan);

/**
* @brief		set the 426 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan426( CAN_FRAME *pCan);


/**
* @brief		decode the 426 CAN message
* @param[in]	c426StatusDefinition_t: pointer to the 423 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan426Decode( c426StatusDefinition_t *c426StatusDefinition );

/**
* @brief		encode the 426 CAN message
* @param[in]	c426StatusDefinition_t: pointer to the 426 mesage
* @param[in]	bBoosterIsDisable: bool
* @param[in]	bLnaIsDisable: bool
* @return       Success or library error message
*/
eMpbError_t eMpbCan426Encode( c426StatusDefinition_t *c426StatusDefinition);



#endif /* CAN426PACKET_H_ */