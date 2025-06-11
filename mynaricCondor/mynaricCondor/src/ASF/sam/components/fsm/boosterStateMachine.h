/**
* @file		    boosterStateMachine.h
* @brief        boosterStateMachine header file.
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
#ifndef BOOSTERSTATEMACHINE_H_
#define BOOSTERSTATEMACHINE_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "LaserData.h"
#include "boosterApcStateMachine.h"
/* Define ------------------------------------------------------------------- */
#define		CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1_APC  ( 500 )
#define		NUMBER_OF_CONTROL_LOOPS  ( 2 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
enum eBoosterStates
{	
	eBoosterLoopStateDisable =0,
	eBoosterLoopStateStandby,
	eBoosterLoopStateApc,
	eBoosterLoopStateAcc
};

typedef enum eBoosterStates eBoosterState_t ;

void eBoosterLoopStateDisableFunction(void);
void eBoosterLoopStateStandbyFunction(void);
void eBoosterLoopStateApcFunction(void);
void eBoosterLoopStateAccFunction(void);
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
* @brief      shutdown the lasers in case of critical error 
* @param[in]  none
* @param[out] none
* @return     none
**/
void vHpaCriticalErrorDetected( void );
/**
* @brief      execute the disable sequence for the lasers diodes 
* @param[in]  none
* @param[out] none
* @return     none
**/
void vHpaDisableSequence( void );
/**
* @brief      re-start the FSM 
* @param[in]  none
* @param[out] none
* @return     none
**/
void vBoosterStateMachineInit( void);
/**
* @brief      run the FSM
* @param[in]  none
* @param[out] none
* @return     none
**/
void vBoosterStateMachineUpdate(void);
/**
* @brief      report actual state of the FSM
* @param[in]  none
* @param[out] none
* @return     eBoosterState actual
**/
eBoosterState_t eBoosterReportState(void);
/**
* @brief      report actual state of the apc FSM
* @param[in]  none
* @param[out] none
* @return     eHpaApcState actual
**/
eHpaApcState_t eBoosterApcReportState(void);
/**
* @brief      disable Hpa line
* @param[in]  none
* @param[out] none
* @return     none 
**/
void vSetDisableHpa( void);
/**
* @brief      reset Hpa alarms
* @param[in]  none
* @param[out] none
* @return     none
**/
void vResetHpaAlarms( void);
/**
* @brief      red stuck state 
* @param[in]  none
* @param[out] none
* @return     none
**/
eBool_t bBoosterGetStuckCondition(void);

eBool_t bIsHpaReadyForReset(void);
void vHpaReadyForReset(void);
#endif /* BOOSTERSTATEMACHINE_H_ */