/**
* @file		    currentSensorsreadChannel.h
* @brief        currentSensorsreadChannel header file.
* @author		juan
* @date			Created on 2024-05-30
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
#ifndef CURRENTSENSORSREADCHANNEL_H_
#define CURRENTSENSORSREADCHANNEL_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "glue.h"
#include "currentSensors.h"
#include "currentSensing.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
  * @brief 		get current value for a specific channel  
  * @param[in]	xStream: the driver hardware number  
  * @param[in]	pfCurrentReaded: the current read in mA.
  * @param[out]	pusCurrentRaw: the current reads in raw.
  */

eMpbError_t eCurrentSensorsReadChannelRun(handle_t xStream, uint16_t usOffset, float fSlope, float fIntercept, float *pfCurrentReadedInMa, uint16_t *pusCurrentRaw);

#endif /* CURRENTSENSORSREADCHANNEL_H_ */