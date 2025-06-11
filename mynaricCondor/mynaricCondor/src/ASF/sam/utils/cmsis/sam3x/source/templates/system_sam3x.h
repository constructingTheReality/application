/**
 * \file
 *
 * \brief Provides the low-level initialization functions that called 
 * on chip startup.
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

#ifndef SYSTEM_SAM3X_H_INCLUDED
#define SYSTEM_SAM3X_H_INCLUDED

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

#include <stdint.h>
#include <compiler.h>

extern uint32_t SystemCoreClock;	/* System Clock Frequency (Core Clock) */
typedef enum
{
	hal_status_ok             = 0,
	hal_status_initError      = 1,
	hal_status_badParam       = 2,
	hal_status_notInitialized = 3,
	hal_status_badPeriphID    = 4,
	hal_status_timeout        = 5,
	hal_status_rxError        = 6,
	hal_status_txError        = 7,
	hal_status_bufEmpty       = 8,
	hal_status_bufFull        = 9,
	hal_status_nak            = 10,
	hal_status_arblost        = 11,
	hal_status_busy           = 12,
	hal_status_notImplemented = 13,
	hal_status_alignmentErr   = 14,
	hal_status_periphErr      = 15,
	hal_status_end            = 16  // end of list indicator
} hal_status_t;
/**
 * @brief Setup the microcontroller system.
 * Initialize the System and update the SystemCoreClock variable.
 */
void SystemInit(void);

/**
 * @brief Updates the SystemCoreClock with current core Clock 
 * retrieved from cpu registers.
 */
void SystemCoreClockUpdate(void);

/** 
 * Initialize flash.
 */
void system_init_flash(uint32_t ul_clk);

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* SYSTEM_SAM3X_H_INCLUDED */
