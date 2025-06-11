/**
* @file 		enableControlaser.c
* @brief		enableControlaser.c source file
* @author		juan andres
* @date			Created on 2021-03-11
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "enableControl.h"
#include "glue.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
//static eAccLaserState_t eAccLaserState = eInitAccDetection;
/* Private function prototypes ---------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
/**
* @brief        Initalization of laser.
*/
void vControlLinesLaserInit( void )
{
 vBinaryOtputSetState( eOutputLnaLddEna, eTrue );
 vBinaryOtputSetState( eOutputLnaLddEna, eFalse );
 vBinaryOtputSetState( eOutputLnaLddEna, eTrue );
 //vBinaryOtputSetState( eOutputHpaSmLddEna, eTrue );
 //vBinaryOtputSetState( eOutputHpaMmLddEna1, eTrue );
 //vBinaryOtputSetState( eOutputHpaMmLddEna2, eTrue );
 
}

/*----------------------------------------------------------------------------*/
void vControlLinesLaserUpdateLna( void )
{
	c406PacketControlDefinition_t *pc406PacketControlDefinition;
	pc406PacketControlDefinition = vLaserDataGetData406();
	
	//c402StatusDefinition_t	*pc402StatusDefinition;
	//pc402StatusDefinition = vLaserDataGetData402();
	
	eBool_t bEnable1 = eFalse;

	bEnable1 = (eBool_t)(pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4);

	vBinaryOtputSetState( eOutputLnaLddEna, !bEnable1 );
	
}

void vControlLinesLaserUpdateHpa( void )
{
	c406PacketControlDefinition_t *pc406PacketControlDefinition;
	pc406PacketControlDefinition = vLaserDataGetData406();
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor;
	pxAmplifierDescriptor = vGetxAmplifierDescriptor( );
	
	
	eBool_t bEnable2 = eFalse;
	eBool_t bEnable3 = eFalse;
	eBool_t bEnable4 = eFalse;
	eBool_t bEnable5 = eFalse;
	eBool_t bEnable6 = eFalse;

	
	bEnable2 = (eBool_t)(pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1);
	bEnable3 = (eBool_t)(pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2);
	bEnable4 = (eBool_t)(pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3);
	
	/*if( pxAmplifierDescriptor->c402StatusDefinition.xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bInternalCriticalErrorFlag == 1 )			
	{
		vBinaryOtputSetState( eOutputHpaSmLddEna, eTrue ); // sm is off in eTrue (inversed logic)
		vBinaryOtputSetState( eOutputHpaMmLddEna1, eFalse );
		vBinaryOtputSetState( eOutputHpaMmLddEna2, eFalse );
		
	}
	else
	{*/
						
	
		vBinaryOtputSetState( eOutputHpaSmLddEna, !bEnable2 );
		vBinaryOtputSetState( eOutputHpaMmLddEna1, bEnable3 );
		vBinaryOtputSetState( eOutputHpaMmLddEna2, bEnable4 );
	//}
	
}


/*---------------------------------------------------------------------*/
