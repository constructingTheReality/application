/*
 * boosterAccMm2.h
 *
 * Created: 6/26/2024 4:22:23 PM
 *  Author: j.castano
 */ 


#ifndef BOOSTERACCMM2_H_
#define BOOSTERACCMM2_H_


#define		CURRENT_INCREASE_BY_STEP_IN_MA_MM_HPA1_ACC  ( 500 )



typedef struct {
	uint16_t usStepsNumberMmHpa2;
	eBool_t  bIncreaseMmHpa2;
	uint16_t usSetpointInmAMmHpa2;
	uint16_t  usCurrentMm2Read;
	
	
	
}AccDataMm2_t;


void vBoosterAccMm2Run(AccDataMm2_t *pAccDataMm2);


#endif /* BOOSTERACCMM2_H_ */