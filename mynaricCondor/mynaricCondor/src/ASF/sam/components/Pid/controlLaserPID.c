/**
* @file 		controlLaserPID.c
* @brief		controlLaserPID.c source file
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
#include "ControlLaserPID.h"
#include "ControlLaserPIDUtil.h"

#include "projectDef.h"

/* Private define ----------------------------------------------------------- */

#define CONTROLLER_PROPORTIONAL_GAIN	        ( 1.862f )
#define CONTROLLER_INTEGRAL_GAIN				      ( 66.91f )
#define CONTROLLER_DERIVATIVE_GAIN				    ( 0.0129f )

#define MINIMUM_DEMAND_PERCENTAGE				( -4093 )           /* % */
#define MAXIMUM_DEMAND_PERCENTAGE				( 4093 )         /* % */

#define MINIMUM_FEEDBACK_PERCENTAGE				( 0 )           /* % */
#define MAXIMUM_FEEDBACK_PERCENTAGE				( 50 )         /* % */

#define MIN_THRESHOLD_MM1_MA				( 640 )   
#define MIN_THRESHOLD_MM2_MA				( 700 )   

#define PID_CONFIG_NUMBER_OF_CHANNELS							( eNumberOfPidChannelConfigurations )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/**
* @brief    Create the pid config variables.
*/
#define X( PIDID, PIDConfigID, kp, ki, kd )                     \
	static  xPIDConfig_t PIDConfigID;               
    PID_LIST
#undef X

        
static const float fProportionalFactorConstant[ PID_CONFIG_NUMBER_OF_CHANNELS ] =
{   
#define X( PIDID, PIDConfigID, kp, ki, kdr )	kp,
        PID_LIST 
#undef X
};

static const float fIntegralFactorConstant[ PID_CONFIG_NUMBER_OF_CHANNELS ] =
{   
#define X( PIDID, PIDConfigID, kp, ki, kd )	ki,
        PID_LIST 
#undef X
};

static const float fDerivativeFactorConstant[ PID_CONFIG_NUMBER_OF_CHANNELS ] =
{   
#define X( PIDID, PIDConfigID, kp, ki, kd )	kd,
        PID_LIST 
#undef X
};


static uint16_t usMinCurrentforMm1_mA = (uint16_t)MIN_THRESHOLD_MM1_MA;
static uint16_t usMinCurrentforMm2_mA = (uint16_t)MIN_THRESHOLD_MM2_MA;

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
        
/**
* @brief        Calcul the PID output.
* @param[in]    fReference: The reference.
* @param[in]    fReferenceFeedback: The reference feedback. 
* @param[in]    pxPIDConfig: The PID configuration.
* @param[out]   pfPIDOutput: The PID output.
*/
//static void vprvControlLaserPIDCalcul( float fReference, float fReferenceFeedback, xPIDConfig_t *pxPIDConfig, float *pfPIDOutput );

/* Private functions -------------------------------------------------------- */

void vSetLnaPidDefaultValues(void)
{
	xprvLnaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eLnaLaserSingleModePowerLoopPID ];
	xprvLnaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eLnaLaserSingleModePowerLoopPID ];
	xprvLnaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eLnaLaserSingleModePowerLoopPID ];
	
	vUpdateLnaPIDValues(xprvLnaSingleModeLaserPowerLoopPIDConfig.fProportionalGain, xprvLnaSingleModeLaserPowerLoopPIDConfig.fIntegralGain,	xprvLnaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain );	
}

void vSetHpaPidDefaultValues(void)
{
	
	//xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserSingleModePowerLoopPID ];
	//xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserSingleModePowerLoopPID ];
	//xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserSingleModePowerLoopPID ];
	
	
	xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserSingleModePowerLoopPID ];
	xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserSingleModePowerLoopPID ];
	xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserSingleModePowerLoopPID ];
	vUpdateHpaSmPIDValues(xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain, xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain );		
		
	xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserMultiMode1PowerLoopPID ];
	xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserMultiMode1PowerLoopPID ];
	xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserMultiMode1PowerLoopPID ];
	vUpdateHpaMm1PIDValues(xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain );	
		
	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserMultiMode2PowerLoopPID ];
	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserMultiMode2PowerLoopPID ];
	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserMultiMode2PowerLoopPID ];
	vUpdateHpaMm2PIDValues(xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain );	

	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserMultM1and2PowerLoopPID ];
	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserMultM1and2PowerLoopPID ];
	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserMultM1and2PowerLoopPID ];
	
	
	usMinCurrentforMm1_mA = (uint16_t)MIN_THRESHOLD_MM1_MA;
	usMinCurrentforMm2_mA = (uint16_t)MIN_THRESHOLD_MM2_MA;
	
	vUpdateHpaMm1and2PIDValues(xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain);


	
}


