
/**
  * @file			test_powerSensors.c
  * @brief    test file for powerSensorsConfigUpdate.c (creating a file with this name is resulting
  														in an unknown error)
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
#include "powerSensorsConfigUpdate.h"
#include "mock_laserData.h"
//#include "mock_CurrentSensing.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
xPowerInputScaling_t pxLocalPowerInputScaling[15];
eMpbError_t eMpbError;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/*----------------------------------------------------------------------------*/ 
void setUp()
{

}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{

}
/*----------------------------------------------------------------------------*/ 

/******************************************************************************/
/*                     ePowerSensorsConfigUpdateCommon                        */
/******************************************************************************/

void test_4_1_ePowerSensorsConfigUpdateCommon_InvalidParams_Fail()
{
	eMpbError = ePowerSensorsConfigUpdateCommon(NULL);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}
/*----------------------------------------------------------------------------*/ 
void test_4_2_ePowerSensorsConfigUpdateCommon_Success()
{
	xCommonControlParameters_t pxCommonControlParameters;
	pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference.fIntercept = 2.0;
	pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference.fSlope = 3.5;
	pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference1.fIntercept = 3.2;
	pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference1.fSlope = 1.9;

	vGetpxCommonControlParameters_ExpectAndReturn(&pxCommonControlParameters);

	eMpbError = ePowerSensorsConfigUpdateCommon(&pxLocalPowerInputScaling[0]);

	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_FLOAT(pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference.fIntercept, pxLocalPowerInputScaling[eExternal_PdReference].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference.fSlope, pxLocalPowerInputScaling[eExternal_PdReference].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference1.fIntercept, pxLocalPowerInputScaling[eExternal_PdReference1].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxCommonControlParameters.xInputScalingCommonControlExternalAdc.xExternalPdReference1.fSlope, pxLocalPowerInputScaling[eExternal_PdReference1].fSlope);
}	

/******************************************************************************/
/*                     ePowerSensorsConfigUpdateLna                           */
/******************************************************************************/
void test_5_1_ePowerSensorsConfigUpdateLna_InvalidParams_Fail()
{
	eMpbError = ePowerSensorsConfigUpdateLna(NULL);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);
}

/*----------------------------------------------------------------------------*/

void test_5_2_ePowerSensorsConfigUpdateLna_Success()
{
	

	xLnaParameters_t pxLnaParameters;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1536.fIntercept = 3.5;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1536.fSlope = 3.1;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1553.fIntercept = 4.7;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1553.fSlope = 9.0;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fIntercept = 7.2;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fSlope = 8.8;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fIntercept = 2;
	pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fSlope = 0;
	pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower1.fIntercept = 7.3;
	pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower1.fSlope = 6.5;
	pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower2.fIntercept = 4;
	pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower2.fSlope = 4;
	pxLnaParameters.xInputScalingLnaAdc.xInternalPdReference.fIntercept = 3.9;
	pxLnaParameters.xInputScalingLnaAdc.xInternalPdReference.fSlope = 7.5; 

	vGetpxLnaParameters_ExpectAndReturn(&pxLnaParameters);

	eMpbError = ePowerSensorsConfigUpdateLna(&pxLocalPowerInputScaling[0]);

	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1536.fIntercept, pxLocalPowerInputScaling[eExternalLnaInputPower_1536].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1536.fSlope, pxLocalPowerInputScaling[eExternalLnaInputPower_1536].fSlope	);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1553.fIntercept, pxLocalPowerInputScaling[eExternalLnaInputPower_1553].fIntercept );
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaInputPower_1553.fSlope, pxLocalPowerInputScaling[eExternalLnaInputPower_1553].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fIntercept, pxLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fSlope, pxLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower1.fIntercept,pxLocalPowerInputScaling[eInternalLnaOutputPower1].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower1.fSlope, pxLocalPowerInputScaling[eInternalLnaOutputPower1].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xInternalPdReference.fIntercept, pxLocalPowerInputScaling[eInternalPdReference].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xInternalPdReference.fSlope, pxLocalPowerInputScaling[eInternalPdReference].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fIntercept, pxLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fSlope,pxLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fSlope );
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower2.fIntercept,pxLocalPowerInputScaling[eInternalLnaOutputPower2].fIntercept );
	TEST_ASSERT_EQUAL_FLOAT(pxLnaParameters.xInputScalingLnaAdc.xInternalLnaOutputPower2.fSlope, pxLocalPowerInputScaling[eInternalLnaOutputPower2].fSlope);


}

/******************************************************************************/
/*                    ePowerSensorsConfigUpdateBooster                        */
/******************************************************************************/

