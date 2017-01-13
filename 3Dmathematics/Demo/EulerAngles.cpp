#include "EulerAngles.h"
#include <math.h>
#include "MathUtil.h"
#include "Quaternion.h"
//ͨ������ŷ���ǵ�ת�ǣ�������΢�����������������
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

	//���������
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
	
	//pitch�ǵ�������90��ʱ���ᷢ��������
	//������float���ͣ�Ҳ�����ܴ���1�����Ե����ǳ��ӽ���1ʱ�����ǾͶ϶�������������
	if (fabs(sp)>0.99999f)
	{
		pitch = kPIOver2*sp;
		bank = 0.0f;
		heading = atan2(-m.m23,m.m11);
	}
	else //û�з���������
	{
		heading = atan2(m.m31,m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12,m.m22);
	}
}

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
{
	//��֮ǰ��ת�ã�֮ǰ��32�����ھ���23
	float sp = -m.m23;

	//pitch�ǵ�������90��ʱ���ᷢ��������
	//������float���ͣ�Ҳ�����ܴ���1�����Ե����ǳ��ӽ���1ʱ�����ǾͶ϶�������������
	if (fabs(sp)>0.99999f)
	{
		pitch = kPIOver2*sp;
		bank = 0.0f;
		heading = atan2(-m.m32, m.m11);  //-m.m31
	}
	else //û�з���������
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
{
	////֮ͬǰ����һ����
	//float sp = -m.m23;

	////pitch�ǵ�������90��ʱ���ᷢ��������
	////������float���ͣ�Ҳ�����ܴ���1�����Ե����ǳ��ӽ���1ʱ�����ǾͶ϶�������������
	//if (fabs(sp)>0.99999f)
	//{
	//	pitch = kPIOver2*sp;
	//	bank = 0.0f;
	//	heading = atan2(-m.m32, m.m11);  //-m.m31
	//}
	//else //û�з���������
	//{
	//	heading = atan2(m.m13, m.m33);
	//	pitch = asin(sp);
	//	bank = atan2(m.m21, m.m22);
	//}

	float sp = -m.m32;

	//pitch�ǵ�������90��ʱ���ᷢ��������
	//������float���ͣ�Ҳ�����ܴ���1�����Ե����ǳ��ӽ���1ʱ�����ǾͶ϶�������������
	if (fabs(sp)>0.99999f)
	{
		pitch = kPIOver2*sp;
		bank = 0.0f;
		heading = atan2(-m.m23, m.m11);
	}
	else //û�з���������
	{
		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}
}

//���嵽����
void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
{
	float sp = -2.0f*(q.y*q.z - q.w*q.x);
	//����Ƿ���������
	if (fabs(sp)>0.9999f)
	{
		//������������
		pitch = kPIOver2*sp;
		heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		//û�з���������
		pitch = asin(sp);
		heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

//���Ե�����
void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
{
	//�����ϵ��X,Y,ZΪ��
	float sp = -2.0f*(q.y*q.z + q.w*q.x);
	//����Ƿ���������
	if (fabs(sp)>0.9999f)
	{
		//������������
		pitch = kPIOver2*sp;
		heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		//û�з���������
		pitch = asin(sp);
		heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}