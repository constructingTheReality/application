/**
* @file 		currentControl.c
* @brief		currentControl.c source file
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
/* Includes ----------------------------------------------------------------- */
#include "currentControl.h"
#include "glue.h"
#include "CurrentOutput.h"
#include "projectDef.h"
/* Private define ----------------------------------------------------------- */
#define CONTROL_CONFIG_NUMBER_OF_CHANNELS							( eNumberOfChannelControlConfigurations )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputLna_1536_PwmOutput;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputLna_1553_PwmOutput;

static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputLna_1536_mAStp;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputLna_1553_mAStp;


//hpa sm
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpa_1536_SmPwmStp;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpa_1553_SmPwmStp;

static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpa_1536_Sm_mAStp;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpa_1553_Sm_mAStp;

//hpa mm 1
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMMPwmStp1_1553;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMMPwmStp1_1536;

static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMM_mAStp1_1553;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMM_mAStp1_1536;


// hpa mm2
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMMPwmStp2_1553;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMMPwmStp2_1536;

static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMM_mAStp2_1553;
static xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputHpaMM_mAStp2_1536;


static uint16_t	usMaxCurrentRangeLocal;
static uint16_t	usMinCurrentRangeLocal;
static float	fMaxPowerRangeLocal;

static const float fCurrentControlSlopeScaleConstant[ CONTROL_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( CurrentControlChannelConfigId, slopeConstant, interceptConstant )	slopeConstant,
	LIST_OF_CONTROL_CHANNELS
	#undef X
};

