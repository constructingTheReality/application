/**
  * @file 			BSPAdc.c
  * @brief			BSPAdc source file.
  * @author			juan andres
  * @date			Created on 3/4/2023
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

#include "BSPAdc.h"
//#include "BSPSpi.h"
#include "glue.h"
#include "mpbDigitalFiltering.h"
#include "CurrentOutput.h"
#include "binaryInput.h"
#include "adc108s102.h"
/* Private define ----------------------------------------------------------- */

/* We add 2 bits of resolution whit oversampling */
#define ADC_NUMBER_CHANNEL						( eNumberOfInternalAdcChannel )
#define ADC_EXTERNAL_NUMBER_CHANNEL				( eNumberOfExternalAdcChannel )


//#define BUFFER_SIZE     NUM_CHANNELS * eNumberOfAdcChannel

#define ADC_ACCUMULATOR_OVERSAMPLING 		( 16 )	/* ( 4^2 )  move from 12 bits to 14 bits */
#define ADC_ACCUMULATOR_DIVIDER					( 4 )	/* ( 2^2 ) */

/* ADC informations */
#define ADC_SAMPLES_PER_CHANNEL					( 1 )
#define ADC_NUM_OF_SEQ									( ADC_ACCUMULATOR_OVERSAMPLING / ADC_SAMPLES_PER_CHANNEL )
#define ADC_DAT_ACQUISTION_PER_SEQUENCE					( ADC_SAMPLES_PER_CHANNEL * ADC_NUMBER_CHANNEL )
#define ADC_EX_DAT_ACQUISTION_PER_SEQUENCE				( ADC_SAMPLES_PER_CHANNEL * ADC_EXTERNAL_NUMBER_CHANNEL )

/* Filter init info */
#define ADC_CLOCK												( ADC_CLK ) 
#define ADC_TIME_CONVERSION_MS					( ( 1000 * ( 1.5 + 12.5 ) ) / ADC_CLOCK ) /* See design document, no define available */
#define ADC_SAMPLING_PERIOD							( uint32_t ) (  ADC_TIME_CONVERSION_MS * ADC_DAT_ACQUISTION_PER_SEQUENCE * ADC_NUM_OF_SEQ ) /* 0.093 ms */
#define ADC_USE_NMS_FILTER							( 0 )	/* 0: No NMS filter, 1: NMS Filter Enable */
#define ADC_USE_RCLP_FILTER							( 1 )	/* 0: No RCLP filter, 1: RCLP Filter Enable */

#define ADC_CALIBRATION_DELAY           ( 1 ) /* ms */

#define FILTER_IS_NEEDED           ( 0 ) /* ms */

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */




#if ( ADC_USE_RCLP_FILTER )

#endif

#if ( ADC_USE_NMS_FILTER )
static xMpbDigitalFilteringNmsFilter_t xprvAdcNmsFilter[ ADC_NUMBER_CHANNEL ];
static xMpbDigitalFilteringNmsFilter_t xprvAdcExternalNmsFilter[ ADC_EXTERNAL_NUMBER_CHANNEL ];
#endif

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

#if ( ADC_USE_RCLP_FILTER )

static xMpbDigitalFilteringRclpFilter_t xprvAdcRclpFilter[ ADC_NUMBER_CHANNEL ];
static xMpbDigitalFilteringRclpFilter_t xprvExternalAdcRclpFilter[ ADC_EXTERNAL_NUMBER_CHANNEL ];

static const uint32_t ulAdcRCLPFilterConstant[ ADC_NUMBER_CHANNEL ] =
{   
#define X( AdcChannelId, RCLPFilterConstant )	RCLPFilterConstant,
        LIST_OF_ADC_CHANNELS 
#undef X
};

static const uint32_t ulExternalAdcRCLPFilterConstant[ ADC_EXTERNAL_NUMBER_CHANNEL ] =
{   
#define X( AdcChannelId, RCLPFilterConstant )	RCLPFilterConstant,
        LIST_OF_EXTERNAL_ADC_CHANNELS 
#undef X
};

#endif


static uint16_t usprvAdcSampleResult[ ADC_DAT_ACQUISTION_PER_SEQUENCE ];
static uint16_t usprvAdcAccumulator[ ADC_NUMBER_CHANNEL ];
static uint16_t usprvAdcResult[ ADC_NUMBER_CHANNEL ];

