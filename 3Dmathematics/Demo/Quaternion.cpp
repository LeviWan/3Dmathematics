#include "Quaternion.h"
#include <math.h>
#include <assert.h>
#include "MathUtil.h"
#include "RotationMatrix.h"
#include "EulerAngles.h"
//全局的单位四元数
const Quaternion kQuaternionIdentity = { 1.0f, 0.0f, 0.0f, 0.0f };

//四元数绕X轴旋转
void Quaternion::setToRotateAboutX(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

//四元数绕Y轴旋转
void Quaternion::setToRotateAboutY(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
}

//四元数绕Z轴旋转
void Quaternion::setToRotateAboutZ(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
}

//四元数绕任意轴平面旋转
void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
	assert(fabs(vectorMag(axis) - 1.0f) < 0.01f);

	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sin(thetaOver2);

	w = cos(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;
}

//得到四元数的旋转角
float Quaternion::getRotationAngle() const
{
	float thetaOver2 = safeAcos(w);

	return thetaOver2 * 2.0f;
}

//得到四元数的旋转平面
Vector3 Quaternion::getRotationAxis() const
{
	float sinThetaOver2Sq = 1.0f - w * w;

	float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

	return Vector3(x*oneOverSinThetaOver2,
		y*oneOverSinThetaOver2, z*oneOverSinThetaOver2);
}

Quaternion Quaternion::operator*(const Quaternion &a) const
{
	Quaternion result;

	result.w = w*a.w - x*a.x - y*a.y - z*a.z;
	result.x = w*a.x + x*a.w + z*a.y - y*a.z;
	result.y = w*a.y + y*a.w + x*a.z - z*a.x;
	result.z = w*a.z + z*a.w + y*a.x - x*a.y;

	return result;
}

Quaternion &Quaternion::operator*=(const Quaternion &a)
{
	*this = *this * a;

	return *this;
}

void Quaternion::normalize()
{
	float mag = (float)sqrt(w*w + x*x + y*y + z*z);

	if (mag > 0.0f)
	{
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else
	{
		assert(false);
		identity();
	}
}

//四元数点乘
float dotProduct(const Quaternion &a, const Quaternion &b)
{
	return a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;
}

//四元数的共轭，表示与之前相反的方向旋转
Quaternion conjugate(const Quaternion &q)
{
	Quaternion result;

	result.w = q.w;

	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

//四元数的幂
Quaternion pow(const Quaternion &q, float exponent)
{
	if (fabs(q.w) > 0.9999f)
	{
		return q;
	}

	float alpha = acos(q.w);

	float newAlpha = exponent * alpha;

	Quaternion result;
	result.w = cos(newAlpha);

	float mult = sin(newAlpha) / sin(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;

	return result;
}

//旋转矩形变换到四元数
void Quaternion::fromRotationMatrix(const RotationMatrix &m)
{
	float m11 = m.m11;
	float m12 = m.m12;
	float m13 = m.m13;

	float m21 = m.m21;
	float m22 = m.m22;
	float m23 = m.m23;

	float m31 = m.m31;
	float m32 = m.m32;
	float m33 = m.m33;

	//先计算出谁最大
	float fourWSquareMinus1 = m11 + m22 + m33;
	float fourXSquareMinus1 = m11 - m22 - m33;
	float fourYSquareMinus1 = m22 - m11 - m33;
	float fourZSquareMinus1 = m33 - m11 - m22;

	//找出最大的是谁
	//假设最大的是W
	int biggestIndex = 0;
	float fourBiggestSquaredMinus1 = fourWSquareMinus1;
	if (fourXSquareMinus1 > fourBiggestSquaredMinus1)
	{
		//如果X比W大，则把X变为最大的
		fourBiggestSquaredMinus1 = fourXSquareMinus1;
		biggestIndex = 1;
	}
	//在检查Y是不是最大
	if (fourYSquareMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquareMinus1;
		biggestIndex = 2;
	}
	//再检查Z
	if (fourZSquareMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquareMinus1;
		biggestIndex = 3;
	}
	//把最大的数算出来
	float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f)*0.5f;
	float mult = 0.25f / biggestVal;
	//通过索引检查谁是最大的
	switch (biggestIndex)
	{
	case 0:
		//W最大
		w = biggestVal;
		x = (m23 - m32)*mult;
		y = (m31 - m13)*mult;
		z = (m12 - m21)*mult;
		break;
	case 1:
		//X最大
		x = biggestVal;
		w = (m23 - m32)*mult;
		y = (m12 + m21)*mult;
		z = (m31 + m13)*mult;
		break;
	case 2:
		//Y最大
		y = biggestVal;
		w = (m31 - m13)*mult;
		x = (m12 + m21)*mult;
		z = (m23 + m32)*mult;
		break;
	case 3:
		//Z最大
		z = biggestVal;
		w = (m12 - m21)*mult;
		x = (m31 + m13)*mult;
		y = (m23 + m32)*mult;
		break;
	default:
		break;
	}
}

//欧拉角到四元数------物体到惯性
void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{
	//欧拉角的局部变量，简化计算
	float sb, sh, sp;
	float cb, ch, cp;

	sinCos(&sp, &cp, orientation.pitch*0.5f);
	sinCos(&sb, &cb, orientation.bank*0.5f);
	sinCos(&sh, &ch, orientation.heading*0.5f);

	w = ch*cp*cb + sh*sp*sb;
	x = ch*sp*cb + sh*cp*sb;
	y = sh*cp*cb - ch*sp*sb;
	z = ch*cp*sb - sh*sp*cb;

}

//欧拉角到四元数------惯性到物体
void Quaternion::setToRotateInertialToObject(const EulerAngles &orientation)
{
	//是之前的共轭

	//欧拉角的局部变量，简化计算
	float sb, sh, sp;
	float cb, ch, cp;

	sinCos(&sp, &cp, orientation.pitch*0.5f);
	sinCos(&sb, &cb, orientation.bank*0.5f);
	sinCos(&sh, &ch, orientation.heading*0.5f);

	w = ch*cp*cb + sh*sp*sb;
	x = -ch*sp*cb - sh*cp*sb;
	y = ch*sp*sb - sh*cp*cb;
	z = sh*sp*cb - ch*cp*sb;
}

//四元数的插值

Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
	//t是0-1之间的系数，首先要判断t
	if (t <= 0.0f) return q0;

	if (t >= 1.0f) return q1;

	//0-1之间时,夹角是点乘得到的，得到的cosW
	float cosOmega = dotProduct(q0,q1);

	//检查q0和q1，检查cosOmega如果小于就把其中一个四元数变为负的

	//先声明一个变量，不要修改穿进来的四元数
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	//避免在插值计算时得到不一致的结果
	if (cosOmega<0.0f)
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}

	//插值计算关键点！  计算出k0以及k1
	float k0, k1;
	//注意！ 如果选择角W很小，也就是v0和v1非常靠近，sinW也就很小，那就接近于除以0了。
	if (cosOmega>0.9999f)
	{
		//用简单 的线性插值
		k0 = 1.0f - t;
		k1 = t;

	}
	else
	{
		//计算sinOmega
		float sinOmega = sqrt(1.0f-cosOmega*cosOmega);

		//计算角度Omega
		float omega = atan2(sinOmega,cosOmega);
		//先计算好除法，后面直接相乘就行
		float oneOverSinOmega = 1.0f / sinOmega;

		k0 = sin((1.0 - t)*omega)*oneOverSinOmega;
		k1 = sin(t*omega)*oneOverSinOmega;

	

	}
	//插值得到一个新的四元数
	Quaternion result;
	result.x = k0*q0.x + k1*q1x;
	result.y = k0*q0.y + k1*q1y;
	result.z = k0*q0.z + k1*q1z;
	result.w = k0*q0.w + k1*q1w;

	return result;
}


