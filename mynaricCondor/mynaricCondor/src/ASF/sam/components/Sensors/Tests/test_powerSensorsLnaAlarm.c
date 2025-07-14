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
#include "powerSensorsLnaAlarm.h"
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
/*                        ePowerSensorLnaAlarmRun                             */
/******************************************************************************/

void test_2_1_ePowerSensorLnaAlarmRun_InvalidParams_Fail()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	float fMockInputPowerReaded;
	float fMockOutputPowerReaded;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	eMpbError = ePowerSensorLnaAlarmRun(NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, NULL );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorLnaAlarmRun(NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorLnaAlarmRun(NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister,NULL );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL,NULL );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorLnaAlarmRun(NULL, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, NULL,NULL );
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}

/*----------------------------------------------------------------------------*/

void test_2_2_ePowerSensorLnaAlarmRun_InputLowLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -50.1f;
	float fMockOutputPowerReaded = 1.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_3_ePowerSensorLnaAlarmRun_InputHighLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = 400.01f;
	float fMockOutputPowerReaded = 0.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eTrue, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);
	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/


void test_2_4_ePowerSensorLnaAlarmRun_OutputHighLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -50.00f;
	float fMockOutputPowerReaded = 350.5f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eFalse;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eTrue, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_5_ePowerSensorLnaAlarmRun_OutputLowLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -25.0f;
	float fMockOutputPowerReaded = -23.3f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);
	
	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}

/*----------------------------------------------------------------------------*/

void test_2_6_ePowerSensorLnaAlarmRun_NoAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -20.0f;
	float fMockOutputPowerReaded = -16.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/
void test_2_7_ePowerSensorLnaAlarmRun_OutputHigh_And_InputHighLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -19.9f;
	float fMockOutputPowerReaded = 1.1f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eFalse;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eTrue, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/
void test_2_8_ePowerSensorLnaAlarmRun_OutputLow_And_InputLowLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -50.01f;
	float fMockOutputPowerReaded = -16.01f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_9_ePowerSensorLnaAlarmRun_OutputHigh_And_InputLowLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -49.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -21.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -15.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 0.0f;

	float fMockInputPowerReaded = -50.0f;
	float fMockOutputPowerReaded = 1.3f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eFalse;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eTrue, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_10_ePowerSensorLnaAlarmRun_OutputLow_And_InputHighLimitAlarm_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -19.9f;
	float fMockOutputPowerReaded = -17.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 1;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eTrue, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_11_ePowerSensorLnaAlarmRun_LowInputLimitGreaterThanHighInputLimit_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -19.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -20.0f;
	float fMockOutputPowerReaded = 1.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_12_ePowerSensorLnaAlarmRun_LowInputLimitEqualToHighInputLimit_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -20.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -20.0f;
	float fMockOutputPowerReaded = 1.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_13_ePowerSensorLnaAlarmRun_LowOutputLimitGreaterThanHighOutputLimit_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = -17.0f;

	float fMockInputPowerReaded = -30.0f;
	float fMockOutputPowerReaded = -20.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_14_ePowerSensorLnaAlarmRun_LowOutputLimitEqualToHighOutputLimit_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;

	float fMockInputPowerReaded = -30.0f;
	float fMockOutputPowerReaded = -20.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eFalse;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/


void test_2_15_ePowerSensorLnaAlarmRun_LowInputLimitBelowLowThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -51.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -30.0f;
	float fMockOutputPowerReaded = -10.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eTrue;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_16_ePowerSensorLnaAlarmRun_LowInputLimitAboveUpperThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = 19.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = 22.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = 22.5f;
	float fMockOutputPowerReaded = -10.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_17_ePowerSensorLnaAlarmRun_HighInputLimitBelowThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -55.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -53.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = -30.0f;
	float fMockOutputPowerReaded = -10.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_18_ePowerSensorLnaAlarmRun_HighInputLimitAboveThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = 1.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = 3.0f;
	float fMockOutputPowerReaded = -10.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_19_ePowerSensorLnaAlarmRun_LowOutputLimitBelowThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -17.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 1.0f;

	float fMockInputPowerReaded = 3.0f;
	float fMockOutputPowerReaded = -10.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_20_ePowerSensorLnaAlarmRun_LowOutputLimitAboveThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = 2.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 3.0f;

	float fMockInputPowerReaded = 3.0f;
	float fMockOutputPowerReaded = 2.5f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_21_ePowerSensorLnaAlarmRun_HighOutputLimitBelowThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = -17.0f;

	float fMockInputPowerReaded = 30.0f;
	float fMockOutputPowerReaded = -17.0f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_22_ePowerSensorLnaAlarmRun_HighOutputLimitAboveThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 3.0f;

	float fMockInputPowerReaded = 3.0f;
	float fMockOutputPowerReaded = 2.5f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

void test_2_23_ePowerSensorLnaAlarmRun_HighOutputLimitAboveThreshold_and_HighInputLimitAboveThreshold_Success()
{
	MpbAlarmsAndStatusRegisterBitAssignment_t pMpbAlarmsAndStatusRegisterBitAssignment;
	c408StatusDefinition_t c408StatusDefinition;
	// Low Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;
	// High Limit Input
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -19.0f;
	// Low Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -16.0f;
	// High Limit Output
	c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 3.0f;

	float fMockInputPowerReaded = 3.0f;
	float fMockOutputPowerReaded = 2.5f;
	xAlarmAndStatusRegister_t pxAlarmRegister;
	eBool_t bLnaPowerCriticalAlarm;

	// Any Input alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = eFalse;
	// Any Output alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = eTrue;
	// Any High alarm
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag = 0;
	bLnaPowerCriticalAlarm = eFalse;

	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow = eTrue;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh = eFalse;
	pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh = eTrue;

	// Invalid CAN
	pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag = 0;

	eMpbError = ePowerSensorLnaAlarmRun(&pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition, fMockInputPowerReaded, fMockOutputPowerReaded, &pxAlarmRegister, &bLnaPowerCriticalAlarm );
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	// Any Input Alarm
	TEST_ASSERT_EQUAL_INT8(eTrue, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus);
	// Ant Output Alarm
	TEST_ASSERT_EQUAL_INT8(eFalse, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus);
	// Critical Alarm (smt is too high and CAN valid)
	TEST_ASSERT_EQUAL_INT32(0, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInternalCriticalErrorInPowerFlag);
	TEST_ASSERT_EQUAL_INT8(eFalse, bLnaPowerCriticalAlarm);
	// Output Low
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow);
	// Input High
	TEST_ASSERT_EQUAL_INT8(eTrue, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh);
	// Output High
	TEST_ASSERT_EQUAL_INT8(eFalse, pMpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh);

	// Invalid CAN 
    TEST_ASSERT_EQUAL_INT8(1, pxAlarmRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);

}
/*----------------------------------------------------------------------------*/

