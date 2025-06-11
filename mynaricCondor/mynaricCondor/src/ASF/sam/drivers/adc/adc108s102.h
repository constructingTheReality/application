/**
* @file		    adc108s102.h
* @brief        adc108s102 header file.
* @author		juan
* @date			Created on 2021-5-04
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
#ifndef ADC108S102_H_
#define ADC108S102_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"

/* Define ------------------------------------------------------------------- */
#define ADC108S102_DONE										( -1 )			/* Internal return code */

#define ADC108S102_RESULT_MASK						0xfff /* 12 bits resolution */

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
#define USE_HAL_DRIVER

//#include <va416xx_hal_spi.h>
//#include "va416xx_evk.h"
//#include "spi_adc.h"
/*
 * In case of Mynaric, we use the hard-wired 3300 mV 
 * for the reference pin VA. 
 */
#define ADC108S102_VA_MV_MINARIC_DEFAULT	3300
/*
 * Defining the ADC resolution being 12 bits, we can use the same driver for
 * both ADC108S102 (10 bits resolution) and ADC128S102 (12 bits resolution)
 * chips. The ADC108S102 effectively returns a 12-bit result with the 2
 * least-significant bits unset.
 */
#define ADC108S102_BITS		12  //10
#define ADC108S102_CHANNELS								( 8 )
#define ADC108S102_MAX_CHANNELS			8

#define BITS_PER_LONG 32
/*
#define GENMASK(h, l) \
-	(((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))
+	(((~UL(0)) - (UL(1) << (l)) + 1) & \
+	 (~UL(0) >> (BITS_PER_LONG - 1 - (h))))*/
/*
 * 16-bit SPI command format:
 *   [15:14] Ignored
 *   [13:11] 3-bit channel address
 *   [10:0]  Ignored
 */
#define ADC108S102_CMD(ch)		((uint16_t)(ch) << 11)
/*
 * 16-bit SPI response format:
 *   [15:12] Zeros
 *   [11:0]  12-bit ADC sample (for ADC108S102, [1:0] will always be 0).
 */
//#define ADC108S102_RES_DATA(res)	((u16)res & GENMASK(11, 0))

struct adc108s102_state {
//	struct spi_device		*spi;
//	struct regulator		*reg;
	uint32_t				va_millivolt;
	/* SPI transfer used by triggered buffer handler*/
//	struct spi_transfer		ring_xfer;
	/* SPI transfer used by direct scan */
//	struct spi_transfer		scan_single_xfer;
	/* SPI message used by ring_xfer SPI transfer */
//	struct spi_message		ring_msg;
	/* SPI message used by scan_single_xfer SPI transfer */
//	struct spi_message		scan_single_msg;

	/*
	 * SPI message buffers:
	 *  tx_buf: |C0|C1|C2|C3|C4|C5|C6|C7|XX|
	 *  rx_buf: |XX|R0|R1|R2|R3|R4|R5|R6|R7|tt|tt|tt|tt|
	 *
	 *  tx_buf: 8 channel read commands, plus 1 dummy command
	 *  rx_buf: 1 dummy response, 8 channel responses
	 */
	uint16_t				rx_buf[9] ;
	uint16_t				tx_buf[9] ;
};
/*
#define ADC108S102_V_CHAN(index)					\
{								\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = index,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
	BIT(IIO_CHAN_INFO_SCALE),			\
	.address = index,					\
	.scan_index = index,					\
	.scan_type = {						\
		.sign = 'u',					\
		.realbits = ADC108S102_BITS,			\
		.storagebits = 16,				\
		.endianness = IIO_BE,				\
	},							\
}*/
/**
* @brief    	setup the spi port
* @param[out]  	pucData: Pointer where to put the data from the EEPROM
* @return   	Success or library error message
*/
//eMpbError_t eAdc128s102SpiSetup(void);
/**
* @brief    	Read one specific channel of the adc
* @param[in]   	xSPIx: Application specific peripheral channel identifier
* @param[in]    usChannel: Address of data to read
* @param[out]  	pucData: Pointer where to put the data from the EEPROM
* @return   	Success or library error message
*/

eMpbError_t eAdc128s102ReadSingleChannel(  uint8_t ucChannel, uint16_t *pusData );
/**
* @brief    	Read in continuos all the channels of the adc
* @param[in]   	xSPIx: Application specific peripheral channel identifier
* @param[in]    ucLength: number of channels
* @param[out]  	pusData: Pointer where to put the data from the EEPROM
* @return   	Success or library error message
*/
//eMpbError_t eAdc128s102ReadChannelsContinuous( uint8_t spiBank, uint8_t ucLength, uint16_t *pusData);





#endif /* ADC108S102_H_ */