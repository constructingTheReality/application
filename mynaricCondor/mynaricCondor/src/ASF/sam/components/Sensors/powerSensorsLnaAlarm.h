/*
 * powerSensorsLnaAlarm.h
 *
 * Created: 6/12/2024 1:00:32 PM
 *  Author: j.castano
 */ 


#ifndef POWERSENSORSLNAALARM_H_
#define POWERSENSORSLNAALARM_H_

#include "mpblibs.h"
#include "dictionaryUtils.h"
#include "mpbLosDetector.h"
#include "can428Packet.h"
#include "can408Packet.h"
#include "can402Packet.h"
#include "powerSensorsAlarmValidateLimits.h"

eMpbError_t ePowerSensorLnaAlarmRun( MpbAlarmsAndStatusRegisterBitAssignment_t *pMpbAlarmsAndStatusRegisterBitAssignment, c408StatusDefinition_t c408StatusDefinition, float fInputPowerReaded , float fOutputPowerReaded ,xAlarmAndStatusRegister_t *pxAlarmRegister, eBool_t*bLnaPowerCriticalAlarm);

#endif /* POWERSENSORSLNAALARM_H_ */