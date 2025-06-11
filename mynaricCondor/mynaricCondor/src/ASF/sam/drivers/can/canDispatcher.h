/**
* @file			canDispatcher.h
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


#ifndef CANDISPATCHER_H_
#define CANDISPATCHER_H_

/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "canDictionary.h"
/* Define ------------------------------------------------------------------- */
#define DEF_FACTORY_INDEX_RESET					   ( 0 )
#define DEF_FACTORY_INDEX_LNA_PROPORTIONAL		   ( 1 )
#define DEF_FACTORY_INDEX_LNA_INTEGRAL			   ( 2 )
#define DEF_FACTORY_INDEX_LNA_DERIVATIVE		   ( 3 )
#define DEF_COMMAND_40A_ADC12VPWR_CM_CH1_SLOPE     ( 4 )
#define DEF_COMMAND_40A_ADC12VPWR_CM_CH1_INTERCEPT ( 5 )
#define DEF_FACTORY_INDEX_LOG					   ( 6 )
#define  DEF_COMMAND_40A_ADC12VPWR_CM_CH2_SLOPE		   ( 7 )
#define  DEF_COMMAND_40A_ADC12VPWR_CM_CH2_INTERCEPT	   ( 8 )
#define  DEF_READ_INTERNAL_ADC						   ( 9 )
#define  DEF_READ_CAN_STATUS						   ( 10 )

#define  DEF_CHANNEL_0   ( 0 )
#define  DEF_CHANNEL_1   ( 1 )
#define  DEF_CHANNEL_2   ( 2 )
#define  DEF_CHANNEL_3   ( 3 )
#define  DEF_CHANNEL_4   ( 4 )
#define  DEF_CHANNEL_5   ( 5 )
#define  DEF_CHANNEL_6   ( 6 )
#define  DEF_CHANNEL_7   ( 7 )
#define  DEF_CHANNEL_8   ( 8 )
#define  DEF_CHANNEL_9   ( 9 )
#define  DEF_CHANNEL_10   ( 10 )
#define  DEF_CHANNEL_11   ( 11 )
#define  DEF_CHANNEL_12   ( 12 )

#define TEMPERATURE_LNA_TH  ( 24 )

#define TEMPERATURE_HPA_SM_TH ( 25)
#define TEMPERATURE_HPA_MM_1_TH ( 26 )
#define TEMPERATURE_HPA_MM_2_TH ( 27 )

#define TEMPERATURE_HPA_MM_3_TH ( 28 )
#define TEMPERATURE_HPA_MM_4_TH ( 29 )
 //#define TEMPERATURE_CASE_TH  ( 30 )
 
#define LNA_INPUT_POWER_MW ( 30 ) 
#define LNA_OUTPUT_POWER_MW ( 31 ) 
#define LNA_SP_IND_DBM ( 32 ) 
#define HPA_SM_BACKFACET_IN_MA ( 33 ) 

#define HPA_OUTPUT_MONITOR_LH_IN_MW ( 34 ) 
#define HPA_OUTPUT_MONITOR_HH_IN_MW ( 35 ) 

	 

#define  DEF_DELAY_SEQUENCE_A   ( 6 )//12
#define  DEF_DELAY_SEQUENCE_B   ( 1 )//2
#define  DEF_DELAY_2_MS   ( 1 )

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
typedef enum eSequenceA
{
	eSequenceAInit = 0,		 
	eSequenceA401 = 1,
	eSequenceA402 = 2,
	eSequenceA414 = 3,
	eSequenceA414a = 4,
	
}eSequenceA_t;

typedef enum eSequenceB
{
	
	eSequenceBInit = 0,
	eSequenceB403 = 1,
	eSequenceB404 = 2,
	eSequenceB405 = 3,
	eSequenceB40A = 4,
	eSequenceB415 = 5,
	eSequenceB411 = 6,
	eSequenceB423 = 7
	
}eSequenceB_t;

typedef union
{
		float	 fValue;
		uint16_t usValue[2];
		uint8_t ucValue[4];
}MyCANData_t;
	
	
typedef union
{
	float fValue;
	uint8_t ucValue[4];
}MyConversionData_t;

/**
  * @brief      Sequence the CAN messages 401,402,403,404 and 405 in loop 
  * @param[in]  none.
  */
void vCanDispatcherSequence(void);
/**
  * @brief      Determines the CAN port and sends data 
  * @param[in]  CAN_FRAME: can data  
  */
void vCanDispatcherSendCanMessage( CAN_FRAME *pCan );

void vCanDispatcherSendFactoryCanMessage( CAN_FRAME *pCan );
/**
  * @brief      dispatch a CAN messages depending of the CAN input message .
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMynaricMessages( CAN_FRAME *frame );

/**
  * @brief      answer the 401 message , beacuase MB0 = 406 
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB0( CAN_FRAME *frame );

/**
  * @brief      answer the 402 message , beacuase MB1 = 407 
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB1( CAN_FRAME *frame );

/**
  * @brief      answer the 403 message , beacuase MB2 = 408 
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB2( CAN_FRAME *frame );
/**
  * @brief      answer the 404 message , beacuase MB3 = 409 
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB3( CAN_FRAME *frame );

/**
  * @brief      no answer , beacuase MB4 = 10 
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB4( CAN_FRAME *frame );

/**
  * @brief      answer the 405 message , beacuase M53 = 40A 
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB5( CAN_FRAME *frame );

/**
  * @brief      answer the 42x message ,
  * @param[in]  CAN frame : input message.  
  */
void vCanDispatcherMessagesMB6( CAN_FRAME *frame );

/**
  * @brief      answer the 407 message ,
  * @param[in]  CAN frame : input message.  
  */
//void vCanDispatcherMessagesMB7( CAN_FRAME *frame );

void vSendFactory(void);
#endif /* CANDISPATCHER_H_ */