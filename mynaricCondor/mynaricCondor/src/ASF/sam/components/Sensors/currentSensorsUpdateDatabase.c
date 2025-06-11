/*
 * currentSensorsUpdateDatabase.c
 *
 * Created: 6/18/2024 12:50:40 PM
 *  Author: j.castano
 */ 
#include "currentSensorsUpdateDatabase.h"


/*------------------------------------------------------------------------------*/

eMpbError_t eCurrentSensorsUpdateDatabaseLna( xCurrentInputScaling_t* pxLocalCurrentInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	
	if(pxLocalCurrentInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		xLnaParameters_t *pxLnaParameters = NULL;
		xLnaParameters_t xLnaParametersl;
		pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl);
	
		pxLnaParameters->xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fIntercept = pxLocalCurrentInputScaling[eAdcExLnaSingleModeldCurrentMonitor].fIntercept; //xScalingExternalLnaSmLedCurrentMonitor.fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fSlope	 = pxLocalCurrentInputScaling[eAdcExLnaSingleModeldCurrentMonitor].fSlope; //xScalingExternalLnaSmLedCurrentMonitor.fSlope;
	
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fIntercept				= pxLocalCurrentInputScaling[eAdcExternalLnaSm_ld_Bfm].fIntercept;
		pxLnaParameters->xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fSlope				= 	pxLocalCurrentInputScaling[eAdcExternalLnaSm_ld_Bfm].fSlope;
	}
	
	
	
	return eMpbError;
}

/*------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensorsUpdateDatabaseHpa( xCurrentInputScaling_t* pxLocalCurrentInputScaling)
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	
	if(pxLocalCurrentInputScaling != NULL)
	{
		
		eMpbError = eSuccess;
		
		xBoosterParameters_t *pxBoosterParameters = NULL;
		pxBoosterParameters = vGetpxBoosterParameters();
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fIntercept =  pxLocalCurrentInputScaling[eAdcExHpaSingleModeld_CurrentMonitor].fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fSlope = pxLocalCurrentInputScaling[eAdcExHpaSingleModeld_CurrentMonitor].fSlope;
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fIntercept = pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor1].fIntercept; //xScalingExternalHpaMmLedCurrentMonitor1.fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fSlope = pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor1].fSlope; //xScalingExternalHpaMmLedCurrentMonitor1.fSlope;
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fIntercept = pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor2].fIntercept; //xScalingExternalHpaMmLedCurrentMonitor2.fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fSlope = pxLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor2].fSlope;
		
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fIntercept = pxLocalCurrentInputScaling[eAdcExternalHpaSm_ld_Bfm].fIntercept;
		pxBoosterParameters->xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fSlope = pxLocalCurrentInputScaling[eAdcExternalHpaSm_ld_Bfm].fSlope;
		
		
	}
	
	
	
	return eMpbError;
}