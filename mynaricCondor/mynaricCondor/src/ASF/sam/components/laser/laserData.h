/**
* @file		    LaserData.h
* @brief        LaserData header file.
* @author		juan
* @date			Created on 2023-1-12
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

#ifndef LASERDATA_H_
#define LASERDATA_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "ControlAlarm.h"
#include "canDictionary.h"
#include "currentSensors.h"
//#include "CurrentSensing.h"
#include "CurrentControl.h"
#include "temperature.h"
#include "PowerSensors.h"
//#include "BSPGpio.h"
#include "nvMemory.h"
#include "mpbLosDetector.h"
#include "mpbPowerIn2Channels.h"
//#include "lnaStateMachine.h"
//#include "mainStateMachine.h"
#include "projectDef.h"
/* Define ------------------------------------------------------------------- */
#define	NUMBER_OF_LEDS_BY_BOARD  (  2  )

#define	MANUFACTURER_NUMBER  (  3  )
#define	SERIAL_NUMBER         ( 1 )

#define MEMORY_SPACE ( 0x6000 )
#define  MAX_NUM_OF_TRYS					( 2 )
//#define  MEMORY_INIT_ADDRESS ( 3 )
#define  MEMORY_INIT_COMMON_ADDRESS			( 20 )
#define  MEMORY_INIT_LNA_ADDRESS			( 500 )
#define  MEMORY_INIT_BOOSTER_ADDRESS		( 2500 )

#define  MEMORY_INIT_COMMON_ADDRESS2		( 4000 )
#define  MEMORY_INIT_LNA_ADDRESS2			( 4500 )
#define  MEMORY_INIT_BOOSTER_ADDRESS2		( 6500 )

#define  MEMORY_INIT_COMMON_ADDRESS3		( 8500 )
#define  MEMORY_INIT_LNA_ADDRESS3			( 10000 )
#define  MEMORY_INIT_BOOSTER_ADDRESS3		( 12500 )


//#define DEMO_VERSION						
//#define DEMO_MASOUR_VERSION
#define  SIZE_OF_CRC16						( 2 )

#define DEF_VERSION_FIRMWARE_MAJOR			( 1 )	
#define DEF_VERSION_FIRMWARE_MINOR			( 0 )
#define DEF_VERSION_FIRMWARE_PATCH			( 1 )


#define ALARM_FOR_LNA_SM_EXTRA_LOW_TEMP			( -50 )		/* degrees C */
#define ALARM_FOR_LNA_SM_LOW_TEMP				( -20 )		/* degrees C */
#define ALARM_FOR_LNA_SM_HIGH_TEMP				( 60 )		/* degrees C */
#define ALARM_FOR_LNA_SM_EXTRA_HIGH_TEMP		( 70 )		/* degrees C */

#define ALARM_FOR_HPA_SM_WAY_TOO_LOW_TEMP	    ( -50 )		/* degrees C */
#define ALARM_FOR_HPA_SM_TOO_LOW_TEMP			( -20 )		/* degrees C */
#define ALARM_FOR_HPA_SM_TOO_HIGH_TEMP			( 60 )		/* degrees C */
#define ALARM_FOR_HPA_SM_WAY_TOO_HIGH_TEMP		( 70 )		/* degrees C */

#define ALARM_FOR_HPA_MM_1_WAY_TOO_LOW_TEMP	    ( -25 )		/* degrees C */
#define ALARM_FOR_HPA_MM_1_TOO_LOW_TEMP			( -10 )		/* degrees C */
#define ALARM_FOR_HPA_MM_1_TOO_HIGH_TEMP		( 50 )		/* degrees C */
#define ALARM_FOR_HPA_MM_1_WAY_TOO_HIGH_TEMP	( 70 )		/* degrees C */

#define ALARM_FOR_HPA_MM_2_WAY_TOO_LOW_TEMP	    ( -25 )		/* degrees C */
#define ALARM_FOR_HPA_MM_2_TOO_LOW_TEMP			( -10 )		/* degrees C */
#define ALARM_FOR_HPA_MM_2_TOO_HIGH_TEMP		( 50 )		/* degrees C */
#define ALARM_FOR_HPA_MM_2_WAY_TOO_HIGH_TEMP	( 70 )		/* degrees C */

#define ALARM_FOR_HPA_MM_3_WAY_TOO_LOW_TEMP	    ( -25 )		/* degrees C */
#define ALARM_FOR_HPA_MM_3_TOO_LOW_TEMP			( -10 )		/* degrees C */
#define ALARM_FOR_HPA_MM_3_TOO_HIGH_TEMP		( 50 )		/* degrees C */
#define ALARM_FOR_HPA_MM_3_WAY_TOO_HIGH_TEMP	( 70 )		/* degrees C */


#define ALARM_FOR_HPA_MM_4_WAY_TOO_LOW_TEMP	    ( -25 )		/* degrees C */
#define ALARM_FOR_HPA_MM_4_TOO_LOW_TEMP			( -10 )		/* degrees C */
#define ALARM_FOR_HPA_MM_4_TOO_HIGH_TEMP		( 50 )		/* degrees C */
#define ALARM_FOR_HPA_MM_4_WAY_TOO_HIGH_TEMP	( 70 )		/* degrees C */

#define ALARM_INTERNAL_WAY_TOO_HIGH_TEMP		( 80 )
#define ALARM_INTERNAL_WAY_LOW_TEMP_MCU  		( -40 )		/* degrees C */
#define ALARM_INTERNAL_LOW_TEMP_MCU				( -20 )		/* degrees C */
#define ALARM_INTERNAL_HIGH_TEMP_MCU			( 60 )		/* degrees C */


/* common control indexes */
#define INDEX_FOR_CALIB_PD_REF1_CH6_SLOPE								( 0 )
#define INDEX_FOR_CALIB_PD_REF1_CH6_INTERCEPT							( 1 )

#define INDEX_FOR_CALIB_CASE_THERMISTOR1_CH20_SLOPE						( 2 )
#define INDEX_FOR_CALIB_CASE_THERMISTOR1_CH20_INTERCEPT					( 3 )

#define INDEX_FOR_CALIB_PD_REF2_CH23_SLOPE								( 4 )
#define INDEX_FOR_CALIB_PD_REF2_CH23_INTERCEPT							( 5 )



/* lna indexes */

#define INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_SLOPE				( 6 )
#define INDEX_FOR_CALIB_LNA_1536_INPUT_MONITOR_CH0_INTERCEPT			( 7 )

#define INDEX_FOR_CALIB_LNA_1553_INPUT_MONITOR_CH0_SLOPE				( 8 )
#define INDEX_FOR_CALIB_LNA_1553_INPUT_MONITOR_CH0_INTERCEPT			( 9 )

#define INDEX_FOR_CALIB_LNA_1536_OUTPUT_MONITOR1_CH1_SLOPE					( 10 )
#define INDEX_FOR_CALIB_LNA_1536_OUTPUT_MONITOR1_CH1_INTERCEPT				( 11 )

