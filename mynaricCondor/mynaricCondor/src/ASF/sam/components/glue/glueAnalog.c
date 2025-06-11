/**
* @file 		GlueAnalog.c
* @brief		GlueAnalog source file.
* @author		juan
* @date			Created on 2021-3-8
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
#include "glue.h"
#include "BSPAdc.h"
#include "BSPPwm.h"
//#include "input.h"
/* Private define ----------------------------------------------------------- */


#define FEEDBACK_RESOLUTION ( 100 )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

/*void vGlueAnalogInit( void )
{

}*/
/*-----------------------------------------------------------------------------*/
extern eMpbError_t eMpblibsAnalogWriteDutyCycle( handle_t xANALOGx, uint32_t cDuty )
{
		eMpbError_t eMpbError = eSuccess ;
		

		switch( xANALOGx )
		{
			case eHandlePwmLnaStp:
			{
				vBSPPwmSetOutputDuty( PIN_PWM_LNA_PWM_STP_CHANNEL,  cDuty);
				
				
			}
			break;
			case eHandlePwmSmStp1 :
			{
				vBSPPwmSetOutputDuty( PIN_PWM_HPA_SM_PWM_STP1_CHANNEL,  cDuty);
				
			}
			break;
			case eHandlePwmSmStp2:
			{
				vBSPPwmSetOutputDuty( PIN_PWM_HPA_SM_PWM_STP2_CHANNEL,  cDuty);
				
			}
			break;
			case eHandlePwmMmStp1:
			{
				vBSPPwmSetOutputDuty( PIN_PWM_HPA_MM_PWM_STP1_CHANNEL,  cDuty);
				
			}
			break;
			case eHandlePwmMmStp2:
			{
				vBSPPwmSetOutputDuty( PIN_PWM_HPA_MM_PWM_STP2_CHANNEL,  cDuty);
				
			}
			break;
			case eHandlePwmMmclck1:
			{
				vBSPPwmSetOutputDuty( PIN_PWM_HPA_MM_CLK1_CHANNEL,  cDuty);
				
			}
			break;
			case eHandlePwmMmclck2:
			{
				vBSPPwmSetOutputDuty( PIN_PWM_HPA_MM_CLK2_CHANNEL,  cDuty);
				
			}
			break;
			
			default:
			{
				vMpblibsAssertParam( 0 );
			}
			break;
		}
		
		return eMpbError;
}

