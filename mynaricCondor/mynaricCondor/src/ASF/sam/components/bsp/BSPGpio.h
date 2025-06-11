/**
  * @file			BSPGpio.h
  * @brief    BSPGpio header file.
  * @author		juan andres
  * @date			Created on 3/ 4/2021
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
#ifndef BSPGPIO_H_
#define BSPGPIO_H_

/* Includes ----------------------------------------------------------------- */

#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
}GPIO_PinState;


typedef uint8_t GPIO_TypeDef ;

/**
* @brief	Struct to contain Gpio port and pin.
*/
typedef struct
{
	uint16_t		usPin;
	GPIO_TypeDef	pxPort; 
}
BSPGpioMap_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */


/**
* @brief		GPIO mapping, retrieves port and pin for relevant handle.
* @param[in]	xGpioHandle: handle of gpio is required.
* @param[out]	pxGpioMap: struct containing port and pin.
*/
void vBSPGpioGetMap( handle_t xGpioHandle, BSPGpioMap_t *pxGpioMap );

/**
* @brief	.
* @note		
*/
eMpbError_t GPIO_SetOutput(uint32_t port, uint32_t mask, uint32_t val);

//eMpbError_t GPIO_Read_Pin(uint32_t port, uint32_t mask ,eBool_t *peBool );

#endif /* __BSP_GPIO_H */