#define INDEX_FOR_CALIB_LNA_1553_OUTPUT_MONITOR2_CH2_SLOPE					( 12 )
#define INDEX_FOR_CALIB_LNA_1553_OUTPUT_MONITOR2_CH2_INTERCEPT				( 13 )

#define INDEX_FOR_CALIB_LNA_SM_BACKFACET_CH7_SLOPE						( 14 )
#define INDEX_FOR_CALIB_LNA_SM_BACKFACET_CH7_INTERCEPT					( 15 )

/* ADC 2 */

#define INDEX_FOR_CALIB_LNA_SM_CURRENT_MONITOR_CH8_SLOPE				( 16 )
#define INDEX_FOR_CALIB_LNA_SM_CURRENT_MONITOR_CH8_INTERCEPT            ( 17 )

#define INDEX_FOR_CALIB_LNA_SM_THERMISTOR_CH12_SLOPE					( 18 )
#define INDEX_FOR_CALIB_LNA_SM_THERMISTOR_CH12_INTERCEPT				( 19 )

/* output lma index */
#define INDEX_FOR_CALIB_LNA_1536_PWM_STP_SLOPE							( 20 )
#define INDEX_FOR_CALIB_LNA_1536_PWM_STP_INTERCEPT						( 21 )

#define INDEX_FOR_CALIB_LNA_1553_PWM_STP_SLOPE							( 22 )							
#define INDEX_FOR_CALIB_LNA_1553_PWM_STP_INTERCEPT						( 23 )							

#define INDEX_FOR_CALIB_LNA_1536_MA_STP_SLOPE							( 24 )
#define INDEX_FOR_CALIB_LNA_1536_MA_STP_INTERCEPT						( 25 )

#define INDEX_FOR_CALIB_LNA_1553_MA_STP_SLOPE							( 26 )
#define INDEX_FOR_CALIB_LNA_1553_MA_STP_INTERCEPT						( 27 )

#define PROPORCIONAL_FACTOR_LNA											( 28 )
#define DERIVATIVE_FACTOR_LNA											( 29 )
#define INTEGRAL_FACTOR_LNA												( 30 )

#define LNA_MIN_CURRENT													  ( 31 )
#define LNA_MAX_CURRENT												      ( 32 )

#define LNA_MAX_POWER												      ( 33 )

/* --------------------------------------------booster indexes */

#define INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_SLOPE						( 34 )
#define INDEX_FOR_CALIB_HPA_1536_INPUT_MONITOR_CH3_INTERCEPT					( 35 )

#define INDEX_FOR_CALIB_HPA_1553_INPUT_MONITOR_CH3_SLOPE						( 36 )
#define INDEX_FOR_CALIB_HPA_1553_INPUT_MONITOR_CH3_INTERCEPT					( 37 )

#define INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1536_CH4_SLOPE				( 38 )
#define INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1536_CH4_INTERCEPT			( 39 )

#define INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1536_CH5_SLOPE				( 40 )
#define INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1536_CH5_INTERCEPT			( 41 )

#define INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1553_CH4_SLOPE				( 42 )
#define INDEX_FOR_CALIB_HPA_OUTPUT_LOW_MONITOR_1553_CH4_INTERCEPT			( 43 )

#define INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1553_CH5_SLOPE				( 44 )
#define INDEX_FOR_CALIB_HPA_OUTPUT_HIGH_MONITOR_1553_CH5_INTERCEPT			( 45 )



/* ADC 2 */
#define INDEX_FOR_CALIB_HPA_SM_CURRENT_MONITOR_CH9_SLOPE				( 46 )
#define INDEX_FOR_CALIB_HPA_SM_CURRENT_MONITOR_CH9_INTERCEPT			( 47 )

#define INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR1_CH10_SLOPE				( 48 )
#define INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR1_CH10_INTERCEPT			( 49 )

#define INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR2_CH11_SLOPE				( 50 )
#define INDEX_FOR_CALIB_HPA_MM_CURRENT_MONITOR2_CH11_INTERCEPT			( 51 )


#define INDEX_FOR_CALIB_HPA_SM_THERMISTOR_CH13_SLOPE					( 52 )
#define INDEX_FOR_CALIB_HPA_SM_THERMISTOR_CH13_INTERCEPT				( 53 )

 /*ADC 3*/
 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR1_CH16_SLOPE					( 54 )
 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR1_CH16_INTERCEPT				( 55 )

 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR2_CH17_SLOPE					( 56 )
 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR2_CH17_INTERCEPT				( 57 )

 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR3_CH18_SLOPE					( 58 )
 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR3_CH18_INTERCEPT				( 59 )

 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR4_CH19_SLOPE					( 60 )
 #define INDEX_FOR_CALIB_HPA_MM_THERMISTOR4_CH19_INTERCEPT				( 61 )

 #define INDEX_FOR_CALIB_HPA_SM_BACKFACET_CH22_SLOPE					( 62 )
 #define INDEX_FOR_CALIB_HPA_SM_BACKFACET_CH22_INTERCEPT				( 63 )
 
 
/*--------- outputs ------------------*/

//hpa sm

#define INDEX_FOR_CALIB_HPA_SM_PWM_STP_1536_SLOPE_						( 64 )
#define INDEX_FOR_CALIB_HPA_SM_PWM_STP_1536_INTERCEPT_					( 65 )

#define INDEX_FOR_CALIB_HPA_SM_PWM_STP_1553_SLOPE_						( 66 )
#define INDEX_FOR_CALIB_HPA_SM_PWM_STP_1553_INTERCEPT_					( 67 )

#define INDEX_FOR_CALIB_HPA_SM_MA_STP_1536_SLOPE_						( 68 )
#define INDEX_FOR_CALIB_HPA_SM_MA_STP_1536_INTERCEPT_					( 69 )

#define INDEX_FOR_CALIB_HPA_SM_MA_STP_1553_SLOPE_						( 70 )
#define INDEX_FOR_CALIB_HPA_SM_MA_STP_1553_INTERCEPT_					( 71 )



// MM1
#define INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1536_SLOPE_						( 72 )
#define INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1536_INTERCEPT_					( 73 )

#define INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1553_SLOPE_						( 74 )
#define INDEX_FOR_CALIB_HPA_MM_PWM_STP1_1553_INTERCEPT_					( 75 )

#define INDEX_FOR_CALIB_HPA_MM_MA_STP1_1536_SLOPE_						( 76 )
#define INDEX_FOR_CALIB_HPA_MM_MA_STP1_1536_INTERCEPT_					( 77 )

#define INDEX_FOR_CALIB_HPA_MM_MA_STP1_1553_SLOPE_						( 78 )
#define INDEX_FOR_CALIB_HPA_MM_MA_STP1_1553_INTERCEPT_					( 79 )

//MM2

#define INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1536_SLOPE_						( 80 )
#define INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1536_INTERCEPT_					( 81 )

#define INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1553_SLOPE_						( 82 )
#define INDEX_FOR_CALIB_HPA_MM_PWM_STP2_1553_INTERCEPT_					( 83 )