static const float fCurrentControlInterceptScaleConstant[ CONTROL_CONFIG_NUMBER_OF_CHANNELS ] =
{
	#define X( CurrentControlChannelConfigId, slopeConstant, interceptConstant )	interceptConstant,
	LIST_OF_CONTROL_CHANNELS
	#undef X
};
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static void vUpdateCurrentControlLnaInternalConfig(void);
static void vUpdateCurrentControlHpaInternalConfig(void);
static void vUpdateCurrentControlLnaInternalConfig(void)
{
	xLnaParameters_t *pxLnaParameters = NULL;
	xLnaParameters_t xLnaParametersl ;
	pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl);
	
	//pxLnaParameters->usMaxCurrentRange = usMaxCurrentRangeLocal;
	pxLnaParameters->xElectricLimits.fCurrentMinimum				= usMinCurrentRangeLocal;
	pxLnaParameters->xElectricLimits.fCurrentMaximum				= usMaxCurrentRangeLocal;
	pxLnaParameters->xElectricLimits.fPowerMaximum					= fMaxPowerRangeLocal;
	
	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fSlope =  xDutyCycleCurrentOutputLna_1536_PwmOutput.fSlope ;
	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fIntercept = xDutyCycleCurrentOutputLna_1536_PwmOutput.fIntercept ;

	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fSlope =  xDutyCycleCurrentOutputLna_1553_PwmOutput.fSlope ;
	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fIntercept = xDutyCycleCurrentOutputLna_1553_PwmOutput.fIntercept ;

	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fSlope =  xDutyCycleCurrentOutputLna_1536_mAStp.fSlope ;
	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fIntercept = xDutyCycleCurrentOutputLna_1536_mAStp.fIntercept ;

	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fSlope =  xDutyCycleCurrentOutputLna_1553_mAStp.fSlope ;
	pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fIntercept = xDutyCycleCurrentOutputLna_1553_mAStp.fIntercept ;
	
}
static void vUpdateCurrentControlHpaInternalConfig(void)
{
		xBoosterParameters_t *pxBoosterParameters = NULL;		
		pxBoosterParameters = vGetpxBoosterParameters();
		
		
		/*pxLnaParameters->xElectricLimits.fCurrentMinimum				= usMinCurrentRangeLocal;
		pxLnaParameters->xElectricLimits.fCurrentMaximum				= usMaxCurrentRangeLocal;
		pxLnaParameters->xElectricLimits.fPowerMaximum					= fMaxPowerRangeLocal;*/
		pxBoosterParameters->xHpaPowersConfig.fHpaMinOutPowerForNextSteps = 550;
		//TODO
		//pxBoosterParameters->xHpaPowersConfig.fHpaBackFacetMin = 
		//pxBoosterParameters->xHpaPowersConfig.fHpaBackFacetMax = 
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fSlope =  xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fIntercept =  xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fIntercept;

		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fSlope =  xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fIntercept =  xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fIntercept;


		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fSlope =  xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fIntercept =  xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fIntercept;

		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fSlope =  xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fIntercept =  xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fIntercept;
		
		//mm1
		
	
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fIntercept =  xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fIntercept;
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fIntercept = xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fIntercept;
		

		
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fSlope = xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fIntercept = xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fIntercept;
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fSlope = xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fIntercept = xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fIntercept;
		

		//mm2
		
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fIntercept =  xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fIntercept;
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fIntercept = xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fIntercept;
		

		
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fSlope = xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fIntercept = xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fIntercept;
		
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fSlope = xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fSlope;
		pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fIntercept = xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fIntercept;
		
		
}
/* Exported functions ------------------------------------------------------- */
void vLnaCurrentControlInit( void )
{
	
	usMaxCurrentRangeLocal										= FACTORY_MAX_CURRENT;
	usMinCurrentRangeLocal										= FACTORY_MIN_CURRENT;
	fMaxPowerRangeLocal										= FACTORY_MAX_POWER;
	

	
	xDutyCycleCurrentOutputLna_1536_PwmOutput.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1LnaLaserDiodeControlCurrentPwm_1536 ];
	xDutyCycleCurrentOutputLna_1536_PwmOutput.fSlope 			= fCurrentControlSlopeScaleConstant[ e974LD1LnaLaserDiodeControlCurrentPwm_1536 ];
	
	xDutyCycleCurrentOutputLna_1553_PwmOutput.fIntercept   		= fCurrentControlInterceptScaleConstant[ e974LD1LnaLaserDiodeControlCurrentPwm_1553 ];
	xDutyCycleCurrentOutputLna_1553_PwmOutput.fSlope   		= fCurrentControlSlopeScaleConstant[ e974LD1LnaLaserDiodeControlCurrentPwm_1553 ];
	
	
	xDutyCycleCurrentOutputLna_1536_mAStp.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1LnaLaserDiodeControlCurrentmA_1536 ];
	xDutyCycleCurrentOutputLna_1536_mAStp.fSlope 			= fCurrentControlSlopeScaleConstant[ e974LD1LnaLaserDiodeControlCurrentmA_1536 ];
	
	xDutyCycleCurrentOutputLna_1553_mAStp.fIntercept   		= fCurrentControlInterceptScaleConstant[ e974LD1LnaLaserDiodeControlCurrentmA_1553 ];
	xDutyCycleCurrentOutputLna_1553_mAStp.fSlope   		= fCurrentControlSlopeScaleConstant[ e974LD1LnaLaserDiodeControlCurrentmA_1553 ];
	
	
	vUpdateCurrentControlLnaInternalConfig();

}
void vBoosterCurrentControlInit( void )
{
	
	xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentPwm_1536 ];
	xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentPwm_1536 ];

	xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentPwm_1553 ];
	xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentPwm_1553 ];
	
	
	xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentmA_1536 ];
	xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentmA_1536 ];
		
	xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentmA_1553 ];
	xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaSmStp1LaserDiodeControlCurrentmA_1553 ];
			
		// mm 1
	xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentPwm_1553 ];
	xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentPwm_1553 ];
	
	xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentPwm_1536 ];
	xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentPwm_1536 ];
	
	xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentmA_1553 ];
	xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentmA_1553 ];
	
	xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentmA_1536 ];
	xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp1LaserDiodeControlCurrentmA_1536 ];
	
	//mm2
	xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentPwm_1553 ];
	xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentPwm_1553 ];
	
	xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentPwm_1536 ];
	xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentPwm_1536 ];
	
	xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentmA_1553 ];
	xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentmA_1553 ];
	
	xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fIntercept 		= fCurrentControlInterceptScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentmA_1536 ];
	xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fSlope     		= fCurrentControlSlopeScaleConstant[ e974LD1HpaMmStp2LaserDiodeControlCurrentmA_1536 ];	
	
	
	  vUpdateCurrentControlHpaInternalConfig();
	  
}
/*------------------------------------------------------------------------------*/
void vCurrentOutputLnaConfigUpdate( void )
{
	
	xLnaParameters_t *pxLnaParameters;
	xLnaParameters_t xLnaParametersl;
	pxLnaParameters = vGetpxLnaParameters(&xLnaParametersl);
		
	usMaxCurrentRangeLocal									=pxLnaParameters->usMaxCurrentRange;
	xDutyCycleCurrentOutputLna_1536_PwmOutput.fSlope 		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fSlope;
	xDutyCycleCurrentOutputLna_1536_PwmOutput.fIntercept 		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fIntercept;

	xDutyCycleCurrentOutputLna_1553_PwmOutput.fSlope  		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fSlope;
	xDutyCycleCurrentOutputLna_1553_PwmOutput.fIntercept  		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fIntercept;
	
	
	
	xDutyCycleCurrentOutputLna_1536_mAStp.fSlope 		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fSlope;
	xDutyCycleCurrentOutputLna_1536_mAStp.fIntercept 		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fIntercept;

	xDutyCycleCurrentOutputLna_1553_mAStp.fSlope  		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fSlope;
	xDutyCycleCurrentOutputLna_1553_mAStp.fIntercept  		= pxLnaParameters->xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fIntercept;
	
}
/*------------------------------------------------------------------------------*/
void vCurrentOutputBoosterConfigUpdate( void )
{
	xBoosterParameters_t *pxBoosterParameters;
	pxBoosterParameters = vGetpxBoosterParameters( );
		
	xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fIntercept;
	xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fSlope 			= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fSlope;
	
	xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fIntercept;
	xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fSlope 			= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fSlope;

	xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fIntercept;
	xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fSlope 			= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fSlope;
	
	xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fIntercept;
	xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fSlope 			= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fSlope;
		
	
	//mm 1
	xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fIntercept;
	xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fSlope     		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fSlope;
	
	xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fIntercept;
	xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fSlope     		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fSlope;
	
	xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fIntercept;
	xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fSlope     		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fSlope;
	
	xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fIntercept;
	xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fSlope     		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fSlope;
	
	
	// mm2
	xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fIntercept 		=  pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fIntercept;
	xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fSlope     		=  pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fSlope;
	
	xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fIntercept 		=  pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fIntercept;
	xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fSlope     		=  pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fSlope;
	
	
	xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fIntercept;
	xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fSlope     		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fSlope;
		
	xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fIntercept 		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fIntercept;
	xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fSlope     		= pxBoosterParameters->xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fSlope;
}
/*---------------------------------------------------------------------------------------*/
eMpbError_t eCurrentControlUpdateHpa1( float fCurrent ) 
{
	xAmplifierDescriptor_t	*pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor = vGetxAmplifierDescriptor();

	xDutyCycleCurrentOutputScaling_t xDutyCyclePowerOutputScalingHpa1;
	uint32_t pfDutyCycle;

	eMpbError_t eMpbError;
	float fCurrentChannel_0 = 0.0f;
	
	
	if(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection == 1)
	{
		xDutyCyclePowerOutputScalingHpa1.fSlope = xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fSlope; 
		xDutyCyclePowerOutputScalingHpa1.fIntercept = xDutyCycleCurrentOutputHpa_1536_SmPwmStp.fIntercept;
				
	}
	else
	{
		xDutyCyclePowerOutputScalingHpa1.fSlope = xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fSlope;
		xDutyCyclePowerOutputScalingHpa1.fIntercept = xDutyCycleCurrentOutputHpa_1553_SmPwmStp.fIntercept;
				
				
	}
			
	eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmSmStp1, xDutyCyclePowerOutputScalingHpa1, fCurrent , &pfDutyCycle  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
			
	
	
	
	

	return eMpbError;	
}
/*----------------------------------------------------------------------*/
eMpbError_t eCurrentControlUpdateMmHpa1( float fCurrent )
{
	xAmplifierDescriptor_t	*pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor = vGetxAmplifierDescriptor();

	xDutyCycleCurrentOutputScaling_t xDutyCyclePowerOutputScalingMmHpa1;
	uint32_t pfDutyCycle;

	eMpbError_t eMpbError;
	float fCurrentChannel_0 = 0.0f;
	
	
	if(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection == 1)
	{
		xDutyCyclePowerOutputScalingMmHpa1.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fSlope;
		xDutyCyclePowerOutputScalingMmHpa1.fIntercept = xDutyCycleCurrentOutputHpaMMPwmStp1_1536.fIntercept;
		
	}
	else
	{
		xDutyCyclePowerOutputScalingMmHpa1.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fSlope;
		xDutyCyclePowerOutputScalingMmHpa1.fIntercept = xDutyCycleCurrentOutputHpaMMPwmStp1_1553.fIntercept;
		
		
	}
	
	eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmMmStp1, xDutyCyclePowerOutputScalingMmHpa1, fCurrent , &pfDutyCycle  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	
	
	
	

	return eMpbError;
}

