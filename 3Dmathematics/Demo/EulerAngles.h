
#ifndef __EULERANGLES_H_INCLUDED__  //头文件的保护
#define __EULERANGLES_H_INCLUDED__

#include "RotationMatrix.h"
#include "Matrix4x3.h"
class Quaternion;
class EulerAngles
{
public:
	float heading; //旋转轴，Y轴
	float pitch;   //旋转轴，X轴
	float bank;		//旋转轴，Z轴

	//构造函数
	EulerAngles(){}

	EulerAngles(float h, float p, float b) :heading(h), pitch(p), bank(b){}

	void canonize();//限制旋转角度

	//旋转矩阵转换为欧拉角（旋转矩阵里有对物体或者惯性坐标系的函数）
	void fromRotationMatrix(const RotationMatrix &m);

	//物理到世界坐标系的矩阵转换为欧拉角
	void fromObjectToWorldMatrix(const Matrix4x3 &m);
	//世界到物体坐标系的矩阵转换为欧拉角
	void fromWorldToObjectMatrix(const Matrix4x3 &m);

	//四元数转换成欧拉角,物体坐标系变换到惯性坐标系
	void fromObjectToInertialQuaternion(const Quaternion &q);
	void fromInertialToObjectQuaternion(const Quaternion &q);

};
#endif