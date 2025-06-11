/**
* @file		    Glue.h
* @brief        glue header file.
* @author		juan
* @date			Created on 2021-03-5
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
#ifndef GLUE_H_
#define GLUE_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "CurrentSensing.h"
#include "CurrentOutput.h"
//#include "powerOutput.h"
#include "mpbMath.h"
#include "thermistor.h"
//#include "mpbDigitalFiltering.h"
//#include "mpbCommandhandler.h"
//#include "mpbSerialDriver.h"

/* Define ------------------------------------------------------------------- */
#define SPI1_HANDLE								( 1 )
#define SPI2_HANDLE               ( 2 )
//#define UART1_HANDLE							( 1 )
//#define UART2_HANDLE							( 2 )
//#define UART3_HANDLE							( 3 )

#define NVM1_SPI_HANDLE                          ( SPI1 )
//#define NVM2_SPI_HANDLE                          ( SPI2 )

/* Exported macro ----------------------------------------------------------- */
#define vDoNothing( x )
/* Exported enum ------------------------------------------------------------ */

/**
* @brief List of general handles
*/
enum Handle
{
	
	//currents internal
	eHandleAdc28VPwrCurrentMonitorCH1 = 0,
	eHandleAdc28VPwrCurrentMonitorCH2 = 1,
	eHandleAdc28VPwrVoltageMonitorCH1 = 2,
	eHandleAdc28VPwrVoltageMonitorCH2 = 3,
	eHandleAdc7VPwrVoltageMonitorCH1 = 4,
	eHandleAdc7VPwrVoltageMonitorCH2 = 5,
	eHandleAdc3_3VPower_VoltageMonitor = 6,
	eHandleAdc3VPower_VoltageMonitor = 7,
	
	eHandleAdcPowerCurrentMonitor = 8,	
	eHandleAdcCanPwrCurrentMonitorCH1 = 9,
	eHandleAdcCanPwrCurrentMonitorCH2 = 10,
	
	//currents external
	
	eHandleAdcExLnaSmldCurrentMonitor = 11,	// 401 fLaserPump4CurrentOfLna
	eHandleAdcExHpaSmld_CurrentMonitor = 12,
	eHandleAdcExHpaMultiModeld_CurrentMonitor1 = 13, // 401 fLaserPump1CurrentOfBooster
	eHandleExternalLnaSm_ld_Bfm = 14,
	eHandleExternalHpaSm_ld_Bfm = 15,	
	eHandleAdcExHpaMultiModeld_CurrentMonitor2= 16,  // 401 fLaserPump2CurrentOfBooster
	
	
	/*eHandleAdcLnaOutm2 = 11,
	eHandleAdcPdReference = 12,
	eHandleAdcLnaOutm1 = 13,*/
	
	eHandlePwmLnaStp = 17,
	eHandlePwmSmStp1 = 18,
	eHandlePwmSmStp2 = 19,
	eHandlePwmMmStp1 = 20,
	eHandlePwmMmStp2 = 21,
	eHandlePwmMmclck1 = 22,
	eHandlePwmMmclck2 = 23,
	eHandleLnaLddEna = 24,
	eHandleHpaSmLddEna = 25,
	eHandleHpaMmLddEna1 = 26,
	eHandleHpaMmLddEna2 = 27,
	
	eHandleFramPwrEna = 28,
	eHandle28vPwrDis1 = 29,
	eHandle28vPwrDis2 = 30,
	eHandleAdcPwrEna = 31,
	eHandleCanPwrEna1 = 32,
	eHandleCanPwrEna2 = 33,
	eHandleAdcCs0     = 34,
	eHandleAdcCs1     = 35,
	eHandleAdcCs2     = 36,
	
	
	eHandleAdcExSmLnaThermistor = 37,
	eHandleAdcExSmHpaThermistor = 38,
	
	eHandleAdcExCaseThermistor = 39,
	eHandleAdcExHpaMmThermistor1 = 40,
	eHandleAdcExHpaMmThermistor2 = 41,
	eHandleAdcExHpaMmThermistor3 = 42,
	eHandleAdcExHpaMmThermistor4 = 43,
	
		
	//powers in order
	eHandleAdcPdReference = 44,
	eHandleAdcLnaOutm1 = 45,
	eHandleAdcLnaOutm2 = 46,			
	eHandleExternalLnaInputPower1 = 47, // should be configured as 2 wavelengths	
	eHandleExternalLnaInputPower2 = 48, // should be configured as 2 wavelengths	
	eHandleExternalLnaOutputPower1 = 49, //401 fLnaOpticalOutputPower
	eHandleExternalLnaOutputPower2 = 50, //401 fLnaOpticalOutputPower	
	eHandleExternalHpaInputPower1 = 51, //401 fBoosterOpticalInputPower
	eHandleExternalHpaInputPower2 = 52, //401 fBoosterOpticalInputPower
	
	eHandleExternalHpaOutputPower_lm1  = 53, // 401 fBoosterOutputOpticalPower
	eHandleExternalHpaOutputPower_hm1 = 54,  // 401 fBoosterOutputOpticalPower		
	eHandleExternalHpaOutputPower_lm2  = 55, // 401 fBoosterOutputOpticalPower
	eHandleExternalHpaOutputPower_hm2 = 56,  // 401 fBoosterOutputOpticalPower
	eHandleExternalPd_ref1 = 57,
	eHandleExternalPd_Ref = 58,
	
	
	

	
	
	eHandleFramCs     =59,
	eHandleFramWp   = 60,
	
	//outputs
	eHandleLnaOutputVoltage = 61,
	eHandle3vPwrEna1 = 62,
	eHandle3vPwrEna2 = 63
	/*eHandle980DiodeTecCurrent,
	eHandleSetpointTemperature,
	eHandleLaserDriver,
	eHandleLaserDriverEnable,
	eHandleLaserDriverPWM,
	eHandleLaserDriverBrake,
	eHandleLaserFeedback,
	eHandleCurrentSensor,
	eHandleInputMA,
	eHandleEnableLaserPdm,
	eHandleNvm ,
	eHandleLaserFault,
	eHandleUartTxEnable,*/
};

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

//void vGlueMpbInitCrc( void );

//uint8_t ucMpbNvmCalculateCrc( const uint8_t* pucBuffer, size_t xBufferSize );

//eMpbError_t eMpbNvmValidateCrc( uint8_t *pucBuffer, size_t xBufferSize, uint8_t ucCheck );

/**
* @brief        Initialize the calibration for analogs
*/
//void vGlueAnalogInit( void );

/**
* @brief        start the reception of the UART
*/
//void vGlueUsartStartReception( void );

/**
* @brief        Convert the HAL error to mpblibs error
* @param[in]    xHalError: the hal error
* @return       the mpblibs equivalent error
*/
//eMpbError_t eGlueMpbErrorConversion( HAL_StatusTypeDef xHalError );





#endif /* GLUE_H_ */