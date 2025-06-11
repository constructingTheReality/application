/**
* @file 		thermistorCircuitUtil.c
* @brief			
* @author		juan Andres Castano Ing.
* @date			Created on 2022-3-9
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/

/* Includes ----------------------------------------------------------------- */
#include "thermistorCircuitUtil.h"
#include "mpbMath.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

eMpbError_t eThermistorCircuitUtilGetThermistanceValue( handle_t xStream, xThermistorCircuitConfig_t xThermistorCircuitConfig, uint32_t *pulThermistance , uint16_t *pRawData )
{
	eMpbError_t eMpbError;
	uint16_t 	usVoltage;

	if(pulThermistance == NULL)
	{
		return eInvalidParameter;
	}
		
  /* Validate parameter */
  vMpblibsAssertParam( pulThermistance );
		
	/* Get thermistor voltage */
	eMpbError = eThermistorAnalogReadmV( xStream, &usVoltage, pRawData );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	/* calculate the thermistance via de Norton equivalent */
	
	eMpbError = eMpbMathDivisionU32( ( usVoltage * xThermistorCircuitConfig.ulSeriesResistor1 ), ( xThermistorCircuitConfig.usReferenceVoltagemV - usVoltage ), pulThermistance );
	
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	return eMpbError;
}

/*----------------------------------------------------------------------------*/

