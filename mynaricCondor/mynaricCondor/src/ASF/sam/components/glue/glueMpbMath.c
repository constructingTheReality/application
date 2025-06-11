/**
* @file 		GlueMpbMath.c
* @brief		GlueMpbMath source file.
* @author		juan
* @date			Created on 2021-03-8
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
#include "glue.h"
#include <math.h>
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

eBool_t eMpbMathFloatIsNaN( float xValue )
{
	if( isnan( xValue ) )
	{
		return eTrue;
	}
	else
	{
		return eFalse;
	}
}
/*----------------------------------------------------------------------------*/

eBool_t eMpbMathFloatIsInfinity( float xValue )
{
	if( isinf( xValue ) )
	{
		return eTrue;
	}
	else
	{
		return eFalse;
	}
}
/*----------------------------------------------------------------------------*/

eBool_t eMpbMathDoubleIsNaN( double xValue )
{
	if( isnan( xValue ) )
	{
		return eTrue;
	}
	else
	{
		return eFalse;
	}
}
/*----------------------------------------------------------------------------*/

eBool_t eMpbMathDoubleIsInfinity( double xValue )
{
	if( isinf( xValue ) )
	{
		return eTrue;
	}
	else
	{
		return eFalse;
	}
}
/*----------------------------------------------------------------------------*/

