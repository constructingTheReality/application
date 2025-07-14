/**
  * @file			test_currentSensorsLnaAlarm.c
  * @brief    test file for test_currentSensorsLnaAlarm.c
  * @author		Isabelle Champion
  * @date			Created on 06/19/24
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
#include "currentSensorsLnaAlarm.h"
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
/*                        eCurrentSensorsLnaAlarmRun                          */
/******************************************************************************/

void test_1_1_eCurrentSensorsLnaAlarmRun_InvalidParams_Fail()
{

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
  c409StatusDefinition_t c409StatusDefinition;
  float fCurrentReaded = 3.5;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pLnaCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsLnaAlarmRun(NULL, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, NULL, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(NULL, c409StatusDefinition, fCurrentReaded, NULL, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, NULL, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(NULL, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(NULL, c409StatusDefinition, fCurrentReaded, NULL, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_1_2_eCurrentSensorsLnaAlarmRun_c409AlarmLowLimit_EqualTo_AlarmHighLimit_Fail()
{
  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
  c409StatusDefinition_t c409StatusDefinition;

  c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.9;
  c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 0.9;

  float fCurrentReaded = 3.5;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pLnaCurrentCriticalAlarm = eFalse;

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_1_3_eCurrentSensorsLnaAlarmRun_c409AlarmLowLimit_GreaterThan_AlarmHighLimit_Fail()
{
  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
  c409StatusDefinition_t c409StatusDefinition;

  c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 7.9;
  c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 0.9;

  float fCurrentReaded = 3.5;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pLnaCurrentCriticalAlarm = eFalse;

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_1_4_eCurrentSensorsLnaAlarmRun_NoAlarm_Success()
{
  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
  c409StatusDefinition_t c409StatusDefinition;

  c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.9;
  c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 5.9;

  float fCurrentReaded = 3.5;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pLnaCurrentCriticalAlarm = eFalse;

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bLnaCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(0, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus );
  TEST_ASSERT_EQUAL_INT8(eFalse, pLnaCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/

void test_1_5_eCurrentSensorsLnaAlarmRun_LowAlarm_Success()
{
  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
  c409StatusDefinition_t c409StatusDefinition;

  c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.9;
  c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 5.9;

  float fCurrentReaded = -3.5;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pLnaCurrentCriticalAlarm = eFalse;

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bLnaCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(0, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus );
  TEST_ASSERT_EQUAL_INT8(eTrue, pLnaCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/

void test_1_6_eCurrentSensorsLnaAlarmRun_HighAlarm_Success()
{
  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
  c409StatusDefinition_t c409StatusDefinition;

  c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.9;
  c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 5.9;

  float fCurrentReaded = 13.5;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pLnaCurrentCriticalAlarm = eFalse;

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition, fCurrentReaded, &pxAlarmRegister, &pLnaCurrentCriticalAlarm);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bLnaCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus );
  TEST_ASSERT_EQUAL_INT8(eTrue, pLnaCurrentCriticalAlarm);
}

/*----------------------------------------------------------------------------*/
