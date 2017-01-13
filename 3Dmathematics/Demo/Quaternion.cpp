#include "Quaternion.h"
#include <math.h>
#include <assert.h>
#include "MathUtil.h"
#include "RotationMatrix.h"
#include "EulerAngles.h"
//ȫ�ֵĵ�λ��Ԫ��
const Quaternion kQuaternionIdentity = { 1.0f, 0.0f, 0.0f, 0.0f };

//��Ԫ����X����ת
void Quaternion::setToRotateAboutX(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

//��Ԫ����Y����ת
void Quaternion::setToRotateAboutY(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
}

//��Ԫ����Z����ת
void Quaternion::setToRotateAboutZ(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
}

//��Ԫ����������ƽ����ת
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

//�õ���Ԫ������ת��
float Quaternion::getRotationAngle() const
{
	float thetaOver2 = safeAcos(w);

	return thetaOver2 * 2.0f;
}

//�õ���Ԫ������תƽ��
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

//��Ԫ�����
float dotProduct(const Quaternion &a, const Quaternion &b)
{
	return a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;
}

//��Ԫ���Ĺ����ʾ��֮ǰ�෴�ķ�����ת
Quaternion conjugate(const Quaternion &q)
{
	Quaternion result;

	result.w = q.w;

	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

//��Ԫ������
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

//��ת���α任����Ԫ��
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

	//�ȼ����˭���
	float fourWSquareMinus1 = m11 + m22 + m33;
	float fourXSquareMinus1 = m11 - m22 - m33;
	float fourYSquareMinus1 = m22 - m11 - m33;
	float fourZSquareMinus1 = m33 - m11 - m22;

	//�ҳ�������˭
	//����������W
	int biggestIndex = 0;
	float fourBiggestSquaredMinus1 = fourWSquareMinus1;
	if (fourXSquareMinus1 > fourBiggestSquaredMinus1)
	{
		//���X��W�����X��Ϊ����
		fourBiggestSquaredMinus1 = fourXSquareMinus1;
		biggestIndex = 1;
	}
	//�ڼ��Y�ǲ������
	if (fourYSquareMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquareMinus1;
		biggestIndex = 2;
	}
	//�ټ��Z
	if (fourZSquareMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquareMinus1;
		biggestIndex = 3;
	}
	//�������������
	float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f)*0.5f;
	float mult = 0.25f / biggestVal;
	//ͨ���������˭������
	switch (biggestIndex)
	{
	case 0:
		//W���
		w = biggestVal;
		x = (m23 - m32)*mult;
		y = (m31 - m13)*mult;
		z = (m12 - m21)*mult;
		break;
	case 1:
		//X���
		x = biggestVal;
		w = (m23 - m32)*mult;
		y = (m12 + m21)*mult;
		z = (m31 + m13)*mult;
		break;
	case 2:
		//Y���
		y = biggestVal;
		w = (m31 - m13)*mult;
		x = (m12 + m21)*mult;
		z = (m23 + m32)*mult;
		break;
	case 3:
		//Z���
		z = biggestVal;
		w = (m12 - m21)*mult;
		x = (m31 + m13)*mult;
		y = (m23 + m32)*mult;
		break;
	default:
		break;
	}
}

//ŷ���ǵ���Ԫ��------���嵽����
void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{
	//ŷ���ǵľֲ��������򻯼���
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

//ŷ���ǵ���Ԫ��------���Ե�����
void Quaternion::setToRotateInertialToObject(const EulerAngles &orientation)
{
	//��֮ǰ�Ĺ���

	//ŷ���ǵľֲ��������򻯼���
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

//��Ԫ���Ĳ�ֵ

Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
	//t��0-1֮���ϵ��������Ҫ�ж�t
	if (t <= 0.0f) return q0;

	if (t >= 1.0f) return q1;

	//0-1֮��ʱ,�н��ǵ�˵õ��ģ��õ���cosW
	float cosOmega = dotProduct(q0,q1);

	//���q0��q1�����cosOmega���С�ھͰ�����һ����Ԫ����Ϊ����

	//������һ����������Ҫ�޸Ĵ���������Ԫ��
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	//�����ڲ�ֵ����ʱ�õ���һ�µĽ��
	if (cosOmega<0.0f)
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}

	//��ֵ����ؼ��㣡  �����k0�Լ�k1
	float k0, k1;
	//ע�⣡ ���ѡ���W��С��Ҳ����v0��v1�ǳ�������sinWҲ�ͺ�С���Ǿͽӽ��ڳ���0�ˡ�
	if (cosOmega>0.9999f)
	{
		//�ü� �����Բ�ֵ
		k0 = 1.0f - t;
		k1 = t;

	}
	else
	{
		//����sinOmega
		float sinOmega = sqrt(1.0f-cosOmega*cosOmega);

		//����Ƕ�Omega
		float omega = atan2(sinOmega,cosOmega);
		//�ȼ���ó���������ֱ����˾���
		float oneOverSinOmega = 1.0f / sinOmega;

		k0 = sin((1.0 - t)*omega)*oneOverSinOmega;
		k1 = sin(t*omega)*oneOverSinOmega;

	

	}
	//��ֵ�õ�һ���µ���Ԫ��
	Quaternion result;
	result.x = k0*q0.x + k1*q1x;
	result.y = k0*q0.y + k1*q1y;
	result.z = k0*q0.z + k1*q1z;
	result.w = k0*q0.w + k1*q1w;

	return result;
}


