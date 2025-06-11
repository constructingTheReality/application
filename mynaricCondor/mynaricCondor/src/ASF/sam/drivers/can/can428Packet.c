
#include "can428Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_423  0.51


static CAN_FRAME cRPDO_428;

/*---------------------------------------------------------------------------*/

void vInit428CanImage( void )
{
	cRPDO_428.data.value = 0;
	cRPDO_428.id = 0x428;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan428( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_428, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan428( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_428, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t eMpbCan428Encode( c428StatusDefinition_t *c428StatusDefinition)
{
	eMpbError_t eMpbError = eSuccess;
//	BytesUnion	cxRawValue;

	if(c428StatusDefinition != NULL)
	{
		//cxRawValue.value							 = c428StatusDefinition.MpbAlarmsAndStatusRegisterBitAssignment;
		cRPDO_428.data.value						= 0 ;
		cRPDO_428.data.value						= (c428StatusDefinition->ulMpbAlarmsValue);
	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	return eMpbError;
}
/*---------------------------------------------------------------------------*/
eMpbError_t eMpbCan428Decode( c428StatusDefinition_t *c428StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;

	if(c428StatusDefinition != NULL)
	{
		
		c428StatusDefinition->ulMpbAlarmsValue = 	cRPDO_428.data.value;		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;

}

 
