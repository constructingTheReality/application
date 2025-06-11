
#include "can405Packet.h"

#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_405;

/*---------------------------------------------------------------------------*/

void vInit405CanImage( void )
{
		cRPDO_405.data.value = 0;
		cRPDO_405.id = 0x405;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan405( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_405, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan405( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_405, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t eMpbCan405Decode( c405Definition_t *c405Definition )
{
	eMpbError_t eMpbError = eSuccess;
	//BytesUnion ValueOfUnitInformation  ;
	

	if(c405Definition != NULL)
	{
		//ValueOfUnitInformation.value									= 0;
		
		c405Definition->ucIdCompany								= cRPDO_405.data.byte[0] & 0x0F; /* 0 ..3 */
		
		
		c405Definition->ulUnitSerialNumber						= ( cRPDO_405.data.value >> DEF_CAN_0405_SERIAL_NUMBER) & ((uint64_t)0x0000000000FFFFFF); // bits 4-27
		
		c405Definition->ucFirmwareVersionMajor					= ( cRPDO_405.data.value >> DEF_CAN_0405_MAJOR_SERIAL_VERSION) & ((uint64_t)0x000000000000000F); // bits 28-31
		c405Definition->ucFirmwareVersionMinor					= ( cRPDO_405.data.value >> DEF_CAN_0405_MINOR_SERIAL_VERSION) & ((uint64_t)0x000000000000000F); // bits 28-31
		c405Definition->ucFirmwareVersionPatch					= ( cRPDO_405.data.value >> DEF_CAN_0405_PATCH_SERIAL_VERSION) & ((uint64_t)0x00000000000001FF); // bits 36-44		

	}
	
	return eMpbError;
	
}


/*------------------------------------------------------------*/
eMpbError_t eMpbCan405Encode( c405Definition_t *c405Definition )
{
	eMpbError_t eMpbError = eSuccess;
	BytesUnion ValueOfUnitInformation  ;


	if(c405Definition != NULL)
	{
		cRPDO_405.data.value								= 0;
		ValueOfUnitInformation.value						= 0;
		ValueOfUnitInformation.value						=  c405Definition->ucIdCompany;
		cRPDO_405.data.byte[0]								=  ( ValueOfUnitInformation.value << DEF_CAN_0405_COMPANY) & ((uint64_t)0x000000000000000F); // bits 0-3
		
		
		ValueOfUnitInformation.s0 = 0;
		ValueOfUnitInformation.value						=  c405Definition->ulUnitSerialNumber;
		ValueOfUnitInformation.value						=  ( ValueOfUnitInformation.value << DEF_CAN_0405_SERIAL_NUMBER) & ((uint64_t)0x000000000FFFFFF0); // bits 4-27
		cRPDO_405.data.value								= cRPDO_405.data.value |  ValueOfUnitInformation.value;


		ValueOfUnitInformation.s0 = 0;
		ValueOfUnitInformation.value						=  c405Definition->ucFirmwareVersionMajor;
		ValueOfUnitInformation.value						=  ( ValueOfUnitInformation.value << DEF_CAN_0405_MAJOR_SERIAL_VERSION) & ((uint64_t)0x00000000F0000000); // bits 28-31
		cRPDO_405.data.value								= cRPDO_405.data.value |  ValueOfUnitInformation.value;
		
		ValueOfUnitInformation.s0 = 0;
		ValueOfUnitInformation.value						=  c405Definition->ucFirmwareVersionMinor;
		ValueOfUnitInformation.value						=  ( ValueOfUnitInformation.value << DEF_CAN_0405_MINOR_SERIAL_VERSION) & ((uint64_t)0x0000000F00000000); // bits 32-35
		cRPDO_405.data.value								= cRPDO_405.data.value |  ValueOfUnitInformation.value;		
		
		
		ValueOfUnitInformation.s0 = 0;
		ValueOfUnitInformation.value						=  c405Definition->ucFirmwareVersionPatch;
		ValueOfUnitInformation.value						=  ( ValueOfUnitInformation.value << DEF_CAN_0405_PATCH_SERIAL_VERSION) & ((uint64_t)0x00001FF000000000); // bits 36-44
		cRPDO_405.data.value								= cRPDO_405.data.value |  ValueOfUnitInformation.value;
		
	}

	return eMpbError;
}
