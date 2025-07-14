/**
  * @file			test_powerSensorsBoosterAlarm.c
  * @brief    test file for powerSensorsBoosterAlarm.c
  * @author		Isabelle Champion
  * @date			Created on 06/12/24
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
#include "powerSensorsBoosterAlarm.h"
#include "dictionaryUtils.h"
#include "mpbLosDetector.h"
#include "powerSensorsAlarmValidateLimits.h"
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
/*                       ePowerSensorBoosterAlarmRun                          */
/******************************************************************************/

void test_1_1_ePowerSensorBoosterAlarmRun_InvalidParams_Fail()
{
  xLosValues_t xpLosValues;
  xLosStates_t pxLosStates;
  eBool_t bHpaPowerLosAlarm;
  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;

  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;


  float fMockInputPowerReaded;
  float fMockOutputPowerReaded;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  eMpbError = ePowerSensorBoosterAlarmRun(NULL, &pxLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, NULL, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, NULL, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, &bHpaPowerLosAlarm, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(NULL, NULL, NULL, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, &bHpaPowerLosAlarm, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, NULL, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(NULL, &pxLosStates, NULL, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(&xpLosValues, &pxLosStates, NULL, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(NULL, &pxLosStates, &bHpaPowerLosAlarm, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(NULL, NULL, NULL, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, NULL );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = ePowerSensorBoosterAlarmRun(NULL, NULL, NULL, NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_1_2_ePowerSensorBoosterAlarmRun_NoAlarmSet_NoLos_Success()
{

  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -1.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;


  float fMockInputPowerReaded = 5.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}

/*----------------------------------------------------------------------------*/

void test_1_3_ePowerSensorBoosterAlarmRun_InputLowLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -11.0f;
  float fMockOutputPowerReaded = 17.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_1_4_ePowerSensorBoosterAlarmRun_InputHighLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 401.0f;
  float fMockOutputPowerReaded = 30.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eFalse;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

  
}
/*----------------------------------------------------------------------------*/

void test_1_5_ePowerSensorBoosterAlarmRun_OutputLowLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -9.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 5.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 17.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 30.5f;

  float fMockInputPowerReaded = 5.0f;
  float fMockOutputPowerReaded = -15.31f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_6_ePowerSensorBoosterAlarmRun_OutputHighLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 5.0f;
  float fMockOutputPowerReaded = 300.41f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_7_ePowerSensorBoosterAlarmRun_InputLow_And_OutputLowLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -19.0f;
  float fMockOutputPowerReaded = -17.4f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_8_ePowerSensorBoosterAlarmRun_InputHigh_And_OutputHighLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 402.0f;
  float fMockOutputPowerReaded = 302.4f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eFalse;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_9_ePowerSensorBoosterAlarmRun_InputHigh_And_OutputLowLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 402.0f;
  float fMockOutputPowerReaded = -16.5f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eFalse;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_10_ePowerSensorBoosterAlarmRun_InputLow_And_OutputHighLimitAlarm_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -100.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -11.0f;
  float fMockOutputPowerReaded = 300.5f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}

/*----------------------------------------------------------------------------*/

void test_1_11_ePowerSensorBoosterAlarmRun_NoAlarm_Los_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -8.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eFallingAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -9.5f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eFalse;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
  
}
/*----------------------------------------------------------------------------*/

void test_1_12_ePowerSensorBoosterAlarmRun_OutputLowLimitAlarm_Los_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -8.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eFallingAndSet;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 6.0f;
  float fMockOutputPowerReaded = -16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eFalse;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_13_ePowerSensorBoosterAlarmRun_OutputHighLimitAlarm_Los_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -8.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eFallingAndSet;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -9.5f;
  float fMockOutputPowerReaded = 400.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eFalse;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_14_ePowerSensorBoosterAlarmRun_InputHighLimitAlarm_Los_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -8.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eRisingAndSet;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 7.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eFalse;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eFalse;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/

void test_1_15_ePowerSensorBoosterAlarmRun_OutputHigh_And_InputHighLimitAlarm_Los_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -8.0f;
  // clear threshold
  xLosValues.fLosClear = 200.0f;
  // current state
  xLosStates_t xLosStates = eRisingAndSet;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 150.0f;
  float fMockOutputPowerReaded = 400.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eFalse;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eFalse;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eTrue, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);
 
  // Invalid CAN 
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}
/*----------------------------------------------------------------------------*/


void test_1_16_ePowerSensorBoosterAlarmRun_HighInputLimitLessThanLowInputLimit_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = -10.1f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -11.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_17_ePowerSensorBoosterAlarmRun_HighInputLimitEqualToLowInputLimit_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = -10.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -11.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eFalse;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_18_ePowerSensorBoosterAlarmRun_HighOutputLimitLessThanLowOutputLimit_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 14.9f;

  float fMockInputPowerReaded = 5.0f;
  float fMockOutputPowerReaded = 15.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_19_ePowerSensorBoosterAlarmRun_HighOutputEqualToLowOutputLimit_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 15.0f;

  float fMockInputPowerReaded = 5.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eFalse;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eFalse;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_20_ePowerSensorBoosterAlarmRun_LowInputLimitBelowThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -11.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 5.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_21_ePowerSensorBoosterAlarmRun_LowInputLimitAboveThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = 6.1f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.3f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 6.2f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}
/*----------------------------------------------------------------------------*/

void test_1_22_ePowerSensorBoosterAlarmRun_HighInputLimitBelowThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -12.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = -11.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = -11.5f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}


