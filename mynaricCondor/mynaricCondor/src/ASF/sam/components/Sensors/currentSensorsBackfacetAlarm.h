/*
 * currentSensorsBackfacetAlarm.h
 *
 * Created: 6/18/2024 12:14:38 PM
 *  Author: j.castano
 */ 


#ifndef CURRENTSENSORSBACKFACETALARM_H_
#define CURRENTSENSORSBACKFACETALARM_H_


#include "mpblibs.h"
#include "dictionaryUtils.h"
#include "can402Packet.h"


eMpbError_t eCurrentSensorsBackfacetAlarmRun( float fLnaBackfacetCurrentReaded, float fHpaBackfacetCurrentReaded, float fLnaBackfacetLimit, float  fBackfacetHpaLimit, AlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment , eBool_t *pLnaBackfacetCurrentCriticalAlarm, eBool_t *pHpaBackfacetCurrentCriticalAlarm);


#endif /* CURRENTSENSORSBACKFACETALARM_H_ */