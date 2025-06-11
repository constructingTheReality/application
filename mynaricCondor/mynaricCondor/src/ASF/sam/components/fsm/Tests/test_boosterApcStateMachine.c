/**
  * @file           test_boosterApcStateMachine.c
  * @brief          Unit Tests for boosterApcStateMachine
  * @author         Isabelle Champion
  * @date           Created on 08/07/2024
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2024 NEP, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB.</center>
  *
  **/
/* Includes ------------------------------------------------------------------*/
#include "unity.h"
#include "boosterApcStateMachine.h"
#include "mpblibs.h"
#include "mock_boosterApcStateMachineGetData.h"
#include "mock_controlLaserPID.h"
#include "mock_accControl.h"
#include "mock_dictionaryUtils.h"

/* Private define ------------------------------------------------------------*/
extern eHpaApcState_t   eBoosterApcState;
extern eBool_t          bLastEnableSmHpa1;
extern eBool_t          bLastEnableHpa1;
extern eBool_t          bLastEnableHpa2;
//extern eBool_t          bControlM1M2IsRising;
extern float            fLastSetPointInDbm;

extern float            fCurrentHpaMm1;
extern float            fCurrentHpaMm2;
extern float            fCurrentHpaMm1Mm2;
extern eBool_t          bControlM1M2IsRising;

/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

eMpbError_t eMpbError;

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void setUp(void)
{
  
}


void shutDown(void)
{

}


/******************************************************************************/
/*                           vHpaApcStateMachineInit                          */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_4_1_vHpaApcStateMachineInit_Success()
{
  vHpaApcStateMachineInit();
  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
}

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                         vHpaApcStateMachineUpdate                          */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_5_1_vHpaApcStateMachineUpdate_SM_enable_NotEqualTo_prev_SM_enable_Success()
{
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eFalse;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 0;
  
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0,0,100,eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_FLOAT(0.0f, fLastSetPointInDbm);

                  /// TEST 2 ///

  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eFalse;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0,0,100,eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_FLOAT(0.0f, fLastSetPointInDbm);

 
}

/*----------------------------------------------------------------------------*/

void test_5_2_vHpaApcStateMachineUpdate_MM1_enable_NotEqualTo_prev_MM1_enable_Success()
{

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableHpa1 = eFalse;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 0;
  
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0,0,100,eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_FLOAT(0.0f, fLastSetPointInDbm);

}

/*----------------------------------------------------------------------------*/

void test_5_3_vHpaApcStateMachineUpdate_MM2_enable_NotEqualTo_prev_MM2_enable_Success()
{
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableHpa2 = eFalse;
  bLastEnableSmHpa1 = eFalse;
  bLastEnableHpa1 = eFalse;

  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 0;
  
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0,0,100,eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_FLOAT(0.0f, fLastSetPointInDbm);

                /// TEST 2 ///

  bLastEnableHpa2 = eFalse;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;

  xBoosterPowers.fSetPointInDbm = 0;
  
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0,0,100,eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);

}
/*----------------------------------------------------------------------------*/

void test_5_4_vHpaApcStateMachineUpdate_MM1_MM2_and_SM_enable_NotEqualTo_prev_enable_Success()
{
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eFalse;
  bLastEnableHpa2 = eFalse;
  bLastEnableHpa1 = eFalse;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 0;
  
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0,0,100,eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_FLOAT(0.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/

void test_5_5_vHpaApcStateMachineUpdate_lastSetpoint_notEqualTo_newSetpoint_Success()
{
  eBoosterApcState = eHpaApcInit;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eTrue;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eTrue;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 10.0f;

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(0.0f,10.0f,100,eFalse);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID ); // Changed to MM1
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  mpb_float1_minor_than_float2_ExpectAndReturn(0.0f, 10.0f, 100, eTrue);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
 
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);


}
/*----------------------------------------------------------------------------*/