/*----------------------------------------------------------------------------*/
eMpbError_t eMpblibsAnalogWriteRes( handle_t xANALOGx, int32_t slResolution, int32_t slOutput )
{
	switch( xANALOGx )
	{
	//	case eHandleSetpointTemperature:
	//	{
			//vBSPTimSetDutyCycle( eTimerSetPointLaser, ( uint8_t )slOutput );
	//	}
	//	break;
		
		default:
		{
			vMpblibsAssertParam( 0 );
		}
		break;
	}
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/
;
eMpbError_t eMpblibsAnalogReadmV( handle_t xANALOGx, int32_t *plReading,  uint16_t *pusRaw )
{
	
	switch( xANALOGx )
	{
		case eHandleAdc28VPwrCurrentMonitorCH1:
		{
			vBSPAdcGetResultMv( eAdc28VPwrCurrentMonitorCH1, plReading, pusRaw );
		}
		break;
		case eHandleAdc28VPwrCurrentMonitorCH2:
		{
			vBSPAdcGetResultMv( eAdc28VPwrCurrentMonitorCH2, plReading, pusRaw );
		}
		break;
		case eHandleAdc28VPwrVoltageMonitorCH1:
		{
			vBSPAdcGetResultMv( eAdc28VPwrVoltageMonitorCH1, plReading, pusRaw );
		}
		break;
		case eHandleAdc28VPwrVoltageMonitorCH2:
		{
			vBSPAdcGetResultMv( eAdc28VPwrVoltageMonitorCH2, plReading, pusRaw );
		}
		break;
		case eHandleAdc7VPwrVoltageMonitorCH1:
		{
			vBSPAdcGetResultMv( eAdc7VPwrVoltageMonitorCH1, plReading, pusRaw );
		}
		break;
		case eHandleAdc7VPwrVoltageMonitorCH2:
		{
			vBSPAdcGetResultMv( eAdc7VPwrVoltageMonitorCH2, plReading, pusRaw );
		}
		break;
		case eHandleAdc3_3VPower_VoltageMonitor:
		{
			vBSPAdcGetResultMv( eAdc3_3VPower_VoltageMonitor, plReading , pusRaw);
		}
		break;
		case eHandleAdc3VPower_VoltageMonitor:
		{
			vBSPAdcGetResultMv( eAdc3VPower_VoltageMonitor, plReading , pusRaw);
		}
		break;
		case eHandleAdcPowerCurrentMonitor:
		{
			vBSPAdcGetResultMv( eAdcPowerCurrentMonitor, plReading , pusRaw );
		}
		break;

		case eHandleAdcCanPwrCurrentMonitorCH1:
		{
			vBSPAdcGetResultMv(eAdcCanPwrCurrentMonitorCH1 , plReading , pusRaw);
		}

		break;
		case eHandleAdcCanPwrCurrentMonitorCH2:
		{
			vBSPAdcGetResultMv( eAdcCanPwrCurrentMonitorCH2 , plReading , pusRaw);
		}

		break;
		
		
		
		case eHandleAdcLnaOutm2:
		{
			vBSPAdcGetResultMv( eAdcLnaOutputPower2, plReading , pusRaw);
		}
		break;
		case eHandleAdcPdReference:
		{
			vBSPAdcGetResultMv( eAdcPdReference, plReading , pusRaw);
		}

		break;
		case eHandleAdcLnaOutm1:
		{
			vBSPAdcGetResultMv( eAdcLnaOutputPower1, plReading , pusRaw);
		}

		break;
		
		
		
		
		/*  external 2 - ADC 1 */
		case eHandleAdcExLnaSmldCurrentMonitor:
		{
			vBSPExternalAdcGetResultMv( eAdcExLnaSmldCurrentMonitor, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		
		
		case eHandleAdcExHpaSmld_CurrentMonitor:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaSmld_CurrentMonitor, plReading , pusRaw );
			//*plReading = *plReading * 1.24090909;
		}

		break;
		case eHandleAdcExHpaMultiModeld_CurrentMonitor1:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaMmld_CurrentMonitor1, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		case eHandleAdcExHpaMultiModeld_CurrentMonitor2:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaMmld_CurrentMonitor2, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		
		case eHandleAdcExSmLnaThermistor:
		{
			vBSPExternalAdcGetResultMv( eAdcExLnaSmld_Thermistor, plReading, pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		
		case eHandleAdcExSmHpaThermistor:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaSmld_Thermistor, plReading, pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		
		
		/*  external 1 - ADC 0 */
		
		case eHandleExternalLnaInputPower1:
		{
			vBSPExternalAdcGetResultMv( eAdcExLna_Inm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
			//*pusRaw = *plReading * 1.24090909;
		}

		break;
		case eHandleExternalLnaInputPower2:
		{
			vBSPExternalAdcGetResultMv( eAdcExLna_Inm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
			//*pusRaw = *plReading * 1.24090909;
		}

		break;
		case eHandleExternalLnaOutputPower1:
		{
			vBSPExternalAdcGetResultMv( eAdcExLna_OutM1, plReading , pusRaw);
			
		}

		break;
		case eHandleExternalLnaOutputPower2:
		{
			vBSPExternalAdcGetResultMv( eAdcExLna_OutM2, plReading, pusRaw);
			
		}

		break;
				
		case eHandleExternalHpaInputPower1:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpa_Inm, plReading , pusRaw);
			
		}

		break;
		case eHandleExternalHpaInputPower2:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpa_Inm, plReading , pusRaw);
			
		}

		break;
		
		case eHandleExternalHpaOutputPower_lm1:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpa_OutLm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		case eHandleExternalHpaOutputPower_lm2:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpa_OutLm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		

		case eHandleExternalHpaOutputPower_hm1:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpa_OutHm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		case eHandleExternalHpaOutputPower_hm2:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpa_OutHm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		
		case eHandleExternalPd_ref1:
		{
			vBSPExternalAdcGetResultMv( eAdcExPd_Ref1, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		case eHandleExternalLnaSm_ld_Bfm:
		{
			vBSPExternalAdcGetResultMv( eAdcExLnaSmld_Bfm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		
		
		/*  external 3 - ADC 2 */
		
		case eHandleAdcExHpaMmThermistor1:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaMMld_Thermistor1, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		case eHandleAdcExHpaMmThermistor2:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaMMld_Thermistor2, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		
		case eHandleAdcExHpaMmThermistor3:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaMMld_Thermistor3, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;
		case eHandleAdcExHpaMmThermistor4:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaMMld_Thermistor4, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;				
		case eHandleAdcExCaseThermistor:
		{
			vBSPExternalAdcGetResultMv( eAdcExCaseThermistor1, plReading , pusRaw );
			//*plReading = *plReading * 1.24090909;
		}

		break;
		
		
		case eHandleExternalHpaSm_ld_Bfm:
		{
			vBSPExternalAdcGetResultMv( eAdcExHpaSmld_Bfm, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		
		case eHandleExternalPd_Ref:
		{
			vBSPExternalAdcGetResultMv( eAdcExPd_Ref2, plReading , pusRaw);
			//*plReading = *plReading * 1.24090909;
		}

		break;		
		
		default:
		{
			vMpblibsAssertParam( 0 );
		}
		break;
		

		
	}
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/

