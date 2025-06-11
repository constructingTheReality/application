/**
* @file		    controlLaserPID.h
* @brief      controlLaserPID header file.
* @author		juan
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
/* Header guard ------------------------------------------------------------- */
#ifndef CONTROLLASERPID_H_
#define CONTROLLASERPID_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "powerControl.h"
/* Define ------------------------------------------------------------------- */
#define CURRENT_INCREASE_BY_STEP_IN_MA_HPA ( 500 )
#define CURRENT_INCREASE_BY_STEP_IN_MA_SM_HPA ( 50 )

					   /*X( PIDID                				,PIDConfigID									kp       ki       kd    )*/
#define PID_LIST       	X( eLnaLaserSingleModePowerLoopPID    ,xprvLnaSingleModeLaserPowerLoopPIDConfig			,1450   ,16.82   ,0    )\
						X( eHpaLaserSingleModePowerLoopPID    ,xprvHpaSingleModeLaserPowerLoopPIDConfig			,2.9    ,0.004   ,0    )\
						X( eHpaLaserMultiMode1PowerLoopPID    ,xprvHpaMultimode1LaserPowerLoopPIDConfig			,0.9    ,0.004   ,0    )\
						X( eHpaLaserMultiMode2PowerLoopPID    ,xprvHpaMultimode2_LaserPowerLoopPIDConfig		,0.9    ,0.004   ,0    )\
						X( eHpaLaserMultM1and2PowerLoopPID    ,xprvHpaMultimode1and2LaserPowerLoopPIDConfig		,1.45   ,0.004   ,0    )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/**
* @brief    Defines the PID enmumeration intervals
*/
typedef enum
{
	#define X( PIDID, PIDConfigID, kp, ki, kd ) PIDID,
	PID_LIST
	#undef X
	eNumberOfPidChannelConfigurations
}
ePIDID_t;
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief        Initialize the PID.
* @param[in]	ePIDID: The PID identifier.
*/
void vControlLaserPIDInit( ePIDID_t ePIDID, uint32_t ulAccLoopControlInterval, xPidValues_t *pxPidValues );

/**
* @brief        Initialize the defaultLNA PID values. 
* @param[in]	none.
*/
void vSetLnaPidDefaultValues(void);
/**
* @brief        Initialize the default  HPA PID values.
* @param[in]	none.
*/
void vSetHpaPidDefaultValues(void);
/**
* @brief        upload the HPA PID values from nvm.
* @param[in]	none.
*/
void vSetHpaPidNvmValues(void);


void vSetPidValues( handle_t eBeacon_Id, float kp, float ki, float kd  );
void vSetInternalPidValues( handle_t eBeacon_Id, float kp, float ki, float kd  );
void vGetPidValues( handle_t eBeacon_Id, float *kp, float *ki, float *kd  );

/**
* @brief        Reset the PID.
* @param[in]	ePIDID: The PID identifier.
*/
void vControlLaserPIDReset( ePIDID_t ePIDID );

eBool_t bControlLaserDeltaTimeHasChanged( ePIDID_t ePIDID, uint32_t ulDeltaTime ) ;
/**
* @brief		Applies the PID to the Laser.
* @param[in]	fReference: the laser reference.
* @param[in]	fReferenceFeedback: the laser reference feedback.
*/
void vControlLaserPIDUpdate( float fReference, float fReferenceFeedback , uint8_t eBeaconId, float *pfControlCurrent);

#endif /* __CONTROLLASERPID_H */




