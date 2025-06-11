/**
 * \file
 *
 * \brief Analog-to-Digital Converter (ADC/ADC12B) example for SAM.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */


#include <string.h>
#include "asf.h"
//#include "conf_board.h"

/*
 * We use two ADC channels for this example:
 *    ADC_CHANNEL_5  (potentiometer)
 *    ADC_CHANNEL_15 (temperature sensor)
 */
#define NUM_CHANNELS    (14)
/** Size of the receive buffer and transmit buffer. */
#define BUFFER_SIZE     NUM_CHANNELS


/** ADC convention done mask. */
#define ADC_DONE_MASK   ( (1<<NUM_CHANNELS) - 1 )

#define channelNumber  14

//#define ADC_CHANNEL_CURRENT  ADC_CHANNEL_0
//#define ADC_CHANNEL_VOLTAGE  ADC_CHANNEL_1

#define	Adc28VPwrCurrentMonitorCH1  ADC_CHANNEL_0
#define	Adc28VPwrCurrentMonitorCH2  ADC_CHANNEL_1
#define	Adc28VPwrVoltageMonitorCH1  ADC_CHANNEL_2
#define	Adc28VPwrVoltageMonitorCH2  ADC_CHANNEL_3
#define	Adc7VPwrVoltageMonitorCH1   ADC_CHANNEL_4
#define	Adc7VPwrVoltageMonitorCH2   ADC_CHANNEL_5
#define	Adc3_3VPower_VoltageMonitor ADC_CHANNEL_6
#define	Adc3VPower_VoltageMonitor   ADC_CHANNEL_7

#define	AdcPowerCurrentMonitor      ADC_CHANNEL_8
#define	AdcCanPwrCurrentMonitorCH1  ADC_CHANNEL_9
#define	AdcCanPwrCurrentMonitorCH2  ADC_CHANNEL_10

#define	AdcLnaPdInput2				ADC_CHANNEL_11
#define	AdcPdReference				ADC_CHANNEL_12	
#define	AdcLnaPdInput1				ADC_CHANNEL_13
	
/** There are two peripherals ADC and ADC12B in SAM3U, you can select one of them. */

/* Tracking Time*/
#define TRACKING_TIME         1
/* Transfer Period */
#define TRANSFER_PERIOD       1
#define STARTUP_TIME               3

/* Sample & Hold Time */
#define SAMPLE_HOLD_TIME   6


/** ADC test mode structure */
struct {
	uint8_t uc_trigger_mode;
	uint8_t uc_pdc_en;
	uint8_t uc_sequence_en;
	uint8_t uc_gain_en;
	uint8_t uc_offset_en;
} g_adc_test_mode;

/** ADC trigger modes */
enum {
	TRIGGER_MODE_SOFTWARE = 0,
	TRIGGER_MODE_ADTRG,
	TRIGGER_MODE_TIMER,
	TRIGGER_MODE_PWM,
	TRIGGER_MODE_FREERUN

} e_trigger_mode;

/** ADC sample data */
struct {
	uint8_t uc_ch_num[channelNumber];
	uint16_t us_value[channelNumber];
	uint16_t us_done;
} g_adc_sample_data;


/**Channel list for sequence*/
enum adc_channel_num_t ch_list[channelNumber] = 
{
	//ADC_CHANNEL_CURRENT,
	//ADC_CHANNEL_VOLTAGE
	Adc28VPwrCurrentMonitorCH1 , 
	Adc28VPwrCurrentMonitorCH2 , 
	Adc28VPwrVoltageMonitorCH1 , 
	Adc28VPwrVoltageMonitorCH2 , 
	Adc7VPwrVoltageMonitorCH1  , 
	Adc7VPwrVoltageMonitorCH2  , 
	Adc3_3VPower_VoltageMonitor, 
	Adc3VPower_VoltageMonitor  , 

	AdcPowerCurrentMonitor      ,
	AdcCanPwrCurrentMonitorCH1  ,
	AdcCanPwrCurrentMonitorCH2  ,

	AdcLnaPdInput2				,
	AdcPdReference				,
	AdcLnaPdInput1				
};

