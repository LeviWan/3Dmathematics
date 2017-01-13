#ifndef __Matrix4x3_H_INCLUDED__
#define __Matrix4x3_H_INCLUDED__


class Vector3;

class Matrix4x3
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	//��ӵ���һ��Ϊƽ�Ƶ�ƫ������//��ξ���
	float tx, ty, tz;


	//��ת����
	//axis ָ����ת�ᣬΪ1��X�ᣬ2��Y��3��Z
	void setRotate(int axis, float theta);

	//���ž���
	void setupScale(const float Kx, const float Ky, const  float Kz);

	//���԰�����������������һ��������
	void setupScale(const Vector3 &s);

	//ͶӰ������������
	//ʹ����������ֱ��ͶӰƽ�棬�Ϳ���ָ����ҪͶӰ��ƽ���ˣ������԰����������Ϊ�ռ��κ���һ��ƽ���ͶӰ
	void setuoProject(const Vector3 &n);

	//������󣨶Ա�׼��ƽ�棩
	//axisΪ����ƽ����߾��������ᣬ//k��ʾ��ԣ�x��y��z����ƽ������ƽ��
	void setupReflect(int axis,float k);


	//������ƽ��ľ���
	//n��ֱ�ھ���ƽ��ĵ�λ����
	void setupReflect(const Vector3 &n);

	//�б�
	//axisָ�����б�������,s,t�ֱ�Ϊ������������б�ֵ��s��t�������б仡��
	void setupShear(int axis,float s,float t);


	//��ƽ�ƺ����Ա任����ξ���4X4���������һ�ж��� 0001 ����ʡȥΪ4X3�ľ���
	void zeroTranslation();      //��ƽ�ƶ���Ϊ0
	void setTranslaton(const Vector3 &d);   //����ƽ�Ʊ任�Ĳ��֣���һ����������ʾ

	void setupTranslation(const Vector3 &d); //�����ı任
	

	
};
//�ǳ�Ա����
Matrix4x3 &operator *(const Matrix4x3 &a, const Matrix4x3 &b);
Vector3   &operator *(const Vector3 &p, const Matrix4x3 &m);

Matrix4x3 &operator *=( Matrix4x3 &a, const Matrix4x3 &b);
Vector3   &operator *=( Vector3 &p, const Matrix4x3 &m);

//����ʽ
//����A������ʽdetA�������Ա任A�µ�ͼ�������������������ӡ�
float determinant(const Matrix4x3 &m);

//�������
	Matrix4x3 inverse(const Matrix4x3 &m);

	//�õ�������ƽ�Ʊ任���Ǹ�����
	Vector3 getTranslation(const Matrix4x3 &m);
#endif