void vSetHpaPidNvmValues( )
{
	float fHpaSingleProportional = 0.0f;
	float fHpasingleIntegralGain = 0.0f;
	float fHpasingleDerivativeGain = 0.0f;
	
	vUploadHpaSmPIDValues( &fHpaSingleProportional, &fHpasingleIntegralGain, &fHpasingleDerivativeGain  );
	
	xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     fHpaSingleProportional;
	xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			= fHpasingleIntegralGain;
	xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		= fHpasingleDerivativeGain;
	
	
/*	xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserMultiMode1PowerLoopPID ];
	xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserMultiMode1PowerLoopPID ];
	xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserMultiMode1PowerLoopPID ];
	vUpdateHpaMm1PIDValues(xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain );
	
	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserMultiMode2PowerLoopPID ];
	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserMultiMode2PowerLoopPID ];
	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserMultiMode2PowerLoopPID ];
	vUpdateHpaMm2PIDValues(xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain );

	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain 	=     fProportionalFactorConstant[ eHpaLaserMultM1and2PowerLoopPID ];
	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain 			=     fIntegralFactorConstant[ eHpaLaserMultM1and2PowerLoopPID ];
	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain 		=     fDerivativeFactorConstant[ eHpaLaserMultM1and2PowerLoopPID ];
	
	vUpdateHpaMm1and2PIDValues(xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain );
*/
}
void vSetPidValues( handle_t eBeacon_Id, float kp, float ki, float kd  )
{
	
	if( eBeacon_Id == eLnaLaserSingleModePowerLoopPID )
	{		
		xprvLnaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     kp ; 
		xprvLnaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvLnaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     kd;
		
		vUpdateLnaPIDValues(xprvLnaSingleModeLaserPowerLoopPIDConfig.fProportionalGain, xprvLnaSingleModeLaserPowerLoopPIDConfig.fIntegralGain,	xprvLnaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain);
	}
	else if( eBeacon_Id == eHpaLaserSingleModePowerLoopPID)
	{
		xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
		
		vUpdateHpaSmPIDValues(xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain, xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain);
	}
	
	else if( eBeacon_Id == eHpaLaserMultiMode1PowerLoopPID)
	{
		xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
		
		vUpdateHpaMm1PIDValues(xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain);
	}	
	
	else if( eBeacon_Id == eHpaLaserMultiMode2PowerLoopPID)
	{
		xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
		
		vUpdateHpaMm2PIDValues(xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain);
	}
	else if( eBeacon_Id == eHpaLaserMultM1and2PowerLoopPID)
	{
		xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
			
		vUpdateHpaMm1and2PIDValues(xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain, xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain,	xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain);
	}	
	
	
	
}


void vSetInternalPidValues( handle_t eBeacon_Id, float kp, float ki, float kd  )
{
	
	if( eBeacon_Id == eLnaLaserSingleModePowerLoopPID )
	{		
		xprvLnaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     kp ; 
		xprvLnaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvLnaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     kd;
	}
	else if( eBeacon_Id == eHpaLaserSingleModePowerLoopPID)
	{
		xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
	}
	else if( eBeacon_Id == eHpaLaserMultiMode1PowerLoopPID)
	{
		xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
	}
	else if( eBeacon_Id == eHpaLaserMultiMode2PowerLoopPID)
	{
		xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
	}
	
	else if( eBeacon_Id == eHpaLaserMultM1and2PowerLoopPID)
	{
		xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain 	=     kp;
		xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain 			=     ki;
		xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain 		=     kd ;
	}
	
	
	
	
}


