
/**
  * @file			mpbControlPIDUtil.h
  * @brief      mpbControlPIDUtil header file.
  * @author			juan andres
  * @date			Created on 3-23-2021
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

#ifndef MPBCONTROLPIDUTIL_H_
#define MPBCONTROLPIDUTIL_H_

/* Includes ----------------------------------------------------------------- */

#include "mpblibs.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
  * @brief          Calculate PID controller's integral error.
  * @param[in]      ulDeltaTime: Tick between two measures.
  * @param[in]      fError: The system error.
  * @param[in]      fIErrorPID: The system integral error.
  * @param[out]     pfNewIError: Pointer on the new integral error.
  */
void vMpbControlPIDUtilCalculIError( uint32_t ulDeltaTime, float fError, float fIErrorPID, float *pfNewIError );

/**
  * @brief          Calculate PID controller's derivative error.
  * @param[in]      ulDeltaTime: Tick between two measures.
  * @param[in]      fError: The system error.
  * @param[in]      fOldError: Old Proportional error.
  * @param[out]     pfDError: Pointer on PID controller's derivative error.
  */
void vMpbControlPIDUtilCalculDError( uint32_t ulDeltaTime, float fError, float fOldError, float *pfDError );

/**
  * @brief          Apply the clamping integral anti-windup method.
  * @param[in]      fError: The system error.
  * @param[in]      fNewIError: The tentative integral error.
  * @param[in]      fCurrentIError: The curren pid integral error.
  * @param[in]      fOutput: the calculated pid output.
  * @param[in]      fLowerLimit: Lower saturation limit.
  * @param[in]      fUpperLimit: Upper saturation limit.
  * @param[out]     pfIErrorPID: The pid new integral error.
  * @param[out]     pfSaturatedOutput: Controller's saturated output.
  */
void vMpbControlPIDUtilAntiWindupClamping( float fError, float fNewIError, float fCurrentIError, float fOutput, float fLowerLimit, float fUpperLimit, float *pfIErrorPID, float *pfSaturatedOutput );

/**
  * @brief          Calculate saturated output of PID.
  * @param[in]      fLowerLimit: Lower saturation limit.
  * @param[in]      fUpperLimit: Upper saturation limit.
  * @param[in]      fOutput: Controller output.
  * @param[out]     pfSaturatedOutput: Controller's saturated output.
  */
void vMpbControlPIDUtilSaturation( float fLowerLimit, float fUpperLimit, float fOutput, float *pfSaturatedOutput );

#endif /* __MPBCONTROL_PID_UTIL_H */





