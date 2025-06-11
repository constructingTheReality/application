/**
  * @file 			BSPDac.c
  * @brief			BSPDac source file.
  * @author			juan andres
  * @date			Created on 3/4/2021
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

#include "BSPDac.h"
#include "BSPAdc.h"
#include "glue.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/*#include "va416xx.h"
#include "va416xx_hal.h"
#include "va416xx_hal_dac.h"
#include "va416xx_hal_irqrouter.h"
#include "va416xx_hal_dma.h"
#include "va416xx_hal_timer.h"
#include "va416xx_debug.h"*/

/* Private define ----------------------------------------------------------- */

#define DAC_NUMBER_CHANNEL							( eNumberOfDacChannel )
#define DAC0_TIM_NUM  									( 13 )  //10
#define DAC1_TIM_NUM  									( 16 )//11
#define ADC_FAST_TIM_NUM								( 12 )

#define DAC0_DMA_CH   (0)
#define DAC1_DMA_CH   (1)

/** PWM frequency in Hz */
#define PWM_FREQUENCY      1000
/** Period value of PWM output waveform */
#define PERIOD_VALUE       100
/** Initial duty cycle value */
#define INIT_DUTY_VALUE    0

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
//static eBool_t bSystemIsInModulation = eFalse;
//static eBool_t bAlternanceBetweenPowerAndCurrent = eFalse; 
//static eBool_t bIsTestModeGlobal = eFalse; 
//static eBool_t bSystemIsBoosted= eTrue;
//static bool go0 = 0;
//static bool go10 = 0;
//static bool go1 = 0;
//static bool go2 = 0;
//static bool go3= 0;
//static uint8_t gPeriodUsec = 0;
//static eDacChannel_t eGlobalChannel;
//static uint8_t numberOfSamples980 = 1;// 1
//static uint8_t numberOfSamples940 = 1; //4
//static uint8_t globalPeriod = 30;
//static uint32_t *pNVIC_ISPRBase = (uint32_t*)0xE000E204;

/** PWM channel instance for LEDs */
pwm_channel_t g_pwm_channel_led;

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/* Private functions -------------------------------------------------------- */

/* Exported functions ------------------------------------------------------- */

void vBSPDacInitAndStart( void )
{	
	

/*	hal_status_t status;
		
	HAL_DAC_Reset();
	
  status = HAL_DAC_Init(VOR_DAC0);
  if(status != hal_status_ok)
	{
		vMpblibsAssertParam(0);
  }
	
  status = HAL_DAC_Init(VOR_DAC1);
  if(status != hal_status_ok)
	{
		vMpblibsAssertParam(0);
  }	
	*/
}

/*----------------------------------------------------------------------------*/
void vBSPDacSetOutputMv( eDacChannel_t eChannel,  uint16_t usOutputValueMv )
{
	/*hal_status_t hal_status;
	
  if( eChannel > eNumberOfDacChannel )
	{ 
		vMpblibsAssertParam(0);
	}
	
  if( usOutputValueMv > 0xfff)
	{ 
		usOutputValueMv = 0xfff; 
	}
  
	eGlobalChannel = eChannel;
	
	

		
	
	
  if( eChannel == eDac1545DiodeOutput)
	{		
		usModulation940Value = (uint16_t)usOutputValueMv ;
		usModulation940LowValue = usLowOutputValueMv;
		
		if( bSystemIsInModulation == eFalse )
		{
			hal_status = HAL_DAC_ManualTrigger(VOR_DAC0, (uint16_t)usOutputValueMv); 
			if ( hal_status != hal_status_ok )
			{
				vMpblibsAssertParam(0);
			}
		}
	
	}	
  //else 
	if( eChannel == eDac980DiodeOutput)
  { 
		usModulation980Value = (uint16_t)usOutputValueMv ;
		usModulation980LowValue = usLowOutputValueMv;
		
		
		
		if( bSystemIsInModulation == eFalse )
		{
			hal_status = HAL_DAC_ManualTrigger(VOR_DAC1, (uint16_t)usOutputValueMv); 
			if ( hal_status != hal_status_ok )
			{
				vMpblibsAssertParam(0);
			}
		}	
  }*/
	
}
void vBSPDacSetOutputDuty( eDacChannel_t eChannel,  uint8_t ucDutyCycle)
{
	//hal write pwm duty
}
/*----------------------------------------------------------------------------------*/



