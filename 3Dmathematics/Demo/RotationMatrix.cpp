#include "RotationMatrix.h";
#include "EulerAngles.h"
#include "MathUtil.h"
#include "Quaternion.h"
//把矩阵设为单位矩阵，对角线元素为1
void RotationMatrix::identity()
{
	m11 = 1.0f;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f;    m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f;   m33 = 1.0f;

}

Vector3 RotationMatrix::insertialToObject(const Vector3 &v)const
{
	return Vector3(
		m11*v.x + m21*v.y + m31*v.z,
		m12*v.x + m22*v.y + m32*v.z,
		m13*v.x + m23*v.y + m33*v.z
		);
}

Vector3 RotationMatrix::objectToInsertial(const Vector3 &v)const
{
	return Vector3(
		m11*v.x + m12*v.y + m13*v.z,
		m21*v.x + m22*v.y + m23*v.z,
		m31*v.x + m32*v.y + m33*v.z
		);
}

//欧拉角,把欧拉角转换为旋转矩阵
void RotationMatrix::setup(const EulerAngles &ororientation)
{
	//惯性坐标系到物理坐标系
	//三个轴的欧拉角分别对应着三个轴的旋转矩阵
	float sh, ch, sp, cp, sb, cb;
	sinCos(&sh, &ch, ororientation.heading); //表示把sh，ch的指针，sh=sin（heading），ch=cos（heading）
	sinCos(&sp, &cp, ororientation.pitch);
	sinCos(&sb, &cb, ororientation.bank);

	m11 = ch*cb + sh*sp*sb;  m12 = sh*sp*cb - ch*sb;  m13 = sh*cp;
	m21 = sb*cp;             m22 = cb*cp;             m23 = -sp;
	m31 = ch*sp*sb - sh*cb;  m32 = sb*sh + ch*sp*sb;  m33 = ch*cp;

}

//四元数转矩阵
void RotationMatrix::fromInertialToObjectQuaternion(const Quaternion &q)
{
	m11 = 1.0f - 2.0f*(q.y*q.y + q.z*q.z);
	m12 = 2.0f*(q.x*q.y + q.w*q.z);
	m13 = 2.0f*(q.x*q.z - q.w*q.y);

	m21 = 2.0f*(q.x*q.y - q.w*q.z);
	m22 = 1.0f - 2.0f*(q.x*q.x + q.z*q.z);
	m23 = 2.0f*(q.y*q.z + q.w*q.x);

	m31 = 2.0f*(q.x*q.z + q.w*q.y);
	m32 = 2.0f*(q.y*q.z - q.w*q.x);
	m33 = 1 - 2.0f*(q.x*q.x + q.y*q.y);
}

void RotationMatrix::fromObjectToInertialQuaternion(const Quaternion &q)
{
	//之前矩阵的转置

	m11 = 1.0f - 2.0f*(q.y*q.y + q.z*q.z);
	m12 = 2.0f*(q.x*q.y - q.w*q.z);
	m13 = 2.0f*(q.x*q.z + q.w*q.y);

	
	m21 = 2.0f*(q.x*q.y + q.w*q.z);
	m22 = 1.0f - 2.0f*(q.x*q.x + q.z*q.z);
	m23 = 2.0f*(q.y*q.z - q.w*q.x);

	
	m31 = 2.0f*(q.x*q.z - q.w*q.y);
	m32 = 2.0f*(q.y*q.z + q.w*q.x);
	
	m33 = 1 - 2.0f*(q.x*q.x + q.y*q.y);
}
