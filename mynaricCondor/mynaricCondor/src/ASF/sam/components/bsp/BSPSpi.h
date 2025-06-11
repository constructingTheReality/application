/**
  * @file			BSPSpi.h
  * @brief    BSP Spi  header file.
  * @author		juan andres
  * @date			Created on 3/ 4/2023
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
#ifndef BSPSPI_H_
#define BSPSPI_H_
/* Includes ----------------------------------------------------------------- */

#include "spi.h"
//#include "board.h"
#include "sysclk.h"

#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/* Buffer size. */
#define DATA_BUFFER_SIZE         0x05
/**
* @brief        Define the DAC inputs.
* @note         DacChannelId               The identifier for the channel.
* @note         RCLP filter constant       The rclp filter constant. 
*/

/*	                	        X(	DacChannelId			,RCLP Filter Constant   )	*/
#define LIST_OF_SPI_CHANNELS	X(  eSpiChannel0		    ,4                     )\
                                X(	eSpiChannel1		    ,4                     )
															
															


/* Exported macro ----------------------------------------------------------- */

/* Chip select. */
#define SPI_CHIP_SEL 0
#define FRAM_CHIP_SEL  (1) 
#define SPI_CHIP_PCS spi_get_pcs(SPI_CHIP_SEL)

#define NUM_SPI_BANKS       (2)

#define SPI_CHIP_SEL0 0
#define SPI_CHIP_SEL1 1
#define SPI_CHIP_SEL2 3
/* Clock polarity. */
#define SPI_CLK_POLARITY 0

/** SPI base address for SPI master mode*/
#define SPI_MASTER_BASE      SPI0
#define SPI1_MASTER_BASE      SPI1

/* Clock phase. */
#define SPI_CLK_PHASE 1

/* Delay before SPCK. */
#define SPI_DLYBS 0x40

/* Delay between consecutive transfers. */
#define SPI_DLYBCT 0x10
/* SPI clock setting (Hz). */
static uint32_t gs_ul_spi_clock = 500000;

	/* Number of commands logged in status. */
	#define NB_STATUS_CMD   20
/* Status block. */
struct status_block_t {
	/** Number of data blocks. */
	uint32_t ul_total_block_number;
	/** Number of SPI commands (including data blocks). */
	uint32_t ul_total_command_number;
	/** Command list. */
	uint32_t ul_cmd_list[NB_STATUS_CMD];
};
/* SPI Status. */
static struct status_block_t gs_spi_status;

/* SPI clock configuration. */
static const uint32_t gs_ul_clock_configurations[] =
{ 500000, 1000000, 2000000, 5000000 };
	
	
	/* SPI example commands for this example. */
	/* slave test state, begin to return RC_RDY. */
	#define CMD_TEST     0x10101010 //0x10101010

	/* Slave data state, begin to return last data block. */
	#define CMD_DATA     0x29380000

	/* Slave status state, begin to return RC_RDY + RC_STATUS. */
	#define CMD_STATUS   0x68390384

	/* Slave idle state, begin to return RC_SYN. */
	#define CMD_END      0x68390484

	/* General return value. */
	#define RC_SYN       0x55AA55AA

	/* Ready status. */
	#define RC_RDY       0x12345678

	/* Slave data mask. */
	#define CMD_DATA_MSK 0xFFFF0000

	/* Slave data block mask. */
	#define DATA_BLOCK_MSK 0x0000FFFF



	/* Number of SPI clock configurations. */
	#define NUM_SPCK_CONFIGURATIONS 4

	/* SPI Communicate buffer size. */
	#define COMM_BUFFER_SIZE   64



/* Address Masks */
#define ADDR_MSB_MASK   (uint32_t)0xFF0000
#define ADDR_MID_MASK   (uint32_t)0x00FF00
#define ADDR_LSB_MASK   (uint32_t)0x0000FF
#define MSB_ADDR_BYTE(addr)   ((uint8_t)((addr & ADDR_MSB_MASK)>>16))
#define MID_ADDR_BYTE(addr)   ((uint8_t)((addr & ADDR_MID_MASK)>>8))
#define LSB_ADDR_BYTE(addr)   ((uint8_t)(addr & ADDR_LSB_MASK))



	/* Current SPI return code. */
	static uint32_t gs_ul_spi_cmd = RC_SYN;

	/* Current SPI state. */
	static uint32_t gs_ul_spi_state = 0;

	/* 64 bytes data buffer for SPI transfer and receive. */
	static uint8_t gs_uc_spi_buffer[COMM_BUFFER_SIZE];


/* Exported enum ------------------------------------------------------------ */

/**
* @brief	Defines the possible ADC channels.
*/                             
typedef enum
{
#define X( spiChannelId, RCLPFilterConstant )	spiChannelId,
	LIST_OF_SPI_CHANNELS 
#undef X
	eNumberOfSpiChannel,
}
eSpiChannel_t;   


/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief	Inits and start the SPI.
* @note		Calibration is performed.
*/
void vBSPSpiMasterInitAndStart( void );
/**
* @brief		 inti the spi for manage the fram .
* @param[in]	csNum: chip seelct.
*/

hal_status_t eBSPSpiFRamInit(uint8_t spiBank, uint8_t csNum);
/**
 * \brief Perform SPI master transfer.
 *
 * \param pbuf Pointer to buffer to transfer.
 * \param size Size of the buffer.
 */
eMpbError_t eBSPSpiMasterTransfer(void *p_buf, uint32_t size);
/**
* @brief		 set the protocol frame to write in the FRAM 
* @param[in]	addr: 3 bytes of addres
* @param[in]	buf : data to write 
* @param[in]	len : length of data to write 
*/
hal_status_t eBSPSpiFramMasterWrite(uint8_t spiBank, uint32_t addr, uint8_t *buf, uint32_t len);
/**
* @brief		 set the protocol frame to read in the FRAM
* @param[in]	addr: 3 bytes of addres
* @param[in]	buf : data to read
*/
hal_status_t eBSPSpiFramMasterRead(uint8_t spiBank, uint32_t addr, uint8_t *buf, uint32_t len);
/**
* @brief		  set the output to the DAC.
* @param[in]	eChannel: the channel requested.
* @param[out]	usOutputValue: The dac output.
*/
//void vBSPDacSetOutputRaw( eDacChannel_t eChannel, uint16_t usOutputValue );

/**
* @brief		  set the output of the DAC in milivolt.
* @param[in]	eChannel: the channel requested.
* @param[out]	usOutputValueMv: The dac output in miliVolt.
*/
//void vBSPDacSetOutputMv( eDacChannel_t eChannel,  uint16_t usOutputValueMv );

//void vBSPDacSetOutputDuty( eDacChannel_t eChannel,  uint8_t ucDutyCycle);

/**
* @brief		  update the raw data channels 
*/
//void vBSPDacUpdateChannels( void );


#endif /* BSPSPI_H_ */