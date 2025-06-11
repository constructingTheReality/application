#include "can410Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5

static CAN_FRAME cRPDO_410;

/*---------------------------------------------------------------------------*/

void vInit410CanImage( void )
{
	cRPDO_410.data.value = 0;
	cRPDO_410.id = 0x410;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan410( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_410, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan410( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_410, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan410Encode( c410StatusDefinition_t *c410StatusDefinition  )
{
	eMpbError_t eMpbError = eSuccess;
	fValue_t fValue;
	floatUnion	fxCoefficientValue;
	uint8_t	ucOperation = 0;
	BytesUnion uxCoefficient;
	
	if(c410StatusDefinition != NULL)
	{	
		/* bits 0..1 */
		ucOperation								= c410StatusDefinition->CoeficientOperation;
		cRPDO_410.data.byte[0]					= ucOperation & 0x03;						
		
		/* bits 10..41 */
		fxCoefficientValue.fValue				= 0.0f;
		fxCoefficientValue.fValue				= c410StatusDefinition->fWriteValueCoefficient;
		uxCoefficient.value                     = 0;
		uxCoefficient.low                       = fxCoefficientValue.ulValue;
		
		uxCoefficient.value                     = ( uxCoefficient.value << DEF_CAN_410_WRITE_VALUE_COEFFICIENT ) & 0x000003FFFFFFFC00; 
		cRPDO_410.data.value					= cRPDO_410.data.value & 0xFFFFFC00000003FF ;
		cRPDO_410.data.value					= cRPDO_410.data.value |  uxCoefficient.value;
				
		
		/* bits 42..53 */
		uxCoefficient.value						= 0;
		uxCoefficient.s0						= c410StatusDefinition->usNumberCoefficient;
		uxCoefficient.value						= ( uxCoefficient.value << DEF_CAN_410_NUMBER_COEFFICIENT ) & 0x003FFC0000000000;		
		cRPDO_410.data.value					= cRPDO_410.data.value & 0xFFC003FFFFFFFFFF ;
		cRPDO_410.data.value					= cRPDO_410.data.value |  uxCoefficient.value;
				
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}


/*------------------------------------------------------------------------------------------*/

eMpbError_t eMpbCan410Decode( c410StatusDefinition_t *c410StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	fValue_t fValue;
	BytesUnion uxCoefficient;
	
	if(c410StatusDefinition != NULL)
	{
		/* bits 0-1*/
		uxCoefficient.value								= 0;
		uxCoefficient.value								= ( cRPDO_410.data.value >> DEF_CAN_410_COEFFICIENT_OPERATION) & 0x0000000000000003; 
		
		c410StatusDefinition->CoeficientOperation		= uxCoefficient.byte[0];
		
		
		
		/* bits 10..41 */
		uxCoefficient.value								= 0;
		uxCoefficient.value								= ( cRPDO_410.data.value >> DEF_CAN_410_WRITE_VALUE_COEFFICIENT) & 0x00000000FFFFFFFF; 
		fValue.ulLocalValue								=  uxCoefficient.low;
		c410StatusDefinition->fWriteValueCoefficient	=	fValue.fLocalValue; 
		
		
		/* bits 42..53 */
		uxCoefficient.value								= 0;
		uxCoefficient.value								= ( cRPDO_410.data.value >> DEF_CAN_410_NUMBER_COEFFICIENT) & 0x0000000000000FFF;
		c410StatusDefinition->usNumberCoefficient		=	uxCoefficient.s0;
		
		
		
		
		
		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
}

