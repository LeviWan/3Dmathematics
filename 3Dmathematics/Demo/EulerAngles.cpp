#include "EulerAngles.h"
#include <math.h>
#include "MathUtil.h"
#include "Quaternion.h"
//通过限制欧拉角的转角，可以稍微避免产生万向锁问题
void EulerAngles::canonize()
{
	pitch = wrapPi(pitch);
	if (pitch<kPIOver2)
	{
		pitch = -kPI - pitch;
		heading += kPI;
		bank += kPI;
	}
	else if (pitch>kPIOver2)
	{
		pitch = kPI - pitch;
		heading += kPI;
		bank += kPI;
	}

	//检查万向锁
	if (fabs(pitch)>kPIOver2-1e-4)
	{
		heading += bank;
		bank = 0.0f;

	}
	else
	{
		bank = wrapPi(bank);
	}

	heading = wrapPi(heading);
}

void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
	//sp=sin(p)
	float sp = -m.m32;
	
	//pitch角等于正负90度时，会发生万向锁
	//由于是float类型，也不可能大于1，所以当它非常接近于1时，我们就断定发生了万向锁
	if (fabs(sp)>0.99999f)
	{
		pitch = kPIOver2*sp;
		bank = 0.0f;
		heading = atan2(-m.m23,m.m11);
	}
	else //没有发生万向锁
	{
		heading = atan2(m.m31,m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12,m.m22);
	}
}

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
{
	//是之前的转置，之前是32，现在就是23
	float sp = -m.m23;

	//pitch角等于正负90度时，会发生万向锁
	//由于是float类型，也不可能大于1，所以当它非常接近于1时，我们就断定发生了万向锁
	if (fabs(sp)>0.99999f)
	{
		pitch = kPIOver2*sp;
		bank = 0.0f;
		heading = atan2(-m.m32, m.m11);  //-m.m31
	}
	else //没有发生万向锁
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
{
	////同之前的是一样的
	//float sp = -m.m23;

	////pitch角等于正负90度时，会发生万向锁
	////由于是float类型，也不可能大于1，所以当它非常接近于1时，我们就断定发生了万向锁
	//if (fabs(sp)>0.99999f)
	//{
	//	pitch = kPIOver2*sp;
	//	bank = 0.0f;
	//	heading = atan2(-m.m32, m.m11);  //-m.m31
	//}
	//else //没有发生万向锁
	//{
	//	heading = atan2(m.m13, m.m33);
	//	pitch = asin(sp);
	//	bank = atan2(m.m21, m.m22);
	//}

	float sp = -m.m32;

	//pitch角等于正负90度时，会发生万向锁
	//由于是float类型，也不可能大于1，所以当它非常接近于1时，我们就断定发生了万向锁
	if (fabs(sp)>0.99999f)
	{
		pitch = kPIOver2*sp;
		bank = 0.0f;
		heading = atan2(-m.m23, m.m11);
	}
	else //没有发生万向锁
	{
		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}
}

//物体到惯性
void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
{
	float sp = -2.0f*(q.y*q.z - q.w*q.x);
	//检查是否发生万向锁
	if (fabs(sp)>0.9999f)
	{
		//发生了万向锁
		pitch = kPIOver2*sp;
		heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		//没有发生万向锁
		pitch = asin(sp);
		heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

//惯性到物体
void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
{
	//共轭关系，X,Y,Z为负
	float sp = -2.0f*(q.y*q.z + q.w*q.x);
	//检查是否发生万向锁
	if (fabs(sp)>0.9999f)
	{
		//发生了万向锁
		pitch = kPIOver2*sp;
		heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		//没有发生万向锁
		pitch = asin(sp);
		heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}