/**
  * @file 			cy15b102qn.c
  * @brief			cy15b102qn source file.
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
#include "cy15b102qn.h"
#include "spi.h"

//#include "va416xx_hal_ioconfig.h"
/*****************************************************************************/ 
/* Local pre-processor symbols/macros ('#define')                            */ 
/*****************************************************************************/

/* Commands */ 
#define FRAM_WREN		      0x06  /* Set write enable latch */
#define FRAM_WRDI		      0x04  /* Reset write enable latch */
#define FRAM_RDSR		      0x05  /* Read status register */
#define FRAM_WRSR		      0x01  /* Write status register */
#define FRAM_READ		      0x03  /* Read memory data */
#define FRAM_WRITE			  0x02  /* Write memory data */
#define FRAM_RDID		      0x9F   /* Read device ID */

/* Address Masks */ 
#define ADDR_MSB_MASK   (uint32_t)0xFF0000
#define ADDR_MID_MASK   (uint32_t)0x00FF00
#define ADDR_LSB_MASK   (uint32_t)0x0000FF
#define MSB_ADDR_BYTE(addr)   ((uint8_t)((addr & ADDR_MSB_MASK)>>16))
#define MID_ADDR_BYTE(addr)   ((uint8_t)((addr & ADDR_MID_MASK)>>8))
#define LSB_ADDR_BYTE(addr)   ((uint8_t)(addr & ADDR_LSB_MASK))


/** FRAM1 Power*/
/*#define FRAM1_PWR_PORT    PORTE
#define FRAM1_PWR_BANK    VOR_GPIO->BANK[4]
#define FRAM1_PWR_PIN     (9)
*/

/** FRAM2 Power*/
/*#define FRAM2_PWR_PORT    PORTE
#define FRAM2_PWR_BANK    VOR_GPIO->BANK[4]
#define FRAM2_PWR_PIN     (7)
*/

/** FRAM1 Power*/
/*#define FRAM1_WP_PORT    PORTE
#define FRAM1_WP_BANK    VOR_GPIO->BANK[4]
#define FRAM1_WP_PIN     (10)
*/

/** FRAM2 Power*/
/*#define FRAM2_WP_PORT    PORTE
#define FRAM2_WP_BANK    VOR_GPIO->BANK[4]
#define FRAM2_WP_PIN     (8)
*/
//#define GPIO_SET(port, pin) (port->SETOUT = (1UL<<pin))
//#define GPIO_CLR(port, pin) (port->CLROUT = (1UL<<pin))



#define SPI_MASTER_MSK      (0xF) // SPI 0-3 support master mode
#define SPI_SLAVE_MSK       (0x7) // SPI 0-2 support slave mode

//#define SPI0_BANK           (0)
//#define SPI1_BANK           (1)
//#define SPI2_BANK           (2)
//#define SPI3_BANK           (3)

//#define SPI_CLK  (SystemCoreClock/2) // SPI peripherals reside on APB1

#define SPI_MIN_WORDLEN     (4)
#define SPI_MAX_WORDLEN     (16)


/*****************************************************************************/ 
/* Global variable definitions (declared in header file with 'extern')       */ 
/*****************************************************************************/

/*****************************************************************************/ 
/* Local type definitions ('typedef')                                        */ 
/*****************************************************************************/

/*****************************************************************************/ 
/* Local variable definitions ('static')                                     */ 
/*****************************************************************************/

//static bool isSpiInit[NUM_SPI_BANKS] = {0};

/*****************************************************************************/ 
/* Local function prototypes ('static')                                      */ 
/*****************************************************************************/

static void wait_idle(void);
//static void wait2_idle(uint8_t spiBank);
/*****************************************************************************/ 
/* Function implementation - global ('extern') and local ('static')          */ 
/*****************************************************************************/

/*******************************************************************************
 **
 ** @brief  Wait for the SPI to be idle, then clear the FIFOs
 **
 ******************************************************************************/
static void wait_idle(void)
{
  /*if(spiBank >= NUM_SPI_BANKS)
	{
		return; 
	}
	*/
		
//	while( !(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_TFE_Msk) ) { };	// Wait until TxBuf sends all		
	
 // while( VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_BUSY_Msk ) { };	// Wait here until bytes are fully transmitted.
	
	
 // VOR_SPI->BANK[spiBank].FIFO_CLR = SPI_FIFO_CLR_RXFIFO_Msk|SPI_FIFO_CLR_TXFIFO_Msk;	// Clear Tx & RX fifo 
}
/*--------------------------------------------------------*/
//static void wait2_idle(uint8_t spiBank)
//{
//  if(spiBank >= NUM_SPI_BANKS)
//	{
//		return; 
//	}
//	
//		
//	while( !(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_TFE_Msk) ) { };	// Wait until TxBuf sends all		
//	
////  while( VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_BUSY_Msk ) { };	// Wait here until bytes are fully transmitted.
//	
//	
//  VOR_SPI->BANK[spiBank].FIFO_CLR = SPI_FIFO_CLR_RXFIFO_Msk|SPI_FIFO_CLR_TXFIFO_Msk;	// Clear Tx & RX fifo 
//}

