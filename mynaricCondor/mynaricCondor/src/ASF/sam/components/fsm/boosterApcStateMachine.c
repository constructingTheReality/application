/**
* @file 		boosterApcStateMachine.c
* @brief		boosterApcStateMachine.c source file
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
#include "boosterApcStateMachine.h"
#include "boosterApcStateMachineGetData.h"
#include "controlLaserPID.h"
#include "accControl.h"
#include "dictionaryUtils.h"
#include "boosterAccSm.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static	eHpaApcState_t eBoosterApcState;
static float			fControlCurrentSm1 = 0;
static float			fCurrentHpaSm1 = 0.0f;
static float			fCurrentHpaMm1 = 0.0f;
static float			fCurrentHpaMm2 = 0.0f;
static float			fCurrentHpaMm1Mm2 = 0.0f;

static eBool_t			bLastEnableSmHpa1 = eFalse;
static eBool_t			bLastEnableHpa1 = eFalse;
static eBool_t			bLastEnableHpa2 = eFalse;
static float fLastSetPointInDbm = 0.0f;

static eBool_t			bControlM1M2IsRising = eFalse;


static void (*boosterApcStateTable[]) (void) =
{
	eHpaApcStateInitFunction,
	eHpaApcStateSmFunction,
	eHpaApcStateMm1_InitFunction,
	eHpaApcStateMm1_ControlFunction,
	eHpaApcStateMm2_InitFunction,
	eHpaApcStateMm2_ControlFunction,
	eHpaApcStateMm1Mm2_InitFunction,
	eHpaApcStateMm1Mm2_ControlFunction
};
/*------------------------------------------------------------------------------*/