/** Global timestamp in milliseconds since start of application */
//static volatile uint32_t gs_ul_ms_ticks = 0;




/**
 * \brief Read converted data through PDC channel.
 *
 * \param p_adc The pointer of adc peripheral.
 * \param p_s_buffer The destination buffer.
 * \param ul_size The size of the buffer.
 */

static uint32_t adc_read_buffer(Adc * p_adc, uint16_t * p_s_buffer, uint32_t ul_size)
{
	/* Check if the first PDC bank is free. */
	if ((p_adc->ADC_RCR == 0) && (p_adc->ADC_RNCR == 0)) {
		p_adc->ADC_RPR = (uint32_t) p_s_buffer;
		p_adc->ADC_RCR = ul_size;
		p_adc->ADC_PTCR = ADC_PTCR_RXTEN;

		return 1;
	} else { /* Check if the second PDC bank is free. */
		if (p_adc->ADC_RNCR == 0) {
			p_adc->ADC_RNPR = (uint32_t) p_s_buffer;
			p_adc->ADC_RNCR = ul_size;

			return 1;
		} else {
			return 0;
		}
	}
}


/**
 * \brief Start ADC sample.
 * Initialize ADC, set clock and timing, and set ADC to given mode.
 */
static void start_adc(void)
{
	/* Enable peripheral clock. */

	uint32_t i;
	pmc_enable_periph_clk(ID_ADC);

	/* Initialize ADC. */
	/*
	 * Formula: ADCClock = MCK / ( (PRESCAL+1) * 2 )
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 * ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */

	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Startup time = 64 / 6.4MHz = 10 us
	 */
	adc_init(ADC, sysclk_get_cpu_hz(), 6400000, ADC_STARTUP_TIME_4);

	memset((void *)&g_adc_sample_data, 0, sizeof(g_adc_sample_data));

	/* Set ADC timing. */

	/* Formula:
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 *
	 *     Transfer Time = (1 * 2 + 3) / 6.4MHz = 781 ns
	 *     Tracking Time = (1 + 1) / 6.4MHz = 312 ns
	 *     Settling Time = 3 / 6.4MHz = 469 ns
	 */
	adc_configure_timing(ADC, TRACKING_TIME, ADC_SETTLING_TIME_3, TRANSFER_PERIOD);


	/* Enable channel number tag. */
	adc_enable_tag(ADC);
	/* Enable/disable sequencer. */
	if (g_adc_test_mode.uc_sequence_en) {
		/* Set user defined channel sequence. */
		adc_configure_sequence(ADC, ch_list, channelNumber ); //2);

		/* Enable sequencer. */
		adc_start_sequencer(ADC);

		/* Enable channels. */
		for (i = 0; i < channelNumber; i++ )//2; i++) {
		{	
			adc_enable_channel(ADC, (enum adc_channel_num_t)i);
		}
		/* Update channel number. */
		g_adc_sample_data.uc_ch_num[0] = ch_list[0];
		g_adc_sample_data.uc_ch_num[1] = ch_list[1];
		g_adc_sample_data.uc_ch_num[2] = ch_list[2];
		g_adc_sample_data.uc_ch_num[3] = ch_list[3];
		g_adc_sample_data.uc_ch_num[4] = ch_list[4];
		g_adc_sample_data.uc_ch_num[5] = ch_list[5];
		
		g_adc_sample_data.uc_ch_num[6] = ch_list[6];
		g_adc_sample_data.uc_ch_num[7] = ch_list[7];
		g_adc_sample_data.uc_ch_num[8] = ch_list[8];
		
		g_adc_sample_data.uc_ch_num[9] = ch_list[9];
		g_adc_sample_data.uc_ch_num[10] = ch_list[10];
		g_adc_sample_data.uc_ch_num[11] = ch_list[11];
		g_adc_sample_data.uc_ch_num[12] = ch_list[12];
		g_adc_sample_data.uc_ch_num[13] = ch_list[13];
		
			
	} else {
		/* Disable sequencer. */
		adc_stop_sequencer(ADC);

		/* Enable channels. */
		adc_enable_channel(ADC, Adc28VPwrCurrentMonitorCH1);
		adc_enable_channel(ADC, Adc28VPwrCurrentMonitorCH2);
		adc_enable_channel(ADC, Adc28VPwrVoltageMonitorCH1);
		adc_enable_channel(ADC, Adc28VPwrVoltageMonitorCH2);
		
		adc_enable_channel(ADC, Adc7VPwrVoltageMonitorCH1);
		adc_enable_channel(ADC, Adc7VPwrVoltageMonitorCH2);
		adc_enable_channel(ADC, Adc3_3VPower_VoltageMonitor);
		adc_enable_channel(ADC, Adc3VPower_VoltageMonitor);
		
		adc_enable_channel(ADC, AdcPowerCurrentMonitor);
		adc_enable_channel(ADC, AdcCanPwrCurrentMonitorCH1);
		adc_enable_channel(ADC, AdcCanPwrCurrentMonitorCH2);
		adc_enable_channel(ADC, AdcLnaPdInput2);
		
		adc_enable_channel(ADC,AdcPdReference );
		adc_enable_channel(ADC,AdcLnaPdInput1);
//#if SAM3S || SAM3XA || SAM4S || SAM4C
		//adc_enable_channel(ADC, ADC_TEMPERATURE_SENSOR);
//#endif
		/* Update channel number. */
		g_adc_sample_data.uc_ch_num[0] = Adc28VPwrCurrentMonitorCH1;
		g_adc_sample_data.uc_ch_num[1] = Adc28VPwrCurrentMonitorCH2;
		g_adc_sample_data.uc_ch_num[2] = Adc28VPwrVoltageMonitorCH1;
		g_adc_sample_data.uc_ch_num[3] = Adc28VPwrVoltageMonitorCH2;


		g_adc_sample_data.uc_ch_num[4] = Adc7VPwrVoltageMonitorCH1;
		g_adc_sample_data.uc_ch_num[5] = Adc7VPwrVoltageMonitorCH2;
		g_adc_sample_data.uc_ch_num[6] = Adc3_3VPower_VoltageMonitor;
		g_adc_sample_data.uc_ch_num[7] = Adc3VPower_VoltageMonitor;
		
		
		g_adc_sample_data.uc_ch_num[8] = AdcPowerCurrentMonitor;
		g_adc_sample_data.uc_ch_num[9] = AdcCanPwrCurrentMonitorCH1;
		g_adc_sample_data.uc_ch_num[10] = AdcCanPwrCurrentMonitorCH2;
		g_adc_sample_data.uc_ch_num[11] = AdcLnaPdInput2;				
		
		g_adc_sample_data.uc_ch_num[12] = AdcPdReference;
		g_adc_sample_data.uc_ch_num[13] = AdcLnaPdInput1;
//#if SAM3S || SAM3XA || SAM4S || SAM4C
		//g_adc_sample_data.uc_ch_num[1] = ADC_TEMPERATURE_SENSOR;
//#else
//		g_adc_sample_data.uc_ch_num[1] = ADC_CHANNEL_POTENTIOMETER;
//#endif
	}


	/* Enable the temperature sensor. */
	adc_enable_ts(ADC);

	/* Set gain and offset (only single ended mode used here). */

	adc_disable_anch(ADC); /* Disable analog change. */

	if (g_adc_test_mode.uc_gain_en) {

		adc_enable_anch(ADC);
		/* gain = 2 */
		adc_set_channel_input_gain(ADC, Adc28VPwrCurrentMonitorCH1, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, Adc28VPwrCurrentMonitorCH2, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, Adc28VPwrVoltageMonitorCH1, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, Adc28VPwrVoltageMonitorCH2, ADC_GAINVALUE_2);
		
		adc_set_channel_input_gain(ADC, Adc7VPwrVoltageMonitorCH1, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, Adc7VPwrVoltageMonitorCH2, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, Adc3_3VPower_VoltageMonitor, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, Adc3VPower_VoltageMonitor, ADC_GAINVALUE_2);
		
		adc_set_channel_input_gain(ADC, AdcPowerCurrentMonitor, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, AdcCanPwrCurrentMonitorCH1 , ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, AdcCanPwrCurrentMonitorCH2, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, AdcLnaPdInput2, ADC_GAINVALUE_2);
		
		adc_set_channel_input_gain(ADC, AdcPdReference, ADC_GAINVALUE_2);
		adc_set_channel_input_gain(ADC, AdcLnaPdInput1, ADC_GAINVALUE_2);
						
				
	} else {

		/* gain = 1 */
		adc_set_channel_input_gain(ADC, Adc28VPwrCurrentMonitorCH1, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, Adc28VPwrCurrentMonitorCH2, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, Adc28VPwrVoltageMonitorCH1, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, Adc28VPwrVoltageMonitorCH2, ADC_GAINVALUE_0);
		
		adc_set_channel_input_gain(ADC, Adc7VPwrVoltageMonitorCH1 , ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, Adc7VPwrVoltageMonitorCH2, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, Adc3_3VPower_VoltageMonitor, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, Adc3VPower_VoltageMonitor, ADC_GAINVALUE_0);

		adc_set_channel_input_gain(ADC, AdcPowerCurrentMonitor, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, AdcCanPwrCurrentMonitorCH1, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, AdcCanPwrCurrentMonitorCH2, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, AdcLnaPdInput2, ADC_GAINVALUE_0);

		adc_set_channel_input_gain(ADC, AdcPdReference, ADC_GAINVALUE_0);
		adc_set_channel_input_gain(ADC, AdcLnaPdInput1, ADC_GAINVALUE_0);
						
		

	}

	if (g_adc_test_mode.uc_offset_en) {

		adc_enable_anch(ADC);
		adc_enable_channel_input_offset(ADC, Adc28VPwrCurrentMonitorCH1);
		adc_enable_channel_input_offset(ADC, Adc28VPwrCurrentMonitorCH2);
		adc_enable_channel_input_offset(ADC, Adc28VPwrVoltageMonitorCH1);
		adc_enable_channel_input_offset(ADC, Adc28VPwrVoltageMonitorCH2);
		
		adc_enable_channel_input_offset(ADC, Adc7VPwrVoltageMonitorCH1);
		adc_enable_channel_input_offset(ADC, Adc7VPwrVoltageMonitorCH2);
		adc_enable_channel_input_offset(ADC, Adc3_3VPower_VoltageMonitor);
		adc_enable_channel_input_offset(ADC, Adc3VPower_VoltageMonitor );
		
		adc_enable_channel_input_offset(ADC, AdcPowerCurrentMonitor);
		adc_enable_channel_input_offset(ADC,AdcCanPwrCurrentMonitorCH1 );
		adc_enable_channel_input_offset(ADC, AdcCanPwrCurrentMonitorCH2 );
		adc_enable_channel_input_offset(ADC,AdcLnaPdInput2 );
		
		adc_enable_channel_input_offset(ADC, AdcPdReference);
		adc_enable_channel_input_offset(ADC,AdcLnaPdInput1 );
					
		
	} else {

		adc_disable_channel_input_offset(ADC, Adc28VPwrCurrentMonitorCH1);
		adc_disable_channel_input_offset(ADC, Adc28VPwrCurrentMonitorCH2);
		adc_disable_channel_input_offset(ADC, Adc28VPwrVoltageMonitorCH1);
		adc_disable_channel_input_offset(ADC, Adc28VPwrVoltageMonitorCH2);

		adc_disable_channel_input_offset(ADC,Adc7VPwrVoltageMonitorCH1 );
		adc_disable_channel_input_offset(ADC,Adc7VPwrVoltageMonitorCH2 );
		adc_disable_channel_input_offset(ADC,Adc3_3VPower_VoltageMonitor );
		adc_disable_channel_input_offset(ADC, Adc3VPower_VoltageMonitor);

		adc_disable_channel_input_offset(ADC, AdcPowerCurrentMonitor);
		adc_disable_channel_input_offset(ADC, AdcCanPwrCurrentMonitorCH1);
		adc_disable_channel_input_offset(ADC, AdcCanPwrCurrentMonitorCH2);
		adc_disable_channel_input_offset(ADC, AdcLnaPdInput2);
		
		adc_disable_channel_input_offset(ADC,AdcPdReference );
		adc_disable_channel_input_offset(ADC, AdcLnaPdInput1);
					
				
	}
	/* Set Auto Calibration Mode. */


	
	


	/* Transfer with/without PDC. */
	if (g_adc_test_mode.uc_pdc_en) {
		adc_read_buffer(ADC, g_adc_sample_data.us_value, BUFFER_SIZE);
		/* Enable PDC channel interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_RXBUFF);
	} else {
		/* Enable Data ready interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_DRDY);
	}
	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC_IRQn);

	/* Configure trigger mode and start convention. */
	switch (g_adc_test_mode.uc_trigger_mode) {
	case TRIGGER_MODE_SOFTWARE:

		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);	/* Disable hardware trigger. */
		break;

	case TRIGGER_MODE_ADTRG:

		gpio_configure_pin(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);
		adc_configure_trigger(ADC, ADC_TRIG_EXT, 0);
		break;

	case TRIGGER_MODE_TIMER:
	//	configure_time_trigger();
		break;

	case TRIGGER_MODE_PWM:
	//	configure_pwm_trigger();
		break;


	case TRIGGER_MODE_FREERUN:
		adc_configure_trigger(ADC, ADC_TRIG_SW, 1);
		break;

	default:
		break;
	}
}