#define INDEX_FOR_CALIB_HPA_MM_MA_STP2_1536_SLOPE_						( 84 )
#define INDEX_FOR_CALIB_HPA_MM_MA_STP2_1536_INTERCEPT_					( 85 )

#define INDEX_FOR_CALIB_HPA_MM_MA_STP2_1553_SLOPE_						( 86 )
#define INDEX_FOR_CALIB_HPA_MM_MA_STP2_1553_INTERCEPT_					( 87 )

/* pid*/


#define PROPORCIONAL_FACTOR_BOOSTER_SM										( 88 )   
#define DERIVATIVE_FACTOR_BOOSTER_SM										( 89 )
#define INTEGRAL_FACTOR_BOOSTER_SM											( 90 )

#define PROPORCIONAL_FACTOR_BOOSTER_MM1										( 91 )   
#define DERIVATIVE_FACTOR_BOOSTER_MM1										( 92 )
#define INTEGRAL_FACTOR_BOOSTER_MM1											( 93 )


#define PROPORCIONAL_FACTOR_BOOSTER_MM2										( 94 )   
#define DERIVATIVE_FACTOR_BOOSTER_MM2										( 95 )
#define INTEGRAL_FACTOR_BOOSTER_MM2											( 96 )



#define HPA_LOS_CLEAR													( 97 )
#define HPA_LOS_SET_														( 98 )

#define HPA_MIN_POWER_FOR_SECOND_STEP										( 99 )
#define HPA_MIN_BACKFACET										( 100 )
#define HPA_MAX_BACKFACET										( 101 )


#define HPA_MAX_CURRENT_SM1										( 102 )
#define HPA_NOMINAL_CURRENT_POURCENTAGE_SM1						( 103 )

#define HPA_MAX_CURRENT_MM1										( 104 )
#define HPA_MAX_CURRENT_MM2										( 105 )

#define HPA_LH_LEVEL_MAX_IN_RAW								    ( 106 )						
#define HPA_HH_LEVEL_MIN_IN_RAW								    ( 107 )						

#define PROPORCIONAL_FACTOR_BOOSTER_MM1_MM2										( 108 )
#define DERIVATIVE_FACTOR_BOOSTER_MM1_MM2										( 109 )
#define INTEGRAL_FACTOR_BOOSTER_MM1_MM2											( 110 )

#define HPA_MAX_CURRENT_STAGE_MM1										( 111 )
#define HPA_MAX_CURRENT_STAGE_MM2										( 112 )


#define RESET_ALARMS													( 122 )

#define PUMP_HIGH_TEMP_LIMIT											( 123 )
#define PUMP_VERY_HIGH_TEMP_LIMIT										( 124 )
#define PUMP_LOW_TEMP_LIMIT												( 125 )
#define PUMP_VERY_LOW_TEMP_LIMIT										( 126 )

#define CASE_HIGH_TEMP_LIMIT											( 127 )
#define CASE_LOW_TEMP_LIMIT												( 128 )


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
enum
{
	e940MultiModeLaserDiode940 = 0,
	e980SingleModeLaserDiode980 = 1,
	eNumberTotalOfLaserBeams = 2
};
/* Exported struct ---------------------------------------------------------- */


typedef struct
{
	eBool_t  bPort;
	uint32_t ulMemoryId;
	uint32_t ulResetTime;
	uint32_t ulRunningTime;
	eBool_t  bTestMode;
}xLaserStatus_t;

typedef enum
{
	eAlarm_none = 0,
	eAlarm_InternalElectronics = 1,
	eAlarm_OverTemperature = 2,
	eAlarm_BoosterInputHigh = 3,
	eAlarm_BoosterOutputHigh = 4,
	eAlarm_LnaOutputHigh = 5,
	eAlarm_LnaCurrentLow = 6,
	eAlarm_LnaCurrentHigh = 7
	
}eAlarmType_t;


typedef enum
{
	eAlarm = 0,
	eTest = 1,
	eIdle = 2,
	eAcc = 3,
	eApc = 4,
	
}eOperationMode_t;

typedef enum
{
	eLnaNone = 0,
	eLnaSingleMode = 1,
	eHpaSingleMode = 2,
	eHpaMultiMode1 = 3,
	eHpaMultiMode2 = 4,
	eHpaMultiMode1and2 = 5
}eBeaconIdUsedActually_t;


/*
typedef struct
{
	float			f28V_PwrCurrentMonitor_Ch1;		/// ch 0 internal ADC 
	float			f28V_PwrCurrentMonitor_Ch2;		/ ch 1 internal ADC 
	float			f28V_PwrVoltageMonitor_Ch1;		/ ch 2 internal ADC 
	float			f28V_PwrVoltageMonitor_Ch2;		/ ch 3 internal ADC 
	float			f7V_PwrVoltageMonitor_Ch1;		/ ch 4 internal ADC 
	float			f7V_PwrVoltageMonitor_Ch2;		/ ch 5 internal ADC 
	float			f3_3V_PwrVoltageMonitor;		/ ch 6 internal ADC 
	float			f3V_ld_PwrVoltageMonitor;		/ ch 7 internal ADC 
	float			fAdcPwrCurrentMonitor;			/ ch 8 internal ADC 
	float			fCanPwrCurrentMonitor1;			/ ch 9 internal ADC 
	float			fCanPwrCurrentMonitor2;			 ch 10 internal ADC
	float			fLnaOutm2;						 ch 11 internal ADC
	float			fPd_Ref;						 ch 12 internal ADC 
	float			fLnaOutm1;						// ch 13 internal ADC 
	
}xInternalAnalogInputsCpu_t;*/

typedef struct
{
	//float fExternalThermistorCase_Raw;
	float fExternalThermistorLnaSmLd;
	//float fExternalThermistorLnaSmLd_Raw;
	float fExternalThermistorHpaSmLd;
	//float fExternalThermistorHpaSmLd_Raw;
	float fExternalThermistorHpaMmLd1;
	//float fExternalThermistorHpaMmLd1_Raw;
	float fExternalThermistorHpaMmLd2;
	//float fExternalThermistorHpaMmLd2_Raw;
	float fExternalThermistorHpaMmLd3;
	//float fExternalThermistorHpaMmLd3_Raw;
	float fExternalThermistorHpaMmLd4;	
	//float fExternalThermistorHpaMmLd4_Raw;	
}xExternalAnalogThermistorsInputs_t;


typedef struct
{
	float fIntercept;
	float fSlope;
}xInputScalingChannel_t;

typedef struct
{
	float fIntercept;
	float fSlope;
}xOutputScalingChannel_t;

typedef struct
{
	float fLnaApc;
	
}xFinalSetpoints_t;

