#include "can411Packet.h"
#include "can410Packet.h"
#include "laserData.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_411;

/*---------------------------------------------------------------------------*/

void vInit411CanImage( void )
{
	cRPDO_411.data.value = 0;
	cRPDO_411.id = 0x411;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan411( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_411, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan411( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_411, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan411Encode( c411StatusDefinition_t *c411StatusDefinition  )
{
	eMpbError_t eMpbError = eSuccess;
	fValue_t fValue;
	floatUnion	fxCoefficientValue;
	uint8_t	ucOperation = 0;
	BytesUnion uxCoefficient;
	
	if(c411StatusDefinition != NULL)
	{
		
		c410StatusDefinition_t *pc410StatusDefinition;			
		pc410StatusDefinition = vLaserDataGetData410();
	//	eMpbCan410Decode( pc410StatusDefinition );
			

		if( pc410StatusDefinition->CoeficientOperation == WRITE_COEFFICIENT_TO_RAM )
		{
			
			c411StatusDefinition->fReadValueCalibrationCoefficient	= pc410StatusDefinition->fWriteValueCoefficient;
			c411StatusDefinition->usNumberCoefStatus				= pc410StatusDefinition->usNumberCoefficient;
		}
			
			cRPDO_411.data.value									= 0;
			fValue.fLocalValue							= c411StatusDefinition->fReadValueCalibrationCoefficient;
			cRPDO_411.data.low						= fValue.ulLocalValue;
			
			
			/*Bit 0-31   */
			fxCoefficientValue.fValue				= 0.0f;
			fxCoefficientValue.fValue				= c411StatusDefinition->fReadValueCalibrationCoefficient;
			uxCoefficient.value                     = 0;
			uxCoefficient.low                       = fxCoefficientValue.ulValue;
			uxCoefficient.value                     = ( uxCoefficient.value << DEF_CAN_411_COEFFICIENT ) & 0x00000000FFFFFFFF;
			cRPDO_411.data.value					= cRPDO_411.data.value & 0xFFFFFFFF00000000 ;
			cRPDO_411.data.value					= cRPDO_411.data.value |  uxCoefficient.value;
			
			
			/* bits 32..43*/
			uxCoefficient.value						= 0;
			uxCoefficient.s0						= c411StatusDefinition->usNumberCoefStatus;
			uxCoefficient.value						= ( uxCoefficient.value << DEF_CAN_411_INDEX_COEFFICIENT ) & 0x00000FFF00000000;
			cRPDO_411.data.value					= cRPDO_411.data.value &  0xFFFFF000FFFFFFFF;
			cRPDO_411.data.value					= cRPDO_411.data.value |  uxCoefficient.value;
			
					

		
		
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}


/*------------------------------------------------------------------------------------------*/

eMpbError_t eMpbCan411Decode( c411StatusDefinition_t *c411StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	fValue_t fValue;
	BytesUnion	cxCoefficient;
	
	if(c411StatusDefinition != NULL)
	{	
		/*Bit 0-31   */	
		cxCoefficient.value												= 0;
		cxCoefficient.value												= ( cRPDO_411.data.value >> DEF_CAN_411_COEFFICIENT) & 0x00000000FFFFFFFF; 
		fValue.ulLocalValue												= cxCoefficient.low;
		
		c411StatusDefinition->fReadValueCalibrationCoefficient			= fValue.fLocalValue;
		
		
		/* bits 32..43*/
		cxCoefficient.value												= 0;
		cxCoefficient.value												= ( cRPDO_411.data.value >> DEF_CAN_411_INDEX_COEFFICIENT) & 0x0000000000000FFF; 
		c411StatusDefinition->usNumberCoefStatus						= cxCoefficient.s0;
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
}

