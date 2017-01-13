#include "Vector3.h";
#include "Matrix4x3.h";
#include "MathUtil.h";

#include <assert.h>  

//��ת����
//axis ָ����ת�ᣬΪ1��X�ᣬ2��Y��3��Z
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

//���ž���
//Kx��Ky,Kz�ֱ��������X,Y,Z���ŵı���

void Matrix4x3::setupScale(const float Kx, const float Ky, const  float Kz)
{
	m11 = Kx;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f; m22 = Ky;    m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f;  m33 = Kz;
}

//ͶӰ��������ͶӰ
//n��ֱ����ҪͶӰ��ƽ�棬��nΪ��λ����
void Matrix4x3::setuoProject(const Vector3 &n)
{
	assert(fabs(n*n - 1.0f) < 0.01f); //����Ƿ�Ϊ��λ����

	//�ȼ���Խ��ߵ�Ԫ��
	m11 = 1.0f - n.x*n.x;
	m22 = 1.0f - n.y*n.y;
	m33 = 1.0f - n.z*n.z;
	//�ڼ�������Ԫ��
	m12 = m21 = -n.x*n.y;
	m13 = m31 = -n.x*n.z;
	m23 = m32 = -n.y*n.z;

	//ͶӰ�任ʱ��û�з���ƽ��
	tx = ty = tz = 0.0f;
}

//x,y,zΪ����ϵ��
void Matrix4x3::setupScale(const Vector3 &s)
{
	m11 = s.x;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f; m22 = s.y;    m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f;   m33 = s.z;

	//���ű任ʱ��û�з���ƽ��
	tx = ty = tz = 0.0f;	
}

//����
void Matrix4x3::setupReflect(int axis ,float k)
{
	switch (axis)
	{
	case 1:  //kΪ0ʱ��X���귢������   ��Ϊ0���ǣ�X=k��ƽ�淢������
		m11 = -1.0f;  m12 = 0.0f;   m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f;    m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f;   m33 = 1.0f;

		tx = 2.0f*k;
		ty = 0.0f;
		tz = 0.0f;
		break;
	case 2:  //kΪ0ʱ��Y���귢������   ��Ϊ0���ǣ�Y=k��ƽ�淢������
		m11 = 1.0f;  m12 = 0.0f;   m13 = 0.0f;
		m21 = 0.0f; m22 = -1.0f;    m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f;   m33 = 1.0f;

		tx = 0.0f;
		ty = 2.0f*k;
		tz = 0.0f;
		break;
	case 3:  //kΪ0ʱ��Z���귢������   ��Ϊ0���ǣ�Z=k��ƽ�淢������
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
//������ƽ��ľ���
//n��ֱ�ھ���ƽ��ĵ�λ����
void Matrix4x3::setupReflect(const Vector3 &n)
{
	assert(fabs(n*n - 1.0f) < 0.01f); //����Ƿ�Ϊ��λ����

	//�������ʽ����Ϊ�ṫʽ���ظ�ʹ�õ���
	float ax = -2.0f*n.x;
	float ay = -2.0f*n.y;
	float az = -2.0f*n.z;

	//�ȼ���Խ��ߣ���Ϊ�����Ķ�����ȹ�ϵ,�ԳƵ�
	m11 = 1.0f + ax*n.x;  
	m22 = 1.0f + ay*n.y;
	m33 = 1.0f + az*n.z;

	m12 = m21 = ax*n.y;
	m13 = m31 = ax*n.z;
	m23 = m32 = ay*n.z;

	//�����ʱ�򣬰�ƽ������Ϊ0��û��ƽ��
	tx = ty = tz = 0.0f;
}

//�б�
//axisָ�����б�������,s,t�ֱ�Ϊ������������б�ֵ��s��t�������б仡��

void Matrix4x3::setupShear(int axis, float s, float t)
{
	switch (axis)
	{
	case 1: //��x�б�yz��x����
		m11 = 1.0f; m12 = s; m13 = t;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 2:  //��y�б�xz��y����
		m11 = 1.0f; m12 = 0.0f; m13 =0.0f;
		m21 = s; m22 = 1.0f; m23 = t;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 3:  //��z�б�xy��z����
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = t; m33 = 1.0f;
		break;
	default:
		break;
	}
	//�б��ʱ�򣬰�ƽ������Ϊ0��û��ƽ��
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

	//����ƽ�ƵĲ���ҲҪ���

	r.tx = a.tx*b.m11 + a.ty*b.m21 + a.tz*b.m31+b.tx;
	r.ty = a.tx*b.m12 + a.ty*b.m22 + a.tz*b.m32+b.ty;
	r.tz = a.tx*b.m13 + a.ty*b.m23 + a.tz*b.m33+b.tz;

	return r;
}

Vector3   &operator *(const Vector3 &p, const Matrix4x3 &m)
{
	//�������˾���
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

//������������ʽ
float determinant(const Matrix4x3 &m)
{
	return m.m11*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m31 - m.m21*m.m33) + m.m13*(m.m21*m.m32 - m.m22*m.m31);
}

//����������
Matrix4x3 inverse(const Matrix4x3 &m)
{
	float det = determinant(m); //�ȼ�������ʽ

	assert(fabs(det) > 0.000001f);
	//��Ϊ����ʽ����Ϊ0,ֻ�з����������ܼ�����
	//��������ɳ˷�
	float oneOverdet = 1/ det;

	Matrix4x3 r; //�������

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

//����ƽ��Ϊ0
void Matrix4x3::zeroTranslation()
{
	tx = ty = tz = 0.0f;
}

//ֻ����ƽ�ƵĲ���
//������ԭ��3x3�������Ա任��ֵ
void Matrix4x3::setTranslaton(const Vector3 &d)
{
	tx = d.x;
	ty = d.y;
	tz = d.z;
}

//ƽ�Ʊ任����
//�����Ա任�Ĳ�������Ϊ��λ����
//ֻƽ�ƣ�û�����Ա仯  ����׼��ƽ�ƾ���
void Matrix4x3::setupTranslation(const Vector3 &d)
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	//ƽ�ƵĲ���
	tx = d.x;  ty = d.y;  tz = d.z;
}

//����һ��ƽ������
Vector3 getTranslation(const Matrix4x3 &m)
{
	return Vector3(m.tx,m.ty,m.tz);
}