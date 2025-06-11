/**
* @file			can405Packet.h
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

#ifndef CAN405PACKET_H_
#define CAN405PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define DEF_CAN_0405_COMPANY						             0
#define DEF_CAN_0405_SERIAL_NUMBER					             4
#define DEF_CAN_0405_MAJOR_SERIAL_VERSION			             28
#define DEF_CAN_0405_MINOR_SERIAL_VERSION			             32
#define DEF_CAN_0405_PATCH_SERIAL_VERSION			             36
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	uint8_t						ucIdCompany;					/*Bit 0-3: mpb id number  */
	uint32_t					ulUnitSerialNumber;				/*Bit 4-27:  serial number  */
	uint8_t						ucFirmwareVersionMajor;			/*Bit 28-31: major  */
	uint8_t						ucFirmwareVersionMinor;			/*Bit 32-35: minor */
	uint8_t						ucFirmwareVersionPatch;			/*Bit 36-44: patch */
	uint8_t						ucParameter1;					
	uint8_t						ucParameter2;					
	uint8_t						ucParameter3;						
}c405Definition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit405CanImage( void );

/**
* @brief		get the 405 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan405( CAN_FRAME *pCan);

/**
* @brief		set the 405 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan405( CAN_FRAME *pCan);


/**
* @brief		decode the 405 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan4054Decode( c405Definition_t *c405Definition );

/**
* @brief		encode the 404 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan405Encode( c405Definition_t *c405Definition );




#endif /* CAN405PACKET_H_ */