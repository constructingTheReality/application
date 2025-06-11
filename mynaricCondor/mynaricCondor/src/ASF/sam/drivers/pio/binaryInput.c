/**
* @file 			binaryInput.c
* @brief			binaryInput source file.
* @author			juan andres
* @date			    Created on 3/3/2022
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2022 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ----------------------------------------------------------------- */
#include "binaryInput.h"
#include "glue.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */

/**
* @brief    BinaryInput structure for debouncing definition
*/
/*typedef struct
{
	const uint16_t			usDebounceOn;
	const uint16_t			usDebounceOff;
	const int32_t			slInitialValue;
}xBinaryInputDefinition_t;

*/
/**
* @brief    BinaryOutput structure definition
*/
typedef struct
{
	const int32_t			slInitialValue;
}xBinaryOutputDefinition_t;


/**
* @brief	BinaryInput structure
*/
/**typedef struct
{
	MpbMathDebounce_t	xDebounce;
	eBool_t				bDebounceState;
}xBinaryInput_t;
*/
typedef struct
{	
	eBool_t				bState;
}xBinaryOutput_t;

/* Private variables -------------------------------------------------------- */

/*static const xBinaryInputDefinition_t xBinaryInputDefinition[] =
{
	#define X( EnumId, DebounceOnCount, DebounceOffCount, InitialValue ) { .usDebounceOn = DebounceOnCount, .usDebounceOff =  DebounceOffCount, .slInitialValue = InitialValue },
	INPUT_BINARY_ACDC
	#undef X
};*/

//static xBinaryInput_t	xBinaryInput[ eNumOfDigitalInput ];


static const xBinaryOutputDefinition_t xBinaryOutputDefinition[] =
{
	#define X( EnumId, InitialValue ) { .slInitialValue = InitialValue },
	OUTPUT_BINARY_DCC
	#undef X
};

static xBinaryOutput_t	xBinaryOutput[ eNumOfDigitalOutput ];
//static eDigitalOutputId_t	xBinaryOutput[ eNumOfDigitalOutput ];

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/**
* @brief		Read the digital input
* @param[in]	eDigitalInput: the digital input ID
* @param[out]	pbState: the state of the digital input
*/
//static void vprvBinaryInputRead( eDigitalInputId_t eDigitalInput, eBool_t *pbState );

/**
* @brief		Set the digital output
* @param[in]	eDigitalOutput: the digital output ID
* @param[out]	bState: the state of the digital output
*/
static void vprvBinaryOutputSet( eDigitalOutputId_t eDigitalOutput, eBool_t bState );

static eBool_t bSemaphore= eFalse;

/* Private functions -------------------------------------------------------- */
static void vprvBinaryOutputSet( eDigitalOutputId_t eDigitalOutput, eBool_t bState )
{
	switch( eDigitalOutput )
	{
		case eOutputLnaLddEna:
		{
			eMpblibsBinaryWrite( eHandleLnaLddEna, bState );
		}
		break;
		case eOutputHpaSmLddEna:
		{
			eMpblibsBinaryWrite( eHandleHpaSmLddEna, bState );
		}
		break;
		
		case eOutputHpaMmLddEna1:
		{
			eMpblibsBinaryWrite( eHandleHpaMmLddEna1, bState );
		}
		break;
		
		case eOutputHpaMmLddEna2:
		{
			eMpblibsBinaryWrite( eHandleHpaMmLddEna2, bState );
		}
		break;		
				
		case eOutputFramPwrEna:
		{
			eMpblibsBinaryWrite( eHandleFramPwrEna, bState );
		}
		break;
		
		case eOutputFramWp:
		{
				eMpblibsBinaryWrite( eHandleFramWp, bState );
		}
		break;
		
		
		case eOutput28vPwrDis1:
		{
			eMpblibsBinaryWrite( eHandle28vPwrDis1, bState );
		}
		break;

		case eOutput3vPwrEna1:
		{
			eMpblibsBinaryWrite( eHandle3vPwrEna1, bState );
		}
		break;
				
		case eOutput3vPwrEna2:
		{
			eMpblibsBinaryWrite( eHandle3vPwrEna2, bState );
		}
		break;
		
		case eOutput28vPwrDis2:
		{
			eMpblibsBinaryWrite( eHandle28vPwrDis2, bState );
		}
		break;
		case eOutputAdcPwrEna:
		{
			eMpblibsBinaryWrite( eHandleAdcPwrEna, bState );
		}
		break;
		case eOutputCanPwrEna1:
		{
			eMpblibsBinaryWrite( eHandleCanPwrEna1, bState );
		}
		break;
		case eOutputCanPwrEna2:
		{
			eMpblibsBinaryWrite( eHandleCanPwrEna2, bState );
		}
		break;
		
		
		case eOutputAdcCs0:
		{
			eMpblibsBinaryWrite( eHandleAdcCs0, bState );
		}
		break;
				
				
		case eOutputAdcCs1:
		{
			eMpblibsBinaryWrite( eHandleAdcCs1, bState );
		}
		break;
						
						
		case eOutputAdcCs2:
		{
			eMpblibsBinaryWrite( eHandleAdcCs2, bState );
		}
		break;
		
		case eOutputFramCs:
		{
			eMpblibsBinaryWrite( eHandleFramCs, bState );
		}
		break;
				
		
		default:
		{
			vMpblibsAssertParam( 0 );
		}
		break;
	}
}
/*-------------------------------------------------------------------------------*/

