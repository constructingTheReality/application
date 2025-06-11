/**
* @file		    nvmMemory.h
* @brief        nvmMemory header file.
* @author		juan
* @date			Created on 2021-3-12
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
#ifndef NVMMEMORY_H_
#define NVMMEMORY_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "BSPGpio.h"
#include "spi_fram.h"
//#include "va416xx_evk.h"
//#include "va416xx_hal_spi.h"

typedef enum{
  en_memcheck_no_app_valid = 0,
  en_memcheck_app_a_valid = 1,
  en_memcheck_app_b_valid = 2
} en_memcheck_t;

typedef enum{
  en_runapp_a,
  en_runapp_b
} en_runapp_t;


/* Define ------------------------------------------------------------------- */
#define MEMORY_INIT_ADDRESS   (  100  ) 
#define MEMORY_CRC_ADDRESS   (  0x800  ) 
#define MEMORY_BOOTLOADER_SHARED   (0) //(0x4000)

#define APPLICATION_TESTA_START_ADDR (0x21000)
#define APPLICATION_A_END_ADDR   (0x1FFFF)
#define APPLICATION_A_CRC_ADDR   (0x1FFFC)
#define APPLICATION_B_START_ADDR (0x8000)
#define APPLICATION_B_END_ADDR   (0x1FFFF)
#define APPLICATION_B_CRC_ADDR   (0x1FFFC)
#define APPLICATION_TEST_END_ADDR (0x37FFF)
#define APPLICATION_TEST_CRC_ADDR   (0x37FFC)
#define APPLICATION_IMG_SZ       (0x18000)
#define VECTOR_TABLE_OFFSET		   (0x0)
#define VECTOR_TABLE_LEN         (0x350)
#define RESET_VECTOR_OFFSET      (0x4)


#define IMAGE_A_CS (0)
#define IMAGE_B_CS (1)

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/*******************************************************************************
 **
 ** @brief $auxwr [addr] [data32] - Write 32 bits to the aux F-ram
 **
 ******************************************************************************/
hal_status_t FRAMAUX_Write( uint32_t addr, uint32_t data , eSpiHandler_t eSpiHandler ,  int id);
hal_status_t FRAMAUX_Multiple_Write(uint32_t addr, uint32_t *pData, eSpiHandler_t eSpiHandler , uint32_t len,  int id  );

/*******************************************************************************
 **
 ** @brief $auxrd [addr] - Read 32 bits from the aux F-ram
 **
 ******************************************************************************/
hal_status_t FRAMAUX_ReadAndPrint( uint32_t addr, uint32_t *pulData, eSpiHandler_t eSpiHandler ,  int id );
hal_status_t FRAMAUX_MultipleReadAndPrint( uint32_t addr, uint32_t *pulData, uint32_t ulLength, eSpiHandler_t eSpiHandler,  int id   );

void Enable_FRAM_Power(int id);
void Disable_FRAM_Power(int id);
bool Bootloader_CheckAppIsValid(en_runapp_t en_runapp, uint32_t* pcrc_calc, uint32_t* pcrc_exp);





#endif /* NVMMEMORY_H_ */