/*******************************************************************************
 **
 ** @brief  Init a SPI periph for F-ram access (SPI in simple polling mode)
 **
 ******************************************************************************/
hal_status_t FRAM_Init( uint8_t csNum)
{
  //if(spiBank >= NUM_SPI_BANKS){ return hal_status_badParam; }
  if(csNum > 7){ return hal_status_badParam; }
  
/*#ifdef USE_HAL_DRIVER
  // using HAL driver
  hal_spi_init_t init;
  init.blockmode = true;
  init.bmstall = true;
  init.clkDiv = 4;
  init.loopback = false;
  init.mdlycap = false;
  init.mode = en_spi_clkmode_0;
  init.ms = en_spi_ms_master;
  init.slaveSelect = csNum;
  init.wordLen = 8;
  
  hal_status_t stat = HAL_Spi_Init(&VOR_SPI->BANK[spiBank], init);
  if(stat != hal_status_ok){ return stat; } // abort if driver init issue
  
  // Turn off HAL SPI driver interrupts (using polling mode)
  NVIC_DisableIRQ((IRQn_Type)(SPI0_RX_IRQn+(2*spiBank)));
  VOR_SPI->BANK[spiBank].IRQ_ENB = 0;
#else
  VOR_SYSCONFIG->PERIPHERAL_CLK_ENABLE |= (CLK_ENABLE_SPI0 << spiBank);
  VOR_SPI->BANK[spiBank].CLKPRESCALE = 0x4;
  VOR_SPI->BANK[spiBank].CTRL0 = 0x7;
  VOR_SPI->BANK[spiBank].CTRL1 = 0x382 | (csNum << SPI_CTRL1_SS_Pos);
#endif */ // HAL driver
  
  //Clear Block Protection bits to enable programming	
	//Does not set SRWD, so WP_n pin has no effect
	//GPIO_SET( FRAM1_WP_PORT, FRAM1_WP_PIN);
	//GPIO_SET( FRAM2_WP_PORT, FRAM2_WP_PIN);
	
/*  wait_idle(spiBank);
  VOR_SPI->BANK[spiBank].DATA = (uint32_t)FRAM_WREN | SPI_DATA_BMSTART_BMSTOP_Msk; // Set Write Enable Latch(WEL) bit 
	wait_idle(spiBank);
  VOR_SPI->BANK[spiBank].DATA = FRAM_WRSR;	// Write single-byte Status Register message
	VOR_SPI->BANK[spiBank].DATA = (uint32_t)0x00 | SPI_DATA_BMSTART_BMSTOP_Msk;	// Clear the BP1/BP0 protection
  wait_idle(spiBank);
  
  isSpiInit[spiBank] = true;*/
  return hal_status_ok;
}

/*******************************************************************************
 **
 ** @brief  Write to F-ram on spi[spiBank]
 **
 ******************************************************************************/
hal_status_t FRAM_Write(uint32_t addr, uint8_t *buf, uint32_t len)
{
  //if(spiBank >= NUM_SPI_BANKS){ return hal_status_badParam; }
  //if(isSpiInit[spiBank] == false){ return hal_status_notInitialized; }
  
  uint32_t volatile voidRead;
  
  //wait_idle(spiBank);
	
/*	VOR_SPI->BANK[spiBank].DATA = (uint32_t)FRAM_WREN | SPI_DATA_BMSTART_BMSTOP_Msk; // Set Write Enable Latch(WEL) bit 
	
	wait_idle(spiBank);
	
  VOR_SPI->BANK[spiBank].DATA = FRAM_WRITE; // Write command 
	VOR_SPI->BANK[spiBank].DATA = MSB_ADDR_BYTE(addr); // Address high byte
	VOR_SPI->BANK[spiBank].DATA = MID_ADDR_BYTE(addr); // Address mid byte 
	VOR_SPI->BANK[spiBank].DATA = LSB_ADDR_BYTE(addr); // Address low byte
  
	
	// READ/POLL the status register until the transaction is completed 
  while(len - 1) 
	{
		while (!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_TNF_Msk)) {};
			
	  VOR_SPI->BANK[spiBank].DATA = *buf++;
	  voidRead = VOR_SPI->BANK[spiBank].DATA;
	  --len;
  }
	
	while(!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_TNF_Msk)){}
		
	VOR_SPI->BANK[spiBank].DATA = (uint32_t)(*buf) | SPI_DATA_BMSTART_BMSTOP_Msk;
		
  wait_idle(spiBank);*/
  
  return hal_status_ok;
}

/*******************************************************************************
 **
 ** @brief  Read from F-ram on spi[spiBank]
 **
 ******************************************************************************/
