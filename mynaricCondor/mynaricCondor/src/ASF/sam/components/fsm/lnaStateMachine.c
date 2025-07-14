/**
* @file 		lnaStateMachine.c
* @brief		lnaStateMachine.c source file
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
#include "lnaStateMachine.h"
#include "mainStateMachine.h"
#include "accControl.h"
#include "apcControlLaser.h"
#include "trajectoryCalculator.h"
#include "binaryInput.h"
#include "BSPAdc.h"
#include "BSPPwm.h"
#include "math.h"

//#include stdio.h
//#include <string.h>
/*#include "control.h"
#include "math.h"
#include "glue.h"
#include "projectDef.h"
#include "modulationStateMachine.h"
#include "BSPDac.h"
#include "va416xx_hal_timer.h"*/
/* Private define ----------------------------------------------------------- */
#define DEBUG_proto 1
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static int init_tmrDisable = 0;
static eBool_t bLnaIsReadyForReset = eFalse ; 
static void (*lnaStateTable[]) (void) =
{ 	
 eLnaLoopStateDisableFunction,
 eLnaLoopStateStandbyFunction,
 eLnaLoopStateApcFunction,
 eLnaLoopStateAccFunction,	
 eLnaLoopStateIdentificationFunction,	
};

static eLnaState_t eLnaState;

static uint16_t			usLastSetpoint ;
static uint16_t			usLastSetpointApc ;

/* Exported functions ------------------------------------------------------- */

void vLnaStateMachineInit( void )
{
	init_tmrDisable = 0;
	eLnaState 	= eLnaLoopStateDisable ;

}

void vLnaAlarmProtocolDetected( void )
{
	init_tmrDisable = 0;
	eLnaState 	= eLnaLoopStateDisable ;
	usLastSetpoint = 0;

}

