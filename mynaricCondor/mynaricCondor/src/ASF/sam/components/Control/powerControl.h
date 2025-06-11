
/**
* @file			PowerControl.h
* @brief		PowerControl.h header file
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
/* Header guard ------------------------------------------------------------- */
#ifndef POWERCONTROL_H_
#define POWERCONTROL_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
//#include "ControlAlarm.h"
#include "LaserData.h"
//#include "cmd_interface.h"
/* Define ------------------------------------------------------------------- */
/**
* @brief        Define the slope intercept values for current control .
* @note         CurrentChannelConfigId     The identifier for the channel.
* @note         slope constant       			 The slope filter constant.
* @note         intercept constant       	 The intercept constant.
*/

/*	                				    X(	PowerControlChannelConfigId		  			,slope Filter Constant	  ,intercept Filter       calibration factor   )	*/
#define LIST_OF_POWER_CONTROL_CHANNELS	X(  eLnaSingleModeLaserDiodeControlPower		,0.43                    ,-33.33               ,1.0)\
										X(  eHpaSingleModeLaserDiodeControlPower		,0.43                    ,-33.33               ,1.0)
/* Exported macro ----------------------------------------------------------- */
//   32  1 
/* Exported enum ------------------------------------------------------------ */
/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( PowerControlChannelConfigId, slopeConstant, interceptConstant, calibrationFactor )	PowerControlChannelConfigId,
	LIST_OF_POWER_CONTROL_CHANNELS 
#undef X
	eNumberOfPowerChannelControlConfigurations,
}
ePowerControlChannelsScaling_t; 

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
  * @brief 		Init the current scaling channels.
*/
void vPowerControlInit( void );

/**
  * @brief 		Update critical currents of the laser.
  * @param[out]	none.
  */

//eMpbError_t ePowerControlUpdate( float fPowerControlSignal ) ;

eMpbError_t ePowerControlUpdate( float fPowerControlSignal , uint8_t eBeaconId ) ;



//void vPowerControlgetOutputScalingValues ( float *pfSlope, float *pfIntercep, float *pfGain, uint8_t eBeaconId );

//void vPowerControlsetOutputScalingValues ( float fSlope, float fIntercep, float fGain, uint8_t eBeaconId);

//eMpbError_t ePowerControlModulationLowLevelUpdate( void );


#endif /* __CURRENTCONTROL_H */





