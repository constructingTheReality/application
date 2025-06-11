/*
 * currentSensorsCommonAlarm.h
 *
 * Created: 6/18/2024 10:41:16 AM
 *  Author: j.castano
 */ 


#ifndef CURRENTSENSORSCOMMONALARM_H_
#define CURRENTSENSORSCOMMONALARM_H_

#define DEF_428_COMMON_ALARMS_POSITION           ( 14 )
#define LEVEL_7V  ( 36.0 )
#define LEVEL_28_CURRENT  ( 166.0 )
#define LEVEL_28V  ( 36.0 )
#define LEVEL_3V  ( 6.6 )

#define LEVEL_ADC  ( 180 )


#include "mpblibs.h"
#include "dictionaryUtils.h"
#include "can428Packet.h"
#include "can423Packet.h"
//#include "laserData.h"

eMpbError_t eCurrentSensorsCommonAlarmRun( c423StatusDefinition_t *c423StatusDefinition, c428StatusDefinition_t * c428StatusDefinition , eBool_t *bInternalAlarm );


#endif /* CURRENTSENSORSCOMMONALARM_H_ */