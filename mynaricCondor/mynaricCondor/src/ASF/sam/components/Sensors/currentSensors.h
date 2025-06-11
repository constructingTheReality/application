/**
* @file			CurrentSensor.h
* @brief		CurrentSensor.h header file
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
#ifndef CURRENTSENSORS_H_
#define CURRENTSENSORS_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
//#include "ControlAlarm.h"
#include "LaserData.h"
#include "glue.h"

/* Define ------------------------------------------------------------------- */
/**
* @brief        Define the slope intercept values for current inputs.
* @note         CurrentChannelConfigId     The identifier for the channel.
* @note         slope constant       			 The slope filter constant.
* @note         intercept constant       	 The intercept constant.
*/

/*	                	            X(	CurrentChannelConfigId		    		,slope Filter Constant	  ,intercept Filter      )	*/
#define LIST_OF_CURRENT_CHANNELS	X(  eAdcInternal28VPwrCurrentMonitorCH1	    ,0.044                   ,0 )\
                                    X(  eAdcInternal28VPwrCurrentMonitorCH2	    ,0.044                   ,0 )\
									X(  eAdcInternal28VPwrVoltageMonitorCH1	    ,0.0086                  ,0 )\
									X(  eAdcInternal28VPwrVoltageMonitorCH2	    ,0.0086                  ,0 )\
									X(  eAdcInternal7VPwrVoltageMonitorCH1	    ,0.0086                  ,0 )\
									X(  eAdcInternal7VPwrVoltageMonitorCH2	    ,0.0086                  ,0 )\
									X(  eAdcInternal3_3VPower_VoltageMonitor    ,0.00161                 ,0 )\
									X(  eAdcInternal3VPower_VoltageMonitor	    ,0.00161                 ,0 )\
									X(  eAdcInternalPowerCurrentMonitor			,0.0000854               ,0 )\
									X(  eAdcInternalCanPwrCurrentMonitorCH1	    ,0.0000854 		         ,0 )\
									X(  eAdcInternalCanPwrCurrentMonitorCH2	    ,0.0000854               ,0 )\
									X(  eAdcExLnaSingleModeldCurrentMonitor	    ,0.000220                ,0 )\
									X(	eAdcExHpaSingleModeld_CurrentMonitor	,0.000220     			 ,0 )\
									X(	eAdcExHpaMultiModeld_CurrentMonitor1	,0.00502               	 ,0 )\
									X(  eAdcExternalLnaSm_ld_Bfm                ,0.000754           	 ,0 )\
									X(	eAdcExternalHpaSm_ld_Bfm	  		    ,0.000754				 ,0 )\
									X(	eAdcExHpaMultiModeld_CurrentMonitor2	,0.00502               	 ,0 )
/* Exported macro ----------------------------------------------------------- */
//0.0026               	 ,-0.9818 )
//0.0027               	 ,-1.1719
/* Exported enum ------------------------------------------------------------ */
/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( CurrentChannelConfigId, slopeConstant, interceptConstant )	CurrentChannelConfigId,
	LIST_OF_CURRENT_CHANNELS 
#undef X
	eNumberOfChannelConfigurations,
}
eCurrentChannelsScaling_t; 

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */

/* Exported function prototypes --------------------------------------------- */

/**
  * @brief 		Init the current scaling internal channels.
*/
void vCurrentSensorsInitInternalChannels( void );

/**
  * @brief 		Init the current scaling internal channels for LNA.
*/
void vCurrentSensorsFactoryInitLnaChannels( void );
/**
  * @brief 		Init the current scaling internal channels for HPA.
*/
void vCurrentSensorsFactoryInitBoosterChannels( void );

/**
* @brief	    set the current intercept scaling factor for the lna
* @param[in]	eChannel: the channel requested.
*/
eMpbError_t eCurrentSensorsLnaConfigUpdate( void );
/**
* @brief	    set the current intercept scaling factor for the booster
* @param[in]	eChannel: the channel requested.
*/
eMpbError_t eCurrentSensorsBoosterConfigUpdate( void );

/**
 * @brief 		Update critical currents of the laser.
 * @param[out]	none.
 */
eMpbError_t eCurrentSensorUpdate( eBool_t *pHpaCurrentAlarm, eBool_t *pLnaCurrentAlarm , eBool_t *pInternalCurrentAlarm  ) ; 
/**
* @brief	    init the calibration factors when nvm memory is empty or damage 
*/
//void vCurrentSensorInitFacotryScaling(void);


#endif /* CURRENTSENSORS_H_ */