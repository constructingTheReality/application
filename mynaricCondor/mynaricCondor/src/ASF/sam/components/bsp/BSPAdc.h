

/**
  * @file			BSPAdc.h
  * @brief    BSPAdc header file.
  * @author		juan andres
  * @date			Created on 3/ 4/2023
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

#ifndef BSPADC_H_
#define BSPADC_H_
/* Includes ----------------------------------------------------------------- */

//#include "va416xx_hal_adc.h"
#include "mpblibs.h"
#include "adc.h"
/** ADC Peripheral clock source (digital side, registers) */
#define ADC_CLK (10000)  // TODO : define
/* Define ------------------------------------------------------------------- */

/**
* @brief        Define the ADC inputs.
* @note         AdcChannelId               The identifier for the channel.
* @note         RCLP filter constant       The rclp filter constant. 
*/

/*	                	        X(	AdcChannelId		    			,RCLP Filter Constant   )	*/
#define LIST_OF_ADC_CHANNELS	X(  eAdc28VPwrCurrentMonitorCH1			,140                   )\
								X(  eAdc28VPwrCurrentMonitorCH2			,140                   )\
								X(  eAdc28VPwrVoltageMonitorCH1			,140                   )\
								X(  eAdc28VPwrVoltageMonitorCH2			,140                   )\
								X(  eAdc7VPwrVoltageMonitorCH1			,140                   )\
								X(  eAdc7VPwrVoltageMonitorCH2			,140                   )\
								X(  eAdc3_3VPower_VoltageMonitor		,140                   )\
								X(  eAdc3VPower_VoltageMonitor 			,140                   )\
								X(  eAdcPowerCurrentMonitor				,140                   )\
								X(  eAdcCanPwrCurrentMonitorCH1			,140                   )\
								X(  eAdcCanPwrCurrentMonitorCH2			,140                   )\
								X(  eAdcLnaOutputPower2					,140                   )\
								X(  eAdcPdReference						,140                   )\
								X(	eAdcLnaOutputPower1					,140                   )
															
															

/*	                	        		X(	AdcExChannelId						,RCLP Filter Constant   )	*/
#define LIST_OF_EXTERNAL_ADC_CHANNELS	X(  eAdcExLna_Inm			            ,3                    )\
										X(	eAdcExLna_OutM1						,3                    )\
										X(	eAdcExLna_OutM2						,3                    )\
										X(	eAdcExHpa_Inm 						,3                    )\
										X(  eAdcExHpa_OutLm						,3                    )\
										X(  eAdcExHpa_OutHm						,3                    )\
										X(	eAdcExPd_Ref1						,3                    )\
										X(	eAdcExLnaSmld_Bfm					,3                    )\
										X(	eAdcExLnaSmldCurrentMonitor			,3                    )\
										X(	eAdcExHpaSmld_CurrentMonitor		,3                    )\
										X(	eAdcExHpaMmld_CurrentMonitor1		,3                    )\
										X(	eAdcExHpaMmld_CurrentMonitor2		,3                    )\
										X(	eAdcExLnaSmld_Thermistor			,3                    )\
										X(	eAdcExHpaSmld_Thermistor			,3                    )\
										X(	eAdcExSpare1						,3                    )\
										X(	eAdcExSpare2						,3                    )\
										X(	eAdcExHpaMMld_Thermistor1			,3                    )\
										X(	eAdcExHpaMMld_Thermistor2			,3                    )\
										X(	eAdcExHpaMMld_Thermistor3			,3                    )\
										X(	eAdcExHpaMMld_Thermistor4			,3                    )\
										X(	eAdcExCaseThermistor1	 			,3                    )\
										X(	eAdcExSpare3						,3                    )\
										X(	eAdcExHpaSmld_Bfm		 			,3                    )\
										X(	eAdcExPd_Ref2		   				,3                    )

																			
