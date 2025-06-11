/**
  * @file 			BSPSpi.c
  * @brief			BSPSpi source file.
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

#include "BSPSpi.h"
#include "glue.h"
#include "binaryInput.h"
#include "usart_spi.h"
/* Private define ----------------------------------------------------------- */

/* We add 2 bits of resolution whit oversampling */
#define SPI_NUMBER_CHANNEL						( eNumberOfSpiChannel )

/* Commands */
#define FRAM_WREN		      0x06
#define FRAM_WRDI		      0x04
#define FRAM_RDSR		      0x05
#define FRAM_WRSR		      0x01
#define FRAM_READ		      0x03
#define FRAM_WRITE	      0x02
#define FRAM_RDID		      0x9F

/* ----------------------------------  SPI_DATA  ---------------------------------- */
#define SPI_DATA_VALUE_Pos                    (0UL)                     /*!< SPI DATA: VALUE (Bit 0) 							         */
#define SPI_DATA_VALUE_Msk                    (0xffffUL)                /*!< SPI DATA: VALUE (Bitfield-Mask: 0xffff)   					 */
#define SPI_DATA_BMSKIPDATA_Pos               (30UL)                    /*!< SPI DATA: BMSKIPDATA (Bit 30) 					             */
#define SPI_DATA_BMSKIPDATA_Msk               (0x40000000UL)            /*!< SPI DATA: BMSKIPDATA (Bitfield-Mask: 0x40000000)            */
#define SPI_DATA_BMSTART_BMSTOP_Pos           (31UL)                    /*!< SPI DATA: BMSTART/BMSTOP (Bit 31) 			                 */
#define SPI_DATA_BMSTART_BMSTOP_Msk           (0x80000000UL)

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static eBool_t isSpiInit[NUM_SPI_BANKS] = {0};
	
/*
static const uint32_t ulAdcRCLPFilterConstant[ ADC_NUMBER_CHANNEL ] =
{   
#define X( SpiChannelId, RCLPFilterConstant )	RCLPFilterConstant,
        LIST_OF_SPI_CHANNELS 
#undef X
};*/
/*******************************************************************************
 **
 ** @brief  Wait for the SPI to be idle, then clear the FIFOs
 **
 ******************************************************************************/
static void wait_idle(Spi *spiBank)
{
  if(spiBank >= NUM_SPI_BANKS)
	{
		return; 
	}
	 uint32_t timeout = SPI_TIMEOUT;
	/* 

	 while (!(spiBank->SPI_SR & SPI_SR_RDRF)) {
		 if (!timeout--) {
			 return SPI_ERROR_TIMEOUT;
		 }
	 }
	spiBank->SPI_SR-	
	while( !(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_TFE_Msk) ) { };	*/
		// Wait until TxBuf sends all		
	/*
  while( VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_BUSY_Msk ) { };	
	  // Wait here until bytes are fully transmitted.
	
	
  VOR_SPI->BANK[spiBank].FIFO_CLR = SPI_FIFO_CLR_RXFIFO_Msk|SPI_FIFO_CLR_TXFIFO_Msk;	
  // Clear Tx & RX fifo */
}


/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void vBSPSpiMasterInitAndStart( void )
{	
	spi_enable_clock(SPI_MASTER_BASE);
	spi_disable(SPI_MASTER_BASE);
	spi_reset(SPI_MASTER_BASE);
	spi_set_lastxfer(SPI_MASTER_BASE);
	spi_set_master_mode(SPI_MASTER_BASE);
	spi_disable_mode_fault_detect(SPI_MASTER_BASE);
	//spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, spi_get_pcs(SPI_CHIP_SEL0));///todo mr PS -> 1
	spi_set_clock_polarity(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_configure_cs_behavior(SPI_MASTER_BASE,SPI_CHIP_SEL, SPI_CS_RISE_FORCED );
	
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_CHIP_SEL,SPI_CSR_BITS_16_BIT);
	spi_set_baudrate_div(SPI_MASTER_BASE, SPI_CHIP_SEL,	( sysclk_get_peripheral_hz() / gs_ul_spi_clock));
	spi_set_transfer_delay(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_DLYBS, SPI_DLYBCT);
	spi_enable(SPI_MASTER_BASE);
	
}

