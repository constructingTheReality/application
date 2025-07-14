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
#include "currentSensors.h"
#include "dictionaryUtils.h"
#include "mock_currentSensorsUpdateDatabase.h"
#include "mock_currentSensorsConfigUpdate.h"
#include "currentSensorsLnaAlarm.h"
#include "currentSensorsHpaAlarm.h"
#include "currentSensorsCommonAlarm.h"
#include "mock_currentSensorsreadChannel.h"
#include "mock_laserData.h"


/* Private define ------------------------------------------------------------*/
#define CURRENT_CONFIG_NUMBER_OF_CHANNELS             ( eNumberOfChannelConfigurations )
#define OFFSET_MIDDLE_POINT                            ( 1500 )
#define MIN_CURRENT_IN_CIRCUIT                          ( 200 )

/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
eMpbError_t eMpbError;
float fCurrentReadedInMa[CURRENT_CONFIG_NUMBER_OF_CHANNELS];
uint16_t usCurrentRaw[CURRENT_CONFIG_NUMBER_OF_CHANNELS];
xCurrentInputScaling_t xLocalCurrentInputScaling[CURRENT_CONFIG_NUMBER_OF_CHANNELS];
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
 
void setUp()
{
 for (int i = eAdcInternal28VPwrCurrentMonitorCH1; i < eNumberOfChannelConfigurations; i ++)
 {
    fCurrentReadedInMa[i] = 1.0;
    usCurrentRaw[i] = 3;
    xLocalCurrentInputScaling[i].fSlope = 1.0;
    xLocalCurrentInputScaling[i].fIntercept = 1.0;
 }
  
}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{
  
}
/*----------------------------------------------------------------------------*/ 
/******************************************************************************/
/*                            eCurrentSensorUpdate                            */
/******************************************************************************/

/*----------------------------------------------------------------------------*/ 
void test_5_1_eCurrentSensorUpdate_eCurrentSensorsReadChannelRunFailure_Fail()
{

  eBool_t pHpaCurrentAlarm;
  eBool_t pLnaCurrentAlarm;
  eBool_t pInternalCurrentAlarm;

  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eUnknownError);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eUnknownError, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_5_2_eCurrentSensorUpdate_eCurrentSensorsLnaAlarmRunFailure_Fail()
{

  eBool_t pHpaCurrentAlarm;
  eBool_t pLnaCurrentAlarm;
  eBool_t pInternalCurrentAlarm;

  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 3.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 3.5;
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_5_3_eCurrentSensorUpdate_eCurrentSensorsHpaAlarmRunFailure_Fail()
{

  eBool_t pHpaCurrentAlarm;
  eBool_t pLnaCurrentAlarm;
  eBool_t pInternalCurrentAlarm;

  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = -3.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 7.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 7.9;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 7.8;
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

}

/*----------------------------------------------------------------------------*/

void test_5_4_eCurrentSensorUpdate_NoAlarms_Success()
{

  eBool_t pHpaCurrentAlarm;
  eBool_t pLnaCurrentAlarm;
  eBool_t pInternalCurrentAlarm;

  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = -3.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1007.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = -4;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1007.8;


  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0.0 );
}

/*----------------------------------------------------------------------------*/

void test_5_5_eCurrentSensorUpdate_LnaCurrentLow_LnaAlarmRaised_Success()
{

  eBool_t pHpaCurrentAlarm;
  eBool_t pLnaCurrentAlarm;
  eBool_t pInternalCurrentAlarm;

  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1007.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;

  // set up params set in common alarm to eFalse
  pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1 = LEVEL_28V + 1;
  pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor = LEVEL_3V;
  pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor = LEVEL_3V;
  pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1 = LEVEL_7V;
  pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2 = LEVEL_7V;
  pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor = LEVEL_ADC;
  pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1 = LEVEL_28_CURRENT;
  pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2 = LEVEL_28_CURRENT;
  pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 = LEVEL_ADC;
  pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2 = LEVEL_ADC;
  
  pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue = 0;

  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0 );
  
}

/*----------------------------------------------------------------------------*/

void test_5_6_eCurrentSensorUpdate_LnaCurrentHigh_LnaAlarmRaised_Success()
{

  eBool_t pHpaCurrentAlarm;
  eBool_t pLnaCurrentAlarm;
  eBool_t pInternalCurrentAlarm;

  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 999.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0 ); 
}

/*----------------------------------------------------------------------------*/

void test_5_7_eCurrentSensorUpdate_HpaCurrent1Low_HpaAlarmRaised_Success()
{

  // pump1:
  fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor] = -5.0;
  //pump2: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1]
  //pump3: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2]
  
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eTrue, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0 ); 
}

/*----------------------------------------------------------------------------*/

void test_5_8_eCurrentSensorUpdate_HpaCurrent1High_HpaAlarmRaised_Success()
{

  // pump1:
  fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor] = 1005.0;
  //pump2: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1]
  //pump3: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2]
  
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eTrue, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0 ); 
}

/*----------------------------------------------------------------------------*/


void test_5_9_eCurrentSensorUpdate_HpaCurrent2Low_HpaAlarmRaised_Success()
{

  // pump1: fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor] = -5.0;
  //pump2: 
  fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1] = -5.0;
  //pump3: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2]
  
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eTrue, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0 ); 
}

/*----------------------------------------------------------------------------*/

void test_5_10_eCurrentSensorUpdate_HpaCurrent2High_HpaAlarmRaised_Success()
{

  // pump1: fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor] = -5.0;
  //pump2: 
  fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1] = 1005.0;
  //pump3: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2]
  
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eTrue, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eFalse,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) <= 0 ); 
  
}

/*----------------------------------------------------------------------------*/


