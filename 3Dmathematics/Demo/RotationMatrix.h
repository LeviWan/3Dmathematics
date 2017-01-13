
#ifndef __ROTATIONMATRIX_H_INCLUDED__  //头文件的保护
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

	//将矩阵设为单位矩阵
	void identity();

	//惯性坐标系旋转到物体坐标系
	//v是惯性坐标系的向量，得到的向量为物体坐标系的向量
	Vector3 insertialToObject(const Vector3 &v)const;
	//物体坐标系旋转到惯性坐标系
	//此时用到的旋转矩阵是之前旋转矩阵的逆，但是由于是正交矩阵，所以也是之前的转置
	Vector3 objectToInsertial(const Vector3 &v)const;

	//欧拉角
	void setup(const EulerAngles &orientation);

	//惯性坐标系到物体坐标系的转化，矩阵==>四元数
	void fromInertialToObjectQuaternion(const Quaternion &q);
	
	//从物体坐标系到惯性坐标系
	void fromObjectToInertialQuaternion(const Quaternion &q);
};

#endif