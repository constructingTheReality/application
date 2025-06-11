/*
 * boosterAccSm.c
 *
 * Created: 6/26/2024 2:58:03 PM
 *  Author: j.castano
 */ 


#include "mpblibs.h"
#include "boosterAccSm.h"
#include "accControl.h"
#include "trajectoryCalculator.h"

static uint16_t usThresholdsPumps[eNumberOfLasers] = { CURRENT_INCREASE_BY_STEP_IN_MA_HPA1,
													   CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1,
													   CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1  
													 };
static void (*boosterAccRunTable[]) (uint16_t) =
{
	vBoosterAccControlOnSm1,
	vBoosterAccControlOnMm1,
	vBoosterAccControlOnMm2	
};

static eMpbError_t (*boosterAccPwmConversionTable[]) (eBool_t,uint16_t,uint16_t*) =
{
	ePwmToCurrentConversion_Hpa1,
	ePwmToCurrentConversion_MmHpa1,
	ePwmToCurrentConversion_MmHpa2
};

static void (*boosterAccEnableDriverTable[]) (eBool_t) =
{
	vBoosterAccEnableOnSm1,
	vBoosterAccEnableOnMm1,
	vBoosterAccEnableOnMm2
};

/*------------------------------------------------------*/
void vBoosterAccRun(  ePumpType_t ePumpType, uint16_t *pusStepsNumber, eBool_t  bIncrease, uint16_t usSetpointInmA, uint16_t  usCurrentRead, eBool_t bEnable)
{
	uint16_t usStepSize = 0;
	
	usStepSize = usThresholdsPumps[ ePumpType ];		
	
	if ( *pusStepsNumber > 0  )
	{
		if( bIncrease == eTrue)
		{
			if( (usSetpointInmA - usCurrentRead) <  usStepSize)
			{
				usCurrentRead = usSetpointInmA ;
			}
			else
			{
				usCurrentRead = usCurrentRead + usStepSize;
			}				
		}
		else
		{
			if( (usCurrentRead-usSetpointInmA) <  usStepSize)
			{
				usCurrentRead = usSetpointInmA;
			}
			else
			{
				usCurrentRead = usCurrentRead - usStepSize;
			}	
		}
				
		*pusStepsNumber = *pusStepsNumber-1;
		
		if( *pusStepsNumber == 0)
		{
			usCurrentRead = usSetpointInmA;
			if( bEnable == eFalse)
			{
				boosterAccEnableDriverTable[ ePumpType ](bEnable);
			}
		}				
		boosterAccRunTable[ ePumpType ] (usCurrentRead);								
	}
}
/*------------------------------------------------------*/
void vBoosterAccControlOnSm1( uint16_t usCurrent)
{
	vAccControlLaserUpdateHpaSm1( usCurrent );
}
/*------------------------------------------------------*/
void vBoosterAccControlOnMm1( uint16_t usCurrent)
{
	vAccControlLaserUpdateHpaMm1( usCurrent );
}
/*------------------------------------------------------*/
void vBoosterAccControlOnMm2( uint16_t usCurrent)
{
	vAccControlLaserUpdateHpaMm2( usCurrent );
}
/*------------------------------------------------------*/
void vBoosterAccEnableOnSm1(eBool_t bEnable)
{
	vEnableHpaSingleMode( bEnable );
}
/*------------------------------------------------------*/
void vBoosterAccEnableOnMm1(eBool_t bEnable)
{
	vEnableHpaMultiMode1( bEnable );	
}
/*------------------------------------------------------*/	
void vBoosterAccEnableOnMm2(eBool_t bEnable)
{
	vEnableHpaMultiMode2( bEnable );	
}
/*------------------------------------------------------*/
void vBoosterSetupAcc(ePumpType_t  ePumpType		,	uint16_t usLastSetpointInPwm	,	float fCurrent, 
					  uint16_t usSetpointInPwm		,	uint16_t *pusSetpointInmA		, eBool_t  bIsStep50mA,
					  uint16_t *pusStepsNumber		,	eBool_t  *pbIncrease			, eBool_t bWavelengthIs1536, eBool_t bHpaReadyForSecondStep)
{
							
	uint16_t usSetpointInmA = 0;
							
	usSetpointInmA = *pusSetpointInmA;
	
	if(usLastSetpointInPwm != usSetpointInPwm )
	{
		
		if( (ePumpType != eSM) && (bHpaReadyForSecondStep == eFalse) )
		{
			
		}
		else
		{
			boosterAccPwmConversionTable[ ePumpType ] (bWavelengthIs1536 , usSetpointInPwm, pusSetpointInmA);	
		
	//	ePwmToCurrentConversion_Hpa1( bWavelengthIs1536, usSetpointInPwm, pusSetpointInmA );
		//eMpbError_t ePwmToCurrentConversion_Hpa1(eBool_t bWavelengthIs1536,  uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA ); 
		
			vTrajectoryCalculatorRun( bIsStep50mA, *pusSetpointInmA, fCurrent,  pusStepsNumber, pbIncrease );
		//void vTrajectoryCalculatorRun( eBool_t bIsStep50mA, uint16_t usSetpoint, uint16_t usCurrentRead,  uint16_t *pNumberOfSteps, eBool_t *pbIncrease);
		
		
			*pusStepsNumber = *pusStepsNumber + 1;
		}
		//usCurrentRead			= (uint16_t)fCurrentHpaSm1;
	}
}		
/*------------------------------------------------------*/
void vBoosterAccManager(	ePumpType_t  ePumpType		,	uint16_t usLastSetpointInPwm	,	float fCurrent, eBool_t bEnable,
							uint16_t usSetpointInPwm		,	uint16_t *pusSetpointInmA		, eBool_t  bIsStep50mA,
							uint16_t *pusStepsNumber		,	eBool_t  *pbIncrease			, eBool_t bWavelengthIs1536, eBool_t bHpaReadyForSecondStep)
{
	
	uint16_t usCurrentRead;
	
	
	if( bEnable == eTrue)
	{
		boosterAccEnableDriverTable[ ePumpType ](bEnable);
	}
	
	
	vBoosterSetupAcc( ePumpType ,	usLastSetpointInPwm	,	fCurrent,
					  usSetpointInPwm		,	pusSetpointInmA		, bIsStep50mA,
					  pusStepsNumber		,	pbIncrease			, bWavelengthIs1536, bHpaReadyForSecondStep);
	
	usCurrentRead	= (uint16_t)fCurrent;
	
	if(bHpaReadyForSecondStep == eFalse)
	{
		vBoosterAccControlOnMm1(0);	
		vBoosterAccControlOnMm2(0);
	}
	else
	{
		vBoosterAccRun(  ePumpType, pusStepsNumber, *pbIncrease, *pusSetpointInmA, usCurrentRead, bEnable);	
	}
	
	
	
}