#define ADC_VOLTAGE_REFERENCE_V				( 3.3 ) // ( 2500 ) 			/* mV */																			
#define ADC_VOLTAGE_REFERENCE_MV			( 3300 ) // ( 2500 ) 			/* mV */
#define ADC_NUMBER_OF_BYTES					( 12 )
//#define ADC_EXTERNAL_NUMBER_OF_BYTES		( 10 )
#define ADC_HARDWARE_RESOLUTION				( 1 << ADC_NUMBER_OF_BYTES ) /* 2^12 = 4096 */
#define ADC_ADDITIONAL_RESOLUTION_BIT		( 2 )
#define ADC_RESOLUTION 						( ( ADC_HARDWARE_RESOLUTION << ADC_ADDITIONAL_RESOLUTION_BIT ) - 1 ) /* ( 2^14 ) - 1 */
#define NUMBER_OF_CHANELS_BY_IC				( 8 )
#define NUMBER_OF_CHANELS_BY_IC_3			( 5 )

/* Exported macro ----------------------------------------------------------- */

#define ADC_LSB_TO_MV( usLsb ) 					( ( usLsb * ADC_VOLTAGE_REFERENCE_MV ) / ADC_RESOLUTION )
#define ADC_LSB_TO_MV_EXTERNAL( usLsb )	( ( usLsb * 3300 ) / ADC_RESOLUTION )																					//(float)usVal / 4095.0f * ADC_VREF;
#define ADC_LSB_TO_RAW_EXTERNAL( usLsb )	( ( usLsb * 4095 ) / ADC_RESOLUTION )																					//(float)usVal / 4095.0f * ADC_VREF;
#define ADC_LSB_TO_MV_INTERNAL( usLsb )	( ( usLsb * ADC_VOLTAGE_REFERENCE_MV ) / ADC_RESOLUTION )																				//(float)usVal / 4095.0f * ADC_VREF;
#define ADC_MV_TO_LSB( usMv )						( ( usMv * ADC_RESOLUTION ) / ADC_VOLTAGE_REFERENCE_MV )
#define ACD_LSB_TO_DEMAND( usLsb ) 			( ( usLsb * 100 ) / ADC_RESOLUTION )

/* Exported enum ------------------------------------------------------------ */

/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( AdcChannelId, RCLPFilterConstant )	AdcChannelId,
	LIST_OF_ADC_CHANNELS 
#undef X
	eNumberOfInternalAdcChannel,
}
eAdcChannel_t;   


typedef enum
{
#define X( AdcExChannelId, RCLPFilterConstant )	AdcExChannelId,
	LIST_OF_EXTERNAL_ADC_CHANNELS 
#undef X
	eNumberOfExternalAdcChannel,
}
eExternalAdcChannel_t;  

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief	Inits and start the ADC.
* @note		Calibration is performed.
*/
void vBSPAdcInitAndStart( void );

/**
* @brief		Get the result of the ADC.
* @param[in]	eChannel: the channel requested.
* @param[out]	pusReading: The adc reading.
*/
void vBSPAdcGetResultRaw( eAdcChannel_t eChannel, uint16_t *pusReading );

/**
* @brief		Get the result of the external ADC.
* @param[in]	eChannel: the channel requested.
* @param[out]	pusReading: The adc reading.
*/
void vBSPExternalAdcGetResultRaw( eExternalAdcChannel_t eChannel, uint16_t *pusReading );


/**
* @brief		Get the result of the ADC in milivolt.
* @param[in]	eChannel: the channel requested.
* @param[out]	pslReadingMv: The adc reading in miliVolt.
*/
void vBSPAdcGetResultMv( eAdcChannel_t eChannel, int32_t *pslReadingMv ,  uint16_t *usReadingRaw );

/**
* @brief		Get the result of the external ADC in milivolt.
* @param[in]	eChannel: the channel requested.
* @param[out]	pslReadingMv: The adc reading in miliVolt.
*/
void vBSPExternalAdcGetResultMv( eExternalAdcChannel_t eChannel, int32_t *pslReadingMv ,  uint16_t *usReadingRaw);


/**
* @brief		  update the raw data channels 
*/
void vBSPAdcUpdateChannels( void );

/**
* @brief		  update the raw data channels
*/
eMpbError_t eBSPExternalAdcChannels(void);



#endif /* __BSP_ADC_H */




