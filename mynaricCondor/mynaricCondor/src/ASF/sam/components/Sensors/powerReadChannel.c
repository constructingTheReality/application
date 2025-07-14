/**
* @file 		powerReadChannel.c
* @brief		powerReadChannel.c source file
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
#include "powerReadChannel.h"


xPowerInputScaling_t *pxLocalPowerInputScaling = NULL;


/*-----------------------------------------------------------------------*/
eMpbError_t ePowerReadOffsetChannelRun( uint16_t *pusInternalOffset, uint16_t *pusExternalOffset , uint16_t *pusExternalOffset1  )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	eBool_t bPointersAreValid = eFalse ;
	uint16_t usOffset = 0;
	
	bPointersAreValid = (pusInternalOffset != NULL) && (pusExternalOffset != NULL) && (pusExternalOffset1 != NULL)  ;
	
	if( bPointersAreValid == eTrue )
	{
		float fPowerReaded;
		xPowerInputScaling_t xPowerInputScaling ;
	
		xPowerInputScaling.fSlope = 1.0;
		xPowerInputScaling.fIntercept = 0.0;
		eMpbError =  eCurrentSensingGetPowermW( eHandleAdcPdReference, xPowerInputScaling.fSlope,xPowerInputScaling.fIntercept , &fPowerReaded,  &usOffset );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		*pusInternalOffset  = usOffset;
		
		eMpbError =  eCurrentSensingGetPowermW( eHandleExternalPd_ref1, xPowerInputScaling.fSlope,xPowerInputScaling.fIntercept,  &fPowerReaded, &usOffset );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		*pusExternalOffset1  = usOffset;
		
		eMpbError =  eCurrentSensingGetPowermW( eHandleExternalPd_Ref, xPowerInputScaling.fSlope,xPowerInputScaling.fIntercept , &fPowerReaded, &usOffset );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		*pusExternalOffset  = usOffset;
		
		
	}
	
	return eMpbError;	
}
/*-----------------------------------------------------------------------*/
eMpbError_t ePowerReadChannelRun(handle_t xStream, uint16_t usOffset, float fSlope, float fIntercept, float *pfPowerReaded, uint16_t *pusPowerRaw)
{
	
	eMpbError_t eMpbError = eSuccess;
	//float fPowerReaded =0.0f;
	
		
	xStream = 	xStream + eHandleAdcPdReference;
		
	eMpbError =  eCurrentSensingGetPowermWOffset( xStream, fSlope, fIntercept, usOffset , pfPowerReaded ,  pusPowerRaw);
	
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	return eMpbError;
	
}