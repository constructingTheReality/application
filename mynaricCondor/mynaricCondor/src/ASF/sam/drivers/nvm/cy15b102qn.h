/**
 * @file		cy15b102qn.h
 * @brief		cy15b102qn header file.
 * @author		juan andres
 * @date		Created on 3/ 4/2023
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

#ifndef CY15B102QN_H_
#define CY15B102QN_H_

/*****************************************************************************/ 
/* Include files                                                             */ 
/*****************************************************************************/

//#include "va416xx_hal.h"

/*****************************************************************************/ 
/* Global pre-processor symbols/macros ('#define')                           */ 
/*****************************************************************************/

#define FRAM_LEN (0x40000)

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */ 
/*****************************************************************************/

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/

/*****************************************************************************/ 
/* Global function prototypes ('extern', definition in C source)             */ 
/*****************************************************************************/

extern hal_status_t FRAM_Init  (uint8_t csNum);
extern hal_status_t FRAM_Write (uint32_t addr, uint8_t *buf, uint32_t len);
extern hal_status_t FRAM_Read  (uint32_t addr, uint8_t *buf, uint32_t len);
extern hal_status_t FRAM_UnInit(void);
extern hal_status_t FRAM_Read32(uint32_t addr, uint32_t *buf, uint32_t len);

/*****************************************************************************/ 
/* End of file                                                               */ 
/*****************************************************************************/
#endif /* CY15B102QN_H_ */