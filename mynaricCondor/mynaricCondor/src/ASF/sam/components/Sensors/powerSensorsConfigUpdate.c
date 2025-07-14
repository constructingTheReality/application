/*
 * powerSensorsConfigUpdate.c
 *
 * Created: 6/12/2024 10:46:01 AM
 *  Author: j.castano
 */ 
#include "powerSensorsConfigUpdate.h"


eMpbError_t ePowerSensorsConfigUpdateCommon(xPowerInputScaling_t *pxLocalPowerInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	if(pxLocalPowerInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		xCommonControlParameters_t *pxCommonControlParameters;
		pxCommonControlParameters = vGetpxCommonControlParameters();

		pxLocalPowerInputScaling[eExternal_PdReference].fIntercept	= pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference.fIntercept ;
		pxLocalPowerInputScaling[eExternal_PdReference].fSlope		= pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference.fSlope ;

		pxLocalPowerInputScaling[eExternal_PdReference1].fIntercept	= pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference1.fIntercept ;
		pxLocalPowerInputScaling[eExternal_PdReference1].fSlope		= pxCommonControlParameters->xInputScalingCommonControlExternalAdc.xExternalPdReference1.fSlope ;
		
		
	}
	return eMpbError;
}
/*----------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsConfigUpdateLna(xPowerInputScaling_t *pxLocalPowerInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
		
	if(pxLocalPowerInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		xLnaParameters_t *pxLnaParameters;
		xLnaParameters_t xLnaParametersl;
		pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl);
		

		
		pxLocalPowerInputScaling[eExternalLnaInputPower_1536].fIntercept		= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1536.fIntercept ;
		pxLocalPowerInputScaling[eExternalLnaInputPower_1536].fSlope			= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1536.fSlope ;
		
		pxLocalPowerInputScaling[eExternalLnaInputPower_1553].fIntercept		= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1553.fIntercept ;
		pxLocalPowerInputScaling[eExternalLnaInputPower_1553].fSlope			= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaInputPower_1553.fSlope ;
		
		
		pxLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fIntercept	= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fIntercept;
		pxLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fSlope		= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fSlope;
		
		
		//xLocalPowerInputScaling[eExternalLnaOutputPower1_1553].fIntercept	= pxLnaParameters->xInputScalingLnaExternalAdc.xExternalLnaOutputPower1_1553.fIntercept;
		//xLocalPowerInputScaling[eExternalLnaOutputPower1_1553].fSlope		= pxLnaParameters->xInputScalingLnaExternalAdc.xExternalLnaOutputPower1_1553.fSlope;
		
		
		pxLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fIntercept	= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fIntercept;
		pxLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fSlope		= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fSlope;
		
		//xLocalPowerInputScaling[eExternalLnaBackFacet].fIntercept		= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fIntercept;
		//xLocalPowerInputScaling[eExternalLnaBackFacet].fSlope			= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fSlope;
		
		
		
		/* internal */
		pxLocalPowerInputScaling[eInternalLnaOutputPower1].fIntercept   = pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower1.fIntercept;
		pxLocalPowerInputScaling[eInternalLnaOutputPower1].fSlope        = pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower1.fSlope;
		
		pxLocalPowerInputScaling[eInternalLnaOutputPower2].fIntercept    = pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower2.fIntercept;
		pxLocalPowerInputScaling[eInternalLnaOutputPower2].fSlope        = pxLnaParameters->xInputScalingLnaAdc.xInternalLnaOutputPower2.fSlope ;
		
		pxLocalPowerInputScaling[eInternalPdReference].fIntercept         =  pxLnaParameters->xInputScalingLnaAdc.xInternalPdReference.fIntercept	;
		pxLocalPowerInputScaling[eInternalPdReference].fSlope             = pxLnaParameters->xInputScalingLnaAdc.xInternalPdReference.fSlope		;
		
	}
	return eMpbError;
}
/*---------------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsConfigUpdateBooster(xPowerInputScaling_t *pxLocalPowerInputScaling, xHpaLimitsConfig_t *pxHpaLimitsConfig, xHpaPowersConfig_t *pxHpaPowersConfig, xLosValues_t *pxLosValues)
{
	
	eBool_t bValidPointers = eFalse;
	eMpbError_t eMpbError = eInvalidParameter;
	
	//bValidPointers = ( pxLocalPowerInputScaling == NULL) || (pxHpaLimitsConfig == NULL) || (pxHpaPowersConfig == NULL) || (pxLosValues==NULL);
	bValidPointers = (( pxLocalPowerInputScaling != NULL) && (pxHpaLimitsConfig != NULL) && (pxHpaPowersConfig != NULL) && (pxLosValues!= NULL) );
		
	if(bValidPointers == eTrue)
	{
		
		eMpbError = eSuccess;
		xBoosterParameters_t *pxBoosterParameters;
		pxBoosterParameters = vGetpxBoosterParameters( );
		
		pxLocalPowerInputScaling[eExternalHpaInputPower_1536].fIntercept		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fIntercept;
		pxLocalPowerInputScaling[eExternalHpaInputPower_1536].fSlope			= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fSlope;
		
		pxLocalPowerInputScaling[eExternalHpaInputPower_1553].fIntercept		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fIntercept;
		pxLocalPowerInputScaling[eExternalHpaInputPower_1553].fSlope			= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fSlope;
		
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fIntercept	= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fIntercept;
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fSlope		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fSlope;
		
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fIntercept  = pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fIntercept;
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fSlope		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fSlope;
		
		
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fIntercept	= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fIntercept;
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fSlope		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fSlope;

		pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fIntercept  = pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fIntercept;
		pxLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fSlope		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fSlope;
		
		
		
		//xPowerInputScalingExternalHpaSm_ld_Bfm.fIntercept		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fIntercept;
		//xPowerInputScalingExternalHpaSm_ld_Bfm.fSlope			= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fSlope;
		
		pxLosValues->fLosClear									= pxBoosterParameters->xLosHpaValues.fLosClear;
		pxLosValues->fLosSet									=  pxBoosterParameters->xLosHpaValues.fLosSet;
		
		pxHpaLimitsConfig->usMaxHpaCurrentSM_mA				= pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentSM_mA;
		pxHpaLimitsConfig->usNominalCurrentPourcentage_sM    = pxBoosterParameters->xHpaLimitsConfig.usNominalCurrentPourcentage_sM;
		pxHpaLimitsConfig->usMaxHpaCurrentMM1_mA				= pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentMM1_mA;
		pxHpaLimitsConfig->usMaxHpaCurrentMM2_mA				= pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentMM2_mA;
		pxHpaLimitsConfig->usMaxHpaCurrentStageMM1_mA				= pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA;
		pxHpaLimitsConfig->usMaxHpaCurrentStageMM2_mA				= pxBoosterParameters->xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA;
		pxHpaLimitsConfig->usMax_Lh_level_raw				= pxBoosterParameters->xHpaLimitsConfig.usMax_Lh_level_raw	;
		pxHpaLimitsConfig->usMin_Hh_level_raw				= pxBoosterParameters->xHpaLimitsConfig.usMin_Hh_level_raw	;
		
		pxHpaPowersConfig->fHpaBackFacetMin					= pxBoosterParameters->xHpaPowersConfig.fHpaBackFacetMin;
		pxHpaPowersConfig->fHpaBackFacetMax					= pxBoosterParameters->xHpaPowersConfig.fHpaBackFacetMax	;
		
	
	}
	return eMpbError;
}
