/**
* @file         powerSensorsAlarmValidateLimits.h
* @brief        Non monolithic filter
* @author       Isabelle Champion
* @date         08/07/2024
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2024 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/

/* Header guard ------------------------------------------------------------- */
#ifndef POWERSENSORSALARMVALIDATELIMITS_H_
#define POWERSENSORSALARMVALIDATELIMITS_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "dictionaryUtils.h"
#include "can428Packet.h"
#include "can408Packet.h"
#include "can402Packet.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */



/**
* @brief        Validate the Output Alarm Limits
* @param[in]	fHighAlarmLimitPowerOutput: Upper limit for the value of the power output limit
* @param[in]	fLowAlarmLimitPowerOutput: Lower limit for the value of the power output limit
* @param[in]	bIsBooster: Booster: true // Lna: false
* @param[out]   pbOutputCheckC408: whether or not the limits are within their valid ranges
* @return	    Success or library error message
*/

eMpbError_t ePowerSensorValidateOutputLimits( eBool_t* pbOutputCheckC408, float fHighAlarmLimitPowerOutput, float fLowAlarmLimitPowerOutput, eBool_t bIsBooster);

/**
* @brief        Validate the Input Alarm Limits
* @param[in]	fHighAlarmLimitPowerOutput: Upper limit for the value of the power input limit
* @param[in]	fLowAlarmLimitPowerOutput: Lower limit for the value of the power input limit
* @param[in]	bIsBooster: Booster: true // Lna: false
* @param[out]   pbOutputCheckC408: whether or not the limits are within their valid ranges
* @return	    Success or library error message
*/
eMpbError_t ePowerSensorValidateInputLimits( eBool_t* pbInputCheckC408,  float fHighAlarmLimitPowerInput, float fLowAlarmLimitPowerInput, eBool_t bIsBooster);


#endif /* POWERSENSORSALARMVALIDATELIMITS_H_ */