void test_5_6_vHpaApcStateMachineUpdate_isRising_setToFalse()
{
  eBoosterApcState = eHpaApcInit;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eTrue;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eTrue;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 9.0f;

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(10.0f,9.0f,100,eFalse);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID ); // Changed to MM1
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  mpb_float1_minor_than_float2_ExpectAndReturn(10.0f, 9.0f, 100, eFalse);

  // within eHpaApcStateInitFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );


  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
 
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);


}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                         eHpaApcStateInitFunction                           */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_6_1_eHpaApcStateInitFunction_setPointTooLow_HPA1_Enabled_Success()
{
  xBoosterPowers_t xBoosterPowers;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;
  xBoosterPowers.fSetPointInDbm = 0.0f;


  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eHpaApcStateInitFunction();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);

}

/*----------------------------------------------------------------------------*/

void test_6_2_eHpaApcStateInitFunction_setPointTooLow_HPA1_notEnabled_Success()
{
  xBoosterPowers_t xBoosterPowers;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eFalse;
  xBoosterPowers.fSetPointInDbm = 0.0f;


  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eHpaApcStateInitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);

}

/*----------------------------------------------------------------------------*/

void test_6_3_eHpaApcStateInitFunction_setPointAboveThreshold_HPA1_notEnabled_Success()
{
  xBoosterPowers_t xBoosterPowers;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eFalse;
  xBoosterPowers.fSetPointInDbm = 20.0f;


  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eHpaApcStateInitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);

}

/*----------------------------------------------------------------------------*/

void test_6_4_eHpaApcStateInitFunction_setPointAboveThreshold_HPA1_Enabled_Success()
{
  xBoosterPowers_t xBoosterPowers;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;
  xBoosterPowers.fSetPointInDbm = 20.0f;


  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );
  vAccControlLaserUpdateHpaSm1_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eHpaApcStateInitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcSm, eBoosterApcState);

}

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                           eHpaApcStateSmFunction                           */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_7_1_eHpaApcStateSmFunction_SM1_Disabled_currentNotLowEnoughToShutdownDiode_Success()
{
  eBoosterApcState = eHpaApcSm;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eFalse;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eTrue;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eFalse;
  cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent = CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE + 1;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 20.0f;

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  mpb_float1_equal_to_float2_ExpectAndReturn(9.0f,20.0f,100,eFalse);

  vControlLaserPIDReset_Expect( eHpaLaserMultiMode1PowerLoopPID ); // Changed to MM1
  vControlLaserPIDReset_Expect( eHpaLaserMultiMode2PowerLoopPID );
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  mpb_float1_minor_than_float2_ExpectAndReturn(9.0f, 20.0f, 100, eTrue);

  TEST_ASSERT_EQUAL(eBoosterApcState, eHpaApcSm);

  // within eHpaApcStateSmFunction

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  uint16_t  usMaxHpaCurrentSM_mA        = 0;
  uint16_t  usNominalCurrentPourcentage_sM    = 0;

  eBoosterApcStateGetDataHpaSmParameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusMaxHpaCurrentSM_mA();
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusNominalCurrentPourcentage_sM();
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusMaxHpaCurrentSM_mA(&usMaxHpaCurrentSM_mA);
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusNominalCurrentPourcentage_sM(&usNominalCurrentPourcentage_sM);

  mpb_float1_minor_than_float2_ExpectAndReturn(CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE+ 1, CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE, 100, eFalse);
  vAccControlLaserUpdateHpaSm1_Expect(CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE  - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC + 1);
  
  // xBoosterPowers.fSetPointInDbm < MIN

  vHpaApcStateMachineUpdate();

  TEST_ASSERT_EQUAL(eHpaApcSm, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);
  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
 
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);

}

/*----------------------------------------------------------------------------*/

void test_7_2_eHpaApcStateSmFunction_SM1_Disabled_currentLowEnoughToShutdownDiode_Success()
{
  eBoosterApcState = eHpaApcSm;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eFalse;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eTrue;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eFalse;
  cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent = CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE -1;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 20.0f;

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  uint16_t  usMaxHpaCurrentSM_mA        = 0;
  uint16_t  usNominalCurrentPourcentage_sM    = 0;

  eBoosterApcStateGetDataHpaSmParameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusMaxHpaCurrentSM_mA();
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusNominalCurrentPourcentage_sM();
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusMaxHpaCurrentSM_mA(&usMaxHpaCurrentSM_mA);
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusNominalCurrentPourcentage_sM(&usNominalCurrentPourcentage_sM);

  mpb_float1_minor_than_float2_ExpectAndReturn(199,200,100,eTrue);
  vAccControlLaserUpdateHpaSm1_Expect(0);

  eHpaApcStateSmFunction();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);

  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/

