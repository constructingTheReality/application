/**
* @file		    temperatureReadChannel.h
* @brief        temperature header file.
* @author		juan
* @date			Created on 2024-05-30
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2024 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef TEMPERATUREREADCHANNEL_H_
#define TEMPERATUREREADCHANNEL_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "glue.h"
#include "thermistor.h"
/* Define ------------------------------------------------------------------- */
#define THERMISTOR_INT_BETA_COEFFICIENT 3892
#define THERMISTOR_CASE_BETA_COEFFICIENT 3976



#define THERMISTOR_CASE_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_CASE_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_CASE_INT_REFERENCE_VOLTAGE		( 3300 ) //2500 ) 			/* mV */
//#define THERMISTOR_CASE_INT_BETA_COEFFICIENT		( 3976 )

#define THERMISTOR_SM_LNA_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_SM_LNA_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_SM_LNA_INT_REFERENCE_VOLTAGE		( 3300 )


#define THERMISTOR_SM_HPA_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_SM_HPA_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_SM_HPA_INT_REFERENCE_VOLTAGE		( 3300 )


#define THERMISTOR_MM_1_HPA_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_MM_1_HPA_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_MM_1_HPA_INT_REFERENCE_VOLTAGE		( 3300 )

#define THERMISTOR_MM_2_HPA_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_MM_2_HPA_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_MM_2_HPA_INT_REFERENCE_VOLTAGE		( 3300 )

#define THERMISTOR_MM_3_HPA_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_MM_3_HPA_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_MM_3_HPA_INT_REFERENCE_VOLTAGE		( 3300 )

#define THERMISTOR_MM_4_HPA_INT_SERIE_RESISTOR_1	  ( 10000 ) 			/* Ohm */
#define THERMISTOR_MM_4_HPA_INT_SERIE_RESISTOR_2	  ( 10000 )		    /* Ohm */
#define THERMISTOR_MM_4_HPA_INT_REFERENCE_VOLTAGE		( 3300 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	float fIntercept;
	float fSlope;

}xTemperatureInputScaling_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */


void vTemperatureReadChannelInit( void );


/**
  * @brief 		get temperature value for a specific channel  
  * @param[in]	xStream: the driver hardware number
  * @param[in]	pfTemperatureReaded: the temperature read in c.
  * @param[in]	pfTemperatureReaded: the temperature read in c.
  * @param[out]	pCriticalAnalogPower: the power reads.
  */

eMpbError_t eTemperatureReadChannelThermistor(handle_t xStream,  float *pfTemperatureReaded , uint16_t *psRawData)   ;



#endif /* TEMPERATUREREADCHANNEL_H_ */