/*----------------------------------------------------------------------*/
eMpbError_t eCurrentControlUpdateMmHpa2( float fCurrent )
{
	xAmplifierDescriptor_t	*pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor = vGetxAmplifierDescriptor();

	xDutyCycleCurrentOutputScaling_t xDutyCyclePowerOutputScalingMmHpa2;
	uint32_t pfDutyCycle;

	eMpbError_t eMpbError;
	float fCurrentChannel_0 = 0.0f;
	
	
	if(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection == 1)
	{
		xDutyCyclePowerOutputScalingMmHpa2.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fSlope;
		xDutyCyclePowerOutputScalingMmHpa2.fIntercept = xDutyCycleCurrentOutputHpaMMPwmStp2_1536.fIntercept;
		
	}
	else
	{
		xDutyCyclePowerOutputScalingMmHpa2.fSlope = xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fSlope;
		xDutyCyclePowerOutputScalingMmHpa2.fIntercept = xDutyCycleCurrentOutputHpaMMPwmStp2_1553.fIntercept;
		
		
	}
	
	eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmMmStp2, xDutyCyclePowerOutputScalingMmHpa2, fCurrent , &pfDutyCycle  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	
	
	
	

	return eMpbError;
}

/*---------------------------------------------------------------------------------------*/
eMpbError_t eCurrentControlUpdateLna( float  fCurrent)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
{
	
	xAmplifierDescriptor_t	*pxAmplifierDescriptor = NULL;
	pxAmplifierDescriptor = vGetxAmplifierDescriptor();
	
	

	
	eMpbError_t eMpbError;
	float fCurrentChannel_0 = 0.0f;
//	eBool_t bLnaIsWorking = eFalse;
	
	//fCurrentChannel_0 = fGetVoltage();
	//fCurrentChannel_0 = 1300;
	
	
	//eMpbError_t ePwmCurrentOutputSetCurrentmA( handle_t xStream, xDutyCycleCurrentOutputScaling_t xDutyCycleCurrentOutputScaling, float fCurrent, uint8_t *pfDutyCycle  );
	uint32_t pfDutyCycle;
	
	
	xDutyCycleCurrentOutputScaling_t xDutyCyclePowerOutputScalingLna;
	
	fCurrentChannel_0 = (float)pxAmplifierDescriptor->c406PacketControlDefinition.fSetGeneralSetpointOnLNA ;
//	bLnaIsWorking = (pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus == 1)? eTrue : eFalse; 
//	c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 == 1)? eTrue : eFalse;
	//402
	
	//if ACC
//	bLnaIsWorking = eTrue;
	//if(bLnaIsWorking == eTrue)
	//{
		if(pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection == 1)
		{
			xDutyCyclePowerOutputScalingLna.fSlope = xDutyCycleCurrentOutputLna_1536_PwmOutput.fSlope;
			xDutyCyclePowerOutputScalingLna.fIntercept = xDutyCycleCurrentOutputLna_1536_PwmOutput.fIntercept;
			//xDutyCycleCurrentOutputLna_1536_PwmStp
		}
		else
		{
			xDutyCyclePowerOutputScalingLna.fSlope = xDutyCycleCurrentOutputLna_1553_PwmOutput.fSlope;
			xDutyCyclePowerOutputScalingLna.fIntercept = xDutyCycleCurrentOutputLna_1553_PwmOutput.fIntercept;
			
			
		}
	
		eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmLnaStp, xDutyCyclePowerOutputScalingLna, fCurrent , &pfDutyCycle  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
	
//	}

	
		
	/*
	
		eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmSmStp1, xDutyCycleCurrentOutputHpaSmPwmStp, fCurrentChannel_0 * 33 , &pfDutyCycle  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		//eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmSmStp2, xDutyCycleCurrentOutputHpaSmPwmStp2, fCurrentChannel_0 * 33 , &pfDutyCycle  );
		//if( eMpbError != eSuccess )
		//{
		//	vMpblibsAssertParam( 0 );
		//}
		eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmMmStp1, xDutyCycleCurrentOutputHpaMMPwmStp1, fCurrentChannel_0 * 33 , &pfDutyCycle  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
		eMpbError = ePwmCurrentOutputSetCurrentmA(eHandlePwmMmStp2 , xDutyCycleCurrentOutputHpaMMPwmStp2, fCurrentChannel_0 * 33 , &pfDutyCycle  );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}	
	*/	
		/*
	eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmMmclck1, xDutyCycleCurrentOutputHpaMMPwmStp1, fCurrentChannel_0 * 33 , &pfDutyCycle  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmMmclck2, xDutyCycleCurrentOutputHpaMMPwmStp1, fCurrentChannel_0 * 33 , &pfDutyCycle  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}*/
		
	/* 980 diode */
	
	//if( ( pxLaserBeamDescriptor->xBeaconId == e980Beacon ) &&
	/*if( pxLaserBeamDescriptor->xLaserOperationMode[e980Beacon - 1].bLaserIsEnable == eTrue)
	{
		fCurrentChannel_1 = pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usActiveSetpoint;
		usCurrentChannelsP_1 = pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usCurrentSetpoint;
		fLowCurrentChannel_1 = pxLaserBeamDescriptor->usLowCurrent[  e980Beacon - 1 ];
		usThresholdCurrent 	= pxLaserBeamDescriptor->xElectricalVariablesStatus[e980Beacon - 1].usCurrentThresholdSetpoint ;
		usMaxThresholdCurrent = pxLaserBeamDescriptor->xMaxSetpointsAllowed.sMaxSetpointCurrent980;
		if( usCurrentChannelsP_1 > usMaxThresholdCurrent  )
		{
			usCurrentChannelsP_1 = usMaxThresholdCurrent;
			fCurrentChannel_1	= (float)usMaxThresholdCurrent;
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usActiveSetpoint = 		fCurrentChannel_1 ;
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usCurrentSetpoint = usCurrentChannelsP_1;
			
		}
		
		if( usCurrentChannelsP_1 < usThresholdCurrent   )
		{
			usCurrentChannelsP_1 = usThresholdCurrent;
			fCurrentChannel_1	= (float)usThresholdCurrent;
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usActiveSetpoint = 		fCurrentChannel_1 ;
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usCurrentSetpoint = usCurrentChannelsP_1;
		}
		
		//		if( fLowCurrentChannel_1 > usCurrentChannelsP_1)
		//		{
		//			usCurrentChannelsP_1 = fLowCurrentChannel_1;
		//		}
		
		if( usLowCurrentChannelsP_1 > usCurrentChannelsP_1)
		{
			fCurrentChannel_1 = usLowCurrentChannelsP_1;
			usCurrentChannelsP_1  = usLowCurrentChannelsP_1;
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usActiveSetpoint = 		usLowCurrentChannelsP_0 ;
			pxLaserBeamDescriptor->xElectricalVariablesStatus[ e980Beacon - 1 ].usCurrentSetpoint = usLowCurrentChannelsP_0;
			
		}
		
		
	}
	else
	{
		fCurrentChannel_1 = 0.0f;
		usCurrentChannelsP_1 = 0; //.0f;
		fLowCurrentChannel_1 = 0;
	}
	*/
	/*eMpbError = eCurrentOutputSetCurrentmA( eHandleLed2OutputVoltage, xDutyCycleCurrentOutputScalingLed2, fCurrentChannel_1, fLowCurrentChannel_1, &fLowVoltageconversionChannel_1, &fVoltageconversionChannel_1  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}*/
	
	
	
	//if( ACC_CONTROL_ENABLE)
	//{
		//	DAC_VoltagesPrint( usCurrentChannelsP_0, fVoltageconversionChannel_0, usCurrentChannelsP_1, fVoltageconversionChannel_1 );
//	}


	return eMpbError;
}


