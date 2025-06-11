/**
 * \file
 *
 * \brief SAM3X-EK board init.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "compiler.h"
#include "board.h"
#include "conf_board.h"
#include "gpio.h"
#include "ioport.h"

void board_init(void)
{
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
#endif

	/* GPIO has been deprecated, the old code just keeps it for compatibility.
	 * In new designs IOPORT is used instead.
	 * Here IOPORT must be initialized for others to use before setting up IO.
	 */
	ioport_init();

	/* Configure Power LED */
//	gpio_configure_pin(LED3_GPIO, LED3_FLAGS);
	//gpio_set_pin_high(LED3_GPIO); /* Turned on by default */

	/* Configure User LED pins */
	//gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	
//	gpio_configure_pin(LED1_GPIO, LED1_FLAGS);
//	gpio_configure_pin(LED2_GPIO, LED2_FLAGS);

	gpio_configure_pin(LNA_LDD_ENA_GPIO, LNA_LDD_ENA_FLAGS);
	gpio_configure_pin(HPA_SM_LDD_ENA_GPIO, HPA_SM_LDD_ENA_FLAGS);
	
	gpio_configure_pin(HPA_MM_LDD_ENA1_GPIO, HPA_MM_LDD_ENA1_FLAGS);
	gpio_configure_pin(HPA_MM_LDD_ENA2_GPIO, HPA_MM_LDD_ENA2_FLAGS);
	
	//gpio_configure_pin(HPA_MM_LDD_ENA2_GPIO, HPA_SM_LDD_ENA2_FLAGS);
	//gpio_configure_pin(HPA_MM_LDD_DIS1_GPIO, HPA_MM_LDD_DIS1_FLAGS);	
	
	gpio_configure_pin(FRAM_PWR_ENA_GPIO, FRAM_PWR_ENA_FLAGS);
	gpio_configure_pin(OUT_28V_PWR_DIS1_GPIO, OUT_28V_PWR_DIS1_FLAGS);
	gpio_configure_pin(OUT_28V_PWR_DIS2_GPIO, OUT_28V_PWR_DIS2_FLAGS);	
	gpio_configure_pin(ADC_VOLT_GPIO, ADC_VOLT_FLAGS);
	
	
	gpio_configure_pin(OUT_3V_PWR_ENA1_GPIO, OUT_3V_PWR_ENA1_FLAGS);
	gpio_configure_pin(OUT_3V_PWR_ENA2_GPIO, OUT_3V_PWR_ENA2_FLAGS);
	
	//ioport_set_pin_mode(ADC_PWR_ENA_GPIO, IOPORT_MODE_PULLUP);
	//ioport_set_pin_dir(ADC_PWR_ENA_GPIO, IOPORT_DIR_OUTPUT);
	
	//gpio_configure_pin(CAN_PWR_ENA1_GPIO, IOPORT_MODE_PULLUP);
	
	
	gpio_configure_pin(CAN_PWR_ENA1_GPIO, CAN_PWR_ENA1_FLAGS);
	gpio_configure_pin(CAN_PWR_ENA2_GPIO, CAN_PWR_ENA2_FLAGS);
	
	
	gpio_configure_pin(ADC_CS0_GPIO, ADC_CS0_FLAGS);
	gpio_configure_pin(ADC_CS1_GPIO, ADC_CS1_FLAGS);
	gpio_configure_pin(ADC_CS2_GPIO, ADC_CS2_FLAGS);
	
	//gpio_configure_pin(FRAM_CS_GPIO, FRAM_CS_FLAGS);
	gpio_configure_pin(FRAM_WP_GPIO, FRAM_WP_PORT);
	

#ifdef CONF_BOARD_UART_CONSOLE
	/* Configure UART pins */
	gpio_configure_group(PINS_UART_PIO, PINS_UART, PINS_UART_FLAGS);
#endif

	/* Configure ADC example pins */
#ifdef CONF_BOARD_ADC
	/* TC TIOA configuration */
	gpio_configure_pin(PIN_TC0_TIOA0,PIN_TC0_TIOA0_FLAGS);
	gpio_configure_pin(PIN_TC0_TIOA1,PIN_TC0_TIOA1_FLAGS);

	/* ADC Trigger configuration */
