/**
* @file 		nvmMemory.c
* @brief		nvmMemory.c source file
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
#include "nvmMemory.h"
#include "spi_fram.h"
//#include "BSPAdc.h"
//#include "glue.h"
#include "projectDef.h"
#include "crc.h"

/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */


static bool CopyApplicationImageFromFRAM(en_runapp_t appSlot);
static void memclr(void * addr, size_t len);

static void memclr(void * addr, size_t len)
{
//	uint32_t mem = 0;
	uint32_t *mem_addr;
	int i;
	if(addr == NULL){
		return;
	}
	mem_addr = addr;
	for(i = 0; i < len /sizeof(uint32_t); i++ ){
		*mem_addr = 0x0;
		mem_addr++;
	}

}


/*******************************************************************************
 **
 ** @brief  Writes the application FW image space in RAM over to FRAM
 ** Returns true if the copy was successful
 **
 ******************************************************************************/
static bool CopyApplicationImageFromFRAM(en_runapp_t appSlot)
{
	uint32_t addrOriginal;
	uint32_t addrCopy;
	
	addrOriginal = APPLICATION_B_START_ADDR;
	
  if(appSlot == en_runapp_a){
	  addrCopy = APPLICATION_TESTA_START_ADDR;
		FRAM_Init(SPI1_BANK,IMAGE_A_CS);
		
  }else if(appSlot == en_runapp_b){
    addrCopy = APPLICATION_TESTA_START_ADDR;
		FRAM_Init(SPI1_BANK,IMAGE_B_CS);
  } else{
		return false;
	}
	
  VOR_SYSCONFIG->ROM_PROT |= SYSCONFIG_ROM_PROT_WREN_Msk; /* Allow writes to code memory space */
	//WDFEED();
  
	memclr((void *) addrCopy,APPLICATION_IMG_SZ);

  
			/* feed watchdog */
	//WDFEED();	
	
  FRAM_Read32(SPI1_BANK, addrOriginal, (uint32_t*)addrCopy, APPLICATION_IMG_SZ);	

		/* feed watchdog */
	//WDFEED();	
	
	VOR_SYSCONFIG->ROM_PROT &= ~SYSCONFIG_ROM_PROT_WREN_Msk; 
	
	FRAM_UnInit((uint8_t)SPI1_BANK);
	
	return true;
}

/*******************************************************************************
 **
 ** @brief $auxwr [addr] [data32] - Write 32 bits to the aux F-ram
 **
 ******************************************************************************/
hal_status_t FRAMAUX_Write(uint32_t addr, uint32_t data, eSpiHandler_t eSpiHandler,  int id )
{
	hal_status_t stat, errStat = hal_status_ok;
	
  if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam; 
	}
  
	//Enable_FRAM_Power( FRAM1 );
	Enable_FRAM_Power( id ); 
	
		if ( id == FRAM1)
	{
		
  stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
	}
	else
	{
		stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN1);
	}
	
  //stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
	//stat = FRAM_Init( (uint8_t)eSpiHandler, FRAM_AUX_SPI_CSN); //3 ss3 g14 ,1 ss1 e11,
  
	if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  stat = FRAM_Write((uint8_t)eSpiHandler, addr, (uint8_t*)&data, 4);

	if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  stat = FRAM_UnInit((uint8_t)eSpiHandler);
  
	if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  return errStat;
}
/*---------------------------------------------------------------------*/

hal_status_t FRAMAUX_Multiple_Write(uint32_t addr, uint32_t *pData, eSpiHandler_t eSpiHandler , uint32_t len ,  int id )
{
	hal_status_t stat, errStat = hal_status_ok;
	
  if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam; 
	}
  //addr = 0x4000;
	
	 /*	GPIO_SetOutput( 4, 0x00000100, 0x00000100 ); //e8 wp high
	GPIO_SetOutput( 4, 0x00000080, 0x00000080 ); //e7 power
	*/
//	stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN1);
	
/*
GPIO_SetOutput( 4, 0x00000200, 0x00000200 ); //e9 power
	GPIO_SetOutput( 4, 0x00000400, 0x00000400 ); // e10 wp*/
	Enable_FRAM_Power( id ); // FRAM1
	
	if ( id == FRAM1)
	{
		
  stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
	}
	else
	{
		stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN1);
	}
	
	//stat = FRAM_Init( (uint8_t)eSpiHandler, FRAM_AUX_SPI_CSN); //3
  
	if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  stat = FRAM_Write((uint8_t)eSpiHandler, addr, (uint8_t*)pData, len );

	if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  stat = FRAM_UnInit((uint8_t)eSpiHandler);
  
	if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
		
	Enable_FRAM_Power(FRAMS_OFF);
  return errStat;
}


