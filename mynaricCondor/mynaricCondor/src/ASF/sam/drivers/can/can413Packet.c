#include "can413Packet.h"

#include "laserData.h"
#include "dictionaryUtils.h"



static CAN_FRAME cRPDO_413;

/*---------------------------------------------------------------------------*/

void vInit413CanImage( void )
{
	cRPDO_413.data.value = 0;
	cRPDO_413.id = 0x413;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan413( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_413, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan413( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_413, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan413Encode( c413StatusDefinition_t *c413StatusDefinition  )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion uxPassword;
	
	if(c413StatusDefinition != NULL)
	{
		
		cRPDO_413.data.value					= 0;
		
		/*Bit 0-6   */
		uxPassword.value						= c413StatusDefinition->ucPassword10;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_10 ) & 0x000000000000007F;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFFFFFFFFFFFF80 ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;
		
		/*Bit 7-13   */
		uxPassword.value						= c413StatusDefinition->ucPassword11;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_11 ) & 0x0000000000003F80;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFFFFFFFFFFC07F ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;
		
		/*Bit 14-20   */
		uxPassword.value						= c413StatusDefinition->ucPassword12;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_12 ) & 0x00000000001FC000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFFFFFFFFE03FFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;
		
		/*Bit 21-27   */
		uxPassword.value						= c413StatusDefinition->ucPassword13;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_13 ) & 0x000000000FE00000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFFFFFFF01FFFFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;

		/*Bit 28-34   */
		uxPassword.value						= c413StatusDefinition->ucPassword14;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_14 ) & 0x00000007F0000000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFFFFF80FFFFFFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;
		
		/*Bit 35-41   */
		uxPassword.value						= c413StatusDefinition->ucPassword15;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_15 ) & 0x000003F800000000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFFFC07FFFFFFFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;
		
		/*Bit 42-48   */
		uxPassword.value						= c413StatusDefinition->ucPassword16;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_16 ) & 0x0001FC0000000000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFFFE03FFFFFFFFFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;

		/*Bit 49-55   */
		uxPassword.value						= c413StatusDefinition->ucPassword17;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_17 ) & 0x00FE000000000000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0xFF01FFFFFFFFFFFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;

		/*Bit 56-63   */
		uxPassword.value						= c413StatusDefinition->ucPassword18;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_413_PASSWORD_18 ) & 0x7F00000000000000;
		cRPDO_413.data.value					= cRPDO_413.data.value & 0x80FFFFFFFFFFFFFF ;
		cRPDO_413.data.value					= cRPDO_413.data.value |  uxPassword.value;
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}


/*------------------------------------------------------------------------------------------*/

eMpbError_t eMpbCan413Decode( c413StatusDefinition_t *c413StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	fValue_t fValue;
	
	BytesUnion uxPassword;
	
	if(c413StatusDefinition != NULL)
	{
		/*Bit 0-6   */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_10) & 0x000000000000007F;
		c413StatusDefinition->ucPassword10								= (uint8_t)uxPassword.s0;
		
		/*Bit 7-13  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_11) & 0x000000000000007F;
		c413StatusDefinition->ucPassword11								= (uint8_t)uxPassword.s0;

		/*Bit 14-20  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_12) & 0x000000000000007F;
		c413StatusDefinition->ucPassword12								= (uint8_t)uxPassword.s0;
		
		/*Bit 21-27  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_13) & 0x000000000000007F;
		c413StatusDefinition->ucPassword13								= (uint8_t)uxPassword.s0;
		
		/*Bit 28-34  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_14) & 0x000000000000007F;
		c413StatusDefinition->ucPassword14								= (uint8_t)uxPassword.s0;
		
		/*Bit 35-41  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_15) & 0x000000000000007F;
		c413StatusDefinition->ucPassword15								= (uint8_t)uxPassword.s0;
		
		/*Bit 42-48  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_16) & 0x000000000000007F;
		c413StatusDefinition->ucPassword16								= (uint8_t)uxPassword.s0;
		
		/*Bit 49-55  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_17) & 0x000000000000007F;
		c413StatusDefinition->ucPassword17								= (uint8_t)uxPassword.s0;

		/*Bit 56-62  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_413.data.value >> DEF_CAN_413_PASSWORD_18) & 0x000000000000007F;
		c413StatusDefinition->ucPassword18								= (uint8_t)uxPassword.s0;
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
}



