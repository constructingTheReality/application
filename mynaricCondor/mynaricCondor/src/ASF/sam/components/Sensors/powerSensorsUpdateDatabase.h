/*
 * powerSensorsUpdateDatabase.h
 *
 * Created: 6/12/2024 11:42:13 AM
 *  Author: j.castano
 */ 


#ifndef POWERSENSORSUPDATEDATABASE_H_
#define POWERSENSORSUPDATEDATABASE_H_

#include "mpblibs.h"
#include "powerSensors.h"
#include "laserData.h"




eMpbError_t ePowerSensorsUpdateDatabaseCommon( xPowerInputScaling_t* pxLocalPowerInputScaling);

eMpbError_t ePowerSensorsUpdateDatabaseLna(xPowerInputScaling_t *pxLocalPowerInputScaling);

eMpbError_t ePowerSensorsUpdateDatabaseBooster(xPowerInputScaling_t *pxLocalPowerInputScaling, xHpaLimitsConfig_t *pxHpaLimitsConfig, xHpaPowersConfig_t *pxHpaPowersConfig, xLosValues_t *pxLosValues);


#endif /* POWERSENSORSUPDATEDATABASE_H_ */