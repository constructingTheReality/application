/*
 * currentSensorsConfigUpdate.c
 *
 * Created: 6/18/2024 1:04:36 PM
 *  Author: j.castano
 */ 
#include "currentSensorsConfigUpdate.h"


eMpbError_t eCurrentSensorsConfigUpdateLna(xCurrentInputScaling_t *pxLocalCurrentInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	xLnaParameters_t *pxLnaParameters;
	xLnaParameters_t xLnaParametersl;
	pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl );
	
	
	if(pxLocalCurrentInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
	
		pxLocalCurrentInputScaling[eAdcExLnaSingleModeldCurrentMonitor].fIntercept 	=pxLnaParameters->xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fIntercept ;
		pxLocalCurrentInputScaling[eAdcExLnaSingleModeldCurrentMonitor].fSlope 		=pxLnaParameters->xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fSlope ;

		pxLocalCurrentInputScaling[eAdcExternalLnaSm_ld_Bfm].fIntercept				= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fIntercept;
		pxLocalCurrentInputScaling[eAdcExternalLnaSm_ld_Bfm].fSlope					= pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fSlope;
		
	}
	
	return eMpbError;
	
}

/*----------------------------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensorsConfigUpdateHpa(xCurrentInputScaling_t *pxLocalCurrentInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	xBoosterParameters_t *pxBoosterParameters;
	pxBoosterParameters = vGetpxBoosterParameters( );
	
	
	if(pxLocalCurrentInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		pxLocalCurrentInputScaling[eAdcExHpaSingleModeld_CurrentMonitor].fIntercept		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fIntercept;
		pxLocalCurrentInputScaling[eAdcExHpaSingleModeld_CurrentMonitor].fSlope			= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fSlope;
	
		pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor1].fIntercept		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fIntercept;
		pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor1].fSlope			= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fSlope;
	
		pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor2].fIntercept		= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fIntercept;
		pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor2].fSlope			= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fSlope;
	
		pxLocalCurrentInputScaling[eAdcExternalHpaSm_ld_Bfm].fIntercept					= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fIntercept;
		pxLocalCurrentInputScaling[eAdcExternalHpaSm_ld_Bfm].fSlope						= pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fSlope;
	
		
	}
	
	return eMpbError;
	
}