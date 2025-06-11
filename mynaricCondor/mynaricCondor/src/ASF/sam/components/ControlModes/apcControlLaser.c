/**
* @file 		apcControlLaser.c
* @brief		apcControlLaser.c source file
* @author		juan andres
* @date			Created on 2021-3-31
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
#include "apcControlLaser.h"
#include "lnaStateMachine.h"
#include "glue.h"
/* Private define ----------------------------------------------------------- */

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
static eApcLaserState_t eApcLnaSingleModeLaserState = eInitApcPidControl;
static eApcLaserState_t eApcHpaSingleModeLaserState = eInitApcPidControl;
static eApcLaserState_t eApcHpaMultiMode1LaserState = eInitApcPidControl;
static eApcLaserState_t eApcHpaMultiMode2LaserState = eInitApcPidControl;
static eApcLaserState_t eApcHpaMultiMode1and2LaserState = eInitApcPidControl;

/* Private function prototypes ---------------------------------------------- */
static void apcLnaControlLaserFsm( xLnaParameters_t * pxLnaParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent) ;
static void apcHpaMm1ControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent) ;
static void apcHpaMm2ControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent) ;
static void apcHpaMm1and2ControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent) ;


static void apcLnaControlLaserFsm( xLnaParameters_t * pxLnaParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent )
{
	/*  state machine for the apc control */
	if ( eApcLnaSingleModeLaserState == eInitApcPidControl )
	{
		
			vControlLaserPIDInit( eLnaLaserSingleModePowerLoopPID, ulDeltaTime , &(pxLnaParameters->xPidValuesLna) );
			eApcLnaSingleModeLaserState = eNormalUpdatePidLoopControl ;
		
	}
	else if ( eApcLnaSingleModeLaserState == eNormalUpdatePidLoopControl )
	{
		
			vControlLaserPIDUpdate( fPowerReference, fPowerReferenceFeedback, eLnaSingleMode , pfControlCurrent );
			
			if( bControlLaserDeltaTimeHasChanged( eLnaLaserSingleModePowerLoopPID, ulDeltaTime  ) == eTrue )
			{
				eApcLnaSingleModeLaserState = eInitApcPidControl ;
			}
		
	}
}
/*---------------------------------------------------------------------------*/
static void apcHpaSmControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime) 
{
	/*  state machine for the apc sm1 control */

	if ( eApcHpaSingleModeLaserState == eInitApcPidControl )
	{
		
		vControlLaserPIDInit( eHpaLaserSingleModePowerLoopPID, ulDeltaTime , &(pxBoosterParameters->xPidSmValuesBooster) );
		eApcHpaSingleModeLaserState = eNormalUpdatePidLoopControl ;
		
	}
	else if ( eApcHpaSingleModeLaserState == eNormalUpdatePidLoopControl )
	{
		
		//vControlLaserPIDUpdate( fPowerReference, fPowerReferenceFeedback, eHpaSingleMode  );
		
		if( bControlLaserDeltaTimeHasChanged( eHpaLaserSingleModePowerLoopPID, ulDeltaTime  ) == eTrue )
		{
			eApcHpaSingleModeLaserState = eInitApcPidControl ;
		}
		
	}
}
/*---------------------------------------------------------------------------*/
static void apcHpaMm1ControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent)
{
	/*  state machine for the apc mm1 control */

	if ( eApcHpaMultiMode1LaserState == eInitApcPidControl )
	{
		
		vControlLaserPIDInit( eHpaLaserMultiMode1PowerLoopPID, ulDeltaTime , &(pxBoosterParameters->xPidMm1ValuesBooster) );
		eApcHpaMultiMode1LaserState = eNormalUpdatePidLoopControl ;
		
	}
	else if ( eApcHpaMultiMode1LaserState == eNormalUpdatePidLoopControl )
	{
		
		vControlLaserPIDUpdate( fPowerReference, fPowerReferenceFeedback, eHpaMultiMode1 , pfControlCurrent );
		
		if( bControlLaserDeltaTimeHasChanged( eHpaLaserMultiMode1PowerLoopPID, ulDeltaTime  ) == eTrue )
		{
			eApcHpaMultiMode1LaserState = eInitApcPidControl ;
		}
		
	}
}
static void apcHpaMm2ControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent)
{
	/*  state machine for the apc mm1 control */

	if ( eApcHpaMultiMode2LaserState == eInitApcPidControl )
	{
		
		vControlLaserPIDInit( eHpaLaserMultiMode2PowerLoopPID, ulDeltaTime , &(pxBoosterParameters->xPidMm2ValuesBooster) );
		eApcHpaMultiMode2LaserState = eNormalUpdatePidLoopControl ;
		
	}
	else if ( eApcHpaMultiMode2LaserState == eNormalUpdatePidLoopControl )
	{
		
		vControlLaserPIDUpdate( fPowerReference, fPowerReferenceFeedback, eHpaMultiMode2  , pfControlCurrent);
		
		if( bControlLaserDeltaTimeHasChanged( eHpaLaserMultiMode2PowerLoopPID, ulDeltaTime  ) == eTrue )
		{
			eApcHpaMultiMode2LaserState = eInitApcPidControl ;
		}
		
	}
}


