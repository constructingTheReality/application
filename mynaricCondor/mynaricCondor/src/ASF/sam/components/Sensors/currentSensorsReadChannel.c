/**
* @file 		currentSensorsReadChannel.c
* @brief		currentSensorsReadChannel source file
* @author		juan andres
* @date			Created on 2024-05-30
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2024 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "currentSensorsReadChannel.h"

xCurrentInputScaling_t *pxLocalxCurrentInputScaling = NULL;

/*-----------------------------------------------------------------------*/
eMpbError_t eCurrentSensorsReadChannelRun(handle_t xStream, uint16_t usOffset, float fSlope, float fIntercept, float *pfCurrentReadedInMa, uint16_t *pusCurrentRaw)
{
	
	eMpbError_t eMpbError = eSuccess;
	//float fPowerReaded =0.0f;
		
	
	/* list 14  external 7 */
	if( xStream == eAdcExternalLnaSm_ld_Bfm)
	{
		eMpbError =  eCurrentSensingGetCurrentmAWithOffset( xStream, fSlope, fIntercept, usOffset ,  pfCurrentReadedInMa, pusCurrentRaw );
		
		
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}	
	}
	else
	{
		//list (internal) ch 0,1,2 , 3, 4, 5, 6 , 7, 8, 9, 10  , (external) list: 11, 12,13, 16,15
		eMpbError =  eCurrentSensingGetCurrentmA( xStream, fSlope, fIntercept, pfCurrentReadedInMa,pusCurrentRaw );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}		
	}	
	return eMpbError;	
}