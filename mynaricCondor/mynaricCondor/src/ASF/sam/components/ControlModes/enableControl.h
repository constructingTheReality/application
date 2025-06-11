




/**
* @file		    accControlLaser.h
* @brief      acccontrolLaser header file.
* @author		juan
* @date			Created on 2021-03-23
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
#ifndef ENABLECONTROL_H_
#define ENABLECONTROL_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "LaserData.h"
#include "binaryInput.h"

/* Define ------------------------------------------------------------------- */

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief        Initalization of laser.
*/
void vControlLinesLaserInit( void );

/**
* @brief		Update control of laser.
*/
void vControlLinesLaserUpdateLna( void );
void vControlLinesLaserUpdateHpa( void );







#endif /* ENABLECONTROL_H_ */