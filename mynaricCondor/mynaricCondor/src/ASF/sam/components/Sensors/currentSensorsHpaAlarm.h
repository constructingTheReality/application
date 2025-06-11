/*
 * currentSensorsHpaAlarm.h
 *
 * Created: 6/17/2024 9:25:46 AM
 *  Author: j.castano
 */ 


#ifndef CURRENTSENSORSHPAALARM_H_
#define CURRENTSENSORSHPAALARM_H_


#include "mpblibs.h"
#include "dictionaryUtils.h"
//#include "mpbLosDetector.h"
//#include "can428Packet.h"
#include "can409Packet.h"
#include "can401Packet.h"
#include "can402Packet.h"

eMpbError_t eCurrentSensorsHpaAlarmRun( c409StatusDefinition_t c409StatusDefinition, 
										float fCurrentReaded1, 
										float fCurrentReaded2, 
										float fCurrentReaded3, 
										AlarmsAndStatusRegisterBitAssignment_t *pxAlarmRegister, 
										eBool_t *pbCurrentCriticalAlarm);



#endif /* CURRENTSENSORSHPAALARM_H_ */