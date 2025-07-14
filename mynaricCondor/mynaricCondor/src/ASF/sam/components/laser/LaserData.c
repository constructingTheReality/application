/**
  * @file 			LaserData.c
  * @brief			LaserData.c source file.
  * @author			juan andres
  * @date			Created on 3/2/2023
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
#include "lib_crc.h"
#include "laserData.h"
#include "binaryInput.h"
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/* Private functions -------------------------------------------------------- */

//static xAmplifierDescriptor_t xLaserBeamGlobalDescriptor;
static xAmplifierDescriptor_t xAmplifierDescriptor;

//static xAmplifierParameters_t xAmplifierParameters;
//static xAmplifierParameters_t xAmplifierParametersImage;

static xCommonControlParameters_t xCommonControlParameters;
static xCommonControlParameters_t xCommonControlParametersImage;

static xLnaParameters_t xLnaParameters;
static xLnaParameters_t xLnaParametersImage;

static xBoosterParameters_t xBoosterParameters;
static xBoosterParameters_t xBoosterParametersImage;

static void svWriteCommonCoefficientesToRam(void);
static void svWriteLnaCoefficientesToRam(void);
static void svWriteBoosterCoefficientesToRam(void);

static void	svReadCommonCoefficients(eBool_t bReadFromRam);
static void	svReadLnaCoefficients(eBool_t bReadFromRam);
static void	svReadBoosterCoefficients(eBool_t bReadFromRam);



static void	svReadCommonCoefficients(eBool_t bReadFromRam)
{
	xInputScalingCommonControlExternalAdc_t xInputScalingCommonControlExternalAdc;
	
	if(bReadFromRam == eTrue)
	{
		memcpy(&xInputScalingCommonControlExternalAdc, &(xCommonControlParametersImage.xInputScalingCommonControlExternalAdc), sizeof(xInputScalingCommonControlExternalAdc_t) );
	}
	else
	{
		memcpy(&xInputScalingCommonControlExternalAdc, &(xCommonControlParameters.xInputScalingCommonControlExternalAdc), sizeof(xInputScalingCommonControlExternalAdc_t) );
	}
	
	
	
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF1_CH6_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingCommonControlExternalAdc.xExternalPdReference1.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF1_CH6_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingCommonControlExternalAdc.xExternalPdReference1.fIntercept;
	}	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_CASE_THERMISTOR1_CH20_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingCommonControlExternalAdc.xExternalCase_Thermistor1.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_CASE_THERMISTOR1_CH20_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingCommonControlExternalAdc.xExternalCase_Thermistor1.fIntercept;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF2_CH23_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingCommonControlExternalAdc.xExternalPdReference.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF2_CH23_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingCommonControlExternalAdc.xExternalPdReference.fIntercept;
	}
		
}

static void	svReadLnaCoefficients(eBool_t bReadFromRam)
{
	xInputScalingLnaAdc_t	xInputScalingLnaAdc;
	xOutputScalingLnaDac_t			xOutputScalingLnaDac;	
	xPidValues_t					xPidValues;
	xLosValues_t					xLosValues;
	xElectricLimits_t				xElectricLimits;

	if(bReadFromRam == eTrue)
	{
		memcpy(&xInputScalingLnaAdc, &(xLnaParametersImage.xInputScalingLnaAdc), sizeof(xInputScalingLnaAdc_t) );
		memcpy(&xOutputScalingLnaDac, &(xLnaParametersImage.xOutputScalingLnaDac), sizeof(xOutputScalingLnaDac_t) );
		memcpy(&xPidValues, &(xLnaParametersImage.xPidValuesLna), sizeof(xPidValues_t) );
		memcpy(&xElectricLimits, &(xLnaParametersImage.xElectricLimits), sizeof(xElectricLimits_t) );
		
	}
	else 
	{
		memcpy(&xInputScalingLnaAdc, &(xLnaParameters.xInputScalingLnaAdc), sizeof(xInputScalingLnaAdc_t) );
		memcpy(&xOutputScalingLnaDac, &(xLnaParameters.xOutputScalingLnaDac), sizeof(xOutputScalingLnaDac_t) );
		memcpy(&xPidValues, &(xLnaParameters.xPidValuesLna), sizeof(xPidValues_t) );
		memcpy(&xElectricLimits, &(xLnaParameters.xElectricLimits), sizeof(xElectricLimits_t) );
	}
	
	
	
	xAmplifierDescriptor.c411StatusDefinition.usNumberCoefStatus = xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient;
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaInputPower_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaInputPower_1536.fIntercept;
	}
	/*-----*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_INPUT_MONITOR_CH0_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaInputPower_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_INPUT_MONITOR_CH0_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaInputPower_1553.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_OUTPUT_MONITOR1_CH1_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_OUTPUT_MONITOR1_CH1_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_OUTPUT_MONITOR2_CH2_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_OUTPUT_MONITOR2_CH2_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fIntercept;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_BACKFACET_CH7_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_BACKFACET_CH7_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fIntercept;
	}
	/*  ADC 2 */
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_CURRENT_MONITOR_CH8_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_CURRENT_MONITOR_CH8_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fIntercept;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_THERMISTOR_CH12_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaSmld_Thermistor.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_THERMISTOR_CH12_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingLnaAdc.xExternalLnaSmld_Thermistor.fIntercept;
	}
	
	/*---outputs */
	/* output lma index */
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_PWM_STP_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fSlope;				
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_PWM_STP_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fIntercept;				
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_PWM_STP_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_PWM_STP_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fIntercept;
	}

	
	/*--*/
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_MA_STP_SLOPE)
		{
			xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fSlope;
		}
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_MA_STP_INTERCEPT)
		{
			xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fIntercept;
		}
		
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_MA_STP_SLOPE)
		{
			xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fSlope;
		}
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_MA_STP_INTERCEPT)
		{
			xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fIntercept;
		}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_LNA)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValues.fPGain ;				
		
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_LNA)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValues.fDGain ;				
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_LNA)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValues.fIGain ;				
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == LNA_MIN_CURRENT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xElectricLimits.fCurrentMinimum ;											
			
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == LNA_MAX_CURRENT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xElectricLimits.fCurrentMaximum ;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == LNA_MAX_POWER)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xElectricLimits.fPowerMaximum ;
	}
	
}

static void	svReadBoosterCoefficients(eBool_t bReadFromRam)
{
	xInputScalingBoosterExternalAdc_t	xInputScalingBoosterExternalAdc;
	xOutputScalingBoosterDac_t			xOutputScalingBoosterDac;
	xPidValues_t						xPidValuesSm;
	xPidValues_t						xPidValuesMm1;
	xPidValues_t						xPidValuesMm2;
	xPidValues_t						xPidValuesMm1Mm2;
	xLosValues_t						xLosHpaValues;
	xHpaPowersConfig_t					xHpaPowersConfig;
	xHpaLimitsConfig_t					xHpaLimitsConfig;
	xPumpTemperaturesLimits_t			xPumpTemperaturesLimits;
	
	if(bReadFromRam == eTrue)
	{
		memcpy(&xInputScalingBoosterExternalAdc, &(xBoosterParametersImage.xInputScalingBoosterExternalAdc ), sizeof(xInputScalingBoosterExternalAdc_t) );
		memcpy(&xOutputScalingBoosterDac, &(xBoosterParametersImage.xOutputScalingBoosterDac ), sizeof(xOutputScalingBoosterDac_t) );
		
		memcpy(&xPidValuesSm, &(xBoosterParametersImage.xPidSmValuesBooster ), sizeof(xPidValues_t) );
		memcpy(&xPidValuesMm1, &(xBoosterParametersImage.xPidMm1ValuesBooster ), sizeof(xPidValues_t) );
		memcpy(&xPidValuesMm2, &(xBoosterParametersImage.xPidMm2ValuesBooster ), sizeof(xPidValues_t) );
		memcpy(&xPidValuesMm1Mm2, &(xBoosterParametersImage.xPidMm1and2ValuesBooster ), sizeof(xPidValues_t) );
		
		memcpy(&xLosHpaValues, &(xBoosterParametersImage.xLosHpaValues ), sizeof(xLosValues_t) );
		memcpy(&xHpaPowersConfig, &(xBoosterParametersImage.xHpaPowersConfig ), sizeof(xHpaPowersConfig_t) );
		
		memcpy(&xHpaLimitsConfig, &(xBoosterParametersImage.xHpaLimitsConfig ), sizeof(xHpaLimitsConfig_t) );
		
		memcpy(&xPumpTemperaturesLimits, &(xBoosterParametersImage.xPumpTemperaturesLimits ), sizeof(xPumpTemperaturesLimits_t) );
		
		
	}
	else
	{
		memcpy(&xInputScalingBoosterExternalAdc, &(xBoosterParameters.xInputScalingBoosterExternalAdc), sizeof(xInputScalingBoosterExternalAdc_t) );
		memcpy(&xOutputScalingBoosterDac, &(xBoosterParameters.xOutputScalingBoosterDac), sizeof(xOutputScalingBoosterDac_t) );
		
		memcpy(&xPidValuesSm, &(xBoosterParameters.xPidSmValuesBooster), sizeof(xPidValues_t) );
		memcpy(&xPidValuesMm1, &(xBoosterParameters.xPidMm1ValuesBooster ), sizeof(xPidValues_t) );
		memcpy(&xPidValuesMm2, &(xBoosterParameters.xPidMm2ValuesBooster ), sizeof(xPidValues_t) );		
		memcpy(&xPidValuesMm1Mm2, &(xBoosterParameters.xPidMm1and2ValuesBooster ), sizeof(xPidValues_t) );
		
		memcpy(&xLosHpaValues, &(xBoosterParameters.xLosHpaValues), sizeof(xLosValues_t) );
		memcpy(&xHpaPowersConfig, &(xBoosterParameters.xHpaPowersConfig ), sizeof(xHpaPowersConfig_t) );
		memcpy(&xHpaLimitsConfig, &(xBoosterParameters.xHpaLimitsConfig ), sizeof(xHpaLimitsConfig_t) );
		memcpy(&xPumpTemperaturesLimits, &(xBoosterParameters.xPumpTemperaturesLimits ), sizeof(xPumpTemperaturesLimits_t) );
	}
	
	xAmplifierDescriptor.c411StatusDefinition.usNumberCoefStatus = xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient;
	
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fIntercept;
	}
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1553_INPUT_MONITOR_CH3_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1553_INPUT_MONITOR_CH3_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fIntercept;
	}
	
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1536_CH4_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1536_CH4_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fIntercept;
	}
	
	/*--------------------------*/		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1536_CH5_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1536_CH5_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fIntercept;
	}
	
	/*--------------------------*/
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1553_CH4_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1553_CH4_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fIntercept;
	}
	
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1553_CH5_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1553_CH5_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fIntercept;
	}


	/*adc 2*/

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_CURRENT_MONITOR_CH9_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_CURRENT_MONITOR_CH9_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR1_CH10_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR1_CH10_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR2_CH11_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR2_CH11_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fIntercept;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_THERMISTOR_CH13_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaSmld_Thermistor.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_THERMISTOR_CH13_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaSmld_Thermistor.fIntercept;
	}


	/*--------------------------*/
	/* adc 3 */
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR1_CH16_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor1.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR1_CH16_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor1.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR2_CH17_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor2.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR2_CH17_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor2.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR3_CH18_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor3.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR3_CH18_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor3.fIntercept;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR4_CH19_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor4.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR4_CH19_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor4.fIntercept;
	}


	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_BACKFACET_CH22_SLOPE)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_BACKFACET_CH22_INTERCEPT)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fIntercept;
	}
	
	/* output */
	
	//hpa sm
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1536_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fSlope;
		
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1536_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fIntercept;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1553_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fSlope;
		
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1553_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fIntercept;
	}
	