eMpbError_t eCurrentControlReset( void )
{
	//	xLaserBeamDescriptor_t *pxLaserBeamDescriptor;
	//	pxLaserBeamDescriptor = vGetLaserBeams( );
	eMpbError_t eMpbError = eSuccess;
	float fVoltageconversionChannel_0 = 0.0f;
	
	//float fLowVoltageconversionChannel_0 = 0.0f;
	//float fLowVoltageconversionChannel_1 = 0.0f;
	//float fVoltageconversionChannel_1 = 0.0f;
	float fCurrentChannel_0 = 0.0f;
	//float fCurrentChannel_1 = 0.0f;
	//uint16_t usCurrentChannelsP_0 = 0; //.0f;
	//uint16_t usCurrentChannelsP_1 = 0; //.0f;
	//	uint16_t usThresholdCurrent = 0;
	//float fLowCurrentChannel_0 = 0.0f;
	//float fLowCurrentChannel_1 = 0.0f;
	
	/* 940 diode */
	fCurrentChannel_0 = 0.0f;
	//	  usCurrentChannelsP_0 = 0; //.0f;
	
//	uint8_t pfDutyCycle;
//	eMpbError = ePwmCurrentOutputSetCurrentmA( eHandlePwmLnaStp, xDutyCycleCurrentOutputLnaPwmStp, fCurrentChannel_0 , &pfDutyCycle  );
	//eMpbError = ePwmCurrentOutputSetCurrentmA( eHandleLed1OutputVoltage, xDutyCycleCurrentOutputScalingLed1, fCurrentChannel_0, &pfDutyCycle  );
	
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
	
	
	/* 980 diode */

/*	fCurrentChannel_1 = 0.0f;
	//	usCurrentChannelsP_1 = 0; //.0f;

	eMpbError = eCurrentOutputSetCurrentmA( eHandleLed2OutputVoltage, xCurrentOutputScaling980Diode, fCurrentChannel_1, fLowCurrentChannel_1, &fLowVoltageconversionChannel_1, &fVoltageconversionChannel_1  );
	
	//	eMpbError = eCurrentOutputSetCurrentmA( eHandle980OutputVoltage, xCurrentOutputScaling980Diode, fCurrentChannel_1, fLowCurrentChannel_1, &fVoltageconversionChannel_1  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}*/
	
	


	return eMpbError;
}