/*----------------------------------------------------------------------------*/

void test_1_23_ePowerSensorBoosterAlarmRun_HighInputLimitAboveThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 7.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 6.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_24_ePowerSensorBoosterAlarmRun_LowOutputLimitBelowThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = -15.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.5f;

  float fMockInputPowerReaded = 6.0f;
  float fMockOutputPowerReaded = 16.0f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_25_ePowerSensorBoosterAlarmRun_LowOutputLimitAboveThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 38.6f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.7f;

  float fMockInputPowerReaded = 6.0f;
  float fMockOutputPowerReaded = 38.65f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}

/*----------------------------------------------------------------------------*/

void test_1_26_ePowerSensorBoosterAlarmRun_HighOutputLimitBelowThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 13.0f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 14.0f;

  float fMockInputPowerReaded = 6.0f;
  float fMockOutputPowerReaded = 13.5f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}


/*----------------------------------------------------------------------------*/

void test_1_27_ePowerSensorBoosterAlarmRun_HighOutputAboveBelowThreshold_NoLos_Success()
{
  xLosValues_t xLosValues;
  // set threshold
  xLosValues.fLosSet = -18.0f;
  // clear threshold
  xLosValues.fLosClear = 40.0f;
  // current state
  xLosStates_t xLosStates = eValidAndClear;

  eBool_t bHpaPowerLosAlarm = eFalse;

  MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment_428;
  c408StatusDefinition_t c408StatusDefinition;
  // Low Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;
  // High Limit Input
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 6.0f;
  // Low Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.2f;
  // High Limit Output
  c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 39.0f;

  float fMockInputPowerReaded = 6.0f;
  float fMockOutputPowerReaded = 17.5f;
  xAlarmAndStatusRegister_t pxAlarmRegister_402;
  eBool_t pbBoosterPowerCriticalAlarm;

  // Any Input alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus = eTrue;
  // Any Output Alarm
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = eTrue;
  // Output too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh = eTrue;
  // Input too High
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh = eTrue;
  // LOS alarm (input)
  pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm = eTrue;

  pbBoosterPowerCriticalAlarm = eFalse;
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;

  // Invalid CAN 
  pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

  eMpbError = ePowerSensorBoosterAlarmRun(&xLosValues, &xLosStates, &bHpaPowerLosAlarm, &pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister_402, &pbBoosterPowerCriticalAlarm );
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  // Any Input Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus);
  // Any Output Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus);
  // Output too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterOutputPowerIsTooHigh);
  // Input too High
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerIsTooHigh);
  
  // LOS alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment_428.bBoosterInputPowerLOSAlarm);

  TEST_ASSERT_EQUAL_INT8(eFalse, pbBoosterPowerCriticalAlarm);
  TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag);

  // Invalid CAN flag
  TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister_402.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
 
}
/*----------------------------------------------------------------------------*/