void test_7_3_eHpaApcStateSmFunction_SM1_Enabled_newCurrentUnderNominalValue_Success()
{
  eBoosterApcState = eHpaApcSm;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eTrue;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eTrue;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;
  cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent = 100.0f;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 20.0f;

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  uint16_t  usMaxHpaCurrentSM_mA        = 1500;
  uint16_t  usNominalCurrentPourcentage_sM    = 100;

  eBoosterApcStateGetDataHpaSmParameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusMaxHpaCurrentSM_mA();
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusNominalCurrentPourcentage_sM();
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusMaxHpaCurrentSM_mA(&usMaxHpaCurrentSM_mA);
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusNominalCurrentPourcentage_sM(&usNominalCurrentPourcentage_sM);

  mpb_float1_minor_than_float2_ExpectAndReturn((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100 , cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC,100, eFalse);

  vAccControlLaserUpdateHpaSm1_Expect(cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateSmFunction();

  TEST_ASSERT_EQUAL(eHpaApcSm, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);

  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/

void test_7_4_eHpaApcStateSmFunction_SM1_Enabled_newCurrentOverNominalValue_MM1Enabled_Success()
{
  eBoosterApcState = eHpaApcSm;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eTrue;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eTrue;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eTrue;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;
  cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent = 1500.0f;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 20.0f;

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  uint16_t  usMaxHpaCurrentSM_mA        = 1499;
  uint16_t  usNominalCurrentPourcentage_sM    = 100;

  eBoosterApcStateGetDataHpaSmParameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusMaxHpaCurrentSM_mA();
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusNominalCurrentPourcentage_sM();
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusMaxHpaCurrentSM_mA(&usMaxHpaCurrentSM_mA);
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusNominalCurrentPourcentage_sM(&usNominalCurrentPourcentage_sM);

  mpb_float1_minor_than_float2_ExpectAndReturn((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100 , cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC,100, eTrue);
  vAccControlLaserUpdateHpaSm1_Expect((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100);

  eHpaApcStateSmFunction();

  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);

  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/

void test_7_5_eHpaApcStateSmFunction_SM1_Enabled_newCurrentOverNominalValue_MM1Disabled_MM2Enabled_Success()
{
  eBoosterApcState = eHpaApcSm;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eTrue;
  bLastEnableHpa2 = eTrue;
  bLastEnableHpa1 = eFalse;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eFalse;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eTrue;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;
  cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent = 1501.0f;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 20.0f;

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  uint16_t  usMaxHpaCurrentSM_mA        = 1500;
  uint16_t  usNominalCurrentPourcentage_sM    = 100;

  eBoosterApcStateGetDataHpaSmParameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusMaxHpaCurrentSM_mA();
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusNominalCurrentPourcentage_sM();
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusMaxHpaCurrentSM_mA(&usMaxHpaCurrentSM_mA);
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusNominalCurrentPourcentage_sM(&usNominalCurrentPourcentage_sM);

  mpb_float1_minor_than_float2_ExpectAndReturn((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100 , cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC,100, eTrue);
  vAccControlLaserUpdateHpaSm1_Expect((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100);

  eHpaApcStateSmFunction();

  TEST_ASSERT_EQUAL(eHpaApcMm2_Init, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableHpa2);

  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/

void test_7_6_eHpaApcStateSmFunction_SM1_Enabled_newCurrentOverNominalValue_MM1Disabled_MM2Disabled_Success()
{
  eBoosterApcState = eHpaApcSm;

  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;

  bLastEnableSmHpa1 = eTrue;
  bLastEnableHpa2 = eFalse;
  bLastEnableHpa1 = eFalse;
  //fLastSetPointInDbm = 0.0f;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = eFalse;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = eFalse;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = eTrue;
  cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent = 1501.0f;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 20.0f;

  vAccControlLaserUpdateHpaMm1_Expect( 0 );
  vAccControlLaserUpdateHpaMm2_Expect( 0 );

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  uint16_t  usMaxHpaCurrentSM_mA        = 1500;
  uint16_t  usNominalCurrentPourcentage_sM    = 100;

  eBoosterApcStateGetDataHpaSmParameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusMaxHpaCurrentSM_mA();
  eBoosterApcStateGetDataHpaSmParameters_IgnoreArg_pusNominalCurrentPourcentage_sM();
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusMaxHpaCurrentSM_mA(&usMaxHpaCurrentSM_mA);
  eBoosterApcStateGetDataHpaSmParameters_ReturnThruPtr_pusNominalCurrentPourcentage_sM(&usNominalCurrentPourcentage_sM);

  mpb_float1_minor_than_float2_ExpectAndReturn((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100 , cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC,100, eTrue);
  vAccControlLaserUpdateHpaSm1_Expect((usMaxHpaCurrentSM_mA *usNominalCurrentPourcentage_sM) / 100);

  eHpaApcStateSmFunction();

  TEST_ASSERT_EQUAL(eHpaApcInit, eBoosterApcState);
  TEST_ASSERT_EQUAL_UINT8(eTrue, bLastEnableSmHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa1);
  TEST_ASSERT_EQUAL_UINT8(eFalse, bLastEnableHpa2);

  //TEST_ASSERT_EQUAL_UINT8(eTrue, bControlM1M2IsRising);
  //TEST_ASSERT_EQUAL_FLOAT(10.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                       eHpaApcStateMm1_InitFunction                         */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_8_1_eHpaApcStateMm1_InitFunction_SM1_disabled_shutdownDiode_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;

  xBoosterCurrents_t xBoosterCurrents;
  xBoosterPowers_t xBoosterPowers;

  eBoosterApcState = eHpaApcMm1_Init;

  vAccControlLaserUpdateHpaMm2_Expect(0);

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn( NULL, eSuccess);  
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_IgnoreArg_pxBoosterCurrents();
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ReturnThruPtr_pxBoosterCurrents(&xBoosterCurrents);

  mpb_float1_minor_than_float2_ExpectAndReturn(-100.0f, 200.0f, 100, eTrue);
  
  vAccControlLaserUpdateHpaMm1_Expect(0 );

  eHpaApcStateMm1_InitFunction();

  TEST_ASSERT_EQUAL(eHpaApcSm, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_8_2_eHpaApcStateMm1_InitFunction_MM1_disabled_shutdownDiode_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =1;

  xBoosterCurrents_t xBoosterCurrents;
  xBoosterPowers_t xBoosterPowers;

  eBoosterApcState = eHpaApcMm1_Init;

  vAccControlLaserUpdateHpaMm2_Expect(0);

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn( NULL, eSuccess);  
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_IgnoreArg_pxBoosterCurrents();
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ReturnThruPtr_pxBoosterCurrents(&xBoosterCurrents);

  mpb_float1_minor_than_float2_ExpectAndReturn(-100.0f, 200.0f, 100, eTrue);
  
  vAccControlLaserUpdateHpaMm1_Expect(0 );

  eHpaApcStateMm1_InitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcSm, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_8_3_eHpaApcStateMm1_InitFunction_MM1_and_SM1_disabled_cantShutdownDiodeYet_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;

  xBoosterCurrents_t xBoosterCurrents;
  xBoosterPowers_t xBoosterPowers;

  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Init;

  vAccControlLaserUpdateHpaMm2_Expect(0);

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn( NULL, eSuccess);  
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_IgnoreArg_pxBoosterCurrents();
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ReturnThruPtr_pxBoosterCurrents(&xBoosterCurrents);


  mpb_float1_minor_than_float2_ExpectAndReturn(200.0f, 200.0f, 100, eFalse);

  vAccControlLaserUpdateHpaMm1_Expect(300.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC );

  eHpaApcStateMm1_InitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_8_4_eHpaApcStateMm1_InitFunction_MM1_and_SM1_enabled_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =1;

  xBoosterCurrents_t xBoosterCurrents;
  xBoosterPowers_t xBoosterPowers;

  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Init;

  vAccControlLaserUpdateHpaMm2_Expect(0);

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn( NULL, eSuccess);  
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_IgnoreArg_pxBoosterCurrents();
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ReturnThruPtr_pxBoosterCurrents(&xBoosterCurrents);


  vControlLaserPIDReset_Expect(eHpaLaserMultiMode1PowerLoopPID);

  eHpaApcStateMm1_InitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcMm1_Control, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_8_5_eHpaApcStateMm1_InitFunction_MM1_and_MM2_disabled_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  xBoosterCurrents_t xBoosterCurrents;
  xBoosterPowers_t xBoosterPowers;

  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Init;

  vAccControlLaserUpdateHpaMm2_Expect(0);

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn( NULL, eSuccess);  
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_IgnoreArg_pxBoosterCurrents();
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ReturnThruPtr_pxBoosterCurrents(&xBoosterCurrents);

  mpb_float1_minor_than_float2_ExpectAndReturn(200.0f, 200.0f, 100, eFalse);
  vAccControlLaserUpdateHpaMm1_Expect(200.0f);

  eHpaApcStateMm1_InitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

  fCurrentHpaMm1 = 200.0f;
  vAccControlLaserUpdateHpaMm2_Expect(0);

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn( NULL, eSuccess);  
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_IgnoreArg_pxBoosterCurrents();
  eBoosterApcStateGetDataGetHpaActualConditionsOnPumps_ReturnThruPtr_pxBoosterCurrents(&xBoosterCurrents);

  mpb_float1_minor_than_float2_ExpectAndReturn(100.0f, 200.0f, 100, eTrue);
  vAccControlLaserUpdateHpaMm1_Expect(0.0f);

  eHpaApcStateMm1_InitFunction();
  
  TEST_ASSERT_EQUAL(eHpaApcSm, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                     eHpaApcStateMm1_ControlFunction                        */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_9_1_eHpaApcStateMm1_ControlFunction_moveToMM1Init_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  xBoosterPowers_t xBoosterPowers;

  uint16_t usMaxHpaCurrentStageMM1_mA;
  uint16_t usMaxHpaCurrentMM1_mA;

  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Control;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init,eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init,eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init,eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 =0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init,eBoosterApcState);


}

/*----------------------------------------------------------------------------*/

void test_9_2_eHpaApcStateMm1_ControlFunction_moveToMM2Init_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  xBoosterPowers_t xBoosterPowers;

  uint16_t usMaxHpaCurrentStageMM1_mA = 299.0f;
  uint16_t usMaxHpaCurrentMM1_mA;

  bControlM1M2IsRising = eTrue;
  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Control;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(299.0f, 300.0f, 100, eTrue);
  vAccControlLaserUpdateHpaMm1_Expect(299.0f);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);
}

/*----------------------------------------------------------------------------*/

void test_9_3_eHpaApcStateMm1_ControlFunction_remainInMM1Control_test1_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  xBoosterPowers_t xBoosterPowers;
  float fCurrentControlHpaMm1 = 0.0f;

  uint16_t usMaxHpaCurrentStageMM1_mA = 299.0f;
  uint16_t usMaxHpaCurrentMM1_mA;

  bControlM1M2IsRising = eTrue;
  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Control;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataUpdateControlMm1_ExpectAndReturn(xBoosterPowers, NULL, eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1_IgnoreArg_pfCurrentControlHpaMm1();
  eBoosterApcStateGetDataUpdateControlMm1_ReturnThruPtr_pfCurrentControlHpaMm1(&fCurrentControlHpaMm1);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Control,eBoosterApcState);
}

/*----------------------------------------------------------------------------*/


void test_9_4_eHpaApcStateMm1_ControlFunction_remainInMM1Control_test2_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  xBoosterPowers_t xBoosterPowers;
  float fCurrentControlHpaMm1 = 0.0f;

  uint16_t usMaxHpaCurrentStageMM1_mA = 299.0f;
  uint16_t usMaxHpaCurrentMM1_mA;

  bControlM1M2IsRising = eFalse;
  fCurrentHpaMm1 = 300.0f;
  eBoosterApcState = eHpaApcMm1_Control;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);



  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataUpdateControlMm1_ExpectAndReturn(xBoosterPowers, NULL, eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1_IgnoreArg_pfCurrentControlHpaMm1();
  eBoosterApcStateGetDataUpdateControlMm1_ReturnThruPtr_pfCurrentControlHpaMm1(&fCurrentControlHpaMm1);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Control,eBoosterApcState);
}

/*----------------------------------------------------------------------------*/

void test_9_5_eHpaApcStateMm1_ControlFunction_remainInMM1Control_test3_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  xBoosterPowers_t xBoosterPowers;
  float fCurrentControlHpaMm1 = 0.0f;

  uint16_t usMaxHpaCurrentStageMM1_mA = 299.0f;
  uint16_t usMaxHpaCurrentMM1_mA;

  bControlM1M2IsRising = eTrue;
  fCurrentHpaMm1 = 100.0f;
  eBoosterApcState = eHpaApcMm1_Control;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm1Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentStageMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_IgnoreArg_pusMaxHpaCurrentMM1_mA();
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM1_mA(&usMaxHpaCurrentStageMM1_mA);
  eBoosterApcStateGetDataHpaMm1Parameters_ReturnThruPtr_pusMaxHpaCurrentMM1_mA(&usMaxHpaCurrentMM1_mA);


  mpb_float1_minor_than_float2_ExpectAndReturn(299.0f, 100.0f, 100, eFalse);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataUpdateControlMm1_ExpectAndReturn(xBoosterPowers, NULL, eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1_IgnoreArg_pfCurrentControlHpaMm1();
  eBoosterApcStateGetDataUpdateControlMm1_ReturnThruPtr_pfCurrentControlHpaMm1(&fCurrentControlHpaMm1);

  eHpaApcStateMm1_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Control,eBoosterApcState);
}

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*                       eHpaApcStateMm2_InitFunction                         */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_10_1_eHpaApcStateMm2_InitFunction_MoveToMM2Control_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1_Control;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vControlLaserPIDReset_Expect(eHpaLaserMultiMode2PowerLoopPID);

  eHpaApcStateMm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Control,eBoosterApcState);

}

/*----------------------------------------------------------------------------*/

void test_10_2_eHpaApcStateMm2_InitFunction_RemainInMM2Init_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vAccControlLaserUpdateHpaMm2_Expect(fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateMm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vAccControlLaserUpdateHpaMm2_Expect(fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateMm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vAccControlLaserUpdateHpaMm2_Expect(fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateMm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);

}

/*----------------------------------------------------------------------------*/

void test_10_3_eHpaApcStateMm2_InitFunction_moveToSmApc_Success()
{
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm2_Init;
  fCurrentHpaMm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  vAccControlLaserUpdateHpaMm2_Expect(0.0f);

  eHpaApcStateMm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Control,eBoosterApcState);
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                     eHpaApcStateMm2_ControlFunction                        */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_11_1_eHpaApcStateMm2_ControlFunction_SM1_AndOr_MM2_disabled_Success()
{
    uint16_t usMaxHpaCurrentStageMM2_mA = 200.0f;
    uint16_t usMaxHpaCurrentMM2_mA;
    float fCurrentControlHpaMm2 = 0.0f;
    xBoosterPowers_t xBoosterPowers;
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm2, 100, eFalse);
  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);
  

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm2, 100, eFalse);

  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  //mpb_float1_minor_than_float2_ExpectAndReturn(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm2, 100, eFalse);

  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Init,eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_11_2_eHpaApcStateMm2_ControlFunction_currentDecreasing_notReadyForMM1_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 200.0f;
  uint16_t usMaxHpaCurrentMM2_mA;
  float fCurrentControlHpaMm2 = 0.0f;
  xBoosterPowers_t xBoosterPowers;
  bControlM1M2IsRising = eFalse;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(fCurrentHpaMm2, 100, 100, eFalse);
  
  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataUpdateControlMm2_ExpectAndReturn(xBoosterPowers, NULL, eSuccess);
  eBoosterApcStateGetDataUpdateControlMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);
 
  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Control,eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_11_3_eHpaApcStateMm2_ControlFunction_currentDecreasing_ReadyForMM1_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 200.0f;
  uint16_t usMaxHpaCurrentMM2_mA;
  float fCurrentControlHpaMm2 = 0.0f;
  xBoosterPowers_t xBoosterPowers;
  bControlM1M2IsRising = eFalse;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 10.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(fCurrentHpaMm2, 100, 100, eTrue);
  
  vAccControlLaserUpdateHpaMm2_Expect(0);
  vControlLaserPIDReset_Expect(eHpaLaserMultiMode1PowerLoopPID);
  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Control,eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_11_4_eHpaApcStateMm2_ControlFunction_currentIncreasing_readyForMM1MM2_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 200.0f;
  uint16_t usMaxHpaCurrentMM2_mA;
  float fCurrentControlHpaMm2 = 0.0f;
  xBoosterPowers_t xBoosterPowers;
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 300.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm2, 100, eTrue);
  
  vAccControlLaserUpdateHpaMm2_Expect(usMaxHpaCurrentStageMM2_mA);
  vControlLaserPIDReset_Expect(eHpaLaserMultM1and2PowerLoopPID);
  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Init,eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_11_5_eHpaApcStateMm2_ControlFunction_currentIncreasing_notReadyForMM1MM2_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 200.0f;
  uint16_t usMaxHpaCurrentMM2_mA;
  float fCurrentControlHpaMm2 = 0.0f;
  xBoosterPowers_t xBoosterPowers;
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm2_Control;
  fCurrentHpaMm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm2, 100, eFalse);
  
  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);

  eBoosterApcStateGetDataUpdateControlMm2_ExpectAndReturn(xBoosterPowers, NULL, eSuccess);
  eBoosterApcStateGetDataUpdateControlMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);
 
  eHpaApcStateMm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Control, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                     eHpaApcStateMm1Mm2_InitFunction                        */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void test_12_1_eHpaApcStateMm1Mm2_InitFunction_SM1_PumpDisabled_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(400.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC, usMaxHpaCurrentStageMM2_mA, 100, eFalse);

  vAccControlLaserUpdateHpaMm1_Expect( 400.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);
  vAccControlLaserUpdateHpaMm2_Expect( 400.0f  - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm1Mm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC, usMaxHpaCurrentStageMM2_mA, 100, eTrue);

  vAccControlLaserUpdateHpaMm1_Expect( 10.0f);
  vAccControlLaserUpdateHpaMm2_Expect( 10.0f);

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm1Mm2);

  TEST_ASSERT_EQUAL(eHpaApcMm2_Control, eBoosterApcState);
  
}

