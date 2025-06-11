/**
* @file 		controlLaserPIDUtil.c
* @brief		controlLaserPIDUtil.c source file
* @author		juan andres
* @date			Created on 2021-03-11
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
#include "ControlLaserPIDUtil.h"
/* Private define ----------------------------------------------------------- */

#define PID_SATURATION_ENABLE                               ( eTrue )
#define PID_ANTIWINDUP_CLAMPING_ENABLE                      ( eTrue )
#define		CURRENT_INCREASE_BY_STEP_IN_W  ( 0.03 ) 
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void vControlLaserPIDUtilInit( float fPGain, float fIGain, float fDGain, float fMinimum, float fMaximum, uint32_t ulAccLoopControlInterval, xPIDConfig_t *pxPIDConfig )
{
	eMpbError_t eMpbError;

	eMpbError = eMpbControlPIDInit( fPGain, fIGain, fDGain, fMinimum, fMaximum, PID_SATURATION_ENABLE, PID_ANTIWINDUP_CLAMPING_ENABLE, ulAccLoopControlInterval, pxPIDConfig );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
}
/*----------------------------------------------------------------------------*/

void vControlLaserPIDUtilReset( xPIDConfig_t *pxPIDConfig )
{
	eMpbError_t eMpbError;
	
	eMpbError = eMpbControlPIDReset( pxPIDConfig );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
}
/*----------------------------------------------------------------------------*/
void vControlLaserPIDCalcul( float fReference, float fReferenceFeedback, xPIDConfig_t *pxPIDConfig, float *pfPIDOutput )
{
	eMpbError_t eMpbError;
	float fPIDError;
	
	/* Calculate Error */
	fPIDError = ( fReference - fReferenceFeedback );
//	fPIDError = 1023 *fPIDError / CURRENT_INCREASE_BY_STEP_IN_W;
	/* Apply PID */
	eMpbError = eMpbControlPIDCalcul( fPIDError, pxPIDConfig, pfPIDOutput );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
}

/*----------------------------------------------------------------------------*/
