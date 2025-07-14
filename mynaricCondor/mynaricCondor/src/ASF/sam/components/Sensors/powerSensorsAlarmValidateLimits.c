/**
* @file           powerSensorsAlarmValidateLimits.c
* @brief
*                 Validate the values of the booster alarm limits
* @author         Isabelle Champion
* @date           Created on 08/07/2024
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2024 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/
/* Includes ------------------------------------------------------------------*/
#include "PowerSensorsAlarmValidateLimits.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

eMpbError_t ePowerSensorValidateOutputLimits( eBool_t* pbOutputCheckC408, float fHighAlarmLimitBoosterPowerOutput, float fLowAlarmLimitBoosterPowerOutput, eBool_t bIsBooster)
{
	float Y1_HighLimitOutput, Y2_HighLimitOutput, Y1_LowLimitOutput;//, Y2_LowLimitOutput;

	unsigned int precision = 100;
	
	if (pbOutputCheckC408 == NULL)
	{
		return eInvalidParameter;
	}
	
	if (bIsBooster == eTrue)
	{
		Y1_HighLimitOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
		Y2_HighLimitOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_BOOSTER;
		Y1_LowLimitOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
		//Y2_LowLimitOutput = Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_BOOSTER;
	}
	else {
		Y1_HighLimitOutput = Y1_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
		Y2_HighLimitOutput = Y2_408_ALARM_HIGH_LIMIT_POWER_OUTPUT_LNA;
		Y1_LowLimitOutput = Y1_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;
		//	Y2_LowLimitOutput = Y2_408_ALARM_LOW_LIMIT_POWER_OUTPUT_LNA;

	}
	

	*pbOutputCheckC408 = (
	( mpb_float1_minor_than_float2(Y1_HighLimitOutput, fHighAlarmLimitBoosterPowerOutput, precision) )
	//|| (Y1_HighLimitOutput ==  fHighAlarmLimitBoosterPowerOutput) )
	
	&&  ( mpb_float1_minor_than_float2(fHighAlarmLimitBoosterPowerOutput, Y2_HighLimitOutput, precision) )
	//|| (fHighAlarmLimitBoosterPowerOutput ==  Y2_HighLimitOutput) )
	
	&&  ( mpb_float1_minor_than_float2(Y1_LowLimitOutput, fLowAlarmLimitBoosterPowerOutput, precision))
	//|| (Y1_LowLimitOutput == fLowAlarmLimitBoosterPowerOutput) )

	&&	mpb_float1_minor_than_float2(fLowAlarmLimitBoosterPowerOutput, fHighAlarmLimitBoosterPowerOutput, precision)
	
	//&&	(c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerOutput <= Y2_LowLimitOutput)

	);

	return eSuccess;
}

/*----------------------------------------------------------------------------*/

eMpbError_t ePowerSensorValidateInputLimits( eBool_t* pbInputCheckC408,  float fHighAlarmLimitBoosterPowerInput, float fLowAlarmLimitBoosterPowerInput, eBool_t bIsBooster)
{
	float Y1_HighLimitInput, Y2_HighLimitInput, Y1_LowLimitInput;//, Y2_LowLimitInput;
	unsigned int precision = 100;

	if (pbInputCheckC408 == NULL)
	{
		return eInvalidParameter;
	}
	if (bIsBooster)
	{
		Y1_HighLimitInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
		Y2_HighLimitInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_BOOSTER;
		Y1_LowLimitInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
		//	Y2_LowLimitInput = Y2_408_ALARM_LOW_LIMIT_POWER_INPUT_BOOSTER;
	}
	else
	{
		Y1_HighLimitInput = Y1_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
		Y2_HighLimitInput = Y2_408_ALARM_HIGH_LIMIT_POWER_INPUT_LNA;
		Y1_LowLimitInput = Y1_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
		//	Y2_LowLimitInput = Y2_408_ALARM_LOW_LIMIT_POWER_INPUT_LNA;
	}

	*pbInputCheckC408 = ( 	
	
	//( mpb_float1_minor_than_float2(Y1_HighLimitInput, fHighAlarmLimitBoosterPowerInput , precision)	) //||
	//(Y1_HighLimitInput == fHighAlarmLimitBoosterPowerInput) )
	
	  ( !mpb_float1_minor_than_float2(Y2_HighLimitInput, fHighAlarmLimitBoosterPowerInput,   precision))
	//|| (fHighAlarmLimitBoosterPowerInput ==  Y2_HighLimitInput) )
	
	&&  ( mpb_float1_minor_than_float2(Y1_LowLimitInput, fLowAlarmLimitBoosterPowerInput, precision) )
	//|| (Y1_LowLimitInput == fLowAlarmLimitBoosterPowerInput) )

	&&  mpb_float1_minor_than_float2(fLowAlarmLimitBoosterPowerInput, fHighAlarmLimitBoosterPowerInput , precision)

	//&&  (c408StatusDefinition.fBoosterSetStatusAlarmLowLimitForPowerInput <= Y2_LowLimitInput) );

	);

	return eSuccess;

}