/**
* @file 		GlueCurrentOutput.c
* @brief		GlueCurrentOutput source file.
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

eMpbError_t eCurrentOutputAnalogWritemV( handle_t xStream, float fVoltage, float fLowVoltage )
{
	eMpbError_t eMpbError = eSuccess;
/*	
	eMpbError = eMpblibsAnalogModulationWritemV( xStream, (int32_t)fVoltage, (int32_t)fLowVoltage );
	
	//	extern eMpbError_t eMpblibsAnalogModulationWritemV( handle_t xANALOGx, int32_t lOutput, int32_t lLowOutput );
	*/
	return eMpbError;
}


eMpbError_t ePwmCurrentOutputAnalogWriteDuty( handle_t xStream, uint32_t ucDutyCycle )
{
	eMpbError_t eMpbError;
	eMpbError = eMpblibsAnalogWriteDutyCycle( xStream, ucDutyCycle ); 
	return eMpbError;
}
/*----------------------------------------------------------------------------*/


 
