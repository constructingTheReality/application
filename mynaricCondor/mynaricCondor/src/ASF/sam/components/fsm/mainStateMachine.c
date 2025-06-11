/**
* @file 		mainStateMachine.c
* @brief		mainStateMachine.c source file
* @author		juan andres
* @date			Created on 2023-07-12
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
#include "mainStateMachine.h"
#include "lnaStateMachine.h"
#include "boosterStateMachine.h"
#include "controlLaserPID.h"
#include "binaryInput.h"
#include "BSPAdc.h"
#include "BSPPwm.h"
#include "mainStateMachineGetData.h"
#include "initMemory.h"

/* Private define ----------------------------------------------------------- */
#define MODULANT_LOOP_CONTROL_IN_MS ( 2 )
#define MAX_FREQUENCY_ACCEPTABLE_980 ( 10000 ) //7
#define DEF_TET_SETPOINT					( 4000 )
#define DAC_940												( 0 )
#define DAC_980												( 1 )
#define INIT_TMO1								( 100 )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

static void (*stateTable[]) (void) = { 
	eMainLoopStateStartupFunction,
	eMainLoopStateShutDownFunction,
	eMainLoopStateInitFunction,
	eMainLoopStateResetFunction,
	eMainLoopStateCriticalErrorFunction
	//eMainLoopStateTestFunction,
	//eMainLoopStateIdentificationFunction  
};

static eMainLoopState_t eMainLoopState;

/* Exported functions ------------------------------------------------------- */

void vMainStateMachineInit( void )
{
	eMainLoopState 	= eMainLoopStateStartup ;
//	vLnaStateMachineInit();
	vBoosterStateMachineInit();
}
/*------------------------------------------------------------------------------*/
void vMainStateMachineUpdate(void)
{	
	eResetRequest_t										ucResetRequest ;	
	//eBool_t bIsEnableLna = eFalse;
	uint8_t ucLnaState = 0;
	uint8_t ucHpaState = 0;
	uint8_t ucApcHpaState = 0;
	eLnaState_t eLnaState = eLnaLoopStateDisable;
	eBoosterState_t eBoosterState = eBoosterLoopStateDisable;
	eHpaApcState_t eHpaApcState = eHpaApcInit;
	
	ucResetRequest										= eGetActualResetCommand();
	//eGetLnaEnableStatus( &bIsEnableLna);			
	//vSetDisableLna(!bIsEnableLna);
		
	/*if( ( ucResetRequest == RESET_LNA) && ( eTrue == bIsLnaReadyForReset()) )
	{
		vLnaStateMachineInit();
		if( eTrue == bInitLnaMemoryImageFromNvm() )
		{
			vCopyImageLnaNvm();
		}
		else
		{
			vCurrentSensorsFactoryInitLnaChannels();
			vCopyImageLnaNvm();
		}
		vLaserInitLna();
		vClearResetMessage();
	}*/
	
	/*if(ucResetRequest == RESET_BOOSTER)
	{
		
		vResetHpaAlarms();
		
		if( eTrue == bInitBoostMemoryImageFromNvm() )
		{
			vCopyImageBoosterNvm();
		}
		else
		{
			vCurrentSensorsFactoryInitBoosterChannels();
			vCopyImageBoosterNvm();
		}
		vLaserInitBooster();
		vBoosterStateMachineInit(  );
		vClearResetMessage();
	}*/
	/*
	if( ucResetRequest == RESET_ALL) 
	{
		if( eTrue == bIsLnaReadyForReset() )
		{	
			vLnaStateMachineInit();
			if(eTrue == bInitCommonMemoryImageFromNvm() )
			{
				vCopyImageCommonNvm();
			}
	
		
			if( eTrue == bInitLnaMemoryImageFromNvm() )
			{
				vCopyImageLnaNvm();
			}
			else
			{
				vCurrentSensorsFactoryInitLnaChannels();
				ePowerSensorsFactoryInitLnaChannels();
			//vLnaThermistorFactoryInitChannels();
				vLnaCurrentControlInit( );
				vSetLnaPidDefaultValues();
			
			}
		}
		
		//booster
		vResetHpaAlarms();
		vBoosterStateMachineInit();
		if( eTrue == bInitBoostMemoryImageFromNvm() )
		{
			vCopyImageBoosterNvm();
		}
		else
		{
			vCurrentSensorsFactoryInitBoosterChannels();
			ePowerSensorsFactoryInitBoosterChannels();
			//vBoosterThermistorFactoryInitChannels();
			vBoosterCurrentControlInit(  );
			vSetHpaPidDefaultValues();
			
		}
		
		vLaserDataInit();
		vCopyImageCommonNvm();
		vCopyImageLnaNvm();
		vCopyImageBoosterNvm();
		
		
		
		vClearResetMessage();
	}
	
	*/

	
	eLnaState = eLnaReportState();	
	eBoosterState = eBoosterReportState();
	eHpaApcState = eBoosterApcReportState();
	
	ucLnaState = (uint8_t)(eLnaState);
	ucHpaState = (uint8_t)(eBoosterState);
	ucApcHpaState = (uint8_t)(eHpaApcState);
	
	eUpdateFsmStates( 	ucLnaState, ucHpaState, ucApcHpaState, (uint8_t)(eMainLoopState));
			
	stateTable[ eMainLoopState ] ();	
	
		
	vLnaStateMachineUpdate();
	vBoosterStateMachineUpdate();
	
	//2. add funtion tu trigger critical alarm = bBoosterInternalCriticalErrorInPowerFlag || sm temp  || mm temp1&& mm temp2
	// once critical error detected shudown inmediatly, not here. should be in main.
	//check for all sources of internal critical error.
//	#ifdef DEMO_VERSION
	
//	#else
	/*if(pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag == 0 ) 
	{
		
			vBoosterStateMachineUpdate();	
		
	}
	else
	{
		
		
		
		vHpaCriticalErrorDetected();
		vBoosterStateMachineInit(  );
		
	}*/
	
//	#endif	
	
}
/*------------------------------------------------------------------------------*/
eMainLoopState_t eReportState(void)
{
	return eMainLoopState;
}
/*------------------------------------------------------------------------------*/
void vSetAlarmCurrentInLna(void)
{
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus  = 1 ;
	vLnaAlarmProtocolDetected();	
}

