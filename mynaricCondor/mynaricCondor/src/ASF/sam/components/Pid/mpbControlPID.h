/**
  * @file			mpbControlPID.h
  * @brief     mpbControlPID header file.
  * @author			juan andres
  * @date			Created on 3-23-2021
  * @note
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

#ifndef MPBCONTROLPID_H_
#define MPBCONTROLPID_H_

/* Includes ----------------------------------------------------------------- */

#include "mpbControlPIDUtil.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

/**
  * @brief  Informations about PID structures.
  */
typedef struct 
{
		uint32_t ulDeltaTime;
		eBool_t bSaturationEnable;
		eBool_t bAntiWindupEnable;
    float fProportionalGain;
    float fIntegralGain;
    float fDerivativeGain;
    float fLowerSaturationLimit;
    float fUpperSaturationLimit;
    float fOldInput;
    float fIError;
    
}xPIDConfig_t;
//}__attribute__ ((packed))xPIDConfig_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
  * @brief          Initialization PID structure.
  * @param[in]      fPGain: Proportional gain of PID controller.
  * @param[in]      fIGain: Integral gain of PID controller.
  * @param[in]      fDGain: Derivative gain of PID controller.
  * @param[in]      fLowerLimit: Lower saturation limit.
  * @param[in]      fUpperLimit: Upper saturation limit.
  * @param[in]      bIsSaturationEnable: output saturation enable/disable.
  * @param[in]      bIsAntiWindupEnable: anti-windup enable/disable.
  * @param[in]      ulDeltaTime: Tick ( mSec ) between two different measures.
  * @param[out]     pxPIDConfig: Pointer on PID controller's structure.
  * @return         Success or library error message.
  */
eMpbError_t eMpbControlPIDInit( float fPGain, float fIGain, float fDGain, float fLowerLimit, float fUpperLimit, eBool_t bIsSaturationEnable, eBool_t bIsAntiWindupEnable, uint32_t ulDeltaTime, xPIDConfig_t *pxPIDConfig );

/**
  * @brief          Add value to PID controller and change output PID structure.
  * @param[in]      fInput: Input of PID.
  * @param[out]     pxPIDConfig: Pointer on a structure which contains informations of PID controller.
  * @param[out]     pfOutput: Pointer on output of PID controller.
  * @return         Success or library error message.
  */
eMpbError_t eMpbControlPIDCalcul( float fInput, xPIDConfig_t *pxPIDConfig, float *pfOutput );

/**
  * @brief          Reset integral error of actual PID.
  * @param[out]     pxPIDConfig: Pointer on a structure which contains informations of PID controller.
  * @return         Success or library error message.
  * @note           Should be used each time the setpoint change.
  */
eMpbError_t eMpbControlPIDReset( xPIDConfig_t *pxPIDConfig );


#endif /* __MPBCONTROLPID_H */