void vGetPidValues( handle_t eBeacon_Id, float *kp, float *ki, float *kd  )
{
	
	if( eBeacon_Id == eLnaLaserSingleModePowerLoopPID )
	{		
		*kp = xprvLnaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	 ; 
		*ki = xprvLnaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			 ;
		*kd = xprvLnaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		;
	}
	else if( eBeacon_Id == eHpaLaserSingleModePowerLoopPID)
	{
		*kp = xprvHpaSingleModeLaserPowerLoopPIDConfig.fProportionalGain 	;
		*ki = xprvHpaSingleModeLaserPowerLoopPIDConfig.fIntegralGain 			;
		*kd = xprvHpaSingleModeLaserPowerLoopPIDConfig.fDerivativeGain 		;
	}
		else if( eBeacon_Id == eHpaLaserMultiMode1PowerLoopPID)
		{
			*kp = xprvHpaMultimode1LaserPowerLoopPIDConfig.fProportionalGain 	;
			*ki = xprvHpaMultimode1LaserPowerLoopPIDConfig.fIntegralGain 			;
			*kd = xprvHpaMultimode1LaserPowerLoopPIDConfig.fDerivativeGain 		;
		}
	else if( eBeacon_Id == eHpaLaserMultiMode2PowerLoopPID)
	{
		*kp = xprvHpaMultimode2_LaserPowerLoopPIDConfig.fProportionalGain 	;
		*ki = xprvHpaMultimode2_LaserPowerLoopPIDConfig.fIntegralGain 			;
		*kd = xprvHpaMultimode2_LaserPowerLoopPIDConfig.fDerivativeGain 		;
	}
	
	else if( eBeacon_Id == eHpaLaserMultM1and2PowerLoopPID)
	{
		*kp = xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fProportionalGain 	;
		*ki = xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fIntegralGain 			;
		*kd = xprvHpaMultimode1and2LaserPowerLoopPIDConfig.fDerivativeGain 		;
	}		
	
}



/* Exported functions ------------------------------------------------------- */

void vControlLaserPIDInit( ePIDID_t ePIDID,  uint32_t ulAccLoopControlInterval, xPidValues_t *pxPidValues )
{
    float fPGain, fIGain, fDGain;

    switch( ePIDID )
    {
        case eLnaLaserSingleModePowerLoopPID:
        {					  					  
			fPGain = pxPidValues->fPGain ; 
			fIGain = pxPidValues->fIGain ; 
			fDGain = pxPidValues->fDGain ; 
					
            vControlLaserPIDUtilInit( fPGain, fIGain, fDGain, -MAXIMUM_DEMAND_PERCENTAGE, MAXIMUM_DEMAND_PERCENTAGE, ulAccLoopControlInterval, &xprvLnaSingleModeLaserPowerLoopPIDConfig );          
        }
        break;        

		case eHpaLaserSingleModePowerLoopPID:
        {
			fPGain = pxPidValues->fPGain 	;
			fIGain = pxPidValues->fIGain 			;
			fDGain = pxPidValues->fDGain 		;
            vControlLaserPIDUtilInit( fPGain, fIGain, fDGain, -MAXIMUM_DEMAND_PERCENTAGE, MAXIMUM_DEMAND_PERCENTAGE, ulAccLoopControlInterval, &xprvHpaSingleModeLaserPowerLoopPIDConfig );          
        }
        break;
		
		case eHpaLaserMultiMode1PowerLoopPID:
		{
			fPGain = pxPidValues->fPGain 	;
			fIGain = pxPidValues->fIGain 			;
			fDGain = pxPidValues->fDGain 		;
			vControlLaserPIDUtilInit( fPGain, fIGain, fDGain, -MAXIMUM_DEMAND_PERCENTAGE, MAXIMUM_DEMAND_PERCENTAGE, ulAccLoopControlInterval, &xprvHpaMultimode1LaserPowerLoopPIDConfig );
		}
		break;
		
		case eHpaLaserMultiMode2PowerLoopPID:
		{
			fPGain = pxPidValues->fPGain 	;
			fIGain = pxPidValues->fIGain 			;
			fDGain = pxPidValues->fDGain 		;
			vControlLaserPIDUtilInit( fPGain, fIGain, fDGain, -MAXIMUM_DEMAND_PERCENTAGE, MAXIMUM_DEMAND_PERCENTAGE, ulAccLoopControlInterval, &xprvHpaMultimode2_LaserPowerLoopPIDConfig );
		}
		break;
		
		
		case eHpaLaserMultM1and2PowerLoopPID:
		{
			fPGain = pxPidValues->fPGain 	;
			fIGain = pxPidValues->fIGain 			;
			fDGain = pxPidValues->fDGain 		;
			vControlLaserPIDUtilInit( fPGain, fIGain, fDGain, -MAXIMUM_DEMAND_PERCENTAGE, MAXIMUM_DEMAND_PERCENTAGE, ulAccLoopControlInterval, &xprvHpaMultimode1and2LaserPowerLoopPIDConfig );
		}
		break;
								

        default:
        {
            vMpblibsAssertParam( 0 );
        }
        break;
    }

}
/*----------------------------------------------------------------------------*/

