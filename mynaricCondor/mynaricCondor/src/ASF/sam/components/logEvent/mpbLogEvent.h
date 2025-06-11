/**
* @file         mpbLogEvent.h
* @brief        fmea and fta reporting utility. 
* @author       juan andres Castano
* @date         Created on 2022-07-30
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2022 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/

#ifndef MPBLOGEVENT_H_
#define MPBLOGEVENT_H_


/* Includes ----------------------------------------------------------------- */
//#include "Defs.h"
#include "mpblibs.h"
//#include "mainStateMachine.h"
#include "LaserData.h"
#include "mpbSamplingTime.h"

/* Private define ----------------------------------------------------------- */
#define  SAMPLING_TIME_FOR_NO_ALARMS_MS		( 100 )
#define  SAMPLING_TIME_FOR_ALARMS_MS 		( 5 )
#define  SAMPLING_TIME_FOR_FAULT_MS 		( 1 )
#define  BUFFER_LOG_SIZE					( 100 )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
typedef struct
{
    uint16_t b980PoweromputingError 			: 1;     /* bit 0 */
	uint16_t b1545PowercomputingError			: 1;     /* bit 1 */
	uint16_t bLowPowerFail      			 	: 1;     /* bit 2 */
	uint16_t bNormalLowPowerFail 			    : 1;     /* bit 3  */
	uint16_t bElectricalFailLowPower			: 1;     /* bit 4 */
    uint16_t b980NormalLowPowerFail   		    : 1;     /* bit 5 */
	uint16_t b1545NormalLowPowerFail 			: 1;     /* bit 6  */
	uint16_t b980ElectricalLowPowerFail	        : 1;     /* bit 7 */
	uint16_t b1545ElectricalLowPowerFail	    : 1;     /* bit 8 */		
}mpbFtaLowPowerBitAssignment_t;

typedef struct
{
    uint16_t b980nmcomputingError 							: 1;     /* bit 0 */
		uint16_t b1545nmcomputingError    					: 1;     /* bit 1 */
	  uint16_t bLowTemperatureFail      					: 1;     /* bit 2 */
		uint16_t bNormalLowTemperatureFail 				  : 1;     /* bit 3  */
	  uint16_t bElectricalFailLowTemperature			: 1;     /* bit 4 */
    uint16_t b980NormalLowTemperatureFail   		: 1;     /* bit 5 */
		uint16_t b1545NormalLowTemperatureFail 			: 1;     /* bit 6  */
	  uint16_t b980ElectricalLowTemperatureFail	  : 1;     /* bit 7 */
	  uint16_t b1545ElectricalLowTemperatureFail	: 1;     /* bit 8 */		
}mpbFtaLowTempBitAssignment_t;

typedef struct
{
    uint8_t bIsAlarm 			: 1;     /* bit 0 */
		uint8_t bIsFault			: 1;     /* bit 1 */
	  uint8_t bNormal				: 1;     /* bit 2 */
		
}mpbEventTypeBitsignment_t;


typedef enum
{
	mpbFtaCodeNoError = 0,
	mpbFtaCodeTempExtremLow ,
	mpbFtaCodePowerExtremLow ,
	mpbFtaCodePowerExtremHigh ,
		
}mpbFtaCode_t;

typedef struct
{
	eBool_t bMpbEventTypeDetectedNone;
	eBool_t bMpbEventTypeDetectedAlarm;
	eBool_t bMpbEventTypeDetectedFault;
}mpbEventTypeDetected_t;

typedef enum
{
	mpbFmeaNoError = 0,
	mpbFmeaLnaPowerMonitor,
	mpbFmeaLnaCurrentMonitor,
	mpbFmeaLnaTempMonitor,
	mpbFmeaHpaPowerMonitor
		
}mpbFmeaMode_t;




typedef struct
{ 
	uint8_t 									ucSampleNumber;
	mpbFmeaMode_t 		 						mpbFmeaMode;
	mpbFtaCode_t 								mpbFtaCode;
	mpbFtaLowTempBitAssignment_t  				mpbFtaLowTempBitAssignment;
	mpbFtaLowPowerBitAssignment_t 				mpbFtaLowPowerBitAssignment;
	//eMainLoopState_t 							eMpbLogMainLoopState;
	xAlarmRegister_t 						 					xAlarmRegister ;
	//xStatusRegister_t											xStatusRegister;
	c401StatusDefinition_t										c401StatusDefinition;
	c402StatusDefinition_t										c402StatusDefinition;
	c403StatusDefinition_t										c403StatusDefinition;
	c404StatusDefinition_t										c404StatusDefinition;
	c405Definition_t											c405Definition;
	c406PacketControlDefinition_t								c406PacketControlDefinition;
	c407PacketControlDefinition_t								c407PacketControlDefinition;
	c408StatusDefinition_t										c408StatusDefinition;
	c409StatusDefinition_t										c409StatusDefinition;
	c40AStatusDefinition_t										c40AStatusDefinition;	
	eOperationMode_t 							eOperationModeBoost;
	eOperationMode_t 							eOperationModeLna;
	uint32_t 									usmpbLogEventTime;
	mpbEventTypeBitsignment_t					xEventType;
	
}xLaserLogEventDescriptor_t;

/**
* @brief      Select and copy the log information, in case os a event.
* @param[in]  pxLaserBeamDescriptor: general info data. 
* @param[in]  pxLaserLogEventDescriptor: specific information to be logged. 
* @param[in]  pMpbSamplingTimeType: specific information to be logged. 
* @param[in]  bEventDetected: alarms/faults detected. 
* @return     Success or library error message
**/
eMpbError_t eMpbLogEventInit( void );

/**
* @brief      Select and copy the log information, in case os a event.
* @param[in]  pxLaserBeamDescriptor: general info data. 
* @param[in]  pxLaserLogEventDescriptor: specific information to be logged. 
* @param[in]  pMpbSamplingTimeType: specific information to be logged. 
* @param[in]  bEventDetected: alarms/faults detected. 
* @return     Success or library error message
**/
eMpbError_t eMpbLogEventRun( xAmplifierDescriptor_t *pxAmplifierDescriptor   );


/**
* @brief      Save the log info batch in nvm. 
* @param[in]  stream: device specific. 
* @param[in]  pxLaserLogEventDescriptor: info to be logged in memory. 
* @return     Success or library error message
**/
eMpbError_t eMpbSaveLogEvent( handle_t stream );

/**
* @brief      Get the log info batch in nvm. 
* @param[in]  stream: device specific. 
* @param[in]  pxLaserLogEventDescriptor: info to be logged in memory. 
* @return     Success or library error message
**/
//eMpbError_t eMpbGetLogEvent( xLaserLogEventDescriptor_t *xLaserLogEventDescriptor );
xLaserLogEventDescriptor_t *eMpbGetLogEvent( uint8_t index );





#endif /* MPBLOGEVENT_H_ */