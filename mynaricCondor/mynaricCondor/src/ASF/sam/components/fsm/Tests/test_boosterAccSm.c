/**
  * @file			test_boosterAccSm.c
  * @brief    test file for boosterAccSm.c
  * @author		Isabelle Champion
  * @date			Created on 07/22/24
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
#include "boosterAccSm.h"
#include "mock_accControl.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
eMpbError_t eMpbError;
AccDataSm1_t pAccDataSm1;
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
/*                              eBoosterAccSmRun                              */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void test_1_1_eBoosterAccSmRun_InvalidParam_Fail()
{

	eMpbError = eBoosterAccSmRun(NULL);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}

/*----------------------------------------------------------------------------*/

void test_1_2_eBoosterAccSmRun_usStepsNumberHpa1_GreaterThanZero_IncreasingCurrent_test1_Success()
{
	pAccDataSm1.usStepsNumberHpa1 = 2;
	pAccDataSm1.bIncreaseHpa1 = eTrue;
	pAccDataSm1.usSetpointInmAHpa1 = CURRENT_INCREASE_BY_STEP_IN_MA_HPA1;

	pAccDataSm1.usCurrentRead = 13;

	vAccControlLaserUpdateHpaSm1_Expect(pAccDataSm1.usSetpointInmAHpa1); 

	eBoosterAccSmRun(&pAccDataSm1);
	TEST_ASSERT_EQUAL_UINT16(pAccDataSm1.usSetpointInmAHpa1, pAccDataSm1.usCurrentRead);
}

/*----------------------------------------------------------------------------*/

void test_1_3_eBoosterAccSmRun_usStepsNumberHpa1_GreaterThanZero_IncreasingCurrent_test2_Success()
{
  pAccDataSm1.usStepsNumberHpa1 = 2;
  pAccDataSm1.bIncreaseHpa1 = eTrue;
  pAccDataSm1.usSetpointInmAHpa1 = 113;
  pAccDataSm1.usCurrentRead = 13;

  vAccControlLaserUpdateHpaSm1_Expect(13 + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1); 

  eBoosterAccSmRun(&pAccDataSm1);
  TEST_ASSERT_EQUAL_UINT16(13 + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1, pAccDataSm1.usCurrentRead);
}
/*----------------------------------------------------------------------------*/

void test_1_4_eBoosterAccSmRun_usStepsNumberHpa1_GreaterThanZero_DecreasingCurrent_test1_Success()
{
  pAccDataSm1.usStepsNumberHpa1 = 2;
  pAccDataSm1.bIncreaseHpa1 = eFalse;
  pAccDataSm1.usSetpointInmAHpa1 = 10;
  pAccDataSm1.usCurrentRead = 13;

  vAccControlLaserUpdateHpaSm1_Expect(pAccDataSm1.usSetpointInmAHpa1); 

  eBoosterAccSmRun(&pAccDataSm1);
  TEST_ASSERT_EQUAL_UINT16(pAccDataSm1.usSetpointInmAHpa1, pAccDataSm1.usCurrentRead);
}
/*----------------------------------------------------------------------------*/

void test_1_5_eBoosterAccSmRun_usStepsNumberHpa1_GreaterThanZero_DecreasingCurrent_test2_Success()
{
  pAccDataSm1.usStepsNumberHpa1 = 2;
  pAccDataSm1.bIncreaseHpa1 = eFalse;
  pAccDataSm1.usSetpointInmAHpa1 = 10;
  pAccDataSm1.usCurrentRead = 130;

  vAccControlLaserUpdateHpaSm1_Expect(130 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1); 

  eBoosterAccSmRun(&pAccDataSm1);
  TEST_ASSERT_EQUAL_UINT16(130 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1, pAccDataSm1.usCurrentRead);
}
/*----------------------------------------------------------------------------*/

void test_1_6_eBoosterAccSmRun_OneStepLeft_Success()
{
  pAccDataSm1.usStepsNumberHpa1 = 1;
  pAccDataSm1.bIncreaseHpa1 = eFalse;
  pAccDataSm1.usSetpointInmAHpa1 = 10;
  pAccDataSm1.usCurrentRead = 130;

  vAccControlLaserUpdateHpaSm1_Expect(pAccDataSm1.usSetpointInmAHpa1); 

  eBoosterAccSmRun(&pAccDataSm1);
  TEST_ASSERT_EQUAL_UINT16(pAccDataSm1.usSetpointInmAHpa1, pAccDataSm1.usCurrentRead);
}
/*----------------------------------------------------------------------------*/

void test_1_7_eBoosterAccSmRun_ZeroSteps_Success()
{
  pAccDataSm1.usStepsNumberHpa1 = 0;
  pAccDataSm1.bIncreaseHpa1 = eFalse;
  pAccDataSm1.usSetpointInmAHpa1 = 10;
  pAccDataSm1.usCurrentRead = 130;


  eBoosterAccSmRun(&pAccDataSm1);
  TEST_ASSERT_EQUAL_UINT16(130, pAccDataSm1.usCurrentRead);
}
/*----------------------------------------------------------------------------*/