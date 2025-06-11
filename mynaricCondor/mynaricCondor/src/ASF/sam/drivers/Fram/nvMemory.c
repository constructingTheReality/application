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
#include "nvMemory.h"
#include "BSPSpi.h"
//#include "BSPAdc.h"
//#include "glue.h"
//#include "projectDef.h"
//#include "crc.h"
#include "binaryInput.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
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
 ** @brief $auxwr [addr] [data32] - Write 32 bits to the aux F-ram
 **
 ******************************************************************************/
hal_status_t FRAM_Write(uint32_t addr, uint32_t data, eSpiHandler_t eSpiHandler )
{
	hal_status_t stat, errStat = hal_status_ok;
	uint32_t len = 4;
	uint16_t usData = 0;
	if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam; 
	}
  
	
	Enable_FRAM_Power(); 
//	Disable_FRAM_Power();

		
    
	 stat = eBSPSpiFRamInit((uint8_t)eSpiHandler, FRAM_CHIP_SEL);
	 if(stat != hal_status_ok )
	 {
		return hal_status_timeout; 
	 }
	 
	 stat = eBSPSpiFramMasterWrite( (uint8_t)eSpiHandler, addr, (uint8_t*)&data, len);
	 if(stat != hal_status_ok)
	 {
		errStat = stat; 
	 }
	Disable_FRAM_Power();
  return errStat;
}
/*---------------------------------------------------------------------*/
hal_status_t FRAM_MultipleWrite(uint32_t addr, uint8_t *buf, eSpiHandler_t eSpiHandler, uint32_t len )
{
	hal_status_t stat, errStat = hal_status_ok;
	
	uint16_t usData = 0;
	if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam; 
	}
  
	
//	Enable_FRAM_Power(); 
//	Disable_FRAM_Power();

		
  
		
		
		/*
	 stat = eBSPSpiFRamInit((uint8_t)eSpiHandler, FRAM_CHIP_SEL);
	 if(stat != hal_status_ok )
	 {
		return hal_status_timeout; 
	 }
	 */
	 stat = eBSPSpiFramMasterWrite( (uint8_t)eSpiHandler, addr, buf, len);
	 if(stat != hal_status_ok)
	 {
		errStat = stat; 
	 }
	//Disable_FRAM_Power();
  return errStat;
}



/*******************************************************************************
 **
 ** @brief $auxrd [addr] - Read 32 bits from the aux F-ram
 **
 ******************************************************************************/
hal_status_t FRAM_Read( uint32_t addr, uint32_t *pulData, eSpiHandler_t eSpiHandler )
{
	hal_status_t stat, errStat = hal_status_ok;
	uint32_t buf;
	
	
	Enable_FRAM_Power();
	//Disable_FRAM_Power();
	
	stat = eBSPSpiFRamInit((uint8_t)eSpiHandler, FRAM_CHIP_SEL);
	 if(stat != hal_status_ok )
	 {
		 return hal_status_timeout;
	 }	
	
	stat = eBSPSpiFramMasterRead((uint8_t)eSpiHandler, addr, &buf,4);
	 if(stat != hal_status_ok )
	 {
		 return hal_status_timeout;
	 }
	Disable_FRAM_Power();
	 return errStat;
}

/*----------------------------------*/

hal_status_t FRAM_MultipleRead( uint32_t addr, uint8_t *pulData, uint32_t ulLength, eSpiHandler_t eSpiHandler)
{
	hal_status_t stat, errStat = hal_status_ok;
	uint32_t buf;
	
	if(addr > FRAM_LEN - 4)
	{
		return hal_status_badParam;
	}
	
	//uint32_t readData = 0;
	
	
	//Enable_FRAM_Power();
	//Disable_FRAM_Power();
	
	/*stat = eBSPSpiFRamInit((uint8_t)eSpiHandler, FRAM_CHIP_SEL);
	if(stat != hal_status_ok )
	{
		return hal_status_timeout;
	}*/

	

	stat = eBSPSpiFramMasterRead((uint8_t)eSpiHandler, addr, pulData, ulLength);
	//stat = eBSPSpiFramMasterRead((uint8_t)eSpiHandler, addr, (uint8_t*)pulData, ulLength);
	if(stat != hal_status_ok )
	{
		return hal_status_timeout;
	}
	//Disable_FRAM_Power();
	return errStat;
	
	
	/*
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
	
	return errStat;*/
}


void Enable_FRAM_Power(void)
{
  
	//vBinaryOtputSetState( eOutputFramPwrEna, eTrue );
	
}


void Disable_FRAM_Power(void)
{

	//vBinaryOtputSetState( eOutputFramPwrEna, eFalse );

}



