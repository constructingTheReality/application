

/**
* @file		    apcControlLaser.h
* @brief      apccontrolLaser header file.
* @author		juan
* @date			Created on 2021-03-23
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef APCCONTROLLASER_H_
#define APCCONTROLLASER_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "laserData.h"
#include "controlLaserPID.h"
/* Define ------------------------------------------------------------------- */
#define LASER_BRAKE_DUTY_CYCLE_VALUE      ( 0 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef enum
{
	eInitApcPidControl =0,
	eNormalUpdatePidLoopControl = 1,
	eResetLoopControl = 2,
}eApcLaserState_t;




/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief        Initalization of laser.
*/
void vApcControlLaserInit( void );
/**
* @brief		Update control of fake signal ( signal meanwhile the adquisition Phase) laser.
*/
//void vApcFakeControlLaserUpdate( uint32_t ulDeltaTime);
/**
* @brief		Update control of laser.
*/

void vApcControlLaserUpdate( uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback , float *pfControlCurrent);

void vApcSm1ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback );
void vApcMm1ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback , float *pfControlCurrent);
void vApcMm2ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback , float *pfControlCurrent);
void vApcMm1and2ControlLaserUpdate( xBoosterParameters_t * pxBoosterParameters, uint32_t ulDeltaTime, float fPowerReference, float fPowerReferenceFeedback , float *pfControlCurrent);
//void vApcControlModulationLowLevelUpdate(void);








#endif /* APCCONTROLLASER_H_ */