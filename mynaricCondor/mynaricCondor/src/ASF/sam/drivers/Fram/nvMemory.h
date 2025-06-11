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
#ifndef NVMEMORY_H_
#define NVMEMORY_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
#include "BSPGpio.h"
#include "spi.h"

/* Define ------------------------------------------------------------------- */
#define FRAM_LEN (0x40000)
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
/*------------------------------------------------------------------------------*/
/**
 * @brief		Write 32 bits to the F-ram
 * @param[in]	addr: address
 * @param[in]	data32: 32-bits data
 */
hal_status_t FRAM_Write( uint32_t addr, uint32_t data , eSpiHandler_t eSpiHandler );
/*------------------------------------------------------------------------------*/
/**
 * @brief		Write len bytes to the F-ram
 * @param[in]	addr: address
 * @param[in]	data32: 32-bits data
 */
hal_status_t FRAM_MultipleWrite(uint32_t addr, uint8_t *buf, eSpiHandler_t eSpiHandler, uint32_t len );
/*------------------------------------------------------------------------------*/
/**
 * @brief		Read 32 bits from the F-ram
 * @param[in]	addr: address
 * @param[out]	pulData: 32-bits data
 */
hal_status_t FRAM_Read( uint32_t addr, uint32_t *pulData, eSpiHandler_t eSpiHandler  );
/*------------------------------------------------------------------------------*/
/**
 * @brief		Read Length bytes from the F-ram
 * @param[in]	addr: address
 * @param[out]	pulData: 32-bits data
 */
//hal_status_t FRAM_MultipleRead( uint32_t addr, uint32_t *pulData, uint32_t ulLength, eSpiHandler_t eSpiHandler);
hal_status_t FRAM_MultipleRead( uint32_t addr, uint8_t *pulData, uint32_t ulLength, eSpiHandler_t eSpiHandler);
/*------------------------------------------------------------------------------*/
/**
 * @brief		Power on the FRAM 
 * @param[in]	none
 * @param[out]	none
 */
void Enable_FRAM_Power(void);
/*------------------------------------------------------------------------------*/
/**
 * @brief		Power off the FRAM 
 * @param[in]	none
 * @param[out]	none
 */
void Disable_FRAM_Power(void);
/*------------------------------------------------------------------------------*/

#endif /* NVMEMORY_H_ */