//#define 						( 68 )
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1536_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fSlope ; 
	}
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1536_INTERCEPT_)
		{
			xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fIntercept ; 
		}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1553_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fSlope;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1553_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fIntercept;
	}
	

//hpa mm1
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1536_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1536_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fIntercept;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1553_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1553_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fIntercept;
	}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1536_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1536_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fIntercept;
	}
		
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1553_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1553_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fIntercept;
	}
	
	//hpa mm2

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1536_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1536_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fIntercept;
	}	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1553_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1553_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fIntercept;
	}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1536_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1536_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fIntercept;
	}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1553_SLOPE_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fSlope;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1553_INTERCEPT_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fIntercept;
	}

/* pid*/
					
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_SM)
	{	
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesSm.fPGain ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_SM)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesSm.fDGain ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_SM)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesSm.fIGain ;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_MM1)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesMm1.fPGain ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_MM1)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesMm1.fDGain ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_MM1)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesMm1.fIGain ;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_MM2)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesMm2.fPGain ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_MM2)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesMm2.fDGain ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_MM2)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xPidValuesMm2.fIGain ;
	}	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_LOS_CLEAR)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = xLosHpaValues.fLosClear ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_LOS_SET_)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  xLosHpaValues.fLosSet ;
	}


	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MIN_POWER_FOR_SECOND_STEP)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  xHpaPowersConfig.fHpaMinOutPowerForNextSteps;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MIN_BACKFACET)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  xHpaPowersConfig.fHpaBackFacetMin;
	}
		
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_BACKFACET)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  xHpaPowersConfig.fHpaBackFacetMax;
	}
	
	
	
	
	/*---*/
	
		/*--*/
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_CURRENT_SM1)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	=	xHpaLimitsConfig.usMaxHpaCurrentSM_mA ;
	}
		
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_NOMINAL_CURRENT_POURCENTAGE_SM1 )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	=	xHpaLimitsConfig.usNominalCurrentPourcentage_sM ;
	}
		

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient ==  HPA_MAX_CURRENT_MM1)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	=	xHpaLimitsConfig.usMaxHpaCurrentMM1_mA  ;
	}
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient ==  HPA_MAX_CURRENT_MM2)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	=	xHpaLimitsConfig.usMaxHpaCurrentMM2_mA  ;
	}
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_LH_LEVEL_MAX_IN_RAW )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	=	xHpaLimitsConfig.usMax_Lh_level_raw  ;
	}
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_HH_LEVEL_MIN_IN_RAW )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xHpaLimitsConfig.usMin_Hh_level_raw  ;
	}
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_MM1_MM2 )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xPidValuesMm1Mm2.fPGain  ;
	}	
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_MM1_MM2 )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xPidValuesMm1Mm2.fDGain  ;
	}
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_MM1_MM2 )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xPidValuesMm1Mm2.fIGain  ;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_CURRENT_STAGE_MM1 )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA  ;
	}	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_CURRENT_STAGE_MM2 )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA  ;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_HIGH_TEMP_LIMIT )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureHighAlarmLimit  ;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_VERY_HIGH_TEMP_LIMIT )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureVeryHighAlarmLimit  ;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_LOW_TEMP_LIMIT )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureLowAlarmLimit  ;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_VERY_LOW_TEMP_LIMIT )
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient	= xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureVeryLowAlarmLimit  ;
	}
			
		
	/*
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == )
	{
		xBoosterParametersImage.xLosHpaValues.fLosClear = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == )
	{
		xBoosterParametersImage.xLosHpaValues.fLosSet = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	*/
	
}

	/* pid
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_LNA)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  1;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_LNA)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  1;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_LNA)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  1;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  1;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  1;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER)
	{
		xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient =  1;
	}		*/				

static void svWriteCommonCoefficientesToRam(void)
{
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF1_CH6_SLOPE)
	{
		xCommonControlParametersImage.xInputScalingCommonControlExternalAdc.xExternalPdReference1.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF1_CH6_INTERCEPT)
	{
		xCommonControlParametersImage.xInputScalingCommonControlExternalAdc.xExternalPdReference1.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_CASE_THERMISTOR1_CH20_SLOPE)
	{
		xCommonControlParametersImage.xInputScalingCommonControlExternalAdc.xExternalCase_Thermistor1.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_CASE_THERMISTOR1_CH20_INTERCEPT)
	{
		xCommonControlParametersImage.xInputScalingCommonControlExternalAdc.xExternalCase_Thermistor1.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	/*--------------------------*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF2_CH23_SLOPE)
	{
		xCommonControlParametersImage.xInputScalingCommonControlExternalAdc.xExternalPdReference.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_PD_REF2_CH23_INTERCEPT)
	{
		xCommonControlParametersImage.xInputScalingCommonControlExternalAdc.xExternalPdReference.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
}


static void svWriteLnaCoefficientesToRam(void)
{
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaInputPower_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaInputPower_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_INPUT_MONITOR_CH0_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaInputPower_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_INPUT_MONITOR_CH0_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaInputPower_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_OUTPUT_MONITOR1_CH1_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_OUTPUT_MONITOR1_CH1_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaOutputPower1_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_OUTPUT_MONITOR2_CH2_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_OUTPUT_MONITOR2_CH2_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaOutputPower2_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_BACKFACET_CH7_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_BACKFACET_CH7_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaSm_ld_Bfm.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	/*  ADC 2 */
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_CURRENT_MONITOR_CH8_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_CURRENT_MONITOR_CH8_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExLnaSingleModeldCurrentMonitor.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_THERMISTOR_CH12_SLOPE)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaSmld_Thermistor.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_SM_THERMISTOR_CH12_INTERCEPT)
	{
		xLnaParametersImage.xInputScalingLnaAdc.xExternalLnaSmld_Thermistor.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	/* output lma index */	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_PWM_STP_SLOPE)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
		//.xInputScalingLnaExternalAdc.xExternalLnaSmld_Thermistor.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_PWM_STP_INTERCEPT)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
		
	}


	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_PWM_STP_SLOPE)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_PWM_STP_INTERCEPT)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentPwm_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	/*---*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_MA_STP_SLOPE)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
		//.xInputScalingLnaExternalAdc.xExternalLnaSmld_Thermistor.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1536_MA_STP_INTERCEPT)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
		
	}


	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_MA_STP_SLOPE)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_LNA_1553_MA_STP_INTERCEPT)
	{
		xLnaParametersImage.xOutputScalingLnaDac.xOutputLnaLaserDiodeControlCurrentmA_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	
	/*---*/
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_LNA)
	{
		xLnaParametersImage.xPidValuesLna.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	
	}	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_LNA)
	{
		xLnaParametersImage.xPidValuesLna.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_LNA)
	{
		xLnaParametersImage.xPidValuesLna.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	/*---*/
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == LNA_MIN_CURRENT)
	{
		xLnaParametersImage.xElectricLimits.fCurrentMinimum = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == LNA_MAX_CURRENT)
	{
		xLnaParametersImage.xElectricLimits.fCurrentMaximum = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == LNA_MAX_POWER)
	{
		xLnaParametersImage.xElectricLimits.fPowerMaximum = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
		
		
	
	
}

