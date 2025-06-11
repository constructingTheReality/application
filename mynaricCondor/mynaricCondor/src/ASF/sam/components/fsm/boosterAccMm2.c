/*
 * boosterAccMm2.c
 *
 * Created: 6/26/2024 4:23:10 PM
 *  Author: j.castano
 */ 
/*
 * boosterAccMm1.c
 *
 * Created: 6/26/2024 3:56:44 PM
 *  Author: j.castano
 */ 

#include "mpblibs.h"
#include "boosterAccMm2.h"
#include "accControl.h"




void vBoosterAccMm2Run(AccDataMm2_t *pAccDataMm2)
{

	if ( pAccDataMm2->usStepsNumberMmHpa2 > 0  )
	{
			if(pAccDataMm2->bIncreaseMmHpa2 == eTrue)
			{
				if( (pAccDataMm2->usSetpointInmAMmHpa2-pAccDataMm2->usCurrentMm2Read) <  CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1_ACC)
				{
					pAccDataMm2->usCurrentMm2Read = pAccDataMm2->usCurrentMm2Read + (pAccDataMm2->usSetpointInmAMmHpa2-pAccDataMm2->usCurrentMm2Read) ;
				}
				else
				{
					pAccDataMm2->usCurrentMm2Read = pAccDataMm2->usCurrentMm2Read + CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1_ACC;
				}
				
			}
			else
			{
				if( (pAccDataMm2->usCurrentMm2Read-pAccDataMm2->usSetpointInmAMmHpa2) <  CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1_ACC)
				{
					//	usCurrentRead = usCurrentRead - (usCurrentRead-usSetpointInmA);
					pAccDataMm2->usCurrentMm1Read = pAccDataMm1->usSetpointInmAMmHpa1;
				}
				else
				{
					pAccDataMm1->usCurrentMm1Read = pAccDataMm1->usCurrentMm1Read - CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1_ACC;
				}
				
			}
			
			
			pAccDataMm1->usStepsNumberMmHpa1--;
			if(pAccDataMm1->usStepsNumberMmHpa1 == 0)
			{
				pAccDataMm1->usCurrentMm1Read = pAccDataMm1->usSetpointInmAMmHpa1;
			}
			//fCurrentMmHpa1			= pxAmplifierDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent;
			vAccControlLaserUpdateHpaMm2( pAccDataMm2->usCurrentMm2Read );
			//vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  usSetpointInPwmMmHpa1*4);
			
	}
		
	

	

}