static void apcHpaMm1and2ControlLaserFsm( xBoosterParameters_t * pxBoosterParameters, float fPowerReference, float fPowerReferenceFeedback, uint32_t ulDeltaTime, float *pfControlCurrent)
{
	/*  state machine for the apc mm1 and mm2 control */

	if ( eApcHpaMultiMode1and2LaserState == eInitApcPidControl )
	{
		
		vControlLaserPIDInit( eHpaLaserMultM1and2PowerLoopPID, ulDeltaTime , &(pxBoosterParameters->xPidMm1and2ValuesBooster) );
		eApcHpaMultiMode1and2LaserState = eNormalUpdatePidLoopControl ;
		
	}
	else if ( eApcHpaMultiMode1and2LaserState == eNormalUpdatePidLoopControl )
	{
		
		vControlLaserPIDUpdate( fPowerReference, fPowerReferenceFeedback, eHpaMultiMode1and2 , pfControlCurrent );
		
		if( bControlLaserDeltaTimeHasChanged( eHpaLaserMultM1and2PowerLoopPID, ulDeltaTime  ) == eTrue )
		{
			eApcHpaMultiMode1and2LaserState = eInitApcPidControl ;
		}
		
	}
}

/* Exported functions ------------------------------------------------------- */
/**
* @brief        Initalization of laser.
*/
void vApcControlLaserInit( void )
{
	eApcLnaSingleModeLaserState = eInitApcPidControl ;
	eApcHpaSingleModeLaserState = eInitApcPidControl ;
	
	 eApcHpaMultiMode1LaserState = eInitApcPidControl;
	 eApcHpaMultiMode2LaserState = eInitApcPidControl;
	 eApcHpaMultiMode1and2LaserState = eInitApcPidControl;
}

/*----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
void vApcControlLaserUpdate( uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback , float *pfControlCurrent )
{
	

	xLnaParameters_t * pxLnaParameters = NULL;
	xLnaParameters_t xLnaParametersl;
	pxLnaParameters =  vGetpxLnaParameters(&xLnaParametersl);

	apcLnaControlLaserFsm( pxLnaParameters, fPowerReference, fPowerReferenceFeedback, ulDeltaTime ,pfControlCurrent) ;
	
}
/*---------------------------------------------------------------------*/

void vApcSm1ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback )
{

	apcHpaSmControlLaserFsm( pxBoosterParameters, fPowerReference, fPowerReferenceFeedback, ulDeltaTime ) ;
		
}
/*---------------------------------------------------------------------*/

void vApcMm1ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback , float *pfControlCurrent)
{

	apcHpaMm1ControlLaserFsm( pxBoosterParameters, fPowerReference, fPowerReferenceFeedback, ulDeltaTime, pfControlCurrent ) ;
	
}
/*---------------------------------------------------------------------*/
void vApcMm2ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback ,float *pfControlCurrent)
{

	apcHpaMm2ControlLaserFsm( pxBoosterParameters, fPowerReference, fPowerReferenceFeedback, ulDeltaTime , pfControlCurrent) ;
	
}

void vApcMm1and2ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback ,float *pfControlCurrent)
{
	apcHpaMm1and2ControlLaserFsm( pxBoosterParameters, fPowerReference, fPowerReferenceFeedback, ulDeltaTime , pfControlCurrent) ;
}
/*---------------------------------------------------------------------*/

