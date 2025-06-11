
/**
* @file			can406Packet.h
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

#ifndef CAN406PACKET_H_
#define CAN406PACKET_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define X1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define X2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 1023.0)
#define Y2_406_LASER_PUM1_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 100.0)


#define X1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define X2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 1023.0)
#define Y2_406_LASER_PUM2_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 100.0)

#define X1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 0.0)
#define X2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 1023.0)
#define Y2_406_LASER_PUM3_CURRENT_BOOSTER_LINEAR_APROX_ENCODE		( 100.0)


#define X1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 0.0)
#define X2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 1023.0)
#define Y2_406_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE		( 100.0)


#define X1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE		( 16.0)
#define X2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE		( 1023.0 )
#define Y2_406_POWER_SETPOINT_BOOST_RANGE1_LINEAR_APROX_ENCODE		( 37.5 )

/*
#define X1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE		( 0.0)
#define Y1_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE		( -15.0)
#define X2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE		( 15.0 )
#define Y2_406_POWER_SETPOINT_LNA_RANGE1_LINEAR_APROX_ENCODE		( 0.0)*/

#define DEF_CAN_0406_LASER_PUMP1_IN_BOOSTER			             8
#define DEF_CAN_0406_LASER_PUMP2_IN_BOOSTER			             18
#define DEF_CAN_0406_LASER_PUMP3_IN_BOOSTER			             28
#define DEF_CAN_0406_LASER_PUMP_IN_LNA				             38


#define DEF_CAN_0406_RESET							             62

#define DEF_CAN_0406_OPTICAL_POWER_RANGE_BOOSTER	             48
#define DEF_CAN_0406_OPTICAL_POWER_RANGE_LNA		             58



/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	uint8_t ucBoosterEnablePumpLaser1 						: 1;     /* bit 0 (0: disable; 1 enable), default is disabled */
	uint8_t ucBoosterEnablePumpLaser2						: 1;     /* bit 1  (0: disable; 1 enable) */
	uint8_t ucBoosterEnablePumpLaser3	   					: 1;     /* bit 2 - (0: disable; 1 enable)*/
	uint8_t ucLnaEnablePumpLaser4							: 1;     /* bit 3 - (0: disable; 1 enable) */
	uint8_t ucSetBoosterControlMode							: 1;     /* bit 4 - (0: ACC; 1: APC), default is ACC. */
	uint8_t ucSetLnaControlMode		 						: 1;     /* bit 5 - (0: ACC; 1: APC), default is ACC. */
	uint8_t ucSetRxChannelOnLna								: 1;     /* bit 6 - (0: CH30-1553nm; 1: CH51-1536nm), default is CH30-1553nm.*/
	uint8_t ucSetTxChannelOnBooster							: 1;     /* bit 7 - (0: CH30-1553nm; 1: CH51-1536nm), default is CH30-1553nm. */
} Status_406_RegisterBitAssignment_t;

typedef enum{
	RESET_ALL = 0,
	RESET_LNA = 1,
	RESET_BOOSTER = 2,
	DO_NOTHING = 3		
}eResetRequest_t;

typedef union
{
	Status_406_RegisterBitAssignment_t Status_406_RegisterBitAssignment;
	uint8_t							   ucStatus_406_RegisterGlobalValue;
}Status_406_Register_t;

typedef struct
{
	Status_406_Register_t	Status_406_Register;
	float					fSetCurrentOnLaserPump1OnBoosterInAcc;	/* Booster CURRENT control driver 1, Bit 8-17: Value 0 1023 = 0% to 100% */
	float					fSetCurrentOnLaserPump2OnBoosterInAcc;	/* Booster CURRENT control driver 2, Bit 18-27: Value 0 1023 = 0% to 100%*/
	float					fSetCurrentOnLaserPump3OnBoosterInAcc;	/* Booster CURRENT control driver 3, Bit 28-37: Value 0 1023 = 0% to 100%*/
	float					fSetGeneralSetpointOnLNA;				/* Lna CURRENT control, Bit 38-47: Value 0 1023 = 0% to 100%*/
	float					fSetSetPointPowerForBoosterInApc;    /* Set Booster Power in APC mode, Bit 48-57: Value 0 1023 = +16 dBm to 37.5 dBm  */	
//	float					fSetSetPointPowerForLnaInApc;    /* Set LNA Power in APC mode, Bit 58-61: Value 0 15 = -15 dBm to 0 dBm  */	
	eResetRequest_t			ucResetRequest;						/* 0: Reset all (electronics, Booster and LNA) 	1: Reset LNA 	2: Reset booster 	3: do nothing */	
}c406PacketControlDefinition_t;


/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit406CanImage( void );

/**
* @brief		get the 406 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/
eMpbError_t getCan406( CAN_FRAME *pCan);

/**
* @brief		set the 406 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan406( CAN_FRAME *pCan);



/**
* @brief		decode the 406 CAN message and set the image (control message)
* @param[in]	c402Status2Definition_t: pointer to the 406 mesage
* @return       Success or library error message
*/

eMpbError_t eMpbCan406Decode( c406PacketControlDefinition_t *c406PacketControlDefinition );
/**
* @brief		encode the 406 CAN message to be sent (control message)
* @param[in]	c402Status2Definition_t: pointer to the 406 mesage
* @return       Success or library error message
*/

eMpbError_t eMpbCan406Encode( c406PacketControlDefinition_t *c406PacketControlDefinition );



#endif /* CAN406PACKET_H_ */