/*---------------------------------------------------------------------------------*/
void vCurrentControlgetOutputScalingValues ( float *pfSlope, float *pfIntercep, float *pfGain, handle_t eBeaconId )
{
	//if( eBeaconId == e940Beacon)
//	{
	//	*pfSlope = xDutyCycleCurrentOutputScalingLed1.fSlope;
	//	*pfIntercep = xDutyCycleCurrentOutputScalingLed1.fIntercept;
		
//	}
/*	else if( eBeaconId ==  e980Beacon )
	{
		*pfSlope = xCurrentOutputScaling980Diode.fSlope;
		*pfIntercep = xCurrentOutputScaling980Diode.fIntercept;
		*pfGain = xCurrentOutputScaling980Diode.fCalibration;
		
		
	}*/
	

}
/*--------------------------------------------------------------------------------------*/
void vCurrentControlsetOutputScalingValues ( float fSlope, float fIntercep, float fGain, handle_t eBeaconId) //eBeaconIdUsedActually_t eBeaconId )
{
	/*xLaserBeamDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetLaserBeams( );
	
	if( eBeaconId ==  e940Beacon )
	{
		pxLaserBeamDescriptor->xCurrentOutput940.fIntercept  = fIntercep ;
		pxLaserBeamDescriptor->xCurrentOutput940.fSlope =  	fSlope ;
		pxLaserBeamDescriptor->xCurrentOutput940.fCalibration= fGain;
	}
	else if( eBeaconId == e980Beacon )
	{
		pxLaserBeamDescriptor->xCurrentOutput1545.fIntercept= fIntercep ;
		pxLaserBeamDescriptor->xCurrentOutput1545.fSlope =  	fSlope ;
		pxLaserBeamDescriptor->xCurrentOutput1545.fCalibration = fGain;
	}
	
	
	vCurrentOutputConfigUpdate();*/
}

