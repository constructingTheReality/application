/*
 * currentSensorsUpdateDatabase.h
 *
 * Created: 6/18/2024 12:49:31 PM
 *  Author: j.castano
 */ 


#ifndef CURRENTSENSORSUPDATEDATABASE_H_
#define CURRENTSENSORSUPDATEDATABASE_H_



#include "mpblibs.h"
#include "currentSensors.h"
#include "laserData.h"




eMpbError_t eCurrentSensorsUpdateDatabaseLna( xCurrentInputScaling_t* pxLocalCurrentInputScaling);

eMpbError_t eCurrentSensorsUpdateDatabaseHpa( xCurrentInputScaling_t* pxLocalCurrentInputScaling);



#endif /* CURRENTSENSORSUPDATEDATABASE_H_ */