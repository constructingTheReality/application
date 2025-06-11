/**
  * @file			BSPDac.h
  * @brief    BSPDac header file.
  * @author		juan andres
  * @date			Created on 3/ 4/2021
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


#ifndef BSPDAC_H_
#define BSPDAC_H_
/* Includes ----------------------------------------------------------------- */

#include "pwm.h"
#include "board.h"
#include "sysclk.h"

#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */

/**
* @brief        Define the DAC inputs.
* @note         DacChannelId               The identifier for the channel.
* @note         RCLP filter constant       The rclp filter constant. 
*/

/*	                	        X(	DacChannelId			,RCLP Filter Constant   )	*/
#define LIST_OF_DAC_CHANNELS	X(  eDacControlLaser1          ,4                     )\
                                X(	eDacControlLaser2    	   ,4                     )
															
															

#define DAC_VOLTAGE_REFERENCE_MV				( 2500 ) //3300 ) 			/* mV */
#define DAC_NUMBER_OF_BYTES						( 12 )
#define DDC_HARDWARE_RESOLUTION					( 1 << ADC_NUMBER_OF_BYTES ) /* 2^12 = 4096 */
#define DAC_ADDITIONAL_RESOLUTION_BIT		    ( 2 )
#define DAC_RESOLUTION 							( ( DDC_HARDWARE_RESOLUTION << DAC_ADDITIONAL_RESOLUTION_BIT ) - 1 ) /* ( 2^14 ) - 1 */

/* Exported macro ----------------------------------------------------------- */

#define DAC_LSB_TO_MV( usLsb ) 					( ( usLsb * DAC_VOLTAGE_REFERENCE_MV ) / DAC_RESOLUTION )
																					//(float)usVal / 4095.0f * ADC_VREF;
#define DAC_MV_TO_LSB( usMv )						( ( usMv * ADC_RESOLUTION ) / DAC_VOLTAGE_REFERENCE_MV )
#define DAC_LSB_TO_DEMAND( usLsb ) 			( ( usLsb * 100 ) / DAC_RESOLUTION )

/* Exported enum ------------------------------------------------------------ */

/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( DacChannelId, RCLPFilterConstant )	DacChannelId,
	LIST_OF_DAC_CHANNELS 
#undef X
	eNumberOfDacChannel,
}
eDacChannel_t;   


/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief	Inits and start the ADC.
* @note		Calibration is performed.
*/
void vBSPDacInitAndStart( void );

/**
* @brief		  set the output to the DAC.
* @param[in]	eChannel: the channel requested.
* @param[out]	usOutputValue: The dac output.
*/
void vBSPDacSetOutputRaw( eDacChannel_t eChannel, uint16_t usOutputValue );

/**
* @brief		  set the output of the DAC in milivolt.
* @param[in]	eChannel: the channel requested.
* @param[out]	usOutputValueMv: The dac output in miliVolt.
*/
void vBSPDacSetOutputMv( eDacChannel_t eChannel,  uint16_t usOutputValueMv );

void vBSPDacSetOutputDuty( eDacChannel_t eChannel,  uint8_t ucDutyCycle);

/**
* @brief		  update the raw data channels 
*/
void vBSPDacUpdateChannels( void );

#endif /* __BSP_DAC_H */

