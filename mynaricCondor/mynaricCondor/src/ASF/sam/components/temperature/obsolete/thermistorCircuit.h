/**
* @file			thermistorCircuit.h
* @brief		thermistorCircuit header file.
* @author		juan
* @date			Created on 2021-03-09
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
**/
/* Header guard ------------------------------------------------------------- */
#ifndef THERMISTORCIRCUIT_H_
#define THERMISTORCIRCUIT_H_
/* Includes ----------------------------------------------------------------- */
#include "thermistor.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief        Allows to get the thermistance from the base circuit
* @param[in]    xStream: Application specific peripheral channel identifier
* @param[in]    xThermistorCircuitConfig: The circuit configuration structure
* @param[out]   pulThermistance: The thermistance
* @return       Success or library error message
*/
eMpbError_t eThermistorCircuitGetThermistance( handle_t xStream, xThermistorCircuitConfig_t xThermistorCircuitConfig,  uint32_t *pulThermistance );

#endif /* __THERMISTORCIRCUIT_H */




