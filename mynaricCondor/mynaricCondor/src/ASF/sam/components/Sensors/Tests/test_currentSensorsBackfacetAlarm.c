/**
  * @file			test_currentSensorsBackfacetAlarm.c
  * @brief    test file for test_currentSensorsBackfacetAlarm.c
  * @author		Isabelle Champion
  * @date			Created on 06/20/24
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2024 MPB, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB </center>
  *
  **/
/* Includes ------------------------------------------------------------------*/

#include "unity.h"
#include "currentSensorsBackfacetAlarm.h"
#include "dictionaryUtils.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
eMpbError_t eMpbError;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
 
void setUp()
{
  
}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{
  
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                    eCurrentSensorsBackfacetAlarmRun                        */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void test_4_1_eCurrentSensorsBackfacetAlarmRun_InvalidParams_Fail()
{
  float fLnaBackfacetCurrentReaded = 3.2;
  float fHpaBackfacetCurrentReaded = 3.4;
  float fLnaBackfacetLimit = 5.4;
  float  fBackfacetHpaLimit = 3.2;
  AlarmsAndStatusRegisterBitAssignment_t pAlarmsAndStatusRegisterBitAssignment;
  eBool_t pLnaBackfacetCurrentCriticalAlarm;
  eBool_t pHpaBackfacetCurrentCriticalAlarm;

  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , NULL, &pLnaBackfacetCurrentCriticalAlarm, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, NULL, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, &pLnaBackfacetCurrentCriticalAlarm, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, NULL, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , NULL, &pLnaBackfacetCurrentCriticalAlarm, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , NULL, NULL, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , NULL, NULL, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  
}

/*----------------------------------------------------------------------------*/

void test_4_2_eCurrentSensorsBackfacetAlarmRun_NoError_Success()
{
  float fLnaBackfacetCurrentReaded = 7.2;
  float fHpaBackfacetCurrentReaded = 7.4;
  float fLnaBackfacetLimit = 4.4;
  float  fBackfacetHpaLimit = 4.2;
  AlarmsAndStatusRegisterBitAssignment_t pAlarmsAndStatusRegisterBitAssignment;
  eBool_t pLnaBackfacetCurrentCriticalAlarm;
  eBool_t pHpaBackfacetCurrentCriticalAlarm;

  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, &pLnaBackfacetCurrentCriticalAlarm, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(0, pAlarmsAndStatusRegisterBitAssignment.bHpaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(0, pAlarmsAndStatusRegisterBitAssignment.bLnaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pHpaBackfacetCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(eFalse, pLnaBackfacetCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/

void test_4_3_eCurrentSensorsBackfacetAlarmRun_LnaError_Success()
{
  float fLnaBackfacetCurrentReaded = -7.2;
  float fHpaBackfacetCurrentReaded = 7.4;
  float fLnaBackfacetLimit = 4.4;
  float  fBackfacetHpaLimit = 4.2;
  AlarmsAndStatusRegisterBitAssignment_t pAlarmsAndStatusRegisterBitAssignment;
  eBool_t pLnaBackfacetCurrentCriticalAlarm;
  eBool_t pHpaBackfacetCurrentCriticalAlarm;

  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, &pLnaBackfacetCurrentCriticalAlarm, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(0, pAlarmsAndStatusRegisterBitAssignment.bHpaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(1, pAlarmsAndStatusRegisterBitAssignment.bLnaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pHpaBackfacetCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(eTrue, pLnaBackfacetCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/

void test_4_4_eCurrentSensorsBackfacetAlarmRun_HpaError_Success()
{
  float fLnaBackfacetCurrentReaded = -7.2;
  float fHpaBackfacetCurrentReaded = 7.4;
  float fLnaBackfacetLimit = 4.4;
  float  fBackfacetHpaLimit = 4.2;
  AlarmsAndStatusRegisterBitAssignment_t pAlarmsAndStatusRegisterBitAssignment;
  eBool_t pLnaBackfacetCurrentCriticalAlarm;
  eBool_t pHpaBackfacetCurrentCriticalAlarm;

  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, &pLnaBackfacetCurrentCriticalAlarm, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(0, pAlarmsAndStatusRegisterBitAssignment.bHpaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(1, pAlarmsAndStatusRegisterBitAssignment.bLnaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pHpaBackfacetCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(eTrue, pLnaBackfacetCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/

void test_4_5_eCurrentSensorsBackfacetAlarmRun_HpaAndLnaError_Success()
{
  float fLnaBackfacetCurrentReaded = -7.2;
  float fHpaBackfacetCurrentReaded = -7.4;
  float fLnaBackfacetLimit = 4.4;
  float  fBackfacetHpaLimit = 4.2;
  AlarmsAndStatusRegisterBitAssignment_t pAlarmsAndStatusRegisterBitAssignment;
  eBool_t pLnaBackfacetCurrentCriticalAlarm;
  eBool_t pHpaBackfacetCurrentCriticalAlarm;

  eMpbError = eCurrentSensorsBackfacetAlarmRun(fLnaBackfacetCurrentReaded ,fHpaBackfacetCurrentReaded ,fLnaBackfacetLimit ,fBackfacetHpaLimit , &pAlarmsAndStatusRegisterBitAssignment, &pLnaBackfacetCurrentCriticalAlarm, &pHpaBackfacetCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(1, pAlarmsAndStatusRegisterBitAssignment.bHpaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(1, pAlarmsAndStatusRegisterBitAssignment.bLnaBackfacetCurrentErrorFlag);
  TEST_ASSERT_EQUAL_INT8(eTrue, pHpaBackfacetCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(eTrue, pLnaBackfacetCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/