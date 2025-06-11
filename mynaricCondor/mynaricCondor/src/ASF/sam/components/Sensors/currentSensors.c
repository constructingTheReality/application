/**
* @file 		CurrentSensor.c
* @brief		CurrentSensor.c source file
* @author		juan andres
* @date			Created on 2023-03-11
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
#include "currentSensors.h"
#include "currentSensorsReadChannel.h"
#include "projectDef.h"
#include "currentSensorsLnaAlarm.h"
#include "currentSensorsHpaAlarm.h"
#include "currentSensorsCommonAlarm.h"
#include "currentSensorsBackfacetAlarm.h"
#include "currentSensorsUpdateDatabase.h"
#include "currentSensorsConfigUpdate.h"

/* Private define ----------------------------------------------------------- */
#define CURRENT_CONFIG_NUMBER_OF_CHANNELS							( eNumberOfChannelConfigurations )
#define OFFSET_MIDDLE_POINT														 ( 1500 )
#define MIN_CURRENT_IN_CIRCUIT                          ( 200 )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

static const float fCurrentSlopeScaleConstant[ CURRENT_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( CurrentChannelConfigId, slopeConstant, interceptConstant )	slopeConstant,
	LIST_OF_CURRENT_CHANNELS
	#undef X
};

static const float fCurrentInterceptScaleConstant[ CURRENT_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( CurrentChannelConfigId, slopeConstant, interceptConstant )	interceptConstant,
	LIST_OF_CURRENT_CHANNELS
	#undef X
};