/*typedef struct
{
	// currents 
	xInputScalingChannel_t  xExLnaSingleModeldCurrentMonitor; 
	xInputScalingChannel_t  xExHpaSingleModeld_CurrentMonitor; 
	
	xInputScalingChannel_t  xExHpaMultiModeld_CurrentMonitor1; 
	xInputScalingChannel_t  xExHpaMultiModeld_CurrentMonitor2;
	//powers
	
	xInputScalingChannel_t  xExternalLnaInputPower;
	xInputScalingChannel_t  xExternalLnaOutputPower1;
	xInputScalingChannel_t  xExternalLnaOutputPower2;
	xInputScalingChannel_t  xExternalHpaInputPower;
	xInputScalingChannel_t  xExternalHpaOutputPower_lm;
	xInputScalingChannel_t  xExternalHpaOutputPower_hm;
	xInputScalingChannel_t  xExternalPdReference1;
	
	xInputScalingChannel_t  xExternalLnaSm_ld_Bfm;
	xInputScalingChannel_t  xExternalHpaSm_ld_Bfm;
	
	xInputScalingChannel_t  xExternalPdReference;
	
	//Thermistors
	xInputScalingChannel_t  xExternalLnaSmld_Thermistor;
	xInputScalingChannel_t  xExternalHpaSmld_Thermistor;
	
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor1;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor2;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor3;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor4;
	
	xInputScalingChannel_t  xExternalCase_Thermistor1;
	
	//spare
	xInputScalingChannel_t  xExternalspare1;
	xInputScalingChannel_t  xExternalspare2;
	xInputScalingChannel_t  xExternalspare3;
	 
}xInputScalingExternalAdc_t;*/






typedef struct
{
	xInputScalingChannel_t  xExternalPdReference1;
	xInputScalingChannel_t  xExternalPdReference;
	xInputScalingChannel_t  xExternalCase_Thermistor1;
	/*spare*/
	xInputScalingChannel_t  xExternalspare1;
	xInputScalingChannel_t  xExternalspare2;
	xInputScalingChannel_t  xExternalspare3;	
}xInputScalingCommonControlExternalAdc_t;




typedef struct
{
	/* currents */
	xInputScalingChannel_t  xExLnaSingleModeldCurrentMonitor;
	/*powers*/
	xInputScalingChannel_t  xExternalLnaInputPower_1536;
	xInputScalingChannel_t  xExternalLnaInputPower_1553;
	xInputScalingChannel_t  xExternalLnaOutputPower1_1536;
	
	xInputScalingChannel_t  xInternalLnaOutputPower1;
	xInputScalingChannel_t  xInternalLnaOutputPower2;
	xInputScalingChannel_t  xInternalPdReference;
	
	//xInputScalingChannel_t  xExternalLnaOutputPower2_1536;
	//xInputScalingChannel_t  xExternalLnaOutputPower1_1553;
	
	xInputScalingChannel_t  xExternalLnaOutputPower2_1553;
	xInputScalingChannel_t  xExternalLnaSm_ld_Bfm;
	/*Thermistors*/
	xInputScalingChannel_t  xExternalLnaSmld_Thermistor;
}xInputScalingLnaAdc_t;

typedef struct
{
	/* currents */
	xInputScalingChannel_t  xExHpaSingleModeld_CurrentMonitor;
	xInputScalingChannel_t  xExHpaMultiModeld_CurrentMonitor1;
	xInputScalingChannel_t  xExHpaMultiModeld_CurrentMonitor2;
	/*powers*/
	xInputScalingChannel_t  xExternalHpaInputPower_1536;
	xInputScalingChannel_t  xExternalHpaInputPower_1553;
	xInputScalingChannel_t  xExternalHpaOutputPower_1536_lm;
	xInputScalingChannel_t  xExternalHpaOutputPower_1536_hm;
	xInputScalingChannel_t  xExternalHpaOutputPower_1553_lm;
	xInputScalingChannel_t  xExternalHpaOutputPower_1553_hm;
	xInputScalingChannel_t  xExternalHpaSm_ld_Bfm;
	/*Thermistors*/
	xInputScalingChannel_t  xExternalHpaSmld_Thermistor;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor1;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor2;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor3;
	xInputScalingChannel_t  xExternalHpaMmld_Thermistor4;
	
	
}xInputScalingBoosterExternalAdc_t;

typedef struct
{
	xOutputScalingChannel_t xOutputLnaLaserDiodeControlCurrentPwm_1553;
	xOutputScalingChannel_t xOutputLnaLaserDiodeControlCurrentPwm_1536;
	xOutputScalingChannel_t xOutputLnaLaserDiodeControlCurrentmA_1553;
	xOutputScalingChannel_t xOutputLnaLaserDiodeControlCurrentmA_1536;

}xOutputScalingLnaDac_t;

typedef struct
{
	xOutputScalingChannel_t xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1553;
	xOutputScalingChannel_t xOutputHpaSmStp1LaserDiodeControlCurrentPwm_1536;
	
	xOutputScalingChannel_t xOutputHpaSmStp1LaserDiodeControlCurrentmA_1553;
	xOutputScalingChannel_t xOutputHpaSmStp1LaserDiodeControlCurrentmA_1536;
	
	
	
	//mm 1
//	xOutputScalingChannel_t xOutputHpaSmStp2LaserDiodeControlCurrent;
	xOutputScalingChannel_t xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1553;
	xOutputScalingChannel_t xOutputHpaMmStp1LaserDiodeControlCurrentPwm_1536;
	
	xOutputScalingChannel_t xOutputHpaMmStp1LaserDiodeControlCurrentmA_1553;
	xOutputScalingChannel_t xOutputHpaMmStp1LaserDiodeControlCurrentmA_1536;
	
	
	//mm2
	xOutputScalingChannel_t xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1553;
	xOutputScalingChannel_t xOutputHpaMmStp2LaserDiodeControlCurrentPwm_1536;
	
	xOutputScalingChannel_t xOutputHpaMmStp2LaserDiodeControlCurrentmA_1553;
	xOutputScalingChannel_t xOutputHpaMmStp2LaserDiodeControlCurrentmA_1536;
	
	xOutputScalingChannel_t xOutputHpaHclk1;
	xOutputScalingChannel_t xOutputHpaHclk2;
}xOutputScalingBoosterDac_t;


typedef struct
{
	float				fAnalogControlLd21; 	
	uint8_t				ucPwmDutyControlLd21; 	
	float				fLnaOpticalOutputPower;
	float				fLaserPump4CurrentOfLna;
	
	
}xAnalogOutputsLna_t;

typedef struct
{
	float				fLnaSetpointAcc;
	float				fLnaSetpointApc;
	float				fMinLevelLna;
	float				fMaxLevelLna;
	float				fGainOfAmplificator;
	xLaserStatus_t		xLaserStatusLna;
	eOperationMode_t	eOperationModeLna;
	
	
}xStatusLna_t;



typedef enum
{
	eItuChannel30 = 1,
	eItuChannel50 = 2
	
}eBoostInputChannels_t;





typedef struct
{
	int16_t 											sMaxSetpointCurrent940;
	int16_t 											sMaxSetpointCurrent980;
	uint16_t 										sMaxSetpointPower940;
	uint16_t 											sMaxSetpointPower980;
}xMaxSetpointsAllowed_t;


typedef struct
{
	uint16_t 										uMinSetpointPower940;
	uint16_t 										uMinSetpointPower980;
}xMinSetpointsAllowed_t;






typedef enum
{
	eLaserStateInit = 0,
	eLaserStateWise,
	eLaserStateBrake,
	eLaserStateFULL,
}eLaserState_t;