static void svWriteBoosterCoefficientesToRam(void)
{
	
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1553_INPUT_MONITOR_CH3_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_1553_INPUT_MONITOR_CH3_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaInputPower_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	

		
		
	/*--------------------------*/
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1553_CH4_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1553_CH4_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_lm.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	/*--------------------------*/
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1553_CH5_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1553_CH5_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1553_hm.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
		/*--------------------------*/
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1536_CH4_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1536_CH4_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_lm.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	/*--------------------------*/

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1536_CH5_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1536_CH5_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaOutputPower_1536_hm.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}		
		
		
	
	
	
	/*  ADC 2 */
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_CURRENT_MONITOR_CH9_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_CURRENT_MONITOR_CH9_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExHpaSingleModeld_CurrentMonitor.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR1_CH10_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR1_CH10_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor1.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR2_CH11_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR2_CH11_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExHpaMultiModeld_CurrentMonitor2.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_THERMISTOR_CH13_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaSmld_Thermistor.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_THERMISTOR_CH13_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaSmld_Thermistor.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	/* adc 3 */
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR1_CH16_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor1.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR1_CH16_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor1.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR2_CH17_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor2.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR2_CH17_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor2.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR3_CH18_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor3.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR3_CH18_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor3.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR4_CH19_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor4.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_THERMISTOR4_CH19_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor4.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_BACKFACET_CH22_SLOPE)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_BACKFACET_CH22_INTERCEPT)
	{
		xBoosterParametersImage.xInputScalingBoosterExternalAdc.xExternalHpaSm_ld_Bfm.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
/* output */

//hpa sm
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1536_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1536_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1553_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_PWM_STP_1553_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1536_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1536_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1553_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_SM_MA_STP_1553_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	
	
	
//hpa mm1
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1536_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1536_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1553_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1553_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1536_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1536_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1553_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP1_1553_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
		
	
	
	
	
	///hpa mm2

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1536_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1536_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1553_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1553_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1536_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1536_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1553_SLOPE_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fSlope = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INDEX_FOR_CALIB_HPA_MM_MA_STP2_1553_INTERCEPT_)
	{
		xBoosterParametersImage.xOutputScalingBoosterDac.xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553.fIntercept = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	

	/* pid*/

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_SM)
	{
		xBoosterParametersImage.xPidSmValuesBooster.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_SM)
	{
		xBoosterParametersImage.xPidSmValuesBooster.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_SM)
	{
		xBoosterParametersImage.xPidSmValuesBooster.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_MM1)
	{
		xBoosterParametersImage.xPidMm1ValuesBooster.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_MM1)
	{
		xBoosterParametersImage.xPidMm1ValuesBooster.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_MM1)
	{
		xBoosterParametersImage.xPidMm1ValuesBooster.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_MM2)
	{
		xBoosterParametersImage.xPidMm2ValuesBooster.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_MM2)
	{
		xBoosterParametersImage.xPidMm2ValuesBooster.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_MM2)
	{
		xBoosterParametersImage.xPidMm2ValuesBooster.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_LOS_CLEAR)
	{
		xBoosterParametersImage.xLosHpaValues.fLosClear = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_LOS_SET_)
	{
		xBoosterParametersImage.xLosHpaValues.fLosSet = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
														   
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MIN_POWER_FOR_SECOND_STEP)
	{
		xBoosterParametersImage.xHpaPowersConfig.fHpaMinOutPowerForNextSteps = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MIN_BACKFACET)
	{
		xBoosterParametersImage.xHpaPowersConfig.fHpaBackFacetMin = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_BACKFACET)
	{
		xBoosterParametersImage.xHpaPowersConfig.fHpaBackFacetMax = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	/*--*/
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_CURRENT_SM1)
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMaxHpaCurrentSM_mA = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_NOMINAL_CURRENT_POURCENTAGE_SM1 )
	{
		xBoosterParametersImage.xHpaLimitsConfig.usNominalCurrentPourcentage_sM = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient ==  HPA_MAX_CURRENT_MM1)
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMaxHpaCurrentMM1_mA = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient ==  HPA_MAX_CURRENT_MM2)
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMaxHpaCurrentMM2_mA = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_LH_LEVEL_MAX_IN_RAW )
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMax_Lh_level_raw = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_HH_LEVEL_MIN_IN_RAW )
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMin_Hh_level_raw = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER_MM1_MM2 )
	{
		xBoosterParametersImage.xPidMm1and2ValuesBooster.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER_MM1_MM2 )
	{
		xBoosterParametersImage.xPidMm1and2ValuesBooster.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}		
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER_MM1_MM2 )
	{
		xBoosterParametersImage.xPidMm1and2ValuesBooster.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_CURRENT_STAGE_MM1 )
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMaxHpaCurrentStageMM1_mA = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == HPA_MAX_CURRENT_STAGE_MM2 )
	{
		xBoosterParametersImage.xHpaLimitsConfig.usMaxHpaCurrentStageMM2_mA = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_HIGH_TEMP_LIMIT )
	{
		xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureHighAlarmLimit = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	 
	 else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_VERY_HIGH_TEMP_LIMIT )
	 {
		 xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureVeryHighAlarmLimit = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	 }
	 
	 else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_LOW_TEMP_LIMIT )
	 {
		 xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureLowAlarmLimit = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	 }
	 
	 else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PUMP_VERY_LOW_TEMP_LIMIT )
	 {
		 xBoosterParametersImage.xPumpTemperaturesLimits.fPumpTemperatureVeryLowAlarmLimit = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	 }
	 else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == CASE_HIGH_TEMP_LIMIT )
	 {
		 xBoosterParametersImage.xPumpTemperaturesLimits.fUnitBaseTemperatureHighAlarmLimit = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	 }	  
	 else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == CASE_LOW_TEMP_LIMIT )
	 {
		xBoosterParametersImage.xPumpTemperaturesLimits.fUnitBaseTemperatureLowAlarmLimit = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	 }	
	
}


	/* pid
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_LNA)
	{
		xAmplifierParametersImage.xPidValuesLna.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_LNA)
	{
		xAmplifierParametersImage.xPidValuesLna.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_LNA)
	{
		xAmplifierParametersImage.xPidValuesLna.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}

	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == PROPORCIONAL_FACTOR_BOOSTER)
	{
		xAmplifierParametersImage.xPidValuesBooster.fPGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}	
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == DERIVATIVE_FACTOR_BOOSTER)
	{
		xAmplifierParametersImage.xPidValuesBooster.fDGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
	
	else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient == INTEGRAL_FACTOR_BOOSTER)
	{
		xAmplifierParametersImage.xPidValuesBooster.fIGain = xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient;
	}
}*/
	
	
void vLaserInitBooster(void)
{
	/* 402 */
	
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver2IsPresent = eTrue; //52
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver3IsPresent = eTrue; // 54
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver2IsEnabled = eFalse; //53
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver3IsEnabled = eFalse; //55
	
	
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterInputPowerLimitAlarmStatus =0;					/*  icd 2.09 page 75. table 28 bit 12*/
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterOpticalOutPowerLimitAlarmStatus = 0;				/*  icd 2.09 page 75. table 28 bit 10*/
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterCurrentLimitAlarmStatus = 0;
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver2AlarmFlag = 0;
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bCurrentBoosterDriver3AlarmFlag = 0;
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterMode	= 0;										/* acc  icd 2.09 page 77. table 28 */
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection =0;								/* acc  icd 2.09 page 77. table 28 */
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserSingleModeStatus = 0;					/* acc  icd 2.09 page 77. table 28 */
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode1Status = 0;					/* acc  icd 2.09 page 77. table 28 */
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode2Status = 0;					/* acc  icd 2.09 page 77. table 28 */
	//xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = 0;					/* acc  icd 2.09 page 77. table 28 */
	
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmStatusGlobalValue = 0;
	
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver2IsEnabled  = 0;
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver3IsEnabled  = 0;
	
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver3IsPresent  = 0;
	xAmplifierDescriptor.c402StatusDefinition.bBoosterLaserDriver2IsPresent  = 0;
	
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor1IsPresent  = 1;
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor2IsPresent  = 1;
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor3IsPresent  = 1;
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor4IsPresent  = 1;
	
		
		
	//eMpbCan402Encode(&xAmplifierDescriptor.c402StatusDefinition);	
	
	/* 414*/	
	xAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower	= -10.0f;		/*  icd 2.09 page 80. table 28*/ 
	xAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower = 0.0f;			/*  0 means disabled. icd 2.09 page 80. table 28*/
	
	/*408*/
	xAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput = -10.0f;   /*  icd 2.09 page 78. table 28*/
	xAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerInput = 5.3f;    /*  icd 2.09 page 78. table 28*/
	 
	xAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput = 15.5f;		/*  icd 2.09 page 79. table 28*/
	xAmplifierDescriptor.c408StatusDefinition.fBoosterSetStatusAlarmHighLimitForPowerOutput = 38.0f;	/*  icd 2.09 page 79. table 28*/

	/* 403*/
	xAmplifierDescriptor.c403StatusDefinition.fBoosterPowerInputAlarmLowLimit = -10.0f;					/*  icd 2.09 page 77. table 28*/
	xAmplifierDescriptor.c403StatusDefinition.fBoosterPowerInputAlarmHighLimit = 6.0f;					/*  icd 2.09 page 77. table 28*/
	
	xAmplifierDescriptor.c403StatusDefinition.fBoosterPowerOutputAlarmLowLimit = 15.5f;					/*  icd 2.09 page 77. table 28*/
	xAmplifierDescriptor.c403StatusDefinition.fBoosterPowerOutputAlarmHighLimit = 38.0f;				/*  icd 2.09 page 77. table 28*/
	
		
	/*406*/
	xAmplifierDescriptor.c406PacketControlDefinition.fSetCurrentOnLaserPump1OnBoosterInAcc = 0.0f;			/*  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.fSetCurrentOnLaserPump2OnBoosterInAcc = 0.0f;			/*  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.fSetCurrentOnLaserPump3OnBoosterInAcc = 0.0f;			/*  icd 2.09 page 77. table 28 */
	
	
	xAmplifierDescriptor.c406PacketControlDefinition.fSetSetPointPowerForBoosterInApc = 16.0f;				/*  icd 2.09 page 77. table 28 */				
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetBoosterControlMode = 0;  /*  ACC  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1 = 0;	/*  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2 = 0;	/*  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3 = 0;	/*  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetTxChannelOnBooster = 0;     /*  icd 2.09 page 78. table 28 */
	xAmplifierDescriptor.c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
	

	

	
	/* 401 */
	xAmplifierDescriptor.c401StatusDefinition.fLaserPump1BoosterCurrent = 0.0f;		/*  icd 2.09 page 75. table 28 */
	xAmplifierDescriptor.c401StatusDefinition.fLaserPump2BoosterCurrent  = 0.0f;	/*  icd 2.09 page 75. table 28 */
	xAmplifierDescriptor.c401StatusDefinition.fLaserPump3BoosterCurrent = 0.0f;		/*  icd 2.09 page 75. table 28 */
	xAmplifierDescriptor.c401StatusDefinition.fLaserPump4LnaCurrent = 0.0f;			/*  icd 2.09 page 75. table 28 */
	
	/* 409 */
	xAmplifierDescriptor.c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump  = 0.0f;			/*  icd 2.09 page 79. table 28 */
	xAmplifierDescriptor.c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump = 2000.0f;        /*  icd 2.09 page 79. table 28 */
	
//	xAmplifierDescriptor.c409StatusDefinition.fSetTemperatureAlarmLowLimitForUnitBase  = -20.0f;			/*  icd 2.09 page 79. table 28 */
//	xAmplifierDescriptor.c409StatusDefinition.fSetTemperatureAlarmHighLimitForUnitBase  = 80.0f;			/*  icd 2.09 page 79. table 28 */
		
		
	
	
	/* 407 */	
	xAmplifierDescriptor.c407PacketControlDefinition.fBoosterCurrent2LowAlarmLimit = 0.0f;					/*  icd 2.09 page 78. table 28 */
	xAmplifierDescriptor.c407PacketControlDefinition.fBoosterCurrent2HighAlarmLimit = 100.0f;				/*  icd 2.09 page 78. table 28 */
	
	xAmplifierDescriptor.c407PacketControlDefinition.fBoosterCurrent3LowAlarmLimit = 0.0f;					/*  icd 2.09 page 78. table 28 */
	xAmplifierDescriptor.c407PacketControlDefinition.fBoosterCurrent3HighAlarmLimit = 100.0f;				/*  icd 2.09 page 78. table 28 */
	
	/* 404*/
	xAmplifierDescriptor.c404StatusDefinition.fBoostHighLimitCurrentAlarm = 32768.0f;						/*  icd 2.09 page 77. table 28 */
	xAmplifierDescriptor.c404StatusDefinition.fBoostLowLimitCurrentAlarm = 0.0f;							/*  icd 2.09 page 77. table 28 */
	
	/* 40A */	
	xAmplifierDescriptor.c40AStatusDefinition.fBoosterDriver2CurrentLowAlarmLimit = 0.0f;					/*  icd 2.09 page 79. table 28 */
	xAmplifierDescriptor.c40AStatusDefinition.fBoosterDriver2CurrentHighAlarmLimit = 32768.0f;				/*  icd 2.09 page 79. table 28 */
	
	xAmplifierDescriptor.c40AStatusDefinition.fBoosterDriver3CurrentLowAlarmLimit = 0.0f;					/*  icd 2.09 page 79. table 28 */
	xAmplifierDescriptor.c40AStatusDefinition.fBoosterDriver3CurrentHighAlarmLimit = 32768.0f;				/*  icd 2.09 page 79. table 28 */
	
	
	
	xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureHighAlarmLimit = 40.0f;
	xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureLowAlarmLimit = 1.0f;
	
	xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureVeryHighAlarmLimit = 60.0f;
	xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureVeryLowAlarmLimit = -10.0f; 
	
	xAmplifierDescriptor.xPumpTemperaturesLimits.fUnitBaseTemperatureHighAlarmLimit = 50.0f;
	xAmplifierDescriptor.xPumpTemperaturesLimits.fUnitBaseTemperatureLowAlarmLimit = -10.0f;
		
	//xAmplifierDescriptor.xHpaLosStates = eValidAndClear;
	eMpbLosDetectorInit(&(xAmplifierDescriptor.xHpaLosStates));
	
}