void test_6_1_ePowerSensorsConfigUpdateBooster_InvalidParams_Fail()
{
	xHpaLimitsConfig_t pxHpaLimitsConfig;
	xHpaPowersConfig_t pxHpaPowersConfig;
	xLosValues_t pxLosValues;

	eMpbError = ePowerSensorsConfigUpdateBooster(NULL, &pxHpaLimitsConfig, &pxHpaPowersConfig, &pxLosValues);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorsConfigUpdateBooster(&pxLocalPowerInputScaling[0], NULL, &pxHpaPowersConfig, &pxLosValues);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorsConfigUpdateBooster(&pxLocalPowerInputScaling[0], &pxHpaLimitsConfig, NULL, &pxLosValues);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorsConfigUpdateBooster(&pxLocalPowerInputScaling[0], &pxHpaLimitsConfig, &pxHpaPowersConfig, NULL);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorsConfigUpdateBooster(NULL, NULL, NULL, NULL);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorsConfigUpdateBooster(NULL, NULL, &pxHpaPowersConfig, &pxLosValues);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError);

	eMpbError = eSuccess;
	eMpbError = ePowerSensorsConfigUpdateBooster(&pxLocalPowerInputScaling[0], &pxHpaLimitsConfig, NULL, NULL);
	TEST_ASSERT_EQUAL(eInvalidParameter, eMpbError); 
	
}
/*----------------------------------------------------------------------------*/ 

void test_6_2_ePowerSensorsConfigUpdateBooster_Success()
{
	xHpaLimitsConfig_t pxHpaLimitsConfig;
	xHpaPowersConfig_t pxHpaPowersConfig;
	xLosValues_t pxLosValues;

	xBoosterParameters_t pxBoosterParameters;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fIntercept = 1.2;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fSlope = 3.2;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fIntercept = 7.1;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fSlope = 0.3;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fIntercept = 6.3;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fSlope = 8.8;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fIntercept = 3.8;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fSlope = 9.0;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fIntercept = 8.4;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fSlope = 4.8;
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fIntercept	= 4.9;	
	pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fSlope = 3.1;
	
	pxBoosterParameters.xLosHpaValues.fLosClear = 4.5;
	pxBoosterParameters.xLosHpaValues.fLosSet = 0.5;

	pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentSM_mA = 8;
	pxBoosterParameters.xHpaLimitsConfig.usNominalCurrentPourcentage_sM = 5;
	pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentMM1_mA = 2;
    pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentMM2_mA = 3;
    pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA = 7;
    pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA = 1;
    pxBoosterParameters.xHpaLimitsConfig.usMax_Lh_level_raw = 9;
    pxBoosterParameters.xHpaLimitsConfig.usMin_Hh_level_raw = 6;
    pxBoosterParameters.xHpaPowersConfig.fHpaBackFacetMin = 4.6;
    pxBoosterParameters.xHpaPowersConfig.fHpaBackFacetMax = 7.0; 

	vGetpxBoosterParameters_ExpectAndReturn(&pxBoosterParameters);


	eMpbError = ePowerSensorsConfigUpdateBooster(&pxLocalPowerInputScaling[0], &pxHpaLimitsConfig, &pxHpaPowersConfig, &pxLosValues);
	TEST_ASSERT_EQUAL(eSuccess, eMpbError);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fIntercept, pxLocalPowerInputScaling[eExternalHpaInputPower_1536].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fSlope, pxLocalPowerInputScaling[eExternalHpaInputPower_1536].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fIntercept, pxLocalPowerInputScaling[eExternalHpaInputPower_1553].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fSlope, pxLocalPowerInputScaling[eExternalHpaInputPower_1553].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fIntercept, pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fSlope, pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fIntercept, pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fSlope, pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fIntercept,pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fIntercept );
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fSlope, pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fSlope);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fIntercept, pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fIntercept);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fSlope, pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fSlope);

	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xLosHpaValues.fLosClear, pxLosValues.fLosClear	);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xLosHpaValues.fLosSet, pxLosValues.fLosSet);

	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentSM_mA, pxHpaLimitsConfig.usMaxHpaCurrentSM_mA	);
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usNominalCurrentPourcentage_sM, pxHpaLimitsConfig.usNominalCurrentPourcentage_sM );
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentMM1_mA, pxHpaLimitsConfig.usMaxHpaCurrentMM1_mA);
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentMM2_mA ,pxHpaLimitsConfig.usMaxHpaCurrentMM2_mA );
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA, pxHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA);
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA, pxHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA);
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMax_Lh_level_raw, pxHpaLimitsConfig.usMax_Lh_level_raw);
	TEST_ASSERT_EQUAL_INT16(pxBoosterParameters.xHpaLimitsConfig.usMin_Hh_level_raw, pxHpaLimitsConfig.usMin_Hh_level_raw );
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xHpaPowersConfig.fHpaBackFacetMin, pxHpaPowersConfig.fHpaBackFacetMin);
	TEST_ASSERT_EQUAL_FLOAT(pxBoosterParameters.xHpaPowersConfig.fHpaBackFacetMax, pxHpaPowersConfig.fHpaBackFacetMax	);

}
/*---------------------------------------------------------------------------------------*/