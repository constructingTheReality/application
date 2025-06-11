/**
* @file 		mpbLogEvent.c
* @brief		fmea and fta reporting utility.  
* @author		juan andres Castano
* @date			Created on 2022-08-18
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2022 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/

/* Includes ----------------------------------------------------------------- */
#include "mpbLogEvent.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static xLaserLogEventDescriptor_t xLaserLogEventDescriptor[ BUFFER_LOG_SIZE ];
static mpbSamplingTimeType_t 			pMpbSamplingTimeType;
static mpbEventTypeDetected_t 		xEventDetected ;
static uint8_t 										ucIndexCounting = 0;
static eBool_t 										bTestSampling = eFalse;
static eBool_t 										bFaultStateIsOn = eFalse;
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static void svSaveLogInformation(xAmplifierDescriptor_t *pxAmplifierDescriptor, uint8_t index, uint16_t  ucSampleNumber , uint32_t ucTimerCounter, mpbEventTypeBitsignment_t		mpbEventTypeBitsignment);
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

static void svSaveLogInformation(xAmplifierDescriptor_t *pxAmplifierDescriptor, uint8_t index, uint16_t  ucSampleNumber, uint32_t ucTimerCounter, mpbEventTypeBitsignment_t mpbEventTypeBitsignment )
{
		uint8_t ucBeaconId = 0;
	//	eMainLoopState_t eMainLoopState;
	
	typedef union
	{
		mpbFtaLowPowerBitAssignment_t		mpbFtaLowPowerBitAssignment;
		uint16_t mpbFtaLowPowerValue;		
	}mpbFtaLowPowerData_t;

	mpbFtaLowPowerData_t mpbFtaLowPowerData;
	mpbFtaLowPowerData.mpbFtaLowPowerValue = 0x1234;
	
		typedef union
	{
		mpbFtaLowTempBitAssignment_t		mpbFtaLowTempBitAssignment;
    uint16_t mpbFtaLowTempValue;		
	}mpbFtaLowTempData_t;

	mpbFtaLowTempData_t mpbFtaLowTempData;
	mpbFtaLowTempData.mpbFtaLowTempValue = 0x5678;
	

	
		if( index < BUFFER_LOG_SIZE )
		{
			xLaserLogEventDescriptor[index].mpbFtaLowPowerBitAssignment = mpbFtaLowPowerData.mpbFtaLowPowerBitAssignment;
			xLaserLogEventDescriptor[index].mpbFtaLowTempBitAssignment = mpbFtaLowTempData.mpbFtaLowTempBitAssignment;
			xLaserLogEventDescriptor[index].ucSampleNumber = ucSampleNumber;
			xLaserLogEventDescriptor[index].usmpbLogEventTime = ucTimerCounter ;
			//xLaserLogEventDescriptor[index].xAlarmRegister = pxLaserBeamDescriptor->xAlarmRegister;
		//	xLaserLogEventDescriptor[index].xStatusRegister = pxLaserBeamDescriptor->xStatusRegister;
			//xLaserLogEventDescriptor[index].eMpbLogMainLoopState =
		//	xLaserLogEventDescriptor[index].xBeaconId = pxLaserBeamDescriptor->xBeaconId;
		//	ucBeaconId = pxLaserBeamDescriptor->xBeaconId;					
		//	xLaserLogEventDescriptor[index].xLaserOperationMode[ucBeaconId]  = pxLaserBeamDescriptor->xLaserOperationMode[ucBeaconId];
	//		xLaserLogEventDescriptor[index].eMpbLogMainLoopState = pxLaserBeamDescriptor->
			
	//		eMainLoopState = getMainLoopState();
			
	/*		xLaserLogEventDescriptor[ index ].eMpbLogMainLoopState = eMainLoopState ;
			xLaserLogEventDescriptor[index].xCriticalAnalogCurrents = pxLaserBeamDescriptor->xCriticalAnalogCurrents;
			xLaserLogEventDescriptor[index].xCriticalAnalogPowers = pxLaserBeamDescriptor->xCriticalAnalogPowers;
			xLaserLogEventDescriptor[index].eControlGeneralMode = pxLaserBeamDescriptor->eControlGeneralMode;
			xLaserLogEventDescriptor[index].xAnalogTemperatureInputs = pxLaserBeamDescriptor->xAnalogTemperatureInputs;
			//xLaserLogEventDescriptor[index].xBeaconStatus = pxLaserBeamDescriptor->xBeaconStatus;
			xLaserLogEventDescriptor[index].eOperationMode[ ucBeaconId ] = pxLaserBeamDescriptor->eOperationMode[ ucBeaconId ];
			xLaserLogEventDescriptor[index].xElectricalVariablesStatus[ ucBeaconId ] = pxLaserBeamDescriptor->xElectricalVariablesStatus[ ucBeaconId ];*/
			
			
			xLaserLogEventDescriptor[index].xEventType = mpbEventTypeBitsignment;
			
			
			//copy contents
			// copy state general
			
		}
		
		if(mpbEventTypeBitsignment.bIsFault == 1)
		{
			for(int i = (index + 1); i< (BUFFER_LOG_SIZE ) ; i++ )
			{
				xLaserLogEventDescriptor[i].usmpbLogEventTime = xLaserLogEventDescriptor[i].usmpbLogEventTime - xLaserLogEventDescriptor[index].usmpbLogEventTime ;
			}	
			
			for(int i = 0; i < (index + 1); i++ )
			{
				xLaserLogEventDescriptor[i].usmpbLogEventTime = xLaserLogEventDescriptor[i].usmpbLogEventTime + xLaserLogEventDescriptor[BUFFER_LOG_SIZE-1].usmpbLogEventTime ;
			}	
		}
	
}
/*-----------------------------------------------------------*/

