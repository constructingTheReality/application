/**
  * @file 			BSPGpio.c
  * @brief			BSPgpio source file.
  * @author			juan andres
  * @date			Created on 3/4/2021
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

#include "BSPGpio.h"
#include "glue.h"
#include "ioport.h"
#include "mynaricBoard.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */

/* Exported functions ------------------------------------------------------- */
void vBSPGpioGetMap( handle_t xGpioHandle, BSPGpioMap_t *pxGpioMap )
{
	switch( xGpioHandle )
	{

		case eHandleLnaLddEna:
		{
			pxGpioMap->usPin	=	LNA_LDD_ENA_GPIO;
			pxGpioMap->pxPort	=	LNA_LDD_ENA_PORT;
		}
		break;
		case eHandleHpaSmLddEna:
		{
			pxGpioMap->usPin	=	HPA_SM_LDD_ENA_GPIO;
			pxGpioMap->pxPort	=	HPA_SM_LDD_ENA_PORT;
		}
		break;
		
		
		
		case eHandleHpaMmLddEna1:
		{
			pxGpioMap->usPin	=	HPA_MM_LDD_ENA1_GPIO;
			pxGpioMap->pxPort	=	HPA_MM_LDD_ENA1_PORT;
		}
		break;
		
		
		
		case eHandleHpaMmLddEna2:
		{
			pxGpioMap->usPin	=	HPA_MM_LDD_ENA2_GPIO;
			pxGpioMap->pxPort	=	HPA_MM_LDD_ENA2_PORT;
		}
		break;
		
		
		
		case eHandleFramPwrEna:
		{
			pxGpioMap->usPin	=	FRAM_PWR_ENA_GPIO;
			pxGpioMap->pxPort	=	FRAM_PWR_ENA_PORT;
		}
		break;
		case eHandle28vPwrDis1:
		{
			pxGpioMap->usPin	=	OUT_28V_PWR_DIS1_GPIO;
			pxGpioMap->pxPort	=	OUT_28V_PWR_DIS1_PORT;
		}
		break;
		case eHandle28vPwrDis2:
		{
			pxGpioMap->usPin	=	OUT_28V_PWR_DIS2_GPIO;
			pxGpioMap->pxPort	=	(OUT_28V_PWR_DIS2_PORT);
		}
		break;
		
		case eHandle3vPwrEna1:
		{
			pxGpioMap->usPin	=	OUT_3V_PWR_ENA1_GPIO;
			pxGpioMap->pxPort	=	(OUT_3V_PWR_ENA1_PORT);
		}
		break;
		case eHandle3vPwrEna2:
		{
			pxGpioMap->usPin	=	OUT_3V_PWR_ENA2_GPIO;
			pxGpioMap->pxPort	=	(OUT_3V_PWR_ENA2_PORT);
		}
		break;
		
		
		case eHandleAdcPwrEna :
		{
			pxGpioMap->usPin	=	ADC_VOLT_GPIO ;//ADC_PWR_ENA_GPIO;
			pxGpioMap->pxPort	=	(ADC_VOLT_PORT); //ADC_PWR_ENA_PORT;
		}
		break;
		case eHandleCanPwrEna1:
		{
			pxGpioMap->usPin	=	CAN_PWR_ENA1_GPIO;
			pxGpioMap->pxPort	=	(CAN_PWR_ENA1_PORT);
		}
		break;
		case eHandleCanPwrEna2:
		{
			pxGpioMap->usPin	=	CAN_PWR_ENA2_GPIO;
			pxGpioMap->pxPort	=	(CAN_PWR_ENA2_PORT);
		}
		break;
			/*case eHandleFramCs:
			{
				pxGpioMap->usPin	=	FRAM_CS_GPIO;
				pxGpioMap->pxPort	=	FRAM_CS_PORT;
			}
			break;*/
			
		case eHandleFramWp:
		{
			pxGpioMap->usPin	=	FRAM_WP_GPIO;
			pxGpioMap->pxPort	=	(FRAM_WP_PORT);
		}
		break;
			
			
		
		case eHandleAdcCs0:
		{
			pxGpioMap->usPin	=	ADC_CS0_GPIO;
			pxGpioMap->pxPort	=	(ADC_CS0_PORT);
		}
		break;
		case eHandleAdcCs1:
		{
			pxGpioMap->usPin	=	ADC_CS1_GPIO;
			pxGpioMap->pxPort	=	(ADC_CS1_PORT);
		}
		break;
		case eHandleAdcCs2:
		{
			pxGpioMap->usPin	=	ADC_CS2_GPIO;
			pxGpioMap->pxPort	=	(ADC_CS2_PORT);
		}
		break;
		
		default:
		{
			vMpblibsAssertParam( 0 );
		}
		break;
	}
}

/*--------------------------------------------------*/

eMpbError_t GPIO_SetOutput(uint32_t port, uint32_t mask, uint32_t val)
{
	
	ioport_set_pin_level(port,val);
	
  //if(port > 6){ return hal_status_badParam; }
 
  return eSuccess;
}
/*----------------------------------------------------------------------------*/
/*hal_status_t GPIO_Read_Pin(uint32_t port, uint32_t mask ,eBool_t *peBool )
{
  
  
  
  
  return hal_status_ok;
}*/
