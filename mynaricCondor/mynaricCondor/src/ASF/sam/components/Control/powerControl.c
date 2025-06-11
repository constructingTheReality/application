/**
* @file 		powerControl.c
* @brief		powerControl.c source file
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
#include "powerControl.h"
#include "powerOutput.h"
#include "glue.h"
/* Private define ----------------------------------------------------------- */
#define CONTROL_POWER_CONFIG_NUMBER_OF_CHANNELS							( eNumberOfPowerChannelControlConfigurations )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static xPowerOutputScaling_t xPowerOutputScalingLnaSingleDiode;
//static xPowerOutputScaling_t xPowerOutputScalingHpaSingleDiode;


static void vPowerOutputConfigUpdate( void );

static const float fPowerControlSlopeScaleConstant[ CONTROL_POWER_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( PowerControlChannelConfigId, slopeConstant, interceptConstant, calibrationFactor )	slopeConstant,
	LIST_OF_POWER_CONTROL_CHANNELS
	#undef X
};

static const float fPowerControlInterceptScaleConstant[ CONTROL_POWER_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( PowerControlChannelConfigId, slopeConstant, interceptConstant, calibrationFactor )	interceptConstant,
	LIST_OF_POWER_CONTROL_CHANNELS
	#undef X
};

static const float fFactoryControlCalibration[ CONTROL_POWER_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( PowerControlChannelConfigId, slopeConstant, interceptConstant, calibrationFactor )	calibrationFactor,
	LIST_OF_POWER_CONTROL_CHANNELS
	#undef X
};

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

//		*pfSlope 			= xPowerOutputScaling1545Diode.fSlope;
//		*pfIntercep 	= xPowerOutputScaling1545Diode.fIntercept;
//		*pfGain 			= xPowerOutputScaling1545Diode.fCalibration;
//	}
//	else if( eBeaconId ==  e980Beacon )
//	{
//		*pfSlope 			= xPowerOutputScaling980Diode.fSlope;
//		*pfIntercep 	= xPowerOutputScaling980Diode.fIntercept;
//		*pfGain 			= xPowerOutputScaling980Diode.fCalibration;

static void vPowerOutputConfigUpdate( void )
{
	
	//	xLaserBeamDescriptor_t *pxLaserBeamDescriptor;
	//	pxLaserBeamDescriptor = vGetLaserBeams( );
	//
	//	if( (pxLaserBeamDescriptor->xPowerInputScaling1545.fIntercept == 0) &&
	//		  (pxLaserBeamDescriptor->xPowerOutputScaling1545Diode.fSlope == 0) &&
	//	    (pxLaserBeamDescriptor->xPowerOutputScaling1545Diode.fCalibration == 0 ) )
	//	{
	//			pxLaserBeamDescriptor->xCurrentOutput940.fIntercept = xPowerOutputScaling1545Diode.fIntercept 		;
	//	pxLaserBeamDescriptor->xCurrentOutput940.fSlope = xPowerOutputScaling1545Diode.fSlope     		;
	//	pxLaserBeamDescriptor->xCurrentOutput940.fCalibration = xPowerOutputScaling1545Diode.fCalibration  	;
	//		pxLaserBeamDescriptor->bExternalMemoryIsReadedAndHaveGoodData = eFalse;
	//	}
	//	else
	//	{
	//
	//	xCurrentOutputScaling940Diode.fIntercept 		= pxLaserBeamDescriptor->xCurrentOutput940.fIntercept;
	//	xCurrentOutputScaling940Diode.fSlope     		= pxLaserBeamDescriptor->xCurrentOutput940.fSlope;
	//	xCurrentOutputScaling940Diode.fCalibration  	= pxLaserBeamDescriptor->xCurrentOutput940.fCalibration;
	//
	//	}
	//
	//
	//	if( (pxLaserBeamDescriptor->xCurrentOutput1545.fIntercept == 0) &&
	//		  (pxLaserBeamDescriptor->xCurrentOutput1545.fSlope == 0) &&
	//	    (pxLaserBeamDescriptor->xCurrentOutput1545.fCalibration == 0 ) )
	//	{
	//		pxLaserBeamDescriptor->xCurrentOutput1545.fIntercept = 	xCurrentOutputScaling980Diode.fIntercept 		;
	//		pxLaserBeamDescriptor->xCurrentOutput1545.fSlope = xCurrentOutputScaling980Diode.fSlope     		;
	//		pxLaserBeamDescriptor->xCurrentOutput1545.fCalibration = xCurrentOutputScaling980Diode.fCalibration  	 ;
	//		pxLaserBeamDescriptor->bExternalMemoryIsReadedAndHaveGoodData = eFalse;
	//	}
	//	else
	//	{
	//	xCurrentOutputScaling980Diode.fIntercept 		= pxLaserBeamDescriptor->xCurrentOutput1545.fIntercept;
	//	xCurrentOutputScaling980Diode.fSlope     		= pxLaserBeamDescriptor->xCurrentOutput1545.fSlope;
	//	xCurrentOutputScaling980Diode.fCalibration  	= pxLaserBeamDescriptor->xCurrentOutput1545.fCalibration;
	//	}
}

