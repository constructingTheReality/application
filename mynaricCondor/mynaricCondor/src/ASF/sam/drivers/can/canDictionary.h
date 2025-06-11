/**
* @file			canDictionary.h
* @brief
* @author		juan andres castano
* @date			Created on 2023-01-19
* @note
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
#ifndef CANDICTIONARY_H_
#define CANDICTIONARY_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
#include "can409Packet.h"
#include "can404PAcket.h"
#include "can405Packet.h"
#include "can406Packet.h"
#include "can407Packet.h"
#include "can408Packet.h"
#include "can401Packet.h"
#include "can402Packet.h"
#include "can010Packet.h"
#include "can403Packet.h"
#include "can40APacket.h"
#include "can414Packet.h"
#include "can415Packet.h"
#include "can411Packet.h"
#include "can412Packet.h"
#include "can413Packet.h"
#include "can410Packet.h"
#include "can423Packet.h"
#include "can426Packet.h"
#include "can428Packet.h"
#include "dictionaryUtils.h"
/* Define ------------------------------------------------------------------- */





#define DEF_RANGE_1_HIGH_LIMIT_SETPOINT_POWER_LNA	             ( -2.9 )
#define DEF_DECIMAL_RANGE_1_HIGH_LIMIT_SETPOINT_POWER_LNA	    ( 11 )


#define DEF_X1_COORDINATE_LINEAR_APROXIMATION_ENCODE			( -30.0)
#define DEF_Y1_COORDINATE_LINEAR_APROXIMATION_ENCODE			( 0.0)
#define DEF_X2_COORDINATE_LINEAR_APROXIMATION_ENCODE			( 38.0)
#define DEF_Y2_COORDINATE_LINEAR_APROXIMATION_ENCODE			( 255.0)

#define DEF_X1_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE1		( 0.0 )
#define DEF_Y1_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE1		( -30.0 )
#define DEF_X2_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE1		( 255.0 )
#define DEF_Y2_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE1		( 37.5 )

#define DEF_X1_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE2		( 0.0 )
#define DEF_Y1_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE2		( -30.0 )
#define DEF_X2_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE2		( 255.0 )
#define DEF_Y2_COORDINATE_LINEAR_APROXIMATION_DECODE_RANGE2		( 38.0 )

#define X1_VOLTAGE_LINEAR_APROXIMATION_ENCODE					( 0.0)
#define Y1_VOLTAGE_LINEAR_APROXIMATION_ENCODE					( 0.0)
#define X2_VOLTAGE_LINEAR_APROXIMATION_ENCODE					( 30.0)
#define Y2_VOLTAGE_LINEAR_APROXIMATION_ENCODE					( 32)

#define X1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE	( 0.0)
#define Y1_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE	( 0.0)
#define X2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE	( 1000.0)
#define Y2_BACKFACET_CURRENT_BOOSTER_LINEAR_APROXIMATION_ENCODE	( 255.0)

#define X1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE		( -40.0)
#define Y1_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE		( 0.0)
#define X2_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE		( 90.0)
#define Y2_INTERNAL_TEMP_SURFACE_TEMP_LINEAR_APROX_ENCODE		( 255.0)


#define X1_LASER_PUM4_POWER_LNA_RANGE1_LINEAR_APROX_ENCODE		( -13.0)
#define Y1_LASER_PUM4_POWER_LNA_RANGE1_LINEAR_APROX_ENCODE		( 0.0)
#define X2_LASER_PUM4_POWER_LNA_RANGE1_LINEAR_APROX_ENCODE		( -3.0)
#define Y2_LASER_PUM4_POWER_LNA_RANGE1_LINEAR_APROX_ENCODE		( 10.0)

#define X1_LASER_PUM4_POWER_LNA_RANGE2_LINEAR_APROX_ENCODE		( -2.9)
#define Y1_LASER_PUM4_POWER_LNA_RANGE2_LINEAR_APROX_ENCODE		( 11.0)
#define X2_LASER_PUM4_POWER_LNA_RANGE2_LINEAR_APROX_ENCODE		( 0.0 )
#define Y2_LASER_PUM4_POWER_LNA_RANGE2_LINEAR_APROX_ENCODE		( 255.0)




#define X1_POWER_SETPOINT_BOOST_RANGE2_LINEAR_APROX_ENCODE		( 37.6)
#define Y1_POWER_SETPOINT_BOOST_RANGE2_LINEAR_APROX_ENCODE		( 681.0)
#define X2_POWER_SETPOINT_BOOST_RANGE2_LINEAR_APROX_ENCODE		( 40.0 )
#define Y2_POWER_SETPOINT_BOOST_RANGE2_LINEAR_APROX_ENCODE		( 1023.0)

/* 404*/

#define DEF_LIMIT_RANGE1_POWER_SETPOINT							( 37.6 )
#define DEF_DECIMAL_LIMIT_RANGE1_POWER_SETPOINT					( 681 )
#define DEF_PRECITION											( 100 )
#define DEF_ADJUST											( 0.5 )

		
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef enum canSequence
{
	canSequence401 = 0,
	canSequence402 = 1,
	canSequence403 = 2,
	canSequence404 = 3,
	canSequence405 = 4	
}CanSequence_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void vInitCanImage( void );



#endif /* CANDICTIONARY_H_ */