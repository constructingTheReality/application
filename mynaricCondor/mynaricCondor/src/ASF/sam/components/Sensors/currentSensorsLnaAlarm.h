/*
 * currentSensorsLnaAlarm.h
 *
 * Created: 6/14/2024 5:03:32 PM
 *  Author: j.castano
 */ 


#ifndef CURRENTSENSORSLNAALARM_H_
#define CURRENTSENSORSLNAALARM_H_


#include "mpblibs.h"
#include "dictionaryUtils.h"

#include "can428Packet.h"
#include "can409Packet.h"
#include "can402Packet.h"

eMpbError_t eCurrentSensorsLnaAlarmRun( MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment, c409StatusDefinition_t c409StatusDefinition, float fCurrentReaded  ,AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister, eBool_t *pLnaCurrentCriticalAlarm);



#endif /* CURRENTSENSORSLNAALARM_H_ */