/*------------------------------------------------------------------------------*/
void vClearAlarmCurrentInLna(void)
{
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus = 0;
	
}
/*------------------------------------------------------------------------------*/
void vSetAlarmCriticalError(void)
{	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bUnitBaseTemperatureAlarmStatus = 1;		
	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag = 1;		
	
	vHpaCriticalErrorDetected();
	vLnaCriticalErrorDetected();
	
		
	/*if( eMainLoopState != eMainLoopStateStartup )
	{
		eMainLoopState = eMainLoopStateShutDown; 
	}*/
	eMainLoopState = eMainLoopStateShutDown; 
}
/*------------------------------------------------------------------------------*/
void vSetResetState(void)
{
	eMainLoopState = eMainLoopStateReset; 
	
}
/*------------------------------------------------------------------------------*/
void eMainLoopStateStartupFunction(void)
{
	//uint16_t usGlobalInternalAlarmValue = 0;
	eBool_t bUniTemperatureAlarm = eFalse;
	static int init_tmr = 0;	
	
	eMainStateMachineGetDataGetUnitTemperatureAlarm( &bUniTemperatureAlarm );
	
	init_tmr++;
	vLnaStateMachineInit();
	vBoosterStateMachineInit();
vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
	vBinaryOtputSetState( eOutputHpaMmLddEna1, eFalse );
	vBinaryOtputSetState( eOutputHpaMmLddEna2, eFalse );			
	vBinaryOtputSetState( eOutputHpaSmLddEna, eFalse );	
	vBinaryOtputSetState( eOutputLnaLddEna, eTrue );
	
	if(init_tmr > INIT_TMO)
	{
		if(  bUniTemperatureAlarm == eFalse)
		{		
			eMainLoopState = eMainLoopStateInit;
			eMainStateMachineGetDataSetResetFromStartup( eTrue);
			vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
			vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
			init_tmr = 0;
		}
		else
		{
			eMainLoopState = eMainLoopStateShutDown;
		}
	
	}
	
}
/*------------------------------------------------------------------------------*/
void eMainLoopStateInitFunction(void)
{
	eResetRequest_t										ucResetRequest ;
	MpbAlarmsAndStatusRegisterBitAssignment_t			MpbAlarmsAndStatusRegisterBitAssignment;	
	
	ucResetRequest										= eGetActualResetCommand();
	eMainStateMachineGetDataGetMpbAlarms( &MpbAlarmsAndStatusRegisterBitAssignment );	
			
	if(MpbAlarmsAndStatusRegisterBitAssignment.bResetFromStartupState == 1 )
	{
	//	MpbAlarmsAndStatusRegisterBitAssignment.bResetFromStartupState = 0;
		ucResetRequest = RESET_ALL ;
		vLnaReadyForReset();	
		vHpaReadyForReset();	
	}
	

	if( (ucResetRequest == RESET_ALL) &&
		( eTrue == bIsLnaReadyForReset() )  && 
		( eTrue == bIsHpaReadyForReset() ) )
	{
		vResetHpaAlarms();
		bInitCommonMemoryImageFromNvm();
		vCopyImageCommonNvm();
		
		vInitLnaRun();
		vInitHpaRun();		
		vLaserDataInit();
		
		if(MpbAlarmsAndStatusRegisterBitAssignment.bResetFromStartupState == 1 )
		{
			vClearResetFromStartupFlag();
		}	//MpbAlarmsAndStatusRegisterBitAssignment.bResetFromStartupState = 0;			}
		else
		{
			eMainLoopState = eMainLoopStateStartup;
		}
		vClearResetFromStartupFlag();

				
	}		
	else if( (ucResetRequest == RESET_LNA) && ( eTrue == bIsLnaReadyForReset() ) )
	{
		vInitLnaRun();
		vClearResetFromStartupFlag();
	}
	else if( (ucResetRequest == RESET_BOOSTER) && ( eTrue == bIsHpaReadyForReset() ) )
	{
		vResetHpaAlarms();
		vInitHpaRun();
		vClearResetFromStartupFlag();
	}
	
}
/*------------------------------------------------------------------------------*/
void eMainLoopStateResetFunction(void)
{
/*	eResetRequest_t			ucResetRequest ;

	ucResetRequest =	eGetActualResetCommand();
			
	if(ucResetRequest == RESET_LNA)
	{
		if ( bResetLna() )
		{
			vPreparingReset();		
			eMainLoopState = eMainLoopStateInit;
		}
		else
		{
			//eMainLoopState =  eMainLoopStateShutDown;
		}		
	}
	else if(ucResetRequest == RESET_BOOSTER)
	{
		if ( bResetBooster() )
		{
			vPreparingReset();	
			eMainLoopState = eMainLoopStateInit;
		}
		else
		{
			//eMainLoopState =  eMainLoopStateShutDown;
		}
			
	}
	else if(ucResetRequest == RESET_ALL)
	{
		if ( bResetLna() ) 
		{
			
				if ( bResetBooster() ) 
				{
					vPreparingReset();	
					eMainLoopState = eMainLoopStateInit;			
				}		
		}
		
		
	}else if(ucResetRequest == DO_NOTHING)
	{
		eMainLoopState = eMainLoopStateInit;	
	}	*/
	
}
/*------------------------------------------------------------------------------*/
void eMainLoopStateShutDownFunction(void)
{
	//eResetRequest_t										ucResetRequest ;
	//xAmplifierDescriptor_t								*pxAmplifierDescriptor;
		
	//pxAmplifierDescriptor 								= vGetxAmplifierDescriptor( );
	//ucResetRequest										= pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest ;
	eResetRequest_t			ucResetRequest ;
	ucResetRequest =	eGetActualResetCommand();	
		
		
	vHpaCriticalErrorDetected();
	vLnaCriticalErrorDetected();
			
	if(ucResetRequest==RESET_ALL)
	{		
		eMainLoopState =  eMainLoopStateStartup;
	}
	/*if(  (pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooHigh == 1)	 ||
		 (pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaOutputPowerIsTooLow == 1)     ||
		 (pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaInputPowerIsTooHigh == 1)	 )	
	{
		//vBinaryOtputSetState( eOutputLnaLddEna, eTrue );
		//pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserDriver1Status = 0;
		
		vEnableLna(eFalse);
		
	}*/
	
	/*
	
	if( (pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLOSAlarm == 1)	||
		(pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerIsTooHigh == 1)  ||
		(pxAmplifierDescriptor->c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bBoosterOutputPowerIsTooHigh == 1)  )
	{
			vBinaryOtputSetState( eOutputHpaSmLddEna, eTrue );
			vBinaryOtputSetState( eOutputHpaMmLddEna1, eTrue );
			vBinaryOtputSetState( eOutputHpaMmLddEna2, eTrue );
			pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = 0;
	}*/
	
	
	
/*
	if( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bUnitBaseTemperatureAlarmStatus == 1 )
	{
			vBinaryOtputSetState( eOutputHpaSmLddEna, eFalse );
			vBinaryOtputSetState( eOutputHpaMmLddEna1, eFalse );
			vBinaryOtputSetState( eOutputHpaMmLddEna2, eFalse );
			
			vBinaryOtputSetState( eOutputLnaLddEna, eFalse );
			
			init_tmr_sht++;
			if(init_tmr_sht > INIT_TMO)
			{
				if( eTrue == mpb_float1_minor_than_float2(  (X1_414_BOOSTER_OPTICAL_OUTPUT_POWER + 1 ),pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower, 10 )  )
				{
					
					eMainLoopState = eMainLoopStateInit;  //eMainLoopStateReset
				}
				init_tmr_sht = 0;
				
			}
	}
	else if(  ( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bUnitBaseTemperatureAlarmStatus == 1 ) ||
		 ( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus == 1 ) ||
		 ( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus == 1) )
	{
		vBinaryOtputSetState( eOutputLnaLddEna, eFalse );
		eMainLoopState = eMainLoopStateInit; //eMainLoopStateReset
	}
	else if(	( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus == 1 ) ||
				( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus == 1) )
	{
				vBinaryOtputSetState( eOutputHpaSmLddEna, eFalse );
				vBinaryOtputSetState( eOutputHpaMmLddEna1, eFalse );
				vBinaryOtputSetState( eOutputHpaMmLddEna2, eFalse );
				
				init_tmr_sht++;
				if(init_tmr_sht > INIT_TMO)
				{
					if( eTrue == mpb_float1_minor_than_float2(  (X1_414_BOOSTER_OPTICAL_OUTPUT_POWER + 1 ),pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower, 10 )  )
					{
					
						eMainLoopState = eMainLoopStateInit;  //eMainLoopStateReset
					}
					init_tmr_sht = 0;
					
				}
				
				
				
	}*/

}

