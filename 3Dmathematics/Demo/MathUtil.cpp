#include "MathUtil.h"
#include <math.h>

float wrapPi(float theta)
{
	//把一个角度限制到正负180度
	theta += kPI;
	theta -= floor(theta*k1Over2PI)*k2PI;
	theta -= kPI;
	return theta;
}

float safeAcos(float x)
{
	if (x <= -1.0f)
	{
		return kPI;
	}
	if (x >= 1.0f)
	{
		return 0.0f;
	}

	return acos(x);
}