void HAL_ADC_Init(void)
{
		/* Set default ADC test mode. */
		memset((void *)&g_adc_test_mode, 0, sizeof(g_adc_test_mode));
		g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_SOFTWARE; //TRIGGER_MODE_FREERUN; //TRIGGER_MODE_SOFTWARE ;//TRIGGER_MODE_FREERUN; //TRIGGER_MODE_SOFTWARE;
		g_adc_test_mode.uc_pdc_en = 1;
		g_adc_test_mode.uc_sequence_en = 0;
		g_adc_test_mode.uc_gain_en = 0;
		g_adc_test_mode.uc_offset_en = 0;

		
		start_adc();
	
}

void HAL_ADC_Update(uint16_t *pusprvAdcSampleResult,uint16_t *pusprvAdcAccumulator, uint8_t ucNumberOfChannels )
{

	uint8_t i = 0;
	
	adc_start(ADC);

	
	if (g_adc_sample_data.us_done == ADC_DONE_MASK)
	{
		
		for (i = 0; i < ucNumberOfChannels; i++)
		{
			
			pusprvAdcSampleResult[i] = 	(int)(g_adc_sample_data.us_value[i] );
			pusprvAdcAccumulator[ i ] += (int)(g_adc_sample_data.us_value[i] );
			
		}
		
		g_adc_sample_data.us_done = 0;
	}
}

