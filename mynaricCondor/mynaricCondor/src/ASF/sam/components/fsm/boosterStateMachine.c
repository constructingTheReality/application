/**
* @file 		boosterStateMachine.c
* @brief		boosterStateMachine.c source file
* @author		juan andres
* @date			Created on 2023-07-12
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "boosterStateMachine.h"
#include "mainStateMachine.h"
#include "accControl.h"
#include "apcControlLaser.h"
#include "binaryInput.h"
#include "boosterAccSm.h"
#include "boosterApcStateMachineGetData.h"
#include "BSPAdc.h"
#include "BSPPwm.h"
#include "trajectoryCalculator.h"
#include "enableControl.h"
#include "boosterApcStateMachineGetData.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
typedef enum
{
	eDisableSM1 = 0,
	eDisableMM1 = 1,
	eDisableMM2 = 2,
	eDisableDone = 3	
}eDisableState_t;


/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

static void (*boosterStateTable[]) (void) =
{ 	
 eBoosterLoopStateDisableFunction,
 eBoosterLoopStateStandbyFunction,
 eBoosterLoopStateApcFunction,
 eBoosterLoopStateAccFunction	
};

static	eBoosterState_t eBoosterState;

static eBool_t bLastEnableSmHpa1 = eFalse;
static eBool_t bLastEnableHpa1 = eFalse;
static eBool_t bLastEnableHpa2 = eFalse;

static eDisableState_t eDisableState ;

static uint16_t			usLastSetpointHpa1 ;
static uint16_t			usLastSetpointMmHpa1 ;
static uint16_t			usLastSetpointMmHpa2 ;
static eBool_t			bControlM1M2IsRising = eFalse;

static float			fLastSetPointInDbm = 0;
static eBool_t			bPrivateHpaIsReadyForReset = eFalse ; 


/* Exported functions ------------------------------------------------------- */
void vHpaCriticalErrorDetected( void )
{
	/*
	   Important notes for a calibrated device with a configured LOS:
	   (a)   If at any time the input signal is lost (i.e., input signal below the LOS SET threshold), both MMLD drivers should turn OFF (or reset each driver current) as fast as possible,
	   and then SM LD driver should turn OFF (or reset the driver current) as well.
	   (b)   If at any time the back-facet power is less than the threshold power,
	   both MMLD drivers should turn OFF (or reset each driver current) as fast as possible.
	   
	   */
	vBoosterAccEnableOnMm2( eFalse );
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP2,  0);
	vBoosterAccEnableOnMm1( eFalse );
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  0);
	
	///add delay here
	
	vBoosterAccEnableOnSm1( eFalse);
	vBSPPwmSetOutputDuty( eHPA_SM_PWM_STP1,  0);
	
	//eBoosterState 	= eBoosterLoopStateDisable ;
		
	vSetDisableHpa();
		
}
/*------------------------------------------------------------------------------*/
void vHpaDisableSequence( void )
{
	static uint16_t usCount = 0;

	/* here is the sequence for shutdown the lasers. 
	   The stuck conditions is read in other part and generate the stuck alarm */

	/*To power off the HPA, the following sequence must be applied:
	(1) Switch the MM pumps off (HPA_MM_LDD_ENA1: LOW and HPA_MM_LDD_ENA2:LOW) 
	    Reset the MM pumps current to 0-mA (or minimum current setting) 
	    This action is a two-step operation.
	NOTE: The HPA_MM_LDD_ENA1&2 hardware line does not affect the HPA SM pump(s) current.
		   Wait for a minimum period of 5 ms and reduce (HPA_MM_PWM_STP1&2) the MM pump(s) current to 0 mA (or to minimum current that can be set). 
		   Again, this action can be done in one step operation.
		   
   (2)  Switch the single mode pump off (HPA_LDD_nENA: HIGH) and reset the single mode pump current (HPA_PWM_STP1) to 0-mA (or minimum current setting) This action is a two-step operation.
   (3)  Turn OFF the input signal.
	*/
	
	if( eDisableState == eDisableMM2)
	{
		usCount++;
		vBoosterAccEnableOnMm2( eFalse );
			//ePwmCurrentOutputAnalogWriteDuty( eHandlePwmMmStp2, 0 );
		if( usCount > NUMBER_OF_CONTROL_LOOPS)			
		{
			vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP2,  0);
			eDisableState = eDisableMM1;
			usCount = 0;	
		}
		
		
		/*if( (usCount > 10) || (cPumpMm2StatusDefinition.fLaserPumpMm2BoosterCurrent < 100) )
		{
			eDisableState = eDisableMM1;	
			usCount = 0;
		}*/
		
		
	}else if( eDisableState == eDisableMM1)
	{
		vBoosterAccEnableOnMm1( eFalse );
		usCount++;
		//ePwmCurrentOutputAnalogWriteDuty( eHandlePwmMmStp1, 0 );
		if( usCount > NUMBER_OF_CONTROL_LOOPS)
		{		
			vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  0);
			eDisableState = eDisableMM2;
			usCount = 0;
		}
		
			
		
		eDisableState = eDisableSM1;
	}
	else if( eDisableState == eDisableSM1)
	{
		vBoosterAccEnableOnSm1( eFalse);
		//ePwmCurrentOutputAnalogWriteDuty( eHandlePwmLnaStp, 0 );
		usCount++;
		if( usCount > NUMBER_OF_CONTROL_LOOPS)
		{
			vBSPPwmSetOutputDuty( eHPA_SM_PWM_STP1,  0);
			eDisableState = eDisableDone;
			usCount = 0;
		}
		
		
	}
	//TODO
	//1. transition to critical error
	// 
	
	//vHpaApcStateMachineInit(); ?
	
	eBoosterState 	= eBoosterLoopStateDisable ;	
}
/*------------------------------------------------------------------------------*/
void vBoosterStateMachineInit( void )
{
	eBoosterState 	= eBoosterLoopStateDisable ;
	vHpaApcStateMachineInit();
}
/*------------------------------------------------------------------------------*/
void vBoosterStateMachineUpdate(void)
{	
	boosterStateTable[ eBoosterState ] ();	
}
/*------------------------------------------------------------------------------*/
eBoosterState_t eBoosterReportState(void)
{
	return eBoosterState;
}
/*------------------------------------------------------------------------------*/
eHpaApcState_t eBoosterApcReportState(void)
{
	eHpaApcState_t eHpaApcState;
	eHpaApcState = xReportHpaApcState();
	return eHpaApcState;
}
/*------------------------------------------------------------------------------*/
void vSetDisableHpa( void)
{
	eBoosterState =  eBoosterLoopStateDisable ;
	eBoosterState = eHpaApcInit;
	fLastSetPointInDbm = 0;
}
/*------------------------------------------------------------------------------*/
void vResetHpaAlarms( void)
{
	eBoosterApcStateGetDataResetHpaAlarms();
}
/*------------------------------------------------------------------------------*/
eBool_t bBoosterGetStuckCondition(void)
{
	eBool_t bStuckDetected = eFalse;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
					   	 
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	
	bStuckDetected = cPumpSm1StatusDefinition.bCriticalStuckDetected;
					   
	return bStuckDetected;
}
/*------------------------------------------------------------------------------*/
eBool_t bIsHpaReadyForReset(void)
{
	
	return bPrivateHpaIsReadyForReset;
	
}
/*------------------------------------------------------------------------------*/
void vHpaReadyForReset(void)
{
	
	bPrivateHpaIsReadyForReset =eTrue;
	
}
/*------------------------------------------------------------------------------*/
void eBoosterLoopStateDisableFunction(void)
{
	eResetRequest_t			eResetRequest ;
	eBool_t bConditionsToResetBooster = eFalse;
	eBool_t bConditionsToResetLna = eFalse;
	
	/* this function will shutdown all the diodes in the correct sequence*/
	vHpaDisableSequence();
	
	/*  the enable/disable functions will be manage inside the FSm for ACC and APC.
		this is done in order to follow a safe shutdown sequence and turn on sequence.
	
		the stuck condition leads to a critical error. this situation is monitored in other place.
	*/
	eBoosterApcStateGetDataGetResetRequest(&eResetRequest, &bConditionsToResetBooster, &bConditionsToResetLna);
	
	/* when the shutdown is finish, move to standby */
	if( eDisableState == eDisableDone)
	{
		eDisableState = eDisableMM2;
		
		if(bConditionsToResetBooster == eFalse)
		{
			eBoosterState =  eBoosterLoopStateStandby;	
		}
		
		bPrivateHpaIsReadyForReset = eTrue;		
	}
}
/*------------------------------------------------------------------------------*/
void eBoosterLoopStateStandbyFunction(void)
{
	eResetRequest_t			eResetRequest ;
	eBool_t bConditionsToResetBooster = eFalse;
	eBool_t bConditionsToResetLna = eFalse;
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
	xBoosterPowers_t xBoosterPowers;

	eBoosterApcStateGetDataGetResetRequest(&eResetRequest, &bConditionsToResetBooster, &bConditionsToResetLna);
	eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers, &bEnable1Booster, &bEnable2Booster, &bEnable3Booster);
	
		
	if( xBoosterPowers.bHpaInAccmode == eTrue )
	{
		eBoosterState =  eBoosterLoopStateAcc ;			
	}
	else
	{
		if( (bEnable1Booster == eTrue) && ((bEnable2Booster==eTrue)||(bEnable3Booster==eTrue))  )
		{
			eBoosterState =  eBoosterLoopStateApc ;			
		}
	}
	bPrivateHpaIsReadyForReset = eFalse;				
	
	

	if( bConditionsToResetBooster == eTrue )
	{
		eBoosterState 	= eBoosterLoopStateDisable ;	
	}
}
/*------------------------------------------------------------------------------*/
void eBoosterLoopStateApcFunction(void)
{
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
		
	eResetRequest_t eResetRequest;
	static float			fControlCurrentSm1 = 0;
	eBool_t					bDisable = eFalse;
	eBool_t					bEnableChange = eFalse;
	float					fCurrentControlHpaMm2 = 0.0f;
	float					fCurrentControlHpaMm1 = 0.0f;
	
	 xBoosterCurrents_t xBoosterCurrents;
	 xBoosterPowers_t xBoosterPowers;
	 eBool_t bSetpointEqual = eFalse;
	 
	 eBool_t bConditionsToResetBooster = eFalse;
	 eBool_t bConditionsToResetLna = eFalse;
	 
	 cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	 cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	 cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
	 	
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
	eBoosterApcStateGetDataGetHpaActualConditionsOnPumps( &xBoosterCurrents);	
	eBoosterApcStateGetDataGetResetRequest(&eResetRequest, &bConditionsToResetBooster, &bConditionsToResetLna);
	//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);
	eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
	
//	cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1  =  (cPumpSm1StatusDefinition.cPumpSm1StatusFlags.ulPumpSm1Value == 0x01)? eTrue:eFalse ; //xBoosterEnablePumps.bEnableHpa1 && (xBoosterStuckAlarmValues.bSm1IsStucked == eFalse) && ( xBoosterAlarmValues.bSm1OverHeat == eFalse ) && ( xBoosterAlarmValues.bSm1UnderHeat == eFalse ) ;
//	cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1  =  (cPumpMm1StatusDefinition.cPumpMm1StatusFlags.ulPumpMm1Value == 0x01)? eTrue:eFalse ; //xBoosterEnablePumps.bEnableMMHpa1 && (xBoosterStuckAlarmValues.bMm1IsStucked == eFalse) && ( xBoosterAlarmValues.bMm1OverHeat == eFalse ) && ( xBoosterAlarmValues.bMm1UnderHeat == eFalse );
//	cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2  =  (cPumpMm2StatusDefinition.cPumpMm2StatusFlags.ulPumpMm2Value == 0x01)? eTrue:eFalse ; //xBoosterEnablePumps.bEnableMMHpa2 && (xBoosterStuckAlarmValues.bMm2IsStucked == eFalse) && ( xBoosterAlarmValues.bMm2OverHeat == eFalse ) && ( xBoosterAlarmValues.bMm2UnderHeat == eFalse );		
	
	//fsetPointInMiliWatts				= pow(10, xBoosterCurrents.fValueConverted  ) ;

	/* possible conditions to force a disable on apc. normal conditions. not alarms? */
	bDisable = (eBool_t)(cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1);
	
	bDisable = ( //( cPumpSm1StatusDefinition.bCriticalStuckDetected == eTrue ) || 
				 ( xBoosterPowers.bHpaInAccmode == eTrue ) ||
				 ( bDisable == eFalse )					   ||								
				 ( bConditionsToResetBooster == eTrue     )								 )? eTrue : eFalse ;
		
	if( bDisable == eTrue)
	{
		vHpaDisableSequence();		
		vHpaApcStateMachineInit();		
	//	eBoosterApcStateGetDataSetResetRequest( DO_NOTHING);
	//	eBoosterState 	= eBoosterLoopStateDisable ;		
	}
		
	/* manage for the enable / disable inputs */
	bEnableChange = ( 
				//	(((eBool_t)(cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1)) != bLastEnableSmHpa1 )  || 
					(((eBool_t)(cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2)) != bLastEnableHpa2) || 
					(((eBool_t)(cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1)) != bLastEnableHpa1 ) );
	
	if(	 bEnableChange == eTrue     )
	{
			vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
			vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
			vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );
			bControlM1M2IsRising = eTrue;
			fLastSetPointInDbm = 0 ; 
			vHpaApcStateMachineInit(); 			
	}
		
	/* for each new trayectory, reset all the pid instances */	
	bSetpointEqual =  mpb_float1_equal_to_float2(fLastSetPointInDbm, xBoosterPowers.fSetPointInDbm, 100);
	
	if( bSetpointEqual == eFalse  )/* || (fLastInputPower != fActualInputPowerInDbm)*/
	{
		vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
		vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );	
		vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );
		bControlM1M2IsRising = ( eTrue == mpb_float1_minor_than_float2( fLastSetPointInDbm , xBoosterPowers.fSetPointInDbm, 100    ))? eTrue : eFalse ;			
	}
	
	
	vHpaApcStateMachineUpdate();
	
	fLastSetPointInDbm = xBoosterPowers.fSetPointInDbm;
	//fLastInputPower = fActualInputPowerInDbm;
	bLastEnableHpa2 = cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2;
	bLastEnableHpa1 = cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1;
	bLastEnableSmHpa1 = cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1;
	
	eBoosterApcStateGetDatasetControlcurrents( fControlCurrentSm1,  fCurrentControlHpaMm1,  fCurrentControlHpaMm2 );
	
}
/*------------------------------------------------------------------------------*/
void eBoosterLoopStateAccFunction(void)
{
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;	
	
	eBool_t					bWavelengthIs1536 = eFalse;

	uint16_t				usSetpointInPwmHpa1 =0;
	uint16_t				usSetpointInPwmMmHpa1 =0;
	uint16_t				usSetpointInPwmMmHpa2 =0;
	static uint16_t			usSetpointInmAHpa1 = 0;
	static uint16_t			usSetpointInmAMmHpa1 = 0;
	static uint16_t			usSetpointInmAMmHpa2 = 0;

	static uint16_t			usStepsNumberHpa1 = 0;
	static uint16_t			usStepsNumberMmHpa1 = 0;
	static uint16_t			usStepsNumberMmHpa2 = 0;
	
	static eBool_t			bIncreaseHpa1 = eFalse;
	static eBool_t			bIncreaseMmHpa1 = eFalse;
	static eBool_t			bIncreaseMmHpa2 = eFalse;
	eBool_t					bHpaReadyForSecondStep = eFalse;
	float					fNominalCurrentSm1 = 0.0f;
	xBoosterPowers_t		xBoosterPowers;
	
	uint16_t	usMaxHpaCurrentSM_mA				= 0;
	uint16_t	usNominalCurrentPourcentage_sM		= 0;

		
	eResetRequest_t eResetRequest;
	eBool_t bConditionsToResetBooster = eFalse;
	eBool_t bConditionsToResetLna = eFalse;
	eBool_t bEnable = eFalse;
	
	
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
	
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
	
//	fCurrentHpaSm1			= cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent;
	
	eBoosterApcStateGetDataHpaSmParameters( &usMaxHpaCurrentSM_mA,  &usNominalCurrentPourcentage_sM);
	
	/* calculate nominal operating value for the SM - this is the min. value before pass to the next stage */
	fNominalCurrentSm1		= ( usMaxHpaCurrentSM_mA ) * ( usNominalCurrentPourcentage_sM ) / 100;

	eBoosterApcStateGetDataGetResetRequest( &eResetRequest,	 &bConditionsToResetBooster , &bConditionsToResetLna );
	
	if( bConditionsToResetBooster == eTrue )
	{
		eBoosterState 	= eBoosterLoopStateDisable ;
	
	}
	
	/* if we change from acc to apc */	
	//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);
	eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
	

	
	if( xBoosterPowers.bHpaInAccmode == eFalse )
	{		
		vHpaDisableSequence();
	}	
	else
	{
		usSetpointInPwmHpa1 = (cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 1)? cPumpSm1StatusDefinition.usLaserPump1AccSetpoint : 0;
		bWavelengthIs1536		= cPumpSm1StatusDefinition.bSm1WavelengthIs1536;
		bEnable				= (eBool_t)(cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1);
		
		
		vBoosterAccManager( eSM ,	usLastSetpointHpa1	,	cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent, bEnable,
							usSetpointInPwmHpa1		,	&usSetpointInmAHpa1		, eTrue,
							&usStepsNumberHpa1		,	&bIncreaseHpa1			, bWavelengthIs1536, eTrue);
		
		/*-------------------------------------------------------------------------------------------*/
		/*  hpa mm1 */	
		usSetpointInPwmMmHpa1 = (cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 1)?  cPumpMm1StatusDefinition.usLaserPumpMm1AccSetpoint : 0;	
		bEnable				= (eBool_t)(cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1);	
		
		
		bHpaReadyForSecondStep = (cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent > fNominalCurrentSm1 )? eTrue : eFalse;  //pxBoosterParameters->xHpaPowersConfig.fHpaMinOutPowerForNextSteps
		bHpaReadyForSecondStep = eTrue;
		
		
		vBoosterAccManager( eMM1 ,	usLastSetpointMmHpa1	,	cPumpMm1StatusDefinition.fLaserPumpMm1BoosterCurrent, bEnable,
							usSetpointInPwmMmHpa1		,	&usSetpointInmAMmHpa1		, eFalse,
							&usStepsNumberMmHpa1		,	&bIncreaseMmHpa1			, bWavelengthIs1536, bHpaReadyForSecondStep);
				
			
		/*-------------------------------------------------------------------------------------------*/		
		/*  hpa mm2 */
		usSetpointInPwmMmHpa2 = (cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 1)? cPumpMm2StatusDefinition.usLaserPumpMm2AccSetpoint : 0;	
		bEnable				= (eBool_t)(cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2);
		
		vBoosterAccManager( eMM2 ,	usLastSetpointMmHpa2	,	cPumpMm2StatusDefinition.fLaserPumpMm2BoosterCurrent, bEnable,
							usSetpointInPwmMmHpa2		,	&usSetpointInmAMmHpa2		, eFalse,
							&usStepsNumberMmHpa2		,	&bIncreaseMmHpa2			, bWavelengthIs1536, bHpaReadyForSecondStep);
		
		
		
		usLastSetpointHpa1 = usSetpointInPwmHpa1;
		
		
		if(bHpaReadyForSecondStep == eTrue ) 
		{
			usLastSetpointMmHpa1 = usSetpointInPwmMmHpa1;
			usLastSetpointMmHpa2 = usSetpointInPwmMmHpa2;
		}
	
		
	
		
	}
		

}
/*------------------------------------------------------------------------------*/
