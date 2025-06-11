/**
  * @file			BSPCan.h
  * @brief    BSP Can header file.
  * @author		juan andres
  * @date			Created on 3/ 4/2023
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB.</center>
  *
  **/
/* Header guard ------------------------------------------------------------- */

#ifndef BSPCAN_H_
#define BSPCAN_H_
/* Includes ----------------------------------------------------------------- */

#include "mpblibs.h"
#include "can.h"
#include "canDictionary.h"
#include "canDispatcher.h"
#include "laserData.h"
/* Define ------------------------------------------------------------------- */
#define NUMBER_OF_FILTERED_MAILBOXES ( 2 )
/**
* @brief        Define the CAN channels.
* @note         CanChannelId               The identifier for the channel.
* @note         Speed        . 
*/

/*	                	        X(	CanChannelId	CAN				Speed	    	 )	*/
#define LIST_OF_CAN_CHANNELS	X(  eCanChannel_0	,CAN0			,CAN_BPS_1000K   )\
								X(	eCanChannel_1	,CAN1			,CAN_BPS_1000K   )
																					
/**
* @brief        Define the CAN mailboxes.
* @note         mailBoxId               The identifier for the mailbox (max 8).
* @note         id						mailbox 6: 0x42x  mask in the last digit .
*/																					
/*	                	        X(	mailBoxId		 id		   interrupt )	*/
#define LIST_OF_RX_MAILBOXES	X(  eMailBox_0		,0x406  ,CAN_IER_MB0 )\
								X(  eMailBox_1		,0x407  ,CAN_IER_MB1 )\
								X(  eMailBox_2		,0x408  ,CAN_IER_MB2 )\
								X(  eMailBox_3		,0x409  ,CAN_IER_MB3 )\
								X(  eMailBox_4		,0x010  ,CAN_IER_MB4 )\
								X(	eMailBox_5		,0x413	,CAN_IER_MB5 )\
								X(	eMailBox_6		,0x420	,CAN_IER_MB6 )
								//X(	eMailBox_7		,0x412	,CAN_IER_MB7 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/**
* @brief	Defines the possible CAN channels.
*/                             
typedef enum
{
#define X( CanChannelId, CAN, Speed )	CanChannelId,
	LIST_OF_CAN_CHANNELS 
#undef X
	eNumberOfCanChannel,
}
eCanChannel_t;   
/**
* @brief	Defines the possible CAN mailboxes.
*/
typedef enum
{
	#define X( mailBoxId, id, interrupt )	mailBoxId,
	LIST_OF_RX_MAILBOXES
	#undef X
	eNumberOfRxMailboxes,
}
eCanMailbox_t;

/* Exported struct ---------------------------------------------------------- */
typedef enum CanSequencer
{
	CAN_MESSAGE_SEQUENCE_INIT = 0,
	CAN_MESSAGE_SEQUENCE_COUNTING = 1,
	CAN_MESSAGE_SEQUENCE_SEND = 2,
	
	
}CanSequencer_t;
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/**
* @brief	Inits and start the CAN.
* @note		.
*/
void vBSPCanInitAndStart( void );

/**
* @brief		Get the result of the ADC.
* @param[in]	eChannel: the channel requested.
* @param[out]	pusReading: The adc reading.
*/
void vBSPCanSend404Continuosly(uint32_t *p408Timer );


#endif /* BSPCAN_H_ */