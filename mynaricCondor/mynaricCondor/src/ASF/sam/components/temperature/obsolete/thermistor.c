/**
* @file           thermistor.c
* @brief          Find the temperature readings according to a given
*                 temperature table and thermistor circuit
* @author         juan andres
* @date           Created on 3-8- 2021
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/
/* Includes ------------------------------------------------------------------*/
#include "thermistor.h"
#include "thermistorCircuit.h"
#include "mpbMath.h"
#include "math.h"

/* Private define ------------------------------------------------------------*/
#define _25_DEGREES_IN_FAHRENHEIT	( 298.15 )
#define KELVIN_TO_DEGREE_CONSTANT	( 273.15 )

/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
eMpbError_t vprvTemperatureInterpolation( const xThermistorTemperature_t *pxTemperatureTable,	uint8_t ucLength, float *pfTemperatureCalculated);

/*----------------------------------------------------------------------------*/
eMpbError_t vprvTemperatureInterpolation( const xThermistorTemperature_t *pxTemperatureTable,	uint8_t ucLength, float *pfTemperatureCalculated)
{
	uint8_t ucStartIndex, usEndIndex, ucGuessIndex;
	float fSlope, fTemporalVariable;
	eMpbError_t	eMpbError;
	
	ucStartIndex = 0;
	usEndIndex = ucLength - 1;
	
	/* Validate entry parameter */
	if( ( pxTemperatureTable == NULL ) ||  ( pfTemperatureCalculated == NULL ) )
	{
		return eInvalidParameter;
	}

	/* Reporting an out of range error when a value exceeds the */
	/* temperature limits of the temperature table. Temperature */
	/* is then the maximum or the minimum, accordingly */
	if( *pfTemperatureCalculated > (float)pxTemperatureTable[ 0 ].ulResistance )
	{
		*pfTemperatureCalculated = pxTemperatureTable[ 0 ].ssTemperature;
		return eOutOfRange;
	}
	else if( *pfTemperatureCalculated < (float)pxTemperatureTable[ ucLength - 1 ].ulResistance )
	{
		*pfTemperatureCalculated = pxTemperatureTable[ ucLength - 1 ].ssTemperature;
		return eOutOfRange;
	}
	

	/* binary search for the index of the closest values */
	do
	{
		ucGuessIndex = ( ucStartIndex + usEndIndex ) >> 1;

		if ( ( (float)pxTemperatureTable[ ucGuessIndex ].ulResistance < *pfTemperatureCalculated ) )
		{
			ucStartIndex = ucGuessIndex++;
		}
		else
		{
			usEndIndex = ucGuessIndex;
		}
	}
	while ( ( ucStartIndex + 1 ) != usEndIndex);
	

	/* Perform interpolation */
	eMpbError = eMpbMathDivisionFloat( ((float)( pxTemperatureTable[ usEndIndex ].ssTemperature - pxTemperatureTable[ ucStartIndex ].ssTemperature )),
	((float)( pxTemperatureTable[ usEndIndex ].ulResistance - pxTemperatureTable[ ucStartIndex ].ulResistance )), &fSlope);
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	fTemporalVariable = fSlope * ( *pfTemperatureCalculated -(float)pxTemperatureTable[ ucStartIndex ].ulResistance ) ;
	
	*pfTemperatureCalculated = (float)( pxTemperatureTable[ ucStartIndex ].ssTemperature ) + fTemporalVariable ;
	
	return eMpbError;
}

/* Exported functions --------------------------------------------------------*/

eMpbError_t eThermistorInitBaseCircuit( xThermistorCircuitConfig_t *pxThermistorCircuitConfig, uint32_t ulSeriesResistor1, uint32_t ulSeriesResistor2, uint16_t usReferenceVoltagemV )
{
	/* Validate entry parameter  to validate */
	if(  pxThermistorCircuitConfig == NULL   )
	{
		return eInvalidParameter;
	}
	
	/* Init Thermistor */
	pxThermistorCircuitConfig->ulSeriesResistor1 = ulSeriesResistor1;
	pxThermistorCircuitConfig->ulSeriesResistor2 = ulSeriesResistor2;
	pxThermistorCircuitConfig->usReferenceVoltagemV = usReferenceVoltagemV;

	return eSuccess;
}
/*----------------------------------------------------------------------------*/