/*static void vprvBinaryInputRead( eDigitalInputId_t eDigitalInput, eBool_t *pbState )
{

	switch( eDigitalInput )
	{
		case eInputVctrlStatMon:
		{
			eMpblibsBinaryRead( eHandleVctrlStatMon, pbState );
		}
		break;
		case eInputDrvPwrStatus:
		{
			eMpblibsBinaryRead( eHandleDrvPwrStatus, pbState );
		}
		break;
		case eInputNadcFault:
		{
			eMpblibsBinaryRead( eHandleNadcFault, pbState );
		}
		break;
		
		case eInputNtrx2Fault:
		{
			eMpblibsBinaryRead( eHandleNtrx2Fault, pbState );
		}
		break;
		
		case eInputNtrx1Fault:
		{
			eMpblibsBinaryRead( eHandleNtrx1Fault, pbState );
		}
		break;
		
		case eInputNpMem2Fault:
		{
			eMpblibsBinaryRead( eHandleNpMem2Fault, pbState );
		}
		break;
		
		case eInputNpMem1Fault:
		{
			eMpblibsBinaryRead( eHandleNpMem1Fault, pbState );
		}
		break;
		
		case eInputNbMemFault:
		{
			eMpblibsBinaryRead( eHandleNbMemFault, pbState );
		}
		break;
		
		case eInputExtAdcFault:
		{
			eMpblibsBinaryRead( eHandleExtAdcFault, pbState );
		}
		break;
		
		
		case eInputCtrlId:
		{
			eMpblibsBinaryRead( eHandleCtrlId, pbState );
		}
		break;
		
		case eInputRev0:
		{
			eMpblibsBinaryRead( eHandleRev0, pbState );
		}
		break;
		case eInputRev1:
		{
			eMpblibsBinaryRead( eHandleRev1, pbState );
		}
		break;
		
		
		
		default:
		{
			vMpblibsAssertParam( 0 );
		}
		break;
	}
	
	
}*/

/* Exported functions ------------------------------------------------------- */
/*void vBinaryOutInit( void )
{
	for( eDigitalOutputId_t eDigitalOutput = ( eDigitalOutputId_t ) 0; eDigitalOutput < eNumOfDigitalOutput; eDigitalOutput++ )
	{
		xBinaryOutput[ eDigitalOutput ].bState = xBinaryOutputDefinition[eDigitalOutput].slInitialValue;

		vBinaryOtputSetState(  eDigitalOutput, xBinaryOutput[ eDigitalOutput ].bState);
		//vMpbMathDebounceInit( &xBinaryInput[ eDigitalInput ].xDebounce, xBinaryInputDefinition[ eDigitalInput ].usDebounceOn, xBinaryInputDefinition[ eDigitalInput ].usDebounceOff, xBinaryInputDefinition[ eDigitalInput ].slInitialValue );
	}



}*/

/*void vBinaryInputInit( void )
{
	for( eDigitalInputId_t eDigitalInput = ( eDigitalInputId_t ) 0; eDigitalInput < eNumOfDigitalInput; eDigitalInput++ )
	{
		vMpbMathDebounceInit( &xBinaryInput[ eDigitalInput ].xDebounce, xBinaryInputDefinition[ eDigitalInput ].usDebounceOn, xBinaryInputDefinition[ eDigitalInput ].usDebounceOff, xBinaryInputDefinition[ eDigitalInput ].slInitialValue );
	}
}*/
/*----------------------------------------------------------------------------*/

/*void vBinaryInputGetState( eDigitalInputId_t eDigitalInput, eBool_t *pbState )
{
	*pbState = xBinaryInput[ eDigitalInput ].bDebounceState;
}*/
/*----------------------------------------------------------------------------*/

/*void vBinaryInputISR( void )
{
	eBool_t bState;
	eBool_t mybDebounceState;
	
	for( eDigitalInputId_t eDigitalInput = ( eDigitalInputId_t ) 0; eDigitalInput < eNumOfDigitalInput; eDigitalInput++ )
	{
		vprvBinaryInputRead( eDigitalInput, &bState );
		
		vMpbMathDebounceUpdate( &( xBinaryInput[ eDigitalInput ].xDebounce ), bState, &mybDebounceState );
		
		xBinaryInput[ eDigitalInput ].bDebounceState =  mybDebounceState;
	}
}*/
/*----------------------------------------------------------------------------*/

void vBinaryOtputSetState( eDigitalOutputId_t eDigitalOutput, eBool_t bState )
{

		vprvBinaryOutputSet( eDigitalOutput, bState );
		
	
	
	
	
}


void vBinarySetLdEnable( eBool_t bState )
{
	if(bSemaphore == eFalse)
	{
		bSemaphore = eTrue;
		vBinaryOtputSetState( eOutputLnaLddEna , !bState );
		bSemaphore = eFalse;
	}
//	eMpblibsBinaryWrite( eHandleLnaLddEna, eFalse );
}


eBool_t bGetSemaphore(void)
{
	
	return bSemaphore;
}

/*------------------------------*/
