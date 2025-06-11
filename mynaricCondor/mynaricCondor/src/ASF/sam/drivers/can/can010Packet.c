
#include "can010Packet.h"

#include "dictionaryUtils.h"

#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51


static CAN_FRAME cRPDO_010;

/*---------------------------------------------------------------------------*/

void vInit010CanImage( void )
{
		cRPDO_010.data.value = 0;
		cRPDO_010.id = 0x010;
}
/*---------------------------------------------------------------------------*/
eMpbError_t getCan010( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(pCan, &cRPDO_010, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/
eMpbError_t setCan010( CAN_FRAME *pCan)
{
	uint8_t size;
	size = sizeof(CAN_FRAME);
	
	memcpy(&cRPDO_010, pCan, size );
	return eSuccess;
}
/*---------------------------------------------------------------------------*/

eMpbError_t eMpbCan010Decode( c010Definition_t *c010Definition )
{
	eBool_t bSelectCan1;
	
	//bSelectCan1 = cRPDO_401.data.byte[0] && 0x80 ;
	
	if(c010Definition != NULL)
	{
		c010Definition->bPortSelector  = bSelectCan1;
		
	}
	
	return eSuccess;
	
}

/*-------------------------------------------------------------*/
eMpbError_t eMpbCan010Encode( c010Definition_t *c010Definition  )
{
	
	
	if(c010Definition != NULL)
	{
		//cRPDO_401.data.byte[0] = ( SelectPort_010->bPortSelected == eTrue)? 0x80 : 0x00;
	}
	
	return eSuccess;
}
