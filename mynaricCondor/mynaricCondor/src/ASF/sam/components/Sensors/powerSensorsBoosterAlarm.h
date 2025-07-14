/*
 * powerSensorsBoosterAlarm.h
 *
 * Created: 6/12/2024 12:19:36 PM
 *  Author: j.castano
 */ 


#ifndef POWERSENSORSBOOSTERALARM_H_
#define POWERSENSORSBOOSTERALARM_H_

#include "mpblibs.h"
#include "dictionaryUtils.h"
#include "mpbLosDetector.h"
#include "can428Packet.h"
#include "can408Packet.h"
#include "can402Packet.h"
#include "powerSensorsAlarmValidateLimits.h"

eMpbError_t ePowerSensorBoosterAlarmRun( xLosValues_t *xpLosValues, xLosStates_t *pxLosStates, eBool_t *bHpaPowerLosAlarm, MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment_428, c408StatusDefinition_t c408StatusDefinition, float fInputPowerReaded , float fOutputPowerReaded ,xAlarmAndStatusRegister_t *pxAlarmRegister_402, eBool_t *pbBoosterPowerCriticalAlarm);


#endif /* POWERSENSORSBOOSTERALARM_H_ */