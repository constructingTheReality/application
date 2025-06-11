/**
* @file		    mainStateMachine.h
* @brief        mainStateMachine header file.
* @author		juan
* @date			Created on 2023-7-12
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef TRAJECTORYCALCULATOR_H_
#define TRAJECTORYCALCULATOR_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
//#include "ControlAlarm.h"
//#include "CurrentSensor.h"
//#include "temperature.h"
//#include "PowerSensor.h"
//#include "BSPGpio.h"
#include "LaserData.h"

/* Define ------------------------------------------------------------------- */
#define MAX_CURRENT_INCREASE_BY_STEP   (50)
#define MAX_CURRENT_INCREASE_BY_STEP_500   (500)
#define		CURRENT_INCREASE_BY_STEP_IN_W  ( 0.02 )   //delata w variation for each 50 mA  in mw 
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief		Init the laser beams
*/
void vTrajectoryCalculatorRun( eBool_t bIsStep50mA, uint16_t usSetpoint, uint16_t usCurrentRead,  uint16_t *pNumberOfSteps, eBool_t *pbIncrease);

//void vTrajectoryCalculatorApcRun( eBool_t bIsInApcMode, float fInitialError,  uint16_t *pNumberOfSteps) ;



#endif /* TRAJECTORYCALCULATOR_H_ */