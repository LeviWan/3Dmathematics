#ifndef __MATHUTIL_H_INCLUDED__  //ͷ�ļ��ı���
#define __MATHUTIL_H_INCLUDED__

#include <math.h>
//����Sin��cos��ʹ��ָ�뷵�ؼ�����

const float kPI = 3.14159265f;
const float k2PI = kPI*2.0;
const float kPIOver2 = kPI/2.0;
const float k1Over2PI = 1.0f / k2PI;
const float k1OverPI = 1.0f / kPI;

inline void sinCos(float *returnSin, float *returnCos, float theta)
{
	*returnSin = sin(theta); 
	*returnCos = cos(theta);
}

extern float wrapPi(float theta);

extern float safeAcos(float x);

#endif