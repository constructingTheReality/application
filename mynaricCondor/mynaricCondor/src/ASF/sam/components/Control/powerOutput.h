/**
* @file           PowerOutput.h
* @brief          Library to calculate a voltage according to a power
*                 sensing signal input.
* @author         juan andres
* @date           Created on 4/6/2021
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
#ifndef POWEROUTPUT_H_
#define POWEROUTPUT_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	float fIntercept;
	float fSlope;
	//float fCalibration;
}xPowerOutputScaling_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief      set the volts for the anlog output (converted from  mW)
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[out] pfVtoltage: Pointer to store the voltage
* @return     Success or library error message
**/
eMpbError_t ePowerOutputSetPowermW( handle_t xStream, xPowerOutputScaling_t xPowerOutputScaling, float fPower, float fLowVoltage, float *pfVoltage  );

/**
* @brief      Set the voltage of the current sensing input in mV
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[out] fVoltage: voltage to write
* @return     Success or library error message
**/
//extern eMpbError_t ePowerOutputAnalogWritemV( handle_t xStream, float fVoltage );
extern eMpbError_t ePowerOutputAnalogWritemV( handle_t xStream, float fVoltage, float fLowVoltage );


#endif /* __POWER_OUTPUT_H */