static uint16_t usprvExternalAdcSampleResult[ ADC_EX_DAT_ACQUISTION_PER_SEQUENCE ];
static uint16_t usprvExternalAdcAccumulator[ ADC_EXTERNAL_NUMBER_CHANNEL ];
static uint16_t usprvExternalAdcResult[ ADC_EXTERNAL_NUMBER_CHANNEL ];

static uint16_t usprvExternalAdcRawResult[ ADC_EXTERNAL_NUMBER_CHANNEL ];



#if ( ADC_USE_NMS_FILTER )
static void vprvBSPAdcInitNmsFilter( void );
#endif

/* Private functions -------------------------------------------------------- */

#if ( ADC_USE_RCLP_FILTER )
static void vprvBSPAdcInitRclpFilter( void )
{
	eMpbError_t eMpbError;
	uint32_t ulSamplingPeriod;
	
	/* Protect against period smaller than 1ms */
	ulSamplingPeriod = ( ADC_SAMPLING_PERIOD > 0 ) ? ADC_SAMPLING_PERIOD : 1;
	
	/* Init filter */
	for( uint8_t ucI = 0; ucI < ADC_NUMBER_CHANNEL; ucI++ )
	{
		eMpbError = eMpbDigitalFilteringRclpInit( &xprvAdcRclpFilter[ ucI ], ulAdcRCLPFilterConstant[ ucI ], ulSamplingPeriod );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
	}
	

	for( uint8_t ucI = 0; ucI < ADC_EXTERNAL_NUMBER_CHANNEL; ucI++ )
	{
		eMpbError = eMpbDigitalFilteringRclpInit( &xprvExternalAdcRclpFilter[ ucI ], ulExternalAdcRCLPFilterConstant[ ucI ], ulSamplingPeriod );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
	}
	
}
#endif
/*----------------------------------------------------------------------------*/

#if ( ADC_USE_NMS_FILTER )
static void vprvBSPAdcInitNmsFilter( void )
{
	eMpbError_t eMpbError;
	for( uint8_t ucI = 0; ucI < ADC_NUMBER_CHANNEL; ucI++ )
	{
		eMpbError = eMpbDigitalFilteringNmsInit( &prv_xAdcNmsFilter[ ucI ] );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
	}
	
	for( uint8_t ucI = 0; ucI < ADC_EXTERNAL_NUMBER_CHANNEL; ucI++ )
	{
		eMpbError = eMpbDigitalFilteringNmsInit( &xprvAdcExternalNmsFilter[ ucI ] );
		if( eMpbError != eSuccess )
		{
			vMpblibsAssertParam( 0 );
		}
	}
	
}
#endif


/* Exported functions ------------------------------------------------------- */

void vBSPAdcInitAndStart( void )
{	
	
	  HAL_ADC_Init();
	
	/* Init Filters */
#if ( ADC_USE_RCLP_FILTER )
	{
		vprvBSPAdcInitRclpFilter();
	}
#endif
#if ( ADC_USE_NMS_FILTER )
	{
		vprvBSPAdcInitNmsFilter();
	}
#endif
	

}
/*----------------------------------------------------------------------------*/

void vBSPAdcGetResultRaw( eAdcChannel_t eChannel, uint16_t *pusReading )
{
	*pusReading = usprvAdcResult[ eChannel ];
}

/*----------------------------------------------------------------------------*/
void vBSPExternalAdcGetResultRaw( eExternalAdcChannel_t eChannel, uint16_t *pusReading )
{
	*pusReading = usprvExternalAdcResult[ eChannel ];	 
}

/*----------------------------------------------------------------------------*/

void vBSPAdcGetResultMv( eAdcChannel_t eChannel, int32_t *pslReadingMv,  uint16_t *usReadingRaw)
{
	uint16_t usAdcResult; 
	
	vBSPAdcGetResultRaw( eChannel, &usAdcResult );
	*usReadingRaw = usAdcResult;
	*pslReadingMv = ADC_LSB_TO_MV( usAdcResult );
	
}

/*----------------------------------------------------------------------------*/
void vBSPExternalAdcGetResultMv( eExternalAdcChannel_t eChannel, int32_t *pslReadingMv ,  uint16_t *usReadingRaw )
{
	uint16_t usAdcResult; 
	
	vBSPExternalAdcGetResultRaw( eChannel, &usAdcResult );
	*usReadingRaw = ADC_LSB_TO_RAW_EXTERNAL(usAdcResult);
	*pslReadingMv = ADC_LSB_TO_MV_EXTERNAL( usAdcResult ) ;
	//*pslReadingMv =  usAdcResult ;
	
}

