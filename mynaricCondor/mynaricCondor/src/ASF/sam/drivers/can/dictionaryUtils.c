#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dictionaryUtils.h"




//float mpb_math_fdiv( float numerator, float denominator );

float mpb_math_fdiv( float numerator, float denominator )
{
	if( numerator >= 0 )
	{
		numerator += (denominator/2);			// add half of divider for rounding
	}
	else
	{
		numerator -= (denominator/2);			// remove half of divider for rounding
	}
	return numerator / denominator;
}


float mpb_math_flinear_approx( float x1, float y1, float x2, float y2, float x, mpb_coerced_t coerce )
{
	float y, x21;

	/* get slope denominator */
	x21 = x2 - x1;
	/* prevent division by 0 */
	if( x21 == 0 )
	{
		return x;
	}
	/* coerce input/output value */
	if( coerce == coerced )
	{
		/* if positive slope */
		if( x21 >= 0 )
		{
			if( x <= x1 )
			{
				return y1;
			}
			else if( x >= x2 )
			{
				return y2;
			}
		}
		/* else negative slope */
		else
		{
			if( x >= x1 )
			{
				return y1;
			}
			else if( x <= x2 )
			{
				return y2;
			}
		}
	}
	/* get input offset */
	y = (x - x1);
	/* multiply by slope numerator */
	y *= (y2 - y1);
	/* divide by slope denominator */
	y = mpb_math_fdiv( y, x21 );
	/* add output offset */
	y += y1;
	/* return value */
	return y;
}


eBool_t mpb_float1_minor_than_float2(float float1, float float2, unsigned int precision)
{
	int int1, int2;
	eBool_t bReturn = eFalse;
	
	if (float1 > 0)
	int1 = (int)(float1 * precision + .5);
	else
	int1 = (int)(float1 * precision - .5);

	if (float2 > 0)
	int2 = (int)(float2 * precision + .5);
	else
	int2 = (int)(float2 * precision - .5);

	
	if(int1 < int2)
	{
		bReturn = eTrue;
	}
	return bReturn;
}

eBool_t mpb_float1_equal_to_float2(float float1, float float2, unsigned int precision)
{
	int int1, int2;
	eBool_t bReturn = eFalse;
	
	if (float1 > 0)
	int1 = (int)(float1 * precision + .5);
	else
	int1 = (int)(float1 * precision - .5);

	if (float2 > 0)
	int2 = (int)(float2 * precision + .5);
	else
	int2 = (int)(float2 * precision - .5);

	
	if(int1 ==  int2)
	{
		bReturn = eTrue;
	}
	return bReturn;
}
/*int main()
{
	float fdBbmCoertedTofloat255,fdBmRecuperated;

	float x1 = -30.0;
	float y1 = 0.0;
	float x2 = 38;
	float y2 = 255;
	static float fdBmFromMpbController = 36.0;
	mpb_coerced_t coerce = coerced;

	float xx1 = 0.0;
	float xy1 = -30.0;
	float xx2 = 255;
	float xy2 = 38;
	float ftypeCastToChar = 0.0;

	int debugMonitor;

	//char char1 = (char)x;
	for( int f = 0; f<100; f++)
	{
		fdBmFromMpbController = fdBmFromMpbController + 0.1;

		fdBbmCoertedTofloat255 = mpb_math_flinear_approx(  x1,  y1,  x2,  y2,  fdBmFromMpbController,  coerce );



		uint8_t test = (uint8_t)(fdBbmCoertedTofloat255);
		ftypeCastToChar = (float)test;


		fdBmRecuperated = mpb_math_flinear_approx(  xx1,  xy1,  xx2,  xy2,  ftypeCastToChar,  coerce );

		debugMonitor++;
	}
	//  printf("Hello world!\n",x);
	return 0;
}*/