typedef enum
{
	eApcControlStateInit = 0,
	eApcControlStateIdle,
	eApcControlStateNormal,
	eApcControlStateAlarm,
	eApcControlStateConfiguration,
}eApcControlState_t;



typedef struct
{
	float fPGain;
	float fIGain;
	float fDGain;
}xPidValues_t;
/*
typedef struct
{
	float fLosClear;
	float fLosSet;
	
}xLosValues_t;*/

typedef struct
{
	float fCurrentMinimum;
	float fCurrentMaximum;
	float fPowerMaximum;
	
}xElectricLimits_t;


typedef struct
{
	eBool_t bDiode980InFault;
	eBool_t bDiode1545InFault;
	eBool_t bSomeInFault;
	
}xFaultsPresents_t;

typedef struct
{
	uint32_t ulSpiAdcErrors;
	uint32_t ulSpiFramErrors;
	uint32_t ulCanErrors;
	
	
}xHardwareErrors_t;



typedef struct
{
uint16_t  usAdcExLna_Inm_raw ;
uint16_t usAdcExLna_OutM1_raw; 
uint16_t usAdcExLna_OutM2_raw; 
uint16_t usAdcExHpa_Inm_raw; 
uint16_t usAdcExHpa_OutL_raw; 
uint16_t usAdcExHpa_OutHm_raw; 
uint16_t usAdcExPd_Ref1_raw; 
uint16_t usAdcExLnaSmld_Bfm_raw; 
uint16_t usAdcExLnaSmldCurrentMonitor_raw; 
uint16_t usAdcExHpaSmld_CurrentMonitor_raw; 
uint16_t usAdcExHpaMmld_CurrentMonitor1_raw; 
uint16_t usAdcExHpaMmld_CurrentMonitor2_raw; 
uint16_t usAdcExLnaSmld_Thermistor_raw;
uint16_t usAdcExHpaSmld_Thermistor_raw;
uint16_t usAdcExHpaMMld_Thermistor1_raw;
uint16_t usAdcExHpaMMld_Thermistor2_raw;
uint16_t usAdcExHpaMMld_Thermistor3_raw;
uint16_t usAdcExHpaMMld_Thermistor4_raw;
uint16_t usAdcExCaseThermistor1_raw;
uint16_t usAdcExHpaSmld_Bfm_raw; 
uint16_t usAdcExPd_Ref2_raw;
uint16_t usAdcIntPd_Ref_raw;


}xExternalAdcChannlesRaw_t;

typedef struct
{
	float fExternalLnaOpticalInputtPower;
	float fInternalLnaOpticalOutputMonitor1;
	float fInternalLnaOpticalOutputMonitor2;
	
	float fInternalHpaOpticalInputMonitor;
	float fExternalHpaOpticalInputMonitor;
	
	float fExternalHpaOpticalOutputMonitor_Lm;
	float fExternalHpaOpticalOutputMonitor_Hm;
	
	
	float fInternalHpaOpticalOutputMonitor;
	
	float fExternalLnaOpticalOutputMonitor1;
	float fExternalLnaOpticalOutputMonitor2;
	
}xPowersInMiliWats_t;

typedef struct
{
	float fLnaSetpointInApcIndbm;
	float fhpa1SetpointInApcIndbm;
	float fhpa2SetpointInApcIndbm;
	float fhpa3SetpointInApcIndbm;
	
	
}xPowersIndBM_t;

typedef struct
{
	float fHpaBackFacetMin;
	float fHpaBackFacetMax;
	float fHpaMinOutPowerForNextSteps;	
}xHpaPowersConfig_t;

typedef struct
{
	float						fLaserPump1BoosterControlCurrent;
	float						fLaserPump2BoosterControlCurrent;
	float						fLaserPump3BoosterControlCurrent;
	float						fLaserPump4LnaControlCurrent;  	
	
}xCurrentControlValues_t;

typedef struct
{
	uint16_t										usMaxHpaCurrentSM_mA;
	uint16_t										usNominalCurrentPourcentage_sM;
	uint16_t										usMaxHpaCurrentMM1_mA;
	uint16_t										usMaxHpaCurrentMM2_mA;
	uint16_t										usMaxHpaCurrentStageMM1_mA;
	uint16_t										usMaxHpaCurrentStageMM2_mA;
	uint16_t										usMax_Lh_level_raw;
	uint16_t										usMin_Hh_level_raw;
}xHpaLimitsConfig_t;

typedef struct
{
	float			fExtern_InputLnaPd_Ref1; //chaneel 6 external adc 0
	float 			fExtern_LnaSmPowerBackFacetMonitor; // chanel 7 external adc 0
	float			fExtern_InputLnaPd_Ref2; // chanel 23 external adc 2
	float 			fExtern_HpaSmCurrentBackFacetMonitor; // chanel 22 external adc 2
	
	float			fIntern_PdReference; // internal ch 13
	
	/*---*/
	float			fCaseTemperature;
	float 			fSingleModeLaserDiodeTemperature;
	
	float			fSingleModeLaserCurrentMonitor;
	float			fInputDbmPowerPd21;
	float			fInputDbmPowerLambda1Pd22;
	float			fInputDbmPowerLambda2Pd23;
	float			fValueBackFacetCurrentLaserPumpLna; 			/*				mA ->  0..255 .  bit 56..63*/
	float				fValueOfLaserPumpTemperatureLna; 				/* -40 to 90degres ->  0..127 .  bit 41..47*/
	
}xAnalogInputs_t;

typedef struct
{
	
	/* lna thermistor*/
	int16_t 											sThresholdForLnaSmAlarmWayTooLowTemperature;
	int16_t 											sThresholdForLnaSmAlarmTooLowTemperature;
	int16_t 											sThresholdForLnaSmAlarmTooHighTemperature;
	int16_t 											sThresholdForLnaSmAlarmWayTooHighTemperature;
	/*hpa Sm thermistor*/
	int16_t 											sThresholdForHpaSmAlarmWayTooLowTemperature;
	int16_t 											sThresholdForHpaSmAlarmTooLowTemperature;
	int16_t 											sThresholdForHpaSmAlarmTooHighTemperature;
	int16_t 											sThresholdForHpaSmAlarmWayTooHighTemperature;
	/*hpa Mm thermistor1*/
	int16_t 											sThresholdForHpaMm1AlarmWayTooLowTemperature;
	int16_t 											sThresholdForHpaMm1AlarmTooLowTemperature;
	int16_t 											sThresholdForHpaMm1AlarmTooHighTemperature;
	int16_t 											sThresholdForHpaMm1AlarmWayTooHighTemperature;
	/*hpa Mm thermistor2*/
	int16_t 											sThresholdForHpaMm2AlarmWayTooLowTemperature;
	int16_t 											sThresholdForHpaMm2AlarmTooLowTemperature;
	int16_t 											sThresholdForHpaMm2AlarmTooHighTemperature;
	int16_t 											sThresholdForHpaMm2AlarmWayTooHighTemperature;
	/*hpa Mm thermistor3*/
	int16_t 											sThresholdForHpaMm3AlarmWayTooLowTemperature;
	int16_t 											sThresholdForHpaMm3AlarmTooLowTemperature;
	int16_t 											sThresholdForHpaMm3AlarmTooHighTemperature;
	int16_t 											sThresholdForHpaMm3AlarmWayTooHighTemperature;
	/*hpa Mm thermistor4*/
	int16_t 											sThresholdForHpaMm4AlarmWayTooLowTemperature;
	int16_t 											sThresholdForHpaMm4AlarmTooLowTemperature;
	int16_t 											sThresholdForHpaMm4AlarmTooHighTemperature;
	int16_t 											sThresholdForHpaMm4AlarmWayTooHighTemperature;
	
}xAlarmsThresholdsForTemperatureValues_t;

