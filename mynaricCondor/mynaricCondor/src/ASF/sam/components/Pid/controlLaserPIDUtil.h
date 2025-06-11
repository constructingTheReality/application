/**
* @file			controlLaserPIDUtil.h
* @brief		controlLaserPIDUtil.h header file
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
#ifndef CONTROLLASERPIDUTIL_H_
#define CONTROLLASERPIDUTIL_H_
/* Includes ----------------------------------------------------------------- */
#include "mpbControlPID.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief        Initialize the PID.
* @param[in]	fPGain: The PID proportionnal gain.
* @param[in]	fIGain: The PID integral gain.
* @param[in]	fDGain: The PID derivative gain.
* @param[in]    fMininum: the PID minimum value.
* @param[in]    fMaxmium: the PID maximum value.
* @param[in]    pxPIDConfig: the PID configuration.
*/
void vControlLaserPIDUtilInit( float fPGain, float fIGain, float fDGain, float fMininum, float fMaxmium, uint32_t ulAccLoopControlInterval, xPIDConfig_t *pxPIDConfig );

/**
* @brief        Reset the PID.
* @param[in]    pxPIDConfig: the PID configuration.
*/
void vControlLaserPIDUtilReset( xPIDConfig_t *pxPIDConfig );


void vControlLaserPIDCalcul( float fReference, float fReferenceFeedback, xPIDConfig_t *pxPIDConfig, float *pfPIDOutput );

#endif /* __CONTROLLASERPIDUTIL_H */