static xCurrentInputScaling_t xLocalCurrentInputScaling[CURRENT_CONFIG_NUMBER_OF_CHANNELS];

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void vCurrentSensorsInitInternalChannels( void )
{
	uint8_t cdata = 0;
	
	static float f1 = 0.0f;
	
	cdata = eNumberOfChannelConfigurations;
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH1 ];
	f1 = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH1].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH1 ];
	f1 = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH1 ];
	
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH2].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH2 ];
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH1].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH2].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH2 ];
	
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH1].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH2].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH2 ];
	
	xLocalCurrentInputScaling[eAdcInternal3_3VPower_VoltageMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal3_3VPower_VoltageMonitor ];
	xLocalCurrentInputScaling[eAdcInternal3_3VPower_VoltageMonitor].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal3_3VPower_VoltageMonitor ];
	
	xLocalCurrentInputScaling[eAdcInternal3VPower_VoltageMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal3VPower_VoltageMonitor ];
	xLocalCurrentInputScaling[eAdcInternal3VPower_VoltageMonitor].fSlope = fCurrentSlopeScaleConstant[ eAdcInternal3VPower_VoltageMonitor ];

	xLocalCurrentInputScaling[eAdcInternalPowerCurrentMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternalPowerCurrentMonitor ];
	xLocalCurrentInputScaling[eAdcInternalPowerCurrentMonitor].fSlope = fCurrentSlopeScaleConstant[ eAdcInternalPowerCurrentMonitor ];
	
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH1].fSlope = fCurrentSlopeScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH2].fSlope = fCurrentSlopeScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH2 ];
		
}
/*-----------------------------------------------------------------------------*/
void vCurrentSensorsFactoryInitLnaChannels( void )
{
	xLocalCurrentInputScaling[eAdcExLnaSingleModeldCurrentMonitor].fIntercept 	= fCurrentInterceptScaleConstant[ eAdcExLnaSingleModeldCurrentMonitor ];
	xLocalCurrentInputScaling[eAdcExLnaSingleModeldCurrentMonitor].fSlope 	= fCurrentSlopeScaleConstant[ eAdcExLnaSingleModeldCurrentMonitor ];

	xLocalCurrentInputScaling[eAdcExternalLnaSm_ld_Bfm].fIntercept			= fCurrentInterceptScaleConstant[ eAdcExternalLnaSm_ld_Bfm ];
	xLocalCurrentInputScaling[eAdcExternalLnaSm_ld_Bfm].fSlope				= fCurrentSlopeScaleConstant[ eAdcExternalLnaSm_ld_Bfm ];
	
	eCurrentSensorsUpdateDatabaseLna( &xLocalCurrentInputScaling[0]);
}
/*-----------------------------------------------------------------------------*/
void vCurrentSensorsFactoryInitBoosterChannels( void )
{
	xLocalCurrentInputScaling[eAdcExHpaSingleModeld_CurrentMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcExHpaSingleModeld_CurrentMonitor ];
	xLocalCurrentInputScaling[eAdcExHpaSingleModeld_CurrentMonitor].fSlope = fCurrentSlopeScaleConstant[ eAdcExHpaSingleModeld_CurrentMonitor ];
	
	xLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor1].fIntercept		= fCurrentInterceptScaleConstant[ eAdcExHpaMultiModeld_CurrentMonitor1 ];
	xLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor1].fSlope			= fCurrentSlopeScaleConstant[ eAdcExHpaMultiModeld_CurrentMonitor1 ];
	
	
	xLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor2].fIntercept      = fCurrentInterceptScaleConstant[ eAdcExHpaMultiModeld_CurrentMonitor2 ];
	xLocalCurrentInputScaling[eAdcExHpaMultiModeld_CurrentMonitor2].fSlope			= fCurrentSlopeScaleConstant[ eAdcExHpaMultiModeld_CurrentMonitor2 ];
		
	
	xLocalCurrentInputScaling[eAdcExternalHpaSm_ld_Bfm].fIntercept		= fCurrentInterceptScaleConstant[ eAdcExternalHpaSm_ld_Bfm ];
	xLocalCurrentInputScaling[eAdcExternalHpaSm_ld_Bfm].fSlope			= fCurrentSlopeScaleConstant[ eAdcExternalHpaSm_ld_Bfm ];
	
	eCurrentSensorsUpdateDatabaseHpa( &xLocalCurrentInputScaling[0]);
}
/*--------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensorsLnaConfigUpdate( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	eMpbError = eCurrentSensorsConfigUpdateLna(&xLocalCurrentInputScaling[0]);
	
	return eMpbError;	
}
/*--------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensorsBoosterConfigUpdate( void )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	eMpbError = eCurrentSensorsConfigUpdateHpa(&xLocalCurrentInputScaling[0]);
	
	return eMpbError;

}
/*------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensorUpdate( eBool_t *pHpaCurrentAlarm, eBool_t *pLnaCurrentAlarm, eBool_t *pInternalCurrentAlarm )
{
	eBool_t bLnaBackfacetCurrentCriticalAlarm;
	eBool_t bHpaBackfacetCurrentCriticalAlarm;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	
	
	eBool_t bLnaCurrentCriticalAlarm = eFalse;
	eBool_t bHpaCurrentAlarm = eFalse;
	eBool_t bInternalCurrentAlarm = eFalse;
	
	eMpbError_t eMpbError;
	uint16_t usOffset = 0;	
	
		
	float fCurrentReadedInMa[CURRENT_CONFIG_NUMBER_OF_CHANNELS];
	uint16_t usCurrentRaw[CURRENT_CONFIG_NUMBER_OF_CHANNELS];
	
	
	usOffset = 	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw;
	
	/* read all the powers , one by one */
	for( uint8_t ucI = eAdcInternal28VPwrCurrentMonitorCH1; ucI< eNumberOfChannelConfigurations; ucI++ )
	{		
		eMpbError = eCurrentSensorsReadChannelRun( ucI, usOffset,  xLocalCurrentInputScaling[ucI].fSlope, xLocalCurrentInputScaling[ucI].fIntercept, &fCurrentReadedInMa[ucI], &usCurrentRaw[ucI]);		
		if( eMpbError != eSuccess )
		{
			return eMpbError; 		//ucI = eNumberOfChannelConfigurations;
		}
	}
	
	/* fill db */
	/*ch internal 0 */
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1 = fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH1];
	/*ch internal 1 */
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2 = fCurrentReadedInMa[eAdcInternal28VPwrCurrentMonitorCH2];
	/*ch internal 2 */
	pxLaserBeamDescriptor->c414StatusDefinition.fPowerSupplyMonitor = fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1];
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1 = fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH1];
	/*ch internal 3 */
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2 = fCurrentReadedInMa[eAdcInternal28VPwrVoltageMonitorCH2];
	/*ch internal 4 */
	pxLaserBeamDescriptor->c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1 = fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH1];	
	/*ch internal 5 */
	pxLaserBeamDescriptor->c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2 = fCurrentReadedInMa[eAdcInternal7VPwrVoltageMonitorCH2];	
	/*ch internal 6 */
	pxLaserBeamDescriptor->c423StatusDefinition.f3_3V_PwrVoltageMonitor = fCurrentReadedInMa[eAdcInternal3_3VPower_VoltageMonitor];		
	/*ch internal 7 */
	pxLaserBeamDescriptor->c423StatusDefinition.f3V_ld_PwrVoltageMonitor = fCurrentReadedInMa[eAdcInternal3VPower_VoltageMonitor];		
	/*ch internal 8 */
	pxLaserBeamDescriptor->c423StatusDefinition.fAdcPwrCurrentMonitor = fCurrentReadedInMa[eAdcInternalPowerCurrentMonitor];		
	/*ch internal 9 */
	pxLaserBeamDescriptor->c423StatusDefinition.fCanPwrCurrentMonitor1 = fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH1];		
	/*ch internal 10 */
	pxLaserBeamDescriptor->c423StatusDefinition.fCanPwrCurrentMonitor2 = fCurrentReadedInMa[eAdcInternalCanPwrCurrentMonitorCH2];		
	/*ch external 11 */
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent =  1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor];		
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw = usCurrentRaw[eAdcExLnaSingleModeldCurrentMonitor];
	/*ch external 12 - ADC #9 */
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent = 1000 * fCurrentReadedInMa[eAdcExHpaSingleModeld_CurrentMonitor];		
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw = usCurrentRaw[eAdcExHpaSingleModeld_CurrentMonitor];
	/*ch external 13 - ADC #10 */
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent = 1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor1];		
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw = usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor1];
	/*ch external 16 - ADC #11 */
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent = 1000 * fCurrentReadedInMa[eAdcExHpaMultiModeld_CurrentMonitor2];		
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw = usCurrentRaw[eAdcExHpaMultiModeld_CurrentMonitor2];
	/*ch external 14 - ADC #7 */
	pxLaserBeamDescriptor->xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor = 1000 * fCurrentReadedInMa[eAdcExternalLnaSm_ld_Bfm];
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw = usCurrentRaw[eAdcExternalLnaSm_ld_Bfm];
	/*ch external 15 - ADC #22 */	
	pxLaserBeamDescriptor->xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor = 1000 * fCurrentReadedInMa[eAdcExternalHpaSm_ld_Bfm];
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw = usCurrentRaw[eAdcExternalHpaSm_ld_Bfm];

	/* alarms */
	
		/* check for alarms*/
		//	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent = fCurrentReaded + fCurrentReaded_Aux ;
	AlarmsAndStatusRegisterBitAssignment_t xAlarmRegister ;	
	
		
	AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister = 	&(pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment);
		
	//&(pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment);		
	
	//memcpy( &(pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment) , &xAlarmRegister, sizeof(AlarmsAndStatusRegisterBitAssignment_t) );
			
	//MpbAlarmsAndStatusRegisterBitAssignment_t MpbAlarmsAndStatusRegisterBitAssignment ;
	//&(pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment);
	
	//memcpy( &(pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment) , &MpbAlarmsAndStatusRegisterBitAssignment, sizeof(AlarmsAndStatusRegisterBitAssignment_t) );
	
	MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment = 	&(pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment);
		
			
	//	vprvSetAlarmsCurrentHpa_BackFacet(pxLaserBeamDescriptor->xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor, xHpaPowersConfig);
		
		
		#ifdef DEMO_VERSION
	//	#else
	
		eMpbError =  eCurrentSensorsLnaAlarmRun( pMpbAlarmsAndStatusRegisterBitAssignment, //&MpbAlarmsAndStatusRegisterBitAssignment,
													pxLaserBeamDescriptor->c409StatusDefinition,
													pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent ,
													pxAlarmRegister, //&xAlarmRegister,
													&bLnaCurrentCriticalAlarm);
		
		if(eMpbError != eSuccess)
		{
			return eMpbError;
		}
		
		if(bLnaCurrentCriticalAlarm == eTrue)
		{
			//vLnaAlarmProtocolDetected();
		}
		
		
		//	eCurrentSensorsLnaAlarmRun( &MpbAlarmsAndStatusRegisterBitAssignment, pxLaserBeamDescriptor->c409StatusDefinition, pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent ,&xAlarmRegister, &bLnaCurrentCriticalAlarm);
			
			eMpbError =  eCurrentSensorsHpaAlarmRun( pxLaserBeamDescriptor->c409StatusDefinition,
														pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent,
														pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent,
														pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent,
														pxAlarmRegister,// pInternalCurrentAlarm//&xAlarmRegister,
														&bHpaCurrentAlarm);
			if(eMpbError != eSuccess)
			{
				return eMpbError;
			}
			
			if(bHpaCurrentAlarm == eTrue)
			{
				// trigger Hpa alarm
			}
		
		/*eCurrentSensorsHpaAlarmRun( pxLaserBeamDescriptor->c409StatusDefinition,
									pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent,
									pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent,
									pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent,
									&xAlarmRegister,
									pHpaCurrentAlarm);*/
		
	//	*pLnaCurrentAlarm  = (pxAlarmRegister->bLnaCurrentLimitAlarmStatus == 1)? eTrue : eFalse;
		
     	
		
		//eCurrentSensorsCommonAlarmRun( &(pxLaserBeamDescriptor->c423StatusDefinition), &pxLaserBeamDescriptor->xInternalAlarms, &bInternalCurrentAlarm );
		/*eCurrentSensorsCommonAlarmRun( &(pxLaserBeamDescriptor->c423StatusDefinition),
										&pxLaserBeamDescriptor->c423StatusDefinition.xInternalAlarms,
										&bInternalCurrentAlarm );*/
			
	/*	eCurrentSensorsCommonAlarmRun( c423StatusDefinition_t *c423StatusDefinition, 
										c428StatusDefinition_t * c428StatusDefinition , 
										eBool_t *bInternalAlarm );*/
			if (bInternalCurrentAlarm == eTrue)
			{
				// trigger both
			}
		/*
		eCurrentSensorsBackfacetAlarmRun( pxLaserBeamDescriptor->xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor, 
										  pxLaserBeamDescriptor->xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor, 
										  float fLnaBackfacetLimit, 
										  float  fBackfacetHpaLimit, 
										  &xAlarmRegister , 
										  &bLnaBackfacetCurrentCriticalAlarm, 
										  &bHpaBackfacetCurrentCriticalAlarm);*/
		
		//	*pInternalCurrentAlarm = bInternalCurrentAlarm ;

		
		//pxAlarmRegister->bLnaCurrentLimitAlarmStatus = ( (bLowLimitAlarm==eTrue) || (bHighLimitAlarm==eTrue) )? 1:0;
		//	vLnaAlarmProtocolDetected();
		


		#endif
	
	
	
		return eMpbError;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/* chhanel 0 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc28VPwrCurrentMonitorCH1, xScalingInternal28V_PwrCurrentMonitor_Ch1, &fCurrentReaded,&usCurrentRaw );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrCurrentMonitor_Ch1 = fCurrentReaded;
	*/
	/* chhanel 1 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc28VPwrCurrentMonitorCH2, xScalingInternal28V_PwrCurrentMonitor_Ch2, &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
		
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrCurrentMonitor_Ch2 = fCurrentReaded;	*/
	/* chhanel 2 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc28VPwrVoltageMonitorCH1, xScalingInternal28V_PwrVoltageMonitor_Ch1, &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c414StatusDefinition.fPowerSupplyMonitor = fCurrentReaded;
		
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrVoltageMonitor_Ch1 = fCurrentReaded;	
	*/
	/* chhanel 3 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc28VPwrVoltageMonitorCH2, xScalingInternal28V_PwrVoltageMonitor_Ch2, &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c423StatusDefinition.f28V_PwrVoltageMonitor_Ch2 = fCurrentReaded;
	*/
	/* chhanel 4 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc7VPwrVoltageMonitorCH1, xScalingInternal7V_PwrVoltageMonitor_Ch1, &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
		
	pxLaserBeamDescriptor->c423StatusDefinition.f7V_PwrVoltageMonitor_Ch1 = fCurrentReaded;	
	*/
	/* chhanel 5 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc7VPwrVoltageMonitorCH2, xScalingInternal7V_PwrVoltageMonitor_Ch2, &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	
	pxLaserBeamDescriptor->c423StatusDefinition.f7V_PwrVoltageMonitor_Ch2 = fCurrentReaded;			
	*/
	/* chanel 6 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc3_3VPower_VoltageMonitor, xScalingInternal3_3V_PwrVoltageMonitor , &fCurrentReaded,&usCurrentRaw );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	
	pxLaserBeamDescriptor->c423StatusDefinition.f3_3V_PwrVoltageMonitor = fCurrentReaded;	
	*/
	/* chanel 7 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdc3VPower_VoltageMonitor, xScalingInternal3V_ld_PwrVoltageMonitor , &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c423StatusDefinition.f3V_ld_PwrVoltageMonitor = fCurrentReaded;	
	
	*/
	
	/* chanel 8 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcPowerCurrentMonitor, xScalingInternalAdcPwrCurrentMonitor , &fCurrentReaded,&usCurrentRaw );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c423StatusDefinition.fAdcPwrCurrentMonitor = fCurrentReaded;	
	*/
	/* chanel 9 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcCanPwrCurrentMonitorCH1, xScalingInternalCanPwrCurrentMonitor1 , &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c423StatusDefinition.fCanPwrCurrentMonitor1 = fCurrentReaded;
	*/
	/* chanel 10 - internal 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcCanPwrCurrentMonitorCH2, xScalingInternalCanPwrCurrentMonitor2 , &fCurrentReaded,&usCurrentRaw );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c423StatusDefinition.fCanPwrCurrentMonitor2 = fCurrentReaded;
		*/
		
		/* TWO CHANNLES MISSING */
		
		
		
	/* chanel ex 7 , list 14
	
	eMpbError =  eCurrentSensingGetCurrentmAWithOffset( eHandleExternalLnaSm_ld_Bfm, xCurrentInputScalingExternalLnaSm_ld_Bfm, usOffset ,  &fCurrentReaded, &usCurrentRaw );
	
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	//pxLaserBeamDescriptor->xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor = fCurrentReaded;
	//pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw = usCurrentRaw;
	pxLaserBeamDescriptor->xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor = fCurrentReaded * 1000 ;
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw = usCurrentRaw;
	*/
	
	/*-----------------------------------*/
	/*-----------------------------------*/
	/*-----------------------------------*/
	/*-----------------------------------*/
	/*-----------------------------------*/
	/*-----------------------------------*/
	/* 11 of the list
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExLnaSmldCurrentMonitor, xScalingExternalLnaSmLedCurrentMonitor , &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent = fCurrentReaded * 1000;
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw = usCurrentRaw;
*/
	
	
	/*--- channel 9-external , 12 of the list 
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaSmld_CurrentMonitor, xScalingExternalHpaSmLedCurrentMonitor , &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent = fCurrentReaded* 1000;
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw = usCurrentRaw;
*/
/*--- channel 10-11 external   13 of the list
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaMultiModeld_CurrentMonitor1, xScalingExternalHpaMmLedCurrentMonitor1 , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent = fCurrentReaded_Aux* 1000;
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw = usCurrentRaw;
	*/

