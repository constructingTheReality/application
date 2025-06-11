
#include "can426Packet.h"
#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_423  0.51


static CAN_FRAME cRPDO_426;

/*---------------------------------------------------------------------------*/

void vInit426CanImage( void )
{
	cRPDO_426.data.value = 0;
	cRPDO_426.id = 0x426;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan426( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_426, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan426( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_426, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t eMpbCan426Encode( c426StatusDefinition_t *c426StatusDefinition)
{	
	eMpbError_t eMpbError = eSuccess;	
	BytesUnion	cxRawValue;
	floatUnion  fxValue;
	uint8_t     ucValue = 0;
	BytesUnion		ValueStateBooster;

	if(c426StatusDefinition != NULL)
	{		
		/* index */
		if(c426StatusDefinition->ucIndex > DEF_MAX_NUMBER_OF_CHANNELS )
		{
	//		c426StatusDefinition->ucIndex = DEF_MAX_NUMBER_OF_CHANNELS;
		}
		
		if(c426StatusDefinition->ucIndex < 0 )
		{
			c426StatusDefinition->ucIndex= 0;
		}
		cRPDO_426.data.value						= 0 ;
		cRPDO_426.data.byte[0]						= c426StatusDefinition->ucIndex;
		
		/* RAW DATA  */
		fxValue.fValue								= c426StatusDefinition->fRawData;
		cxRawValue.value							= 0;
		
		cRPDO_426.data.byte[1]						 = fxValue.bytes[0];
		cRPDO_426.data.byte[2]						 = fxValue.bytes[1];
		cRPDO_426.data.byte[3]						 = fxValue.bytes[2];
		cRPDO_426.data.byte[4]						 = fxValue.bytes[3];	
		
		/* states */
		cRPDO_426.data.byte[5]						 = c426StatusDefinition->usCommonState;	
		cRPDO_426.data.byte[6]						 = c426StatusDefinition->usLnaState;	
		cRPDO_426.data.byte[7]						 = c426StatusDefinition->usBoosterState;	
			
		ucValue										 =	c426StatusDefinition->eHpaApcState;	
		ucValue										 = (ucValue << 4 ) & 0xF0;
		cRPDO_426.data.byte[7]						= cRPDO_426.data.byte[7] | (ucValue ) ;
			
	}
	else
	{
		eMpbError = eOutOfMemory;
	}
	
	return eMpbError;
}
/*---------------------------------------------------------------------------*/
eMpbError_t eMpbCan426Decode( c426StatusDefinition_t *c426StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	BytesUnion	cxValue;
	floatUnion  fxValue;



	if(c426StatusDefinition != NULL)
	{
		/* index */
		c426StatusDefinition->ucIndex							= cRPDO_426.data.byte[0];
		
		/* raw data  */
		cxValue.value											= 0;
		cxValue.value											= ( cRPDO_426.data.value >> DEF_CAN_426_RAW_DATA) & 0x00000000FFFFFFFF; 
		fxValue.ulValue											= cxValue.low;
		c426StatusDefinition->fRawData							= fxValue.fValue;
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;

}

