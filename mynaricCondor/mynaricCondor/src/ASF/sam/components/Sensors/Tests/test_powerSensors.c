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
#include "powerSensors.h"
#include "dictionaryUtils.h"
#include "mock_powerSensorsUpdateDatabase.h"
#include "mpbPowerIn2Channels.h"
#include "mpbLosDetector.h"
#include "mock_powerSensorsConfigUpdate.h"
#include "mock_laserData.h"
#include "mpbLibs.h"
#include "powerSensorsBoosterAlarm.h"
#include "powerSensorsLnaAlarm.h"
#include "mock_powerReadChannel.h"
//#include "mpbPowerIn2Channels.h"
#include "math.h"
#include "mock_boosterStateMachine.h"
#include "mock_lnaStateMachine.h" 
#include "powerSensorsAlarmValidateLimits.h"

/* Private define ------------------------------------------------------------*/
#define POWER_CONFIG_NUMBER_OF_CHANNELS ( eNumberOfPowerChannelConfigurations )
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
eMpbError_t eMpbError;
float fMockPowerReaded[POWER_CONFIG_NUMBER_OF_CHANNELS]; 
uint16_t usMockPowerRaw[POWER_CONFIG_NUMBER_OF_CHANNELS]; 
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
 
void setUp()
{
  for( int i = 0; i < POWER_CONFIG_NUMBER_OF_CHANNELS;  i ++ )
  {
    fMockPowerReaded[i] = 0.5f* i + 0.3f;
    usMockPowerRaw[i] = 5*i - 2;
  }
  
}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{
  
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                            ePowerSensorUpdate                              */
/******************************************************************************/

/*----------------------------------------------------------------------------*/

void test_3_1_ePowerSensorUpdate_eMpbPowerIn2ChannelsRunFailure_Fail()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 0;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
 
  // No Set Up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  
}

/*----------------------------------------------------------------------------*/

void test_3_2_ePowerSensorUpdate_ePowerReadOffsetChannelRunFailure_Fail()
{
  
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eInvalidParameter);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();

  eMpbError = ePowerSensorUpdate();
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_3_3_ePowerSensorUpdate_ePowerReadChannelRunFailure_test1_Fail()
{

  uint16_t usMockExternalOffset = 0;

  xAmplifierDescriptor_t pxAmplifierDescriptor;

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(0,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();

  // 2
  ePowerReadChannelRun_ExpectAndReturn(1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();

  // 3
  ePowerReadChannelRun_ExpectAndReturn(2,usMockExternalOffset, NULL, NULL, NULL, eUnknownError);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();


  eMpbError = ePowerSensorUpdate();
  TEST_ASSERT_EQUAL(eUnknownError, eMpbError);

}

/*----------------------------------------------------------------------------*/


void test_3_4_ePowerSensorUpdate_ePowerReadChannelRunFailure_test2_Fail()
{
 
  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  xAmplifierDescriptor_t pxAmplifierDescriptor;

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+2]);

  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eInvalidParameter);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);


  eMpbError = ePowerSensorUpdate();
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_3_5_ePowerSensorUpdate_boostChannel0_LnaChannel1_noAlarms_Success()
{
  
  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 0;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
 
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1553]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1553]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower2_1553] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));


}
/*----------------------------------------------------------------------------*/

void test_3_6_ePowerSensorUpdate_boostChannel0_LnaChannel0_noAlarms_Success()
{
  
  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 0;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 0;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
 
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1553]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1553]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower2_1553] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1553]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1553]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1553_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1553_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1553_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1553_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));


}

/*----------------------------------------------------------------------------*/

void test_3_7_ePowerSensorUpdate_boostChannel1_LnaChannel0_noAlarms_Success()
{
  

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 0;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
 
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1553]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1553]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1553_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1553_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1553_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1553_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

}
/*----------------------------------------------------------------------------*/

void test_3_8_ePowerSensorUpdate_boostChannel1_LnaChannel1_noAlarms_Success()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
 
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

}

/*----------------------------------------------------------------------------*/

