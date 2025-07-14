/*
 * powerSensorsConfigUpdate.h
 *
 * Created: 6/12/2024 10:44:32 AM
 *  Author: j.castano
 */ 


#ifndef POWERSENSORSCONFIGUPDATE_H_
#define POWERSENSORSCONFIGUPDATE_H_

#include "mpblibs.h"
#include "powerSensors.h"
#include "currentSensing.h"
#include "laserData.h"
/*
void vPowerSensorsConfigUpdateCommon(void);
void vPowerSensorsConfigUpdateLna( void );
void vPowerSensorsConfigUpdateBooster( void );*/

eMpbError_t ePowerSensorsConfigUpdateBooster(xPowerInputScaling_t *pxLocalPowerInputScaling, xHpaLimitsConfig_t *pxHpaLimitsConfig, xHpaPowersConfig_t *pxHpaPowersConfig, xLosValues_t *pxLosValues);

eMpbError_t ePowerSensorsConfigUpdateLna(xPowerInputScaling_t *pxLocalPowerInputScaling);

eMpbError_t ePowerSensorsConfigUpdateCommon(xPowerInputScaling_t *pxLocalPowerInputScaling);



#endif /* POWERSENSORSCONFIGUPDATE_H_ */