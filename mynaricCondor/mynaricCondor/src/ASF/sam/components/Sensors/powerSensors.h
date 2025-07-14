/**
* @file			PowerSensor.h
* @brief		PowerSensor.h header file
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

#ifndef POWERSENSORS_H_
#define POWERSENSORS_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "mpbLosDetector.h"
#include "LaserData.h"
#include "glue.h"
#include "currentSensing.h"
/* Define ------------------------------------------------------------------- */
#define  LOS_SET_LIMIT  (-10.5)//(-49.0 )  /( 0.0000125893) 
#define  LOS_CLEAR_LIMIT   (-4)//(-51 ) //( 0.0000079433 )

#define MAX_HPA_CURRENT_SM_IN_MA		( 550 )
#define NOMINAL_CURRENT_SM_IN_POURCENTAGE  ( 75 )
#define MAX_HPA_CURRENT_STAGE_MM_1_IN_MA		( 1500 )
#define MAX_HPA_CURRENT_STAGE_MM_2_IN_MA		( 1500 )
#define MAX_HPA_CURRENT_MM_1_IN_MA		( 5000 )
#define MAX_HPA_CURRENT_MM_2_IN_MA		( 5000 )
#define MAX_LH_LEVEL_IN_RAW				( 3970 )  //3900
#define MIN_HH_LEVEL_IN_RAW				( 640 )  // 600

#define MAX_BF_IN_MA				( 1500 )
#define MIN_BF_IN_MA				( 800 )




/**
* @brief        Define the slope intercept values for power inputs.
* @note         PowerChannelConfigId     The identifier for the channel.
* @note         slope constant       		 The slope filter constant.
* @note         intercept constant     	 The intercept constant.
*/

/*	                	          X(	PowerChannelConfigId					,slope Filter Constant		,intercept Filter Constant   )	*/
#define LIST_OF_POWER_CHANNELS	  X(    eInternalPdReference	               ,1               		,0 )\
								  X(    eInternalLnaOutputPower1	           ,0.0000189        		,0 )\
								  X(    eInternalLnaOutputPower2               ,0.0000189        		,0 )\
								  X(    eExternalLnaInputPower_1536            ,0.00000000187      		,0 )\
								  X(    eExternalLnaInputPower_1553            ,0.00000000187      		,0 )\
								  X(    eExternalLnaOutputPower1_1536          ,0.0000189          		,0 )\
								  X(    eExternalLnaOutputPower2_1553          ,0.0000189          		,0 )\
								  X(    eExternalHpaInputPower_1536            ,0.0000189          		,0 )\
								  X(    eExternalHpaInputPower_1553            ,0.0000189          		,0 )\
								  X(    eExternalHpaOutputPower_1536_lm        ,0.000191           		,0 )\
								  X(    eExternalHpaOutputPower_1536_hm        ,0.00189            		,0 )\
								  X(    eExternalHpaOutputPower_1553_lm        ,0.000191           		,0 )\
								  X(    eExternalHpaOutputPower_1553_hm        ,0.00189            		,0 )\
								  X(	eExternal_PdReference1				   ,1						,0 )\
								  X(	eExternal_PdReference				   ,1						,0 )
								  

/* Exported macro ----------------------------------------------------------- */
/*//eInternalLnaOutputPower1	           ,0.0000189          		,0 )\
//X(    eInternalLnaOutputPower2               ,0.0000189 042385552 */
/* Exported enum ------------------------------------------------------------ */
/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( PowerChannelConfigId, slopeConstant, interceptConstant )	PowerChannelConfigId,
	LIST_OF_POWER_CHANNELS 
#undef X
	eNumberOfPowerChannelConfigurations,
}
ePowerChannelsScaling_t; 

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */

/* Exported function prototypes --------------------------------------------- */

/**
  * @brief 		Init the power sensors - common section - with factory - emergency- values. In case nvm fail.
  * @param[in]	none.
  * @param[out]	none.
  * @return     Success or library error message
*/

eMpbError_t ePowerSensorsFactoryInitCommonChannels( void );
/**
  * @brief 		Init the power sensors - LNA section - with factory - emergency- values. In case nvm fail.
  * @param[in]	none.
  * @param[out]	none.
  * @return     Success or library error message
*/
eMpbError_t ePowerSensorsFactoryInitLnaChannels( void );

/**
  * @brief 		Init the power sensors - HPA section - with factory - emergency- values. In case nvm fail.
  * @param[in]	none.
  * @param[out]	none.
  * @return     Success or library error message
*/
eMpbError_t ePowerSensorsFactoryInitBoosterChannels( void );

/**
  * @brief 		Save the config from the DB - common section - into the local copy.  
  * @param[in]	none.
  * @param[out]	none.
  * @return     Success or library error message
*/
eMpbError_t ePowerSensorsCommonConfigUpdate( void );
/**
  * @brief 		Save the config from the DB - LNA section - into the local copy.  
  * @param[in]	none.
  * @param[out]	none.
  * @return     Success or library error message
*/
eMpbError_t ePowerSensorsLnaConfigUpdate( void );
/**
  * @brief 		Save the config from the DB - HPA section - into the local copy.  
  * @param[in]	none.
  * @param[out]	none.
  * @return     Success or library error message
*/
eMpbError_t ePowerSensorsBoosterConfigUpdate( void );

/**
  * @brief 		Update critical power of the laser.
  * @param[out]	alarms detected.
  * @return     Success or library error message
  */
eMpbError_t ePowerSensorUpdate( eBool_t *pbHpaPowerLosAlarm, eBool_t *pbLnaPowerCriticalAlarm, eBool_t *pbBoosterPowerCriticalAlarm );




#endif /* __POWERSENSOR_H */






