/**
* @file			can414Packet.h
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

#ifndef CAN414PACKET_H_
#define CAN414PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define X1_414_BOOSTER_OPTICAL_INPUT_POWER						( -10.0)
#define Y1_414_BOOSTER_OPTICAL_INPUT_POWER						( 0.0)
#define X2_414_BOOSTER_OPTICAL_INPUT_POWER						( 6.0)
#define Y2_414_BOOSTER_OPTICAL_INPUT_POWER						( 1023.0)

#define X1_414_BOOSTER_OPTICAL_OUTPUT_POWER						( 16.0)
#define Y1_414_BOOSTER_OPTICAL_OUTPUT_POWER						( 1)
#define X2_414_BOOSTER_OPTICAL_OUTPUT_POWER						( 37.5)
#define Y2_414_BOOSTER_OPTICAL_OUTPUT_POWER						( 1023.0)

#define X1_414_LNA_OPTICAL_INPUT_POWER							( -50.0)
#define Y1_414_LNA_OPTICAL_INPUT_POWER							( 0.0)
#define X2_414_LNA_OPTICAL_INPUT_POWER							( -40.0)
#define Y2_414_LNA_OPTICAL_INPUT_POWER							( 1023.0)

#define X1_414_LNA_OPTICAL_OUTPUT_POWER							( -15.0)
#define Y1_414_LNA_OPTICAL_OUTPUT_POWER							( 1)
#define X2_414_LNA_OPTICAL_OUTPUT_POWER							( 0.0)
#define Y2_414_LNA_OPTICAL_OUTPUT_POWER							( 1023.0)

#define X1_414_UNIT_BASE_TEMPERATURE							( -40.0)
#define Y1_414_UNIT_BASE_TEMPERATURE							( 0.0)
#define X2_414_UNIT_BASE_TEMPERATURE							( 90.0 )
#define Y2_414_UNIT_BASE_TEMPERATURE							( 255.0)

#define X1_414_BACKFACET_MONITOR								( 0.0)
#define Y1_414_BACKFACET_MONITOR								( 0.0)
#define X2_414_BACKFACET_MONITOR								( 28.0 )
#define Y2_414_BACKFACET_MONITOR								( 255 )

#define DEF_CAN_414_BOOSTER_OPTICAL_INPUT_POWER            ( 0 )
#define DEF_CAN_414_BOOSTER_OPTICAL_OUTPUT_POWER           ( 10 )
#define DEF_CAN_414_LNA_OPTICAL_INPUT_POWER		           ( 20 )
#define DEF_CAN_414_LNA_OPTICAL_OUTPUT_POWER	           ( 30 )
#define DEF_CAN_414_UNIT_BASE_TEMPERATURE		           ( 40 )
#define DEF_CAN_414_BACKFACET_HPA_MONITOR		           ( 48 )
#define DEF_CAN_414_BACKFACET_LNA_MONITOR		           ( 56 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float						fBoostOpticalInputPower;			/*Bit 0-9 */
	float						fBoostOpticalOutputPower;			/*Bit 10-19 */
	float						fLnaOpticalInputtPower;				/*Bit 20-29 */
	float						fLnaOpticalOutputPower;				/*Bit 30-39 */
	float						fUnitBaseTemperature;				/*Bit 40-47 */
	float						fBackFacetHpaMonitorRaw ; 				/*Bit 48-55 */  //fPowerSupplyMonitor;
	float						fBackFacetLnaMonitorRaw ; 				/*/*Bit 56-63 */  
	
	
}c414StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit414CanImage( void );

/**
* @brief		get the 404 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan414( CAN_FRAME *pCan);

/**
* @brief		set the 414 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan414( CAN_FRAME *pCan);


/**
* @brief		decode the 414 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 404 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan414Decode( c414StatusDefinition_t *c414StatusDefinition );

/**
* @brief		encode the 414 CAN message
* @param[in]	c404StatusDefinition_t: pointer to the 414 mesage
* @param[in]	bBoosterIsDisable: bool  
* @param[in]	bLnaIsDisable: bool
* @return       Success or library error message
*/
eMpbError_t eMpbCan414Encode( c414StatusDefinition_t *c414StatusDefinition, eBool_t bBoosterIsDisable, eBool_t bLnaIsDisable );


#endif /* CAN414PACKET_H_ */