hal_status_t FRAM_Read(uint8_t spiBank, uint32_t addr, uint8_t *buf, uint32_t len)
{
 // if(spiBank >= NUM_SPI_BANKS){ return hal_status_badParam; }
/*  if(isSpiInit[spiBank] == false){ return hal_status_notInitialized; }
  
  uint32_t volatile voidRead;
  uint32_t i;
  
  wait_idle(spiBank);
  VOR_SPI->BANK[spiBank].DATA = FRAM_READ; // Read command 
	VOR_SPI->BANK[spiBank].DATA = MSB_ADDR_BYTE(addr); // ff Address high byte
	VOR_SPI->BANK[spiBank].DATA = MID_ADDR_BYTE(addr); // Address mid byte 
	VOR_SPI->BANK[spiBank].DATA = LSB_ADDR_BYTE(addr); // Address low byte
  
  for(i=0; i<4; i++) {
		VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
	  while( !(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk) ) { };
	  voidRead =	VOR_SPI->BANK[spiBank].DATA; // Void read
  }
  
  for(i=0; i<len; i++) {
	  VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
		while(!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk)){}
	  *buf = VOR_SPI->BANK[spiBank].DATA;
		buf++;
	}
	VOR_SPI->BANK[spiBank].DATA = SPI_DATA_BMSTART_BMSTOP_Msk; // Terminate Block Transfer
	wait_idle(spiBank);
  */
  return hal_status_ok;
}

/*******************************************************************************
 **
 ** @brief  Un-init the F-ram and SPI
 **
 ******************************************************************************/
hal_status_t FRAM_UnInit(uint8_t spiBank)
{
//  if(spiBank >= NUM_SPI_BANKS){ return hal_status_badParam; }
  
 /* wait_idle(spiBank);
	VOR_SPI->BANK[spiBank].DATA = (uint32_t)FRAM_WREN | SPI_DATA_BMSTART_BMSTOP_Msk; // Set Write Enable Latch(WEL) bit 
	wait_idle(spiBank);
  VOR_SPI->BANK[spiBank].DATA = FRAM_WRSR;	// Write single-byte Status Register message
	VOR_SPI->BANK[spiBank].DATA = (uint32_t)0xfd | SPI_DATA_BMSTART_BMSTOP_Msk;	// Set the BP1/BP0 protection
  wait_idle(spiBank);
  
  hal_status_t stat = hal_status_ok;
  
#ifdef USE_HAL_DRIVER
  stat = HAL_Spi_DeInit(&VOR_SPI->BANK[spiBank]);
#else
  VOR_SPI->BANK[spiBank].CTRL1 = 0;
  VOR_SPI->BANK[spiBank].CTRL0 = 0;
  VOR_SYSCONFIG->PERIPHERAL_CLK_ENABLE &= ~(CLK_ENABLE_SPI0 << spiBank);
#endif
  isSpiInit[spiBank] = false;*/
  return stat;
}

/*******************************************************************************
 **
 ** @brief  Read from F-ram on spi[spiBank]
 **
 ******************************************************************************/
hal_status_t FRAM_Read32(uint8_t spiBank, uint32_t addr, uint32_t *buf, uint32_t len)
{
  //if(spiBank >= NUM_SPI_BANKS){ return hal_status_badParam; }
/*  if(isSpiInit[spiBank] == false){ return hal_status_notInitialized; }
  
  uint32_t volatile voidRead;
  uint32_t i;
  
  wait_idle(spiBank);
  VOR_SPI->BANK[spiBank].DATA = FRAM_READ; // Read command 
	VOR_SPI->BANK[spiBank].DATA = MSB_ADDR_BYTE(addr); // Address high byte
	VOR_SPI->BANK[spiBank].DATA = MID_ADDR_BYTE(addr); // Address mid byte 
	VOR_SPI->BANK[spiBank].DATA = LSB_ADDR_BYTE(addr); // Address low byte
  
  for(i=0; i<4; i++) {
		VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
	  while( !(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk) ) { };
	  voidRead =	VOR_SPI->BANK[spiBank].DATA; // Void read
  }
  
  for(i=0; i<len; i+=sizeof(int32_t)) {
		voidRead = 0;
	  VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
		while(!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk)){}
		voidRead = (VOR_SPI->BANK[spiBank].DATA);

		VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
		while(!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk)){}
		voidRead |= ((uint32_t)(VOR_SPI->BANK[spiBank].DATA) << 8) & 0x0000FF00;

		VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
		while(!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk)){}
		voidRead |= ((uint32_t)(VOR_SPI->BANK[spiBank].DATA) << 16) & 0x00FF0000;

		VOR_SPI->BANK[spiBank].DATA = 0x00; // Pump the SPI
		while(!(VOR_SPI->BANK[spiBank].STATUS & SPI_STATUS_RNE_Msk)){}
		voidRead |= ((uint32_t)(VOR_SPI->BANK[spiBank].DATA) << 24) & 0xFF000000;

		*buf = voidRead;
		buf++;
	}
	VOR_SPI->BANK[spiBank].DATA = SPI_DATA_BMSTART_BMSTOP_Msk; // Terminate Block Transfer
	wait_idle(spiBank);*/
  
  return hal_status_ok;
}


/*****************************************************************************/ 
/* End of file                                                               */ 
/*****************************************************************************/

