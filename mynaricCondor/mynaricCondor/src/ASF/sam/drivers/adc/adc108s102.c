/**
* @file 		ADC108S102.c
* @brief		ADC108S102 source file.
* @author		juan
* @date			Created on 2021-05-4
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/

/* Includes ----------------------------------------------------------------- */
#include "adc108s102.h"
#include "binaryInput.h"
#include "bspAdc.h"
#include "bspSpi.h"
/* Private define ----------------------------------------------------------- */
#define ADC108S102_REFERENCE_VA_MV_DEFAULT		( 3300 )
//#define ADC108S102_BITS							( 12   )
//#define ADC108S102_MAX_CHANNELS					(  8   )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

//eMpbError_t eAdc128s102SpiSetup(void)
//{
//
//}

/*---------------------------------------------------------------------*/
eMpbError_t eAdc128s102ReadSingleChannel( uint8_t ucChannel, uint16_t *pusData )
{
	/*hal_status_t stat, errStat = hal_status_ok;*/
	eMpbError_t eMpbError = eSuccess; //rror;
	uint16_t usData = 0;
	
	/*
	if ( ucChannel < eAdcExLnaSmldCurrentMonitor)  //adc0
	{
		vBinaryOtputSetState( eOutputAdcCs0, eFalse );	
	}
	else if (ucChannel > eAdcExHpaSmld_Thermistor2 )  //adc2
	{
		ucChannel = ucChannel - eAdcExHpaMMld_Thermistor1;
		
		vBinaryOtputSetState( eOutputAdcCs2, eFalse );	
	}
	else      //adc1
	{
		ucChannel = ucChannel - eAdcExLnaSmldCurrentMonitor;
		vBinaryOtputSetState( eOutputAdcCs1, eFalse );	
	}*/
	
	usData = ADC108S102_CMD(ucChannel);
	
	
	
	eMpbError = eBSPSpiMasterTransfer(&usData, sizeof(usData));
	if( eMpbError != eSuccess)
	{
		*pusData = 0;
		return eMpbError;
	}
	/*vBinaryOtputSetState( eOutputAdcCs0, eTrue );
	vBinaryOtputSetState( eOutputAdcCs1, eTrue );
	vBinaryOtputSetState( eOutputAdcCs2, eTrue );*/
	
	*pusData = usData;
	*pusData &= ADC108S102_RESULT_MASK;
	/*
	stat = ADC_Init((uint8_t)spiBank, FRAM_ADC_SPI_CSN);
	if(stat != hal_status_ok){ errStat = stat; }
	
	errStat = ADC_Read( spiBank, ucChannel, pusData ) ;
	if(stat != hal_status_ok)
	{
		errStat = stat;
	}
	
	*pusData &= ADC108S102_RESULT_MASK;
	
	stat = ADC_UnInit((uint8_t)spiBank);
	if(stat != hal_status_ok)
	{
		errStat = stat;
	}

	if(errStat == hal_status_ok)
	{
		eMpbError = eSuccess;
	}
	*/
	return  eMpbError;
}
/*-------------------------------------------------------------------*/

//eMpbError_t eAdc128s102ReadChannelsContinuous( uint8_t spiBank, uint8_t ucLength, uint16_t *pusData)
//{
//
//}

/*----------------------------------------------------------------------*/





