
#include "can423Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_423  0.51


static CAN_FRAME cRPDO_423;

/*---------------------------------------------------------------------------*/

void vInit423CanImage( void )
{
		cRPDO_423.data.value = 0;
		cRPDO_423.id = 0x423;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan423( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_423, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan423( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_423, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan423Encode( c423StatusDefinition_t *c423StatusDefinition)
{
	


	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxBoosterOpticalInputPower;
	BytesUnion	cxBoosterOpticalOutputPower;
	BytesUnion	cxLnaOpticalOutputPower;
	BytesUnion	cxLnaOpticalInputPower;
	BytesUnion	cxUnitBaseTemperature;
	
	BytesUnion	cxPowerSupplyMonitor;
	
	
	floatUnion  fxValue;
	//mpb_coerced_t coerce = not_coerced;


	if(c423StatusDefinition != NULL)
	{
		
		/* ch 0 internal ADC  0..4 0->28V */	
		if(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1 > X2_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1 = X2_423_28V_MONITOR;
		}
		
		if(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1 < X1_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1 = X1_423_28V_MONITOR;
		}
		
		cxBoosterOpticalInputPower.value			= 0;
		cxBoosterOpticalInputPower.s0				= (uint16_t)(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1);
		cxBoosterOpticalInputPower.value			= ( cxBoosterOpticalInputPower.value << DEF_CAN_423_28V_CURRENT_MONITOR_CH1 ) & 0x000000000000001F; /* bits 0-4 */		
		cRPDO_423.data.value						= cRPDO_423.data.value & 0xFFFFFFFFFFFFFFE0 ;
		cRPDO_423.data.value						= cRPDO_423.data.value |  cxBoosterOpticalInputPower.value;
		

		/* ch 1 internal ADC  5..9 0->28V */
		if(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2 > X2_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2 = X2_423_28V_MONITOR;
		}
		
		if(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2 < X1_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2 = X1_423_28V_MONITOR;
		}
		
		
		
		cxBoosterOpticalOutputPower.value						= 0;
		cxBoosterOpticalOutputPower.s0							= (uint16_t)(c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2);
		cxBoosterOpticalOutputPower.value						= ( cxBoosterOpticalOutputPower.value << DEF_CAN_423_28V_CURRENT_MONITOR_CH2 ) & 0x00000000000003E0; /* bits 5-9 */

		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFFFFFFFFFC1F ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxBoosterOpticalOutputPower.value;
		
		
		
		/* ch 2 internal ADC  10..14 0->28V */
		if(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1 > X2_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1 = X2_423_28V_MONITOR;
		}
		
		if(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1 < X1_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1 = X1_423_28V_MONITOR;
		}
		

		cxLnaOpticalInputPower.value							= 0;
		cxLnaOpticalInputPower.s0								= (uint16_t)(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1);
		cxLnaOpticalInputPower.value							= ( cxLnaOpticalInputPower.value << DEF_CAN_423_28V_VOLTAGE_MONITOR_CH1 ) & 0x0000000000007C00; /* 10..14*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFFFFFFFF83FF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxLnaOpticalInputPower.value;
		
			
		
		/* ch 3 internal ADC  15.. 19 0->28V */
		if(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch2 > X2_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrVoltageMonitor_Ch2 = X2_423_28V_MONITOR;
		}
		
		if(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch2 < X1_423_28V_MONITOR )
		{
			c423StatusDefinition->f28V_PwrVoltageMonitor_Ch2 = X1_423_28V_MONITOR;
		}
		

		cxLnaOpticalOutputPower.value							= 0;
		cxLnaOpticalOutputPower.s0								= (uint16_t)(c423StatusDefinition->f28V_PwrVoltageMonitor_Ch2);
		cxLnaOpticalOutputPower.value							= ( cxLnaOpticalOutputPower.value << DEF_CAN_423_28V_VOLTAGE_MONITOR_CH2 ) & 0x00000000000F8000; /*15..19*/ 
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFFFFFFF07FFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxLnaOpticalOutputPower.value;		

		
		/* ch 4 internal ADC  20.. 24 0->7V */
		if(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1 > X2_423_7V_MONITOR )
		{
			c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1 = X2_423_7V_MONITOR;
		}
		
		if(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1 < X1_423_7V_MONITOR )
		{
			c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1 = X1_423_7V_MONITOR;
		}
		
		cxUnitBaseTemperature.value								= 0;
		cxUnitBaseTemperature.byte[0]							= (uint8_t)(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1);
		cxUnitBaseTemperature.value								= ( cxUnitBaseTemperature.value << DEF_CAN_423_7V_VOLTAGE_MONITOR_CH1 )  & 0x0000000001F00000; /*20..24*/ 
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFFFFFE0FFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxUnitBaseTemperature.value;		

				

		/* ch 5 internal ADC  25..29 0->7V*/
		if(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2 > X2_423_7V_MONITOR )
		{
			c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2 = X2_423_7V_MONITOR;
		}
		
		if(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2 < X1_423_7V_MONITOR )
		{
			c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2 = X1_423_7V_MONITOR;
		}
		
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_423_7V_VOLTAGE_MONITOR_CH2 ) & 0x000000003E000000; /*25..29*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFFFFC1FFFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxPowerSupplyMonitor.value;
				

	    /* ch 6 internal ADC  30 to 34 0->3V*/
		if(c423StatusDefinition->f3_3V_PwrVoltageMonitor > X2_423_3V_MONITOR )
		{
			c423StatusDefinition->f3_3V_PwrVoltageMonitor = X2_423_3V_MONITOR;
		}
		
		if(c423StatusDefinition->f3_3V_PwrVoltageMonitor < X1_423_3V_MONITOR )
		{
			c423StatusDefinition->f3_3V_PwrVoltageMonitor = X1_423_3V_MONITOR;
		}
		
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(c423StatusDefinition->f3_3V_PwrVoltageMonitor);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_423_3V_VOLTAGE_MONITOR ) & 0x00000007C0000000; /*30..34*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFFF83FFFFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxPowerSupplyMonitor.value;



	    /* ch 7 internal ADC  35 to 39 0->3V*/
		if(c423StatusDefinition->f3V_ld_PwrVoltageMonitor > X2_423_3V_MONITOR )
		{
			c423StatusDefinition->f3V_ld_PwrVoltageMonitor = X2_423_3V_MONITOR;
		}
		
		if(c423StatusDefinition->f3V_ld_PwrVoltageMonitor < X1_423_3V_MONITOR )
		{
			c423StatusDefinition->f3V_ld_PwrVoltageMonitor = X1_423_3V_MONITOR;
		}
		
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(c423StatusDefinition->f3V_ld_PwrVoltageMonitor);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_423_3_3_VOLTAGE_MONITOR ) & 0x000000F800000000; /*35..39*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFFF07FFFFFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxPowerSupplyMonitor.value;




	    /* ch 8 internal ADC  40 to 44 0->3V*/
		if(c423StatusDefinition->fAdcPwrCurrentMonitor > X2_423_3V_MONITOR )
		{
			c423StatusDefinition->fAdcPwrCurrentMonitor = X2_423_3V_MONITOR;
		}
		
		if(c423StatusDefinition->fAdcPwrCurrentMonitor < X1_423_3V_MONITOR )
		{
			c423StatusDefinition->fAdcPwrCurrentMonitor = X1_423_3V_MONITOR;
		}
		
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(c423StatusDefinition->fAdcPwrCurrentMonitor);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_423_ADC_VOLTAGE_MONITOR ) & 0x00001F0000000000; /*40..44*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFFE0FFFFFFFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxPowerSupplyMonitor.value;


	    /* ch 9 internal ADC  45 to 49 0->3V*/
		if(c423StatusDefinition->fCanPwrCurrentMonitor1 > X2_423_3V_MONITOR )
		{
			c423StatusDefinition->fCanPwrCurrentMonitor1 = X2_423_3V_MONITOR;
		}
		
		if(c423StatusDefinition->fCanPwrCurrentMonitor1 < X1_423_3V_MONITOR )
		{
			c423StatusDefinition->fCanPwrCurrentMonitor1 = X1_423_3V_MONITOR;
		}
		
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(c423StatusDefinition->fCanPwrCurrentMonitor1);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_423_CAN_VOLTAGE_MONITOR1 ) & 0x0003E00000000000; /*45..49*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFFFC1FFFFFFFFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxPowerSupplyMonitor.value;


	    /* ch 10 internal ADC 50.. 54 0->3V*/
		if(c423StatusDefinition->fCanPwrCurrentMonitor2 > X2_423_3V_MONITOR )
		{
			c423StatusDefinition->fCanPwrCurrentMonitor2 = X2_423_3V_MONITOR;
		}
		
		if(c423StatusDefinition->fCanPwrCurrentMonitor2 < X1_423_3V_MONITOR )
		{
			c423StatusDefinition->fCanPwrCurrentMonitor2 = X1_423_3V_MONITOR;
		}
		
		cxPowerSupplyMonitor.value								= 0;
		cxPowerSupplyMonitor.byte[0]							= (uint8_t)(c423StatusDefinition->fCanPwrCurrentMonitor2);
		cxPowerSupplyMonitor.value								= ( cxPowerSupplyMonitor.value << DEF_CAN_423_CAN_VOLTAGE_MONITOR2 ) & 0x007C000000000000; /*50..54*/
		
		cRPDO_423.data.value									= cRPDO_423.data.value & 0xFF83FFFFFFFFFFFF ;
		cRPDO_423.data.value									= cRPDO_423.data.value |  cxPowerSupplyMonitor.value;

	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}