void test_3_9_ePowerSensorUpdate_boostChannel1_LnaChannel1_BoosterAlarm_DueToLos_Success()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eFallingAndSet;
 
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);


  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);

  vHpaCriticalErrorDetected_Expect();


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

}

/*----------------------------------------------------------------------------*/

void test_3_10_ePowerSensorUpdate_boostChannel1_LnaChannel1_BoosterAlarm_And_LnaAlarm_DueToPower_Success()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
  
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  float fTempValue = 500.0f;
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  //ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fTempValue);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);

  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);

  vHpaCriticalErrorDetected_Expect();
  vLnaCriticalErrorDetected_Expect();


  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

  TEST_ASSERT_EQUAL(eFalse, pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}

/*----------------------------------------------------------------------------*/


void test_3_11_ePowerSensorUpdate_boostChannel1_LnaChannel1_ePowerSensorBoosterAlarmRunFailure_Fail()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  uint16_t temp = 7;
  float temp1 = 6;
  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
  
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up
  xLosValues_t pxMockLosValues;
  pxMockLosValues.fLosClear = 0.5;
  pxMockLosValues.fLosSet = 0.5;
  ePowerSensorsConfigUpdateBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsConfigUpdateBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsConfigUpdateBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsConfigUpdateBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsConfigUpdateBooster_IgnoreArg_pxLosValues();
  ePowerSensorsConfigUpdateBooster_ReturnThruPtr_pxLosValues(&pxMockLosValues);
  eMpbError = ePowerSensorsBoosterConfigUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  float fTempValue = 500.0f;
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  //ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fTempValue);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);

  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);

  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

  TEST_ASSERT_EQUAL(eFalse, pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}

/*----------------------------------------------------------------------------*/

void test_3_12_ePowerSensorUpdate_boostChannel1_LnaChannel1_LnaAlarm_dueToPower_Success()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
  
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;

  for( int i = 0; i < POWER_CONFIG_NUMBER_OF_CHANNELS;  i ++ )
  {
    fMockPowerReaded[i] = 0;
    usMockPowerRaw[i] = 0;
  }
  fMockPowerReaded[eExternalLnaInputPower_1536] = 2000;
  usMockPowerRaw[eExternalLnaInputPower_1536] = 2000;
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up
  

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  float fTempValue = 500.0f;
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  //ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fTempValue);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);

  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);

  vLnaCriticalErrorDetected_Expect();

  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

  TEST_ASSERT_EQUAL(eFalse, pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}

/*----------------------------------------------------------------------------*/