void vControlLaserPIDReset( ePIDID_t ePIDID )
{
    switch( ePIDID )
    {
        case eLnaLaserSingleModePowerLoopPID:
        {
            vControlLaserPIDUtilReset( &xprvLnaSingleModeLaserPowerLoopPIDConfig );
            
        }
        break;
        case eHpaLaserSingleModePowerLoopPID:
        {
            vControlLaserPIDUtilReset( &xprvHpaSingleModeLaserPowerLoopPIDConfig );
        }
        break;
		
		case eHpaLaserMultiMode1PowerLoopPID:
		{
			vControlLaserPIDUtilReset( &xprvHpaMultimode1LaserPowerLoopPIDConfig );
		}
		break;
		
		case eHpaLaserMultiMode2PowerLoopPID:
		{
			vControlLaserPIDUtilReset( &xprvHpaMultimode2_LaserPowerLoopPIDConfig );
		}
		break;
		
		case eHpaLaserMultM1and2PowerLoopPID:
		{
			vControlLaserPIDUtilReset( &xprvHpaMultimode1and2LaserPowerLoopPIDConfig );
		}
		break;
				
		
		
        default:
        {
            vMpblibsAssertParam( 0 );
        }
        break;
    }
}
/*----------------------------------------------------------------------------*/
eBool_t bControlLaserDeltaTimeHasChanged( ePIDID_t ePIDID, uint32_t ulDeltaTime ) 
{
	eBool_t eBool = eFalse;
	
	switch( ePIDID )
    {
				case eLnaLaserSingleModePowerLoopPID:
        {
					if( xprvLnaSingleModeLaserPowerLoopPIDConfig.ulDeltaTime != ulDeltaTime )
					{
						eBool = eTrue;
					}
          
        }
        break;
				
        case eHpaLaserSingleModePowerLoopPID:
        {
					if( xprvHpaSingleModeLaserPowerLoopPIDConfig.ulDeltaTime != ulDeltaTime )
					{
						eBool = eTrue;
					}
          
        }
        break;
		

        case eHpaLaserMultiMode1PowerLoopPID:
        {
	        if( xprvHpaMultimode1LaserPowerLoopPIDConfig.ulDeltaTime != ulDeltaTime )
	        {
		        eBool = eTrue;
	        }
	        
        }
        break;


        case eHpaLaserMultiMode2PowerLoopPID:
        {
	        if( xprvHpaMultimode2_LaserPowerLoopPIDConfig.ulDeltaTime != ulDeltaTime )
	        {
		        eBool = eTrue;
	        }
	        
        }
        break;
		
		case eHpaLaserMultM1and2PowerLoopPID:
		{
		    if( xprvHpaMultimode1and2LaserPowerLoopPIDConfig.ulDeltaTime != ulDeltaTime )
		    {
		        eBool = eTrue;
		      }
			        
        }
        break;
		
		
		
        default:
        {
            vMpblibsAssertParam( 0 );
        }
        break;
    }
	
	return eBool;
}
/*----------------------------------------------------------------------------*/
void vControlLaserPIDUpdate( float fReference, float fReferenceFeedback , uint8_t eBeaconId, float *pfControlCurrent)
{
	float fOutputControlSignal;
    float fCurrent;
	static uint16_t usCount = 0;
	static float fCopyReferenceFeedback = 0.0f;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	

	if ( eBeaconId == eLnaSingleMode)
	{
		vControlLaserPIDCalcul( fReference, fReferenceFeedback, &xprvLnaSingleModeLaserPowerLoopPIDConfig, &fOutputControlSignal );	
		
		fOutputControlSignal = fOutputControlSignal/ 7.04 ; // * 0.14 + 9./ 7.04 ; //pwm to mA  --> 4093 / 581
				
		if(fOutputControlSignal > 40 )  ///steps
		{
			fOutputControlSignal = 40;
		}
				
		if(fOutputControlSignal < (-40 )  )
		{
				fOutputControlSignal = -40;
		}
				

		fOutputControlSignal =pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent  + fOutputControlSignal;
				
				
		fCurrent = fOutputControlSignal ;//+ flowCurrent;

		if(fCurrent < 0)
		{
			fCurrent =0;
		}
				//580 / 4093 = 0.1417 mA.
		eCurrentControlUpdateLna(  fCurrent ) ;
	}
	else if ( eBeaconId == eHpaSingleMode)
	{
		vControlLaserPIDCalcul( fReference, fReferenceFeedback, &xprvHpaSingleModeLaserPowerLoopPIDConfig, &fOutputControlSignal );	
		
		
		
		if(fOutputControlSignal > CURRENT_INCREASE_BY_STEP_IN_MA_SM_HPA )  
		{
			fOutputControlSignal = CURRENT_INCREASE_BY_STEP_IN_MA_SM_HPA;
		}
		
		if(fOutputControlSignal < (-CURRENT_INCREASE_BY_STEP_IN_MA_SM_HPA )  )
		{
			fOutputControlSignal = -CURRENT_INCREASE_BY_STEP_IN_MA_SM_HPA;
		}
		
		
		fOutputControlSignal = pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent  + fOutputControlSignal;
		if(fOutputControlSignal < 0)
		{
			fOutputControlSignal =0;
		}
		eCurrentControlUpdateHpa1(  fOutputControlSignal ) ;
		
		
	}
	else if ( eBeaconId == eHpaMultiMode1)
	{
		vControlLaserPIDCalcul( fReference, fReferenceFeedback, &xprvHpaMultimode1LaserPowerLoopPIDConfig, &fOutputControlSignal );
		
		if(fOutputControlSignal > CURRENT_INCREASE_BY_STEP_IN_MA_HPA )  ///steps
		{
			fOutputControlSignal = CURRENT_INCREASE_BY_STEP_IN_MA_HPA;
		}
			
		if(fOutputControlSignal < (-CURRENT_INCREASE_BY_STEP_IN_MA_HPA )  )
		{
			fOutputControlSignal = -CURRENT_INCREASE_BY_STEP_IN_MA_HPA;
		}	
		
		
		fCurrent = pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent;
		
		if( fOutputControlSignal>0)// &&)
		{	
			if( fCurrent < usMinCurrentforMm1_mA )
			{
				fOutputControlSignal =  usMinCurrentforMm1_mA;	
			}
			 		
			/*if (fCopyReferenceFeedback == 100*fReferenceFeedback)
			{
				usCount = usCount + 10;
				fOutputControlSignal = fOutputControlSignal + usCount;	
			}
			else
			{
				usCount = 0;
			}*/
			
		}
		
		fOutputControlSignal = fCurrent + fOutputControlSignal;
		
		if(fOutputControlSignal < 0)
		{
			fOutputControlSignal =0;
		}
        
     	if( fOutputControlSignal > 5000 )
	    {
		    fOutputControlSignal = 5000;
	    }
		eCurrentControlUpdateMmHpa1(  fOutputControlSignal ) ;	
		*pfControlCurrent =		fOutputControlSignal;
		
	}
	 
	else if ( eBeaconId == eHpaMultiMode2)
	{
		vControlLaserPIDCalcul( fReference, fReferenceFeedback, &xprvHpaMultimode2_LaserPowerLoopPIDConfig, &fOutputControlSignal );
		
		if(fOutputControlSignal > CURRENT_INCREASE_BY_STEP_IN_MA_HPA )  ///steps
		{
			fOutputControlSignal = CURRENT_INCREASE_BY_STEP_IN_MA_HPA;
		}
		
		if(fOutputControlSignal < (-CURRENT_INCREASE_BY_STEP_IN_MA_HPA )  )
		{
			fOutputControlSignal = -CURRENT_INCREASE_BY_STEP_IN_MA_HPA;
		}
		
		fCurrent = pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent;
		fOutputControlSignal = fCurrent + fOutputControlSignal;
		
	/*	if(fReferenceFeedback < 10)
		{
			usCount = usCount + 10;*/
			
			if( fOutputControlSignal < usMinCurrentforMm2_mA) 
			{
				
				fOutputControlSignal =  usMinCurrentforMm2_mA;
				
								
			}
			//fOutputControlSignal = fOutputControlSignal + usCount;
			
		/*}
		else
		{
			usCount  = 0;
		}*/
		
		
		
		
		
		
		
		/*if (fCurrent < 500)
		{
			fCurrent = 500;
		}
		fOutputControlSignal = fCurrent + fOutputControlSignal;*/
		if(fOutputControlSignal < 0)
		{
			fOutputControlSignal =0;
		}
		if( fOutputControlSignal > 5000 )
		{
			fOutputControlSignal = 5000;
		}
		//fOutputControlSignal = pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent  + fOutputControlSignal;
		eCurrentControlUpdateMmHpa2(  fOutputControlSignal ) ;
		*pfControlCurrent =		fOutputControlSignal;
	}
	else if ( eBeaconId == eHpaMultiMode1and2)
	{
		vControlLaserPIDCalcul( fReference, fReferenceFeedback, &xprvHpaMultimode1and2LaserPowerLoopPIDConfig, &fOutputControlSignal );
		
		if(fOutputControlSignal > CURRENT_INCREASE_BY_STEP_IN_MA_HPA )  ///steps
		{
			fOutputControlSignal = CURRENT_INCREASE_BY_STEP_IN_MA_HPA;
		}
		
		if(fOutputControlSignal < (-CURRENT_INCREASE_BY_STEP_IN_MA_HPA )  )
		{
			fOutputControlSignal = -CURRENT_INCREASE_BY_STEP_IN_MA_HPA;
		}
		
		fOutputControlSignal = pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent  + fOutputControlSignal;
		if(fOutputControlSignal < 0)
		{
			fOutputControlSignal =0;
		}
		
		eCurrentControlUpdateMmHpa1(  fOutputControlSignal ) ;
		eCurrentControlUpdateMmHpa2(  fOutputControlSignal ) ;
		*pfControlCurrent =		fOutputControlSignal;
		
	}
	
	
	
	/* Cast DAC */
	//if( fReference > fReferenceFeedback)
	//{
	//	fOutputControlSignal = 0;
	//}
	
/*	if( fOutputControlSignal < 0 )
	{
		fOutputControlSignal = 0;
	}*/
	
	// -100 100 % to 0...4093 pwm (current) 
	//   delta p = 0.021 mW for 10 ma steps 
	// 
	
	//fOutputControlSignal =  ( 50 * fOutputControlSignal / 0.03);
	
	//fReference = 100%
	// fcontrol   x 
	// 
//	fOutputControlSignal =  ( 100 * fOutputControlSignal / fReference);
	// X = fcontrol * 100 / fReference
	// convert power to current
	//  600 ma (probably 583)->   0.604 mw
	//    x                     fOutputControlSignal
	// x = fOutputControlSignal * 600 ma / 0.604   
//	fOutputControlSignal = fOutputControlSignal * xLnaParameters->xElectricLimits.fCurrentMaximum / xLnaParameters->xElectricLimits.fPowerMaximum ;
	
	//fOutputControlSignal = fOutputControlSignal * -58099990 + 581  ;
	
	
		//ePowerControlUpdate( fOutputControlSignal , eBeaconId) ;
		//add current output 
		


	
	
/*	if(APC_CONTROL_ENABLE)// DEBUG_PRINTS_POWER )
	{
		DAC_PowerPrint( fReference, fReferenceFeedback, fOutputControlSignal );
	}*/
	fCopyReferenceFeedback = 100 * fReferenceFeedback;
}
/*----------------------------------------------------------------------------*/