eMpbError_t eMpbLogEventInit( void )
{
	eMpbError_t 					eMpbError = eSuccess;
	
	memset(&xLaserLogEventDescriptor,0, (sizeof(xLaserLogEventDescriptor)) );
	eMpbSamplingTimeInit();
	
	return eMpbError;
}

/*----------------------------------------------------------*/
eMpbError_t eMpbLogEventRun( xAmplifierDescriptor_t *pxAmplifierDescriptor )
{
	eMpbError_t 					eMpbError = eSuccess;
	static uint8_t 				ucBufferIndex = 0;	
	static uint16_t 				ucSampleNumber = 0;	
	static uint8_t 				ucTimerCounter = 0;	
	static uint32_t 			ucTimerGeneral = 0;	
	//static uint8_t 				ucSimulAlarm = 1;	
	//static uint8_t 				ucSimulFault = 0;	
	mpbSamplingTimeType_t mpbSamplingTimeType;
	mpbEventTypeBitsignment_t mpbEventTypeBitsignment;
		
	xEventDetected.bMpbEventTypeDetectedAlarm = eTrue;//( (pxLaserBeamDescriptor->xAlarmRegister.AlarmGlobalValue != 0) )? eTrue : eFalse; // ucSimulAlarm;
  xEventDetected.bMpbEventTypeDetectedFault = bTestSampling; //( pxLaserBeamDescriptor->xFaultsPresents.bSomeInFault == eTrue )? eTrue : eFalse; //ucSimulFault; //
		
	eMpbError = eMpbSamplingTimeRun( 	xEventDetected.bMpbEventTypeDetectedAlarm,
																		xEventDetected.bMpbEventTypeDetectedFault,
																		&mpbSamplingTimeType );
	
	if( mpbSamplingTimeType == mpbSamplingTimeTypeAlarms )
	{		
		mpbEventTypeBitsignment.bIsAlarm = 1;
		mpbEventTypeBitsignment.bIsFault = 0;
		mpbEventTypeBitsignment.bNormal = 0;
		ucTimerCounter++;
		ucSampleNumber++;
		bFaultStateIsOn= eFalse;
		if(ucTimerCounter > SAMPLING_TIME_FOR_ALARMS_MS)
		{
				ucTimerCounter = 0;
			ucBufferIndex++;
			ucTimerGeneral = ucTimerGeneral + SAMPLING_TIME_FOR_ALARMS_MS;
			if(ucBufferIndex > BUFFER_LOG_SIZE)
			{
				ucBufferIndex = 0;
				ucTimerGeneral = 0;
			}
			svSaveLogInformation(pxAmplifierDescriptor,ucBufferIndex, ucSampleNumber, ucTimerGeneral,mpbEventTypeBitsignment);
		}
		
	}else if( mpbSamplingTimeType == mpbSamplingTimeTypeFaults )
	{
		mpbEventTypeBitsignment.bIsAlarm = 0;
		mpbEventTypeBitsignment.bIsFault = 1;
		mpbEventTypeBitsignment.bNormal = 0;
		
		
		if(bFaultStateIsOn == eFalse )
		{
			ucTimerGeneral++;
			bFaultStateIsOn = eTrue;
			ucBufferIndex++;
			ucSampleNumber++;
			svSaveLogInformation(pxAmplifierDescriptor, ucBufferIndex,ucSampleNumber, ucTimerGeneral,mpbEventTypeBitsignment);
		
			eMpbSaveLogEvent( 1 );//mem 1
			eMpbSaveLogEvent( 2 );//mem 2
			/*if( ucBufferIndex >= BUFFER_LOG_SIZE )
			{
			ucBufferIndex = 0;
			eMpbSaveLogEvent( 1 );//mem 1
			eMpbSaveLogEvent( 2 );//mem 2
			}*/
		}
		
	}else
	{
		mpbEventTypeBitsignment.bIsAlarm = 0;
		mpbEventTypeBitsignment.bIsFault = 0;
		mpbEventTypeBitsignment.bNormal = 1;
		ucBufferIndex = 0;
		ucTimerCounter = 0;
		ucTimerGeneral = 0;
	}
	
//	ucBufferIndex++;
	
	if( ucBufferIndex >= BUFFER_LOG_SIZE )
	{
	//x	ucBufferIndex = 0;
	}
	
	
	return eMpbError;	
}

/*-------------------------------------------------------*/
eMpbError_t eMpbSaveLogEvent( handle_t stream )
{
	eMpbError_t eMpbError = eSuccess;
	
	
	return eMpbError;	
}
/*---------------------------------------------------------*/
xLaserLogEventDescriptor_t *eMpbGetLogEvent( uint8_t index )
{
	return &xLaserLogEventDescriptor[ index ];
}

