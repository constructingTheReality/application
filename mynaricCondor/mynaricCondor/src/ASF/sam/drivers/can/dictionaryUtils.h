/**
* @file			dictionaryUtils.h
* @brief
* @author		juan
* @date			Created on 2023-xx-xx
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Header guard ------------------------------------------------------------- */
#ifndef DICTIONARYUTILS_H_
#define DICTIONARYUTILS_H_
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

/**
* @brief	internal structures
*/
typedef union
{
	float			fLocalValue;
	uint32_t		ulLocalValue;
}fValue_t;

typedef enum
{
	coerced		,
	not_coerced
}
mpb_coerced_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
//float mpb_math_fdiv( float numerator, float denominator );
/**
* @brief		Initialize the timebase structure
* @param[in]	pxTimeBase: pointer to the timebase structure
* @param[in]	ucTickPerMs: the number of tick per miliseconds
* @return       Success or library error message
*/
float mpb_math_fdiv( float numerator, float denominator );

/**
* @brief		Initialize the timebase structure
* @param[in]	pxTimeBase: pointer to the timebase structure
* @param[in]	ucTickPerMs: the number of tick per miliseconds
* @return       Success or library error message
*/

float mpb_math_flinear_approx( float x1, float y1, float x2, float y2, float x, mpb_coerced_t coerce );


eBool_t mpb_float1_minor_than_float2(float float1, float float2, unsigned int precision);

eBool_t mpb_float1_equal_to_float2(float float1, float float2, unsigned int precision);

#endif /* DICTIONARYUTILS_H_ */