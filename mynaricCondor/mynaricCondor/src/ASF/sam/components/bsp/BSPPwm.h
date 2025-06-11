/**
  * @file			BSPPwm.h
  * @brief    BSP Pwm header file.
  * @author		juan andres
  * @date			Created on 3/ 2/2023
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB.</center>
  *
  **/
/* Header guard ------------------------------------------------------------- */
#ifndef BSPPWM_H_
#define BSPPWM_H_
/* Includes ----------------------------------------------------------------- */

#include "pwm.h"
//#include "board.h"
#include "mynaricBoard.h"
#include "sysclk.h"
#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/** PWM frequency in Hz */
#define PWM_FREQUENCY      12000

/** Period value of PWM output waveform */
#define PERIOD_VALUE       4095 //1023
#define PERIOD_VALUE1      42
/** Period value of CLK output waveform */
#define PERIOD_CLK_VALUE   100
/** Initial duty cycle value */
#define INIT_DUTY_VALUE    0
#define INIT_DUTY_VALUE1    20
/**
* @brief        Define the PWM outputs.
* @note         PwmChannelId               The identifier for the channel.
*/
/*	                	        X(	PwmChannelId			,Channel 					      alignment			InitialPolarity		InitialDutyCycle	Period	   )	*/
#define LIST_OF_PWM_CHANNELS	X(  eLNA_PWM_STP           ,PIN_PWM_LNA_PWM_STP_CHANNEL       ,PWM_ALIGN_LEFT     ,PWM_LOW           , INIT_DUTY_VALUE	,PERIOD_VALUE )\
								X(  eHPA_SM_PWM_STP1       ,PIN_PWM_HPA_SM_PWM_STP1_CHANNEL   ,PWM_ALIGN_LEFT     ,PWM_LOW           , INIT_DUTY_VALUE	,PERIOD_VALUE )\
								X(  eHPA_SM_PWM_STP2       ,PIN_PWM_HPA_SM_PWM_STP2_CHANNEL   ,PWM_ALIGN_LEFT     ,PWM_LOW           , INIT_DUTY_VALUE	,PERIOD_VALUE )\
								X(  eHPA_MM_PWM_STP1       ,PIN_PWM_HPA_MM_PWM_STP1_CHANNEL   ,PWM_ALIGN_LEFT     ,PWM_LOW           , INIT_DUTY_VALUE	,PERIOD_VALUE )\
								X(  eHPA_MM_PWM_STP2       ,PIN_PWM_HPA_MM_PWM_STP2_CHANNEL   ,PWM_ALIGN_LEFT     ,PWM_LOW           , INIT_DUTY_VALUE	,PERIOD_VALUE )\
								X(  eHPA_MM_CLK1		   ,PIN_PWM_HPA_MM_CLK1_CHANNEL		  ,PWM_ALIGN_LEFT     ,PWM_HIGH          , INIT_DUTY_VALUE1	,PERIOD_VALUE1 )\
								X(	eHPA_MM_CLK2    	   ,PIN_PWM_HPA_MM_CLK2_CHANNEL		  ,PWM_ALIGN_LEFT     ,PWM_HIGH          , INIT_DUTY_VALUE1 ,PERIOD_VALUE1 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( PwmChannelId ,Channel, Alignment, InitialPolarity, InitialDutyCycle, Period )	PwmChannelId,
	LIST_OF_PWM_CHANNELS 
#undef X
	eNumberOfPwmChannel,
}
ePwmChannel_t;   
 
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief	Inits and start the Pwm.
* @note		
*/
void vBSPPwmInitAndStart( void );

/**
* @brief		  set the output of the pwm in duty cycle.
* @param[in]	eChannel: the channel requested.
*/
void vBSPPwmSetOutputDuty( ePwmChannel_t eChannel,  uint32_t ucDutyCycle);


#endif /* BSPPWM_H_ */