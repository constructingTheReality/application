/**
* @file			can423Packet.h
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

#ifndef CAN423PACKET_H_
#define CAN423PACKET_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "can.h"
/* Define ------------------------------------------------------------------- */
#define X1_423_28V_MONITOR		( 0.0)
#define Y1_423_28V_MONITOR		( 0.0)
#define X2_423_28V_MONITOR		( 28.0)
#define Y2_423_28V_MONITOR		( 28.0)

#define X1_423_7V_MONITOR		( 0.0)
#define Y1_423_7V_MONITOR		( 0.0)
#define X2_423_7V_MONITOR		( 7.0)
#define Y2_423_7V_MONITOR		( 7.0)

#define X1_423_3V_MONITOR		( 0.0)
#define Y1_423_3V_MONITOR		( 0.0)
#define X2_423_3V_MONITOR		( 3.2)
#define Y2_423_3V_MONITOR		( 3.2)

#define DEF_CAN_423_28V_CURRENT_MONITOR_CH1		            ( 0 )
#define DEF_CAN_423_28V_CURRENT_MONITOR_CH2					( 5 )
#define DEF_CAN_423_28V_VOLTAGE_MONITOR_CH1		            ( 10 )
#define DEF_CAN_423_28V_VOLTAGE_MONITOR_CH2					( 15 )

#define DEF_CAN_423_7V_VOLTAGE_MONITOR_CH1		            ( 20 )
#define DEF_CAN_423_7V_VOLTAGE_MONITOR_CH2					( 25 )

#define DEF_CAN_423_3V_VOLTAGE_MONITOR			            ( 30 )
#define DEF_CAN_423_3_3_VOLTAGE_MONITOR						( 35 )

#define DEF_CAN_423_ADC_VOLTAGE_MONITOR			            ( 40 )

#define DEF_CAN_423_CAN_VOLTAGE_MONITOR1		            ( 45 )
#define DEF_CAN_423_CAN_VOLTAGE_MONITOR2		            ( 50 )


/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

typedef struct
{
	float			f28V_PwrCurrentMonitor_Ch1;		/* ch 0 internal ADC  0..4 0->28V */
	float			f28V_PwrCurrentMonitor_Ch2;		/* ch 1 internal ADC  5..9 0->28V */
	float			f28V_PwrVoltageMonitor_Ch1;		/* ch 2 internal ADC  10..14 0->28V */
	float			f28V_PwrVoltageMonitor_Ch2;		/* ch 3 internal ADC  15.. 19 0->28V */
	float			f7V_PwrVoltageMonitor_Ch1;		/* ch 4 internal ADC  20.. 24 0->7V */
	float			f7V_PwrVoltageMonitor_Ch2;		/* ch 5 internal ADC  25..29 0->7V*/
	float			f3_3V_PwrVoltageMonitor;		/* ch 6 internal ADC  30 to 34 0->3V*/
	float			f3V_ld_PwrVoltageMonitor;		/* ch 7 internal ADC  35 to 39 0->3V*/
	float			fAdcPwrCurrentMonitor;			/* ch 8 internal ADC  40 to 44 0->3V*/
	float			fCanPwrCurrentMonitor1;			/* ch 9 internal ADC  45 to 49 0->3V*/
	float			fCanPwrCurrentMonitor2;			/* ch 10 internal ADC 50.. 54 0->3V*/
	
}c423StatusDefinition_t;



/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

void vInit423CanImage( void );

/**
* @brief		get the 423 CAN message from the image
* @param[in]	pCan pointer to save the info
* @return       Success or library error message
*/

eMpbError_t getCan423( CAN_FRAME *pCan);

/**
* @brief		set the 423 CAN message from the image
* @param[in]	pCan pointer with info
* @return       Success or library error message
*/
eMpbError_t setCan423( CAN_FRAME *pCan);


/**
* @brief		decode the 423 CAN message
* @param[in]	c423StatusDefinition_t: pointer to the 423 mesage
* @return       Success or library error message
*/
eMpbError_t eMpbCan423Decode( c423StatusDefinition_t *c423StatusDefinition );

/**
* @brief		encode the 423 CAN message
* @param[in]	c423StatusDefinition_t: pointer to the 423 mesage
* @param[in]	bBoosterIsDisable: bool
* @param[in]	bLnaIsDisable: bool
* @return       Success or library error message
*/
eMpbError_t eMpbCan423Encode( c423StatusDefinition_t *c423StatusDefinition);



#endif /* CAN423PACKET_H_ */