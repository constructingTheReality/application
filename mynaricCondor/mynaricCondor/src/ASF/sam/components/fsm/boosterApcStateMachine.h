/**
* @file		    boosterApcStateMachine.h
* @brief        boosterApcStateMachine header file.
* @author		juan
* @date			Created on 2024-7-12
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
#ifndef BOOSTERAPCSTATEMACHINE_H_
#define BOOSTERAPCSTATEMACHINE_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"


/* Define ------------------------------------------------------------------- */
#define		CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE  ( 500 )
#define		CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC  ( 100 )
#define		MIN_SETPOINT_FOR_APC_BOOSTER_IN_DBM  ( 16 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
enum eHpaApcState
{
	eHpaApcInit = 0,
	eHpaApcSm = 1,
	eHpaApcMm1_Init = 2,
	eHpaApcMm1_Control = 3,
	eHpaApcMm2_Init = 4,
	eHpaApcMm2_Control = 5,
	eHpaApcMm1Mm2_Init = 6,
	eHpaApcMm1Mm2_Control = 7
};


typedef enum eHpaApcState eHpaApcState_t ;
eHpaApcState_t xReportHpaApcState(void); 
void eHpaApcStateInitFunction(void);
void eHpaApcStateSmFunction(void);
void eHpaApcStateMm1_InitFunction(void);
void eHpaApcStateMm1_ControlFunction(void);
void eHpaApcStateMm2_InitFunction(void);
void eHpaApcStateMm2_ControlFunction(void);
void eHpaApcStateMm1Mm2_InitFunction(void);
void eHpaApcStateMm1Mm2_ControlFunction(void);

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
* @brief      init the hpa apc fsm
* @param[in]  none
* @param[out] none
* @return     none
**/
void vHpaApcStateMachineInit( void );
/**
* @brief      move or tick the fsm 
* @param[in]  none
* @param[out] none
* @return     none
**/
void vHpaApcStateMachineUpdate(void);


#endif /* BOOSTERAPCSTATEMACHINE_H_ */