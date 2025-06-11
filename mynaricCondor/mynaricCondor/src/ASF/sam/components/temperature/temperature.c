/**
* @file 		temperature.c
* @brief		temperature source file.
* @author		juan
* @date			Created on 2023-08-10
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
#include "temperature.h"
#include "mainStateMachine.h"
#include "temperatureReadChannel.h"
//#include "ControlAlarm.h"
//#include "Glue.h"

/* Private define ----------------------------------------------------------- */

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static void vprvSetTemperatureAlarms( float fTemperatureReaded , float fVeryLowLimit, float fVeryHighLimit, float fHighLimit , eBool_t *bVeryLowAlarm , eBool_t *bVeryHighAlarm , eBool_t *bHighAlarm  );

/* Private functions -------------------------------------------------------- */
static void vprvSetTemperatureAlarms( float fTemperatureReaded , float fVeryLowLimit, float fVeryHighLimit, float fHighLimit , eBool_t *bVeryLowAlarm , eBool_t *bVeryHighAlarm , eBool_t *bHighAlarm  )
{
	unsigned int precision = 100;
	
	*bVeryHighAlarm		= (mpb_float1_minor_than_float2( fVeryHighLimit , fTemperatureReaded, precision)) ? DEF_YES:DEF_NO;
	*bHighAlarm			= (mpb_float1_minor_than_float2( fHighLimit , fTemperatureReaded, precision)) ? DEF_YES:DEF_NO;
	*bVeryLowAlarm		= (mpb_float1_minor_than_float2( fTemperatureReaded, fVeryLowLimit, precision)) ? DEF_YES:DEF_NO;	
}
	 
/* Exported functions ------------------------------------------------------- */
void vTemperatureInit( void )
{
	vTemperatureReadChannelInit();	
}
/*----------------------------------------------------------------------------*/

void vTemperatureUpdate( void )
{
	eMpbError_t eMpbError ;
	float		fTemperatureReaded = 0.0f;
	float		fVeryLowLimit = 0.0f;
	float		fVeryHighLimit = 0.0f;
	float		fHighLimit = 0.0f;
	eBool_t		bVeryLowAlarm = eFalse;
	eBool_t		bVeryHighAlarm = eFalse;
	eBool_t		bHighAlarm = eFalse;
	uint16_t	usTemperatureRawData =0;
	
	/* read all the thermistors , one by one */
	for( uint8_t ucI =eHandleAdcExSmLnaThermistor; ucI<eHandleAdcPdReference; ucI++ )
	{
		
		eMpbError = eTemperatureReadChannelThermistor( ucI,  &fTemperatureReaded, &usTemperatureRawData)  ;
		if( eMpbError == eSuccess )
		{
			vLaserSetTemperatureInCan(ucI, fTemperatureReaded);
			
			eMpbError = eLaserGetLimitTemperature( ucI, &fVeryHighLimit , &fVeryLowLimit, &fHighLimit );
			if( eMpbError != eSuccess )
			{
				fVeryHighLimit	= DEFAULT_VERY_HIGH_LIMIT ;
				fVeryLowLimit	= DEFAULT_VERY_LOW_LIMIT ;
				fHighLimit		= DEFAULT_HIGH_LIMIT ;
			}
			
			/* check alarms */
			vprvSetTemperatureAlarms( fTemperatureReaded , fVeryLowLimit, fVeryHighLimit, fHighLimit ,  &bVeryLowAlarm , &bVeryHighAlarm , &bHighAlarm  );
			
			/* set db			 */
			vLaserSetTemperatureFlagAlarm( ucI, bVeryLowAlarm , bVeryHighAlarm, bHighAlarm );
			
			if( bVeryHighAlarm == eTrue) 
			{
				vSetAlarmCriticalError();
			}
		}
		
		
	}
	
}
	
/*----------------------------------------------------------------------------*/
