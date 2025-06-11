/**
  * @file 			BSPCan.c
  * @brief			BSPcan source file.
  * @author			juan andres
  * @date			Created on 3/3/2023
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB.</center>
  *
  **/
  
/* Includes ----------------------------------------------------------------- */

#include "BSPCan.h"
#include "glue.h"
#include "sysclk.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* Private define ----------------------------------------------------------- */
#define CAN_NUMBER_CHANNEL						( eNumberOfCanChannel )
#define CAN_RX_MAILBOX_NUMBER					( eNumberOfRxMailboxes )
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
static CanSequencer_t xCanSequencer404;
static eBool_t b404Sent = eFalse;
/* Private variables -------------------------------------------------------- */
static const uint32_t ulCanChannelsId[ CAN_NUMBER_CHANNEL ] =
{
	#define X( CanChannelId, CAN, Speed  )	CanChannelId,
	LIST_OF_CAN_CHANNELS
	#undef X
};
static const Can* ulCanModule[ CAN_NUMBER_CHANNEL ] =
{
	#define X( CanChannelId, CAN, Speed  )	CAN,
	LIST_OF_CAN_CHANNELS
	#undef X
};
static const uint32_t ulCanSpeeds[ CAN_NUMBER_CHANNEL ] =
{
	#define X( CanChannelId, CAN, Speed  )	Speed,
	LIST_OF_CAN_CHANNELS
	#undef X
};

static const uint32_t ulCanMailboxId[ CAN_RX_MAILBOX_NUMBER ] =
{
	#define X( mailBoxId, id, interrupt  )	id,
	LIST_OF_RX_MAILBOXES
	#undef X
};
static const uint32_t ulCanMailboxInterrupt[ CAN_RX_MAILBOX_NUMBER ] =
{
	#define X( mailBoxId, id, interrupt  )	interrupt,
	LIST_OF_RX_MAILBOXES
	#undef X
};
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