/*-----------------------------------------------------------------------------------------------*/
hal_status_t eBSPSpiFRamInit(uint8_t spiBank, uint8_t csNum)
{
	

			
/*	spi_status_t spi_status;
	uint8_t data_read, Chip_Sel_read;
	if(spiBank >= NUM_SPI_BANKS){ return hal_status_badParam; }
	if(csNum > 2){ return hal_status_badParam; }
	
		spi_enable_clock(SPI_MASTER_BASE);
		spi_disable(SPI_MASTER_BASE);
		spi_reset(SPI_MASTER_BASE);
		//spi_set_variable_peripheral_select(SPI_MASTER_BASE);
	//	spi_set_lastxfer(SPI_MASTER_BASE);
		spi_set_master_mode(SPI_MASTER_BASE);
		spi_disable_mode_fault_detect(SPI_MASTER_BASE);
		spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, spi_get_pcs(FRAM_CHIP_SEL));
		
		spi_set_clock_polarity(SPI_MASTER_BASE, FRAM_CHIP_SEL, SPI_CLK_POLARITY);
		spi_set_clock_phase(SPI_MASTER_BASE, FRAM_CHIP_SEL, SPI_CLK_PHASE);
		
		spi_configure_cs_behavior(SPI_MASTER_BASE,FRAM_CHIP_SEL, SPI_CS_RISE_NO_TX );
		spi_set_delay_between_chip_select(SPI_MASTER_BASE, 6);
		
		spi_set_bits_per_transfer(SPI_MASTER_BASE, FRAM_CHIP_SEL,SPI_CSR_BITS_8_BIT);
		spi_set_baudrate_div(SPI_MASTER_BASE, FRAM_CHIP_SEL,	( sysclk_get_peripheral_hz() / gs_ul_spi_clock));
		SPI0->SPI_CSR[0] |= SPI_CSR_CSAAT;
		//	spi_set_transfer_delay(SPI_MASTER_BASE, FRAM_CHIP_SEL, SPI_DLYBS, SPI_DLYBCT);
		spi_enable(SPI_MASTER_BASE);
		


		vBinaryOtputSetState( eOutputFramCs, eFalse );
		while ((SPI0->SPI_SR & SPI_SR_TDRE) == 0);
		
		
		uint32_t usData = (uint32_t) (FRAM_WREN );
		spi_status = spi_write(SPI_MASTER_BASE, (uint16_t)usData, FRAM_CHIP_SEL, 0);
		if( spi_status != SPI_OK)
		{
			return hal_status_timeout;	
		}
		
		
		while ((SPI0->SPI_SR & SPI_SR_RDRF) == 0);
	
		vBinaryOtputSetState( eOutputFramCs, eTrue );
		
		vBinaryOtputSetState( eOutputFramCs, eFalse);
		
		while ((SPI0->SPI_SR & SPI_SR_TDRE) == 0);
	
		spi_status = spi_write(SPI_MASTER_BASE, (uint16_t)FRAM_WRSR, FRAM_CHIP_SEL, 0);
		if( spi_status != SPI_OK)
		{
			return hal_status_timeout;
		}
		
		spi_status = spi_write(SPI_MASTER_BASE, (uint16_t)0x0, FRAM_CHIP_SEL, 0);//2
		if( spi_status != SPI_OK)
		{
			return hal_status_timeout;
		}
		
		while(spi_transmission_done(SPI0) == 0)
		{
			
		}
		vBinaryOtputSetState( eOutputFramCs, eTrue );	
		//vBinaryOtputSetState( eOutputFramCs, eFalse);	

		//read status
		spi_write(SPI_MASTER_BASE, (uint16_t)FRAM_RDSR, FRAM_CHIP_SEL, 0);				
		spi_write(SPI_MASTER_BASE, (uint16_t)0, FRAM_CHIP_SEL, 0);			
		while ((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RDRF) == 0);			
		spi_read(SPI0, &data_read, &Chip_Sel_read);		
		while(spi_transmission_done(SPI0) == 0)
		{
		
		}
		vBinaryOtputSetState( eOutputFramCs, eTrue );	
			
	isSpiInit[1] = eTrue;
	*/
	return hal_status_ok;
}

