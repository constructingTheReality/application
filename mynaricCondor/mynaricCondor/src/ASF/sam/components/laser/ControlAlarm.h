/**
* @file			ControlAlarm.h
* @brief    controlAlarm header file.
* @author		juan
* @date			Created on 2021-03-3
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
#ifndef __CONTROLALARM_H
#define __CONTROLALARM_H
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "laserData.h"
/* Define ------------------------------------------------------------------- */
#define ALARM_FOR_BOOSTER_INPUT_HIGH			( 1900 )
#define ALARM_FOR_BOOSTER_INPUT_LOW				( 400 )
#define ALARM_FOR_BOOSTER_OUTPUT_LOW			( 100 )
#define ALARM_FOR_BOOSTER_OUTPUT_HIGH			( 4000 )

#define ALARM_FOR_LNA_OUTPUT_LOW				( 200 )
#define ALARM_FOR_LNA_OUTPUT_HIGH				( 3900 )
	

/*currents alarms*/
#define ALARM_FOR_940_TOO_LOW_WRT_TO_SETPOINT	  ( 450 )		/* mA */
#define ALARM_FOR_940_CURRENT_TOO_HIGH    		  ( 3300 )	/* mA */
#define ALARM_FOR_940_CURRENT_WAY_TOO_HIGH      ( 6600 )	/* mA */
#define MAX_RANGE_FOR_940_OUPUT_CURRENT           ( 6000)  /*mA */
#define MAX_VALUE_FOR_CURRENT_ERROR 						( 110 )


#define SYSTEM_ALARM_TEMPERATURE_IS_WAY_TO_LONG			( 0x00000000000000001 )
#define SYSTEM_ALARM_TEMPERATURE_IS_TO_LOW					( 2 )

#define	DEF_YES	1
#define	DEF_NO	0
enum
{
	eSystemAlarmTemperatureIsWayTooLong = 1,
	eSystemAlarmTemperatureIsTooLong = 2
};




typedef struct
{
	int16_t 											sThresholdForAlarmLowInternal_2_5VoltageMonitor;
	int16_t 											sThresholdForAlarmHighInternal_2_5VoltageMonitor;
	int16_t 											sThresholdForPhotoDiodeOffsetTooHigh;
	int16_t 											sThresholdForPhotoDiodeOffsetTooLow;
}xAlarmsThresholdsForVoltageValues_t;

typedef struct
{
	float 											fThresholdForAlarmLowInputBooster;
	float 											fThresholdForAlarmHighInputBooster;
	float 											fThresholdForAlarmLowOutputBooster;
	float 											fThresholdForAlarmHighOutputBooster;
	float 											fThresholdForAlarmLowOutputLna;
	float 											fThresholdForAlarmHighOutputLna;
}xAlarmsThresholdsForPowerValues_t;

typedef struct
{
	int16_t 											sThresholdForAlarm940TooLowWrtToSetPoint;
	int16_t 											sThresholdForAlarm940TooHigh;
	int16_t 											sThresholdForAlarm940WayTooHigh;
	
	int16_t 											sThresholdForAlarm980TooLowWrtToSetPoint;
	int16_t 											sThresholdForAlarm980TooHigh;
	int16_t 											sThresholdForAlarm980WayTooHigh;
	
	int16_t 											sThresholdForAlarmTecTooHigh;
	int16_t 											sThresholdForAlarmTecWayTooHigh;
	
	int16_t 											sThresholdForFault940MultiModeDiodeCurrentSetpointTooHigh;
	int16_t 											sThresholdForFault980SingleModeDiodeCurrentSetpointTooHigh;
	
	int16_t 											sThresholdForAlarmRs485Sp1NegativeTooHigh;
	int16_t 											sThresholdForAlarmRs485Sp0NegativeTooHigh;
	int16_t 											sThresholdForAlarmFramBankANegativeTooHigh;
	int16_t 											sThresholdForAlarmFramBankBNegativeTooHigh;
	
}xAlarmsThresholdsForCurrentValues_t;




/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* alarms register bit */
/* meaning when bit value = 1 */
typedef struct
{
	uint64_t bBosterOpticalInputIsTooHigh				 						: 1;     /* bit 0 - FAULT*/
	uint64_t bBosterOpticalInputIsTooLow			    						: 1;     /* bit 1 */
	uint64_t bBosterOpticalOutputIsTooHigh    									: 1;     /* bit 2 */
	uint64_t bBosterOpticalOutputIsTooLow				 						: 1;     /* bit 3  - FAULT */
	uint64_t bLnaOpticalInputIsTooLow				 							: 1;     /* bit 4  - FAULT */
	uint64_t bLnaOpticalInputIsTooHigh				 							: 1;     /* bit 5  - FAULT */
	
	
	
} AlarmsRegisterBitAssignment_t;


typedef union
{
	AlarmsRegisterBitAssignment_t AlarmsRegisterBitAssignment;
	uint8_t												AlarmsRegisterBytes[8];
	uint64_t 											AlarmGlobalValue;
	
}xAlarmRegister_t;

/* Global variables --------------------------------------------------------- */
//static AlarmsRegisterBitAssignment_t gAlarmsRegisterBitAssignment ;

/* Exported function prototypes --------------------------------------------- */

/**
* @brief		Alarm control state machine.
*/
//void vControlAlarmInitAlarms(void);
//void vControlAlarmInitAlarms(xAlarmsThresholdsValues_t *pxAlarmsThresholdsValues);

void vControlAlarm( void );

//void vControlAlarmClear(xAlarmRegister_t *pxAlarmRegister);

void vControlAlarmSetCriticalAlarms(  void);//float fRead , xAlarmRegister_t *pxAlarmRegister, xAlarmsThresholdsValues_t *pxAlarmsThresholdsValues);


#endif /* __CONTROLALARM_H */
