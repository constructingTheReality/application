/**
* @file			can401Packet.h
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
#ifndef CAN401PACKET_H_
#define CAN401PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */

#define DEF_PRECITION											( 100 )

#define FIRST_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER			( 20 )  /*in dBm */
#define FIRST_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER_			( 19 )  /*in dBm */

#define SECOND_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER			( 37 )

#define THIRD_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER			( 40 )
#define THIRD_DECIMAL_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER	( 255 )

#define SECOND_DECIMAL_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER	( 193 ) 

#define DEF_CAN_0401_PUMP1_CURRENT_IN_BOOSTER					 0

#define DEF_CAN_0401_PUMP2_CURRENT_IN_BOOSTER					 16

#define DEF_CAN_0401_PUMP3_CURRENT_IN_BOOSTER					 32

#define DEF_CAN_0401_PUMP4_CURRENT_IN_LNA						 48

#define DEF_CAN_0401_BOOSTER_OPTICAL_INPUT_POWER   				 40
#define DEF_CAN_0401_LNA_OPTICAL_OUTPUT_POWER   				 48
#define DEF_CAN_0401_BOOSTER_OPTICAL_OUTPUT_POWER   			 56




#define FIRST_DECIMAL_LIMIT_FOR_BOOSTER_OUTPUT_OPTICAL_POWER	( 17 ) /* in decimal */


#define X1_CHANEL_30_1553_NM_INPUT_OPT_POW_BOOSTER_ENCODE		( -10.0)
#define Y1_CHANEL_30_1553_NM_INPUT_OPT_POW_BOOSTER_ENCODE		( 0.0)
#define X2_CHANEL_30_1553_NM_INPUT_OPT_POW_BOOSTER_ENCODE		( 6.0)
#define Y2_CHANEL_30_1553_NM_INPUT_OPT_POW_BOOSTER_ENCODE		( 255.0 )


#define X1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define X2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 16383.0)
#define Y2_401_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 65535.0)


#define X1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define X2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 16383.0)
#define Y2_401_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 65535.0)

#define X1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define X2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 16383.0)
#define Y2_401_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 65535.0)


#define X1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 0.0)
#define X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 16383.0)
#define Y2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 65535.0)




#define X1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE		( -10.0)
#define Y1_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE		( 0.0)
#define X2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE		( 6.0)
#define Y2_CHANEL_1_CH51_1536_NM_IN_OPT_POW_BOOSTER_ENCODE		( 255.0)
#define X1_CHANEL_30_1553_NM_OUTPUT_POW_LNA_ENCODE				( 0.0)
#define Y1_CHANEL_30_1553_NM_OUTPUT_POW_LNA_ENCODE				( 0.0)
#define X2_CHANEL_30_1553_NM_OUTPUT_POW_LNA_ENCODE				( 1000.0)
#define Y2_CHANEL_30_1553_NM_OUTPUT_POW_LNA_ENCODE				( 255.0)

#define X1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE				( -15.0)
#define Y1_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE				( 0.0)
#define X2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE				( 0.0)
#define Y2_CHANEL_51_1536_NM_OUTPUT_POW_LNA_ENCODE				( 255.0)

#define X1_RANGE_1_BOOSTER_OUTPUT_OPTICAL_POWER					( -30.0)
#define Y1_RANGE_1_BOOSTER_OUTPUT_OPTICAL_POWER					( 0.0 )
#define X2_RANGE_1_BOOSTER_OUTPUT_OPTICAL_POWER					( 19.0)
#define Y2_RANGE_1_BOOSTER_OUTPUT_OPTICAL_POWER					( 17.0 )

#define X1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER					( 16.0)
#define Y1_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER					( 0 )
#define X2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER					( 37.5)
#define Y2_RANGE_2_BOOSTER_OUTPUT_OPTICAL_POWER					( 255 )

#define X1_RANGE_3_BOOSTER_OUTPUT_OPTICAL_POWER					( 37.0)
#define Y1_RANGE_3_BOOSTER_OUTPUT_OPTICAL_POWER					( 194.0 )
#define X2_RANGE_3_BOOSTER_OUTPUT_OPTICAL_POWER					( 40.0)
#define Y2_RANGE_3_BOOSTER_OUTPUT_OPTICAL_POWER					( 255.0 )

#define FLOAT_ADJUST  0.5

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{	
	float						fLaserPump1BoosterCurrent;				/*16 bits :  0...65536  , 0ma to 32768 mA, bits  0 to 15 */
	float						fLaserPump2BoosterCurrent;				/*16 bits :  0...65536  , 0ma to 32768 mA, bits  16 to 31 */
	float						fLaserPump3BoosterCurrent;				/*16 bits :  0...65536  , 0ma to 32768 mA , bits  32 to 47 */
	float						fLaserPump4LnaCurrent;  				/*16 bits : 0...65536  , 0ma to 32768 mA, bits  48 to 63 */	
	//float						fBoosterOpticalInputPower;					/*8 bits :  0...255= -10dBm to +6dBm  , bits  40 to 47 */
	//float						fLnaOpticalOutputPower;						/*8 bits :  0...255= -15dBm to 0dBm  , bits  48 to 55 */
	//float						fBoosterOutputOpticalPower;					/*8 bits :  0...255= +16dBm to +37.5dBm  , bits  56 to 63  resolution = 0.084 dBm*/	
}c401StatusDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit401CanImage( void );

/**
* @brief		get the 401 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan401( CAN_FRAME *pCan);

/**
* @brief		set the 401 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan401( CAN_FRAME *pCan);


/**
* @brief		decode the 401 CAN message
* @param[in]	c401StatusDefinition_t: pointer to the 401 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan401Decode( c401StatusDefinition_t *c401StatusDefinition );

/**
* @brief		encode the 401 CAN message
* @param[in]	c401StatusDefinition_t: pointer to the 401 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan401Encode( c401StatusDefinition_t *c401Status1Definition );


#endif /* CAN401PACKET_H_ */