/*
 * powerSensorsUpdateDatabase.c
 *
 * Created: 6/12/2024 11:42:47 AM
 *  Author: j.castano
 */ 
#include "powerSensorsUpdateDatabase.h"


eMpbError_t ePowerSensorsUpdateDatabaseCommon( xPowerInputScaling_t* pxLocalPowerInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	if(pxLocalPowerInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		xCommonControlParameters_t * pxCommonControlParameters = NULL;
		pxCommonControlParameters = vGetpxCommonControlParameters();
		
		pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference1.fIntercept			= pxLocalPowerInputScaling[eExternal_PdReference1].fIntercept	;
		pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference1.fSlope				= pxLocalPowerInputScaling[eExternal_PdReference1].fSlope	;
		
		pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference.fIntercept			= pxLocalPowerInputScaling[eExternal_PdReference].fIntercept	;
		pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference.fSlope				= pxLocalPowerInputScaling[eExternal_PdReference].fSlope	;
		
		
	}
	return eMpbError;
}
/*----------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsUpdateDatabaseLna(xPowerInputScaling_t *pxLocalPowerInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	if(pxLocalPowerInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		xLnaParameters_t *pxLnaParameters = NULL;
		xLnaParameters_t xLnaParametersl;
		pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl);
		
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1536.fIntercept		= pxLocalPowerInputScaling[eExternalLnaInputPower_1536].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1536.fSlope			= pxLocalPowerInputScaling[eExternalLnaInputPower_1536].fSlope;
		
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1553.fIntercept		= pxLocalPowerInputScaling[eExternalLnaInputPower_1553].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1553.fSlope			= pxLocalPowerInputScaling[eExternalLnaInputPower_1553].fSlope;
		
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fIntercept	= pxLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fSlope		= pxLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fSlope;
		
		//pxLnaParameters->xInputScalingLnaExternalAdc.xExternalLnaOutputPower1_1553.fIntercept	= xLocalPowerInputScaling[eExternalLnaOutputPower1_1553].fIntercept;
		//pxLnaParameters->xInputScalingLnaExternalAdc.xExternalLnaOutputPower1_1553.fSlope		= xLocalPowerInputScaling[eExternalLnaOutputPower1_1553].fSlope;
		
		
		//	pxLnaParameters->xInputScalingLnaExternalAdc.xExternalLnaOutputPower2_1536.fIntercept	= xLocalPowerInputScaling[eExternalLnaOutputPower2_1536].fIntercept;
		//	pxLnaParameters->xInputScalingLnaExternalAdc.xExternalLnaOutputPower2_1536.fSlope		= xLocalPowerInputScaling[eExternalLnaOutputPower2_1536].fSlope;
		
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fIntercept	= pxLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fSlope		= pxLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fSlope;
		
		//pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fIntercept		= xLocalPowerInputScaling[eExternalLnaBackFacet].fIntercept;
		//pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fSlope			= xLocalPowerInputScaling[eExternalLnaBackFacet].fSlope;
		
		/* internal */
		pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower1.fIntercept	= pxLocalPowerInputScaling[eInternalLnaOutputPower1].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower1.fSlope		= pxLocalPowerInputScaling[eInternalLnaOutputPower1].fSlope;
		
		pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower2.fIntercept	= pxLocalPowerInputScaling[eInternalLnaOutputPower2].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower2.fSlope		= pxLocalPowerInputScaling[eInternalLnaOutputPower2].fSlope;
		
		pxLnaParameters->xInputScalingLnaAdc.xInternalPdReference.fIntercept	= pxLocalPowerInputScaling[eInternalPdReference].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xInternalPdReference.fSlope		= pxLocalPowerInputScaling[eInternalPdReference].fSlope;
	}
	return eMpbError;
}
/*---------------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsUpdateDatabaseBooster(xPowerInputScaling_t *pxLocalPowerInputScaling, xHpaLimitsConfig_t *pxHpaLimitsConfig, xHpaPowersConfig_t *pxHpaPowersConfig, xLosValues_t *pxLosValues)
{
	
	eBool_t bValidPointers = eFalse;
	eMpbError_t eMpbError = eInvalidParameter;
	
	bValidPointers = ( pxLocalPowerInputScaling == NULL) || (pxHpaLimitsConfig == NULL) || (pxHpaPowersConfig == NULL) || (pxLosValues==NULL);
	
	if(bValidPointers == eTrue)
	{
		
		eMpbError = eSuccess;
		xBoosterParameters_t *pxBoosterParameters = NULL;
		pxBoosterParameters = vGetpxBoosterParameters();
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fIntercept		= pxLocalPowerInputScaling[eExternalHpaInputPower_1536].fIntercept ;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fSlope			= pxLocalPowerInputScaling[eExternalHpaInputPower_1536].fSlope;
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fIntercept		= pxLocalPowerInputScaling[eExternalHpaInputPower_1553].fIntercept ;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fSlope			= pxLocalPowerInputScaling[eExternalHpaInputPower_1553].fSlope;
		//xPowerInputScalinExternalHpaInputPower_1536;
		//static xPowerInputScaling_t xPowerInputScalinExternalHpaInputPower_1553;
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fIntercept	= pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fSlope		= pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fSlope;
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fIntercept  = pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fSlope		= pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fSlope	;
		
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fIntercept	= pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fSlope		= pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fSlope;

		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fIntercept   = pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fSlope		= pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fSlope	;
		

		//pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fIntercept		= xPowerInputScalingExternalHpaSm_ld_Bfm.fIntercept;
		//pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fSlope			= xPowerInputScalingExternalHpaSm_ld_Bfm.fSlope	;
		
		pxBoosterParameters->xLosHpaValues.fLosClear												= pxLosValues->fLosClear ;
		pxBoosterParameters->xLosHpaValues.fLosSet													= pxLosValues->fLosSet ;
		
		pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentSM_mA									= pxHpaLimitsConfig->usMaxHpaCurrentSM_mA;
		pxBoosterParameters->xHpaLimitsConfig.usNominalCurrentPourcentage_sM						= pxHpaLimitsConfig->usNominalCurrentPourcentage_sM;
		pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentMM1_mA									= pxHpaLimitsConfig->usMaxHpaCurrentMM1_mA;
		pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentMM2_mA									= pxHpaLimitsConfig->usMaxHpaCurrentMM2_mA;
		pxBoosterParameters->xHpaLimitsConfig.usMax_Lh_level_raw									= pxHpaLimitsConfig->usMax_Lh_level_raw;
		pxBoosterParameters->xHpaLimitsConfig.usMin_Hh_level_raw									= pxHpaLimitsConfig->usMin_Hh_level_raw;
		
		pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA	   						= pxHpaLimitsConfig->usMaxHpaCurrentStageMM1_mA;
		pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA							= pxHpaLimitsConfig->usMaxHpaCurrentStageMM2_mA;
		
		
		pxBoosterParameters->xHpaPowersConfig.fHpaBackFacetMin										= pxHpaPowersConfig->fHpaBackFacetMin;
		pxBoosterParameters->xHpaPowersConfig.fHpaBackFacetMax										= pxHpaPowersConfig->fHpaBackFacetMax;
		
	}
	return eMpbError;
}