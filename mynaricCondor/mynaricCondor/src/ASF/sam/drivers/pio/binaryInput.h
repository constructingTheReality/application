 /**
 * @file		    binaryInput.h
 * @brief        binaryInput header file.
 * @author		juan
 * @date			Created on 2022-3-2
 * @copyright MPB, Montreal, Qc
 * <h2><center>&copy; COPYRIGHT 2022 MPB, Montreal, Quebec, Canada</center></h2>
 * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
 * <center>This document contains confidential and proprietary information
 * of MPB (subject to a non-disclosure agreement) and shall</center>
 * <center>not be disclosed, distributed, or reproduced in whole or in
 * part, without the prior written authorization of MPB.</center>
 *
 **/
 /* Header guard ------------------------------------------------------------- */
 #ifndef __BINARYINPUT_H
 #define __BINARYINPUT_H
 /* Includes ----------------------------------------------------------------- */
 #include "mpblibs.h"
 /* Define ------------------------------------------------------------------- */
 /*                                              Debounce    		Debounce			Initial 		)*/
 /*                     EnumId,        	  	   	OnCount(ms), 	    OffCount(ms)    	Value 			 */
 /*#define INPUT_BINARY_ACDC	X( eInputNtrx2Fault, 	    50, 		    		50,						1			)\
								X( eInputNtrx1Fault, 	    50, 		    		50,						1			)\
								X( eInputNpMem2Fault,	    50, 		    		50,						1			)\
								X( eInputNpMem1Fault,	    50, 		    		50,						1			)\
								X( eInputNbMemFault, 	    50, 		    		50,						1			)\
								X( eInputExtAdcFault,	    50, 		    		50,						1			)\
								X( eInputVctrlStatMon, 		50,   				  50, 					1			)\
								X( eInputDrvPwrStatus,		50, 	    			50, 					1			)\
								X( eInputNadcFault, 	    50, 		    		50,						1			)\
								X( eInputCtrlId,    	    50, 		    		50,						1			)\
								X( eInputRev0,			 	    50, 		    		50,						1			)\
								X( eInputRev1,			 	    50, 		    		50,						1			)
 */
 
 #define OUTPUT_BINARY_DCC	X( eOutputLnaLddEna,		1			)\
							X( eOutputHpaSmLddEna ,	    1			)\
							X( eOutputHpaMmLddEna1,	    1			)\
							X( eOutputHpaMmLddEna2,	    1			)\
							X( eOutputFramPwrEna, 		1			)\
							X( eOutputFramWp,	 		1			)\
							X( eOutput28vPwrDis1,		1			)\
							X( eOutput28vPwrDis2,  	    1			)\
							X( eOutput3vPwrEna1,		1			)\
							X( eOutput3vPwrEna2,		1			)\
							X( eOutputAdcPwrEna,   	    1			)\
							X( eOutputCanPwrEna1,  	    1			)\
							X( eOutputCanPwrEna2,  	    1			)\
							X( eOutputAdcCs0,  			1			)\
							X( eOutputFramCs,  		    1			)\
							X( eOutputAdcCs1,  		    1			)\
							X( eOutputAdcCs2,	  	    1			)
 
 /* Exported macro ----------------------------------------------------------- */
 /* Exported enum ------------------------------------------------------------ */
 /**
 * @brief	Contains the list of all the binaryInputs
 */
 /*typedef enum
 {
	 #define X( EnumId, DebounceOnCount, DebounceOffCount, InitialValue )	EnumId,
	 INPUT_BINARY_ACDC
	 #undef X
	 eNumOfDigitalInput,
 }
 eDigitalInputId_t;*/

 /**
 * @brief	Contains the list of all the binaryInputs
 */
 typedef enum
 {
	 #define X( EnumId, InitialValue )	EnumId,
	 OUTPUT_BINARY_DCC
	 #undef X
	 eNumOfDigitalOutput,
 }
 eDigitalOutputId_t;

 /* Exported struct ---------------------------------------------------------- */
 /* Global variables --------------------------------------------------------- */
 /* Exported function prototypes --------------------------------------------- */

 /**
 * @brief		Initialize the binary inputs
 */
 //void vBinaryInputInit( void );

 /**
 * @brief		Get the state of the binary input
 * @param[in]	eDigitalInput: the digital input identifier
 * @param[out]	pbState: the debouce state of the digital input
 */
 //void vBinaryInputGetState( eDigitalInputId_t eDigitalInput, eBool_t *pbState );

 /**
 * @brief		Interrupt to update the binary input debouce
 * @note			This is not a real interupt, this function is manually called in the systick handler
 */
 //void vBinaryInputISR( void );

 /**
 * @brief			Set the state of the binary output
 * @param[in]	eDigitalOutput: the digital output identifier
 * @param[out]	bState: the out state of the digital ouput
 */
 //void vBinaryOutInit( void );
 void vBinaryOtputSetState( eDigitalOutputId_t eDigitalOutput, eBool_t bState );
 

 void vBinarySetLdEnable( eBool_t bState );


eBool_t bGetSemaphore(void);


 #endif /* __BINARYINPUT_H */