typedef struct
{
	//	xAlarmsThresholdsForPowerValues_t				xAlarmsThresholdsForPowerValues;
	//	xAlarmsThresholdsForCurrentValues_t			xAlarmsThresholdsForCurrentValues;
	xAlarmsThresholdsForTemperatureValues_t	xAlarmsThresholdsForTemperatureValues;
	//	xAlarmsThresholdsForVoltageValues_t			xAlarmsThresholdsForVoltageValues;
}xAlarmsThresholdsValues_t;

typedef struct
{
	uint16_t bAdc28VPwrCurrentMonitorCH1_Ok					: 1;     /* bit 0 */
	uint16_t bAdc28VPwrCurrentMonitorCH2_Ok					: 1;     /* bit 1  0: absent 1:present  */
	uint16_t bAdc28VPwrVoltageMonitorCH1_Ok					: 1;     /* bit 2  0: input optical power is within limits 	1: output optical power out of limits */
	uint16_t bAdc28VPwrVoltageMonitorCH2_Ok					: 1;     /* bit 3  0:disabled, 1:enabled */
	uint16_t bAdc7VPwrVoltageMonitorCH1_Ok					: 1;     /* bit 4 - (0: ACC, 1: APC) */
	uint16_t bAdc7VPwrVoltageMonitorCH2_Ok					: 1;     /* bit 5 - (0: ACC, 1: APC) */
	uint16_t bAdc3_3VPower_VoltageMonitor_Ok				: 1;     /* bit 6 - (0: RX Amplify CH30-1553.33 nm, 1: RX Amplify CH51-1536.61 nm) */
	uint16_t bAdc3VPower_VoltageMonitor_Ok					: 1;     /* bit 7 - (0: TX boost CH30-1553.33nm,    1: TX Boost CH51-1536.61 nm) */
	uint16_t bCan1_VoltageMonitor_Ok						: 1;     /* bit 8 - (0: within limits, 1: out of limits) */
	uint16_t bCan2_VoltageMonitor_Ok						: 1;     /* bit 9 - (0: within limits, 1: out of limits) */
	uint16_t bAdc_VoltageMonitor_Ok							: 1;     /* bit 10 - (0: within limits, 1: out of limits) */
	
} AlarmsInternalRegisterBitAssignment_t;

typedef union{
	uint16_t									usGlobalValue;
	AlarmsInternalRegisterBitAssignment_t		AlarmsInternalRegisterBitAssignment;
}xInternalAlarms_t;
	
typedef struct
{
	float						fUnitBaseTemperatureLowAlarmLimit;	/*Bit 0-7 */
	float						fUnitBaseTemperatureHighAlarmLimit;	/*Bit 8-15 */
	float						fPumpTemperatureLowAlarmLimit;	    /*Bit 16-23 */
	float						fPumpTemperatureHighAlarmLimit;	    /*Bit 24-31 */
		
	float						fPumpTemperatureVeryLowAlarmLimit;	    /*Bit 32-39 */
	float						fPumpTemperatureVeryHighAlarmLimit;	    /*Bit 40-47 */
		
		
}xPumpTemperaturesLimits_t;
	
typedef struct
{
	
	//xBoosterAnalogInputs_t						xBoosterAnalogInputs;
	//xBoosterAnalogOutputs_t						xBoosterAnalogOutputs;
	//xSafetyAnalog_t								xSafetyAnalog;
	ePower_2Channels_State_t					ePower_2Channels_State;
	CanSequence_t								CanSequence;
	eBool_t										eNvmMemoryUpdateIdNeeded;
	xAnalogInputs_t								xAnalogInputs;
	xAnalogOutputsLna_t							xAnalogOutputsLna;	
	xStatusLna_t								xStatusLna;	
	xLosStates_t								xHpaLosStates;
	xAlarmAndStatusRegister_t					xAlarmAndStatusRegister;
	xAlarmsThresholdsValues_t					xAlarmsThresholdsValues;
	/*dictionary registers */
	c010Definition_t							c010Definition;
	c401StatusDefinition_t						c401StatusDefinition;		
	c402StatusDefinition_t						c402StatusDefinition;
	c403StatusDefinition_t						c403StatusDefinition;
	c404StatusDefinition_t						c404StatusDefinition;
	c405Definition_t							c405Definition;
	c414StatusDefinition_t						c414StatusDefinition;
	c415StatusDefinition_t						c415StatusDefinition;
	c406PacketControlDefinition_t				c406PacketControlDefinition;
	c407PacketControlDefinition_t				c407PacketControlDefinition;
	c408StatusDefinition_t						c408StatusDefinition;
	c409StatusDefinition_t						c409StatusDefinition;
	c410StatusDefinition_t						c410StatusDefinition;
	c40AStatusDefinition_t						c40AStatusDefinition;
	c411StatusDefinition_t						c411StatusDefinition;
	c412StatusDefinition_t						c412StatusDefinition;
	c413StatusDefinition_t						c413StatusDefinition;
//	c426StatusDefinition_t						c426StatusDefinition;
	c428StatusDefinition_t						c428StatusDefinition;	
	
	c423StatusDefinition_t						c423StatusDefinition; //	xInternalAnalogInputsCpu;
	xExternalAnalogThermistorsInputs_t			xExternalAnalogThermistorsInputs;
	xFaultsPresents_t							xFaultsPresents;
	eBool_t										bPasswordIsCorrect;
	xHardwareErrors_t							xHardwareErrors;
	xExternalAdcChannlesRaw_t					xExternalAdcChannlesRaw;
	xPumpTemperaturesLimits_t					xPumpTemperaturesLimits;
	
	//eBool_t										bCalibNeeded ;
	eBool_t										bWriteCommonMemoryNeeded ;
	eBool_t										bWriteLnaMemoryNeeded ;
	eBool_t										bWriteBoosterMemoryNeeded ;
	eBool_t										bWriteAllMemoryNeeded ;
	eOperationMode_t							eOperationModeLna;
	eOperationMode_t							eOperationModeBoost;
	xPowersInMiliWats_t							xPowersInMiliWats;
	xPowersIndBM_t								xPowersIndBM;
	//xHpaStuckStatus_t							xHpaStuckStatusSm1;
	//xHpaStuckStatus_t							xHpaStuckStatusMm1;
	//xHpaStuckStatus_t							xHpaStuckStatusMm2;
//	CanBusStatusRegisterBitAssignment_t					CanBusStatusRegisterBitAssignment;
	xFinalSetpoints_t							xFinalSetpoints;
	xInternalAlarms_t							xInternalAlarms;
	xCurrentControlValues_t						xCurrentControlValues;
	uint8_t									eLnaState;
	uint8_t									eHpaState;
	uint8_t									eHpaApcState;
	
	uint8_t							eMainLoopState;
	float										fCurrentSave;

} xAmplifierDescriptor_t;

