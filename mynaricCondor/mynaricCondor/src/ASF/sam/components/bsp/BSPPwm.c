/**
  * @file 			BSPPwm.c
  * @brief			BSPPwm source file.
  * @author			juan andres
  * @date			Created on 3/4/2023
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB.</center>
  *
  **/
  
/* Includes ----------------------------------------------------------------- */

#include "BSPPwm.h"
#include "glue.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* Private define ----------------------------------------------------------- */

#define PWM_NUMBER_CHANNEL							( eNumberOfPwmChannel )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static const uint32_t ulPwmChannelNumber[ PWM_NUMBER_CHANNEL ] =
{
	#define X( PwmChannelId ,Channel, Alignment, InitialPolarity, InitialDutyCycle, Period )	Channel,
	LIST_OF_PWM_CHANNELS
	#undef X
};
static const uint32_t ulPwmChannelAlignment[ PWM_NUMBER_CHANNEL ] =
{
	#define X( PwmChannelId ,Channel, Alignment, InitialPolarity, InitialDutyCycle, Period)	Alignment,
	LIST_OF_PWM_CHANNELS
	#undef X
};
static const uint32_t ulPwmChannelInitialPolarity[ PWM_NUMBER_CHANNEL ] =
{
	#define X( PwmChannelId ,Channel, Alignment, InitialPolarity, InitialDutyCycle, Period )	InitialPolarity,
	LIST_OF_PWM_CHANNELS
	#undef X
};

static const uint32_t ulPwmChannelInitialDutyCycle[ PWM_NUMBER_CHANNEL ] =
{
	#define X( PwmChannelId ,Channel, Alignment, InitialPolarity, InitialDutyCycle, Period)	InitialDutyCycle,
	LIST_OF_PWM_CHANNELS
	#undef X
};
static const uint32_t ulPwmChannelPeriod[ PWM_NUMBER_CHANNEL ] =
{
	#define X( PwmChannelId ,Channel, Alignment, InitialPolarity, InitialDutyCycle, Period )	Period,
	LIST_OF_PWM_CHANNELS
	#undef X
};
/* Private functions -------------------------------------------------------- */

pwm_channel_t g_pwm_channel_led[PWM_NUMBER_CHANNEL];

/* Exported functions ------------------------------------------------------- */

void vBSPPwmInitAndStart( void )
{	
	
	for( uint8_t ucI = 0; ucI < PIN_PWM_HPA_MM_CLK1_CHANNEL ; ucI++ ) //PWM_NUMBER_CHANNEL
	{
		pwm_channel_disable(PWM, ulPwmChannelNumber[ucI]);
		g_pwm_channel_led[ucI].channel = ulPwmChannelNumber[ucI];
		g_pwm_channel_led[ucI].alignment = ulPwmChannelAlignment[ucI];
		g_pwm_channel_led[ucI].polarity = ulPwmChannelInitialPolarity[ucI];
		g_pwm_channel_led[ucI].ul_prescaler = PWM_CMR_CPRE_CLKA;
		g_pwm_channel_led[ucI].ul_period = ulPwmChannelPeriod[ucI];
		g_pwm_channel_led[ucI].ul_duty = ulPwmChannelInitialDutyCycle[ucI];
		pwm_channel_init(PWM, &g_pwm_channel_led[ucI]);
		pwm_channel_disable_interrupt(PWM, ulPwmChannelNumber[ucI], 0);
		pwm_channel_enable(PWM, ulPwmChannelNumber[ucI]);
	}
	
	for( uint8_t ucI = PIN_PWM_HPA_MM_CLK1_CHANNEL; ucI < PWM_NUMBER_CHANNEL; ucI++ )
	{
		pwm_channel_disable(PWM, ulPwmChannelNumber[ucI]);
		g_pwm_channel_led[ucI].channel = ulPwmChannelNumber[ucI];
		g_pwm_channel_led[ucI].alignment = ulPwmChannelAlignment[ucI];
		g_pwm_channel_led[ucI].polarity = ulPwmChannelInitialPolarity[ucI];
		g_pwm_channel_led[ucI].ul_prescaler = PWM_CMR_CPRE_MCK;//PWM_CMR_CPRE_CLKB; //PWM_CMR_CPRE_MCK
		g_pwm_channel_led[ucI].ul_period = ulPwmChannelPeriod[ucI];
		g_pwm_channel_led[ucI].ul_duty = ulPwmChannelInitialDutyCycle[ucI];
  		pwm_channel_init(PWM, &g_pwm_channel_led[ucI]);
		pwm_channel_disable_interrupt(PWM, ulPwmChannelNumber[ucI], 0);
		pwm_channel_enable(PWM, ulPwmChannelNumber[ucI]);
	}
	
	
		/* Set PWM clock A as PWM_FREQUENCY*PERIOD_VALUE (clock B is not used) */
		pwm_clock_t clock_setting = {
			.ul_clka = PWM_FREQUENCY * PERIOD_VALUE ,
			.ul_clkb = 0,//1400000 * 100,//20* PWM_FREQUENCY * PERIOD_VALUE ,
			.ul_mck = sysclk_get_cpu_hz()
		};
		
		pwm_init(PWM, &clock_setting);
		
}

/*----------------------------------------------------------------------------*/
void vBSPPwmSetOutputDuty( ePwmChannel_t eChannel,  uint32_t ucDutyCycle)
{
		pwm_channel_update_duty(PWM, &g_pwm_channel_led[eChannel], ucDutyCycle);
}
/*----------------------------------------------------------------------------------*/


