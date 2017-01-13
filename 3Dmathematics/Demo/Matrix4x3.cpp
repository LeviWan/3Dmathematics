#include "Vector3.h";
#include "Matrix4x3.h";
#include "MathUtil.h";

#include <assert.h>  

//旋转矩阵
//axis 指定旋转轴，为1是X轴，2是Y，3是Z
void Matrix4x3::setRotate(int axis, float theta)
{
	float s, c; //sin ,cos
	sinCos(&s,&c,theta);

	switch (axis)
	{

	case 1:
		m11 = 1.0f;  m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f;  m22 = c;    m23 = s;
		m31 = 0.0f;  m32 = -s;   m33 = c;
		break;
	case 2:
		m11 = c;     m12 = 0.0f; m13 = -s;
		m21 = 0.0f;  m22 = 1;    m23 = 0.0f;
		m31 = s;     m32 = 0;    m33 = c;
		break;
	case 3:
		m11 = c;     m12 = s;      m13 = 0.0f;
		m21 = -s;    m22 = c;      m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;   m33 = 1.0f;
		break;
	default:
		assert(false);
	}

}

//缩放矩阵，
//Kx，Ky,Kz分别代表他将X,Y,Z缩放的比例

void Matrix4x3::setupScale(const float Kx, const float Ky, const  float Kz)
{
	m11 = Kx;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f; m22 = Ky;    m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f;  m33 = Kz;
}

//投影矩阵，正交投影
//n垂直于需要投影的平面，且n为单位向量
void Matrix4x3::setuoProject(const Vector3 &n)
{
	assert(fabs(n*n - 1.0f) < 0.01f); //检查是否为单位向量

	//先计算对角线的元素
	m11 = 1.0f - n.x*n.x;
	m22 = 1.0f - n.y*n.y;
	m33 = 1.0f - n.z*n.z;
	//在计算其他元素
	m12 = m21 = -n.x*n.y;
	m13 = m31 = -n.x*n.z;
	m23 = m32 = -n.y*n.z;

	//投影变换时，没有发生平移
	tx = ty = tz = 0.0f;
}

//x,y,z为缩放系数
void Matrix4x3::setupScale(const Vector3 &s)
{
	m11 = s.x;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f; m22 = s.y;    m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f;   m33 = s.z;

	//缩放变换时，没有发生平移
	tx = ty = tz = 0.0f;	
}

//镜像
void Matrix4x3::setupReflect(int axis ,float k)
{
	switch (axis)
	{
	case 1:  //k为0时，X坐标发生镜像   不为0则是，X=k的平面发生镜像
		m11 = -1.0f;  m12 = 0.0f;   m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f;    m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f;   m33 = 1.0f;

		tx = 2.0f*k;
		ty = 0.0f;
		tz = 0.0f;
		break;
	case 2:  //k为0时，Y坐标发生镜像   不为0则是，Y=k的平面发生镜像
		m11 = 1.0f;  m12 = 0.0f;   m13 = 0.0f;
		m21 = 0.0f; m22 = -1.0f;    m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f;   m33 = 1.0f;

		tx = 0.0f;
		ty = 2.0f*k;
		tz = 0.0f;
		break;
	case 3:  //k为0时，Z坐标发生镜像   不为0则是，Z=k的平面发生镜像
		m11 = 1.0f;  m12 = 0.0f;   m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f;    m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f;   m33 = -1.0f;

		tx = 0.0f;
		ty = 0.0f;
		tz = 2.0f*k;
		break;
	default:
		assert(false);
		break;
	}
}
//对任意平面的镜像
//n垂直于镜像平面的单位向量
void Matrix4x3::setupReflect(const Vector3 &n)
{
	assert(fabs(n*n - 1.0f) < 0.01f); //检查是否为单位向量

	//公共表达式，因为会公式中重复使用到！
	float ax = -2.0f*n.x;
	float ay = -2.0f*n.y;
	float az = -2.0f*n.z;

	//先计算对角线，因为其他的都有相等关系,对称的
	m11 = 1.0f + ax*n.x;  
	m22 = 1.0f + ay*n.y;
	m33 = 1.0f + az*n.z;

	m12 = m21 = ax*n.y;
	m13 = m31 = ax*n.z;
	m23 = m32 = ay*n.z;

	//镜像的时候，把平移设置为0，没有平移
	tx = ty = tz = 0.0f;
}