/*----------------------------------------------------------------------------*/
void test_12_2_eHpaApcStateMm1Mm2_InitFunction_MM1_PumpDisabled_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(400.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC, usMaxHpaCurrentStageMM2_mA, 100, eFalse);

  vAccControlLaserUpdateHpaMm1_Expect( 400.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);
  vAccControlLaserUpdateHpaMm2_Expect( 400.0f  - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm1Mm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC, usMaxHpaCurrentStageMM2_mA, 100, eTrue);

  vAccControlLaserUpdateHpaMm1_Expect( 10.0f);
  vAccControlLaserUpdateHpaMm2_Expect( 10.0f);

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm1Mm2);

  TEST_ASSERT_EQUAL(eHpaApcMm1_Control, eBoosterApcState);
  
}

/*----------------------------------------------------------------------------*/
void test_12_3_eHpaApcStateMm1Mm2_InitFunction_MM2_PumpDisabled_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(400.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC, usMaxHpaCurrentStageMM2_mA, 100, eFalse);

  vAccControlLaserUpdateHpaMm1_Expect( 400.0f - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);
  vAccControlLaserUpdateHpaMm2_Expect( 400.0f  - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC);

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm1Mm2 = 100.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  mpb_float1_minor_than_float2_ExpectAndReturn(fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC, usMaxHpaCurrentStageMM2_mA, 100, eTrue);

  vAccControlLaserUpdateHpaMm1_Expect( 10.0f);
  vAccControlLaserUpdateHpaMm2_Expect( 10.0f);

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(usMaxHpaCurrentStageMM2_mA, fCurrentHpaMm1Mm2);

  TEST_ASSERT_EQUAL(eHpaApcMm2_Control, eBoosterApcState);
  
}