/*---------------------------------------------------------------------------*/

void vBSPAdcUpdateChannels( void )
{
	static uint8_t 	ucAdcCount = 0;
  eMpbError_t 		eMpbError;
	uint32_t 				ulAdcResult;
	
	/* internal ADC */
	HAL_ADC_Update( &usprvAdcSampleResult[0], &usprvAdcAccumulator[0], (uint8_t)ADC_NUMBER_CHANNEL );
	
	
	//for( uint8_t ucI = 0; ucI < ADC_NUMBER_CHANNEL; ucI++ )
	//{		
	//	HAL_ADC_ReadSingle( ucI, &usprvAdcSampleResult[ ucI ] ); TODO
	
	
	
	//	HAL_ADC_ReadSingle( ucI, &usVal );
		//usprvAdcSampleResult[ ucI ] = usVal; //(float)usVal / 4095.0f * ADC_VREF;
	//	HAL_ADC_ReadSingle( ucI, &usprvAdcSampleResult[ ucI ] );

/*		usVal = (uint16_t)(VOR_ADC->FIFO_DATA);		
		usprvAdcSampleResult[ ucI ] = usVal; //(uint16_t)(*pusVal) ; //+  ucI )  ;*/
		

	//	usprvAdcAccumulator[ ucI ] += usprvAdcSampleResult[ ucI ];
	//}
	
	
	/* Check if we completed the accumulation */
	ucAdcCount++;
	if( ucAdcCount == ADC_NUM_OF_SEQ )
	{
		ucAdcCount = 0;
		for( uint8_t ucI = 0; ucI < ADC_NUMBER_CHANNEL; ucI++ )
		{
			ulAdcResult = usprvAdcAccumulator[ ucI ] / ADC_ACCUMULATOR_DIVIDER;
			
#if ( ADC_USE_NMS_FILTER )
			{
				eMpbError = eMpbDigitalFilteringNmsAdd( &xprvAdcNmsFilter[ ucI ], ulAdcResult, ( int32_t* ) &ulAdcResult, NULL );
        if( eMpbError != eSuccess )
        {
           vMpblibsAssertParam( 0 );
        }
			}
#endif
			
#if ( ADC_USE_RCLP_FILTER )
			{
				eMpbError = eMpbDigitalFilteringRclpAdd( &xprvAdcRclpFilter[ ucI ], ulAdcResult, ( int32_t* ) &ulAdcResult );
				if( eMpbError != eSuccess )
				{
            vMpblibsAssertParam( 0 );
        }
			}
#endif	
			
			usprvAdcResult[ ucI ] = ulAdcResult;
			usprvAdcAccumulator[ ucI ] = 0;
		}
	}
 
 }

