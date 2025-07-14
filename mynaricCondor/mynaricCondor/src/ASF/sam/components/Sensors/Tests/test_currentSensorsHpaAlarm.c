/**
  * @file			test_currentSensorsHpaAlarm.c
  * @brief    test file for test_currentSensorsHpaAlarm.c
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
#include "currentSensorsHpaAlarm.h"
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
/******************************************************************************/
/*                        eCurrentSensorsHpaAlarmRun                          */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
void test_2_1_eCurrentSensorsHpaAlarmRun_InvalidParams_Fail()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 0.4;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 0.5;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,NULL,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,NULL,NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}

/*----------------------------------------------------------------------------*/
void test_2_2_eCurrentSensorsHpaAlarmRun_LowLimitEqualToHighLimit_Fail()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 0.4;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 0.4;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/
void test_2_3_eCurrentSensorsHpaAlarmRun_LowLimitGreaterThanHighLimit_Fail()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 0.4;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = -0.4;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}
/*----------------------------------------------------------------------------*/

void test_2_4_eCurrentSensorsHpaAlarmRun_noAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/
void test_2_5_eCurrentSensorsHpaAlarmRun_Current1LowAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = -11.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/
void test_2_6_eCurrentSensorsHpaAlarmRun_Current1HighAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 11.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_7_eCurrentSensorsHpaAlarmRun_Current2LowAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = -12.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_8_eCurrentSensorsHpaAlarmRun_Current2HighAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 12.0;
  float fCurrentReaded3 = 3.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_9_eCurrentSensorsHpaAlarmRun_Current3LowAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 2.0;
  float fCurrentReaded3 = -4.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eTrue ,pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_10_eCurrentSensorsHpaAlarmRun_Current3HighAlarm_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 1.0;
  float fCurrentReaded2 = 1.0;
  float fCurrentReaded3 = 11.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_11_eCurrentSensorsHpaAlarmRun_AllAlarmsRaised_Success()
{
  c409StatusDefinition_t c409StatusDefinition;
  c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -3.1;
  c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 10.9;

  float fCurrentReaded1 = 11.0;
  float fCurrentReaded2 = -11.0;
  float fCurrentReaded3 = 11.0;
  AlarmsAndStatusRegisterBitAssignment_t pxAlarmRegister;
  eBool_t pbCurrentCriticalAlarm = eFalse;

  eMpbError = eCurrentSensorsHpaAlarmRun(c409StatusDefinition, fCurrentReaded1, fCurrentReaded2, fCurrentReaded3,&pxAlarmRegister,&pbCurrentCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bBoosterCurrentLimitAlarmStatus);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bCurrentBoosterDriver2AlarmFlag);
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.bCurrentBoosterDriver3AlarmFlag);

}
/*----------------------------------------------------------------------------*/