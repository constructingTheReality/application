/**
* @file			thermistorCircuitUtil.h
* @brief
* @author		juan
* @date			Created on 2021-3-9
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/
/* Header guard ------------------------------------------------------------- */
#ifndef __THERMISTORCIRCUITUTIL_H
#define __THERMISTORCIRCUITUTIL_H
/* Includes ----------------------------------------------------------------- */
#include "thermistorCircuit.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief      Get the temperature from the resistor measured and beta coefficient of thermistor
* @param[in]  xStream: Application specific peripheral channel identifier
* @param[in]  xThermistorCircuitConfig: The circuit configuration structure
* @param[out] pulThermistance: Pointer to a variable where to save the resistance read
* @return     Success or library error message
* @note       Temperature precision is to the hundredths
**/
eMpbError_t eThermistorCircuitUtilGetThermistanceValue( handle_t xStream, xThermistorCircuitConfig_t xThermistorCircuitConfig, uint32_t *pulThermistance, uint16_t *pRawData );


#endif /* __THERMISTORCIRCUITUTIL_H */
