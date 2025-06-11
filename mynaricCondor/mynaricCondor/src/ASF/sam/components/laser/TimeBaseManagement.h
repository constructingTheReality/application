/**
  * @file			TimeBaseManagement.h
  * @brief          TimeBaseManagement header file.
  * @author			juan andres
  * @date			Created on 3/3/2021
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

#ifndef __TIMEBASE_MANAGEMENT_H
#define __TIMEBASE_MANAGEMENT_H

/* Includes ----------------------------------------------------------------- */

#include "mpblibs.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */                           
/* Exported enum ------------------------------------------------------------ */
                                
/**
  * @brief  list of TimeBase.
  */
typedef enum 
{
    eAlarmTimeBase, 
    eSlowSensorsTimeBase,	
		eCriticalSensorsTimeBase,	
	  eContinuosWaveLoopControl,	
		eModulantWaveLoopControl,	
	  eApcLoopControl,	
    eTECTimeBase,
	  eBEAMTimeBase,
    eLEDStatusTimeBase,
	  eCommunicacionTimeout, 
		eChronometer980TimeBase,
		eChronometer1545TimeBase,
		eFmeaLoggerTimeBase,
		eNumberOfTimeBases,

}
eTimeBaseID_t;
                                
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
  * @brief  Initialization of all timebase structures.
  */
void vTimeBaseManagementInit( void );
//void vTimeBaseManagementInit( uint32_t ulInitValue980, uint32_t ulInitValue940 );

/**
  * @brief      Reset tick of an oppportun timebase.
  * @param[in]  eTimeBaseID: Time base ID.
  */
void vTimeBaseManagementResetTick( eTimeBaseID_t eTimeBaseID );

/**
  * @brief      Tick all timebases.
  */
void vTimeBaseManagementTick( void );
//void vTimeBaseManagementTick( eBool_t bDiode980IsEmittingPower, eBool_t bDiode1545IsEmittingPower );

/**
  * @brief      Get tick value of an opportun timebase.
  * @param[in]  eTimeBaseID: Time base ID.
  * @param[out] pulTick: Pointer on a tick.
  */
void vTimeBaseManagementGetTick( eTimeBaseID_t eTimeBaseID, uint32_t *pulTick );

#endif  /* __TIMEBASE_MANAGEMENT_H */
