/*
 * boosterAccRun.h
 *
 * Created: 7/3/2024 2:53:51 PM
 *  Author: j.castano
 */ 


#ifndef BOOSTERACCRUN_H_
#define BOOSTERACCRUN_H_


#define		BOOSTER_ACC_RUNNER_CURRENT_INCREASE_BY_STEP_IN_MA_HPA1  ( 100 )


typedef struct {
	uint16_t usStepsNumberHpa1;
	eBool_t  bIncreaseHpa1;
	uint16_t usSetpointInmAHpa1;
	uint16_t  usCurrentRead;
	
	
	
}AccDataSm1_t;


void vBoosterAccSmRun(AccDataSm1_t *pAccDataSm1);




#endif /* BOOSTERACCRUN_H_ */