//切变
//axis指定的切变坐标轴,s,t分别为其他两个轴的切变值，s，t决定了切变弧度

void Matrix4x3::setupShear(int axis, float s, float t)
{
	switch (axis)
	{
	case 1: //用x切变yz，x不变
		m11 = 1.0f; m12 = s; m13 = t;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 2:  //用y切变xz，y不变
		m11 = 1.0f; m12 = 0.0f; m13 =0.0f;
		m21 = s; m22 = 1.0f; m23 = t;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 3:  //用z切变xy，z不变
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = t; m33 = 1.0f;
		break;
	default:
		break;
	}
	//切变的时候，把平移设置为0，没有平移
	tx = ty = tz = 0.0f;
}
Matrix4x3 &operator *(const Matrix4x3 &a, const Matrix4x3 &b)
{
	Matrix4x3 r;
	r.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;
	r.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
	r.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;

	r.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
	r.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
	r.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;

	r.m31 = a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
	r.m32 = a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
	r.m33 = a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;

	//矩阵平移的部分也要相乘

	r.tx = a.tx*b.m11 + a.ty*b.m21 + a.tz*b.m31+b.tx;
	r.ty = a.tx*b.m12 + a.ty*b.m22 + a.tz*b.m32+b.ty;
	r.tz = a.tx*b.m13 + a.ty*b.m23 + a.tz*b.m33+b.tz;

	return r;
}

Vector3   &operator *(const Vector3 &p, const Matrix4x3 &m)
{
	//行向量乘矩阵
	return Vector3(
		p.x*m.m11+p.y*m.m21+p.z*m.m31,
		p.x*m.m12 + p.y*m.m22 + p.z*m.m32,
		p.x*m.m13 + p.y*m.m23 + p.z*m.m33
		);
}
Vector3   &operator *=(Vector3 &p, const Matrix4x3 &m)
{
	p = p*m;
	return p;
}

Matrix4x3 &operator *=(Matrix4x3 &a, const Matrix4x3 &b)
{
	a = a*b;
	return a;
}

//计算矩阵的行列式
float determinant(const Matrix4x3 &m)
{
	return m.m11*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m31 - m.m21*m.m33) + m.m13*(m.m21*m.m32 - m.m22*m.m31);
}

//计算矩阵的逆
Matrix4x3 inverse(const Matrix4x3 &m)
{
	float det = determinant(m); //先计算行列式

	assert(fabs(det) > 0.000001f);
	//因为行列式不能为0,只有非奇异矩阵才能计算逆
	//除法换算成乘法
	float oneOverdet = 1/ det;

	Matrix4x3 r; //矩阵的逆

	r.m11 = (m.m22*m.m33 - m.m23*m.m32)*oneOverdet;
	r.m12 = (m.m13*m.m32 - m.m12*m.m33)*oneOverdet;
	r.m13 = (m.m12*m.m23 - m.m13*m.m22)*oneOverdet;

	r.m21 = (m.m23*m.m31 - m.m21*m.m33)*oneOverdet;
	r.m22 = (m.m11*m.m33 - m.m13*m.m31)*oneOverdet;
	r.m23 = (m.m13*m.m21 - m.m11*m.m23)*oneOverdet;

	r.m31 = (m.m21*m.m32 - m.m22*m.m31)*oneOverdet;
	r.m32 = (m.m12*m.m31 - m.m11*m.m32)*oneOverdet;
	r.m33 = (m.m11*m.m22 - m.m12*m.m21)*oneOverdet;

	return r;

}

//设置平移为0
void Matrix4x3::zeroTranslation()
{
	tx = ty = tz = 0.0f;
}

//只设置平移的部分
//保留了原来3x3矩阵线性变换的值
void Matrix4x3::setTranslaton(const Vector3 &d)
{
	tx = d.x;
	ty = d.y;
	tz = d.z;
}

//平移变换矩阵
//把线性变换的部分设置为单位矩阵
//只平移，没有线性变化  ，标准的平移矩阵
void Matrix4x3::setupTranslation(const Vector3 &d)
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	//平移的部分
	tx = d.x;  ty = d.y;  tz = d.z;
}

//返回一个平移向量
Vector3 getTranslation(const Matrix4x3 &m)
{
	return Vector3(m.tx,m.ty,m.tz);
}