/*----------------------------------------------------------------------------*/
eMpbError_t eBSPSpiMasterTransfer(void *p_buf, uint32_t size)
{
	
		uint8_t uc_pcs;
		static uint16_t data;
		spi_status_t spi_status ;

		uint16_t *p_buffer;

		p_buffer = p_buf;
	
		spi_status = spi_write(SPI_MASTER_BASE, p_buffer[0], 0, 1);
		if(  spi_status != SPI_OK)
		{
			return eDriverError;
		}
		
		/* Wait transfer done. */
		while ((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RDRF) == 0);
		
		spi_status = spi_read(SPI_MASTER_BASE, &data, &uc_pcs);
		if ( spi_status != SPI_OK)
		{
			return eDriverError;
		}
		
		p_buffer[0] = data;
		
		return eSuccess;
	
		
	
}
/*-----------------------------------------------------------------------------------------------*/
hal_status_t eBSPSpiFramMasterWrite(uint8_t spiBank, uint32_t addr, uint8_t *buf, uint32_t len)
{
	uint8_t data_read, Chip_Sel_read;
	hal_status_t hal_status;
	spi_status_t spi_status;
	Spi *p_spi;
	uint32_t lenTemp = 0;
	uint8_t uc_pcs;
	uint8_t ucData;

	uint8_t dataRx = 0;
	
	uint8_t *pbuf = NULL;
//	uint8_t *p_buffer;

	
	/* Data buffer. */
	uint8_t data[DATA_BUFFER_SIZE] = {FRAM_WREN};
	uint8_t data2[500] = {0};
	pbuf = &data2[0];
	lenTemp = len;		
		
		struct usart_spi_device USART_SPI_DEVICE_EXAMPLE = {
			/* Board specific select ID. */
			.id = USART_SPI_DEVICE_EXAMPLE_ID
		};
		
		
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
		//uint8_t ucData = 0;
	ucData = FRAM_WREN;
	// write enbale 
	spi_status = usart_spi_write_packet(USART_SPI_EXAMPLE, data, 1);	
	if(spi_status != 0)
	{
		return hal_status_periphErr;
	}	
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )


	usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	
	
	*pbuf++ = FRAM_WRITE;
	*pbuf++  =  MSB_ADDR_BYTE(addr);
	*pbuf++  =  MID_ADDR_BYTE(addr);
	*pbuf++  =  LSB_ADDR_BYTE(addr);
	
	while(lenTemp)
	{
		*pbuf++  = 	*buf++;
		lenTemp--;
	}
		
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	spi_status = usart_spi_write_packet(USART_SPI_EXAMPLE, data2, len + 4 ); 
	if(spi_status != 0)
	{
		return hal_status_periphErr;
	}	
	
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )	 
	usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	
	
