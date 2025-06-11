/**
  * @file 			mpbControlPIDUtil.c
  * @brief			mpbControlPIDUtil source file.
  * @author			juan andres
  * @date			Created on 3-23-2021
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

#include "mpbControlPIDUtil.h"

/* Private define ----------------------------------------------------------- */

#define MILLISECOND_TO_SECOND		( 1000 )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void vMpbControlPIDUtilCalculIError( uint32_t ulDeltaTime, float fError, float fIErrorPID, float *pfNewIError )
{
	vMpblibsAssertParam( pfIError );
	vMpblibsAssertParam( ulDeltaTime );
	
	*pfNewIError = ( fIErrorPID + ( fError * ( ( float )ulDeltaTime / MILLISECOND_TO_SECOND ) ) );
}
/*----------------------------------------------------------------------------*/

void vMpbControlPIDUtilCalculDError( uint32_t ulDeltaTime, float fError, float fOldError, float *pfDError )
{
	vMpblibsAssertParam( pfDError );
	vMpblibsAssertParam( ulDeltaTime );
	
	*pfDError = ( ( fError - fOldError ) / ( ( float )ulDeltaTime / MILLISECOND_TO_SECOND ) );
}
/*----------------------------------------------------------------------------*/

void vMpbControlPIDUtilAntiWindupClamping( float fError, float fNewIError, float fCurrentIError, float fOutput, float fLowerLimit, float fUpperLimit, float *pfIErrorPID, float *pfSaturatedOutput )
{
    /* Positive saturation */
    if( fOutput > fUpperLimit )
    {
        /* Clamp the ouput */
       *pfSaturatedOutput = fUpperLimit;
       
       /* Error is the same sign? Inhibit integration */
       if( fError > 0 )
       {
           *pfIErrorPID = fCurrentIError;
       }
       else
       {
           *pfIErrorPID = fNewIError;
       }
    }
    /* Negative saturation */
    else if( fOutput < fLowerLimit )
    {
        /* Clamp the ouput */
        *pfSaturatedOutput = fLowerLimit;
        
        /* Error is the same sign? Inhibit integration */
        if( fError < 0 )
        {
            *pfIErrorPID = fCurrentIError;
        }
        else
        {
            *pfIErrorPID = fNewIError;
        }
    }
    /* No clamping required */
    else
    {
        *pfSaturatedOutput = fOutput;
        *pfIErrorPID = fNewIError;
    }
    
}
/*----------------------------------------------------------------------------*/

void vMpbControlPIDUtilSaturation( float fLowerLimit, float fUpperLimit, float fOutput,  float *pfSaturatedOutput )
{
	vMpblibsAssertParam( pfSaturatedOutput );
	vMpblibsAssertParam( pbIsOutputSaturated );
	
    if ( fOutput < fLowerLimit )
    {
        *pfSaturatedOutput = fLowerLimit;
    }
    else if ( fOutput > fUpperLimit )
    {
        *pfSaturatedOutput = fUpperLimit;
    }
    else
    {
        *pfSaturatedOutput = fOutput;
    }
}
/*----------------------------------------------------------------------------*/