/*------------------------------------------------------------------------------*/
void eMainLoopStateCriticalErrorFunction(void)
{
	
	//Critical Error protocol
	
//	xAmplifierDescriptor_t *pxAmplifierDescriptor;
//	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	
	//Raise the internal critical error flag in the REPORTStatusUnit function.	
	//pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag = 1;
	eMainLoopState =  eMainLoopStateShutDown;
	
}
/*void eMainLoopStateReadyFunction(void)
{

	eBool_t bResetFsm 			= eFalse;
	xLaserBeamDescriptor_t 	*pxLaserBeamDescriptor;
	pxLaserBeamDescriptor 	= vGetLaserBeams( );
	eOperationMode_t 						eOperationMode;
	eBeaconIdUsedActually_t 		xBeaconId;
	eBool_t bIsTestMode 				= eFalse;
	xBeaconId 									= pxLaserBeamDescriptor->xBeaconId;
	eOperationMode 							= pxLaserBeamDescriptor->eOperationMode[ xBeaconId - 1 ];
	pxLaserBeamDescriptor->xStatusRegister.StatusRegisterBitAssignment.bQfbIsInReadyState = eTrue;
	pxLaserBeamDescriptor->xStatusRegister.StatusRegisterBitAssignment.bQfbIsInOnState = eFalse;
	
	if( pxLaserBeamDescriptor->bSystemIsInTestMode == eTrue  )
	{
		v
	}
	else if( ( (pxLaserBeamDescriptor->xLaserOperationMode[ e980Beacon- 1].bLaserIsEnable == eTrue ) &&
	( pxLaserBeamDescriptor->xBeaconId == e980Beacon ) )		||
	((pxLaserBeamDescriptor->xLaserOperationMode[ e940Beacon- 1].bLaserIsEnable == eTrue ) &&
	( pxLaserBeamDescriptor->xBeaconId == e940Beacon ) )	)
	{
		eMainLoopState = eMainLoopStateOn ;
		pxLaserBeamDescriptor->xStatusRegister.StatusRegisterBitAssignment.bQfbIsInOnState = eTrue;
		pxLaserBeamDescriptor->xStatusRegister.StatusRegisterBitAssignment.bQfbIsInReadyState = eFalse;
	}
	else
	{
		eprvControlType( eOperationMode, bIsTestMode );
		
	}
	
	
	pxLaserBeamDescriptor->xStatusRegister.StatusRegisterBitAssignment.bQfbIsInOffState = eFalse;

	vprvOutputsUpdate( bResetFsm, eFalse , eFalse );
}*/
/*------------------------------------------------------------------------------*/
//void eMainLoopStateTestFunction(void)
//{
	//eMpbError_t eMpbError;