void vLnaCriticalErrorDetected( void )
{
	eLnaState 	= eLnaLoopStateDisable ;
	
	vEnableLna( eFalse );
	vBSPPwmSetOutputDuty( eLNA_PWM_STP,  0);
	
	usLastSetpoint = 0;
}
/*------------------------------------------------------------------------------*/
void vLnaStateMachineUpdate(void)
{	
	#ifdef DEMO_VERSION 
	//	eLnaState = eLnaLoopStateidentification ;
	#endif
		//eLnaState = eLnaLoopStateidentification ;
	
	lnaStateTable[ eLnaState ] ();	
}
/*------------------------------------------------------------------------------*/
eLnaState_t eLnaReportState(void)
{
	return eLnaState;
}
/*------------------------------------------------------------------------------*/
void eLnaLoopStateDisableFunction(void)
{
//	eResetRequest_t										ucResetRequest ;
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	eBool_t	bLnaIsEnabled = eFalse;
	static eBool_t bDisableInit = eFalse;	
	
	//ucResetRequest			= pxLaserBeamDescriptor->c406PacketControlDefinition.ucResetRequest ;
	
	
	/*-----DisableLNAProtocol---*/
		
	/* 1) Use the ENABLE/DISABLE-LNA function to disable the LNA laser driver */
	//	vBinaryOtputSetState( eOutputLnaLddEna, eTrue );
		 vEnableLna(eFalse);
	//	 vEnableLna(eTrue);
		 vEnableLna(eFalse);
	//	 vBinaryClearLdEnable();
		 
		 vAccControlLaserUpdateLna( 0 );
	
	//bLnaIsEnabled = (pxLaserBeamDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 == 1)? eTrue : eFalse;
	//if(pxLaserBeamDescriptor->eMainLoopState == eMainLoopStateInit )
	if(bDisableInit == eFalse)
	{
	
		init_tmrDisable = 0;
		bDisableInit = eTrue ;
		//if( (ucResetRequest == RESET_LNA)  )
		//{
		//	init_tmrDisable = 0;
	//	}

	}
	else
	{
		
	 pxLaserBeamDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 = 0;
	/*3) If the LNA laser driver is effectively disabled, end the protocol.*/
		if(init_tmrDisable < INIT_TMO)
		{
			init_tmrDisable++;
		}
		else
		{
			init_tmrDisable = 0;
			bDisableInit = eFalse ;
		
		//bEnable1 = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;

		//if( eTrue == mpb_float1_minor_than_float2(  pxLaserBeamDescriptor->c414StatusDefinition.fLnaOpticalOutputPower, (X1_414_LNA_OPTICAL_OUTPUT_POWER + 1 ),  0 )  )
			if( eTrue == mpb_float1_minor_than_float2(  (Y1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE + 10 ), pxLaserBeamDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent  ,  100 )  )
			{			
			/*  2) Check the enabled status of LNA laser driver with the REPORTEnable function */
			pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = eFalse;	
			eLnaState =  eLnaLoopStateStandby;
			}
			else
			{
				pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = eTrue;	
			//eMainLoopState = eMainLoopStateShutDown;
			
		//	#if DEBUG_proto == 1
		//	eLnaState =  eLnaLoopStateDisable;
			//#else
			//vSetResetState();
				vSetAlarmIsDetected();
			
			//#endif
			}
			bLnaIsReadyForReset = eTrue;
		}
		
	}
}
/*------------------------------------------------------------------------------*/
void eLnaLoopStateStandbyFunction(void)
{
	eResetRequest_t			ucResetRequest ;
	eBool_t bEnable1 = eFalse;
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor();
	
	bLnaIsReadyForReset = eFalse;
	
	ucResetRequest			= pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest ;
	
	
	
	bEnable1 = (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 == 1)? eTrue : eFalse;
	//vBinaryOtputSetState( eOutputLnaLddEna, bEnable1 );
	vEnableLna(bEnable1);
	
	
	if(bEnable1 == eTrue)
	{
		if( (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode ==  1 ) )			
		{
			//eLnaState =  eLnaLoopStateApc ;		 temporally diasble for the tests TVAC
			pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode = 1 ;
		}
		else
		{
			eLnaState =  eLnaLoopStateAcc ;	
			pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode = 0 ;
		}

	
		pxAmplifierDescriptor->xFinalSetpoints.fLnaApc = -15.0; //dbm
	}
	
//	bEnable1
//	pxLaserBeamDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = eFalse;
	
	/*
	
	If  the LNA optical output is going lower than the LNA LOW alarm limit in the REPORTPhotodiodes function, raise the LNA output alarm flag in the REPORTPhotodiodes function.
	// done outside 
	
	SET LNA related operational parameters

	1) Use the SETCurrentLimits function to set the high and low alarm limits for all the LNA laser driver current
	//done outside

	2) Use the SETChannel function to set the LNA ITU wavelength channel
	//done ouside

	3) Use the SETPhotodiodeLimits function to set the high and low alarm limits for the LNA optical input
	//done outside

	4) Use the SETPhotodiodeLimits function to set the high and low alarm limits for the LNA optical output
	//done outside

	5) Use the SETCurrentLNA function to set the LNA laser driver current
	// done in acc fsm

	6) Use the SET-LNAPowerAPC function to set the LNA APC optical power setpoint back to the minimum value -15 dBm.
	

*/

	
			
	if( (ucResetRequest == RESET_LNA) || (ucResetRequest == RESET_ALL) )
	{
		vSetDisableLna(eTrue);
//		pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
	}
	
}
/*------------------------------------------------------------------------------*/
void eLnaLoopStateApcFunction(void)
{
	uint16_t				usSetpointInPourcent = 0;
	float					fSetpointInDbm = 0.0f;
	eBool_t					bIsInApc = 0;
	static float			fsetPointInMiliWatts = 0.0f;
	static uint16_t			usSetPointInPourcentage = 0;
	float					fsetPointInMiliWatts2 = 0.0f;
	float					fActualOutputPowerInMiliWatts = 0.0f;
	float					fInitialError = 0.0f;
	float					fCurrentControlLnaSm1 = 0.0f;
	eResetRequest_t			ucResetRequest ;

	xAmplifierDescriptor_t *pxAmplifierDescriptor;		
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	ucResetRequest			= pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest ;
	
	static int init_tmr_sht = 0;
	uint32_t uUsDelta = 50;
	
	usSetpointInPourcent			= pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA;
	usSetPointInPourcentage        = pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA;
	fActualOutputPowerInMiliWatts		= pxAmplifierDescriptor->xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1;
	
/*
	if( (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode ==  0 ) )
	{
		vSetDisableLna(eTrue);
	}
	else
	{*/
			
		//fsetPointInMiliWatts = 0.000578768*usSetPointInPourcentage + 0.003162;	
		//lna output power = 77.3 mW
		//  (x1,y1) 0,0    (x2,y2) 1023,77.3mw)  y= 0.076x
		//fsetPointInMiliWatts = 0.076*usSetPointInPourcentage ;	
		
		// (x1,y1) (0, 0.1 ) corresponding to 0,-10            (x2,y2)  1023,1    y ? 0.001x + 0.1
		
		fsetPointInMiliWatts = 0.001*usSetPointInPourcentage + 0.1 ;	
		
		
		fSetpointInDbm				=  10 * log10( fsetPointInMiliWatts );
		pxAmplifierDescriptor->xPowersIndBM.fLnaSetpointInApcIndbm = fSetpointInDbm;
		
	
		vApcControlLaserUpdate(  uUsDelta, fsetPointInMiliWatts, fActualOutputPowerInMiliWatts , &fCurrentControlLnaSm1);	
	
//	}
	
	if( (ucResetRequest == RESET_LNA) || (ucResetRequest == RESET_ALL) )
	{
		//vSetDisableLna(eTrue);
		vLnaStateMachineInit();
		pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
		//	eLnaState =  eLnaLoopStateDisable ;
			
	}
		
	usLastSetpointApc = usSetpointInPourcent;
	

}
/*------------------------------------------------------------------------------*/
void eLnaLoopStateAccFunction(void)
{
	eResetRequest_t			ucResetRequest ;
	xAmplifierDescriptor_t *pxAmplifierDescriptor;
	uint16_t				usSetpointInMa = 0;
	uint16_t				usSetpointInPwm = 0;
	//static uint16_t			usLastSetpoint = 0;
	static uint16_t			usCurrentRead = 0;
	uint16_t				usDeltaRange = 0;
	static uint16_t			usStepsNumber = 0;
	static eBool_t			bIncrease = eFalse;
	eBool_t					bWavelengthIs1536 = eFalse; 
	static uint16_t			usSetpointInmA = 0;
	//static	uint16_t		usOutputCurrentInMa = 0;
	eBool_t					bIsInAcc = 0;
	eBool_t bEnableLna = eFalse;
		
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );			
	ucResetRequest			= pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest ;
		
	bEnableLna = (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 == 1)? eTrue : eFalse;
	if( bEnableLna == eFalse)
	{
		pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = 0;
		vLnaStateMachineInit();
		
	}
	else
	{
		pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = 1;	
	}
	
	
	if( (pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode ==  1 ) )
	{
			//vSetDisableLna(eTrue);
		vLnaStateMachineInit();
			
	}
	else
	{
		if( bEnableLna == eFalse)
		{
			usSetpointInPwm = 0;
			vLnaStateMachineInit();
			//	usLastSetpoint = 0;
		}
		else
		{
			usSetpointInPwm			= pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA;	
		}
		
		bWavelengthIs1536		= ( pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetRxChannelOnLna == 1 )? eTrue : eFalse ;
	
	//todo : check safe in the sp in current
		
		if(usLastSetpoint != usSetpointInPwm)
		{		
				//bIsInAcc				= (pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode == 0)? eTrue : eFalse; 
				usCurrentRead			= pxAmplifierDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent;	
				ePwmToCurrentConversion( bWavelengthIs1536, usSetpointInPwm, &usSetpointInmA );		
				vTrajectoryCalculatorRun( eTrue, usSetpointInmA, usCurrentRead,  &usStepsNumber, &bIncrease);
		}
			
		if ( usStepsNumber > 0  )
		{
			if(bIncrease == eTrue)
			{
					if( (usSetpointInmA-usCurrentRead) <  CURRENT_INCREASE_BY_STEP_IN_MA)
					{
						usCurrentRead = usCurrentRead + (usSetpointInmA-usCurrentRead) ;		
					}
					else
					{
						usCurrentRead = usCurrentRead + CURRENT_INCREASE_BY_STEP_IN_MA;		
					}
					
			}
			else
			{
					if( (usCurrentRead-usSetpointInmA) <  CURRENT_INCREASE_BY_STEP_IN_MA)
					{
					//	usCurrentRead = usCurrentRead - (usCurrentRead-usSetpointInmA);
						usCurrentRead = usSetpointInmA;
					}
					else
					{
						usCurrentRead = usCurrentRead - CURRENT_INCREASE_BY_STEP_IN_MA;
					}
					
			}
		
			
				usStepsNumber--;
				if(usStepsNumber == 0)	
				{
					usCurrentRead = usSetpointInmA;
				}
				vAccControlLaserUpdateLna( usCurrentRead );
				
		}
		
		
	}
	
	if( (ucResetRequest == RESET_LNA) || (ucResetRequest == RESET_ALL) )
	{
		vLnaStateMachineInit();
		usSetpointInPwm = 0;
//		pxAmplifierDescriptor->c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
	}
		
		usLastSetpoint = usSetpointInPwm;
	
	/*The LNA laser driver current can be changed with the SETCurrentLNA function while the LNA laser driver is enabled with the ENABLE/DISABLE-LNA function.

	Enabling/Disabling the laser driver:

	The LNA laser driver may be enabled and disabled any number of times.
	Disabling the laser driver is allowed at any time without conditions.
	Enabling the laser driver with the ENABLE/DISABLE-LNA function can only be executed when the LNA laser driver set current of the REPORTCurrents function is within the high and low alarm limit current range of the LNA laser driver as reported in the REPORTCurrents function.
*/
	
