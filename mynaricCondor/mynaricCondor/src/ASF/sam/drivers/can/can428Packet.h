/**
* @file			can426Packet.h
* @brief
* @author		juan andres castano
* @date			Created on 2023-01-19
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef CAN428PACKET_H_
#define CAN428PACKET_H_


/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
//#define DEF_MAX_NUMBER_OF_CHANNELS	            ( 23 )

//#define DEF_CAN_426_INDEX		            ( 0 )
//#define DEF_CAN_426_RAW_DATA				( 8 )


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
typedef struct
{
	uint64_t bLnaInputPowerLOSAlarm							: 1;     /* bit 0  */
	uint64_t bLnaInputPowerIsTooHigh						: 1;     /* bit 1  */
	uint64_t bLnaOutputPowerIsTooHigh	 					: 1;     /* bit 2  */
	uint64_t bLnaCurrentHighAlarmStatus						: 1;     /* bit 3  */
	
	uint64_t bBoosterbackfacetIscorrect						: 1;     /* bit 4  */	
	uint64_t bBoosterInputPowerLOSAlarm						: 1;     /* bit 5  */
	uint64_t bBoosterInputPowerIsTooHigh					: 1;     /* bit 6  */
																			//uint64_t bBoosterInputPowerIsTooLow						: 1;     /* bit 5  */		
	uint64_t bSm_DriverStucked								: 1;     /* bit 7  */
	uint64_t bMm1_DriverStucked								: 1;     /* bit 8  */
	uint64_t bMm2_DriverStucked								: 1;     /* bit 9  */
	
	uint64_t bBoosterOutputPowerIsTooHigh					: 1;     /* bit 10  */
																			//uint64_t bBoosterCurrentIsTooLow		: 1;     /* bit 4  */
	uint64_t bBoosterCurrentIsTooHigh						: 1;     /* bit 11  */
	
																			//uint64_t bLnaCurrentLowAlarmStatus						: 1;     /* bit 6  */
	
	
																					//	uint64_t bTXCANHasAError								: 1;     /* bit 10  */
	uint64_t bRXCANHasAError								: 1;     /* bit 12  */
	
																						//uint64_t bHpaAboveLosClear									: 1;     /* bit 9  */
																						//uint64_t bLnaOutputPowerIsTooLow	  					: 1;     /* bit 12  */	
	
																						//uint64_t bSpiAdcTimeoutAlarm 							: 1;     /* bit 15  */
	uint64_t bMemoryACrcErrorDetectedAtPowerUp 				: 1;     /* bit 13  */
																							//uint64_t bInternalAdcError28vCmCh1ooLow 				: 1;     /* bit 17  */
																							//uint64_t bInternalAdcError28vCmCh1tooHigh 				: 1;     /* bit 18  */
	uint64_t bInternalAdcError28vVmCh1TooLow 				: 1;     /* bit 14  */
																							//uint64_t bInternalAdcError28vVmCh1TooHigh				: 1;     /* bit 15  */
																							//uint64_t bInternalAdcError28vVmCh2tooLow				: 1;     /* bit 16  */
																							//uint64_t bInternalAdcError28vVmCh2toohigh				: 1;     /* bit 22  */
																							//uint64_t bInternalAdcError7vPwrVmCh1TooLow				: 1;     /* bit 17  */																								//uint64_t bInternalAdcError7vPwrVmCh1TooHigh				: 1;     /* bit 24  */
	uint64_t bInternalAdcError7vPwrVmCh2tooLow				: 1;     /* bit 15  */
																								//uint64_t bResetFromStartupState							: 1;     /* bit 26  */
	uint64_t bInternalAdcError3vPwrVmTooLow					: 1;     /* bit 16  */
					
																								//uint64_t bInternalAdcError3_3vPwrVmtooLow				: 1;     /* bit 28 */				
	uint64_t bInternalAdcErrorAdcPwrCmtooLow				: 1;     /* bit 17  */
	//uint64_t bInternalAdcError28vCm_TooLow					: 1;     /* bit 18  */				
	//uint64_t bInternalCAN_PwrError_TooLow					: 1;     /* bit 18 */
																								//uint64_t bInternalAdcErrorCanPwrCm1tooLow				: 1;     /* bit 30  */
																								//uint64_t bInternalAdcErrorCanPwrCm1tooHigh				: 1;     /* bit 21  */
																								//uint64_t bInternalAdcErrorCanPwrCm2TooLow				: 1;     /* bit 32  */
																								//	uint64_t bInternalAdcErrorCanPwrCm2TooHigh				: 1;     /* bit 18  */
																										//uint64_t bHpaUnderLosSet										: 1;     /* bit 17  */
	uint64_t bPassWordValidated								: 1;     /* bit 18  */
	
	
	uint64_t bLnaSmAlarmLowTemperature				: 1;     /* bit 19  */
	uint64_t bLnaSmAlarmHighTemperature					: 1;     /* bit 20 */
	uint64_t bLnaSmAlarmWayTooHighTemperature				: 1;     /* bit 21  - FAULT */
	
	/*hpa Sm thermistor*/	
	uint64_t bHpaSmAlarmLowTemperature				: 1;     /* bit 22   */
	uint64_t bHpaSmAlarmHighTemperature					: 1;     /* bit 23   */
	uint64_t bHpaSmAlarmWayTooHighTemperature				: 1;     /* bit 24  - FAULT */
	
	/*hpa Mm1 thermistor*/
	uint64_t bHpaMm1AlarmLowTemperature				: 1;     /* bit 25   */
	uint64_t bHpaMm1AlarmHighTemperature					: 1;     /* bit 26 */
	uint64_t bHpaMm1AlarmWayTooHighTemperature				: 1;     /* bit 27  - FAULT */
	
	/*hpa Mm2 thermistor*/
	uint64_t bHpaMm2AlarmLowTemperature				: 1;     /* bit 28   */
	uint64_t bHpaMm2AlarmHighTemperature					: 1;     /* bit 29   */
	uint64_t bHpaMm2AlarmWayTooHighTemperature				: 1;     /* bit 30  - FAULT */
	
	/*case thermistor*/
	uint64_t bCaseAlarmLowTemperature				: 1;     /* bit 31   */
	uint64_t bCaseAlarmHighTemperature					: 1;     /* bit 32   */
	uint64_t bCaseAlarmWayTooHighTemperature				: 1;     /* bit 33  - FAULT */
	
	
	
	uint64_t bResetFromStartupState							: 1;     /* bit 34  */

} MpbAlarmsAndStatusRegisterBitAssignment_t;

/* Exported struct ---------------------------------------------------------- */

typedef union
{
	MpbAlarmsAndStatusRegisterBitAssignment_t			MpbAlarmsAndStatusRegisterBitAssignment;
	uint64_t											ulMpbAlarmsValue;	
}c428StatusDefinition_t;



/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit428CanImage( void );

/**
* @brief		get the 428 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan428( CAN_FRAME *pCan);

/**
* @brief		set the 428 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan428( CAN_FRAME *pCan);


/**
* @brief		decode the 428 CAN message
* @param[in]	c428StatusDefinition_t: pointer to the 428 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan428Decode( c428StatusDefinition_t *c428StatusDefinition );

/**
* @brief		encode the 428 CAN message
* @param[in]	c428StatusDefinition_t: pointer to the 428 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan428Encode( c428StatusDefinition_t *c428StatusDefinition);



#endif /* CAN426PACKET_H_ */