void test_5_11_eCurrentSensorUpdate_HpaCurrent3Low_HpaAlarmRaised_Success()
{

  // pump1: fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor] = -5.0;
  //pump2: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1] = 1005.0;
  //pump3: 
  fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2] = -5.0;
  
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eTrue,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eTrue,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) > 0 );
}

/*----------------------------------------------------------------------------*/


void test_5_12_eCurrentSensorUpdate_HpaCurrent3High_HpaAlarmRaised_Success()
{

  // pump1: fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor] = -5.0;
  //pump2: fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1] = 1005.0;
  //pump3: 
  fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2] = 1000.1;
  
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 900.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 37000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 900;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;

  fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1] = 37.0; // >= 36.0
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eTrue,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  
  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eTrue,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) > 0 );

}

/*----------------------------------------------------------------------------*/



void test_5_13_eCurrentSensorUpdate_CommonAlarmFlagsNotRaised_Success()
{
 
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1] = 20.0; // < LEVEL_28V
  fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor] = 7.1; // > 6.6
  fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor] = 7.1;
  fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1] = 40.2; // > 36.6
  fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2] = 40.3;
  fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor] = 200.3; // > 180
  fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1] = 200.2; // > 166
  fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2] = 200.2;
  fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1] = 181.2; // > 180
  fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2] = 300;
  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 0;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  

  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eTrue,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) > 0 );

}

/*----------------------------------------------------------------------------*/

void test_5_14_eCurrentSensorUpdate_CommonAlarmFlagsRaised_Success()
{
 
  // Initialization
  vCurrentSensorsInitInternalChannels();

  eCurrentSensorsUpdateDatabaseLna_ExpectAndReturn(NULL,eSuccess);
  eCurrentSensorsUpdateDatabaseLna_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitLnaChannels();

  eCurrentSensorsUpdateDatabaseHpa_ExpectAndReturn(NULL, eSuccess);
  eCurrentSensorsUpdateDatabaseHpa_IgnoreArg_pxLocalCurrentInputScaling();
  vCurrentSensorsFactoryInitBoosterChannels();

  fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1] = 20.0; // < LEVEL_28V
  fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor] = 5.1; // < 6.6
  fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor] = 7.1;
  fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1] = 30.2; // < 36.6
  fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2] = 40.3;
  fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor] = 100.3; // < 180
  fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1] = 10.2; // < 166
  fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2] = 200.2;
  fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1] = 170.2; // < 180
  fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2] = 300;
  // End of Init

  xAmplifierDescriptor_t pxLaserBeamDescriptor;
  pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = 2;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 1000.5;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump = 0;
  pxLaserBeamDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 1010;
  // current read = 1000
  vGetxAmplifierDescriptor_ExpectAndReturn(&pxLaserBeamDescriptor);

  // 17 iterations
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1]));
  
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1 + 1, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1 +1]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 + 1]));
 
  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+2, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+2]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +2]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+3, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+3]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +3]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+4, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+4]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +4]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+5, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+5]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +5]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+6, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+6]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +6]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+7, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+7]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +7]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+8, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+8]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +8]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+9, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+9]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +9]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+10, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+10]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +10]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+11, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+11]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +11]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+12, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+12]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +12]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+13, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+13]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +13]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+14, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+14]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +14]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+15, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+15]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +15]));

  eCurrentSensorsReadChannelRun_ExpectAndReturn(eAdcInternal28VPwrCurrentMonitorCH1+16, pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw, xLocalCurrentInputScaling[0],NULL,NULL, eSuccess);
  eCurrentSensorsReadChannelRun_IgnoreArg_xCurrentInputScaling();
  eCurrentSensorsReadChannelRun_IgnoreArg_pfCurrentReadedInMa();
  eCurrentSensorsReadChannelRun_IgnoreArg_pusCurrentRaw();
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pfCurrentReadedInMa(&(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1+16]));
  eCurrentSensorsReadChannelRun_ReturnThruPtr_pusCurrentRaw(&(usCurrentRaw[eAdcInternal28VPwrCurrentMonitorCH1 +16]));


  eMpbError = eCurrentSensorUpdate();
  TEST_ASSERT_EQUAL(eSuccess, eMpbError);

  // CHECKS //
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c414StatusDefinition.fPowerSupplyMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3_3V_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor], pxLaserBeamDescriptor.c423StatusDefinition.f3V_ld_PwrVoltageMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor], pxLaserBeamDescriptor.c423StatusDefinition.fAdcPwrCurrentMonitor);
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor1 );
  TEST_ASSERT_EQUAL_FLOAT(fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2], pxLaserBeamDescriptor.c423StatusDefinition.fCanPwrCurrentMonitor2);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalLnaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw);
  TEST_ASSERT_EQUAL_FLOAT(1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor);
  TEST_ASSERT_EQUAL_INT16(usCurrentRaw[eAdcExternalHpaSm_ld_Bfm], pxLaserBeamDescriptor.xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw);

  // LNA High alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaCurrentHighAlarmStatus);
  // LNA alarm
  TEST_ASSERT_EQUAL_INT8(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus);
 
  // HPA alarm pump 1
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus);

  // HPA alarm pump 2
  TEST_ASSERT_EQUAL(eFalse, pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag);

  // HPA alarm pump 3
  TEST_ASSERT_EQUAL(eFalse,pxLaserBeamDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag);
  

  // Common Alarm
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow );
  TEST_ASSERT_EQUAL_INT8(eTrue, pxLaserBeamDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow );
  
  TEST_ASSERT_EQUAL(eTrue,
        ((pxLaserBeamDescriptor.c428StatusDefinition.ulMpbAlarmsValue & 0x00000000000FC000)
         >> DEF_428_COMMON_ALARMS_POSITION) > 0 );

}
/*----------------------------------------------------------------------------*/