/*
typedef struct
{
	xInputScalingExternalAdc_t					xInputScalingExternalAdc;
	xOutputScalingDac_t							xOutputScalingDac;
	eBool_t										bCanPort1Selected;
	uint8_t										ucCompanyId;
	uint32_t									ulSerialNumber;
	xPidValues_t								xPidValuesLna;
	xPidValues_t								xPidValuesBooster;
	eOperationMode_t							eOperationModeBoost;
	eOperationMode_t							eOperationModeLna;
	uint8_t										cResetCause;
	//xAlarmRegister_t		 					xAlarmRegister ;
	
	uint8_t										cSoftwareVersion[4];
	uint8_t										cIdNumber;
	eBool_t										bSendFactory;
	uint16_t									usCrc16Value;
} xAmplifierParameters_t;*/

typedef struct
{
	xInputScalingCommonControlExternalAdc_t					xInputScalingCommonControlExternalAdc;
	eBool_t													bCanPort1Selected;
	uint8_t													ucCompanyId;
	uint32_t												ulSerialNumber;
	uint8_t													cResetCause;
	uint8_t													cSoftwareVersion[4];
	uint8_t													cIdNumber;
	eBool_t													bSendFactory;
	uint16_t												usCrc16Value;
} xCommonControlParameters_t;

typedef struct
{
	xInputScalingLnaAdc_t							xInputScalingLnaAdc;
	xOutputScalingLnaDac_t							xOutputScalingLnaDac;
	xPidValues_t									xPidValuesLna;
//	xLosValues_t									xLosValues;
	uint16_t										usMaxCurrentRange;
	xElectricLimits_t								xElectricLimits;
	uint16_t										usCrc16Value;
} xLnaParameters_t;




typedef struct
{
	xInputScalingBoosterExternalAdc_t				xInputScalingBoosterExternalAdc;
	xOutputScalingBoosterDac_t						xOutputScalingBoosterDac;
	xPidValues_t									xPidSmValuesBooster;
	xPidValues_t									xPidMm1ValuesBooster;
	xPidValues_t									xPidMm2ValuesBooster;
	xPidValues_t									xPidMm1and2ValuesBooster;
	xLosValues_t									xLosHpaValues; 
	xHpaPowersConfig_t								xHpaPowersConfig;	
	xHpaLimitsConfig_t								xHpaLimitsConfig;
	xPumpTemperaturesLimits_t						xPumpTemperaturesLimits;
	uint16_t										usCrc16Value;
} xBoosterParameters_t;


typedef enum
{
	eThreshold1545OutputPower = 0,
	eThreshold1980OutputPower = 1,
	eThresholdQfbCaseTemperature = 2,
	eThreshold940MultiModeLaserDiodeCurrent = 3,
	eThreshold980SingleModeLaserDiodeCurrent = 4,
	eThreshold940MultiModeLaserDiodeCaseTemperature = 5,
	eThreshold980SingleModeLaserDiodeCaseTemperature = 6,
	eThreshold980LaserDiodeTecCurrent = 7,
	eThreshold940MultiModeLaserDiodeCurrentSetpoint = 8,
	eThreshold980SingleModeLaserDiodeCurrentSetpoint = 9,
	eThresholdInternalMcuTemperature = 10,
	eThresholdInternal_1_0_bandGapMonitor = 11,
	eThresholdInternal_1_5_bandGapMonitor = 12,
	eThresholdInternalAnalog_1_5_Monitor = 13,
	eThresholdInternalDigital_1_5_Monitor = 14,
	eThresholdInternal_2_5_V_referenceVoltageMonitor = 15,
	eThresholdRs485CurrentMonitorSp1Negative = 16,
	eThresholdRs485CurrentMonitorCommonPositive = 17,
	eThresholdRs485CurrentMonitorSp0Negative = 18,
	eThresholdFramMemoryCurrentMonitorBankANegative = 19,
	eThresholdFramMemoryCurrentMonitorCommonPositive = 20,
	eThresholdFramMemoryCurrentMonitorBankBNegative = 21,
	eThresholdPhotoDiodeOffset = 22,
	eThreshold980SingleModeLaserDiodeBackFacetMonitor = 23,
	eThresholdTotalNumberOfIndexAlarms = 24,
}eThresholdValues_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief		Init the laser beams
*/
//void vLaserBeamsInit( void ); //xLaserBeamDescriptor_t *pxLaserBeamDescriptor );






/**
* @brief		get the laser data
*///
void vLaserInitBooster(void);
void vLaserInitLna(void);
void vLaserDataInit(void);
void vControlAlarmInitAlarms(void);

CanSequence_t getCanSequence(void);

void setCanSequence(CanSequence_t  CanSequence);

void vLaserBeamsFactoryCommonDefaultValues( void );
void vLaserBeamsFactoryLnaDefaultValues( void );
void vLaserBeamsFactoryBoosterDefaultValues( void );

/**
* @brief	    get the full data strccture descriptor for the lasers 
*/
xAmplifierDescriptor_t* vGetxAmplifierDescriptor( void );

//xAmplifierParameters_t* vGetxAmplifierParameters( void );
//xLnaParameters_t * vGetpxLnaParameters( void );
xLnaParameters_t * vGetpxLnaParameters( xLnaParameters_t *xLnaParametersl );
xBoosterParameters_t * vGetpxBoosterParameters( void );
void vLaserSetTemperatureInCan( handle_t xStream, float fTemperatureReaded);

eMpbError_t	eLaserGetLimitTemperature( handle_t xStream, float *pfVeryHighLimit , float *pfVeryLowLimit, float *pfHighLimit );
void vLaserSetTemperatureFlagAlarm( handle_t xStream, eBool_t bVeryLowAlarm , eBool_t bVeryHighAlarm, eBool_t bHighAlarm );		

xCommonControlParameters_t * vGetpxCommonControlParameters( void );
void vClearResetStartup(void);

//xInternalAnalogInputsCpu_t* vpGetInternalAnalogInputs(void);

c402StatusDefinition_t* vGet402Message( void );
//float fGetVoltage(void );
eBool_t bCanPort1IsSelected( void );
void vSetCanPort1( eBool_t bSelectCan1 );

void vGetSerialNumber(uint32_t *uSerialNumber);
void vSetSerialNumber(uint32_t uSerialNumber);
void vSetSendConfig(void);
eBool_t bGetSendConfig(void);
void vResetSendConfig(void);

void vGetCompanyId(uint8_t *ucCompanyId);
void vSetCompanyId(uint8_t ucCompanyId);



