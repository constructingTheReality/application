/**
  * @file			test_moveCurrentToSetpoint.c
  * @brief    test file for moveCurrentToSetpoint.c
  * @author		Isabelle Champion
  * @date			Created on 07/31/24
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
#include "moveCurrentToSetpoint.h"

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
/*                         eShiftCurrentTowardsSetpoint                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/

void test_1_1_eShiftCurrentTowardsSetpoint_InvalidParams_Fail()
{
  // increase per step: 50
  uint16_t usSetpointInmA = 153;
  uint16_t usNumberOfSteps = 3;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 0;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  NULL,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  eMpbError = eSuccess;
  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  eMpbError = eSuccess;
  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  NULL,  bIncrease, NULL);
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);


}

/*----------------------------------------------------------------------------*/

void test_1_2_eShiftCurrentTowardsSetpoint_Increase_fullAndPartialSteps_test1_Success()
{
  uint16_t usSetpointInmA = 153;
  uint16_t usNumberOfSteps = 4;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 0;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(50, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(100, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(150, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(usSetpointInmA, usCurrentRead);


}

/*----------------------------------------------------------------------------*/


void test_1_3_eShiftCurrentTowardsSetpoint_Increase_fullAndPartialSteps_test2_Success()
{
  uint16_t usSetpointInmA = 149;
  uint16_t usNumberOfSteps = 3;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 1;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(51, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(101, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(usSetpointInmA, usCurrentRead);


}

/*----------------------------------------------------------------------------*/

void test_1_4_eShiftCurrentTowardsSetpoint_Increase_OnlyFullSteps_Success()
{
  uint16_t usSetpointInmA = 150;
  uint16_t usNumberOfSteps = 3;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 1;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(51, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(101, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(150, usCurrentRead);


}

/*----------------------------------------------------------------------------*/

void test_1_5_eShiftCurrentTowardsSetpoint_noStepsNeeded_Success()
{
  uint16_t usSetpointInmA = 150;
  uint16_t usNumberOfSteps = 0;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 150;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(150, usCurrentRead);

}

/*----------------------------------------------------------------------------*/

void test_1_6_eShiftCurrentTowardsSetpoint_tooManyStepsCalculated_Success()
{
  uint16_t usSetpointInmA = 150;
  uint16_t usNumberOfSteps = 1;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 150;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(150, usCurrentRead);

}

/*----------------------------------------------------------------------------*/

void test_1_7_eShiftCurrentTowardsSetpoint_Decrease_onlyFullSteps_Success()
{
  uint16_t usSetpointInmA = 150;
  uint16_t usNumberOfSteps = 1;
  eBool_t bIncrease = eFalse;
  uint16_t usCurrentRead = 200;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(150, usCurrentRead);

}

/*----------------------------------------------------------------------------*/

void test_1_8_eShiftCurrentTowardsSetpoint_Decrease_fullAndPartialSteps_Success()
{
  uint16_t usSetpointInmA = 0;
  uint16_t usNumberOfSteps = 5;
  eBool_t bIncrease = eFalse;
  uint16_t usCurrentRead = 201;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(151, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(101, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(51, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(1, usCurrentRead);

  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(0, usCurrentRead);


}

/*----------------------------------------------------------------------------*/

void test_1_9_eShiftCurrentTowardsSetpoint_Decrease_onlyPartialSteps_Success()
{
  uint16_t usSetpointInmA = 0;
  uint16_t usNumberOfSteps = 1;
  eBool_t bIncrease = eFalse;
  uint16_t usCurrentRead = 25;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(0, usCurrentRead);

}

/*----------------------------------------------------------------------------*/

void test_1_10_eShiftCurrentTowardsSetpoint_Increase_onlyPartialSteps_Success()
{
  uint16_t usSetpointInmA = 25;
  uint16_t usNumberOfSteps = 1;
  eBool_t bIncrease = eTrue;
  uint16_t usCurrentRead = 4;


  eMpbError = eShiftCurrentTowardsSetpoint( usSetpointInmA,  &usNumberOfSteps,  bIncrease, &usCurrentRead);
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_UINT16(25, usCurrentRead);

}

/*----------------------------------------------------------------------------*/