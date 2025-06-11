/**
* @file           thermistor.h
* @brief          Thermistor header file.
* @author         juan andres
* @date           Created on 2021- 03 -5 
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/

/**
@page ThermistorCircuit
\verbatim

            R1                R2
    o-----/\/\/\------------/\/\/\------- A
											|
											|         
											/         
v1										\ Rt    
											/         
											|         
											|         
											|    
 o-----------------------------------------B
											|
										GND

\endverbatim
 **/

/* Header guard ------------------------------------------------------------- */
#ifndef __THERMISTOR_H
#define __THERMISTOR_H

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"

/* Define ------------------------------------------------------------------- */
#define MAX_NUMBER_OF_POINTS			 				25		  /* Maximum Nb of points in a TempCal list */
#define NUMBER_OF_POINTS_TO_GET_AVERAGE 	60    /*   Number of Temperature samples to average  */

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/**
* @brief    The type of thermistor
*/
typedef enum
{
	eThermistorType10k = 10000,
	eThermistorType20k = 20000,
	eThermistorType30k = 30000,
}eThermistorType_t;

/**
* @brief  Structure to associate a temperature to a resistance
* @note   Temperature value in hundredths of degree celsius (x100)
**/
typedef struct
{
                     		
    uint16_t 	usResistanceValues[ MAX_NUMBER_OF_POINTS ];    /**< Resistance value in ohms */
    int16_t  	ssTemperatureValues[ MAX_NUMBER_OF_POINTS ];  /**< Temperature value in hundredths of degree celsius (x100) */
	  uint8_t 	ucNumberOfPointsUsed;
} xTemperatureToResistence_t; 



/* Exported struct ---------------------------------------------------------- */

/**
* @brief  Structure to associate a temperature to a resistance
* @note   Temperature value in hundredths of degree celsius (x100)
**/
typedef struct
{
    uint32_t ulResistance;    /**< Resistance value in ohms */
    int16_t  ssTemperature;   /**< Temperature value in hundredths of degree celsius (x100) */
}xThermistorTemperature_t;

/**
* @brief  Circuit configuration structure for temperature control with a
*         thermistance
* @note   See @ref ThermistorCircuit
**/
typedef struct
{
    
    uint32_t ulSeriesResistor1;     /**< Series resistor configuration 1 */
    uint32_t ulSeriesResistor2;     /**< Series resistor configuration 2 */
		uint16_t usReferenceVoltagemV;  /**< Voltage Reference in mV */
}xThermistorCircuitConfig_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief      Initialize the thermistor base circuit structure
* @param[out] pxThermistorCircuitConfig: Pointer to the circuit
*             configuration structure
* @param[in]  ulSeriesResistor1: Resistor next to voltage source
* @param[in]  ulSeriesResistor2: Resistor next to output voltage 
* @param[in]  usReferenceVoltagemV: reference voltage in mV
* @param[in]  usInputVoltagemV: Source voltage in mV
* @return     Success or library error message
* @note       Input voltage also can't be 0.
**/
eMpbError_t eThermistorInitBaseCircuit( xThermistorCircuitConfig_t *pxThermistorCircuitConfig, uint32_t ulSeriesResistor1, uint32_t ulSeriesResistor2, uint16_t usReferenceVoltagemV );

/**
* @brief      Get the temperature from the required look-up table using the
*             ADC value
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[in]  xThermistorCircuitConfig: The circuit configuration structure
* @param[in]  pxTemperatureTable: Pointer to the temperature look-up table
* @param[in]  ucLength: Temperature look-up table length
* @param[out] pfTemperature: Pointer to a variable where to save the data
* @return     Success or library error message
* @note       Temperature precision is to the hundredths
**/
eMpbError_t eThermistorGetTemperatureTable( handle_t xStream, xThermistorCircuitConfig_t xThermistorCircuitConfig, const xThermistorTemperature_t *pxTemperatureTable, uint8_t ucLength, float *pfTemperature, uint16_t *pRawData );

/**
* @brief      Get the temperature from the resistor measured and beta coefficient of thermistor
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[in]  ulBetaCoefficient: beta coefficient of thermistor
* @param[in]  xThermistorCircuitConfig: The circuit configuration structure
* @param[in]  eThermistorType: 10K Thermistor, 20K Thermistor, etc...
* @param[out] pfTemperature: Pointer to a variable where to save the temperature
* @return     Success or library error message
* @note       Temperature resolution is to the hundredths
* @note       Temperature precision depends on the temperature 
* @note       https://www.ametherm.com/thermistor/ntc-thermistor-beta
**/
eMpbError_t eThermistorGetTemperatureBeta( handle_t xStream, uint32_t ulBetaCoefficient, xThermistorCircuitConfig_t xThermistorCircuitConfig, eThermistorType_t eThermistorType, float *pfTemperature , uint16_t *pRawData);

/**
* @brief      Get the temperature from the mpb table method 
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[in]  ucLength: Length of the table
* @param[in]  pxTemperatureTable: Pointer to the temperature look-up table
* @param[out] pfTemperatureReaded: Pointer to a variable where to save the temperature
* @return     Success or library error message
**/
eMpbError_t eTemperatureAveragingThermistor( handle_t xStream, uint8_t ucLength, const xThermistorTemperature_t *pxTemperatureTable, float *pfTemperatureReaded );

/**
* @brief      Get the voltage of the thermistor input in mV
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[out] pusVoltage: Pointer to store the voltage
* @return     Success or library error message
**/
extern eMpbError_t eThermistorAnalogReadmV( handle_t xStream, uint16_t *pusVoltage, uint16_t *pRawData );

/**
* @brief        Calculate the log of a double for beta calculation
* @param[in]    dValue: Value that we want the log of
* @param[out]   pdResult: Result of the log
* @return       Success or library error message
*/
extern eMpbError_t eThermistorLogarithm( double dValue, double *pdResult );




#endif	/* __THERMISTOR_H */
