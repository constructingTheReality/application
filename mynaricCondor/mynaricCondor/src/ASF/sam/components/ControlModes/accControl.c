/**
* @file 		accControlLaser.c
* @brief		accControlLaser.c source file
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
#include "accControl.h"
#include "glue.h"
/* Private define ----------------------------------------------------------- */
#define ACC_ACCEPTABLE_ERROR 5  /* mV  */
#define ACC_STEPS_CONTROL_IN_MV 50  /* mV  */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
//static eAccLaserState_t eAccLaserState = eInitAccDetection;
/* Private function prototypes ---------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
/**
* @brief        Initalization of laser.
*/
void vAccControlLaserInit( void )
{
//	eAccLaserState = eInitAccDetection ;
}

/*----------------------------------------------------------------------------*/
void vAccControlLaserUpdateHpaSm1( float fCurrent )
{
	eCurrentControlUpdateHpa1( fCurrent );

}

void vAccControlLaserUpdateHpaMm1( float fCurrent )
{
	eCurrentControlUpdateMmHpa1( fCurrent );
}

void vAccControlLaserUpdateHpaMm2( float fCurrent )
{
	eCurrentControlUpdateMmHpa2( fCurrent );
}
/*----------------------------------------------------------------------------*/
void vAccControlLaserUpdateLna( float fCurrent )
{
//	uint32_t ulCurrent;
	uint32_t ulSetpoint;
//	eBeaconIdUsedActually_t eBeaconIdUsedActually;
	
//	xLaserBeamDescriptor_t *pxLaserBeamDescriptor;	
//	pxLaserBeamDescriptor = vGetLaserBeams( );
	
//	eBeaconIdUsedActually = (eBeaconIdUsedActually_t) ((pxLaserBeamDescriptor->xBeaconId) - 1);
	
//	if ( pxLaserBeamDescriptor->xBeaconId == e940Beacon )
//	{
		//ulCurrent = pxLaserBeamDescriptor->xCriticalAnalogCurrents.f940MultiModeLaserDiodeCurrent;
// 		//pxLaserBeamDescriptor->xCriticalAnalogCurrents.f940MultiModeLaserDiodeFakeCurrent = ulCurrent;
//	}
//	else
//	{
		//ulCurrent = pxLaserBeamDescriptor->xCriticalAnalogCurrents.f980SingleModeLaserDiodeCurrent;
		//pxLaserBeamDescriptor->xCriticalAnalogCurrents.f980SingleModeLaserDiodeFakeCurrent = ulCurrent;
//	}
	
//	ulSetpoint = 156; //pxLaserBeamDescriptor->xElectricalVariablesStatus[ eBeaconIdUsedActually ].usCurrentSetpoint ;
	//pxLaserBeamDescriptor->xElectricalVariablesStatus[ eBeaconIdUsedActually ].usActiveSetpoint = ulSetpoint ;
	
	/*  state machine for the acc control 
	if( pxLaserBeamDescriptor->eOperationMode[ eBeaconIdUsedActually ] == eAcc )
	{
		if ( eAccLaserState == eInitAccDetection )
		{
			if( ulCurrent > ( ulSetpoint + ACC_ACCEPTABLE_ERROR ) )
			{
					eAccLaserState = eDecreaseActiveSetpoint ;
			}
			else if ( ulCurrent < ( ulSetpoint - ACC_ACCEPTABLE_ERROR )  )
			{
					eAccLaserState = eIncreaseActiveSetpoint ;
			}
			
		}
		else if ( eAccLaserState == eIncreaseActiveSetpoint )
		{
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ eBeaconIdUsedActually ].usActiveSetpoint = (pxLaserBeamDescriptor->xElectricalVariablesStatus[ eBeaconIdUsedActually ].usActiveSetpoint) + ACC_STEPS_CONTROL_IN_MV;
			eAccLaserState = eInitAccDetection ;
		}
		else if ( eAccLaserState == eDecreaseActiveSetpoint )
		{
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ eBeaconIdUsedActually ].usActiveSetpoint = ( pxLaserBeamDescriptor->xElectricalVariablesStatus[ eBeaconIdUsedActually ].usActiveSetpoint ) - ACC_STEPS_CONTROL_IN_MV;
			eAccLaserState = eInitAccDetection ;
		}*/
		
		eCurrentControlUpdateLna( fCurrent );
		
	//}
	
	
}


/*---------------------------------------------------------------------*/