void vLaserInitLna(void)
{
	/* 402 */
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPhotodiodeIsPresent = 1;					/*  icd 2.09 page 75. table 28 0x402 bit 1*/
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaOpticalPowerOutputLimitAlarmStatus = 0;			/*  icd 2.09 page 75. table 28 0x402 bit 8*/
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus = 0;						/*  icd 2.09 page 75. table 28 0x402 bit 9*/
	
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode = 0;										/*  icd 2.09 page 75. table 28 0x402 bit 5 mode ACC */
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = 0;							/*  icd 2.09 page 75. table 28 0x402 bit 6 rx 1553 */
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = 0;						/*  icd 2.09 page 75. table 28 0x402 bit 3 */
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaInputPowerLimitAlarmStatus = 0;					/*  icd 2.09 page 75. table 28 0x402 bit 2 */
	
//	xAmplifierDescriptor.c402StatusDefinition.fLnaOpticalInputPowerValue = -50.0f;
	
	/* 403*/
	xAmplifierDescriptor.c403StatusDefinition.fLnaPowerInputAlarmLowLimit = -50.0f;				/*  icd 2.09 page 23. table 28 0x403 */
	xAmplifierDescriptor.c403StatusDefinition.fLnaPowerInputAlarmHighLimit = -20.0f;			/*  icd 2.09 page 23. table 28 0x403 */
	xAmplifierDescriptor.c403StatusDefinition.fLnaPowerOutputAlarmLowLimit = -15.5f;			/*  icd 2.09 page 23. table 28 0x403 */
	xAmplifierDescriptor.c403StatusDefinition.fLnaPowerOutputAlarmHighLimit = 0.5f;				/*  icd 2.09 page 23. table 28 0x403 */
	
	/* 404*/
	xAmplifierDescriptor.c404StatusDefinition.fLnaLowLimitCurrentAlarm = 0.0f;					/*  icd 2.09 page 77. table 28 0x404 0..15 */
	xAmplifierDescriptor.c404StatusDefinition.fLnaHighLimitCurrentAlarm = 32768.0f;				/*  icd 2.09 page 77. table 28 0x404 16..31 */

	/*406*/
	xAmplifierDescriptor.c406PacketControlDefinition.fSetGeneralSetpointOnLNA = 0;			   /* By default LNA CURRENT set to 0% bits 38-47*/
	
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode = 0;  /* 406 bit 5 By default LNA in ACC */
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucSetRxChannelOnLna =	0;	/* 406 bit 6 Rx channel 1553 */
	xAmplifierDescriptor.c406PacketControlDefinition.Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 = 0;  /* 406 bit 3 By default LNA is disabled */
	
	
	xAmplifierDescriptor.c406PacketControlDefinition.ucResetRequest = DO_NOTHING;
	
	/*408*/
	xAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerInput = -50.0f;					/* 408 bits 0..7*/
	xAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerInput = -20.0f;				/* 408 bits 8..15*/
	
	xAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmLowLimitForPowerOutput = -15.5f;				/* 408 bits 16..23*/
	xAmplifierDescriptor.c408StatusDefinition.fLnaSetStatusAlarmHighLimitForPowerOutput = 0.5f;					/* 408 bits 24..31*/
	
	/* 409 */
	xAmplifierDescriptor.c409StatusDefinition.fSetLnaAlarmLowLimitForCurrentPump = 0.0f;						/* 409 bits 0..9*/
	xAmplifierDescriptor.c409StatusDefinition.fSetLnaAlarmHighLimitForCurrentPump = 100.0f;						/* 408 bits 10..19*/
	
	/* 414*/
	xAmplifierDescriptor.c414StatusDefinition.fLnaOpticalInputtPower = -50.0f;									/* 414 20..29  0 ? */
	xAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower =  0.0f;									/*414 30..39*/

	xAmplifierDescriptor.bWriteCommonMemoryNeeded = eFalse;
	xAmplifierDescriptor.bWriteLnaMemoryNeeded = eFalse;
	xAmplifierDescriptor.bWriteBoosterMemoryNeeded = eFalse;
	xAmplifierDescriptor.bWriteAllMemoryNeeded = eFalse;
	
	
		
	//xLnaParameters.fLosClear = -51.0f;
	//xLnaParameters.fLosSet = -49.0f;
		
}

void vLaserDataInit(void)
{
	vLaserInitBooster();
	vLaserInitLna();
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTemporaryDisableFunction = 0;			/*  icd 2.09 page 24. table 28 0x402 bit 14 */
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bUnitBaseTemperatureAlarmStatus = 0;		/*  icd 2.09 page 24. table 28 0x402 bit 13 */
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor1IsPresent = eTrue;																	/*  icd 2.09 page 24. table 28 0x402 bit 48 */
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor2IsPresent =  eTrue;																/*  icd 2.09 page 24. table 28 0x402 bit 49 */
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor3IsPresent =  eTrue;																/*  icd 2.09 page 24. table 28 0x402 bit 50 */
	xAmplifierDescriptor.c402StatusDefinition.bTemperatureSensor4IsPresent =  eTrue;																/*  icd 2.09 page 24. table 28 0x402 bit 51 */
	
	xAmplifierDescriptor.xInternalAlarms.usGlobalValue = 0;
	
	xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor1 = -40.0f;		/*  icd 2.09 page 24. table 28 0x402 bit 20-26 */
	xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor2 = -40.0f;		/*  icd 2.09 page 24. table 28 0x402 bit 27-33 */
	xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor3 = -40.0f;		/*  icd 2.09 page 24. table 28 0x402 bit 34-40 */
	xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor4 = -40.0f;		/*  icd 2.09 page 24. table 28 0x402 bit 41-47  */
	
	xAmplifierDescriptor.c405Definition.ucIdCompany = (uint8_t) MANUFACTURER_NUMBER;
	xCommonControlParameters.ulSerialNumber = (uint8_t) SERIAL_NUMBER;
	xCommonControlParameters.cSoftwareVersion[0] = (uint8_t) DEF_VERSION_FIRMWARE_MAJOR;
	xCommonControlParameters.cSoftwareVersion[1] = (uint8_t) DEF_VERSION_FIRMWARE_MINOR;
	xCommonControlParameters.cSoftwareVersion[2] = (uint8_t) DEF_VERSION_FIRMWARE_PATCH;
	
	xAmplifierDescriptor.c405Definition.ulUnitSerialNumber = xCommonControlParameters.ulSerialNumber;
	xAmplifierDescriptor.c405Definition.ucFirmwareVersionMajor = (uint8_t) DEF_VERSION_FIRMWARE_MAJOR;
	xAmplifierDescriptor.c405Definition.ucFirmwareVersionMinor = (uint8_t) DEF_VERSION_FIRMWARE_MINOR;
	xAmplifierDescriptor.c405Definition.ucFirmwareVersionPatch = (uint8_t) DEF_VERSION_FIRMWARE_PATCH;
	
	xAmplifierDescriptor.c010Definition.bPortSelector = 0;
	xAmplifierDescriptor.c407PacketControlDefinition.bSaveSettingsInNvm = eFalse;


	xAmplifierDescriptor.c409StatusDefinition.fSetTemperatureAlarmLowLimitForUnitBase = -30.0f;
	xAmplifierDescriptor.c409StatusDefinition.fSetTemperatureAlarmHighLimitForUnitBase = 70.0f;
	//xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.	
		
	
	xAmplifierDescriptor.c410StatusDefinition.CoeficientOperation = DO_OPERATION_NOTHING;
	xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient = 4096;
	xAmplifierDescriptor.c410StatusDefinition.fWriteValueCoefficient = 0.0f;
	
	
	xAmplifierDescriptor.c411StatusDefinition.fReadValueCalibrationCoefficient = 0.0f;
	xAmplifierDescriptor.c411StatusDefinition.usNumberCoefStatus = 4096;
	
	xAmplifierDescriptor.c412StatusDefinition.ucPassword1 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword2 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword3 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword4 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword5 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword6 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword7 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword8 = 0X30;
	xAmplifierDescriptor.c412StatusDefinition.ucPassword9 = 0X30;
	
	
	xAmplifierDescriptor.c413StatusDefinition.ucPassword10 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword11 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword12 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword13 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword14 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword15 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword16 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword17 = 0X30;
	xAmplifierDescriptor.c413StatusDefinition.ucPassword18 = 0X30;
	
	
	

	
	xAmplifierDescriptor.c414StatusDefinition.fBackFacetHpaMonitorRaw = 0.0f;
	xAmplifierDescriptor.c414StatusDefinition.fBackFacetLnaMonitorRaw = 0.0f;
	//xAmplifierDescriptor.c414StatusDefinition.fUnitBaseTemperature = -40.0f;
	

	xAmplifierDescriptor.bPasswordIsCorrect = eFalse;
	
	/*xLnaParameters.xInputScalingLnaExternalAdc.xExternalLnaSmld_Thermistor.fIntercept = 0.0f;
	xLnaParameters.xInputScalingLnaExternalAdc.xExternalLnaSmld_Thermistor.fSlope = 1.0f;
	
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaSmld_Thermistor.fSlope = 1.0f;
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaSmld_Thermistor.fIntercept = 0.0f;
		
	
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor1.fSlope = 1.0f;
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor1.fIntercept = 0.0f;	
	
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor2.fSlope = 1.0f;
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor2.fIntercept = 0.0f;	

	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor3.fSlope = 1.0f;
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor3.fIntercept = 0.0f;	
	
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor4.fSlope = 1.0f;
	xBoosterParameters.xInputScalingBoosterExternalAdc.xExternalHpaMmld_Thermistor4.fIntercept = 0.0f;	

	*/	

	
	
	
	
}