/*----------------------------------------------------------------------------*/

void test_12_4_eHpaApcStateMm1Mm2_InitFunction_pumpsAllEnabled_Success()
{
  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Init;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);

  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );

  eHpaApcStateMm1Mm2_InitFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Control, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                    eHpaApcStateMm1Mm2_ControlFunction                      */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_13_1_eHpaApcStateMm1Mm2_ControlFunction_variousPumpsDisabled_Success()
{
  xBoosterPowers_t xBoosterPowers;
  float fCurrentControlHpaMm2;

  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 0;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 0;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 0;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1_Init, eBoosterApcState);


}

/*----------------------------------------------------------------------------*/

void test_13_2_eHpaApcStateMm1Mm2_ControlFunction_currentIsRising_Success()
{
  xBoosterPowers_t xBoosterPowers;
  float fCurrentControlHpaMm2;

  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eTrue;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
           
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Control, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_13_3_eHpaApcStateMm1Mm2_ControlFunction_currentIsNotRising_Success()
{
  xBoosterPowers_t xBoosterPowers;
  float fCurrentControlHpaMm2;

  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eFalse;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 400.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);


  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  
  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
 
  mpb_float1_minor_than_float2_ExpectAndReturn(400.0f, 10.0f, 100, eFalse);

  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
  
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ExpectAndReturn( xBoosterPowers, NULL , eSuccess);
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_IgnoreArg_pfCurrentControlHpaMm2();
  eBoosterApcStateGetDataUpdateControlMm1AndMm2_ReturnThruPtr_pfCurrentControlHpaMm2(&fCurrentControlHpaMm2);
  

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm1Mm2_Control, eBoosterApcState);

}
/*----------------------------------------------------------------------------*/

