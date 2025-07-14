/**
  * @file			test_powerSensorsAlarmValidateLimits.c
  * @brief    test file for powerSensorsAlarmValidateLimits.c
  * @author		Isabelle Champion
  * @date			Created on 07/09/24
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
#include "powerSensorsAlarmValidateLimits.h"
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
/*                     ePowerSensorValidateOutputLimits                       */
/******************************************************************************/
void test_1_1_ePowerSensorValidateOutputLimits_InvalidParam_Fail()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER + 5;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER +2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(NULL,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}

/*----------------------------------------------------------------------------*/

void test_1_2_ePowerSensorValidateOutputLimits_LimitsInRange_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_3_ePowerSensorValidateOutputLimits_LimitsInRange_Booster_Test2_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER -1;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER +1;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_4_ePowerSensorValidateOutputLimits_LimitsEqual_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_5_ePowerSensorValidateOutputLimits_UpperLimitLessThanLowerLimit_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_6_ePowerSensorValidateOutputLimits_UpperLimitTooHigh_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER +3;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_7_ePowerSensorValidateOutputLimits_UpperLimitTooLow_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER-1;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER-2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_8_ePowerSensorValidateOutputLimits_LowerLimitTooHigh_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER +3;
  float fLowAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER +2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_9_ePowerSensorValidateOutputLimits_LowerLimitTooLow_Booster_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER -2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_10_ePowerSensorValidateOutputLimits_LimitsInRange_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_11_ePowerSensorValidateOutputLimits_LimitsInRange_Lna_Test2_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA -1;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA +1;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_12_ePowerSensorValidateOutputLimits_LimitsEqual_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  float fLowAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_13_ePowerSensorValidateOutputLimits_UpperLimitLessThanLowerLimit_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  float fLowAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_14_ePowerSensorValidateOutputLimits_UpperLimitTooHigh_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA+3;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_15_ePowerSensorValidateOutputLimits_UpperLimitTooLow_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA-1;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA-2;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_16_ePowerSensorValidateOutputLimits_LowerLimitTooHigh_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA +3;
  float fLowAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA +2;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_1_17_ePowerSensorValidateOutputLimits_LowerLimitTooLow_Lna_Success()
{
  eBool_t pbOutputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  float fLowAlarmLimitBoosterPowerOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA -2;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateOutputLimits(&pbOutputCheckC408,fHighAlarmLimitBoosterPowerOutput,fLowAlarmLimitBoosterPowerOutput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbOutputCheckC408);

}

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                     ePowerSensorValidateInputLimits                        */
/******************************************************************************/

void test_2_1_ePowerSensorValidateInputLimits_InvalidParam_Fail()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER + 5;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER +2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(NULL,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}

/*----------------------------------------------------------------------------*/

void test_2_2_ePowerSensorValidateInputLimits_LimitsInRange_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_3_ePowerSensorValidateInputLimits_LimitsInRange_Booster_Test2_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER -1;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER +1;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_4_ePowerSensorValidateInputLimits_LimitsEqual_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_5_ePowerSensorValidateInputLimits_UpperLimitLessThanLowerLimit_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_6_ePowerSensorValidateInputLimits_UpperLimitTooHigh_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER +3;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_7_ePowerSensorValidateInputLimits_UpperLimitTooLow_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER-1;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER-2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_8_ePowerSensorValidateInputLimits_LowerLimitTooHigh_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER +3;
  float fLowAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER +2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_9_ePowerSensorValidateInputLimits_LowerLimitTooLow_Booster_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER -2;
  eBool_t bIsBooster = eTrue;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_10_ePowerSensorValidateInputLimits_LimitsInRange_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_11_ePowerSensorValidateInputLimits_LimitsInRange_Lna_Test2_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA -1;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA +1;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eTrue, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_12_ePowerSensorValidateInputLimits_LimitsEqual_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  float fLowAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_13_ePowerSensorValidateInputLimits_UpperLimitLessThanLowerLimit_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  float fLowAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_14_ePowerSensorValidateInputLimits_UpperLimitTooHigh_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA+3;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_15_ePowerSensorValidateInputLimits_UpperLimitTooLow_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA-1;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA-2;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_16_ePowerSensorValidateInputLimits_LowerLimitTooHigh_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA +3;
  float fLowAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA +2;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);
}

/*----------------------------------------------------------------------------*/

void test_2_17_ePowerSensorValidateInputLimits_LowerLimitTooLow_Lna_Success()
{
  eBool_t pbInputCheckC408 = eFalse;
  float fHighAlarmLimitBoosterPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  float fLowAlarmLimitBoosterPowerInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA -2;
  eBool_t bIsBooster = eFalse;

  eMpbError = ePowerSensorValidateInputLimits(&pbInputCheckC408,fHighAlarmLimitBoosterPowerInput,fLowAlarmLimitBoosterPowerInput,bIsBooster);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL(eFalse, pbInputCheckC408);

}

/*----------------------------------------------------------------------------*/