/*-------------------------------------------------------------------*/
eMpbError_t eBSPExternalAdcChannels(void)
 {
	static uint8_t 	ucExternalAdcCount = 0;
	eMpbError_t 	eMpbError;
	uint16_t		usData;
	uint8_t 		ucCount =0;
	uint32_t 		ulExternalAdcResult;
	
//	vBinaryOtputSetState( eOutputAdcCs0, eFalse );
	//eMpbError =  eAdc128s102ReadSingleChannel( 0, &usprvExternalAdcSampleResult[ 7 ] );	
//	eMpbError =  eAdc128s102ReadSingleChannel( 1, &usprvExternalAdcSampleResult[ 2 ] );	
//	eMpbError =  eAdc128s102ReadSingleChannel( 2, &usprvExternalAdcSampleResult[ 3 ] );	
//	eMpbError =  eAdc128s102ReadSingleChannel( 3, &usprvExternalAdcSampleResult[ 4 ] );	
//	vBinaryOtputSetState( eOutputAdcCs0, eTrue );
/* first 8 channels 	*/		
	for( uint8_t ucJ = 0; ucJ < eAdcExLnaSmldCurrentMonitor  ; ucJ++ )  //
	{		
		//vBSPSpiMasterCsInitAndStart( SPI_CHIP_SEL0 );	
		//vBinaryOtputSetState( eOutputAdcCs0, eFalse );	
		vBinaryOtputSetState( eOutputAdcCs0, eFalse );
		eMpbError =  eAdc128s102ReadSingleChannel( ucJ, &usData );	
		vBinaryOtputSetState( eOutputAdcCs0, eTrue );
		
		
		
		if(ucJ == 0)
		{
			ucCount = eAdcExLnaSmld_Bfm;
		}		
		else
		{
			ucCount = ucJ - 1 ; 	
		}
		
		
		
		
		usprvExternalAdcSampleResult[ ucCount ]	= usData;
	
    if(eMpbError == eSuccess)		
		{	
		usprvExternalAdcAccumulator[ ucCount ] += usprvExternalAdcSampleResult[ ucCount ];
		}
		else
		{
			return eMpbError;
		}
	}
	
	/* second 8 channels */
	//for( uint8_t ucJ2 = eAdcExLnaSmldCurrentMonitor; ucJ2 < eAdcExHpaMMld_Thermistor3  ; ucJ2++ )  //
	for( uint8_t ucJ2 = 0; ucJ2 < NUMBER_OF_CHANELS_BY_IC  ; ucJ2++ )  //
	{
		vBinaryOtputSetState( eOutputAdcCs1, eFalse );
		eMpbError =  eAdc128s102ReadSingleChannel( ucJ2, &usData );
		vBinaryOtputSetState( eOutputAdcCs1, eTrue );
		
		if(ucJ2 == 0)
		{
			ucCount = eAdcExSpare2;
		}
		else
		{
			ucCount = eAdcExLnaSmldCurrentMonitor +  ucJ2 - 1 ;
		}
		
		
	//	ucCount = ucJ2 + eAdcExLnaSmldCurrentMonitor; // place from the 8e position on the buffer 
		
		usprvExternalAdcSampleResult[ ucCount ]	= usData;
		
		if(eMpbError == eSuccess)
		{
			usprvExternalAdcAccumulator[ ucCount ] += usprvExternalAdcSampleResult[ ucCount ];
		}
		else
		{
			return eMpbError;
		}
	}
		
	/*third 8 channels */
	//for( uint8_t ucJ = eAdcExHpaMMld_Thermistor3; ucJ < ADC_EXTERNAL_NUMBER_CHANNEL  ; ucJ++ )  //
	for( uint8_t ucJ3 = 0; ucJ3 < NUMBER_OF_CHANELS_BY_IC  ; ucJ3++ )  //
	{
		vBinaryOtputSetState( eOutputAdcCs2, eFalse );
		eMpbError =  eAdc128s102ReadSingleChannel( ucJ3, &usData );
		vBinaryOtputSetState( eOutputAdcCs2, eTrue );
		
		if(ucJ3 == 0)
		{
			ucCount = eAdcExPd_Ref2;
		}
		else
		{
			ucCount = eAdcExHpaMMld_Thermistor1 + ucJ3 - 1 ;
		}
		
		
		//ucCount = ucJ3 + eAdcExHpaMMld_Thermistor3; // place from the 16e position on the buffer 
		
		usprvExternalAdcSampleResult[ ucCount ]	= usData;
		
		if(eMpbError == eSuccess)
		{
			usprvExternalAdcAccumulator[ ucCount ] += usprvExternalAdcSampleResult[ ucCount ];
		}
		else
		{
			return eMpbError;
		}
	}
	
	// Check if we completed the accumulation 
	ucExternalAdcCount++;
	if( ucExternalAdcCount == ADC_NUM_OF_SEQ )
	{
		ucExternalAdcCount = 0;
		for( uint8_t ucI = 0; ucI < ADC_EXTERNAL_NUMBER_CHANNEL; ucI++ )
		{
			ulExternalAdcResult = usprvExternalAdcAccumulator[ ucI ] / ADC_ACCUMULATOR_DIVIDER;
			
			
#if (FILTER_IS_NEEDED)
	eMpbError = eMpbDigitalFilteringRclpAdd( &xprvExternalAdcRclpFilter[ ucI ], ulExternalAdcResult, ( int32_t* ) &ulExternalAdcResult );
	if( eMpbError != eSuccess )
	{
        vMpblibsAssertParam( 0 );
    }	
#endif
			usprvExternalAdcResult[ ucI ] = ulExternalAdcResult;
			usprvExternalAdcAccumulator[ ucI ] = 0;
		}
	}
	return eMpbError;
 }

/*-------------------------------------------------------------------*/