void test_3_13_ePowerSensorUpdate_boostChannel1_LnaChannel1_BoosterAlarm_dueToPower_Success()
{

  uint16_t usMockInternalOffset = 3;
  uint16_t usMockExternalOffset = 4;
  uint16_t usMockExternalOffset1 = 5;

  xAmplifierDescriptor_t pxAmplifierDescriptor;

  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 1;
  pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = 1;
  pxAmplifierDescriptor.xHpaLosStates = eValidAndClear;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
  pxAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
  
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
  pxAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;

  for( int i = 0; i < POWER_CONFIG_NUMBER_OF_CHANNELS;  i ++ )
  {
    fMockPowerReaded[i] = 0;
    usMockPowerRaw[i] = 0;
  }
  fMockPowerReaded[eExternalHpaInputPower_1536] = 2000;
  usMockPowerRaw[eExternalHpaInputPower_1536] = 2000;
  // Set up 
    
  ePowerSensorsUpdateDatabaseCommon_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseCommon_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitCommonChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseLna_ExpectAndReturn(NULL, eSuccess);
  ePowerSensorsUpdateDatabaseLna_IgnoreArg_pxLocalPowerInputScaling();
  eMpbError = ePowerSensorsFactoryInitLnaChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);

  ePowerSensorsUpdateDatabaseBooster_ExpectAndReturn(NULL, NULL, NULL, NULL, eSuccess);
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLocalPowerInputScaling();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaLimitsConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxHpaPowersConfig();
  ePowerSensorsUpdateDatabaseBooster_IgnoreArg_pxLosValues();
  eMpbError = ePowerSensorsFactoryInitBoosterChannels();
  TEST_ASSERT_EQUAL(eMpbError, eSuccess);
  
  // End of set up
  

  vGetxAmplifierDescriptor_ExpectAndReturn(&pxAmplifierDescriptor);

  ePowerReadOffsetChannelRun_ExpectAndReturn(NULL,NULL,NULL, eSuccess);
  ePowerReadOffsetChannelRun_IgnoreArg_pusInternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset();
  ePowerReadOffsetChannelRun_IgnoreArg_pusExternalOffset1();
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusInternalOffset(&usMockInternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset(&usMockExternalOffset);
  ePowerReadOffsetChannelRun_ReturnThruPtr_pusExternalOffset1(&usMockExternalOffset1);

  // 15 iterations
  // 1
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&(fMockPowerReaded[eInternalPdReference]));
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference]);
  // 2
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 1,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +1]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference +1]);

  // 3
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 2,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference +2]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&(usMockPowerRaw[eInternalPdReference+2]));


  // 4
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 3,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+3]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+3]);

  // 5
  float fTempValue = 500.0f;
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 4,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  //ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+4]);
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fTempValue);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+4]);

  // 6
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 5,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+5]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+5]);

  // 7
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 6,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+6]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+6]);

  // 8
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 7,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+7]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+7]);

  // 9
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 8,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+8]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+8]);

  // 10
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 9,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+9]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+9]);

  // 11
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 10,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+10]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+10]);

  // 12
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 11,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+11]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+11]);

  // 13
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 12,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+12]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+12]);

  // 14
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 13,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+13]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+13]);

  // 15
  ePowerReadChannelRun_ExpectAndReturn(eInternalPdReference + 14,usMockExternalOffset, NULL, NULL, NULL, eSuccess);
  ePowerReadChannelRun_IgnoreArg_pxPowerInputScaling();
  ePowerReadChannelRun_IgnoreArg_pfPowerReaded();
  ePowerReadChannelRun_IgnoreArg_pusPowerRaw();
  ePowerReadChannelRun_ReturnThruPtr_pfPowerReaded(&fMockPowerReaded[eInternalPdReference+14]);
  ePowerReadChannelRun_ReturnThruPtr_pusPowerRaw(&usMockPowerRaw[eInternalPdReference+14]);

  vHpaCriticalErrorDetected_Expect();

  eMpbError = ePowerSensorUpdate();
 
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref1);
  
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xAnalogInputs.fExtern_InputLnaPd_Ref2);
  TEST_ASSERT_EQUAL_INT16(usMockExternalOffset1, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xAnalogInputs.fIntern_PdReference);
  TEST_ASSERT_EQUAL_INT16(usMockInternalOffset, pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower2], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eInternalLnaOutputPower1], pxAmplifierDescriptor.xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1);

  // first IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalInputtPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalLnaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower);

  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower2_1553]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalLnaOutputPower1_1536]* 1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2);

  TEST_ASSERT_EQUAL_FLOAT(10 * log10(fMockPowerReaded[eExternalLnaOutputPower1_1536] ), pxAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower1_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalLnaOutputPower2_1553], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw);

  // second IF
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaInputPower_1536]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalInputMonitor);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaInputPower_1536], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw);
  TEST_ASSERT_EQUAL_FLOAT(10*log10(fMockPowerReaded[eExternalHpaInputPower_1536]*1000), pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_lm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm );
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_lm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw);
  TEST_ASSERT_EQUAL_FLOAT(fMockPowerReaded[eExternalHpaOutputPower_1536_hm]*1000, pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm);
  TEST_ASSERT_EQUAL_INT16(usMockPowerRaw[eExternalHpaOutputPower_1536_hm], pxAmplifierDescriptor.xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw);

  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ,pxAmplifierDescriptor.xPowersInMiliWats.fInternalHpaOpticalOutputMonitor);
  TEST_ASSERT_EQUAL_FLOAT(pxAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower, 10 * log10(pxAmplifierDescriptor.xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm));

  TEST_ASSERT_EQUAL(eFalse, pxAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCanPacketInvalidFlag);
}

/*----------------------------------------------------------------------------*/