void vPowerControlInit( void )
{
	//xPowerOutputScalingLnaSingleDiode.fCalibration = fFactoryControlCalibration[ eLnaSingleModeLaserDiodeControlPower ];;
	xPowerOutputScalingLnaSingleDiode.fIntercept 	= fPowerControlInterceptScaleConstant[ eLnaSingleModeLaserDiodeControlPower ];
	xPowerOutputScalingLnaSingleDiode.fSlope 			= fPowerControlSlopeScaleConstant[ eLnaSingleModeLaserDiodeControlPower ];
	
	/*xPowerOutputScaling980Diode.fCalibration = fFactoryControlCalibration[ e980MultiModeLaserDiodeControlPower ];;
	xPowerOutputScaling980Diode.fIntercept 	= fPowerControlInterceptScaleConstant[ e980MultiModeLaserDiodeControlPower ];
	xPowerOutputScaling980Diode.fSlope 			= fPowerControlSlopeScaleConstant[ e980MultiModeLaserDiodeControlPower ];
	*/
	
}
/*------------------------------------------------------------------------------*/
eMpbError_t ePowerControlUpdate( float fPowerControlSignal , eBeaconIdUsedActually_t eBeaconId )
{
	eMpbError_t eMpbError = eSuccess;
	float fVoltageconversionChannel_0 = 0.0f;
	float fLowVoltage = 0.0f;
	//	static float fLastPowerControlSignal = 0.0f;
	//xLaserBeamDescriptor_t *pxLaserBeamDescriptor;
	//pxLaserBeamDescriptor = vGetLaserBeams( );
	
	xLnaParameters_t * pxLnaParameters = NULL;
	xLnaParameters_t xLnaParametersl;
	pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl);
	
	
	//	if( fPowerControlSignal < 0)
	//	{
	//		fPowerControlSignal = fLastPowerControlSignal - fPowerControlSignal ;
	//
	//			if( fPowerControlSignal < 0)
	//			{
	//				fPowerControlSignal = 0;
	//			}
	//	}
	//xPowerOutputScalingLnaSingleDiode.fCalibration = pxLnaParameters.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fIntercept;
	xPowerOutputScalingLnaSingleDiode.fIntercept = pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fIntercept;
	xPowerOutputScalingLnaSingleDiode.fSlope = pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fSlope;
	
	/*xPowerOutputScaling980Diode.fCalibration = pxLaserBeamDescriptor->xCurrentOutput1545.fCalibration;
	xPowerOutputScaling980Diode.fIntercept = pxLaserBeamDescriptor->xCurrentOutput1545.fIntercept;
	xPowerOutputScaling980Diode.fSlope = pxLaserBeamDescriptor->xCurrentOutput1545.fSlope;*/
	if( eBeaconId == eLnaSingleMode)
	{
		//ePwmCurrentOutputSetPowermW
		//eMpbError_t ePwmCurrentOutputSetPowermW( handle_t xStream, xDutyCyclePowerOutputScaling_t xDutyCyclePowerOutputScaling, float fPower, uint32_t *pfDutyCycle  )
	}
	//if( ( pxLaserBeamDescriptor->xBeaconId == e980Beacon ) &&
	
	
	//if( pxLaserBeamDescriptor->xLaserOperationMode[e940Beacon - 1].bLaserIsEnable )
	//{
		//fLowVoltage = pxLaserBeamDescriptor->usLowCurrent[e940Beacon - 1];
		
		//fPowerControlSignal = ( fPowerControlSignal * pxLaserBeamDescriptor->xMaxSetpointsAllowed.sMaxSetpointCurrent940 ) / 100;

		//if( fPowerControlSignal < fLowVoltage)
		//{
		//	fPowerControlSignal = fPowerControlSignal + fLowVoltage;
		//}
		
		//	fLowVoltage = fLowVoltage * xPowerOutputScaling1545Diode.fSlope + xPowerOutputScaling1545Diode.fIntercept;
		
		//eMpbError = ePowerOutputSetPowermW( eHandleLnaOutputVoltage, xPowerOutputScalingLnaSingleDiode, fPowerControlSignal, fLowVoltage, &fVoltageconversionChannel_0  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		
	//}
	
	//if( eBeaconId ==  e980Beacon )
	/*if( pxLaserBeamDescriptor->xLaserOperationMode[e980Beacon - 1].bLaserIsEnable )
	{
		
		fPowerControlSignal = ( fPowerControlSignal * pxLaserBeamDescriptor->xMaxSetpointsAllowed.sMaxSetpointCurrent980 ) / 100;
		eMpbError = ePowerOutputSetPowermW( eHandle980OutputVoltage, xPowerOutputScaling980Diode, fPowerControlSignal, fLowVoltage, &fVoltageconversionChannel_0  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		
	}*/
	
	//fLastPowerControlSignal = fPowerControlSignal;
	
	return eMpbError;
}

