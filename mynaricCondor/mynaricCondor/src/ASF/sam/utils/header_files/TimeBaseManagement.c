/**
  * @file 			TimeBaseManagement.c
  * @brief			TimeBaseManagement source file.
  * @author			juan andres
  * @date			Created on 3/2/2021
  * @copyright MPB, Montreal, Qc
  * <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
  * <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
  * <center>This document contains confidential and proprietary information
  * of MPB (subject to a non-disclosure agreement) and shall</center>
  * <center>not be disclosed, distributed, or reproduced in whole or in
  * part, without the prior written authorization of MPB.</center>
  *
  **/
  
/* Includes ----------------------------------------------------------------- */

#include "TimeBaseManagement.h"
//#include "mpbTimeBase.h"

/* Private define ----------------------------------------------------------- */

#define TICK_PER_MS ( 1 )

/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

static mpbTimeBase_t xprvMpbTimeBase[ eNumberOfTimeBases ]; 

/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void vTimeBaseManagementInit( void )
{
    for( eTimeBaseID_t eTimeBaseID = ( eTimeBaseID_t )0; eTimeBaseID < eNumberOfTimeBases; eTimeBaseID++ )
    {
        vTimeBaseManagementResetTick( eTimeBaseID );
    }
			
}
/*----------------------------------------------------------------------------*/

void vTimeBaseManagementResetTick( eTimeBaseID_t eTimeBaseID )
{
    eMpbError_t eMpbError;
    
    eMpbError = eMpbTimeBaseInit( &( xprvMpbTimeBase[ eTimeBaseID ] ), TICK_PER_MS );
    if( eMpbError != eSuccess )
    {
        vMpblibsAssertParam( 0 );
    }  
		
		
}
/*----------------------------------------------------------------------------*/

void vTimeBaseManagementTick( void )
{
    eMpbError_t eMpbError;
    
    for( eTimeBaseID_t eTimeBaseID = ( eTimeBaseID_t )0; eTimeBaseID < eNumberOfTimeBases; eTimeBaseID++ )
    {
        eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eTimeBaseID ] ) );
        if( eMpbError != eSuccess )
        {
            vMpblibsAssertParam( 0 );
        }
				
				
				
    }
	

		/*	eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eLEDStatusTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
		
		eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eAlarmTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eSlowSensorsTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eCriticalSensorsTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eContinuosWaveLoopControl ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eModulantWaveLoopControl ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eApcLoopControl ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eTECTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eBEAMTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eLEDStatusTimeBase ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}
					
					eMpbError = eMpbTimeBaseTick( &( xprvMpbTimeBase[ eCommunicacionTimeout ] ) );
					if( eMpbError != eSuccess )
					{
            vMpblibsAssertParam( 0 );
					}*/
					
					
		
		
		
		
				
}
/*----------------------------------------------------------------------------*/

void vTimeBaseManagementGetTick( eTimeBaseID_t eTimeBaseID, uint32_t *pulTick )
{
    eMpbTimeBaseGetMs( &( xprvMpbTimeBase[ eTimeBaseID ] ) , pulTick);
	//eMpbError_t eMpbTimeBaseGetMs( mpbTimeBase_t *pxTimeBase, uint32_t *ulMs );
}
/*---------------------------------------------------------------------------*/
