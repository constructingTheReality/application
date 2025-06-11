/**
* @file 		temperatureReadChannel.c
* @brief		temperatureReadChannel.c source file
* @author		juan andres
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
/* Includes ----------------------------------------------------------------- */
#include "temperatureReadChannel.h"
#include "MpbMultiModeThermistor.h"
#include "MpbSingleModeThermistor.h"
#include "MpbthermistorCase.h"
#include "thermistor.h"

static xThermistorCircuitConfig_t xprvThermistorSMLnaCircuitConfig;
static xThermistorCircuitConfig_t xprvThermistorSMHpaCircuitConfig;
static xThermistorCircuitConfig_t xprvThermistorMM_1_HpaCircuitConfig;
static xThermistorCircuitConfig_t xprvThermistorMM_2_HpaCircuitConfig;
static xThermistorCircuitConfig_t xprvThermistorMM_3_HpaCircuitConfig;
static xThermistorCircuitConfig_t xprvThermistorMM_4_HpaCircuitConfig;
static xThermistorCircuitConfig_t xprvThermistorCaseCircuitConfig;


void vTemperatureReadChannelInit( void )
{
	eMpbError_t eMpbError;

	/* init the case thermistors*/
	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorCaseCircuitConfig, THERMISTOR_CASE_INT_SERIE_RESISTOR_1, THERMISTOR_CASE_INT_SERIE_RESISTOR_2, THERMISTOR_CASE_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}

	/*init the sm thermistors*/
	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorSMLnaCircuitConfig, THERMISTOR_SM_LNA_INT_SERIE_RESISTOR_1, THERMISTOR_SM_LNA_INT_SERIE_RESISTOR_2, THERMISTOR_SM_LNA_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}


	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorSMHpaCircuitConfig, THERMISTOR_SM_HPA_INT_SERIE_RESISTOR_1, THERMISTOR_SM_HPA_INT_SERIE_RESISTOR_2, THERMISTOR_SM_HPA_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}

	/* init the mm thermistors*/
	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorMM_1_HpaCircuitConfig, THERMISTOR_MM_1_HPA_INT_SERIE_RESISTOR_1, THERMISTOR_MM_1_HPA_INT_SERIE_RESISTOR_2, THERMISTOR_MM_1_HPA_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}

	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorMM_2_HpaCircuitConfig, THERMISTOR_MM_2_HPA_INT_SERIE_RESISTOR_1, THERMISTOR_MM_2_HPA_INT_SERIE_RESISTOR_2, THERMISTOR_MM_2_HPA_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}


	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorMM_3_HpaCircuitConfig, THERMISTOR_MM_3_HPA_INT_SERIE_RESISTOR_1, THERMISTOR_MM_3_HPA_INT_SERIE_RESISTOR_2, THERMISTOR_MM_3_HPA_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}


	eMpbError = eThermistorInitBaseCircuit( &xprvThermistorMM_4_HpaCircuitConfig, THERMISTOR_MM_4_HPA_INT_SERIE_RESISTOR_1, THERMISTOR_MM_4_HPA_INT_SERIE_RESISTOR_2, THERMISTOR_MM_4_HPA_INT_REFERENCE_VOLTAGE  );
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}

}
/*-----------------------------------------------------------------------*/

eMpbError_t eTemperatureReadChannelThermistor(handle_t xStream,  float *pfTemperatureReaded, uint16_t *psRawData)    
{
	
	eMpbError_t eMpbError;
	float fTemperature;
	uint8_t ucLength =0;
	xThermistorCircuitConfig_t xThermistorCircuitConfig;
	const xThermistorTemperature_t  *xThermistorTemperatureTable;

	if(xStream == eHandleAdcExSmLnaThermistor )
	{
		xThermistorCircuitConfig = xprvThermistorSMLnaCircuitConfig;
		xThermistorTemperatureTable = &xMPBSINGLEMODETHERMISTORTemperatureTable[0];
		ucLength = MPBSINGLEMODETHERMISTOR_TABLE_LENGTH;
	}
	else if(xStream == eHandleAdcExSmHpaThermistor )
	{
		xThermistorCircuitConfig = xprvThermistorSMHpaCircuitConfig;
		xThermistorTemperatureTable = &xMPBSINGLEMODETHERMISTORTemperatureTable[0];
		ucLength = MPBSINGLEMODETHERMISTOR_TABLE_LENGTH;
	}
	else if(xStream == eHandleAdcExHpaMmThermistor1 )
	{
		xThermistorCircuitConfig = xprvThermistorMM_1_HpaCircuitConfig;
		xThermistorTemperatureTable = &xMPBMULTIMODETHERMISTORTemperatureTable[0];
		ucLength = MPBMULTIMODETHERMISTOR_TABLE_LENGTH;
	}
	else if(xStream == eHandleAdcExHpaMmThermistor2 )
	{
		xThermistorCircuitConfig = xprvThermistorMM_2_HpaCircuitConfig;
		xThermistorTemperatureTable = &xMPBMULTIMODETHERMISTORTemperatureTable[0];
		ucLength = MPBMULTIMODETHERMISTOR_TABLE_LENGTH;
	}
	else if(xStream == eHandleAdcExHpaMmThermistor3 )
	{
		xThermistorCircuitConfig = xprvThermistorMM_3_HpaCircuitConfig;
		xThermistorTemperatureTable = &xMPBMULTIMODETHERMISTORTemperatureTable[0];
		ucLength = MPBMULTIMODETHERMISTOR_TABLE_LENGTH;
	}
	else if(xStream == eHandleAdcExHpaMmThermistor4 )
	{
		xThermistorCircuitConfig = xprvThermistorMM_4_HpaCircuitConfig;
		xThermistorTemperatureTable = &xMPBMULTIMODETHERMISTORTemperatureTable[0];
		ucLength = MPBMULTIMODETHERMISTOR_TABLE_LENGTH;
	}
	else if(xStream == eHandleAdcExCaseThermistor )
	{
		xThermistorCircuitConfig = xprvThermistorCaseCircuitConfig;
		xThermistorTemperatureTable = &xMPBTHERMISTORCASETemperatureTable[0];
		ucLength = MPBTHERMISTORCASE_TABLE_LENGTH;
	}
	
	
	eMpbError = eThermistorGetTemperatureTable( xStream, xThermistorCircuitConfig, (xThermistorTemperatureTable), ucLength, &fTemperature, psRawData );
//	eMpbError = eThermistorGetTemperatureTable( xStream, xThermistorCircuitConfig, (xThermistorTemperatureTable), ucLength, &fTemperature );
	
	if( eMpbError != eSuccess )
	{
		vMpblibsAssertParam( 0 );
	}
		
	fTemperature = ( fTemperature/100 );
	*pfTemperatureReaded = fTemperature;

   return eMpbError;	
}