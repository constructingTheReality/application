/**
* @file 		GlueCurrentSensing.c
* @brief		GlueCurrentSensing source file.
* @author		juan andres
* @date			Created on 2021- 03 -11
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "glue.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

eMpbError_t eCurrentSensingAnalogReadmV( handle_t xStream, float *pfVoltage, uint16_t *usPowerRaw)
{
	int32_t slAdcVoltage;
	uint16_t usRaw;
	
	eMpblibsAnalogReadmV( xStream, &slAdcVoltage , &usRaw );
	
	/* Need one operand to be a float, the other will be promoted */
	*pfVoltage = ( ( ( float ) slAdcVoltage ) ) ; /// CURRENT_SENSING_OP_AMP_GAIN );
	*usPowerRaw = usRaw;
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/

eMpbError_t eCurrentSensingPowerAnalogReadmV( handle_t xStream, float *pfVoltage , uint16_t *pRawData )
{
	int32_t slAdcVoltage;
	 uint16_t pRaw;
	
	eMpblibsAnalogReadmV( xStream, &slAdcVoltage, &pRaw );
	
	/* Need one operand to be a float, the other will be promoted */
	*pfVoltage = ( ( ( float ) slAdcVoltage ) ) ; /// CURRENT_SENSING_OP_AMP_GAIN );
	*pRawData = pRaw;
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/