/*******************************************************************************
 **
 ** @brief $auxrd [addr] - Read 32 bits from the aux F-ram
 **
 ******************************************************************************/
hal_status_t FRAMAUX_ReadAndPrint( uint32_t addr, uint32_t *pulData, eSpiHandler_t eSpiHandler ,  int id )
{
	hal_status_t stat, errStat = hal_status_ok;
	
  if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam; 
	}
  
  //uint32_t readData = 0;
	//Enable_FRAM_Power( FRAM1 );
 // stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
		Enable_FRAM_Power( id ); 
	
		if ( id == FRAM1)
	{
		
  stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
	}
	else
	{
		stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN1);
	}
	
  //stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI_CSN);
	
  if(stat != hal_status_ok){ errStat = stat; }
	
  stat = FRAM_Read((uint8_t)eSpiHandler, addr, (uint8_t*)pulData, 4);	
  if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  stat = FRAM_UnInit((uint8_t)eSpiHandler);	
  if(stat != hal_status_ok)
	{
		errStat = stat; 
	}

  return errStat;
}


hal_status_t FRAMAUX_MultipleReadAndPrint( uint32_t addr, uint32_t *pulData, uint32_t ulLength, eSpiHandler_t eSpiHandler, int id  )
{
	hal_status_t stat, errStat = hal_status_ok;
	
  if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam; 
	}
  
  //uint32_t readData = 0;
	
		
	Enable_FRAM_Power( id );  //FRAM1
	
	if ( id == FRAM1)
	{
		
  stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
	}
	else
	{
		stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN1);
	}
	
  //stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI1_CSN0);
	
	
//  stat = FRAM_Init((uint8_t)eSpiHandler, FRAM_AUX_SPI_CSN);
	
  if(stat != hal_status_ok){ errStat = stat; }
	
	stat = FRAM_Read((uint8_t)eSpiHandler, addr, (uint8_t*)pulData, ulLength );
	
 // stat = FRAM_Read((uint8_t)eSpiHandler, addr, (uint8_t*)pulData, 4);	
  if(stat != hal_status_ok)
	{
		errStat = stat; 
	}
	
  stat = FRAM_UnInit((uint8_t)eSpiHandler);	
  if(stat != hal_status_ok)
	{
		errStat = stat; 
	}

	Enable_FRAM_Power(FRAMS_OFF);
	
  return errStat;
}


void Enable_FRAM_Power(int id)
{
/*	
	if(id & (FRAM1 & FRAM2)){
		HAL_Iocfg_SetupPins(FRAM_Enable_PinCfgArr);
	}*/
	if(id & FRAM1){
		
		  GPIO_SetOutput( 4, 0x00000200, 0x00000200 ); //e9 power
		  GPIO_SetOutput( 4, 0x00000400, 0x00000400 ); // e10 wp
		

		
		
			GPIO_SetOutput( 4, 0x00000100, 0x00000000 ); //e8 wp high
			GPIO_SetOutput( 4, 0x00000080, 0x00000000 ); //e7 power
				
		
	
		
		
		
	//	GPIO_CLR(FRAM1_PWR_PORT, FRAM1_PWR_PIN);
	//	GPIO_SET(FRAM1_WP_PORT, FRAM1_WP_PIN);
	}
  else if(id & FRAM2){
		GPIO_SetOutput( 4, 0x00000100, 0x00000100 ); //e8 wp high
		GPIO_SetOutput( 4, 0x00000080, 0x00000080 ); //e7 power
		GPIO_SetOutput( 4, 0x00000200, 0x00000000 ); //e9 power
		 GPIO_SetOutput( 4, 0x00000400, 0x00000000 ); // e10 wp
		
		
		//GPIO_CLR(FRAM2_PWR_PORT, FRAM2_PWR_PIN);
		//GPIO_SET(FRAM2_WP_PORT, FRAM2_WP_PIN);
	}
	else if( id == FRAMS_OFF)
	{
		GPIO_SetOutput( 4, 0x00000200, 0x00000000 ); //e9 power
	//	GPIO_SetOutput( 4, 0x00000400, 0x00000000 ); // e10 wp
		
		GPIO_SetOutput( 4, 0x00000100, 0x00000000 ); //e8 wp high
	//	GPIO_SetOutput( 4, 0x00000080, 0x00000000 ); //e7 power
				
		
	}
	
}