void test_13_4_eHpaApcStateMm1Mm2_ControlFunction_currentIsNotRising_currentLessthanMaxMM2Current_Success()
{

  fLastSetPointInDbm = 90.0f;

  xBoosterPowers_t xBoosterPowers;
  xBoosterPowers.fSetPointInDbm = 9.0f;
  float fCurrentControlHpaMm2;

  uint16_t usMaxHpaCurrentStageMM2_mA = 10.0f;
  uint16_t usMaxHpaCurrentMM2_mA;

 
  bControlM1M2IsRising = eFalse;
  cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
  cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
  cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;

  cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 = 1;
  cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 = 1;
  cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 = 1;

  eBoosterApcState = eHpaApcMm1Mm2_Control;
  fCurrentHpaMm2 = 5.0f;

  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ExpectAndReturn( NULL, eSuccess) ;
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_IgnoreArg_pcPumpSm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpSm1_ReturnThruPtr_pcPumpSm1StatusDefinition(&cPumpSm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ExpectAndReturn( NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_IgnoreArg_pcPumpMm1StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm1_ReturnThruPtr_pcPumpMm1StatusDefinition(&cPumpMm1StatusDefinition);

  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ExpectAndReturn(  NULL, eSuccess);
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_IgnoreArg_pcPumpMm2StatusDefinition();
  eBoosterApcStateGetDataGetConditionsOnPumpMm2_ReturnThruPtr_pcPumpMm2StatusDefinition(&cPumpMm2StatusDefinition);


  eBoosterApcStateGetDataHpaMm2Parameters_ExpectAndReturn(NULL, NULL, eSuccess);
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_IgnoreArg_pusMaxHpaCurrentStageMM2_mA();
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentMM2_mA(&usMaxHpaCurrentMM2_mA);
  eBoosterApcStateGetDataHpaMm2Parameters_ReturnThruPtr_pusMaxHpaCurrentStageMM2_mA(&usMaxHpaCurrentStageMM2_mA);
  
  eBoosterApcStateGetDataPowersAndOperationMode_ExpectAndReturn(NULL, eSuccess);
  eBoosterApcStateGetDataPowersAndOperationMode_IgnoreArg_pxBoosterPowers();
  eBoosterApcStateGetDataPowersAndOperationMode_ReturnThruPtr_pxBoosterPowers(&xBoosterPowers);
 
  mpb_float1_minor_than_float2_ExpectAndReturn(5.0f, 10.0f, 100, eTrue);
  vControlLaserPIDReset_Expect( eHpaLaserMultM1and2PowerLoopPID );
  vAccControlLaserUpdateHpaMm1_Expect( usMaxHpaCurrentStageMM2_mA );
  vAccControlLaserUpdateHpaMm2_Expect( usMaxHpaCurrentStageMM2_mA );
  
 

  eHpaApcStateMm1Mm2_ControlFunction();
  TEST_ASSERT_EQUAL(eHpaApcMm2_Control, eBoosterApcState);
  TEST_ASSERT_EQUAL_FLOAT(9.0f, fLastSetPointInDbm);

}
/*----------------------------------------------------------------------------*/