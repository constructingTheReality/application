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

static float fCurrentReadedInMa[CURRENT_CONFIG_NUMBER_OF_CHANNELS];

static uint16_t usCurrentRaw[CURRENT_CONFIG_NUMBER_OF_CHANNELS];


/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void vCurrentSensorsInitInternalChannels( void )
{
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH1].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrCurrentMonitorCH2].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrCurrentMonitorCH2 ];
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH1].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternal28VPwrVoltageMonitorCH2].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal28VPwrVoltageMonitorCH2 ];
	
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH1].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternal7VPwrVoltageMonitorCH2].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal7VPwrVoltageMonitorCH2 ];
	
	xLocalCurrentInputScaling[eAdcInternal3_3VPower_VoltageMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal3_3VPower_VoltageMonitor ];
	xLocalCurrentInputScaling[eAdcInternal3_3VPower_VoltageMonitor].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal3_3VPower_VoltageMonitor ];
	
	xLocalCurrentInputScaling[eAdcInternal3VPower_VoltageMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternal3VPower_VoltageMonitor ];
	xLocalCurrentInputScaling[eAdcInternal3VPower_VoltageMonitor].fSlope = fCurrentInterceptScaleConstant[ eAdcInternal3VPower_VoltageMonitor ];

	xLocalCurrentInputScaling[eAdcInternalPowerCurrentMonitor].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternalPowerCurrentMonitor ];
	xLocalCurrentInputScaling[eAdcInternalPowerCurrentMonitor].fSlope = fCurrentInterceptScaleConstant[ eAdcInternalPowerCurrentMonitor ];
	
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH1].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH1 ];
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH1].fSlope = fCurrentInterceptScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH1 ];
	
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH2].fIntercept = fCurrentInterceptScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH2 ];
	xLocalCurrentInputScaling[eAdcInternalCanPwrCurrentMonitorCH2].fSlope = fCurrentInterceptScaleConstant[ eAdcInternalCanPwrCurrentMonitorCH2 ];
		
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

/*--------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensorUpdate(void)
{
	/*  FIX IDEAS

	* offset given as a parameter to this function 
	* LNA high, LNA low, Booster high, Booster low given as params
	* Common alarm: check 6 values that are within the CAN against global variable limits : would be a lot of parameters to consider
	
	* reporting back alarms: within LNA
		- pxAlarmRegister->bLnaCurrentLimitAlarmStatus set to 1 if high OR low is triggered
		- pMpbAlarmsAndStatusRegisterBitAssignment->bLnaCurrentHighAlarmStatus set to 1 if HIGH is triggered
	* HPA
		- pxAlarmRegister->bBoosterCurrentLimitAlarmStatus set to 1 if high OR low is triggered (current 1)
		- pxAlarmRegister->bCurrentBoosterDriver2AlarmFlag set to 1 if high OR low is triggered (current 2)
		- pxAlarmRegister->bCurrentBoosterDriver3AlarmFlag set to 1 if high OR low is triggered (current 3)
		- return 1 in critical alarm if ANY of the three are triggered
	* Common
		- c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vVmCh1TooLow
		- c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError3vPwrVmTooLow
		- c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError7vPwrVmCh2tooLow
		- c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcErrorAdcPwrCmtooLow 
		- c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalAdcError28vCm_TooLow
		- c428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment.bInternalCAN_PwrError_TooLow 

		- each of these are set if various readings are below global variable limits
		- return 1 if any of them are flagged 
	*/


	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor();
	
	eMpbError_t eMpbError;
	uint16_t usOffset = 0;	

	eBool_t bLnaCurrentCriticalAlarm = eFalse;
	eBool_t bHpaCurrentAlarm = eFalse;
	eBool_t bInternalCurrentAlarm = eFalse;

	usOffset = 	pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw;
	
	/* read all the powers , one by one */
	for( uint8_t ucI = eAdcInternal28VPwrCurrentMonitorCH1; ucI< eNumberOfChannelConfigurations; ucI++ )
	{		
		eMpbError = eCurrentSensorsReadChannelRun( ucI, usOffset,  xLocalCurrentInputScaling[ucI], &fCurrentReadedInMa[ucI], &usCurrentRaw[ucI]);		
		if( eMpbError != eSuccess )
		{
			return eMpbError;
		}
	}

	AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister = 	&(pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment);		
	MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment = 	&(pxLaserBeamDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment);
	
	#ifdef DEMO_VERSION
	#else

	// NEED: get upper and lower limits from CAN

	eMpbError = eCurrentSensorsLnaAlarmRun( 1000 * fCurrentReadedInMa[eAdcExLnaSingleModeldCurrentMonitor],
								pMpbAlarmsAndStatusRegisterBitAssignment, 
								pxLaserBeamDescriptor->c409StatusDefinition, 
								pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent ,
								pxAlarmRegister, 
								&bLnaCurrentCriticalAlarm);
		
	if(eMpbError != eSuccess)
	{
		return eMpbError;
	}

	// NOT EDITED UNDER HERE
	if(bLnaCurrentCriticalAlarm == eTrue)
	{
		//vLnaAlarmProtocolDetected(); // trigger Lna alarm
	}

	// NEED: Get upper and lower limits from CAN
	eMpbError = eCurrentSensorsHpaAlarmRun( pxLaserBeamDescriptor->c409StatusDefinition,
								pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump1BoosterCurrent,
								pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent,
								pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent,
								pxAlarmRegister,
								&bHpaCurrentAlarm);

	if (eMpbError != eSuccess)
	{
		return eMpbError;
	}

	if(bHpaCurrentAlarm == eTrue)
	{
		// trigger Hpa alarm
	}
				
		
	eMpbError = eCurrentSensorsCommonAlarmRun( &(pxLaserBeamDescriptor->c423StatusDefinition), 
									&(pxLaserBeamDescriptor->c428StatusDefinition), 
									&bInternalCurrentAlarm );

	if (bInternalCurrentAlarm == eTrue)
	{
		// trigger both 
	}
		
	//pxAlarmRegister->bLnaCurrentLimitAlarmStatus = ( (bLowLimitAlarm==eTrue) || (bHighLimitAlarm==eTrue) )? 1:0;
	//	vLnaAlarmProtocolDetected();
		
	#endif
	
	return eMpbError;

}


/*--------------------------------------------------------------------------------*/
eMpbError_t eCurrentSensingGetCurrentValue(eCurrentChannelsScaling_t eChannel, float *fCurrentmA, uint16_t *usCurrentRaw)
{
	if (fCurrentmA == NULL || usCurrentRaw == NULL)
	{
		return eInvalidParameter;
	}

	if (eChannel < eAdcInternal28VPwrCurrentMonitorCH1 || eChannel >= eNumberOfChannelConfigurations)
	{
		return eInvalidParameter;
	}

	*fCurrentmA = fCurrentReadedInMa[eChannel];
	*usCurrentRaw = usCurrentRaw[eChannel];

	return eSuccess;

}

/*--------------------------------------------------------------------------------*/