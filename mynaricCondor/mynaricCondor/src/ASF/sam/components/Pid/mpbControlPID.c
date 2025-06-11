/**
  * @file 			mpbControlPID.c
  * @brief			mpbControlPID source file.
  * @author			juan andres
  * @date			Created on 3-23-2021
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
  
/* Includes ----------------------------------------------------------------- */

#include "mpbControlPID.h"

/* Private define ----------------------------------------------------------- */

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

eMpbError_t eMpbControlPIDInit( float fPGain, float fIGain, float fDGain, float fLowerLimit, float fUpperLimit, eBool_t bIsSaturationEnable, eBool_t bIsAntiWindupEnable, uint32_t ulDeltaTime, xPIDConfig_t *pxPIDConfig )
{
    if( ( pxPIDConfig == NULL ) || ( ulDeltaTime == 0 ) )
    {
        return eInvalidParameter;
    }
	
	/* to implement antiwindup, saturation must be enabled */
	if ( ( !bIsSaturationEnable ) && ( bIsAntiWindupEnable ) )
	{
		return eInvalidParameter;
	}
	
	if ( bIsSaturationEnable )
	{
		 /* Lower limit must be equal or lower than upper limit */
		if ( fLowerLimit > fUpperLimit )
		{
			return eInvalidParameter;
		}
		pxPIDConfig->fLowerSaturationLimit = fLowerLimit;
		pxPIDConfig->fUpperSaturationLimit = fUpperLimit;
	}
	else
	{
		pxPIDConfig->fLowerSaturationLimit = 0;
		pxPIDConfig->fUpperSaturationLimit = 0;
	}
	
    pxPIDConfig->fOldInput = 0;
    pxPIDConfig->fIError   = 0;
    pxPIDConfig->fProportionalGain = fPGain;
    pxPIDConfig->fIntegralGain     = fIGain;
    pxPIDConfig->fDerivativeGain   = fDGain;
    pxPIDConfig->ulDeltaTime       = ulDeltaTime;
    pxPIDConfig->bSaturationEnable = bIsSaturationEnable;
    pxPIDConfig->bAntiWindupEnable = bIsAntiWindupEnable;
	
    return eSuccess;
}
/*----------------------------------------------------------------------------*/

eMpbError_t eMpbControlPIDCalcul( float fInput, xPIDConfig_t *pxPIDConfig, float *pfOutput )
{
    float fPError;
    float fNewIError;
    float fDError;
	float fOutput;
	
    /* Validate entry parameters */
    if( ( pxPIDConfig == NULL ) || ( pfOutput == NULL ) )
    {
        return eInvalidParameter;
    }

    /* Calcul of PID controller's Proportional error */
    fPError = fInput;
    
    /* Calcul of PID controller's Integral error */
    vMpbControlPIDUtilCalculIError( pxPIDConfig->ulDeltaTime, fPError, pxPIDConfig->fIError, &fNewIError );
    
    /* Calcul of PID controller's Derivative error */
    vMpbControlPIDUtilCalculDError( pxPIDConfig->ulDeltaTime, fPError, pxPIDConfig->fOldInput, &fDError );

    /* Update variables */
    pxPIDConfig->fOldInput = fPError;
    
    /* Calcul Ouput */
    fOutput = ( ( pxPIDConfig->fProportionalGain * fPError ) + ( pxPIDConfig->fIntegralGain * fNewIError ) + ( pxPIDConfig->fDerivativeGain * fDError ) );
    
    /* Check for antiwindup, clamping, of integral error */
    if( pxPIDConfig->bAntiWindupEnable )
    {
        vMpbControlPIDUtilAntiWindupClamping( fPError, fNewIError, pxPIDConfig->fIError, fOutput, pxPIDConfig->fLowerSaturationLimit, pxPIDConfig->fUpperSaturationLimit, &( pxPIDConfig->fIError ), pfOutput ); 
    }
    else
    {
        /* Set new integral error */
        pxPIDConfig->fIError = fNewIError;
        
        /* Apply saturation */
        if( pxPIDConfig->bSaturationEnable )
        {
            vMpbControlPIDUtilSaturation( pxPIDConfig->fLowerSaturationLimit, pxPIDConfig->fUpperSaturationLimit, fOutput, pfOutput );
        }
        else
        {
            *pfOutput = fOutput;
        }
    }
    
	return eSuccess;
}
/*----------------------------------------------------------------------------*/

eMpbError_t eMpbControlPIDReset( xPIDConfig_t *pxPIDConfig )
{
    if( pxPIDConfig == NULL )
    {
        return eInvalidParameter;
    }
    
    pxPIDConfig->fOldInput = 0;
    pxPIDConfig->fIError   = 0;
    
    return eSuccess;
}
/*----------------------------------------------------------------------------*/
