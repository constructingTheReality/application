/*
 * currentSensorsConfigUpdate.h
 *
 * Created: 6/18/2024 1:03:08 PM
 *  Author: j.castano
 */ 


#ifndef CURRENTSENSORSCONFIGUPDATE_H_
#define CURRENTSENSORSCONFIGUPDATE_H_


#include "mpblibs.h"
//#include "powerSensors.h"
#include "currentSensing.h"
#include "laserData.h"
/*
void vPowerSensorsConfigUpdateCommon(void);
void vPowerSensorsConfigUpdateLna( void );
void vPowerSensorsConfigUpdateBooster( void );*/

//eMpbError_t ePowerSensorsConfigUpdateBooster(xPowerInputScaling_t *pxLocalPowerInputScaling, xHpaLimitsConfig_t *pxHpaLimitsConfig, xHpaPowersConfig_t *pxHpaPowersConfig, xLosValues_t *pxLosValues);

eMpbError_t eCurrentSensorsConfigUpdateLna(xCurrentInputScaling_t *pxLocalCurrentInputScaling);

eMpbError_t eCurrentSensorsConfigUpdateHpa(xCurrentInputScaling_t *pxLocalCurrentInputScaling);


#endif /* CURRENTSENSORSCONFIGUPDATE_H_ */