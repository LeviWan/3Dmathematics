
#ifndef __ROTATIONMATRIX_H_INCLUDED__  //ͷ�ļ��ı���
#define __ROTATIONMATRIX_H_INCLUDED__

#include "Vector3.h";

class EulerAngles;
class Quaternion;
class RotationMatrix
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	//��������Ϊ��λ����
	void identity();

	//��������ϵ��ת����������ϵ
	//v�ǹ�������ϵ���������õ�������Ϊ��������ϵ������
	Vector3 insertialToObject(const Vector3 &v)const;
	//��������ϵ��ת����������ϵ
	//��ʱ�õ�����ת������֮ǰ��ת������棬����������������������Ҳ��֮ǰ��ת��
	Vector3 objectToInsertial(const Vector3 &v)const;

	//ŷ����
	void setup(const EulerAngles &orientation);

	//��������ϵ����������ϵ��ת��������==>��Ԫ��
	void fromInertialToObjectQuaternion(const Quaternion &q);
	
	//����������ϵ����������ϵ
	void fromObjectToInertialQuaternion(const Quaternion &q);
};

#endif