static void vSetCanMyPort(CAN_FRAME *frame)
{
	if(frame->id == 0x010)
	{
		if( frame->data.byte[0] == 0x80 )
		{
			vSetCanPort1( eTrue );
		}
		else
		{
			vSetCanPort1( eFalse );
		}
	}
}
/*----------------------------------------------------------------------------*/
static void vRxCan0_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMynaricMessages( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_0_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB0( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_1_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB1( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_2_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB2( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_3_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB3( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_4_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB4( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_5_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB5( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_6_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMessagesMB6( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCanMB_7_Callback(CAN_FRAME *frame)
{
//	vCanDispatcherMessagesMB7( frame );
}
/*----------------------------------------------------------------------------*/
static void vRxCan1_Callback(CAN_FRAME *frame)
{
	vCanDispatcherMynaricMessages( frame );
}

/*----------------------------------------------------------------------------*/
static void vRxCanPort0_Callback(CAN_FRAME *frame)
{
	vSetCanMyPort( frame);	
}
/*----------------------------------------------------------------------------*/
static void vRxCanPort1_Callback(CAN_FRAME *frame)
{
	vSetCanMyPort( frame);
}
/*----------------------------------------------------------------------------*/
void CAN1_Handler(void)
{
	vInterruptHandler(CAN1);
}
/*----------------------------------------------------------------------------*/

void CAN0_Handler(void)
{
	//tiemStamp= get_timestamp_value(CAN0);
	vInterruptHandler(CAN0);
}

/*----------------------------------------------------------------------------*/
void vBSPCanInitAndStart( void )
{	
	uint32_t ul_sysclk;
	ul_sysclk = sysclk_get_cpu_hz();
	
	for( uint8_t ucI = 0; ucI < CAN_NUMBER_CHANNEL; ucI++ )
	{		
		can_init( ulCanModule[ucI], ul_sysclk, ulCanSpeeds[ucI] );
		can_disable_interrupt(ulCanModule[ucI], CAN_DISABLE_ALL_INTERRUPT_MASK);
		reset_all_mailbox(ulCanModule[ucI]);		
	}

	for( uint8_t ucI = 0; ucI < (CAN_RX_MAILBOX_NUMBER- NUMBER_OF_FILTERED_MAILBOXES ); ucI++ )
	{
		for( uint8_t ucJ = 0; ucJ < CAN_NUMBER_CHANNEL; ucJ++ )
		{
			mailbox_set_id( ulCanModule[ucJ], ucI, ulCanMailboxId[ucI], false) ;
			mailbox_set_mode(ulCanModule[ucJ], ucI, CAN_MB_RX_MODE);			
			can_enable_interrupt(ulCanModule[ucJ], ulCanMailboxInterrupt[ucI] );
		//	can_enable_interrupt(ulCanModule[ucJ], CAN_IER_WARN);  // Warning Limit 
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_BOFF);  // Bus Off
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_ERRA);   //Error Active
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_ERRP);   //Error Pasive
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_CERR);   //5. CRC Error Rx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_SERR);  //2. Stuffing Error Rx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_FERR);  //3. Form Error Rx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_BERR);  //1. Bit Error Tx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_AERR);	//4. Acknowledgment Error  Tx
			mailbox_set_accept_mask(ulCanModule[ucJ], ucI, 0x7ff, false); //7ff 111 1111 1111 ->no filtering, should match exact the id mailbox			
		}
		
	}

	for( uint8_t ucI = (CAN_RX_MAILBOX_NUMBER- NUMBER_OF_FILTERED_MAILBOXES ); ucI < (CAN_RX_MAILBOX_NUMBER); ucI++ )
	{
		for( uint8_t ucJ = 0; ucJ < CAN_NUMBER_CHANNEL; ucJ++ )
		{
			mailbox_set_id( ulCanModule[ucJ], ucI, ulCanMailboxId[ucI], false) ;
			mailbox_set_mode(ulCanModule[ucJ], ucI, CAN_MB_RX_MODE);			
			can_enable_interrupt(ulCanModule[ucJ], ulCanMailboxInterrupt[ucI] );		
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_BOFF);  // Bus Off
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_ERRA);   //Error Active
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_ERRP);   //Error Pasive
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_CERR);   //5. CRC Error Rx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_SERR);  //2. Stuffing Error Rx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_FERR);  //3. Form Error Rx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_BERR);  //1. Bit Error Tx
			can_enable_interrupt(ulCanModule[ucJ], CAN_IER_AERR);	//4. Acknowledgment Error  Tx
			mailbox_set_accept_mask(ulCanModule[ucJ], ucI, 0x7f0, false); //7ff 111 1111 0 -> filtering 41x, should match exact the id mailbox mb5		 ADN 42X FOR mb6	
		}
		
	}
	

	/*setting a callback for each mailbox */
	setCallback( eMailBox_0, vRxCanMB_0_Callback);
	setCallback( eMailBox_1, vRxCanMB_1_Callback);
	setCallback( eMailBox_2, vRxCanMB_2_Callback);
	setCallback( eMailBox_3, vRxCanMB_3_Callback);
	setCallback( eMailBox_4, vRxCanMB_4_Callback);
	setCallback( eMailBox_5, vRxCanMB_5_Callback);
	setCallback( eMailBox_6, vRxCanMB_6_Callback);
//	setCallback( eMailBox_7, vRxCanMB_7_Callback);
			
	
	vInitCanImage();

	NVIC_EnableIRQ(CAN0_IRQn);
	NVIC_EnableIRQ(CAN1_IRQn);
}
/*----------------------------------------------------------------------------*/
void vBSPCanSend404Continuosly(uint32_t *p408Timer )
{
		if(xCanSequencer404 == CAN_MESSAGE_SEQUENCE_INIT)
		{
			if( b404Sent == eFalse )
			{
				*p408Timer = 0;				
				xCanSequencer404 = CAN_MESSAGE_SEQUENCE_COUNTING;				
			}
			
			
		}
		else if( xCanSequencer404 == CAN_MESSAGE_SEQUENCE_COUNTING)
		{
			if( b404Sent == eTrue )
			{
				xCanSequencer404 = CAN_MESSAGE_SEQUENCE_INIT	;
			}
			
			if(*p408Timer == 500)
			{
				xCanSequencer404 = CAN_MESSAGE_SEQUENCE_SEND;	
			}
			
		}else
		{
			
			xCanSequencer404 = CAN_MESSAGE_SEQUENCE_SEND;	
		}
	
}
/*----------------------------------------------------------------------------*/