//	eBool_t bIsTestMode 				= eFalse;
	
//	xAmplifierDescriptor_t *pxAmplifierDescriptor;
//	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
//	eResetRequest_t			ucResetRequest;
//	uint32_t   ucLnaPwmStp = 0;
//	uint32_t   ucHpaSmPwmStp = 0;
//	uint32_t   ucHpaMmPwmStp1 = 0;
//	uint32_t   ucHpaMmPwmStp2 = 0;
	
	
	/*eBool_t bEnable1 = eFalse;
	eBool_t bEnable2 = eFalse;
	eBool_t bEnable3 = eFalse;
	eBool_t bEnable4 = eFalse;
	eBool_t bEnable5 = eFalse;
	eBool_t bEnable6 = eFalse;*/
	
	
//	ucLnaPwmStp = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA ;
	//ucLnaPwmStp = 2  * ucLnaPwmStp;
//	vBSPPwmSetOutputDuty( eLNA_PWM_STP,  ucLnaPwmStp);
	
/*	ucHpaSmPwmStp = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump1OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_SM_PWM_STP1,  ucHpaSmPwmStp);
	
	
	ucHpaMmPwmStp1 = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump2OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  ucHpaMmPwmStp1);
	
	
	ucHpaMmPwmStp2 = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump3OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP2,  ucHpaMmPwmStp2);*/
	
	
	
	/* io */
