/*
 * boosterApcStateMachineGetData.h
 *
 * Created: 6/19/2024 12:39:30 PM
 *  Author: j.castano
 */ 


#ifndef BOOSTERAPCSTATEMACHINEGETDATA_H_
#define BOOSTERAPCSTATEMACHINEGETDATA_H_

#include "mpblibs.h"
#include "can406Packet.h"

#define		DIVIDE_BY_TEN  ( 0.1 )


typedef struct{

	uint8_t					bEnableHpa1  : 1  ; /* bit 0 */
	uint8_t					bSm1IsStucked : 1 ;/* bit 1 */
	uint8_t					bSm1OverHeat : 1; /* bit 2 */
	uint8_t					bSm1UnderHeat : 1; /* bit 3 */
}PumpSm1BitAssignment_t;

typedef union
{
	PumpSm1BitAssignment_t			PumpSm1BitAssignment;
	uint8_t							ulPumpSm1Value;
}cPumpSm1StatusFlags_t;

typedef struct
{
	cPumpSm1StatusFlags_t			cPumpSm1StatusFlags;
	float							fLaserPump1BoosterCurrent;
	uint16_t						usLaserPump1AccSetpoint;
	eBool_t							bSm1WavelengthIs1536;
	eBool_t							bCriticalStuckDetected;
}cPumpSm1StatusDefinition_t;

/*----------*/
typedef struct{

	uint8_t					bEnableMMHpa1  : 1  ; /* bit 0 */
	uint8_t					bMm1IsStucked : 1 ;/* bit 1 */
	uint8_t					bMm1OverHeat : 1; /* bit 2 */
	uint8_t					bMm1UnderHeat : 1; /* bit 3 */
}PumpMm1BitAssignment_t;

typedef union
{
	PumpMm1BitAssignment_t			PumpMm1BitAssignment;
	uint8_t							ulPumpMm1Value;
}cPumpMm1StatusFlags_t;


typedef struct
{
	cPumpMm1StatusFlags_t			cPumpMm1StatusFlags;
	float							fLaserPumpMm1BoosterCurrent;
	uint16_t						usLaserPumpMm1AccSetpoint;
}cPumpMm1StatusDefinition_t;

/*----------*/
typedef struct{

	uint8_t					bEnableMMHpa2  : 1  ; /* bit 0 */
	uint8_t					bMm2IsStucked : 1 ;/* bit 1 */
	uint8_t					bMm2OverHeat : 1; /* bit 2 */
	uint8_t					bMm2UnderHeat : 1; /* bit 3 */
}PumpMm2BitAssignment_t;

typedef union
{
	PumpMm2BitAssignment_t			Pump2BitAssignment;
	uint8_t							ulPumpMm2Value;
}cPumpMm2StatusFlags_t;

typedef struct
{
	cPumpMm2StatusFlags_t			cPumpMm2StatusFlags;
	float							fLaserPumpMm2BoosterCurrent;
	uint16_t						usLaserPumpMm2AccSetpoint;
	
}cPumpMm2StatusDefinition_t;

	
	
typedef struct{
	
	
	float	fCurrentHpaSm1;
	
	float fCurrentHpaMm1;
	float fCurrentHpaMm2;
	
	
}xBoosterCurrents_t;

typedef struct{
		float	fActualOutputPowerInMiliWatts;
		float fActualPowerInDbm;
		float fActualInputPowerInDbm;
		float	fSetPointInDbm;
		float  fSetPointInMiliWatts;
		float fValueConverted; 
		eBool_t bHpaInAccmode;
		
				
}xBoosterPowers_t;
	
		

	
eMpbError_t eBoosterApcStateGetDataGetConditionsOnPumpSm1( cPumpSm1StatusDefinition_t *pcPumpSm1StatusDefinition)	;

eMpbError_t eBoosterApcStateGetDataGetConditionsOnPumpMm1(  cPumpMm1StatusDefinition_t *pcPumpMm1StatusDefinition)	;
	
eMpbError_t eBoosterApcStateGetDataGetConditionsOnPumpMm2(  cPumpMm2StatusDefinition_t *pcPumpMm2StatusDefinition)	;


eMpbError_t eBoosterApcStateGetDataGetHpaActualConditionsOnPumps( xBoosterCurrents_t *pxBoosterCurrents);	


eMpbError_t eBoosterApcStateGetDataGetResetRequest( eResetRequest_t *peResetRequest, eBool_t *pbConditionsToResetBooster, eBool_t *pConditionsToResetLna);	

eMpbError_t eBoosterApcStateGetDataSetResetRequest( eResetRequest_t eResetRequest);	

//eMpbError_t eBoosterApcStateGetDataPowersAndOperationMode( xBoosterPowers_t *pxBoosterPowers);		
eMpbError_t eBoosterApcStateGetDataPowersAndOperationMode( xBoosterPowers_t *pxBoosterPowers, eBool_t *bEnable1Booster, eBool_t *bEnable2Booster, eBool_t *bEnable3Booster );

eMpbError_t eBoosterApcStateGetDataHpaSmParameters( uint16_t *pusMaxHpaCurrentSM_mA,  uint16_t *pusNominalCurrentPourcentage_sM);

eMpbError_t eBoosterApcStateGetDataHpaMm1Parameters( uint16_t *pusMaxHpaCurrentStageMM1_mA,  uint16_t *pusMaxHpaCurrentMM1_mA);

eMpbError_t eBoosterApcStateGetDataHpaMm2Parameters( uint16_t *pusMaxHpaCurrentStageMM2_mA,  uint16_t *pusMaxHpaCurrentMM2_mA);

eMpbError_t eBoosterApcStateGetDataUpdateControlMm1(xBoosterPowers_t xBoosterPowers, float *pfCurrentControlHpaMm1 )   ;
eMpbError_t eBoosterApcStateGetDataUpdateControlMm2(xBoosterPowers_t xBoosterPowers, float *pfCurrentControlHpaMm2 );

eMpbError_t eBoosterApcStateGetDataUpdateControlMm1AndMm2(xBoosterPowers_t xBoosterPowers, float *pfCurrentControlHpaMm2 );

eMpbError_t eBoosterApcStateGetDatasetControlcurrents(float fControlCurrentSm1, float fCurrentControlHpaMm1, float fCurrentControlHpaMm2 );	

eMpbError_t eBoosterApcStateGetDataResetHpaAlarms( void);
#endif /* BOOSTERAPCSTATEMACHINEGETDATA_H_ */