void vControlAlarmInitAlarms(void)
{
	
	
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForLnaSmAlarmWayTooLowTemperature = (float) (ALARM_FOR_LNA_SM_EXTRA_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForLnaSmAlarmTooLowTemperature =  (float) (ALARM_FOR_LNA_SM_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForLnaSmAlarmTooHighTemperature =  (float )(ALARM_FOR_LNA_SM_HIGH_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForLnaSmAlarmWayTooHighTemperature =  (float )(ALARM_FOR_LNA_SM_EXTRA_HIGH_TEMP);
	
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaSmAlarmWayTooLowTemperature =  (float )(ALARM_FOR_HPA_SM_WAY_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaSmAlarmTooLowTemperature =  (float)(ALARM_FOR_HPA_SM_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaSmAlarmTooHighTemperature =  (float)(ALARM_FOR_HPA_SM_TOO_HIGH_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaSmAlarmWayTooHighTemperature =  (float )(ALARM_FOR_HPA_SM_WAY_TOO_HIGH_TEMP);

	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm1AlarmWayTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_1_WAY_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm1AlarmTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_1_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm1AlarmTooHighTemperature =  (float )(ALARM_FOR_HPA_MM_1_TOO_HIGH_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm1AlarmWayTooHighTemperature =  (float)(ALARM_FOR_HPA_MM_1_WAY_TOO_HIGH_TEMP);
	
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm2AlarmWayTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_2_WAY_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm2AlarmTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_2_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm2AlarmTooHighTemperature =  (float )(ALARM_FOR_HPA_MM_2_TOO_HIGH_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm2AlarmWayTooHighTemperature =  (float )(ALARM_FOR_HPA_MM_2_WAY_TOO_HIGH_TEMP);

	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm3AlarmWayTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_3_WAY_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm3AlarmTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_3_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm3AlarmTooHighTemperature =  (float )(ALARM_FOR_HPA_MM_3_TOO_HIGH_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm3AlarmWayTooHighTemperature =  (float)(ALARM_FOR_HPA_MM_3_WAY_TOO_HIGH_TEMP);
	
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm4AlarmWayTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_4_WAY_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm4AlarmTooLowTemperature =  (float )(ALARM_FOR_HPA_MM_4_TOO_LOW_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm4AlarmTooHighTemperature =  (float )(ALARM_FOR_HPA_MM_4_TOO_HIGH_TEMP);
	xAmplifierDescriptor.xAlarmsThresholdsValues.xAlarmsThresholdsForTemperatureValues.sThresholdForHpaMm4AlarmWayTooHighTemperature =  (float )(ALARM_FOR_HPA_MM_4_WAY_TOO_HIGH_TEMP);
	
}

/*------------------------------------------------------------------------------*/
CanSequence_t getCanSequence(void)
{
	return (xAmplifierDescriptor.CanSequence);
}
/*------------------------------------------------------------------------------*/
void setCanSequence(CanSequence_t  CanSequence)
{
	xAmplifierDescriptor.CanSequence = CanSequence;
}

/* Exported functions ------------------------------------------------------- */
xAmplifierDescriptor_t* vGetxAmplifierDescriptor( void )
{
	return &xAmplifierDescriptor;
}
/*------------------------------------------------------------------------------*/
/*xAmplifierParameters_t* vGetxAmplifierParameters( void )
{
	return (&xAmplifierParameters);
}*/
/*------------------------------------------------------------------------------*/
xCommonControlParameters_t * vGetpxCommonControlParameters( void )
{
	return (&xCommonControlParameters);
}
void vClearResetStartup(void)
{
	xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bResetFromStartupState = 0;
}

/*------------------------------------------------------------------------------*/
xLnaParameters_t * vGetpxLnaParameters( xLnaParameters_t *xLnaParametersl )
{
	memcpy( xLnaParametersl, &xLnaParameters, sizeof(xLnaParameters_t) );
	
	return (&xLnaParameters);
}
/*------------------------------------------------------------------------------*/
xBoosterParameters_t * vGetpxBoosterParameters( void )
{
	return (&xBoosterParameters);
}


void vLaserSetTemperatureInCan( handle_t xStream, float fTemperatureReaded)
{
		if(xStream == eHandleAdcExSmLnaThermistor )
		{
			xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor4 = fTemperatureReaded ;
			xAmplifierDescriptor.xExternalAnalogThermistorsInputs.fExternalThermistorLnaSmLd = fTemperatureReaded;
		}
		else if(xStream == eHandleAdcExSmHpaThermistor )
		{
			xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor1 = fTemperatureReaded ;
			xAmplifierDescriptor.xExternalAnalogThermistorsInputs.fExternalThermistorHpaSmLd = fTemperatureReaded;
		}
		else if(xStream == eHandleAdcExHpaMmThermistor1 )
		{
			xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor2 = fTemperatureReaded ;
			xAmplifierDescriptor.xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd1 = fTemperatureReaded;
		}
		else if(xStream == eHandleAdcExHpaMmThermistor2 )
		{
			xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor3 = fTemperatureReaded ;
			xAmplifierDescriptor.xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd2 = fTemperatureReaded;
		}
		else if(xStream == eHandleAdcExHpaMmThermistor3 )
		{
			xAmplifierDescriptor.c402StatusDefinition.fTemperatureValueSensor4 = fTemperatureReaded ;
			xAmplifierDescriptor.xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd3 = fTemperatureReaded;
		}
		else if(xStream == eHandleAdcExHpaMmThermistor4 )
		{
			
			xAmplifierDescriptor.xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd4 = fTemperatureReaded;
		}
		else if(xStream == eHandleAdcExCaseThermistor )
		{
			xAmplifierDescriptor.c414StatusDefinition.fUnitBaseTemperature = fTemperatureReaded ;
			
		}
	
	
	
}

eMpbError_t	eLaserGetLimitTemperature( handle_t xStream, float *pfVeryHighLimit , float *pfVeryLowLimit, float *pfHighLimit )
{
    eMpbError_t eMpbError = eSuccess;
	if(xStream == eHandleAdcExCaseThermistor )
	{
		*pfVeryHighLimit = xAmplifierDescriptor.xPumpTemperaturesLimits.fUnitBaseTemperatureHighAlarmLimit;
		*pfHighLimit = xAmplifierDescriptor.xPumpTemperaturesLimits.fUnitBaseTemperatureHighAlarmLimit;
		*pfVeryLowLimit = xAmplifierDescriptor.xPumpTemperaturesLimits.fUnitBaseTemperatureLowAlarmLimit;
	}
	else
	{
		*pfVeryHighLimit = xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureVeryHighAlarmLimit;
		*pfHighLimit = xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureHighAlarmLimit;
		*pfVeryLowLimit = xAmplifierDescriptor.xPumpTemperaturesLimits.fPumpTemperatureVeryLowAlarmLimit;
	
	}
	return eMpbError;
}


void vLaserSetTemperatureFlagAlarm( handle_t xStream, eBool_t bVeryLowAlarm , eBool_t bVeryHighAlarm, eBool_t bHighAlarm )
{
	if(xStream == eHandleAdcExSmLnaThermistor )
	{
		/*this ones does not generate critical alarm*/
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaSmAlarmLowTemperature = (bVeryLowAlarm == eTrue)? 1 : 0 ;
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaSmAlarmHighTemperature = (bHighAlarm == eTrue)? 1 : 0 ;
		
		//next does generate critical alarm
		if(bVeryHighAlarm == eTrue)
		{
			xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bLnaSmAlarmWayTooHighTemperature = 1;			
		}
	}
	else if(xStream == eHandleAdcExSmHpaThermistor )
	{		
		/*this one does not generate critical alarm*/
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmHighTemperature = (bHighAlarm == eTrue)? 1: 0;
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmLowTemperature = (bVeryLowAlarm == eTrue)? 1:0;		
		/*next two does generate critical alarm*/
		if(bVeryHighAlarm == eTrue)
		{
			xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaSmAlarmWayTooHighTemperature = 1;
		}
	}
	else if(xStream == eHandleAdcExHpaMmThermistor1 )
	{
		/*this ones does not generate critical alarm*/
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmLowTemperature = (bVeryLowAlarm == eTrue)? 1:0;
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmHighTemperature = (bHighAlarm == eTrue)? 1:0;
			
		/*next does generate critical alarm*/
		if(bVeryHighAlarm == eTrue)
		{
			xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm1AlarmWayTooHighTemperature = 1;
		}
		
	}
	else if(xStream == eHandleAdcExHpaMmThermistor2 )
	{
		/*this one does not generate critical alarm*/
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmHighTemperature = (bHighAlarm == eTrue)? 1: 0;
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmLowTemperature = (bVeryLowAlarm == eTrue)? 1: 0;
		/*next two does generate critical alarm*/
		if(bVeryHighAlarm == eTrue)
		{
			xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bHpaMm2AlarmWayTooHighTemperature = 1;
		}
	}
	/*else if(xStream == eHandleAdcExHpaMmThermistor3 )
	{
				
	}
	else if(xStream == eHandleAdcExHpaMmThermistor4 )
	{
		
		
	}*/
	else if(xStream == eHandleAdcExCaseThermistor )
	{
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bCaseAlarmHighTemperature = (bHighAlarm == eTrue)? 1: 0;
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bCaseAlarmLowTemperature = (bVeryLowAlarm == eTrue)? 1: 0;
		/*next two does generate critical alarm*/
		if(bVeryHighAlarm == eTrue)
		{
			xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bCaseAlarmWayTooHighTemperature = 1;
		}
		
	}
	
}
/*------------------------------------------------------------------------------*/
/*xInternalAnalogInputsCpu_t* vpGetInternalAnalogInputs(void)
{
	return &(xAmplifierDescriptor.xInternalAnalogInputsCpu);
}*/
/*------------------------------------------------------------------------------*/
c402StatusDefinition_t* vGet402Message( void )
{
	return &(xAmplifierDescriptor.c402StatusDefinition);
}
/*------------------------------------------------------------------------------*/
/*float fGetVoltage(void )
{
	return xAmplifierDescriptor.xInternalAnalogInputsCpu.f28V_PwrCurrentMonitor_Ch1;
}*/
/*------------------------------------------------------------------------------*/
void vLaserBeamsFactoryCommonDefaultValues( void )
{
	
}
void vLaserBeamsFactoryLnaDefaultValues( void )
{
	
}
void vLaserBeamsFactoryBoosterDefaultValues( void )
{
	
}

void vLaserBeamsFactoryDefaultValues( void )
{

	int16_t LowFault, LowAlarm, HighAlarm, HighFault ;
	
	memset( &xAmplifierDescriptor, 0, sizeof(xAmplifierDescriptor_t) );
	


	
	/* inital current alarms 

	xLaserBeamGlobalDescriptor.cSoftwareVersion[0] = (version[0]);
	xLaserBeamGlobalDescriptor.cSoftwareVersion[1] = (version[1]);
	xLaserBeamGlobalDescriptor.cSoftwareVersion[2] = (version[2]);
	xLaserBeamGlobalDescriptor.cSoftwareVersion[3] = (version[3]);*/
	//xLaserBeamGlobalDescriptor.fVersion = fVersionFirmware;

	//xLaserBeamGlobalDescriptor.xElectricalVariablesStatus[0].usCurrentThresholdSetpoint = 3000;
	//xLaserBeamGlobalDescriptor.xElectricalVariablesStatus[1].usCurrentThresholdSetpoint = 3000;

	/* inital temp alarms */

	

//	vCurrentSensorInitFacotryScaling();
//	vPowerSensorScalingFactory();
//	vCurrentControlInit( );
//	vSetPidInitialValues();
	
//	vTemperatureInit();
//	vPowerControlInit( );
	
	
	
	
	//	 xLaserBeamGlobalDescriptor.eNvmMemoryUpdateIdNeeded = eTrue;
}


/*-------------------------------------------------------------*/
eBool_t bCanPort1IsSelected( void )
{
	return (xCommonControlParameters.bCanPort1Selected);
}
/*-------------------------------------------------------------*/
void vSetCanPort1( eBool_t bSelectCan1 )
{
	xCommonControlParameters.bCanPort1Selected = bSelectCan1;
}
/*-------------------------------------------------------------*/
void vGetSerialNumber(uint32_t *uSerialNumber)
{
	*uSerialNumber = xCommonControlParameters.ulSerialNumber;
}
/*-------------------------------------------------------------*/
void vSetSerialNumber(uint32_t uSerialNumber)
{
	xCommonControlParameters.ulSerialNumber = uSerialNumber;
}
/*-------------------------------------------------------------*/

void vGetCompanyId(uint8_t *ucCompanyId)
{
	*ucCompanyId = xCommonControlParameters.ucCompanyId;
}
/*-------------------------------------------------------------*/
void vSetCompanyId(uint8_t ucCompanyId)
{
	xCommonControlParameters.ucCompanyId = ucCompanyId;
}

/*-------------------------------------------------------------*/
void vLaserDataGetCan401Info( c401StatusDefinition_t  *c401StatusDefinition )
{
	
	memcpy( c401StatusDefinition, &(xAmplifierDescriptor.c401StatusDefinition), sizeof(c401StatusDefinition_t) );
	
	/*c401Status1Definition->fInternalMountingSurfaceTemperature	= xAmplifierDescriptor.xBoosterAnalogInputs.fInternalMountingSurfaceTemperature;
	c401Status1Definition->fLaserPump1CurrentOfBooster			= xAmplifierDescriptor.xBoosterAnalogOutputs.fLaserPump1CurrentOfBooster;
	c401Status1Definition->fLaserPump2CurrentOfBooster			= xAmplifierDescriptor.xBoosterAnalogOutputs.fLaserPump2CurrentOfBooster;
	c401Status1Definition->fLaserPump3CurrentOfBooster			= xAmplifierDescriptor.xBoosterAnalogOutputs.fLaserPump3CurrentOfBooster;
	c401Status1Definition->fLaserPump4CurrentOfLna				= xAmplifierDescriptor.xAnalogOutputsLna.fLaserPump4CurrentOfLna;
	c401Status1Definition->fBoosterOpticalInputPower			= xAmplifierDescriptor.xBoosterAnalogInputs.fBoosterOpticalInputPower;
	c401Status1Definition->fLnaOpticalOutputPower				= xAmplifierDescriptor.xAnalogOutputsLna.fLnaOpticalOutputPower;	
	c401Status1Definition->fBoosterOutputOpticalPowerIndBmApc   = xAmplifierDescriptor.xBoosterAnalogOutputs.fBoosterOutputOpticalPowerIndBmApc;*/

}
//void vLaserDataGetCan414Info( c414StatusDefinition_t  *c414StatusDefinition )
//{
	/*xAmplifierDescriptor.c414StatusDefinition.fBoostOpticalInputPower = 3.389f;
	xAmplifierDescriptor.c414StatusDefinition.fBoostOpticalOutputPower= 31.589f;
	xAmplifierDescriptor.c414StatusDefinition.fLnaOpticalOutputPower= -7.211f;
	xAmplifierDescriptor.c414StatusDefinition.fUnitBaseTemperature= 32.689f;
	xAmplifierDescriptor.c414StatusDefinition.fPowerSupplyMonitor= 26.789f;
	*/
	
//	memcpy( c414StatusDefinition, &(xAmplifierDescriptor.c414StatusDefinition), sizeof(c414StatusDefinition_t) );
	
	/*c401Status1Definition->fInternalMountingSurfaceTemperature	= xAmplifierDescriptor.xBoosterAnalogInputs.fInternalMountingSurfaceTemperature;
	c401Status1Definition->fLaserPump1CurrentOfBooster			= xAmplifierDescriptor.xBoosterAnalogOutputs.fLaserPump1CurrentOfBooster;
	c401Status1Definition->fLaserPump2CurrentOfBooster			= xAmplifierDescriptor.xBoosterAnalogOutputs.fLaserPump2CurrentOfBooster;
	c401Status1Definition->fLaserPump3CurrentOfBooster			= xAmplifierDescriptor.xBoosterAnalogOutputs.fLaserPump3CurrentOfBooster;
	c401Status1Definition->fLaserPump4CurrentOfLna				= xAmplifierDescriptor.xAnalogOutputsLna.fLaserPump4CurrentOfLna;
	c401Status1Definition->fBoosterOpticalInputPower			= xAmplifierDescriptor.xBoosterAnalogInputs.fBoosterOpticalInputPower;
	c401Status1Definition->fLnaOpticalOutputPower				= xAmplifierDescriptor.xAnalogOutputsLna.fLnaOpticalOutputPower;	
	c401Status1Definition->fBoosterOutputOpticalPowerIndBmApc   = xAmplifierDescriptor.xBoosterAnalogOutputs.fBoosterOutputOpticalPowerIndBmApc;*/

//}

c414StatusDefinition_t *  pLaserDataGetCan414Info( void )
{
	return &(xAmplifierDescriptor.c414StatusDefinition);
}
/*-----*/
c415StatusDefinition_t  * pLaserDataGetCan415Info( void )
{
	//memcpy( c415StatusDefinition, &(xAmplifierDescriptor.c415StatusDefinition), sizeof(c415StatusDefinition_t) );
	return &(xAmplifierDescriptor.c415StatusDefinition);
}
/*-------------------------------------------------------------*/
c402StatusDefinition_t* vLaserDataGetData402(void )
{
	return &(xAmplifierDescriptor.c402StatusDefinition);
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan402Info( c402StatusDefinition_t  *c402StatusDefinition )
{
	
	//memcpy( c402StatusDefinition, &(xAmplifierDescriptor.c402StatusDefinition), sizeof(c402StatusDefinition_t) );
	c402StatusDefinition = &(xAmplifierDescriptor.c402StatusDefinition);
	
}
/*------------------------------------------------------------------------------*/
c402StatusDefinition_t  * pLaserDataGetCan402Pointer( void )
{
	
	//memcpy( c402StatusDefinition, &(xAmplifierDescriptor.c402StatusDefinition), sizeof(c402StatusDefinition_t) );
	return &(xAmplifierDescriptor.c402StatusDefinition);
	
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan403Info( c403StatusDefinition_t  *c403StatusDefinition )
{
	memcpy( c403StatusDefinition, &(xAmplifierDescriptor.c403StatusDefinition), sizeof(c403StatusDefinition_t) );
	
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan404Info( c404StatusDefinition_t  *c404StatusDefinition )
{
	memcpy( c404StatusDefinition, &(xAmplifierDescriptor.c404StatusDefinition), sizeof(c404StatusDefinition_t) );
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan405Info( c405Definition_t  *c405Definition )
{
	memcpy( c405Definition, &(xAmplifierDescriptor.c405Definition), sizeof(c405Definition_t) );
}
/*------------------------------------------------------------------------------*/
c406PacketControlDefinition_t* vLaserDataGetData406(void )
{
	return &(xAmplifierDescriptor.c406PacketControlDefinition);	
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan406Info( c406PacketControlDefinition_t  *c406PacketControlDefinition )
{
	memcpy( c406PacketControlDefinition, &(xAmplifierDescriptor.c406PacketControlDefinition), sizeof(c406PacketControlDefinition_t) );
//	c406PacketControl1Definition = &(xAmplifierDescriptor.c406PacketControl1Definition);
	
}
/*------------------------------------------------------------------------------*/
void vLaserDataSetCan406Info( c406PacketControlDefinition_t  *c406PacketControlDefinition )
{
	memcpy( &(xAmplifierDescriptor.c406PacketControlDefinition), c406PacketControlDefinition,  sizeof(c406PacketControlDefinition_t) );
}
/*------------------------------------------------------------------------------*/
c407PacketControlDefinition_t* vLaserDataGetData407(void )
{
	return &(xAmplifierDescriptor.c407PacketControlDefinition);
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan407Info( c407PacketControlDefinition_t  *c407PacketControlDefinition )
{
	
}
void vLaserDataSetCan407Info( c407PacketControlDefinition_t  *c407PacketControlDefinition )
{
	memcpy( &(xAmplifierDescriptor.c407PacketControlDefinition), c407PacketControlDefinition,  sizeof(c407PacketControlDefinition_t) );
}

/*------------------------------------------------------------------------------*/
c408StatusDefinition_t* vLaserDataGetData408(void )
{
	return &(xAmplifierDescriptor.c408StatusDefinition);
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan408Info( c408StatusDefinition_t  *c408StatusDefinition )
{
	memcpy( c408StatusDefinition, &(xAmplifierDescriptor.c408StatusDefinition), sizeof(c408StatusDefinition_t) );
}
/*------------------------------------------------------------------------------*/
c403StatusDefinition_t* vLaserDataGetData403(void )
{
	return &(xAmplifierDescriptor.c403StatusDefinition);
}
c404StatusDefinition_t* vLaserDataGetData404(void )
{
	return &(xAmplifierDescriptor.c404StatusDefinition);
}
c409StatusDefinition_t* vLaserDataGetData409(void )
{
	
	return &(xAmplifierDescriptor.c409StatusDefinition);
}
/*------------------------------------------------------------------------------*/
c410StatusDefinition_t* vLaserDataGetData410(void )
{
	return &(xAmplifierDescriptor.c410StatusDefinition);
}
/*------------------------------------------------------------------------------*/
c412StatusDefinition_t* vLaserDataGetData412(void )
{
	return &(xAmplifierDescriptor.c412StatusDefinition);
}
/*------------------------------------------------------------------------------*/
c413StatusDefinition_t* vLaserDataGetData413(void )
{
	return &(xAmplifierDescriptor.c413StatusDefinition);
}
/*------------------------------------------------------------------------------*/
eBool_t bValidatePassword(c412StatusDefinition_t *c412StatusDefinition , c413StatusDefinition_t* c413StatusDefinition  )
{ //MYNARIK_MK3_CONDOR
	if( (c412StatusDefinition->ucPassword1 == 0x4D) && (c412StatusDefinition->ucPassword2 == 0x59) && (c412StatusDefinition->ucPassword3 == 0x4e) &&
	    (c412StatusDefinition->ucPassword4 == 0x41) && (c412StatusDefinition->ucPassword5 == 0x52) && (c412StatusDefinition->ucPassword6 == 0x49) &&
		(c412StatusDefinition->ucPassword7 == 0x4b) && (c412StatusDefinition->ucPassword8 == 0x5f) && (c412StatusDefinition->ucPassword9 == 0x4d) && 
		(c413StatusDefinition->ucPassword10 == 0x4b) && (c413StatusDefinition->ucPassword11 == 0x33) && (c413StatusDefinition->ucPassword12 == 0x5f) &&
	    (c413StatusDefinition->ucPassword13 == 0x43) && (c413StatusDefinition->ucPassword14 == 0x4f) && (c413StatusDefinition->ucPassword15 == 0x4e) &&
		(c413StatusDefinition->ucPassword16 == 0x44) && (c413StatusDefinition->ucPassword17 == 0x4f) && (c413StatusDefinition->ucPassword18 == 0x52)		
		
		)
  	{
		  xAmplifierDescriptor.bPasswordIsCorrect = eTrue;
		  xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bPassWordValidated = 1;
	}
	else
	{
		xAmplifierDescriptor.bPasswordIsCorrect = eFalse;
		xAmplifierDescriptor.c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment.bPassWordValidated = 0;
	}
}


/*------------------------------------------------------------------------------*/
void vLaserDataGetCan409Info( c409StatusDefinition_t  *c409StatusDefinition )
{
	memcpy( c409StatusDefinition, &(xAmplifierDescriptor.c409StatusDefinition), sizeof(c409StatusDefinition_t) );
}
/*------------------------------------------------------------------------------*/
c409StatusDefinition_t  * vLaserDataGetCan409Pointer( void  )
{
	return  &(xAmplifierDescriptor.c409StatusDefinition);
}
/*------------------------------------------------------------------------------*/
c40AStatusDefinition_t* vLaserDataGetCan40AInfo( void )
{
	//memcpy( c40AStatusDefinition, &(xAmplifierDescriptor.c40AStatusDefinition), sizeof(c40AStatusDefinition_t) );
	return  &(xAmplifierDescriptor.c40AStatusDefinition);
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan423Info( c423StatusDefinition_t  *c423StatusDefinition )
{
	//memcpy( c40AStatusDefinition, &(xAmplifierDescriptor.c40AStatusDefinition), sizeof(c40AStatusDefinition_t) );
	memcpy( c423StatusDefinition, &(xAmplifierDescriptor.c423StatusDefinition), sizeof(c423StatusDefinition_t) );
}
/*------------------------------------------------------------------------------*/
c428StatusDefinition_t * pLaserDataGetCan428Info( void )
{
	return  &(xAmplifierDescriptor.c428StatusDefinition);
}
/*------------------------------------------------------------------------------*/
xExternalAnalogThermistorsInputs_t*  pLaserDataGetThermistorData( void )
{
	return  &(xAmplifierDescriptor.xExternalAnalogThermistorsInputs);
}
/*------------------------------------------------------------------------------*/
void vLaserDataGetCan411Info( c411StatusDefinition_t  *c411StatusDefinition )
{
	memcpy( c411StatusDefinition, &(xAmplifierDescriptor.c411StatusDefinition), sizeof(c411StatusDefinition_t) );
}
/*------------------------------------------------------------------------------*/
uint8_t cGetresetCause(void)
{
	return xCommonControlParameters.cResetCause;
}
/*------------------------------------------------------------------------------*/
xPidValues_t* getLnaPidValues( void)
{
	return &(xLnaParameters.xPidValuesLna);
}
/*------------------------------------------------------------------------------*/
void setLnaPidProportionalValue( float fPvalue)
{
	xLnaParameters.xPidValuesLna.fPGain = fPvalue;
}
/*------------------------------------------------------------------------------*/
void setLnaPidIntegralValue( float fPvalue)
{
	xLnaParameters.xPidValuesLna.fIGain = fPvalue;
}
void setLnaPidDerivativeValue( float fPvalue)
{
	xLnaParameters.xPidValuesLna.fDGain = fPvalue;
}
/*------------------------------------------------------------------------------*/
void vSetSendConfig(void)
{
	xCommonControlParameters.bSendFactory = eTrue;
}
/*------------------------------------------------------------------------------*/
eBool_t bGetSendConfig(void)
{
	return xCommonControlParameters.bSendFactory;
}
/*------------------------------------------------------------------------------*/
void vResetSendConfig(void)
{
	xCommonControlParameters.bSendFactory = eFalse;
}
/*------------------------------------------------------------------------------*/

void vUpdateCommonNvmMemory(void)
{
	
	uint16_t usSize						= 0;
	uint16_t usSizeCrcCalculData		= 0;
	hal_status_t hal_status				= hal_status_ok;
	uint16_t usCrc16Calculated			= 0;
	
	
	usSize = sizeof(xCommonControlParameters_t );
	
	usSizeCrcCalculData = sizeof(xCommonControlParameters_t);

//	if(xAmplifierDescriptor.bWriteCommonMemoryNeeded == eTrue )
//	{
//		xAmplifierDescriptor.bWriteCommonMemoryNeeded = eFalse ;
		
		usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xCommonControlParametersImage, (usSizeCrcCalculData-SIZE_OF_CRC16-3) );
		
		xCommonControlParametersImage.usCrc16Value = usCrc16Calculated ;
		
		hal_status = FRAM_MultipleWrite( (uint32_t)MEMORY_INIT_COMMON_ADDRESS, ((uint8_t*)&xCommonControlParametersImage), eSpi0Bank , usSize );
		
//	}

}


void vUpdateLnaNvmMemory(void)
{
	
	uint16_t usSize						= 0;
	uint16_t usSizeCrcCalculData		= 0;
	hal_status_t hal_status				= hal_status_ok;
	uint16_t usCrc16Calculated			= 0;
	
	
	usSize = sizeof(xLnaParameters_t );
	
	usSizeCrcCalculData = sizeof(xLnaParameters_t);

//	if(xAmplifierDescriptor.bWriteLnaMemoryNeeded == eTrue )
//	{
//		xAmplifierDescriptor.bWriteLnaMemoryNeeded = eFalse ;
		
		usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xLnaParametersImage, (usSizeCrcCalculData-SIZE_OF_CRC16-3) );
		
		xLnaParametersImage.usCrc16Value = usCrc16Calculated ;
		
		hal_status = FRAM_MultipleWrite( (uint32_t)MEMORY_INIT_LNA_ADDRESS, ((uint8_t*)&xLnaParametersImage), eSpi0Bank , usSize );
		
//	}

}
/*------------------------------------------------------------------------------*/
void vUpdateBoostNvmMemory(void)
{
	
	uint16_t usSize						= 0;
	uint16_t usSizeCrcCalculData		= 0;
	hal_status_t hal_status				= hal_status_ok;
	uint16_t usCrc16Calculated			= 0;
	
	
	usSize = sizeof(xBoosterParameters_t );
	
	usSizeCrcCalculData = sizeof(xBoosterParameters_t);

//	if(xAmplifierDescriptor.bWriteBoosterMemoryNeeded == eTrue )
//	{
	//	xAmplifierDescriptor.bWriteBoosterMemoryNeeded = eFalse ;
		
		usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xBoosterParametersImage, (usSizeCrcCalculData-SIZE_OF_CRC16-3) );
		
		xBoosterParametersImage.usCrc16Value = usCrc16Calculated ;
		
		hal_status = FRAM_MultipleWrite( (uint32_t)MEMORY_INIT_BOOSTER_ADDRESS, ((uint8_t*)&xBoosterParametersImage), eSpi0Bank , usSize );
		
	//}
}


void vUpdateConfigInfo(void)
{
	eBool_t bReadFromRam = eFalse;
	
	if( xAmplifierDescriptor.c410StatusDefinition.CoeficientOperation == WRITE_COEFFICIENT_TO_RAM)
	{
		bReadFromRam = eTrue;
		
		//common inputs
		if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient < INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_SLOPE )
		{
			svWriteCommonCoefficientesToRam();
			svReadCommonCoefficients(bReadFromRam );
		}//lna inputs and outputs
		else if( (xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient < INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_SLOPE) &&
			  	 (xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient > INDEX_FOR_CALIB_PD_REF2_CH23_INTERCEPT ) )
		{
			svWriteLnaCoefficientesToRam();
			svReadLnaCoefficients(bReadFromRam );
			
		}//hpa inputs and outputs
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient > LNA_MAX_POWER )				 
		{
			svWriteBoosterCoefficientesToRam();
			svReadBoosterCoefficients(bReadFromRam );

		}
		// lna outputs

		
				
	}
	else if ( xAmplifierDescriptor.c410StatusDefinition.CoeficientOperation == DO_OPERATION_NOTHING)
	{
		
	}
	else
	{
		bReadFromRam = (xAmplifierDescriptor.c410StatusDefinition.CoeficientOperation == READ_COEFFICIENT_TO_RAM)? eTrue : eFalse;
		//common
		if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient < INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_SLOPE )
		{
			
			svReadCommonCoefficients(bReadFromRam );
		}//lna
		else if( (xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient < INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_SLOPE) &&
				 (xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient > INDEX_FOR_CALIB_PD_REF2_CH23_INTERCEPT ) )
		{
			
			svReadLnaCoefficients(bReadFromRam );
			
		}//hpa
		else if( xAmplifierDescriptor.c410StatusDefinition.usNumberCoefficient > LNA_MAX_POWER )
		{
			
			svReadBoosterCoefficients(bReadFromRam );

		}
		
	}
	
		
	xAmplifierDescriptor.c410StatusDefinition.CoeficientOperation = DO_OPERATION_NOTHING ;
	xAmplifierDescriptor.bWriteAllMemoryNeeded = eFalse;	
	//vSetUpdateMemoryWriteNeeded(eFalse);
	

	
}
/*--------------------------------------------------------------------------------
eBool_t bInitMemoryImageFromNvm(void)
{
	uint16_t		usSize				= 0;
	uint16_t		usCrc16Calculated	= 0;
	hal_status_t	hal_status			= hal_status_ok;
	eBool_t			bSucces				= eTrue;
	
	usSize = sizeof(xAmplifierParameters_t );				
	memset( &xAmplifierParameters, 0 , usSize );
	
	for( uint8_t ucK =0; ucK < MAX_NUM_OF_TRYS ; ucK++)
	{
		hal_status =  FRAM_MultipleRead( (uint32_t)MEMORY_INIT_ADDRESS , ((uint32_t*)&xAmplifierParameters), usSize, eSpi0Bank);										
		if( hal_status == hal_status_ok)
		{
			ucK = MAX_NUM_OF_TRYS;
				
		
			usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xAmplifierParameters, (usSize-SIZE_OF_CRC16) );
						
			if( xAmplifierParameters.usCrc16Value == usCrc16Calculated )
			{
				vCurrentSensorsConfigUpdate();
				vPowerSensorsConfigUpdate();
			//	vCurrentOutputConfigUpdate( );
			//	vUpdateNvmMemory();				
			}		
			else
			{
			
			 
			}
		}
		else
		{
			bSucces = eFalse;
		}
		
		
			
	}	
	return bSucces;
}*/

/*--------------------------------------------------------------------------------*/
eBool_t bInitCommonMemoryImageFromNvm(void)
{
	uint16_t		usSize				= 0;
	uint16_t		usCrc16Calculated	= 0;
	hal_status_t	hal_status			= hal_status_ok;
	eBool_t			bSucces				= eFalse;
	
	usSize = sizeof(xCommonControlParameters_t );
	
	memset( &xCommonControlParameters, 0 , usSize );
	
	for( uint8_t ucK =0; ucK < MAX_NUM_OF_TRYS ; ucK++)
	{
		hal_status =  FRAM_MultipleRead( (uint32_t)MEMORY_INIT_COMMON_ADDRESS , ((uint8_t*)&xCommonControlParameters), usSize, eSpi0Bank);
		if( hal_status == hal_status_ok)
		{
			
			
			
			usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xCommonControlParameters, (usSize-SIZE_OF_CRC16-3) );
			
			
			if( xCommonControlParameters.usCrc16Value == usCrc16Calculated )
			{
				//vCurrentSensorsConfigUpdate();	//
				ucK = MAX_NUM_OF_TRYS;
				//ePowerSensorsFactoryInitCommonChannels();
				ePowerSensorsCommonConfigUpdate();
				
				//vTemperatureSensorsCommonConfigUpdate();
				bSucces = eTrue;
				
			}
			else
			{
				ePowerSensorsFactoryInitCommonChannels();
				bSucces = eFalse;
				
			}
		}

		
		
		
	}
	return bSucces;
}



/*--------------------------------------------------------------------------------*/
eBool_t bInitLnaMemoryImageFromNvm(void)
{
	uint16_t		usSize				= 0;
	uint16_t		usCrc16Calculated	= 0;
	hal_status_t	hal_status			= hal_status_ok;
	eBool_t			bSucces				= eFalse;
	
	usSize = sizeof(xLnaParameters_t );
	memset( &xLnaParameters, 0 , usSize );
	
	for( uint8_t ucK =0; ucK < MAX_NUM_OF_TRYS ; ucK++)
	{
		hal_status =  FRAM_MultipleRead( (uint32_t)MEMORY_INIT_LNA_ADDRESS , ((uint32_t*)&xLnaParameters), usSize, eSpi0Bank);
		if( hal_status == hal_status_ok)
		{
			
			
			
			usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xLnaParameters, (usSize-SIZE_OF_CRC16-3) );
			
			if( xLnaParameters.usCrc16Value == usCrc16Calculated )
			{
				bSucces = eTrue;
				ucK = MAX_NUM_OF_TRYS;
				eCurrentSensorsLnaConfigUpdate();
				ePowerSensorsLnaConfigUpdate();
				//vTemperatureSensorsLnaConfigUpdate();
				vCurrentOutputLnaConfigUpdate( );
					
				
			}
			else
			{
				bSucces = eFalse;
				
			}
		}

		
		
		
	}
	return bSucces;
}
eBool_t bInitBoostMemoryImageFromNvm(void)
{
	uint16_t		usSize				= 0;
	uint16_t		usCrc16Calculated	= 0;
	hal_status_t	hal_status			= hal_status_ok;
	eBool_t			bSucces				= eFalse;
	
	usSize = sizeof(xBoosterParameters_t );
	memset( &xBoosterParameters, 0 , usSize );
	
	/*hal_status =  FRAM_MultipleRead( (uint32_t)MEMORY_INIT_BOOSTER_ADDRESS , ((uint32_t*)&xBoosterParameters), usSize, eSpi0Bank);
	
	usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xBoosterParametersImage, (usSize-SIZE_OF_CRC16-3) );
			
	xBoosterParametersImage.usCrc16Value = usCrc16Calculated ;
			
	hal_status = FRAM_MultipleWrite( (uint32_t)MEMORY_INIT_BOOSTER_ADDRESS, ((uint8_t*)&xBoosterParametersImage), eSpi0Bank , usSize );
	
	hal_status =  FRAM_MultipleRead( (uint32_t)MEMORY_INIT_BOOSTER_ADDRESS , ((uint32_t*)&xBoosterParametersImage), usSize, eSpi0Bank);
	*/
	
	
	for( uint8_t ucK =0; ucK < MAX_NUM_OF_TRYS ; ucK++)
	{
		hal_status =  FRAM_MultipleRead( (uint32_t)MEMORY_INIT_BOOSTER_ADDRESS , ((uint32_t*)&xBoosterParameters), usSize, eSpi0Bank);
		if( hal_status == hal_status_ok)
		{
			
			
			
			usCrc16Calculated = crc_ccitt_ffff( (unsigned char *)&xBoosterParameters, (usSize-SIZE_OF_CRC16-3) );
			
			if( xBoosterParameters.usCrc16Value == usCrc16Calculated )
			{
				bSucces = eTrue;
				ucK = MAX_NUM_OF_TRYS;
				eCurrentSensorsBoosterConfigUpdate();
				ePowerSensorsBoosterConfigUpdate();
				//vTemperatureSensorsBoosterConfigUpdate();
				vCurrentOutputBoosterConfigUpdate();
				//	vUpdateNvmMemory();
			}
			else
			{
				
				bSucces = eFalse;
			}
		}
		
		
		
		
	}
	
	
	return bSucces;
}


/*-----------------------------------------------------------------------------------*/
void setInternalCriticalErrorFlag(eBool_t value)
{
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag = 0;
}
/*-------------------------------------------*/
void vInitWithFullResetRequest(void)
{
	xAmplifierDescriptor.c406PacketControlDefinition.ucResetRequest = RESET_ALL ;
	
}

void vIncreaseSpiAdcErrors(void)
{
	xAmplifierDescriptor.xHardwareErrors.ulSpiAdcErrors = xAmplifierDescriptor.xHardwareErrors.ulSpiAdcErrors +1;
}
void vClearSpiAdcErrors(void)
{
	xAmplifierDescriptor.xHardwareErrors.ulSpiAdcErrors = 0;
}
void vIncreaseSpiFramErrors(void)
{
	xAmplifierDescriptor.xHardwareErrors.ulSpiFramErrors = xAmplifierDescriptor.xHardwareErrors.ulSpiFramErrors + 1;
}
void vClearSpiFramErrors(void)
{
	xAmplifierDescriptor.xHardwareErrors.ulSpiFramErrors = 0;
}
void vIncreaseCanErrors(void)
{
	xAmplifierDescriptor.xHardwareErrors.ulCanErrors = xAmplifierDescriptor.xHardwareErrors.ulCanErrors + 1;
}
/*
void vUpdateNvm(eBool_t bUpdate)
{
	xAmplifierDescriptor.bCalibNeeded	 = bUpdate;
}
eBool_t vGetUpdateNvm(void)
{
	return xAmplifierDescriptor.bCalibNeeded;
}*/
/*void vCopyImageNvm(void)
{
	memcpy(&xAmplifierParametersImage, &xAmplifierParameters, sizeof(xAmplifierParameters_t) );
}
*/

 void vCopyImageCommonNvm(void)
 {
	 memcpy(&xCommonControlParametersImage, &xCommonControlParameters, sizeof(xCommonControlParameters_t) );
 }
 void vCopyImageLnaNvm(void)
 {
	 memcpy(&xLnaParametersImage, &xLnaParameters, sizeof(xLnaParameters_t) );
 }
 void vCopyImageBoosterNvm(void)
 {
	 memcpy(&xBoosterParametersImage, &xBoosterParameters, sizeof(xBoosterParameters_t) );
 }
eBool_t vGetUpdateMemoryWriteNeeded(void)
{
	return xAmplifierDescriptor.bWriteAllMemoryNeeded;	
}

eBool_t bResetIsDemanded(void)
{ 
	eBool_t bResetIsCommanded = eFalse;
	
	bResetIsCommanded = (xAmplifierDescriptor.c406PacketControlDefinition.ucResetRequest != DO_NOTHING )? eTrue : eFalse ;
	
	return bResetIsCommanded;	
}
eBool_t vGetUpdateCommonMemoryWriteNeeded(void)
{
	return xAmplifierDescriptor.bWriteCommonMemoryNeeded;	
}
eBool_t vGetUpdateLnaMemoryWriteNeeded(void)
{
	return xAmplifierDescriptor.bWriteLnaMemoryNeeded;
}
eBool_t vGetUpdateBoosterMemoryWriteNeeded(void)
{
	return xAmplifierDescriptor.bWriteBoosterMemoryNeeded;
}

void vSetUpdateMemoryWriteNeeded(eBool_t bWriteMemoryNeeded)
{
	xAmplifierDescriptor.bWriteAllMemoryNeeded = bWriteMemoryNeeded;	
}
void vSetUpdateCommonMemoryWriteNeeded(eBool_t bWriteMemoryNeeded)
{
	xAmplifierDescriptor.bWriteCommonMemoryNeeded = bWriteMemoryNeeded;	
}
void vSetUpdateLnaMemoryWriteNeeded(eBool_t bWriteMemoryNeeded)
{
	xAmplifierDescriptor.bWriteLnaMemoryNeeded = bWriteMemoryNeeded;	
}
void vSetUpdateBoosterMemoryWriteNeeded(eBool_t bWriteMemoryNeeded)
{
	xAmplifierDescriptor.bWriteBoosterMemoryNeeded = bWriteMemoryNeeded;	
}

void vLaserSetCurrentAlarm( eBool_t bAlarmExist)
{
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaCurrentLimitAlarmStatus = (bAlarmExist == eTrue)? 1: 0;
}


void vUpdateLnaPIDValues( float fLnasingleProportional, float fLnasingleIntegralGain,	float fLnasingleDerivativeGain  )
{
	xLnaParameters.xPidValuesLna.fPGain = fLnasingleProportional;
	xLnaParameters.xPidValuesLna.fIGain = fLnasingleIntegralGain;
	xLnaParameters.xPidValuesLna.fDGain = fLnasingleDerivativeGain;
	
	
}

void vUpdateHpaSmPIDValues( float fLnasingleProportional, float fLnasingleIntegralGain,	float fLnasingleDerivativeGain  )
{
	xBoosterParameters.xPidSmValuesBooster.fPGain = fLnasingleProportional;
	xBoosterParameters.xPidSmValuesBooster.fIGain = fLnasingleIntegralGain;
	xBoosterParameters.xPidSmValuesBooster.fDGain = fLnasingleDerivativeGain;
}

void vUploadHpaSmPIDValues( float *pfHpaSingleProportional, float *pfHpasingleIntegralGain,	float *pfHpasingleDerivativeGain  )
{
	*pfHpaSingleProportional = xBoosterParameters.xPidSmValuesBooster.fPGain;
	*pfHpasingleIntegralGain = xBoosterParameters.xPidSmValuesBooster.fIGain ;
	*pfHpasingleDerivativeGain = xBoosterParameters.xPidSmValuesBooster.fDGain ;
}

void vUpdateHpaMm1PIDValues( float fLnasingleProportional, float fLnasingleIntegralGain,	float fLnasingleDerivativeGain  )
{
	xBoosterParameters.xPidMm1ValuesBooster.fPGain = fLnasingleProportional;
	xBoosterParameters.xPidMm1ValuesBooster.fIGain = fLnasingleIntegralGain;
	xBoosterParameters.xPidMm1ValuesBooster.fDGain = fLnasingleDerivativeGain;
}
void vUpdateHpaMm2PIDValues( float fLnasingleProportional, float fLnasingleIntegralGain,	float fLnasingleDerivativeGain  )
{
	xBoosterParameters.xPidMm2ValuesBooster.fPGain = fLnasingleProportional;
	xBoosterParameters.xPidMm2ValuesBooster.fIGain = fLnasingleIntegralGain;
	xBoosterParameters.xPidMm2ValuesBooster.fDGain = fLnasingleDerivativeGain;
}

void vUpdateHpaMm1and2PIDValues( float fHpaMM1and2Proportional, float fHpaMM1and2IntegralGain,	float fHpaMM1and2DerivativeGain  )
{
	xBoosterParameters.xPidMm1and2ValuesBooster.fPGain = fHpaMM1and2Proportional;
	xBoosterParameters.xPidMm1and2ValuesBooster.fIGain = fHpaMM1and2IntegralGain;
	xBoosterParameters.xPidMm1and2ValuesBooster.fDGain = fHpaMM1and2DerivativeGain;
}

void vEnableLna(eBool_t bEnable)
{
	vBinaryOtputSetState( eOutputLnaLddEna, !bEnable );
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = (bEnable== eTrue)? 1 : 0;
	
}

void vEnableHpaSingleMode( eBool_t bEnable )
{
	vBinaryOtputSetState( eOutputHpaSmLddEna , !bEnable );
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserSingleModeStatus = (bEnable== eTrue)? 1 : 0;
}

void vEnableHpaMultiMode1( eBool_t bEnable )
{
	vBinaryOtputSetState( eOutputHpaMmLddEna1 , bEnable );
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode1Status = (bEnable== eTrue)? 1 : 0;
}
void vEnableHpaMultiMode2( eBool_t bEnable )
{
	vBinaryOtputSetState( eOutputHpaMmLddEna2 , bEnable );
	xAmplifierDescriptor.c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode2Status = (bEnable== eTrue)? 1 : 0;
}
/*------------------------------------------*/
xPumpTemperaturesLimits_t * vpGetPumpTemperatureLimits( void)
{
	return &(xAmplifierDescriptor.xPumpTemperaturesLimits);
	
}
/*
void vEnableDisableLnaFunction(eBool_t bEnable)
{
	
}
void vEnableDisableBoosterFunction(eBool_t bEnable)
{
	
}
void vReportEnableFunction(eBool_t bEnable)
{
	
}*/
/*
eAlarmType_t eAlarmDetectorBooster(void)
{
	eAlarmType_t eAlarmType = eAlarm_none;
	
		xAmplifierDescriptor
		eAlarm_LnaCurrentLow = 6,
		eAlarm_LnaCurrentHigh = 7
	
	return eAlarmType;
}

eAlarmType_t eAlarmDetectorLna(void)
{
	eAlarmType_t eAlarmType = eAlarm_none;
		
		
		
	return eAlarmType;
}*/
/*----------*/
/*
eBool_t vGetUpdateLnaMemoryWriteNeeded(void)
{
	return xAmplifierDescriptor.bWriteLnaMemoryNeeded;
}
void vSetUpdateLnaMemoryWriteNeeded(eBool_t bWriteMemoryNeeded)
{
	xAmplifierDescriptor.bWriteLnaMemoryNeeded = bWriteMemoryNeeded;
}*/

/*--------------*/
/*eBool_t vGetUpdateBoosterMemoryWriteNeeded(void)
{
	return xAmplifierDescriptor.bWriteBoosterMemoryNeeded;
}
void vSetUpdateBoosterMemoryWriteNeeded(eBool_t bWriteMemoryNeeded)
{
	xAmplifierDescriptor.bWriteBoosterMemoryNeeded = bWriteMemoryNeeded;
}*/