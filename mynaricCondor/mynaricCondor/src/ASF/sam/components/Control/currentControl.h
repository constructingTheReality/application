/**
* @file			CurrentControl.h
* @brief		CurrentControl.h header file
* @author		juan andres
* @date			Created on 2021-03-11
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
#ifndef CURRENTCONTROL_H_
#define CURRENTCONTROL_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
//#include "ControlAlarm.h"
#include "LaserData.h"
//#include "cmd_interface.h"
/* Define ------------------------------------------------------------------- */
#define FACTORY_MAX_CURRENT ( 581 )
#define FACTORY_MIN_CURRENT ( 75 )
#define FACTORY_MAX_POWER ( 0.604 )  //mW
/**
* @brief        Define the slope intercept values for current control .
* @note         CurrentChannelConfigId     The identifier for the channel.
* @note         slope constant       			 The slope filter constant.
* @note         intercept constant       	 The intercept constant.
*/
/*	                	            X(	CurrentControlChannelConfigId			    ,slope Filter Constant	  ,intercept Filter   )	*/
#define LIST_OF_CONTROL_CHANNELS	X(  e974LD1LnaLaserDiodeControlCurrentPwm_1536			,7.162            	  ,-68.038   )\
                                    X(  e974LD1LnaLaserDiodeControlCurrentmA_1536			,0.559            	  ,9.5       )\
									X(  e974LD1LnaLaserDiodeControlCurrentPwm_1553			,7.162             	  ,-68.038   )\
									X(  e974LD1LnaLaserDiodeControlCurrentmA_1553			,0.559                ,9.5       )\
									X(  e974LD1HpaSmStp1LaserDiodeControlCurrentmA_1536		,0.568             	  ,0         )\
									X(  e974LD1HpaSmStp1LaserDiodeControlCurrentPwm_1536	,8.252				  ,-701.421  )\
									X(  e974LD1HpaSmStp1LaserDiodeControlCurrentmA_1553		,0.568             	  ,0         )\
									X(  e974LD1HpaSmStp1LaserDiodeControlCurrentPwm_1553	,8.252	              ,-701.421  )\
									X(  e974LD1HpaMmStp1LaserDiodeControlCurrentmA_1553		,5.018             	  ,24        )\
									X(  e974LD1HpaMmStp1LaserDiodeControlCurrentPwm_1553	,0.797             	  ,-19.1373  )\
									X(  e974LD1HpaMmStp1LaserDiodeControlCurrentmA_1536		,5.018             	  ,24        )\
									X(  e974LD1HpaMmStp1LaserDiodeControlCurrentPwm_1536	,0.797             	  ,-19.1373  )\
									X(  e974LD1HpaMmStp2LaserDiodeControlCurrentmA_1553		,5.018             	  ,24        )\
									X(  e974LD1HpaMmStp2LaserDiodeControlCurrentPwm_1553	,0.797             	  ,-19.1373  )\
									X(  e974LD1HpaMmStp2LaserDiodeControlCurrentmA_1536		,5.018             	  ,24        )\
									X(  e974LD1HpaMmStp2LaserDiodeControlCurrentPwm_1536	,0.797             	  ,-19.1373  )\
									X(  e974LD1HpaHclk1										,1                 	  ,0         )\
									X(	e974LD1HpaHclk2										,1                    ,0 	     )
// HPA : LaserDiodeControlCurrentmA .-> setpoint in % (0..1023) to mA (0...581)  y ? 7.045x
//		 LaserDiodeControlCurrentPwm -> 0--581 -->  0 ..4093 ( y ? 7.162x -68.038)
//hpa mm1
//		 LaserDiodeControlCurrentmA .-> setpoint in % (0..1023) to mA (24...5157)   y ? 5.018x + 24
//		 LaserDiodeControlCurrentPwm -> 24--5157 -->  0 ..4093 ( y ? 0.797x -19.1373)
//
//LNA:
// 9.5--581 -->  0 ..4093 ( y ? 7.162x -68.038)
// 0...1023 (sp in %) -->  0..581 (max current)   == 0.567

//y ? 8.252x -701.421   current output in pwm >  85,0     581,4093    85 -> current at 0 pwm
/* Exported macro ----------------------------------------------------------- */

/* Exported enum ------------------------------------------------------------ */

/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( CurrentControlChannelConfigId, slopeConstant, interceptConstant )	CurrentControlChannelConfigId,
	LIST_OF_CONTROL_CHANNELS 
#undef X
	eNumberOfChannelControlConfigurations,
}
eCurrentControlChannelsScaling_t; 

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
  * @brief 		Init the current scaling channels.
*/
//void vCurrentControlInit( void );
void vLnaCurrentControlInit( void );
void vBoosterCurrentControlInit( void );

void vCurrentOutputLnaConfigUpdate( void );
void vCurrentOutputBoosterConfigUpdate( void );
//void vCurrentOutputConfigUpdate( void );


/**
  * @brief 		Update critical currents of the laser.
  * @param[out]	none.
  */

eMpbError_t eCurrentControlUpdateHpa1( float fCurrent ) ; 

eMpbError_t eCurrentControlUpdateMmHpa1( float fCurrent ) ; 
eMpbError_t eCurrentControlUpdateMmHpa2( float fCurrent ) ; 
eMpbError_t eCurrentControlUpdateLna( float fCurrent ) ; 

eMpbError_t eCurrentControlReset( void ) ;

void vCurrentControlgetOutputScalingValues ( float *pfSlope, float *pfIntercep, float *pfGain, handle_t eCurrentDriver );


void vCurrentControlsetOutputScalingValues ( float fSlope, float fIntercep, float fGain, handle_t eCurrentDriver );



eMpbError_t eCurrentCalibration( float fIntercept, float fSlope, float fGain ); 

eMpbError_t ePwmToCurrentConversion(eBool_t bWavelengthIs1536,  uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA ); 
eMpbError_t ePwmToCurrentConversion_Hpa1(eBool_t bWavelengthIs1536,  uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA ); 
eMpbError_t ePwmToCurrentConversion_MmHpa1( eBool_t bWavelengthIs1536, uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA );
eMpbError_t ePwmToCurrentConversion_MmHpa2( eBool_t bWavelengthIs1536, uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA );

#endif /* __CURRENTCONTROL_H */