/*	bEnable1 = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;	
	bEnable2 = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1;
	bEnable3 = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2;
	bEnable4 = pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3;
	
	vBinaryOtputSetState( eOutputLnaLddEna, bEnable1 );
	vBinaryOtputSetState( eOutputHpaSmLddEna, bEnable2 );
	vBinaryOtputSetState( eOutputHpaMmLddEna1, bEnable3 );
	vBinaryOtputSetState( eOutputHpaMmLddEna2, bEnable4 );
	*/
/*	ucResetRequest = pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest;
	
	if( ucResetRequest == RESET_LNA)
	{
		vBinaryOtputSetState( eOutput28vPwrDis1, eTrue );
		vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
		eMainLoopState =  eMainLoopStateReset;
	}
	else if( ucResetRequest == RESET_BOOSTER)
	{
		vBinaryOtputSetState( eOutput28vPwrDis2, eTrue );
		vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
		eMainLoopState =  eMainLoopStateReset;
	}
	else if( ucResetRequest == RESET_ALL)
	{
		eMainLoopState =  eMainLoopStateReset;
		//vBinaryOtputSetState( eOutput28vPwrDis1, eTrue );
		//vBinaryOtputSetState( eOutput28vPwrDis2, eTrue );
	}else if( ucResetRequest == DO_NOTHING)
	{
		vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
		vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
	}*/
	//
	//vBinaryOtputSetState( eOutput28vPwrDis2, bEnable2 );


