/**
* @file         mpbSampligTime.h
* @brief        auxliary function for stablish the sampling time for the log system
* @author       juan andres Castano
* @date         Created on 2022-08-18
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2022 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/

#ifndef MPBSAMPLIGTIME_H_
#define MPBSAMPLIGTIME_H_

/* Includes ----------------------------------------------------------------- */
//#include "Defs.h"
#include "mpblibs.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */

typedef enum
{
	mpbSamplingTimeTypeNoAlarms = 0,
	mpbSamplingTimeTypeAlarms ,
	mpbSamplingTimeTypeFaults
}mpbSamplingTimeType_t;



/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

/**
* @brief      init the FSM for the sampling time determination.
* @return     Success or library error message
**/
eMpbError_t eMpbSamplingTimeInit(void);

/**
* @brief      Run the FSM for the sampling time determination.
* @param[in]  bAlarmDetected: some alarm is present in the system.
* @param[in]  bFaultDetected: some fault is present in the system.
* @return     Success or library error message
**/
eMpbError_t eMpbSamplingTimeRun( eBool_t bAlarmDetected, eBool_t bFaultDetected, mpbSamplingTimeType_t *pmpbSamplingTimeType );




#endif /* MPBSAMPLIGTIME_H_ */