/* 16 of the list
	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaMultiModeld_CurrentMonitor2, xScalingExternalHpaMmLedCurrentMonitor2 , &fCurrentReaded ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent = fCurrentReaded* 1000;
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw = usCurrentRaw;
	*/

	/* chanel ex 22 , 15 of the list
			
	eMpbError =  eCurrentSensingGetCurrentmAWithOffset( eHandleExternalHpaSm_ld_Bfm, xCurrentInputScalingExternalHpaSm_ld_Bfm, usOffset, &fCurrentReaded, &usCurrentRaw );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
//	pxLaserBeamDescriptor->xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor = fCurrentReaded * 1000 ;
//	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw = usCurrentRaw;
	
	pxLaserBeamDescriptor->xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor = fCurrentReaded * 1000;
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw = usCurrentRaw;
	*/
	/* check for alarms
//	pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent = fCurrentReaded + fCurrentReaded_Aux ;
	AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister = 	&(pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister);
	
	MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment = 	&(pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment);
	
	vprvSetAlarmsCurrentHpa_BackFacet(pxLaserBeamDescriptor->xAnalogInputs.fExtern_HpaSmCurrentBackFacetMonitor, xHpaPowersConfig);
	
	
	#ifdef DEMO_VERSION 
	#else
		
	vprvSetAlarmsCurrentLna( pMpbAlarmsAndStatusRegisterBitAssignment, pxLaserBeamDescriptor->c409StatusDefinition, pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent ,pxAlarmRegister);
	*pLnaCurrentAlarm  = (pxAlarmRegister->bLnaCurrentLimitAlarmStatus == 1)? eTrue : eFalse;
	
	
	
	vprvSetInternalAlarmCommon( &(pxLaserBeamDescriptor->c423StatusDefinition), &pxLaserBeamDescriptor->xInternalAlarms, &bInternalCurrentAlarm );
//	*pInternalCurrentAlarm = bInternalCurrentAlarm ;

	
	//pxAlarmRegister->bLnaCurrentLimitAlarmStatus = ( (bLowLimitAlarm==eTrue) || (bHighLimitAlarm==eTrue) )? 1:0;
//	vLnaAlarmProtocolDetected();
	vprvSetAlarmsCurrentBooster( pxLaserBeamDescriptor->c409StatusDefinition, pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent,
																			  pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent,
																			  pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent,
																			  pxAlarmRegister);

	#endif*/
	