//}
/*------------------------------------------------------------------------------*/
//void eMainLoopStateIdentificationFunction(void)
//{
	//eMpbError_t eMpbError;
	//static uint8_t ucCounter = 0;
	
	//xAmplifierDescriptor_t *pxAmplifierDescriptor;
	//pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
									//  1		2			3		4		5		 6		7		8			9		10
  /*	static uint16_t usInputData[100] = {0,		1023,	 1023,		1023,	1023,	500,	200,	100,		100,	200,
										0,		0,			0,		1023,	0,		1023,	500,	700,		0,		900,
										0,		1023,		0,		1023,	0,		1023,   0,		1023,		0,		1023,
										500,	0,		  500,		0,		500,	 0,		600,    0,			700,	0,
										0,		0,		  0,        100,    300,    500,    700,	900,		1023,	0,
								        0,		1023,	 900,		800,	700,	500,	200,	100,		1023,	0,
										0,		100,     200,		1023,	560,	1023,	900,	1023,		800,	900,
										0,		1023,		0,		1023,	0,		1023,   0,		1023,		0,		1023,
										500,	0,		  500,		0,		500,	 0,		600,    0,			700,	0,
										0,		0,		  0,        100,    300,    500,    700,	900,		1023,	0
										  };*/
	/*
	static float fPowerOutputData1[100];
	static float fCurrentData1[100];
	static float fCurrentData2[100];*/
	
	/*static float fTemperatureData1[100];
	static float fTemperatureData2[100];
	static float fTemperatureData3[100];
	static float fTemperatureData4[100];*/
	
	//uint16_t   ucPwmStp_1 = 0;
	//uint16_t   ucPwmStp_2 = 1023;
	
		/* io 
		
	vBinaryOtputSetState( eOutputLnaLddEna, eTrue );
	vBinaryOtputSetState( eOutputHpaSmLddEna, eTrue );
	vBinaryOtputSetState( eOutputHpaMmLddEna1, eTrue );
	vBinaryOtputSetState( eOutputHpaMmLddEna2, eTrue );
		
		
	vBinaryOtputSetState( OUT_3V_PWR_ENA1_GPIOeOutput28vPwrDis1, eFalse );
	vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );*/
	
	/* LNA experiment 
	if(ucCounter < 100)
	{
		ucPwmStp_1 = usInputData[ ucCounter ];
		vBSPPwmSetOutputDuty( eLNA_PWM_STP,  ucPwmStp_1);
		fPowerOutputData1[ucCounter ] = pxAmplifierDescriptor->c414StatusDefinition.fLnaOpticalOutputPower;
		fCurrentData1[ucCounter ] = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent ;
		fTemperatureData1[ucCounter ] = pxAmplifierDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorLnaSmLd ;
		
		// HPA experiment 
		ucPwmStp_1 = usInputData[ ucCounter ];
		vBSPPwmSetOutputDuty( eHPA_SM_PWM_STP1,  ucPwmStp_2);
		vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  ucPwmStp_1);
		vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP2,  ucPwmStp_1);
		
		fPowerOutputData1[ucCounter ] = pxAmplifierDescriptor->c414StatusDefinition.fBoostOpticalOutputPower;
		fCurrentData1[ucCounter ] = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump2BoosterCurrent ;
		fCurrentData2[ucCounter ] = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump3BoosterCurrent ;
		
		fTemperatureData1[ucCounter ] = pxAmplifierDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd1 ;
		fTemperatureData2[ucCounter ] = pxAmplifierDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd2 ;
		fTemperatureData3[ucCounter ] = pxAmplifierDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd3 ;
		fTemperatureData4[ucCounter ] = pxAmplifierDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd4 ;
					
	}
	
	*/
	
	
	
	
	/*ucHpaSmPwmStp = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump1OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_SM_PWM_STP1,  ucHpaSmPwmStp);
	
	
	ucHpaMmPwmStp1 = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump2OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  ucHpaMmPwmStp1);
	
	
	ucHpaMmPwmStp2 = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump3OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP2,  ucHpaMmPwmStp2);*/
	
	
	

	
	
	//ucCounter++;

//}
/*--------------------------------------------------------*/
void vSetAlarmIsDetected(void)
{
	eMainLoopState =  eMainLoopStateCriticalError;		
}

eBool_t bMainFsmHpaGetStuckCondition(void)
{
	return bBoosterGetStuckCondition();
	
}