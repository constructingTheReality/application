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
#ifndef MAINSTATEMACHINE_H_
#define MAINSTATEMACHINE_H_/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "LaserData.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
enum eMainLoopStates
{
	eMainLoopStateStartup = 0,
	eMainLoopStateShutDown,
	eMainLoopStateInit,
	eMainLoopStateReset,
	eMainLoopStateCriticalError
	//eMainLoopStateTest,
	//eMainLoopStateIdentification	
};

typedef enum eMainLoopStates eMainLoopState_t ;

void eMainLoopStateStartupFunction(void);
void eMainLoopStateShutDownFunction(void);
void eMainLoopStateInitFunction(void);
void eMainLoopStateResetFunction(void);
void eMainLoopStateCriticalErrorFunction(void);
//void eMainLoopStateTestFunction(void);
//void eMainLoopStateIdentificationFunction(void);


/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief		Init the laser beams
*/
void vMainStateMachineInit( void );
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vMainStateMachineUpdate(void);

/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
eMainLoopState_t eReportState(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vSetAlarmCurrentInLna(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vClearAlarmCurrentInLna(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vSetAlarmCriticalError(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vSetResetState(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vSetAlarmIsDetected(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
eBool_t bMainFsmHpaGetStuckCondition(void);

#endif /* __MAINSTATEMACHINE_H */