eMpbError_t ePwmToCurrentConversion( eBool_t bWavelengthIs1536, uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	if(pusSetpointInmA != NULL)
	{
		
		eMpbError = eSuccess;
		
		if( bWavelengthIs1536 == eTrue)
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputLna_1536_mAStp.fSlope + xDutyCycleCurrentOutputLna_1536_mAStp.fIntercept;	
		}
		else
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputLna_1553_mAStp.fSlope + xDutyCycleCurrentOutputLna_1553_mAStp.fIntercept;	
		}
	}
	return eMpbError;
	
}

eMpbError_t ePwmToCurrentConversion_Hpa1( eBool_t bWavelengthIs1536, uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA )
{
	eMpbError_t eMpbError = eInvalidParameter;
		
	if(pusSetpointInmA != NULL)
	{
		eMpbError = eSuccess;
		if( bWavelengthIs1536 == eTrue)
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fSlope + xDutyCycleCurrentOutputHpa_1536_Sm_mAStp.fIntercept;
		}
		else
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fSlope + xDutyCycleCurrentOutputHpa_1553_Sm_mAStp.fIntercept;
		}
	}
	return eMpbError;
}

eMpbError_t ePwmToCurrentConversion_MmHpa1( eBool_t bWavelengthIs1536, uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	if(pusSetpointInmA != NULL)
	{
		eMpbError = eSuccess;
		if( bWavelengthIs1536 == eTrue)
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fSlope + xDutyCycleCurrentOutputHpaMM_mAStp1_1536.fIntercept;
		}
		else
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fSlope + xDutyCycleCurrentOutputHpaMM_mAStp1_1553.fIntercept;
		}
	}
	return eMpbError;
}
/*--------------------------------------------------------------------------------------*/
eMpbError_t ePwmToCurrentConversion_MmHpa2( eBool_t bWavelengthIs1536, uint16_t usSetpointInPwm, uint16_t *pusSetpointInmA )
{
	eMpbError_t eMpbError = eInvalidParameter;
	
	if(pusSetpointInmA != NULL)
	{	
		eMpbError = eSuccess;
		if( bWavelengthIs1536 == eTrue)
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fSlope + xDutyCycleCurrentOutputHpaMM_mAStp2_1536.fIntercept;
		}
		else
		{
			*pusSetpointInmA = usSetpointInPwm * xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fSlope + xDutyCycleCurrentOutputHpaMM_mAStp2_1553.fIntercept;
		}
	}
	return eMpbError;
}




