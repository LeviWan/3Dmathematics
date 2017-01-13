
#ifndef __EULERANGLES_H_INCLUDED__  //ͷ�ļ��ı���
#define __EULERANGLES_H_INCLUDED__

#include "RotationMatrix.h"
#include "Matrix4x3.h"
class Quaternion;
class EulerAngles
{
public:
	float heading; //��ת�ᣬY��
	float pitch;   //��ת�ᣬX��
	float bank;		//��ת�ᣬZ��

	//���캯��
	EulerAngles(){}

	EulerAngles(float h, float p, float b) :heading(h), pitch(p), bank(b){}

	void canonize();//������ת�Ƕ�

	//��ת����ת��Ϊŷ���ǣ���ת�������ж�������߹�������ϵ�ĺ�����
	void fromRotationMatrix(const RotationMatrix &m);

	//������������ϵ�ľ���ת��Ϊŷ����
	void fromObjectToWorldMatrix(const Matrix4x3 &m);
	//���絽��������ϵ�ľ���ת��Ϊŷ����
	void fromWorldToObjectMatrix(const Matrix4x3 &m);

	//��Ԫ��ת����ŷ����,��������ϵ�任����������ϵ
	void fromObjectToInertialQuaternion(const Quaternion &q);
	void fromInertialToObjectQuaternion(const Quaternion &q);

};
#endif