/**
* @file		    initMemory.h
* @brief        initMemory header file.
* @author		juan
* @date			Created on 2024-9-9
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
#ifndef INITMEMORY_H_
#define INITMEMORY_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
 * @brief 		Sequence to reset the LNA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vInitLnaRun(void);
/**
 * @brief 		Sequence to reset the HPA. Re-init calibration info from memory. 
 * @param[out]	none.
 */
void vInitHpaRun(void);

#endif /* INITMEMORY_H_ */