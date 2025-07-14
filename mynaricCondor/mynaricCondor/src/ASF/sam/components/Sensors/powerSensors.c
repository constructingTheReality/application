/**
* @file 		PowerSensor.c
* @brief		PowerSensor.c source file
* @author		juan andres
* @date			Created on 2021-03-11
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "powerSensors.h"
#include "powerSensorsConfigUpdate.h"
#include "powerSensorsUpdateDatabase.h"
#include "powerSensorsConfigUpdate.h"
#include "powerSensorsBoosterAlarm.h"
#include "powerSensorsLnaAlarm.h"
#include "powerReadChannel.h"
#include "mpbPowerIn2Channels.h"
#include "math.h"
#include "boosterStateMachine.h"
#include "lnaStateMachine.h"


/* Private define ----------------------------------------------------------- */
#define POWER_CONFIG_NUMBER_OF_CHANNELS							( eNumberOfPowerChannelConfigurations )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static xLosValues_t xLosHpaValues = {0};
static xHpaLimitsConfig_t xLocalHpaLimitsConfig= {0};
static xHpaPowersConfig_t xLocalHpaPowersConfig = {0};

static const float fPowerSlopeScaleConstant[ POWER_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( PowerChannelConfigId, slopeConstant, interceptConstant )	slopeConstant,
	LIST_OF_POWER_CHANNELS
	#undef X
};

static const float fPowerInterceptScaleConstant[ POWER_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( PowerChannelConfigId, slopeConstant, interceptConstant )	interceptConstant,
	LIST_OF_POWER_CHANNELS
	#undef X
};