/*---------------------------------------------------------------------------------*/

void vPowerControlgetOutputScalingValues ( float *pfSlope, float *pfIntercep, float *pfGain, eBeaconIdUsedActually_t eBeaconId )
{
	if( eBeaconId == eLnaSingleMode)
	{
		*pfSlope 			= xPowerOutputScalingLnaSingleDiode.fSlope;
		*pfIntercep 	= xPowerOutputScalingLnaSingleDiode.fIntercept;
		//*pfGain 			= xPowerOutputScalingLnaSingleDiode.fCalibration;
	}
	/*else if( eBeaconId ==  e980Beacon )
	{
		*pfSlope 			= xPowerOutputScaling980Diode.fSlope;
		*pfIntercep 	= xPowerOutputScaling980Diode.fIntercept;
		*pfGain 			= xPowerOutputScaling980Diode.fCalibration;
		
		
	}*/
	

}
/*--------------------------------------------------------------------------*/
void vPowerControlsetOutputScalingValues ( float fSlope, float fIntercep, float fGain, eBeaconIdUsedActually_t eBeaconId )
{
	//	xLaserBeamDescriptor_t *pxLaserBeamDescriptor;
	//pxLaserBeamDescriptor = vGetLaserBeams( );
	
	if( eBeaconId ==  eLnaSingleMode )
	{
		xPowerOutputScalingLnaSingleDiode.fSlope 				= fSlope;
		xPowerOutputScalingLnaSingleDiode.fIntercept 		= fIntercep;
		//xPowerOutputScaling1545Diode.fCalibration 	=  fGain;
	}
	/*else if( eBeaconId == e980Beacon)
	{
		xPowerOutputScaling980Diode.fSlope 				= fSlope;
		xPowerOutputScaling980Diode.fIntercept 		= fIntercep;
		xPowerOutputScaling980Diode.fCalibration 	=  fGain;
	}*/

	vPowerOutputConfigUpdate();
	
}
/*------------------------------------------------------------------------------*/
/*
eMpbError_t ePowerControlModulationLowLevelUpdate( void )
{
	eMpbError_t eMpbError;
	xLaserBeamDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetLaserBeams( );
	float fPowerControlSignal = 0.0f;
	float fVoltageconversionChannel_0 = 0.0f;
	float fLowVoltage = 0.0f;
	
	
	// 940 diode 
	if( pxLaserBeamDescriptor->xBeaconId == e940Beacon )
	{
		fPowerControlSignal = pxLaserBeamDescriptor->usLowCurrent[ e940Beacon - 1 ] ;
		fLowVoltage = pxLaserBeamDescriptor->usLowCurrent[  e940Beacon - 1 ];
		
		eMpbError = ePowerOutputSetPowermW( eHandle1545OutputVoltage, xPowerOutputScaling1545Diode, fPowerControlSignal, fLowVoltage, &fVoltageconversionChannel_0  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
	}
	else if( pxLaserBeamDescriptor->xBeaconId == e980Beacon )
	{
		fPowerControlSignal = pxLaserBeamDescriptor->usLowCurrent[ e980Beacon - 1 ] ;
		fLowVoltage = pxLaserBeamDescriptor->usLowCurrent[  e980Beacon - 1 ];
		
		eMpbError = ePowerOutputSetPowermW( eHandle980OutputVoltage, xPowerOutputScaling980Diode, fPowerControlSignal, fLowVoltage, &fVoltageconversionChannel_0  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		
	}
	return eMpbError;
}
*/
/*----------------------------------------------------------------------------*/



