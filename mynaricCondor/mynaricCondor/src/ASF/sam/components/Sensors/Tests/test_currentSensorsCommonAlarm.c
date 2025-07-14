/**
  * @file			test_currentSensorsCommonAlarm.c
  * @brief    test file for test_currentSensorsCommonAlarm.c
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
#include "currentSensorsCommonAlarm.h"
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
void test_3_1_eCurrentSensorsHpaAlarmRun_InvalidParams_Fail()
{
  c423StatusDefinition_t c423StatusDefinition;
  c428StatusDefinition_t c428StatusDefinition;
  eBool_t bInternalAlarm = eFalse;
  
  eMpbError = eCurrentSensorsCommonAlarmRun(NULL, &c428StatusDefinition, &bInternalAlarm);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsCommonAlarmRun(&c423StatusDefinition, NULL, &bInternalAlarm);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsCommonAlarmRun(&c423StatusDefinition, &c428StatusDefinition, NULL);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsCommonAlarmRun(NULL, NULL, &bInternalAlarm);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsCommonAlarmRun(NULL, &c428StatusDefinition, NULL);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsCommonAlarmRun(&c423StatusDefinition, NULL, NULL);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);
  eMpbError = eSuccess;
  eMpbError = eCurrentSensorsCommonAlarmRun(NULL, NULL, NULL);
  TEST_ASSERT_EQUAL(eMpbError, eInvalidParameter);

}
/*----------------------------------------------------------------------------*/

void test_3_2_eCurrentSensorsHpaAlarmRun_noAlarmsRaised_Success()
{
  c423StatusDefinition_t c423StatusDefinition;
  c428StatusDefinition_t c428StatusDefinition;
  c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1 = LEVEL_28V; // eFalse

  c423StatusDefinition.f3_3V_PwrVoltageMonitor = LEVEL_3V ; 
  c423StatusDefinition.f3V_ld_PwrVoltageMonitor = LEVEL_3V +1; // eFalse

  c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1 = LEVEL_7V; 
  c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2 = LEVEL_7V; // eFalse

  c423StatusDefinition.fAdcPwrCurrentMonitor = LEVEL_ADC; // eFalse

  c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1 = LEVEL_28_CURRENT; // eFalse
  c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2 = LEVEL_28_CURRENT; // eFalse
 
  c423StatusDefinition.fCanPwrCurrentMonitor1 = LEVEL_ADC; // eFalse
  c423StatusDefinition.fCanPwrCurrentMonitor2 = LEVEL_ADC; 

  c428StatusDefinition.ulMpbAlarmsValue = 0; //bInternalAlarm = 0;

  eBool_t bInternalAlarm = eFalse;
  
  eMpbError = eCurrentSensorsCommonAlarmRun(&c423StatusDefinition, &c428StatusDefinition, &bInternalAlarm);
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow);
  TEST_ASSERT_EQUAL_INT8(0, bInternalAlarm);
}
/*----------------------------------------------------------------------------*/

void test_3_3_eCurrentSensorsHpaAlarmRun_AllLowAlarmsRaised_Success()
{
  c423StatusDefinition_t c423StatusDefinition;
  c428StatusDefinition_t c428StatusDefinition;
  c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1 = LEVEL_28V -1; // eTrue

  c423StatusDefinition.f3_3V_PwrVoltageMonitor = LEVEL_3V-1; // eTrue
  c423StatusDefinition.f3V_ld_PwrVoltageMonitor = LEVEL_3V -1; // eTrue

  c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1 = LEVEL_7V; 
  c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2 = LEVEL_7V-1; // eTrue

  c423StatusDefinition.fAdcPwrCurrentMonitor = LEVEL_ADC-1; // eTrue

  c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1 = LEVEL_28_CURRENT; // eFalse
  c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2 = LEVEL_28_CURRENT-1; // eTrue
 
  c423StatusDefinition.fCanPwrCurrentMonitor1 = LEVEL_ADC-1; // eTrue
  c423StatusDefinition.fCanPwrCurrentMonitor2 = LEVEL_ADC; 

  c428StatusDefinition.ulMpbAlarmsValue = 1; //bInternalAlarm = 0;

  eBool_t bInternalAlarm = eFalse;
  
  eMpbError = eCurrentSensorsCommonAlarmRun(&c423StatusDefinition, &c428StatusDefinition, &bInternalAlarm);
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow);
  TEST_ASSERT_EQUAL_INT8(1, bInternalAlarm);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

void test_3_4_eCurrentSensorsHpaAlarmRun_someLowAlarmsRaised_Success()
{
  c423StatusDefinition_t c423StatusDefinition;
  c428StatusDefinition_t c428StatusDefinition;
  c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1 = LEVEL_28V +1; // eFalse

  c423StatusDefinition.f3_3V_PwrVoltageMonitor = LEVEL_3V ;
  c423StatusDefinition.f3V_ld_PwrVoltageMonitor = LEVEL_3V -1; // eTrue

  c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1 = LEVEL_7V -1; // eTrue
  c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2 = LEVEL_7V;

  c423StatusDefinition.fAdcPwrCurrentMonitor = LEVEL_ADC+1; // eFalse

  c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1 = LEVEL_28_CURRENT-1; // eTrue
  c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2 = LEVEL_28_CURRENT;
 
  c423StatusDefinition.fCanPwrCurrentMonitor1 = LEVEL_ADC;
  c423StatusDefinition.fCanPwrCurrentMonitor2 = LEVEL_ADC-1; // eTrue

  c428StatusDefinition.ulMpbAlarmsValue = 1; //bInternalAlarm = 0;

  eBool_t bInternalAlarm = eFalse;
  
  eMpbError = eCurrentSensorsCommonAlarmRun(&c423StatusDefinition, &c428StatusDefinition, &bInternalAlarm);
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow);
  TEST_ASSERT_EQUAL_INT8(eFalse, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow);
  TEST_ASSERT_EQUAL_INT8(eTrue, c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow);
  TEST_ASSERT_EQUAL_INT8(1, bInternalAlarm);
}
/*----------------------------------------------------------------------------*/