eMpbError_t eThermistorGetTemperatureTable( handle_t xStream, xThermistorCircuitConfig_t xThermistorCircuitConfig, const xThermistorTemperature_t *pxTemperatureTable, uint8_t ucLength, float *pfTemperature )
{
	eMpbError_t eMpbError;
	uint32_t ulThermistance;
	static uint32_t ulTest1 = 0;
	static int32_t slTest1 = 0;
	static uint32_t ulTest2 = 0;
	static int32_t slTest2 = 0;	
	
	/* Validate entry parameters */
	if( ( pxTemperatureTable == NULL ) || ( pfTemperature == NULL ) )
	{
		return eInvalidParameter;
	}
	
	/* Get thermistance */
	eMpbError = eThermistorCircuitGetThermistance( xStream, xThermistorCircuitConfig, &ulThermistance );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	/* Reporting an out of range error when a value exceeds the */
	/* temperature limits of the temperature table. Temperature */
	/* is then the maximum or the minimum, accordingly */
	if( ulThermistance > pxTemperatureTable[ 0 ].ulResistance )
	{
		*pfTemperature = pxTemperatureTable[ 0 ].ssTemperature;
		return eOutOfRange;
	}
	else if( ulThermistance < pxTemperatureTable[ ucLength - 1 ].ulResistance )
	{
		*pfTemperature = pxTemperatureTable[ ucLength - 1 ].ssTemperature;
		return eOutOfRange;
	}
	else
	{
		for( uint8_t ucI = 0; ucI < ucLength ; ucI++ )
		{
			if( pxTemperatureTable[ ucI ].ulResistance == ulThermistance )
			{
				*pfTemperature = pxTemperatureTable[ ucI ].ssTemperature;
				return eMpbError;
			}
			ulTest1 = pxTemperatureTable[ ucI ].ulResistance ;
			slTest1 = pxTemperatureTable[ ucI ].ssTemperature ;
			
			ulTest2 = pxTemperatureTable[ ucI - 1 ].ulResistance ;
			slTest2 = pxTemperatureTable[ ucI - 1 ].ssTemperature ;
			
			if( pxTemperatureTable[ ucI ].ulResistance < ulThermistance )
			{
				return eMpbMathLinearApproxFloat( (float)pxTemperatureTable[ ucI ].ulResistance, (float)pxTemperatureTable[ ucI ].ssTemperature, (float)pxTemperatureTable[ ucI - 1 ].ulResistance, pxTemperatureTable[ ucI - 1 ].ssTemperature, (float)ulThermistance, eMpbMathCoerce, pfTemperature );
			}
		}
	}
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eThermistorGetTemperatureBeta( handle_t xStream, uint32_t ulBetaCoefficient, xThermistorCircuitConfig_t xThermistorCircuitConfig, eThermistorType_t eThermistorType, float *pfTemperature )
{
	uint32_t ulThermistance;
	double dLogResult;
	float fDivResult;
	eMpbError_t eMpbError;
	
	/* Validate entry parameter */
	if( pfTemperature == NULL )
	{
		return eInvalidParameter;
	}
	
	/* Get thermistance */
	eMpbError = eThermistorCircuitGetThermistance( xStream, xThermistorCircuitConfig, &ulThermistance );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	/* log( Rt1/Rt2 )	*/
	eMpbError = eMpbMathDivisionFloat( eThermistorType, (float)ulThermistance, &fDivResult );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	/* Calculate the log */
	eMpbError = eThermistorLogarithm( ( double ) fDivResult, &dLogResult );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	/*	( Beta/T1 ) - log( Rt1/Rt2 )	*/
	eMpbError = eMpbMathDivisionFloat( (float)ulBetaCoefficient, (float)_25_DEGREES_IN_FAHRENHEIT, &fDivResult );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	fDivResult -= ( float )dLogResult;
	
	/*	Beta / [ ( Beta/T1 ) - log( Rt1/Rt2 ) ]	*/
	eMpbError = eMpbMathDivisionFloat( (float)ulBetaCoefficient, (float)fDivResult, &fDivResult );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	/* conversion from Kelvin to Celsius	*/
	*pfTemperature = ( fDivResult - (float)KELVIN_TO_DEGREE_CONSTANT );
	
	return eMpbError;
}

/*-----------------------------------------------------------------------------*/
eMpbError_t eTemperatureAveragingThermistor( handle_t xStream, uint8_t ucLength, const xThermistorTemperature_t *pxTemperatureTable, float *pfTemperatureReaded )
{
	
	static uint8_t 	ucAccumulatorIndex = 0;
	uint16_t 				usVoltage;
	static float 		fTemperatureCalculated = 0.0f;
	static float		fTemperatureAccumulator = 0.0f;
	eMpbError_t			eMpbError;
	uint16_t			usRaw;
	
	/* Validate parameter */
	vMpblibsAssertParam( pxTemperatureTable );
	
	/* Get thermistor voltage */
	eMpbError = eThermistorAnalogReadmV( xStream, &usVoltage, &usRaw );
	if( eMpbError != eSuccess )
	{
		return eMpbError;
	}
	
	fTemperatureCalculated = (float)usVoltage;
	
	/* Interpolate actual raw data to get actual temperature  */
	eMpbError = vprvTemperatureInterpolation( pxTemperatureTable,	ucLength, &fTemperatureCalculated );
	
	/*  Accumulate the temperature measurements */
	fTemperatureAccumulator += fTemperatureCalculated;
	ucAccumulatorIndex++;

	/* Compute Average Temperature if enough measurements  */
	if ( ucAccumulatorIndex >= NUMBER_OF_POINTS_TO_GET_AVERAGE )
	{
		eMpbError = eMpbMathDivisionFloat( fTemperatureAccumulator, (float)ucAccumulatorIndex, pfTemperatureReaded );
		if( eMpbError != eSuccess )
		{
			return eMpbError;
		}
		fTemperatureAccumulator = 0.0;
		ucAccumulatorIndex = 0;
	}
	
	return eMpbError;
}

/*----------------------------------------------------------------------------*/
eMpbError_t eThermistorLogarithm( double dValue, double *pdResult )
{
	*pdResult = log( dValue );
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/
eMpbError_t eThermistorAnalogReadmV( handle_t xStream, uint16_t *pusVoltage, uint16_t *pRawData )
{
	int32_t slAdcVoltage;
	uint16_t usRaw =0;
	
	eMpblibsAnalogReadmV( xStream, &slAdcVoltage , &usRaw);
	
	/* Need one operand to be a float, the other will be promoted */
	*pusVoltage = ( ( ( uint16_t ) slAdcVoltage ) ) ;
	*pRawData = usRaw; 
	
	
	return eSuccess;
}
