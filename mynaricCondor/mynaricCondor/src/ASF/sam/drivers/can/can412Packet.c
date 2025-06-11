#include "can412Packet.h"

#include "laserData.h"
#include "dictionaryUtils.h"



static CAN_FRAME cRPDO_412;

/*---------------------------------------------------------------------------*/

void vInit412CanImage( void )
{
	cRPDO_412.data.value = 0;
	cRPDO_412.id = 0x412;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan412( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_412, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan412( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_412, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/


eMpbError_t eMpbCan412Encode( c412StatusDefinition_t *c412StatusDefinition  )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion uxPassword;
	
	if(c412StatusDefinition != NULL)
	{
		
		cRPDO_412.data.value					= 0;
		
		/*Bit 0-6   */		
		uxPassword.value						= c412StatusDefinition->ucPassword1;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_1 ) & 0x000000000000007F;		
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFFFFFFFFFFFF80 ;		
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;
		
		/*Bit 7-13   */
		uxPassword.value						= c412StatusDefinition->ucPassword2;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_2 ) & 0x0000000000003F80;
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFFFFFFFFFFC07F ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;
		
		/*Bit 14-20   */
		uxPassword.value						= c412StatusDefinition->ucPassword3;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_3 ) & 0x00000000001FC000;		
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFFFFFFFFE03FFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;
		
		/*Bit 21-27   */
		uxPassword.value						= c412StatusDefinition->ucPassword4;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_4 ) & 0x000000000FE00000;				
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFFFFFFF01FFFFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;

		/*Bit 28-34   */
		uxPassword.value						= c412StatusDefinition->ucPassword5;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_5 ) & 0x00000007F0000000;		
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFFFFF80FFFFFFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;
		
		/*Bit 35-41   */
		uxPassword.value						= c412StatusDefinition->ucPassword6;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_6 ) & 0x000003F800000000;		
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFFFC07FFFFFFFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;
		
		/*Bit 42-48   */
		uxPassword.value						= c412StatusDefinition->ucPassword7;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_7 ) & 0x0001FC0000000000;				
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFFFE03FFFFFFFFFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;

		/*Bit 49-55   */
		uxPassword.value						= c412StatusDefinition->ucPassword8;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_8 ) & 0x00FE000000000000;		
		cRPDO_412.data.value					= cRPDO_412.data.value & 0xFF01FFFFFFFFFFFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;

		/*Bit 56-63   */
		uxPassword.value						= c412StatusDefinition->ucPassword9;
		uxPassword.value						= ( uxPassword.value << DEF_CAN_412_PASSWORD_9 ) & 0x7F00000000000000;		
		cRPDO_412.data.value					= cRPDO_412.data.value & 0x80FFFFFFFFFFFFFF ;
		cRPDO_412.data.value					= cRPDO_412.data.value |  uxPassword.value;		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
	
}


/*------------------------------------------------------------------------------------------*/

eMpbError_t eMpbCan412Decode( c412StatusDefinition_t *c412StatusDefinition )
{
	
	eMpbError_t eMpbError = eSuccess;
	//fValue_t fValue;
	
	BytesUnion uxPassword;
	
	if(c412StatusDefinition != NULL)
	{
		/*Bit 0-6   */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_1) & 0x000000000000007F;
		c412StatusDefinition->ucPassword1								= (uint8_t)uxPassword.s0;
		
		/*Bit 7-13  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_2) & 0x000000000000007F;
		c412StatusDefinition->ucPassword2								= (uint8_t)uxPassword.s0;

		/*Bit 14-20  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_3) & 0x000000000000007F;
		c412StatusDefinition->ucPassword3								= (uint8_t)uxPassword.s0;
		
		/*Bit 21-27  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_4) & 0x000000000000007F;
		c412StatusDefinition->ucPassword4								= (uint8_t)uxPassword.s0;
				
		/*Bit 28-34  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_5) & 0x000000000000007F;
		c412StatusDefinition->ucPassword5								= (uint8_t)uxPassword.s0;
		
		/*Bit 35-41  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_6) & 0x000000000000007F;
		c412StatusDefinition->ucPassword6								= (uint8_t)uxPassword.s0;
		
		/*Bit 42-48  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_7) & 0x000000000000007F;
		c412StatusDefinition->ucPassword7								= (uint8_t)uxPassword.s0;		
		
		/*Bit 49-55  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_8) & 0x000000000000007F;
		c412StatusDefinition->ucPassword8								= (uint8_t)uxPassword.s0;

		/*Bit 56-62  */
		uxPassword.value												= 0;
		uxPassword.value												= ( cRPDO_412.data.value >> DEF_CAN_412_PASSWORD_9) & 0x000000000000007F;
		c412StatusDefinition->ucPassword9								= (uint8_t)uxPassword.s0;		
	}
	else
	{
		eMpbError = eOutOfMemory;
	}


	return eMpbError;
	
}