/**
 * \brief Interrupt handler for the ADC.
 */
void ADC_Handler(void)
{
	uint32_t i;
	uint32_t ul_temp;
	uint8_t uc_ch_num;

	/* With PDC transfer */
	if (g_adc_test_mode.uc_pdc_en) {
		if ((adc_get_status(ADC) & ADC_ISR_RXBUFF) ==
				ADC_ISR_RXBUFF) {
			g_adc_sample_data.us_done = ADC_DONE_MASK;
			adc_read_buffer(ADC, g_adc_sample_data.us_value, BUFFER_SIZE);
			/* Only keep sample value, and discard channel number. */
			for (i = 0; i < NUM_CHANNELS; i++) {
				g_adc_sample_data.us_value[i] &= ADC_LCDR_LDATA_Msk;
			}
		}
	} else {	/* Without PDC transfer */
		if ((adc_get_status(ADC) & ADC_ISR_DRDY) ==
				ADC_ISR_DRDY) {
			ul_temp = adc_get_latest_value(ADC);
			for (i = 0; i < NUM_CHANNELS; i++) {
				uc_ch_num = (ul_temp & ADC_LCDR_CHNB_Msk) >>
						ADC_LCDR_CHNB_Pos;
				if (g_adc_sample_data.uc_ch_num[i] == uc_ch_num) {
					g_adc_sample_data.us_value[i] =
							ul_temp &
							ADC_LCDR_LDATA_Msk;
					g_adc_sample_data.us_done |= 1 << i;
				}
			}
		}
	}
}