void Disable_FRAM_Power(int id){
/*	
	if(id & (FRAM1 & FRAM2)){
		HAL_Iocfg_SetupPins(FRAM_Disable_PinCfgArr);
	}*/

/*	if(id & FRAM1){
		GPIO_SET(FRAM1_PWR_PORT, FRAM1_PWR_PIN);
		GPIO_CLR(FRAM1_WP_PORT, FRAM1_WP_PIN);
	}
  else if(id & FRAM2){
		GPIO_SET(FRAM2_PWR_PORT, FRAM2_PWR_PIN);
		GPIO_CLR(FRAM2_WP_PORT, FRAM2_WP_PIN);
	}*/
		if(id & FRAM1){
			GPIO_SetOutput( 4, 0x00000200, 0x00000000 ); //e9 power
			GPIO_SetOutput( 4, 0x00000400, 0x00000000 ); // e10 wp
			
		
		
	//	GPIO_CLR(FRAM1_PWR_PORT, FRAM1_PWR_PIN);
	//	GPIO_SET(FRAM1_WP_PORT, FRAM1_WP_PIN);
	}
  else if(id & FRAM2){
			GPIO_SetOutput( 4, 0x00000100, 0x00000000 ); //e8 wp high
			GPIO_SetOutput( 4, 0x00000080, 0x00000000 ); //e7 power
					
		//GPIO_CLR(FRAM2_PWR_PORT, FRAM2_PWR_PIN);
		//GPIO_SET(FRAM2_WP_PORT, FRAM2_WP_PIN);
	}
	

}

/*******************************************************************************
 **
 ** @brief  Checks the application A and B images (CRC and reset vector)
 **
 ******************************************************************************/
bool Bootloader_CheckAppIsValid(en_runapp_t en_runapp, uint32_t* pcrc_calc, uint32_t* pcrc_exp)
{
  bool retVal = 0;
//  uint32_t resetVector;
  uint32_t crc_calc, crc_exp;
  
  // Check APP B
	
	if(en_runapp == en_runapp_b)
	{
		Enable_FRAM_Power( FRAM2 );  //FRAM1
		
		CopyApplicationImageFromFRAM(en_runapp_b);
		
		Enable_FRAM_Power( FRAMS_OFF );  //FRAM1

		crc_exp = *((uint32_t*)(APPLICATION_B_CRC_ADDR));
	  *pcrc_exp = crc_exp;
		//    crc_calc = CalculateCRC16((uint8_t*)APPLICATION_B_START_ADDR, (uint8_t*)APPLICATION_B_CRC_ADDR);
		//	WDFEED();
		crc_calc = CalculateCRC32((uint8_t*)APPLICATION_TESTA_START_ADDR, (uint8_t*)APPLICATION_TEST_CRC_ADDR);
		*pcrc_calc = crc_calc;
		//WDFEED();
		if(crc_exp == crc_calc){
				retVal = 1;
				return retVal;
			}
		}
	
	
	if(en_runapp == en_runapp_a)
	{
		/*If B failed lets try A as the reseve*/
		// Check APP A
		Enable_FRAM_Power( FRAM1 );  //FRAM1
		
		CopyApplicationImageFromFRAM(en_runapp_a);
		Enable_FRAM_Power( FRAMS_OFF );  //FRAM1
		
		crc_exp = *((uint32_t*)(APPLICATION_A_CRC_ADDR));
		*pcrc_exp = crc_exp;
	 //   crc_calc = CalculateCRC16((uint8_t*)APPLICATION_B_START_ADDR, (uint8_t*)APPLICATION_B_CRC_ADDR);
	//	WDFEED();
		crc_calc = CalculateCRC32((uint8_t*)APPLICATION_TESTA_START_ADDR, (uint8_t*)APPLICATION_TEST_CRC_ADDR);
		*pcrc_calc = crc_calc;
	//	WDFEED();
		if(crc_exp == crc_calc){

				retVal = 1;
			}
		}
	
  
	return retVal;
}


