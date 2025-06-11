/**
* @file		    boosterAccSm.h
* @brief        boosterAccSm header file.
* @author		juan
* @date			Created on 2023-7-12
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2023 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef BOOSTERACCSM_H_
#define BOOSTERACCSM_H_

/* Define ------------------------------------------------------------------- */
#define		CURRENT_INCREASE_BY_STEP_IN_MA_HPA1  ( 100 )
#define		CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1  ( 500 )
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
typedef enum{
	eSM =0,
	eMM1 =1,
	eMM2 = 2,
	eNumberOfLasers = 3 
}ePumpType_t;

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief      
* @param[in]  PumpType: The pump laser : Sm, mm1 or mm2.
* @param[in]  bIncrease: new setpoint received is bigger that the older one.
* @param[in]  usSetpointInmA: setpint in mA
* @param[in]  usCurrentRead: actual current readed for the particular laser
* @param[in]  bEnable:  the first SM has reached the min threshold current value, in order to continue with further stages
* @param[out] pusStepsNumber: the number of steps 
* @return     none
**/
void vBoosterAccRun(  ePumpType_t PumpType, uint16_t *pusStepsNumber, eBool_t  bIncrease, uint16_t usSetpointInmA, uint16_t  usCurrentRead, eBool_t bEnable);
/**
* @brief      set the current to the pump sm1 
* @param[in]  usCurrent to be applied.
* @param[out] none 
* @return     none
**/
void vBoosterAccControlOnSm1( uint16_t usCurrent);
/**
* @brief      set the current to the pump Mm1
* @param[in]  usCurrent to be applied.
* @param[out] none
* @return     none
**/
void vBoosterAccControlOnMm1( uint16_t usCurrent);
/**
* @brief      set the current to the pump Mm2
* @param[in]  usCurrent to be applied.
* @param[out] none
* @return     none
**/
void vBoosterAccControlOnMm2( uint16_t usCurrent);
/**
* @brief      set the enable line to the pump Sm1
* @param[in]  bEnable : true or false 
* @param[out] none
* @return     none
**/
void vBoosterAccEnableOnSm1(eBool_t bEnable);
/**
* @brief      set the enable line to the pump Mm1
* @param[in]  bEnable : true or false
* @param[out] non
* @return     none
**/
void vBoosterAccEnableOnMm1(eBool_t bEnable);
/**
* @brief      set the enable line to the pump Mm2
* @param[in]  bEnable : true or false
* @param[out] none
* @return     none
**/
void vBoosterAccEnableOnMm2(eBool_t bEnable);
/**
* @brief      Prepare the execution for the next setpoint in ACC 
* @param[in]  PumpType: The pump laser : Sm, mm1 or mm2.
* @param[in]  usLastSetpointInPwm: last setpoint executed.
* @param[in]  fCurrent: actual current of the diode.
* @param[in]  usSetpointInPwm: new setpoint received.
* @param[in]  bIsStep50mA: step for ramp up is 50 mA.
* @param[in]  bWavelengthIs1536: input wavelength is 1536.
* @param[in]  bHpaReadyForSecondStep:  the first SM has reached the min threshold current value, in order to continue with further stages
* @param[out]  pbIncrease: new setpoint received is bigger that the older one.
* @param[out] pusStepsNumber: the number of steps
* @return     none
**/
void vBoosterSetupAcc(	ePumpType_t  ePumpType		,	uint16_t usLastSetpointInPwm	,	float fCurrent,
						uint16_t usSetpointInPwm		,	uint16_t *pusSetpointInmA		, eBool_t  bIsStep50mA,
						uint16_t *pusStepsNumber		,	eBool_t  *pbIncrease			, eBool_t bWavelengthIs1536, eBool_t bHpaReadyForSecondStep);

/**
* @brief      sequence between setup and run of the ACC 
* @param[in]  PumpType: The pump laser : Sm, mm1 or mm2.
* @param[in]  usLastSetpointInPwm: last setpoint executed.
* @param[in]  fCurrent: actual current of the diode.
* @param[in]  bEnable: enable laser
* @param[in]  usSetpointInPwm: new setpoint received.
* @param[in]  bIsStep50mA: step for ramp up is 50 mA.
* @param[in]  bWavelengthIs1536: input wavelength is 1536.
* @param[in]  bHpaReadyForSecondStep:  the first SM has reached the min threshold current value, in order to continue with further stages
* @param[out]  pbIncrease: new setpoint received is bigger that the older one.
* @param[out] pusStepsNumber: the number of steps
* @return     none
**/
void vBoosterAccManager(	ePumpType_t  ePumpType		,	uint16_t usLastSetpointInPwm	,	float fCurrent , eBool_t bEnable , 
							uint16_t usSetpointInPwm		,	uint16_t *pusSetpointInmA		, eBool_t  bIsStep50mA,
							uint16_t *pusStepsNumber		,	eBool_t  *pbIncrease			, eBool_t bWavelengthIs1536, eBool_t bHpaReadyForSecondStep);

#endif /* BOOSTERACCSM_H_ */