/*	//bInitMemoryImageFromNvm();
	if ( eFalse == bInitMemoryImageFromNvm() )
	{
		vLaserBeamsFactoryDefaultValues();
	}
		
	vCopyImageNvm();
	
	
		
	if(ucResetRequest == RESET_LNA)
	{
		vLaserInitLna();
	}
	else if(ucResetRequest == RESET_BOOSTER)
	{
		vLaserInitBooster();
	}
	else if(ucResetRequest == RESET_ALL)
	{
		vLaserDataInit();
	}
	//eMainLoopState =  eMainLoopStateTest;
	if( (pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump1OnBoosterInAcc > 0 ) || 
	    (pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump2OnBoosterInAcc > 0 ) || 
		(pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump3OnBoosterInAcc > 0 ) ||
		(pxAmplifierDescriptor->c406PacketControlDefinition.fSetSetPointPowerForBoosterInApc > 0 ) ) 
	{
		eMainLoopState =  eMainLoopStateDisableBooster ;	
	}
	else if()
	{
		eMainLoopState =  eMainLoopStateDisableLna ;	
	}
	*/
}


void vSetDisableLna( eBool_t bSetdisable)
{
	if( bSetdisable == eTrue )
	{
		eLnaState =  eLnaLoopStateDisable ;
		usLastSetpoint = 0;	
	}
	
		//bDisableInit = eFalse ;
}
/*------------------------------------------------------------------------------*/
eBool_t bIsLnaReadyForReset( void)
{
	
	return bLnaIsReadyForReset;
}