void vHpaApcStateMachineInit( void )
{
	eBoosterApcState	= eHpaApcInit;	
}
/*------------------------------------------------------------------------------*/
void vHpaApcStateMachineUpdate(void)
{		
		cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
		cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
		cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
		eBool_t bEnable1Booster = eFalse;
		eBool_t bEnable2Booster = eFalse;
		eBool_t bEnable3Booster = eFalse;
		eBool_t bSetpointEqual = eFalse;
		xBoosterPowers_t xBoosterPowers;
		
		eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
		eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
		eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
		
	/* manage for the enable / disable inputs */
	if(	 ((eBool_t)(cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1) != bLastEnableHpa1)  ||
		 ((eBool_t)(cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2) != bLastEnableHpa2) ||
		 ((eBool_t)(cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 != bLastEnableSmHpa1 ) )  )
	{
		vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
		vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
		vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );
		bControlM1M2IsRising = eTrue;
		fLastSetPointInDbm = 0 ; 
		eBoosterApcState = eHpaApcInit;
	}
	
	eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
	
	bSetpointEqual =  mpb_float1_equal_to_float2(fLastSetPointInDbm, xBoosterPowers.fSetPointInDbm, 100);
	
	/* for each new trayectory, reset all the pid instances */
	if(bSetpointEqual == eFalse)
	{
		vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
		vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
		vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );
		bControlM1M2IsRising = ( eTrue == mpb_float1_minor_than_float2( fLastSetPointInDbm , xBoosterPowers.fSetPointInDbm, 100    ))? eTrue : eFalse ;
	}
	
	/* send hpa state to db */
	//vSetHpaDataBase(eBoosterApcState);
	boosterApcStateTable[ eBoosterApcState ] ();	
	
	
	bLastEnableHpa2 = (eBool_t)(cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2);
	bLastEnableHpa1 = (eBool_t)(cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1);
	bLastEnableSmHpa1 = (eBool_t)(cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1);
	
	fLastSetPointInDbm = xBoosterPowers.fSetPointInDbm;
	
}
/*------------------------------------------------------------------------------*/
eHpaApcState_t xReportHpaApcState(void)
{
	return eBoosterApcState;
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateInitFunction(void)
{
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
	/*assure that clear mm1, sm1, and mm2*/
		vAccControlLaserUpdateHpaMm1( 0 );
		vAccControlLaserUpdateHpaMm2( 0 );
		vAccControlLaserUpdateHpaSm1( 0 );
		
		//xBoosterCurrents_t xBoosterCurrents;
		xBoosterPowers_t xBoosterPowers;
		cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
		cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
		cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
		
		eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
		eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
		eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
		//eBoosterApcStateGetDataGetHpaActualConditionsOnPumps( &xBoosterCurrents);	
		//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);	
		eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
		
		if( ( xBoosterPowers.fSetPointInDbm >= MIN_SETPOINT_FOR_APC_BOOSTER_IN_DBM ) &&
			 (cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 1 ) )
		{
			vBoosterAccEnableOnSm1( eTrue );
			eBoosterApcState = eHpaApcSm;	
		}
		
//		if( (bDisable == eTrue) && (bDisableProtcolIsDone == eTrue) )
//		{
			/* shutdown when alarm is fnished. now ready to re-try */			
//			bDetectingDisableCondition = eTrue; 
//			eBoosterState 	= eBoosterLoopStateStandby ;
			//eHpaApcState	= eHpaApcInit;
			//pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
//		}	
		
		/*if( (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetBoosterControlMode ==  0 ) )
		{		
			vSetDisableHpa();
		}	*/ 
	//eBoosterApcState =  eHpaApcSm;
	
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateSmFunction(void)
{
	uint16_t	usMaxHpaCurrentSM_mA				= 0;
	uint16_t	usNominalCurrentPourcentage_sM		= 0;
	float		fNominalCurrentOfSm1				= 0;
	
	/*assure that clear mm1 and mm2 */
	vAccControlLaserUpdateHpaMm1( 0 );
	vAccControlLaserUpdateHpaMm2( 0 );
		
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
			
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
				
	fCurrentHpaSm1			= cPumpSm1StatusDefinition.fLaserPump1BoosterCurrent;  
		
	eBoosterApcStateGetDataHpaSmParameters( &usMaxHpaCurrentSM_mA,  &usNominalCurrentPourcentage_sM);	
		
	/* calculate nominal operating value for the SM - this is the min. value before pass to the next stage */
	fNominalCurrentOfSm1		= ( usMaxHpaCurrentSM_mA ) * ( usNominalCurrentPourcentage_sM ) / 100;
		
	/* if the disable order is received, then ramp down */
	if( cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 )  
	{ /* ramp down */
		fControlCurrentSm1 = fCurrentHpaSm1 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC;
					
//		if(fCurrentHpaSm1 < CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE)
		if( mpb_float1_minor_than_float2(fCurrentHpaSm1 ,CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE, 100) )
		{
			fControlCurrentSm1 = 0;
			vBoosterAccEnableOnSm1( eFalse);
			eBoosterApcState = eHpaApcInit;
		}
		/* send current to SM pump */	
		vAccControlLaserUpdateHpaSm1( fControlCurrentSm1 );			
	}
	else
	{ /* ramp up */ 
		vBoosterAccEnableOnSm1( eTrue );
		
		fControlCurrentSm1 = fCurrentHpaSm1 + CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC;
			
		if(eTrue == mpb_float1_minor_than_float2(   fNominalCurrentOfSm1 , fControlCurrentSm1  , 100 ) )
		{
			fControlCurrentSm1 = fNominalCurrentOfSm1;
			/* the next transition is for the case, the MM1 be damaged, then use only the MM2 */	
			if( cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 1)
			{
				eBoosterApcState = eHpaApcMm1_Init;	
			}
			else if( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 1 )
			{
				eBoosterApcState = eHpaApcMm2_Init;
			}	
			else
			{
							// ADDED //
				eBoosterApcState = eHpaApcInit;

			}			
		}			
		vAccControlLaserUpdateHpaSm1( fControlCurrentSm1 );						
	}		
	
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateMm1_InitFunction(void)
{
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
		
	float fCurrentControlHpaMm1 = 0.0f;
	
	/*assure that clear mm2*/
	vAccControlLaserUpdateHpaMm2( 0 );
	
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
	xBoosterCurrents_t xBoosterCurrents;
	xBoosterPowers_t xBoosterPowers;
			
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
	//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);	
	eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
	
	eBoosterApcStateGetDataGetHpaActualConditionsOnPumps( &xBoosterCurrents);
	
	fCurrentHpaMm1			= cPumpMm1StatusDefinition.fLaserPumpMm1BoosterCurrent; 
			
		
	if(  ( cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 0) ||
	     ( cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 ))   
	{/* ramp down */
		fCurrentControlHpaMm1 = fCurrentHpaMm1 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC;
			
		//if(fCurrentControlHpaMm1 < CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE)
		if(mpb_float1_minor_than_float2(fCurrentControlHpaMm1 , CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE,100) )
		{
			fCurrentControlHpaMm1 = 0;			
			vBoosterAccEnableOnMm1( eFalse );	
			eBoosterApcState = eHpaApcSm	;									
		}
		vAccControlLaserUpdateHpaMm1( fCurrentControlHpaMm1 );	
	}
	else
	{
		vBoosterAccEnableOnMm1( eTrue );
		eBoosterApcState =  eHpaApcMm1_Control;	
		vControlLaserPIDReset( eHpaLaserMultiMode1PowerLoopPID );
	}
	/*else if( eTrue == mpb_float1_minor_than_float2( xBoosterPowers.fActualOutputPowerInMiliWatts, 
													xBoosterPowers.fSetPointInMiliWatts, 100   ) )
	{			
		eBoosterApcState = eHpaApcMm1_Control;				
	}*/
	
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateMm1_ControlFunction(void)
{	
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
			
	float fCurrentControlHpaMm1 = 0.0f;
	uint16_t usMaxHpaCurrentStageMM1_mA;
	uint16_t usMaxHpaCurrentMM1_mA;
	xBoosterPowers_t xBoosterPowers;
		
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
		
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
		
	eBoosterApcStateGetDataHpaMm1Parameters( &usMaxHpaCurrentStageMM1_mA,  &usMaxHpaCurrentMM1_mA);		
		
	fCurrentHpaMm1			= cPumpMm1StatusDefinition.fLaserPumpMm1BoosterCurrent; 
	
		if(		( cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 0) || 
				( cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 ) //||   //TODO: check conditions
			//	( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 0  ) //&& (bLastEnableHpa2 == eFalse) ) // this last codition ?
		  )
		{
			eBoosterApcState = eHpaApcMm1_Init;
		}		
		else if( ( bControlM1M2IsRising == eTrue ) &&   		
				 (cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 1 ) &&
				 (eTrue == mpb_float1_minor_than_float2( usMaxHpaCurrentStageMM1_mA , fCurrentHpaMm1  , 100 ) ) 				 
			   )
		{		/* if we reach the current threshold for mm1 and should pass to MM2 */
				vAccControlLaserUpdateHpaMm1( usMaxHpaCurrentStageMM1_mA  );
				eBoosterApcState = eHpaApcMm2_Init;				
		}
		else
		{
			/*runing normal APC -pid- with MM1  */			
			//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);			
			eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
			eBoosterApcStateGetDataUpdateControlMm1( xBoosterPowers, &fCurrentControlHpaMm1 )   ;
		}
	
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateMm2_InitFunction(void)
{	
		float fCurrentControlHpaMm2 = 0.0f;
		cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
		cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
		cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
			
		eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
		eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
		eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
		
		

		if( ( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 0)  || 
		    ( cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 ) ) 
		{
			fCurrentControlHpaMm2 = fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC;
			
			if(fCurrentControlHpaMm2 < CURRENT_ENOUGH_LOW_TO_SHUTDOWN_THE_DIODE)
			{
				fCurrentControlHpaMm2 = 0;
				vBoosterAccEnableOnMm2( eFalse );
				eBoosterApcState = eHpaApcMm1_Control	;  
			}
			vAccControlLaserUpdateHpaMm2( fCurrentControlHpaMm2 );
		}
		else 
		{
			eBoosterApcState = eHpaApcMm2_Control;
			vBoosterAccEnableOnMm2( eTrue );
			vControlLaserPIDReset( eHpaLaserMultiMode2PowerLoopPID );
		}
}

/*------------------------------------------------------------------------------*/
void eHpaApcStateMm2_ControlFunction(void)
{
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
		
	uint16_t usMaxHpaCurrentStageMM2_mA;
	uint16_t usMaxHpaCurrentMM2_mA;
	float	fCurrentControlHpaMm2 = 0.0f;
	xBoosterPowers_t xBoosterPowers;
	eBool_t bReadyToPassToStageMM1And2 = eFalse;
	eBool_t bReaydToPassToStageMM1 = eFalse;
	
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
		
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;

	eBoosterApcStateGetDataHpaMm2Parameters( &usMaxHpaCurrentStageMM2_mA,  &usMaxHpaCurrentMM2_mA);
	fCurrentHpaMm2			= cPumpMm2StatusDefinition.fLaserPumpMm2BoosterCurrent; 
		if( cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == eTrue ) 
		{
			bReadyToPassToStageMM1And2 = ( bControlM1M2IsRising == eTrue ) &&  //go up normal, with mm1 and mm2 enabled
										( eTrue == mpb_float1_minor_than_float2(   usMaxHpaCurrentStageMM2_mA , fCurrentHpaMm2  , 100 )   );
						  		
			bReaydToPassToStageMM1 = ( bControlM1M2IsRising == eFalse ) &&
									 ( eTrue == mpb_float1_minor_than_float2( fCurrentHpaMm2, 700, 100    ) );  
						     //TODO min current AT 0 PWM
		}
		
		if( ( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 0   )  ||
			( cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 ) )
		{
			eBoosterApcState = eHpaApcMm2_Init;
		}					
		else if(  bReadyToPassToStageMM1And2 == eTrue )  
		{
			vAccControlLaserUpdateHpaMm2( usMaxHpaCurrentStageMM2_mA  );		
			eBoosterApcState = eHpaApcMm1Mm2_Init;
			vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );	
		}
		/*go down	with mm1 and mm2 enabled	*/ 
		else if( bReaydToPassToStageMM1 == eTrue )
		{
			fCurrentControlHpaMm2 = 0;
			eBoosterApcState = eHpaApcMm1_Control;
			vAccControlLaserUpdateHpaMm2( fCurrentControlHpaMm2 );
			vControlLaserPIDReset( eHpaLaserMultiMode1PowerLoopPID );								
		}	
		else
		{
			//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);
			eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
			eBoosterApcStateGetDataUpdateControlMm2( xBoosterPowers, &fCurrentControlHpaMm2 );
		}		
			
	//eBoosterApcState =  eHpaApcMm1Mm2_Init;
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateMm1Mm2_InitFunction(void)
{
	uint16_t usMaxHpaCurrentStageMM2_mA;
	uint16_t usMaxHpaCurrentMM2_mA;
			
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
		
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
		
	eBoosterApcStateGetDataHpaMm2Parameters( &usMaxHpaCurrentStageMM2_mA,  &usMaxHpaCurrentMM2_mA);
	fCurrentHpaMm2			= cPumpMm2StatusDefinition.fLaserPumpMm2BoosterCurrent; 
	
	if( ( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 0) ||
	    ( cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 0) || 
		( cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 ) )  //( bDisable == eTrue) ||
	{
		fCurrentHpaMm1Mm2 = fCurrentHpaMm2 - CURRENT_INCREASE_BY_STEP_IN_MA_HPA1_APC;
		//if(fCurrentHpaMm1Mm2 < usMaxHpaCurrentStageMM2_mA)
		if ( mpb_float1_minor_than_float2(fCurrentHpaMm1Mm2, usMaxHpaCurrentStageMM2_mA, 100))
		{
			fCurrentHpaMm1Mm2 = usMaxHpaCurrentStageMM2_mA;
			eBoosterApcState = eHpaApcMm2_Init;
		}
		vAccControlLaserUpdateHpaMm1( fCurrentHpaMm1Mm2 );
		vAccControlLaserUpdateHpaMm2( fCurrentHpaMm1Mm2 );
	}
	else
	{
		vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );
		eBoosterApcState =  eHpaApcMm1Mm2_Control;
	}
	
}
/*------------------------------------------------------------------------------*/
void eHpaApcStateMm1Mm2_ControlFunction(void)
{
	eBool_t bEnable1Booster = eFalse;
	eBool_t bEnable2Booster = eFalse;
	eBool_t bEnable3Booster = eFalse;
		
	uint16_t usMaxHpaCurrentStageMM2_mA;
	uint16_t usMaxHpaCurrentMM2_mA;
		
	xBoosterPowers_t xBoosterPowers;
	float fCurrentControlHpaMm2;
		//float fCurrentControlHpaMm1;
		
	cPumpMm2StatusDefinition_t cPumpMm2StatusDefinition;
	cPumpMm1StatusDefinition_t cPumpMm1StatusDefinition;
	cPumpSm1StatusDefinition_t cPumpSm1StatusDefinition;
		
	eBoosterApcStateGetDataGetConditionsOnPumpSm1( &cPumpSm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm1(  &cPumpMm1StatusDefinition)	;
	eBoosterApcStateGetDataGetConditionsOnPumpMm2(  &cPumpMm2StatusDefinition)	;
	fCurrentHpaMm2			= cPumpMm2StatusDefinition.fLaserPumpMm2BoosterCurrent; 
		
		if( (cPumpSm1StatusDefinition.cPumpSm1StatusFlags.PumpSm1BitAssignment.bEnableHpa1 == 0 )  ||
			(cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 0)		||
			( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 0 )
		  )
		{
			eBoosterApcState =  eHpaApcMm1_Init;							
		}
		
		/*
		if( cPumpMm1StatusDefinition.cPumpMm1StatusFlags.PumpMm1BitAssignment.bEnableMMHpa1 == 0)
		{
			eBoosterApcState =  eHpaApcMm1_Init;
		}
		
		if( cPumpMm2StatusDefinition.cPumpMm2StatusFlags.Pump2BitAssignment.bEnableMMHpa2 == 0 )
		{
			eBoosterApcState =  eHpaApcMm2_Init;
		}*/
		
			
		if( bControlM1M2IsRising == eFalse ) 
		{			
			eBoosterApcStateGetDataHpaMm2Parameters( &usMaxHpaCurrentStageMM2_mA,  &usMaxHpaCurrentMM2_mA);
			//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);		
			eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );
				
			if( eTrue == mpb_float1_minor_than_float2( fCurrentHpaMm2 , usMaxHpaCurrentStageMM2_mA, 100    ) )
			{
				vControlLaserPIDReset( eHpaLaserMultM1and2PowerLoopPID );
				vAccControlLaserUpdateHpaMm1( usMaxHpaCurrentStageMM2_mA );
				vAccControlLaserUpdateHpaMm2( usMaxHpaCurrentStageMM2_mA );
				fCurrentControlHpaMm2  = (float)(usMaxHpaCurrentStageMM2_mA) ;
					
				eBoosterApcState =  eHpaApcMm2_Control;	
				fLastSetPointInDbm = xBoosterPowers.fSetPointInDbm;
				return;
			}	
		}
	
		
		//eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers);
		eBoosterApcStateGetDataPowersAndOperationMode( &xBoosterPowers , &bEnable1Booster, &bEnable2Booster, &bEnable3Booster );						
		eBoosterApcStateGetDataUpdateControlMm1AndMm2( xBoosterPowers, &fCurrentControlHpaMm2 );
		

}
/*------------------------------------------------------------------------------*/
