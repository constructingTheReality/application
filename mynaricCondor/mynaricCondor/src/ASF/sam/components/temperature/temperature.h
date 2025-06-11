/**
* @file		    temperature.h
* @brief        temperature header file.
* @author		juan
* @date			Created on 2023-3-10
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
#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
//#include "SPD_07179_REV_0.h"
//#include "ControlAlarm.h"
//#include "LaserDiodeBeam.h"
//#include "cmd_interface.h"

/* Define ------------------------------------------------------------------- */
#define  DEFAULT_VERY_HIGH_LIMIT   ( 70 )
#define  DEFAULT_VERY_LOW_LIMIT    ( -10.0 )
#define  DEFAULT_HIGH_LIMIT        ( 50 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/*enum
{
	eLnaSingleModeTemperatureThermistor = 0,
	eHpaSingleModeTemperatureThermistor = 1,
	eHpaMultiModeTemperatureThermistor1 = 2,
	eHpaMultiModeTemperatureThermistor2 = 3,
	eHpaMultiModeTemperatureThermistor3 = 4,
	eHpaMultiModeTemperatureThermistor4 = 5,
	eNumberTotalOfThermistors = 6,
	
};*/
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
* @brief		Init the temperature sensor circuitry
*/
void vTemperatureInit( void );

void vTemperatureUpdate( void );


#endif /* TEMPERATURE_H_ */