void vLnaReadyForReset( void)
{
	
	bLnaIsReadyForReset = eTrue;
}
/*------------------------------------------------------------------------------*/
void eLnaLoopStateIdentificationFunction(void)
{
	xAmplifierDescriptor_t *pxAmplifierDescriptor;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	//static uint16_t usLnaPwm =0;
	float fActualOutputPowerInMiliWatts = 0.0f;

	static int init_tmr_sht = 0;
//	uint32_t uUsDelta = 100;
//	static uint16_t usCurrentRead = 0;
	
	eMpbError_t eMpbError;
	//static uint8_t ucCounter = 0;
	//static eBool_t bGo = eFalse;
	
	static uint32_t ucHpaMmPwmStp2 =0;
	static uint32_t ucHpaMmPwmStp1 =0;
	static uint32_t ucHpaSmPwmStp2 =0;
	static uint32_t ucLnaSmPwmStp =0;
	
	
	static eBool_t bLnaLddEna = eTrue;
	static eBool_t bLnaLddEnaCopy = eTrue;
	static eBool_t bHpaSmLddEna = eTrue;
	static eBool_t bHpaMmLddEna1 = eTrue;

	static eBool_t bHpaMmLddEna2 = eTrue;
	
	//	vBinaryOtputSetState( eOutputLnaLddEna, eFalse );  //eFalse
//		vBinaryOtputSetState( eOutputHpaSmLddEna, eTrue );
	//	vBinaryOtputSetState( eOutputHpaMmLddEna1, eTrue );
	//	vBinaryOtputSetState( eOutputHpaMmLddEna2, eTrue )
	
	//usLnaPwm = (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA;
	
	
	//vBinaryOtputSetState( eOutputLnaLddEna, eFalse );
	
	/*
		bLnaLddEna = (eBool_t)pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;
		if( bLnaLddEnaCopy != bLnaLddEna)
		{
			if(bLnaLddEna == eTrue)
			{
			
				bLnaLddEna = eTrue ;
					vBinarySetLdEnable( eTrue  );
			}
			else
			{
				vBinarySetLdEnable( eFalse  );
			}
		}
		*/
		
		bHpaSmLddEna = (eBool_t)pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1;
		vBinaryOtputSetState( eOutputHpaSmLddEna, !bHpaSmLddEna );
		
		bHpaMmLddEna1 = (eBool_t)pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2;
		vBinaryOtputSetState( eOutputHpaMmLddEna1, bHpaMmLddEna1 );
		
		bHpaMmLddEna2 = (eBool_t)pxAmplifierDescriptor->c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3;
		vBinaryOtputSetState( eOutputHpaMmLddEna2, bHpaMmLddEna2 );
	
	
	
	ucHpaSmPwmStp2 = 4 * (uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump1OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_SM_PWM_STP1,  ucHpaSmPwmStp2);
	
	
	ucHpaMmPwmStp1 = 4 *(uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump2OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP1,  ucHpaMmPwmStp1);
	
	
	ucHpaMmPwmStp2 = 4 *(uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetCurrentOnLaserPump3OnBoosterInAcc ;
	
	vBSPPwmSetOutputDuty( eHPA_MM_PWM_STP2,  ucHpaMmPwmStp2);
	
//	ucLnaSmPwmStp = 4 *(uint32_t)pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA;

//	vBSPPwmSetOutputDuty( eLNA_PWM_STP,  ucLnaSmPwmStp);
	

	
//		vBinaryOtputSetState( eOutput3vPwrEna1, eTrue );
//		vBinaryOtputSetState( eOutput3vPwrEna1, eFalse );
//		vBinaryOtputSetState( eOutput3vPwrEna1, eTrue );
		
		
		
//vBinaryOtputSetState( eOutput3vPwrEna2, eTrue );
//vBinaryOtputSetState( eOutput3vPwrEna2, eFalse );
//vBinaryOtputSetState( eOutput3vPwrEna2, eTrue );
//	vAccControlLaserUpdate( usCurrentRead );
	

	
		  							//  1		2			3		4		5		 6		7		8			9		10
 /*	static uint16_t usInputData[130] = { 80,	84,			88,		102,	106,	110,	114,	118,		122,	126,
										130,	134,		138,	142,	146,	150,	154,	158,		162,	166,
										170,	174,		178,	182,	186,	190,    194,	198,		202,	206,
										210,	214,	    218,	222,	226,	230,	234,	238,		242,	246,
										250,	254,		260,    264,    270,    274,    278,	282,		286,	290,
								        294,	298,		302,	306,	310,	314,	318,	322,		326,	330,
										334,	338,		342,	346,	350,	354,	358,	362,		366,	370,
										374, 	378,		382,	386,	390,	394,    398,	402,		406,	410,
										414,	418,	    422,	426,	430,	434,	438,    442,		446,    450,
										454,	458,	    462,    466,    470,    474,    478,	482,	    486,	490,
										494,	498,        502,    506,    510,    514,    518,    522,        526,     528,
										532,    536,        540,    544,    548,    552,    556,    560,        562,    566,
										570,    574,        578,    580,    584,    584,    584,    584,        584,    584   
									};*/

		  			/*					//  1		2			3		4		5		 6		7		8			9		10
		static uint16_t usInputData[130] = { 580,	576,		572,	568,	564,	560,	556,	552,		548,	542,
			  								538,	534,		530,	526,	522,	518,	514,	510,		504,	500,
			  								496,	492,		488,	484,	480,	476,    472,	468,		464,	460,
			  								456,	452,	    448,	444,	440,	436,	432,	428,		424,	420,
			  								416,	412,		408,    404,    400,    396,    392,	388,		384,	380,
			  								376,	372,		368,	364,	360,	356,	352,	348,		344,	340,
			  								350,	360,		370,	380,	390,	400,	420,	440,		460,	480,
			  								460, 	450,		440,	430,	420,	410,    400,	390,		380,	370,
			  								366,	362,	    358,	354,	350,	346,	342,    338,		334,    330,
			  								326,	322,	    318,    314,    310,    306,    302,	288,	    284,	280,
			  								276,	272,        268,    264,    262,    258,    254,    250,        246,    242,
			  								220,    210,        200,    196,    192,    188,    184,    180,        176,    170,
			  								166,    162,        158,    142,    136,    120,    114,    108,        90,    80
		  								};*/
										  																			  
	/*  data 2. 1/2 inpuit power 
									//  1		2			3		4		5		 6		7		8			9		10
  	static uint16_t usInputData[100] = { 430,	440,		450,	460,	470,	480,	490,	500,		510,	520,
										530,	540,		550,	560,	570,	580,	590,	600,		590,	580,
										570,	560,		550,	540,	550,	560,    570,	560,		550,	540,
										530,	520,	    510,	500,	490,	480,	470,	460,		450,	440,
										430,	420,		410,    400,    390,    380,    370,	360,		370,	360,
								        350,	340,		330,	320,	310,	300,	290,	280,		270,	260,
										250,	240,		230,	220,	210,	200,	190,	180,		170,	160,
										150, 	140,		130,	120,	110,	100,    90,		80,			90,		100,
										110,	120,	    130,	140,	150,	160,	170,    180,		190,    200,
										210,	220,	    230,    240,    250,    260,    270,	280,	    290,	300
										  };*/
	
	/* 50 static uint16_t usInputData[100] = { 0,		50,			100,	150	,	200,	250,	300,	350,		400,	450,
										500,	500,		450,	400,	400,	400,	350,	350,		350,	300,
										300,	300,		300,	250,	250,	250,    250,	250,		200,	200,
										200,	250,	    250,	250,	200,	200,	200,	200,		200,	250,
										200,	250,		250,    250,    250,    300,    300,	300,		350,	350,
										350,	300,		300,	350,	350,	350,	350,	300,		350,	300,
										350,	350,		300,	300,	350,	350,	300,	300,		250,	250,
										250, 	250,		200,	250,	200,	250,    200,	150,		150,	150,
										200,	200,	    200,	250,	200,	150,	150,    150,		100,    150,
										100,	150,	    100,    150,    200,    250,    200,	150,	    100,	180
											};*/
		
/*	static float fPowerOutputData1[130];
	static float fCurrentData1[130];
	static float fCurrentData2[130];
	
	static float fTemperatureData1[130];
	static float fTemperatureData2[130];
	static float fTemperatureData3[1300];
	static float fTemperatureData4[130];
	
	uint16_t   ucPwmStp_1 = 0;
	
	uint16_t   ucPwmStp_2 = 1023;*/
	
		/* io */
		
//	vBinaryOtputSetState( eOutputLnaLddEna, eTrue );  //eFalse
//	vBinaryOtputSetState( eOutputHpaSmLddEna, eTrue );
//	vBinaryOtputSetState( eOutputHpaMmLddEna1, eTrue );
//	vBinaryOtputSetState( eOutputHpaMmLddEna2, eTrue );
		
		
	//vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
	//vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
		//fActualOutputPowerInMiliWatts		= pxAmplifierDescriptor->xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1;
		
//	if (bGo == eTrue)
//	{	
		
	/* LNA experiment */
	//if(ucCounter < 130)
	//{
		/*vBinaryOtputSetState( eOutputLnaLddEna, eFalse );
		usCurrentRead = usInputData[ ucCounter ];
		//vBSPPwmSetOutputDuty( eLNA_PWM_STP,  ucPwmStp_1);
		vAccControlLaserUpdateLna( usCurrentRead );
		fPowerOutputData1[ucCounter ] = pxAmplifierDescriptor->xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1;
		fCurrentData1[ucCounter ] = pxAmplifierDescriptor->c401StatusDefinition.fLaserPump4LnaCurrent ;
		fTemperatureData1[ucCounter ] = pxAmplifierDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorLnaSmLd ;
		*/
		/* HPA experiment 
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
					*/
	//}
	
	
	
	
	bLnaLddEnaCopy = bLnaLddEna;

	

	
	

		
	
	//ucCounter++;
	
	//	if( ucCounter >= 130)
	//	{
	//		ucPwmStp_1 = 0;
	//	}

//	}
	


}

	
	