#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__

#include "Vector3.h"
class RotationMatrix;
class EulerAngles;
class Quaternion
{
public:

	float w, x, y, z;

	void identity() { w = 1.0f; x = y = z = 0.0f; }

	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const Vector3 &axis, float theta);

	float getRotationAngle() const;
	Vector3 getRotationAxis() const;

	Quaternion operator *(const Quaternion &a) const;
	Quaternion &operator *=(const Quaternion &a);

	void normalize();

	//从旋转矩阵变换到四元数
	void fromRotationMatrix(const RotationMatrix &m);
	//欧拉角转换成四元数
	//物体坐标系到惯性坐标系
	void setToRotateObjectToInertial(const EulerAngles &orientation);
	//惯性到物体
	void setToRotateInertialToObject(const EulerAngles &orientation);


};

extern const Quaternion kQuaternionIdentity;
extern float dotProduct(const Quaternion &a, const Quaternion &b);
extern Quaternion conjugate(const Quaternion &q);
extern Quaternion pow(const Quaternion &q, float exponent);
//四元数的插值运算
extern Quaternion slerp(const Quaternion &q0, const Quaternion &q1,float t);

#endif