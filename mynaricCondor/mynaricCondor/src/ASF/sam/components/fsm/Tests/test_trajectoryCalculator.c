/**
  * @file			test_trajectoryCalculator.c
  * @brief    test file for trajectoryCalculator.c
  * @author		Isabelle Champion
  * @date			Created on 07/23/24
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
#include "mpblibs.h"
#include "mock_laserData.h"
#include "trajectoryCalculator.h"
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
/*                         eTrajectoryCalculatorRun                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/

void test_1_1_vTrajectoryCalculatorRun_InvalidParams_Fail()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 90;
  uint16_t usCurrentRead = 10;
  uint16_t pNumberOfSteps = 5;
  eBool_t pbIncrease = eTrue;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  NULL, &pbIncrease);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

  eMpbError = eSuccess;
  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  NULL, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_1_2_vTrajectoryCalculatorRun_SetpointGreaterThanCurrent_test1_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 90;
  uint16_t usCurrentRead = 15;
  uint16_t pNumberOfSteps;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eTrue, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(4, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_3_vTrajectoryCalculatorRun_SetpointGreaterThanCurrent_test2_Success()
{
  uint16_t usStepSize = 80;
  uint16_t usSetpoint = 90;
  uint16_t usCurrentRead = 10;
  uint16_t pNumberOfSteps;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eTrue, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(1, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_4_vTrajectoryCalculatorRun_SetpointGreaterThanCurrent_test3_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 90;
  uint16_t usCurrentRead = 80;
  uint16_t pNumberOfSteps;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eTrue, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(1, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_5_vTrajectoryCalculatorRun_SetpointGreaterThanCurrent_test4_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 82;
  uint16_t usCurrentRead = 0;
  uint16_t pNumberOfSteps;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eTrue, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(5, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_6_vTrajectoryCalculatorRun_SetpointEqualToCurrent_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 90;
  uint16_t usCurrentRead = 90;
  uint16_t pNumberOfSteps;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eFalse, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(0, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_7_vTrajectoryCalculatorRun_SetpointLessThanCurrent_test1_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 100;
  uint16_t usCurrentRead = 130;
  uint16_t pNumberOfSteps;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eFalse, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(2, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_8_vTrajectoryCalculatorRun_SetpointLessThanCurrent_test2_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 100;
  uint16_t usCurrentRead = 120;
  uint16_t pNumberOfSteps = 5;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eFalse, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(1, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_9_vTrajectoryCalculatorRun_SetpointLessThanCurrent_test3_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 100;
  uint16_t usCurrentRead = 103;
  uint16_t pNumberOfSteps = 5;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eFalse, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(1, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_10_vTrajectoryCalculatorRun_SetpointLessThanCurrent_test4_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 20;
  uint16_t usCurrentRead = 120;
  uint16_t pNumberOfSteps = 5;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eFalse, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(5, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/

void test_1_11_vTrajectoryCalculatorRun_SetpointGreaterThanCurrent_test5_Success()
{
  uint16_t usStepSize = 20;
  uint16_t usSetpoint = 120;
  uint16_t usCurrentRead = 20;
  uint16_t pNumberOfSteps = 5;
  eBool_t pbIncrease = eFalse;


  eMpbError = eTrajectoryCalculatorRun(usStepSize, usSetpoint, usCurrentRead,  &pNumberOfSteps, &pbIncrease);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT8(eTrue, pbIncrease);
  TEST_ASSERT_EQUAL_UINT16(5, pNumberOfSteps);

}

/*----------------------------------------------------------------------------*/