//	gpio_configure_pin(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);

	/* PWMH0 configuration */
//	gpio_configure_pin(PIN_PWMC_PWMH0_TRIG, PIN_PWMC_PWMH0_TRIG_FLAG);
#endif

#ifdef CONF_BOARD_PWM
	
	gpio_configure_pin(PIN_PWM_LNA_PWM_STP_GPIO, PIN_PWM_LNA_PWM_STP_FLAGS);
	gpio_configure_pin(PIN_PWM_HPA_SM_PWM_STP1_GPIO, PIN_PWM_HPA_SM_PWM_STP1_FLAGS);
	gpio_configure_pin(PIN_PWM_HPA_SM_PWM_STP2_GPIO, PIN_PWM_HPA_SM_PWM_STP2_FLAGS);
	gpio_configure_pin(PIN_PWM_HPA_MM_PWM_STP1_GPIO, PIN_PWM_HPA_MM_PWM_STP1_FLAGS);
	gpio_configure_pin(PIN_PWM_HPA_MM_PWM_STP2_GPIO, PIN_PWM_HPA_MM_PWM_STP2_FLAGS);
	gpio_configure_pin(PIN_PWM_HPA_MM_CLK1_GPIO, PIN_PWM_HPA_MM_CLK1_FLAGS);
	gpio_configure_pin(PIN_PWM_HPA_MM_CLK2_GPIO, PIN_PWM_HPA_MM_CLK2_FLAGS);
#endif	

	/* Configure SPI0 pins */
#ifdef CONF_BOARD_SPI0
	gpio_configure_pin(SPI0_MISO_GPIO, SPI0_MISO_FLAGS);
	gpio_configure_pin(SPI0_MOSI_GPIO, SPI0_MOSI_FLAGS);
	gpio_configure_pin(SPI0_SPCK_GPIO, SPI0_SPCK_FLAGS);

	//gpio_configure_pin(SPI0_NPCS0_GPIO, SPI0_NPCS0_FLAGS);
	//gpio_configure_pin(SPI0_NPCS1_GPIO, SPI0_NPCS1_FLAGS);
	//gpio_configure_pin(SPI0_NPCS3_PB23_GPIO, SPI0_NPCS3_PB23_FLAGS);

	/**
	 * For NPCS 1, 2, and 3, different PINs can be used to access the same
	 * NPCS line.
	 * Depending on the application requirements, the default PIN may not be
	 * available.
	 * Hence a different PIN should be selected using the
	 * CONF_BOARD_SPI_NPCS_GPIO and
	 * CONF_BOARD_SPI_NPCS_FLAGS macros.
	 */

#   ifdef CONF_BOARD_SPI0_NPCS0
	//	gpio_configure_pin(SPI0_NPCS0_GPIO, SPI0_NPCS0_FLAGS);
#   endif

#   ifdef CONF_BOARD_SPI0_NPCS1
#       if defined(CONF_BOARD_SPI0_NPCS1_GPIO) && \
		defined(CONF_BOARD_SPI0_NPCS1_FLAGS)
			gpio_configure_pin(CONF_BOARD_SPI0_NPCS1_GPIO,
					CONF_BOARD_SPI0_NPCS1_FLAGS);
#       else
			gpio_configure_pin(SPI0_NPCS1_PA29_GPIO,
					SPI0_NPCS1_PA29_FLAGS);
#       endif
#   endif

#   ifdef CONF_BOARD_SPI0_NPCS2
#       if defined(CONF_BOARD_SPI0_NPCS2_GPIO) && \
		defined(CONF_BOARD_SPI0_NPCS2_FLAGS)
			gpio_configure_pin(CONF_BOARD_SPI0_NPCS2_GPIO,
					CONF_BOARD_SPI0_NPCS2_FLAGS);
#       else
			gpio_configure_pin(SPI0_NPCS2_PA30_GPIO,
					SPI0_NPCS2_PA30_FLAGS);
