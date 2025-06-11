/**
* @file		    lnaStateMachine.h
* @brief        lnaStateMachine header file.
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
#ifndef LNASTATEMACHINE_H_
#define LNASTATEMACHINE_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
//#include "ControlAlarm.h"
//#include "CurrentSensor.h"
//#include "temperature.h"
//#include "PowerSensor.h"
//#include "BSPGpio.h"
#include "LaserData.h"

/* Define ------------------------------------------------------------------- */
#define		CURRENT_INCREASE_BY_STEP_IN_MA  ( 50 )

#define INIT_TMO  								( 10 )

#define X1_APC_LNA_SETPOINT							( 0.0)
#define Y1_APC_LNA_SETPOINT							( 0.03162 )    // -15 DBM IN m WATSS
#define X2_APC_LNA_SETPOINT							( 1023.0 )
#define Y2_APC_LNA_SETPOINT							( 0.6237 )    // 0 dBm IN m WATSS


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
enum eLnaStates
{
	eLnaLoopStateDisable = 0,
	eLnaLoopStateStandby,
	eLnaLoopStateApc,
	eLnaLoopStateAcc,
	eLnaLoopStateidentification,
};

typedef enum eLnaStates eLnaState_t ;

void eLnaLoopStateDisableFunction(void);
void eLnaLoopStateStandbyFunction(void);
void eLnaLoopStateApcFunction(void);
void eLnaLoopStateAccFunction(void);
void eLnaLoopStateIdentificationFunction(void);
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vLnaStateMachineInit( void );
/**
 * @brief 		Trigger a evolve of the LNA FSM.
 * @param[out]	none.
 */
void vLnaStateMachineUpdate(void);
/**
 * @brief 		Getter to the LNA actual state. 
 * @param[out]	none.
 */
eLnaState_t eLnaReportState(void);

/**
 * @brief 		trigger a not critical alarm. 
 * @param[out]	none.
 */
void vLnaAlarmProtocolDetected( void );
/**
 * @brief 		trigger a shutdown critical. 
 * @param[out]	none.
 */
void vLnaCriticalErrorDetected( void );
/**
 * @brief 		Send a message to go to disable state 
 * @param[out]	none.
 */
void vSetDisableLna( eBool_t bSetdisable);
/**
 * @brief 		Getter to the flag indicating the LNA is reset, and common section can reset as well 
 * @param[out]	none.
 */
eBool_t bIsLnaReadyForReset( void);

void vLnaReadyForReset( void);
#endif /* LNASTATEMACHINE_H_ */