/* garbage */

	/*--- channel 12 external */
	//xScalingExternalTh.fIntercept = 0.0f;
	//xScalingExternalTh.fSlope = 1.0f;
	
	
/*	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExSmLnaThermistor, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmld_Thermistor_raw = usCurrentRaw;
	*/
	/*--- channel 13 external */
/*	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExSmHpaThermistor, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_Thermistor_raw = usCurrentRaw;
 */
 
	/*--- channel 16 external */
/*	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaMmThermistor1, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor1_raw = usCurrentRaw;
*/
	/*--- channel 17 external */
/*	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaMmThermistor2, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor2_raw = usCurrentRaw;
	*/
	
	/*--- channel 18 external */
	/*eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaMmThermistor3, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
		pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor3_raw = usCurrentRaw;*/
 	/*--- channel 19 external */
 	/*eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExHpaMmThermistor4, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
 	if( eMpbError != eSuccess )
 	{
	 	vMpblibsAssertParam( 0 );
 	}
 	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor4_raw = usCurrentRaw;
 */
	/*--- channel 20 external */
/*	eMpbError =  eCurrentSensingGetCurrentmA( eHandleAdcExCaseThermistor, xScalingExternalTh , &fCurrentReaded_Aux ,&usCurrentRaw);
	if( eMpbError != eSuccess )
	{
		 vMpblibsAssertParam( 0 );
	}
	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExCaseThermistor1_raw = usCurrentRaw;
 */
 
 


/*------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


