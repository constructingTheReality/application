/**
* @file		    powerReadChannel.h
* @brief        powerReadChannel header file.
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
#ifndef POWERREADCHANNEL_H_
#define POWERREADCHANNEL_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "glue.h"
#include "powerSensors.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
  * @brief 		get the offset in raw data. this info will be used for calculate the power in the other channels. 
  * @param[out]	pusInternalOffset: offset in internal ADC channel 12.
  * @param[out]	pusExternalOffset: offset in external ADC channel 06.
  * @param[out]	pusExternalOffset1: offset in external ADC channel 23.
  */

eMpbError_t ePowerReadOffsetChannelRun( uint16_t *pusInternalOffset, uint16_t *pusExternalOffset , uint16_t *pusExternalOffset1  );
/**
  * @brief 		get temperature value for a specific channel  
  * @param[in]	xStream: the driver hardware number
  * @param[in]	usOffset: needed to calcul the input power.
  * @param[in]	pfTemperatureReaded: the temperature read in c.
  * @param[out]	pCriticalAnalogPower: the power reads.
  */

eMpbError_t ePowerReadChannelRun(handle_t xStream, uint16_t usOffset, float fSlope, float fIntercept, float *pfPowerReaded, uint16_t *pusPowerRaw);


#endif /* POWERREADCHANNEL_H_ */