//uniint
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	ucData = FRAM_WREN;
	// write enbale
	spi_status = usart_spi_write_packet(USART_SPI_EXAMPLE, &ucData, 1);	
	
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )
	
	ucData = FRAM_WRSR;
	spi_status = usart_spi_write_packet(USART_SPI_EXAMPLE, &ucData, 1);	
	if(spi_status != 0)
	{
		return hal_status_periphErr;
	}
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )
	
	ucData = 0xfd;
	spi_status = usart_spi_write_packet(USART_SPI_EXAMPLE, &ucData, 1);
	if(spi_status != 0)
	{
			return hal_status_periphErr;
	}
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )
	usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
		
	return hal_status_ok;
}
/*-----------------------------------------------------------------------------------------*/
hal_status_t eBSPSpiFramMasterRead(uint8_t spiBank, uint32_t addr, uint8_t *buf, uint32_t len)
{
	uint32_t ulSpiStatus = 0;
	uint8_t data_read, Chip_Sel_read;
	Spi *p_spi;
	hal_status_t hal_status = eSuccess;
	uint8_t uc_pcs;
	uint8_t ucData;
	spi_status_t spi_status;
	static uint8_t ucDataRx[8];
	
	static uint32_t i;
	//uint8_t *p_buffer;
	uint32_t volatile voidRead;

	uint8_t data[DATA_BUFFER_SIZE] = {0,0,0,0,0};
			
	struct usart_spi_device USART_SPI_DEVICE_EXAMPLE = {
				/* Board specific select ID. */
		.id = USART_SPI_DEVICE_EXAMPLE_ID
	};
	
	/* initialization */
	usart_spi_init(USART_SPI_EXAMPLE);
	usart_spi_setup_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE, SPI_MODE_0, USART_SPI_EXAMPLE_BAUDRATE, 0);
	usart_spi_enable(USART_SPI_EXAMPLE);
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	
	
	/* commnd read + addres = 4 bytes -> spi mosi*/
	data[0] = FRAM_READ;
	data[1] =  MSB_ADDR_BYTE(addr);
	data[2] =  MID_ADDR_BYTE(addr);
	data[3] =  LSB_ADDR_BYTE(addr);
	
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);	
	ulSpiStatus = usart_spi_write_packet(USART_SPI_EXAMPLE, data, 4);
	if(ulSpiStatus != 0)
	{
		return hal_status_periphErr;
	}

	/* read the data on spi MISO*/	
	for(i=0; i<len; i++) 
	{		
		usart_spi_read_single(USART_SPI_EXAMPLE, &data_read);		
		*buf = data_read;			
		buf++;		
	}
	
	
	usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	
	//uniint
	
	
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	ucData = FRAM_WREN;
	// write enbale
	usart_spi_write_packet(USART_SPI_EXAMPLE, &ucData, 1);
	if(ulSpiStatus != 0)
	{
		return hal_status_periphErr;
	}
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )
	
	ucData = FRAM_WRSR;
	usart_spi_write_packet(USART_SPI_EXAMPLE, &ucData, 1);
	if(ulSpiStatus != 0)
	{
		return hal_status_periphErr;
	}
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )
	
	ucData = 0xfd;
	usart_spi_write_packet(USART_SPI_EXAMPLE, &ucData, 1);
	if(ulSpiStatus != 0)
	{
		return hal_status_periphErr;
	}
	while ( !usart_spi_is_tx_empty(USART_SPI_EXAMPLE) )
	
	usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	
	return hal_status;
}

/*void vBSPAdcGetResultRaw( eAdcChannel_t eChannel, uint16_t *pusReading )
{
	*pusReading = usprvAdcResult[ eChannel ];
}**/

/*----------------------------------------------------------------------------*/
/*void vBSPExternalAdcGetResultRaw( eExternalAdcChannel_t eChannel, uint16_t *pusReading )
{
	*pusReading = usprvExternalAdcResult[ eChannel ];	 
}*/

/*----------------------------------------------------------------------------*/
/*
void vBSPAdcGetResultMv( eAdcChannel_t eChannel, int32_t *pslReadingMv )
{
	uint16_t usAdcResult; 
	
	vBSPAdcGetResultRaw( eChannel, &usAdcResult );
	*pslReadingMv = ADC_LSB_TO_MV( usAdcResult );
	
}*/

/*----------------------------------------------------------------------------*/
/*void vBSPExternalAdcGetResultMv( eExternalAdcChannel_t eChannel, int32_t *pslReadingMv )
{
	uint16_t usAdcResult; 
	
	vBSPExternalAdcGetResultRaw( eChannel, &usAdcResult );
	*pslReadingMv = ADC_LSB_TO_MV_EXTERNAL( usAdcResult );
	
}*/

/*---------------------------------------------------------------------------*/

/*void vBSPAdcUpdateChannels( void )
{
	//static uint8_t 	ucAdcCount = 0;
  //eMpbError_t 		eMpbError;
//	uint32_t 				ulAdcResult;
	

//	HAL_ADC_Update( &usprvAdcSampleResult[0], &usprvAdcAccumulator[0], (uint8_t)ADC_NUMBER_CHANNEL );
	
	
 }*/


/*-------------------------------------------------------------------*/
 
