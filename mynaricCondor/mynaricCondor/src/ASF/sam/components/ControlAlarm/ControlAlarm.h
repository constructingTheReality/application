/**
* @file			ControlAlarm.h
* @brief    controlAlarm header file.
* @author		juan
* @date			Created on 2023-08-3
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

#ifndef CONTROLALARM_H_
#define CONTROLALARM_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
#define ALARM_LOW_FOR_1545_OUPUT_POWER							( -20 )    /* mW */
#define ALARM_HIGH_FOR_1545_OUPUT_POWER							( 20 )  /* mW */
#define FAULT_HIGH_FOR_1545_OUPUT_POWER							( 50 )  /* mW */
#define MAX_RANGE_FOR_1545_OUPUT_POWER							( 2000 )  /* mW */


#define ALARM_LOW_FOR_980_OUPUT_POWER							  ( -20 )		/* mW */
#define ALARM_HIGH_FOR_980_OUPUT_POWER							( 20 )  /* mW */
#define FAULT_HIGH_FOR_980_OUPUT_POWER							( 50 )  /* mW */
#define MAX_RANGE_FOR_980_OUPUT_POWER							( 2000 )  /* mW */



#define ALARM_FOR_QFB_EXTRA_LOW_TEMP					  ( -50 )		/* degrees C */
#define ALARM_FOR_QFB_LOW_TEMP								  ( -20 )		/* degrees C */
#define ALARM_FOR_QFB_HIGH_TEMP								  ( 60 )		/* degrees C */
#define ALARM_FOR_QFB_EXTRA_HIGH_TEMP					  ( 70 )		/* degrees C */

#define ALARM_FOR_980_WAY_TOO_LOW_TEMP				  ( -25 )		/* degrees C */
#define ALARM_FOR_980_TOO_LOW_TEMP						  ( -10 )		/* degrees C */
#define ALARM_FOR_980_TOO_HIGH_TEMP						  ( 50 )		/* degrees C */
#define ALARM_FOR_980_WAY_TOO_HIGH_TEMP				  ( 70 )		/* degrees C */

#define ALARM_FOR_940_WAY_TOO_LOW_TEMP				  ( -25 )		/* degrees C */
#define ALARM_FOR_940_TOO_LOW_TEMP						  ( -10 )		/* degrees C */
#define ALARM_FOR_940_TOO_HIGH_TEMP						  ( 50 )		/* degrees C */
#define ALARM_FOR_940_WAY_TOO_HIGH_TEMP				  ( 70 )		/* degrees C */

#define ALARM_INTERNAL_WAY_TOO_HIGH_TEMP     ( 80 )`
#define ALARM_INTERNAL_WAY_LOW_TEMP_MCU  			  ( -40 )		/* degrees C */
#define ALARM_INTERNAL_LOW_TEMP_MCU						  ( -20 )		/* degrees C */
#define ALARM_INTERNAL_HIGH_TEMP_MCU					  ( 60 )		/* degrees C */


/*currents alarms*/
#define ALARM_FOR_940_TOO_LOW_WRT_TO_SETPOINT	  ( 450 )		/* mA */
#define ALARM_FOR_940_CURRENT_TOO_HIGH    		  ( 3300 )	/* mA */
#define ALARM_FOR_940_CURRENT_WAY_TOO_HIGH      ( 6600 )	/* mA */
#define MAX_RANGE_FOR_940_OUPUT_CURRENT           ( 6000)  /*mA */
#define MAX_VALUE_FOR_CURRENT_ERROR 						( 110 )



#define ALARM_FOR_980_TOO_LOW_WRT_TO_SETPOINT	  ( 50 )		/* mA */
#define ALARM_FOR_980_CURRENT_TOO_HIGH    		  ( 550 )	/* mA */
#define ALARM_FOR_980_CURRENT_WAY_TOO_HIGH      ( 1100 )	/* mA */
#define MAX_RANGE_FOR_980_OUPUT_CURRENT           (1000)  /*mA */

#define ALARM_FOR_TEC_CURRENT_TOO_HIGH    		  ( 250 )	/* mA */
#define ALARM_FOR_TEC_CURRENT_WAY_TOO_HIGH      ( 300 )	/* mA  TBD  */

#define ALARM_FOR_940_MUTLTIMODE_CURRENT_SETPOINT	  ( 4000 )		/* mA */
#define FAULT_FOR_940_MUTLTIMODE_CURRENT_SETPOINT	  ( 6000 )		/* mA */
#define ALARM_FOR_980_SINGLEMODE_CURRENT_SETPOINT	  ( 1000 )		/* mA */

#define ALARM_FOR_RS485_SP1_CURRENT_TOO_HIGH    		( 3300 )	/* mA */
#define ALARM_FOR_RS485_SP0_CURRENT_TOO_HIGH    		( 3300 )	/* mA */

#define ALARM_FOR_FRAM_BANK_A_NEGATIVE_CURRENT_TOO_HIGH    		( 3300 )	/* mA */
#define ALARM_FOR_FRAM_BANK_B_NEGATIVE_CURRENT_TOO_HIGH    		( 3300 )	/* mA */
#define ALARM_FOR_FRAM_COMMON_NEGATIVE_CURRENT_TOO_HIGH    		( 3300 )	/* mA */


/* voltage alarms */
#define ALARM_2_5_V_LOW_REFERENCE_VOLTAGE_MONITOR	  ( 2000 )		/* mV 2450*/
#define ALARM_2_5_V_HIGH_REFERENCE_VOLTAGE_MONITOR	  ( 2550 )		/* mV */
#define ALARM_FOR_PHOTODIODE_OFFSET_TOO_HIGH    		( 900 )	/* mV */
#define ALARM_FOR_PHOTODIODE_OFFSET_TOO_LOW    		( 100 )	/* mV */

#define SYSTEM_ALARM_TEMPERATURE_IS_WAY_TO_LONG			( 0x00000000000000001 )
#define SYSTEM_ALARM_TEMPERATURE_IS_TO_LOW					( 2 )

#define	DEF_YES	1
#define	DEF_NO	0


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief		Alarm control state machine.
*/
void vUpdateStatusAndAlarm( void );

#endif /* CONTROLALARM_H_ */