#       endif
#   endif

#   ifdef CONF_BOARD_SPI0_NPCS3
#       if defined(CONF_BOARD_SPI0_NPCS3_GPIO) && \
		defined(CONF_BOARD_SPI0_NPCS3_FLAGS)
			gpio_configure_pin(CONF_BOARD_SPI0_NPCS3_GPIO,
					CONF_BOARD_SPI0_NPCS3_FLAGS);
#       else
			gpio_configure_pin(SPI0_NPCS3_PA31_GPIO,
					SPI0_NPCS3_PA31_FLAGS);
#       endif
#   endif
#endif // #ifdef CONF_BOARD_SPI0

	/* Configure SPI1 pins */
#ifdef CONF_BOARD_SPI1
	gpio_configure_pin(SPI1_MISO_GPIO, SPI1_MISO_FLAGS);
	gpio_configure_pin(SPI1_MOSI_GPIO, SPI1_MOSI_FLAGS);
	gpio_configure_pin(SPI1_SPCK_GPIO, SPI1_SPCK_FLAGS);
	
	
	

#   ifdef CONF_BOARD_SPI1_NPCS0
		gpio_configure_pin(SPI1_NPCS0_GPIO, SPI1_NPCS0_FLAGS);
#   endif

#   ifdef CONF_BOARD_SPI1_NPCS1
		gpio_configure_pin(SPI1_NPCS1_GPIO, SPI1_NPCS1_FLAGS);
#   endif

#   ifdef CONF_BOARD_SPI1_NPCS2
		gpio_configure_pin(SPI1_NPCS2_GPIO, SPI1_NPCS2_FLAGS);
#   endif

#   ifdef CONF_BOARD_SPI1_NPCS3
		gpio_configure_pin(SPI1_NPCS3_GPIO, SPI1_NPCS3_FLAGS);
#   endif
#endif



#ifdef CONF_BOARD_USART_RXD
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);
	
#endif

#ifdef CONF_BOARD_USART_TXD
	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_CTS
	/* Configure USART CTS pin */
	gpio_configure_pin(PIN_USART0_CTS_IDX, PIN_USART0_CTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART_RTS
	/* Configure USART RTS pin */
	gpio_configure_pin(PIN_USART0_RTS_IDX, PIN_USART0_RTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART_SCK
	/* Configure USART synchronous communication SCK pin */
	gpio_configure_pin(PIN_USART0_SCK_IDX, PIN_USART0_SCK_FLAGS);
#endif

	gpio_configure_pin(FRAM_WP_GPIO, FRAM_WP_FLAGS);
		
			
			
#ifdef CONF_BOARD_CAN0
	/* Configure the CAN0 TX and RX pins. */
	gpio_configure_pin(PIN_CAN0_RX_IDX, PIN_CAN0_RX_FLAGS);
	gpio_configure_pin(PIN_CAN0_TX_IDX, PIN_CAN0_TX_FLAGS);
	/* Configure the transiver0 RS & EN pins. */
	//gpio_configure_pin(PIN_CAN0_TR_RS_IDX, PIN_CAN0_TR_RS_FLAGS);
	//gpio_configure_pin(PIN_CAN0_TR_EN_IDX, PIN_CAN0_TR_EN_FLAGS);
#endif

#ifdef CONF_BOARD_CAN1
	/* Configure the CAN1 TX and RX pin. */
	gpio_configure_pin(PIN_CAN1_RX_IDX, PIN_CAN1_RX_FLAGS);
	gpio_configure_pin(PIN_CAN1_TX_IDX, PIN_CAN1_TX_FLAGS);
	/* Configure the transiver1 RS & EN pins. */
	//gpio_configure_pin(PIN_CAN1_TR_RS_IDX, PIN_CAN1_TR_RS_FLAGS);
//	gpio_configure_pin(PIN_CAN1_TR_EN_IDX, PIN_CAN1_TR_EN_FLAGS);
#endif


#ifdef CONF_BOARD_PCK0
	gpio_configure_pin(PIN_PCK0, PIN_PCK0_FLAGS);
#endif

}
