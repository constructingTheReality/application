/*
 * canDictionary.c
 *
 * Created: 1/19/2023 8:52:20 AM
 *  Author: j.castano
 */ 

#include "canDictionary.h"
#include "can409Packet.h"


#define  FLOAT_ADJUST  0.5
#define  FLOAT_ADJUST_408  0.51
#define  FLOAT_ADJUST_408a  0.47
#define  FLOAT_ADJUST_ENCODE  12.0



void vInitCanImage( void )
{
	vInit404CanImage();
	vInit405CanImage();
	vInit406CanImage();
	vInit407CanImage();
	vInit408CanImage();
	vInit010CanImage();
	vInit401CanImage();
	vInit402CanImage();
	vInit403CanImage();
	vInit409CanImage();
	vInit411CanImage();
	vInit412CanImage();
	vInit413CanImage();
	vInit414CanImage();
	vInit415CanImage();
	vInit40ACanImage();
	vInit410CanImage();
	vInit423CanImage();
	vInit426CanImage();
	vInit428CanImage();

}


/*-------------------------------------------------------------*/