eMpbError_t eMpbCan423Decode( c423StatusDefinition_t *c423StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxBoosterOpticalInputPower;
	BytesUnion	cxBoosterOpticalOutputPower;
	BytesUnion	cxLnaOpticalOutputPower;
	BytesUnion	cxLnaOpticalInputPower;
	BytesUnion	cxUnitBaseTemperature;
	BytesUnion	cxPowerSupplyMonitor;
	
	
	floatUnion  fxValue;
	//mpb_coerced_t coerce = coerced;


	if(c423StatusDefinition != NULL)
	{
		/* ch 0 internal ADC  0..4 0->28V */
		cxBoosterOpticalInputPower.value						= 0;
		cxBoosterOpticalInputPower.value						= ( cRPDO_423.data.value >> DEF_CAN_423_28V_CURRENT_MONITOR_CH1) & 0x000000000000001F; // bits 0-4
		
		c423StatusDefinition->f28V_PwrCurrentMonitor_Ch1			= (float)(cxBoosterOpticalInputPower.s0 );
		
		
		/* ch 1 internal ADC  5..9 0->28V */
		cxBoosterOpticalOutputPower.value						= 0;
		cxBoosterOpticalOutputPower.value						= ( cRPDO_423.data.value >> DEF_CAN_423_28V_CURRENT_MONITOR_CH2) & 0x000000000000001F; // bits 5..9
		c423StatusDefinition->f28V_PwrCurrentMonitor_Ch2			= (float)(cxBoosterOpticalOutputPower.s0 );
	
		
			
		/* ch 2 internal ADC  10..14 0->28V */
		cxLnaOpticalInputPower.value							= 0;
		cxLnaOpticalInputPower.value							= ( cRPDO_423.data.value >> DEF_CAN_423_28V_VOLTAGE_MONITOR_CH1) & 0x000000000000001F; 
		c423StatusDefinition->f28V_PwrVoltageMonitor_Ch1			= (float)(cxLnaOpticalInputPower.s0 );
		

		/* ch 3 internal ADC  15.. 19 0->28V */
		cxLnaOpticalOutputPower.value							= 0;
		cxLnaOpticalOutputPower.value							= ( cRPDO_423.data.value >> DEF_CAN_423_28V_VOLTAGE_MONITOR_CH2) & 0x000000000000001F; 
		c423StatusDefinition->f28V_PwrVoltageMonitor_Ch2			= (float)(cxLnaOpticalOutputPower.s0 );
		

		/* ch 4 internal ADC  20.. 24 0->7V */
		cxUnitBaseTemperature.value							= 0;
		cxUnitBaseTemperature.value							= ( cRPDO_423.data.value >> DEF_CAN_423_7V_VOLTAGE_MONITOR_CH1) & 0x000000000000001F;
		c423StatusDefinition->f7V_PwrVoltageMonitor_Ch1			= (float)(cxUnitBaseTemperature.byte[0] );
		
		
		/* ch 5 internal ADC  25..29 0->7V*/
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_423.data.value >> DEF_CAN_423_7V_VOLTAGE_MONITOR_CH2) & 0x000000000000001F;
		c423StatusDefinition->f7V_PwrVoltageMonitor_Ch2		= (float)(cxPowerSupplyMonitor.byte[0] );
		
		/* ch 6 internal ADC  30 to 34 0->3V*/
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_423.data.value >> DEF_CAN_423_3V_VOLTAGE_MONITOR) & 0x000000000000001F;
		c423StatusDefinition->f3_3V_PwrVoltageMonitor		= (float)(cxPowerSupplyMonitor.byte[0] );
		
		/* ch 7 internal ADC  35 to 39 0->3V*/
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_423.data.value >> DEF_CAN_423_3_3_VOLTAGE_MONITOR) & 0x000000000000001F;
		c423StatusDefinition->f3V_ld_PwrVoltageMonitor		= (float)(cxPowerSupplyMonitor.byte[0] );
		
		/* ch 8 internal ADC  40 to 44 0->3V*/
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_423.data.value >> DEF_CAN_423_ADC_VOLTAGE_MONITOR) & 0x000000000000001F;
		c423StatusDefinition->fAdcPwrCurrentMonitor			= (float)(cxPowerSupplyMonitor.byte[0] );
	
		/* ch 9 internal ADC  45 to 49 0->3V*/
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_423.data.value >> DEF_CAN_423_CAN_VOLTAGE_MONITOR1) & 0x000000000000001F;
		c423StatusDefinition->fCanPwrCurrentMonitor1		= (float)(cxPowerSupplyMonitor.byte[0] );

		/* ch 10 internal ADC 50.. 54 0->3V*/
		cxPowerSupplyMonitor.value							= 0;
		cxPowerSupplyMonitor.value							= ( cRPDO_423.data.value >> DEF_CAN_423_CAN_VOLTAGE_MONITOR2) & 0x000000000000001F;
		c423StatusDefinition->fCanPwrCurrentMonitor2		= (float)(cxPowerSupplyMonitor.byte[0] );
		
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	


	
	


	
}
