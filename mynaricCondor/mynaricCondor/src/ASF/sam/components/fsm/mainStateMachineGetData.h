/*
 * mainStateMachineGetData.h
 *
 * Created: 8/23/2024 9:53:23 AM
 *  Author: j.castano
 */ 


#ifndef MAINSTATEMACHINEGETDATA_H_
#define MAINSTATEMACHINEGETDATA_H_

#include "LaserData.h"
#include "mpblibs.h"
#include "can428Packet.h"


eMpbError_t eMainStateMachineGetDataGetUnitTemperatureAlarm( eBool_t *bUniTemperatureAlarm )	;

eMpbError_t eMainStateMachineGetDataGetMpbAlarms( MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment )	;

void vClearResetFromStartupFlag(void);

eResetRequest_t eGetActualResetCommand(void);

eMpbError_t eMainStateMachineGetDataSetResetFromStartup( eBool_t bResetFromStartup );

eMpbError_t eGetLnaEnableStatus( eBool_t *bIsEnabled);

void vClearResetMessage( void);

eMpbError_t eUpdateFsmStates( 	uint8_t	ucLnaState, uint8_t ucHpaState, uint8_t ucHpaApcState, uint8_t ucMainLoopState);

#endif /* MAINSTATEMACHINEGETDATA_H_ */