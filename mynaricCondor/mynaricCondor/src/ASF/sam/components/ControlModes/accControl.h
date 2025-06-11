
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
#ifndef ACCCONTROL_H_
#define ACCCONTROL_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "LaserData.h"
#include "currentControl.h"

/* Define ------------------------------------------------------------------- */
#define LASER_BRAKE_DUTY_CYCLE_VALUE      ( 0 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef enum
{
	eInitAccDetection =0,
	eIncreaseActiveSetpoint = 1,
	eDecreaseActiveSetpoint = 2,
	
}eAccLaserState_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief        Initalization of laser.
*/
void vAccControlLaserInit( void );

/**
* @brief		Update control of laser.
*/
void vAccControlLaserUpdateHpaSm1( float fCurrent );
void vAccControlLaserUpdateHpaMm1( float fCurrent );
void vAccControlLaserUpdateHpaMm2( float fCurrent );
void vAccControlLaserUpdateLna( float fCurrent );






#endif /* ACCCONTROL_H_ */