static xPowerInputScaling_t xLocalPowerInputScaling[POWER_CONFIG_NUMBER_OF_CHANNELS];

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
eMpbError_t ePowerSensorsFactoryInitCommonChannels( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	xLocalPowerInputScaling[eExternal_PdReference1].fIntercept = fPowerInterceptScaleConstant[ eExternal_PdReference1];
	xLocalPowerInputScaling[eExternal_PdReference1].fSlope		= fPowerSlopeScaleConstant[ eExternal_PdReference1];
	
	xLocalPowerInputScaling[eExternal_PdReference].fIntercept = fPowerInterceptScaleConstant[ eExternal_PdReference];
	xLocalPowerInputScaling[eExternal_PdReference].fSlope		= fPowerSlopeScaleConstant[ eExternal_PdReference];
	
	eMpbError = ePowerSensorsUpdateDatabaseCommon( &xLocalPowerInputScaling[0] );
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsFactoryInitLnaChannels( void )
{ 
	
	eMpbError_t eMpbError = eInvalidParameter;
	
	xLocalPowerInputScaling[eExternalLnaInputPower_1536].fIntercept 			= fPowerInterceptScaleConstant[ eExternalLnaInputPower_1536 ];
	xLocalPowerInputScaling[eExternalLnaInputPower_1536].fSlope     			= fPowerSlopeScaleConstant[ eExternalLnaInputPower_1536 ];
	
	xLocalPowerInputScaling[eExternalLnaInputPower_1553].fIntercept 			= fPowerInterceptScaleConstant[ eExternalLnaInputPower_1553 ];
	xLocalPowerInputScaling[eExternalLnaInputPower_1553].fSlope     			= fPowerSlopeScaleConstant[ eExternalLnaInputPower_1553 ];

 
	xLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fIntercept 		= fPowerInterceptScaleConstant[ eExternalLnaOutputPower1_1536 ];
	xLocalPowerInputScaling[eExternalLnaOutputPower1_1536].fSlope     		= fPowerSlopeScaleConstant[ eExternalLnaOutputPower1_1536 ];

	xLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fIntercept 		= fPowerInterceptScaleConstant[ eExternalLnaOutputPower2_1553 ];
	xLocalPowerInputScaling[eExternalLnaOutputPower2_1553].fSlope     		= fPowerSlopeScaleConstant[ eExternalLnaOutputPower2_1553 ];
	
	//xLocalPowerInputScaling[eExternalLnaBackFacet].fIntercept 		= fPowerInterceptScaleConstant[ eExternalLnaBackFacet ];
	//xLocalPowerInputScaling[eExternalLnaBackFacet].fSlope     		= fPowerSlopeScaleConstant[ eExternalLnaBackFacet ];
	
	/* internal */
	xLocalPowerInputScaling[eInternalLnaOutputPower1].fIntercept	= fPowerInterceptScaleConstant[ eInternalLnaOutputPower1 ];
	xLocalPowerInputScaling[eInternalLnaOutputPower1].fSlope		= fPowerSlopeScaleConstant[ eInternalLnaOutputPower1 ];
	
	xLocalPowerInputScaling[eInternalLnaOutputPower2].fIntercept	= fPowerInterceptScaleConstant[ eInternalLnaOutputPower2 ];
	xLocalPowerInputScaling[eInternalLnaOutputPower2].fSlope		= fPowerSlopeScaleConstant[ eInternalLnaOutputPower2 ];	
	
	xLocalPowerInputScaling[eInternalPdReference].fIntercept	= fPowerInterceptScaleConstant[ eInternalPdReference ];
	xLocalPowerInputScaling[eInternalPdReference].fSlope		= fPowerSlopeScaleConstant[ eInternalPdReference ];
	
	
	eMpbError = ePowerSensorsUpdateDatabaseLna(&xLocalPowerInputScaling[0]);
	
	return eMpbError;
	
}
/*-----------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsFactoryInitBoosterChannels( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	xLosHpaValues.fLosClear = (float)(LOS_CLEAR_LIMIT);
	xLosHpaValues.fLosSet  =  (float)(LOS_SET_LIMIT);
	
	xLocalPowerInputScaling[eExternalHpaInputPower_1536].fIntercept		= fPowerInterceptScaleConstant[ eExternalHpaInputPower_1536 ];
	xLocalPowerInputScaling[eExternalHpaInputPower_1536].fSlope			= fPowerSlopeScaleConstant[ eExternalHpaInputPower_1536 ];
	
	xLocalPowerInputScaling[eExternalHpaInputPower_1553].fIntercept		= fPowerInterceptScaleConstant[ eExternalHpaInputPower_1553 ];
	xLocalPowerInputScaling[eExternalHpaInputPower_1553].fSlope			= fPowerSlopeScaleConstant[ eExternalHpaInputPower_1553 ];
	
	
	xLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fIntercept		= fPowerInterceptScaleConstant[ eExternalHpaOutputPower_1536_lm ];
	xLocalPowerInputScaling[eExternalHpaOutputPower_1536_lm].fSlope			= fPowerSlopeScaleConstant[ eExternalHpaOutputPower_1536_lm ];
	
	xLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fIntercept		= fPowerInterceptScaleConstant[ eExternalHpaOutputPower_1536_hm ];
	xLocalPowerInputScaling[eExternalHpaOutputPower_1536_hm].fSlope			= fPowerSlopeScaleConstant[ eExternalHpaOutputPower_1536_hm ];
	
	xLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fIntercept		= fPowerInterceptScaleConstant[ eExternalHpaOutputPower_1553_lm ];
	xLocalPowerInputScaling[eExternalHpaOutputPower_1553_lm].fSlope			= fPowerSlopeScaleConstant[ eExternalHpaOutputPower_1553_lm ];
	
	xLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fIntercept		= fPowerInterceptScaleConstant[ eExternalHpaOutputPower_1553_hm ];
	xLocalPowerInputScaling[eExternalHpaOutputPower_1553_hm].fSlope			= fPowerSlopeScaleConstant[ eExternalHpaOutputPower_1553_hm ];
	
	
	xLocalHpaLimitsConfig.usMaxHpaCurrentSM_mA					= MAX_HPA_CURRENT_SM_IN_MA ;
	xLocalHpaLimitsConfig.usNominalCurrentPourcentage_sM		= NOMINAL_CURRENT_SM_IN_POURCENTAGE;
	
	xLocalHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA					= MAX_HPA_CURRENT_STAGE_MM_1_IN_MA;
    xLocalHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA					= MAX_HPA_CURRENT_STAGE_MM_2_IN_MA;
	
	xLocalHpaLimitsConfig.usMaxHpaCurrentMM1_mA					= MAX_HPA_CURRENT_MM_1_IN_MA;
    xLocalHpaLimitsConfig.usMaxHpaCurrentMM2_mA					= MAX_HPA_CURRENT_MM_2_IN_MA;
  	xLocalHpaLimitsConfig.usMax_Lh_level_raw                    = MAX_LH_LEVEL_IN_RAW;
 	xLocalHpaLimitsConfig.usMin_Hh_level_raw					= MIN_HH_LEVEL_IN_RAW;	

	xLocalHpaPowersConfig.fHpaBackFacetMin						= MIN_BF_IN_MA;
	xLocalHpaPowersConfig.fHpaBackFacetMax						= MAX_BF_IN_MA;
	
	
	eMpbError = ePowerSensorsUpdateDatabaseBooster(&xLocalPowerInputScaling[0], &xLocalHpaLimitsConfig , &xLocalHpaPowersConfig  , &xLosHpaValues );
	
	return eMpbError;
}

/*--------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsCommonConfigUpdate( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	eMpbError = ePowerSensorsConfigUpdateCommon( &xLocalPowerInputScaling[0] );
	
	return eMpbError;
}
/*--------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsLnaConfigUpdate( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	eMpbError = ePowerSensorsConfigUpdateLna(&xLocalPowerInputScaling[0]);
	 
	return eMpbError;
}
/*--------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorsBoosterConfigUpdate( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
		
	eMpbError = ePowerSensorsConfigUpdateBooster(&xLocalPowerInputScaling[0], &xLocalHpaLimitsConfig , &xLocalHpaPowersConfig, &xLosHpaValues);
	return eMpbError;
	
}
/*------------------------------------------------------------------------------*/
eMpbError_t ePowerSensorUpdate( eBool_t *pbHpaPowerLosAlarm, eBool_t *pbLnaPowerCriticalAlarm, eBool_t *pbBoosterPowerCriticalAlarm )
{
	eMpbError_t eMpbError;
	xAmplifierDescriptor_t *pxAmplifierDescriptor;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );

	float fLocalInputPowerReaded_Aux;
	uint16_t usLocalInputPowerReadedRaw_Aux;
	float fLocalOutputPowerReaded_Aux;
	uint16_t usLocalOutputPowerReadedRaw_Aux;
	float fLocalOutputPowerReaded_Aux2;
	uint16_t usLocalOutputPowerReadedRaw_Aux2;
	float fPower;
	
	ePower_2Channels_State_t *pePower_2Channels_State = NULL;
	//uint16_t usPowerRaw_Aux = 0;
	uint16_t usInternalOffset = 0;
	uint16_t usExternalOffset = 0;
	uint16_t usExternalOffset1 = 0;
	float fPowerReaded[POWER_CONFIG_NUMBER_OF_CHANNELS]; 
	uint16_t usPowerRaw[POWER_CONFIG_NUMBER_OF_CHANNELS]; 

	
	
	/* first , need to read the offset */	
	eMpbError = ePowerReadOffsetChannelRun( &usInternalOffset, &usExternalOffset , &usExternalOffset1 );
		if (eMpbError != eSuccess)
		{
			return eMpbError;
		}
	
	/* ex channel 6 - this gives the offset value for the next channels */
	pxAmplifierDescriptor->xAnalogInputs.fExtern_InputLnaPd_Ref1 = usExternalOffset;
	pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw = usExternalOffset;
	
	
	/* chanel ex 23  , same as ext. 6*/
	pxAmplifierDescriptor->xAnalogInputs.fExtern_InputLnaPd_Ref2 = usExternalOffset1;
	pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw = usExternalOffset1;
	
	
	/* internal adc channel 12*/
	pxAmplifierDescriptor->xAnalogInputs.fIntern_PdReference = usInternalOffset;	
	pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcIntPd_Ref_raw = usInternalOffset;
	
	
	/* read all the powers , one by one */
	for( uint8_t ucI = eInternalPdReference; ucI< eNumberOfPowerChannelConfigurations; ucI++ )
	{				
		eMpbError = ePowerReadChannelRun(ucI,usExternalOffset, xLocalPowerInputScaling[ucI].fSlope, xLocalPowerInputScaling[ucI].fIntercept, &fPowerReaded[ucI] , &usPowerRaw[ucI])	;	
		if( eMpbError != eSuccess )
		{
			//ucI = eNumberOfPowerChannelConfigurations;
			return eMpbError;
		}	
	}
	
//	if( eMpbError == eSuccess )
//	{
		
	
		/* ---internal channels */
		/* internal adc channel 11*/
		pxAmplifierDescriptor->xPowersInMiliWats.fInternalLnaOpticalOutputMonitor2 = fPowerReaded[eInternalLnaOutputPower2];
		/* internal adc channel 13	*/
		pxAmplifierDescriptor->xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1 = fPowerReaded[eInternalLnaOutputPower1];

		/* ---external channels */
		/* ch 0, 1 and 2 */
	
		if(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection == 0 )
		{
			fLocalInputPowerReaded_Aux = fPowerReaded[eExternalLnaInputPower_1553];	
			usLocalInputPowerReadedRaw_Aux = usPowerRaw[eExternalLnaInputPower_1553];

			fLocalOutputPowerReaded_Aux = fPowerReaded[eExternalLnaOutputPower2_1553];
			usLocalOutputPowerReadedRaw_Aux = usPowerRaw[eExternalLnaOutputPower2_1553];
		
		
		}
		else
		{
			fLocalInputPowerReaded_Aux = fPowerReaded[eExternalLnaInputPower_1536];	
			usLocalInputPowerReadedRaw_Aux = usPowerRaw[eExternalLnaInputPower_1536];	
		
			fLocalOutputPowerReaded_Aux = fPowerReaded[eExternalLnaOutputPower1_1536];
			usLocalOutputPowerReadedRaw_Aux = usPowerRaw[eExternalLnaOutputPower1_1536];
		
		}
		/* ch 0  in db*/
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalLnaOpticalInputtPower = fLocalInputPowerReaded_Aux;
	
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalLnaOpticalInputtPower  = fLocalInputPowerReaded_Aux * 1000 ;
		pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExLna_Inm_raw = usLocalInputPowerReadedRaw_Aux;
			/* in Dbm */
		pxAmplifierDescriptor->c414StatusDefinition.fLnaOpticalInputtPower  = 10 * log10(pxAmplifierDescriptor->xPowersInMiliWats.fExternalLnaOpticalInputtPower  );
	
		/*ch1 - 2 in db - LNA one Wavelength par channel */
	
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalLnaOpticalOutputMonitor1 = fPowerReaded[eExternalLnaOutputPower2_1553]* 1000;
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalLnaOpticalOutputMonitor2 = fPowerReaded[eExternalLnaOutputPower1_1536]* 1000;
	
		/*  in Dbm */
		pxAmplifierDescriptor->c414StatusDefinition.fLnaOpticalOutputPower  = 10 * log10(1000*fLocalOutputPowerReaded_Aux  );
		pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw  = usPowerRaw[eExternalLnaOutputPower1_1536];
		pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw = usPowerRaw[eExternalLnaOutputPower2_1553];
	
	
		/* chanel ex 3 */
		if(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection == 1 )
		{
			fLocalInputPowerReaded_Aux = fPowerReaded[eExternalHpaInputPower_1536];
			usLocalInputPowerReadedRaw_Aux = usPowerRaw[eExternalHpaInputPower_1536];
		
			fLocalOutputPowerReaded_Aux = fPowerReaded[eExternalHpaOutputPower_1536_lm];
			usLocalOutputPowerReadedRaw_Aux = usPowerRaw[eExternalHpaOutputPower_1536_lm];
		
			fLocalOutputPowerReaded_Aux2 = fPowerReaded[eExternalHpaOutputPower_1536_hm];
			usLocalOutputPowerReadedRaw_Aux2 = usPowerRaw[eExternalHpaOutputPower_1536_hm];
				
		}
		else
		{
			fLocalInputPowerReaded_Aux = fPowerReaded[eExternalHpaInputPower_1553];
			usLocalInputPowerReadedRaw_Aux = usPowerRaw[eExternalHpaInputPower_1553];

			fLocalOutputPowerReaded_Aux = fPowerReaded[eExternalHpaOutputPower_1553_lm];
			usLocalOutputPowerReadedRaw_Aux = usPowerRaw[eExternalHpaOutputPower_1553_lm];
		
			fLocalOutputPowerReaded_Aux2 = fPowerReaded[eExternalHpaOutputPower_1553_hm];
			usLocalOutputPowerReadedRaw_Aux2 = usPowerRaw[eExternalHpaOutputPower_1553_hm];
		
		}
	
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalHpaOpticalInputMonitor  = fLocalInputPowerReaded_Aux * 1000;
		pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw = usLocalInputPowerReadedRaw_Aux;
		
		
		pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalInputPower = fLocalInputPowerReaded_Aux * 1000;
		
		/* in Dbm */
		pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalInputPower  = 10 * log10(pxAmplifierDescriptor->xPowersInMiliWats.fExternalHpaOpticalInputMonitor  );
	
		/* chanel ex 4-5 */
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm = fLocalOutputPowerReaded_Aux* 1000;
		pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw = usLocalOutputPowerReadedRaw_Aux ;
	
		pxAmplifierDescriptor->xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm = fLocalOutputPowerReaded_Aux2* 1000;
		pxAmplifierDescriptor->xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw = usLocalOutputPowerReadedRaw_Aux2;
	
	
	
		pePower_2Channels_State = &(pxAmplifierDescriptor->ePower_2Channels_State);
	
		eMpbError =  eMpbPowerIn2ChannelsRun( usLocalOutputPowerReadedRaw_Aux,  
							usLocalOutputPowerReadedRaw_Aux2,
							 pxAmplifierDescriptor->xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm,
							 pxAmplifierDescriptor->xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm,
							xLocalHpaLimitsConfig.usMax_Lh_level_raw, 
							xLocalHpaLimitsConfig.usMin_Hh_level_raw, 
							pePower_2Channels_State , 
							&fPower);
	
		if (eMpbError != eSuccess)
		{
			return eMpbError;
		}	
		pxAmplifierDescriptor->xPowersInMiliWats.fInternalHpaOpticalOutputMonitor = fPower;
		if(fPower ==0)
		{
						pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower = 0;
		}else
		{
			
			pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower  = 10 * log10(fPower);
			
		}
	
	#ifdef DEMO_VERSION
	#else
	
		xAlarmAndStatusRegister_t *pxAlarmRegister_402 = 	&(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister);
		MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment_428 = 	&(pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment);
	
		#ifdef DEMO_MASOUR_VERSION
		
		#else
		
		eMpbError =   ePowerSensorBoosterAlarmRun(&xLosHpaValues,
								 &(pxAmplifierDescriptor->xHpaLosStates), 
								pbHpaPowerLosAlarm, 
								pMpbAlarmsAndStatusRegisterBitAssignment_428, 
								pxAmplifierDescriptor->c408StatusDefinition, 
								pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalInputPower , 
								pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower , 
								pxAlarmRegister_402 , 
								pbBoosterPowerCriticalAlarm);
		
		#endif						
		if (eMpbError != eSuccess)
		{
			return eMpbError;
		}
		
		if(*pbBoosterPowerCriticalAlarm == eTrue)// && )
		{
			if(pxAmplifierDescriptor->eMainLoopState >= 2)
			{
				vHpaCriticalErrorDetected();
			}
			else
			{
			pxAlarmRegister_402->AlarmsAndStatusRegisterBitAssignment.bBoosterInternalCriticalErrorInPowerFlag = 0;
				*pbBoosterPowerCriticalAlarm = eFalse ;
					
			}
			
		}

		eMpbError =  ePowerSensorLnaAlarmRun( pMpbAlarmsAndStatusRegisterBitAssignment_428, 
							pxAmplifierDescriptor->c408StatusDefinition, 
							pxAmplifierDescriptor->c414StatusDefinition.fLnaOpticalInputtPower , 
							pxAmplifierDescriptor->c414StatusDefinition.fLnaOpticalOutputPower ,
							pxAlarmRegister_402, 
							pbLnaPowerCriticalAlarm);
		if (eMpbError != eSuccess)
		{
			return eMpbError;
		}
		if(*pbLnaPowerCriticalAlarm == eTrue)
		{
			vLnaCriticalErrorDetected();
		}

		#endif
	//}
	
	return eMpbError;
}


/*----------------------------------------------------------------------------*/