void vLaserDataGetCan401Info( c401StatusDefinition_t  *c401Status1Definition );
//void vLaserDataGetCan414Info( c414StatusDefinition_t  *c414StatusDefinition );
c414StatusDefinition_t *  pLaserDataGetCan414Info( void );
c415StatusDefinition_t  * pLaserDataGetCan415Info( void );



c402StatusDefinition_t* vLaserDataGetData402(void );

void vLaserDataGetCan402Info( c402StatusDefinition_t  *c402StatusDefinition );
c402StatusDefinition_t  * pLaserDataGetCan402Pointer( void );

void vLaserDataGetCan403Info( c403StatusDefinition_t  *c403StatusDefinition );
void vLaserDataGetCan404Info( c404StatusDefinition_t  *c404StatusDefinition );
void vLaserDataGetCan405Info( c405Definition_t  *c405Definition );

c406PacketControlDefinition_t* vLaserDataGetData406(void );
void vLaserDataGetCan406Info( c406PacketControlDefinition_t  *c406PacketControlDefinition );
void vLaserDataSetCan406Info( c406PacketControlDefinition_t  *c406PacketControlDefinition );

c407PacketControlDefinition_t* vLaserDataGetData407(void );
void vLaserDataGetCan407Info( c407PacketControlDefinition_t  *c407PacketControlDefinition );
void vLaserDataSetCan407Info( c407PacketControlDefinition_t  *c407PacketControlDefinition );
c408StatusDefinition_t* vLaserDataGetData408(void );
void vLaserDataGetCan408Info( c408StatusDefinition_t  *c408StatusDefinition );

c403StatusDefinition_t* vLaserDataGetData403(void );
c404StatusDefinition_t* vLaserDataGetData404(void );
c409StatusDefinition_t* vLaserDataGetData409(void );
c410StatusDefinition_t* vLaserDataGetData410(void );
c412StatusDefinition_t* vLaserDataGetData412(void );
c413StatusDefinition_t* vLaserDataGetData413(void );
//c410StatusDefinition_t* vLaserDataGetData410(void );

eBool_t bValidatePassword(c412StatusDefinition_t* c412StatusDefinition, c413StatusDefinition_t* c413StatusDefinition );

void vLaserDataGetCan409Info( c409StatusDefinition_t  *c409StatusDefinition );
c409StatusDefinition_t  * vLaserDataGetCan409Pointer( void  );
c40AStatusDefinition_t* vLaserDataGetCan40AInfo( void );
void vLaserDataGetCan423Info( c423StatusDefinition_t  *c423StatusDefinition );

c428StatusDefinition_t * pLaserDataGetCan428Info( void );
xExternalAnalogThermistorsInputs_t*  pLaserDataGetThermistorData( void );
void vLaserDataGetCan411Info( c411StatusDefinition_t  *c411StatusDefinition );
//void vLaserDataGetCanMpb40AInfo( c40AStatusDefinition_t  *c40AStatusDefinition );
								




//void vUpdateNvmMemory(void);

void vUpdateCommonNvmMemory(void);
void vUpdateLnaNvmMemory(void);
void vUpdateBoostNvmMemory(void);

void vUpdateConfigInfo(void);
eBool_t bInitCommonMemoryImageFromNvm(void);
eBool_t bInitLnaMemoryImageFromNvm(void);
eBool_t bInitBoostMemoryImageFromNvm(void);


xPidValues_t* getLnaPidValues( void);
void setLnaPidProportionalValue( float fPvalue);
void setLnaPidIntegralValue( float fPvalue);
void setLnaPidDerivativeValue( float fPvalue);

uint8_t cGetresetCause(void);

/*
void vTestSerialMemory(void);
void vCheckCalibrationFactors(void);
eBool_t bExternalMemoryIsReadedAndHaveGoodData(void);
void vSafetyCheckLimits(void);
eBool_t bSystemInAlarm(void);


void vLaserUpdate(void);






void vSetSpiError(void );
void vClearSpiError(void);
void vUpdatePIDValues( float f980Proportional, float f980IntegralGain,	float f980DerivativeGain , float f940Proportional, float f940IntegralGain,	float f940DerivativeGain );

void ResetSetpoint(void);
*/

/* -- icd 2.07 functions-*/
void setInternalCriticalErrorFlag(eBool_t value);
void vInitWithFullResetRequest(void); 

void vIncreaseSpiAdcErrors(void);
void vClearSpiAdcErrors(void);
void vIncreaseSpiFramErrors(void);
void vClearSpiFramErrors(void);
void vIncreaseCanErrors(void);
//void vUpdateNvm(eBool_t bUpdate);

//eBool_t vGetUpdateNvm(void);


eBool_t vGetUpdateMemoryWriteNeeded(void);
eBool_t bResetIsDemanded(void);
eBool_t vGetUpdateCommonMemoryWriteNeeded(void);
eBool_t vGetUpdateLnaMemoryWriteNeeded(void);
eBool_t vGetUpdateBoosterMemoryWriteNeeded(void);


void vSetUpdateMemoryWriteNeeded(eBool_t bWriteMemoryNeeded);

void vSetUpdateCommonMemoryWriteNeeded(eBool_t bWriteMemoryNeeded);
void vSetUpdateLnaMemoryWriteNeeded(eBool_t bWriteMemoryNeeded);
void vSetUpdateBoosterMemoryWriteNeeded(eBool_t bWriteMemoryNeeded);

void vCopyImageCommonNvm(void);
void vCopyImageLnaNvm(void);
void vCopyImageBoosterNvm(void);
void vLaserSetCurrentAlarm( eBool_t bAlarmExist);
void vUpdateLnaPIDValues( float fLnasingleProportional, float fLnasingleIntegralGain,	float fLnasingleDerivativeGain  );
void vUpdateHpaSmPIDValues( float fHpaSingleProportional, float fHpaSingleIntegralGain,	float fHpaSingleDerivativeGain );
void vUploadHpaSmPIDValues( float *pfHpaSingleProportional, float *pfHpasingleIntegralGain,	float *pfHpasingleDerivativeGain  );

void vUpdateHpaMm1PIDValues( float fHpaSingleProportional, float fHpaSingleIntegralGain,	float fHpaSingleDerivativeGain );
void vUpdateHpaMm2PIDValues( float fHpaSingleProportional, float fHpaSingleIntegralGain,	float fHpaSingleDerivativeGain );
void vUpdateHpaMm1and2PIDValues( float fHpaMM1and2Proportional, float fHpaMM1and2IntegralGain,	float fHpaMM1and2DerivativeGain );
/*---*/
/*void vEnableDisableLnaFunction(eBool_t bEnable);
void vEnableDisableBoosterFunction(eBool_t bEnable);
void vReportEnableFunction(eBool_t bEnable);*/



void vEnableLna(eBool_t bEnable);
void vEnableHpaSingleMode( eBool_t bEnable );
void vEnableHpaMultiMode1( eBool_t bEnable );
void vEnableHpaMultiMode2( eBool_t bEnable );

xPumpTemperaturesLimits_t * vpGetPumpTemperatureLimits( void);
//void vCopyImageNvm(void);
#endif /* LASERDATA_H_ */