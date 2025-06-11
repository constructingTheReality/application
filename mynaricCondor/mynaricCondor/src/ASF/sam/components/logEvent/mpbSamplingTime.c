/**
* @file 		mpbSampligTime.c
* @brief		auxliary function for stablish the sampling time for the log system
* @author		juan andres Castano
* @date			Created on 2022-08-18
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/

/* Includes ----------------------------------------------------------------- */
#include "mpbSamplingTime.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static mpbSamplingTimeType_t mpbSamplingTimeType;
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
eMpbError_t eMpbSamplingTimeInit(void)
{
	eMpbError_t eMpbError = eSuccess;
	
	mpbSamplingTimeType = mpbSamplingTimeTypeNoAlarms;
	
	return eMpbError;
}
/*-------------------------------------------------*/

eMpbError_t eMpbSamplingTimeRun( eBool_t bAlarmDetected, eBool_t bFaultDetected , mpbSamplingTimeType_t *pmpbSamplingTimeType)
{
	eMpbError_t eMpbError = eSuccess;
	
	if( mpbSamplingTimeType == mpbSamplingTimeTypeNoAlarms )
	{
		if( bAlarmDetected == eTrue )
		{
			mpbSamplingTimeType = mpbSamplingTimeTypeAlarms;
		}
	}
	else if( mpbSamplingTimeType == mpbSamplingTimeTypeAlarms )
	{
		if( bFaultDetected == eTrue )
		{
			mpbSamplingTimeType = mpbSamplingTimeTypeFaults;
		}
		else if( bAlarmDetected == eFalse )
		{
			mpbSamplingTimeType = mpbSamplingTimeTypeNoAlarms;
		}
		
	}
	else if( mpbSamplingTimeType == mpbSamplingTimeTypeFaults )
	{
		if( ( bFaultDetected == eFalse ) && (bAlarmDetected == eTrue ) )
		{
			mpbSamplingTimeType = mpbSamplingTimeTypeAlarms;
		}
		else if( ( bFaultDetected == eFalse ) && (bAlarmDetected == eFalse ) )
		{
			mpbSamplingTimeType = mpbSamplingTimeTypeNoAlarms;
		}
		
	}
	*pmpbSamplingTimeType = mpbSamplingTimeType;
	
	return eMpbError;
}

