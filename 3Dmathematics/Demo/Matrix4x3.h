#ifndef __Matrix4x3_H_INCLUDED__
#define __Matrix4x3_H_INCLUDED__


class Vector3;

class Matrix4x3
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	//多加的这一行为平移的偏移量，//齐次矩阵
	float tx, ty, tz;


	//旋转矩阵
	//axis 指定旋转轴，为1是X轴，2是Y，3是Z
	void setRotate(int axis, float theta);

	//缩放矩阵
	void setupScale(const float Kx, const float Ky, const  float Kz);

	//可以把这三个参数放在有一个向量里
	void setupScale(const Vector3 &s);

	//投影矩阵，正交矩阵
	//使参数向量垂直于投影平面，就可以指定需要投影的平面了，还可以把这个向量作为空间任何有一个平面的投影
	void setuoProject(const Vector3 &n);

	//镜像矩阵（对标准轴平面）
	//axis为镜像平面或者镜像坐标轴，//k表示相对（x，y，z）轴平移量的平面
	void setupReflect(int axis,float k);


	//对任意平面的镜像
	//n垂直于镜像平面的单位向量
	void setupReflect(const Vector3 &n);

	//切变
	//axis指定的切变坐标轴,s,t分别为其他两个轴的切变值，s，t决定了切变弧度
	void setupShear(int axis,float s,float t);


	//带平移和线性变换的齐次矩阵4X4，但是最后一列都是 0001 所有省去为4X3的矩阵
	void zeroTranslation();      //把平移都变为0
	void setTranslaton(const Vector3 &d);   //设置平移变换的部分，用一个向量来表示

	void setupTranslation(const Vector3 &d); //真正的变换
	

	
};
//非成员函数
Matrix4x3 &operator *(const Matrix4x3 &a, const Matrix4x3 &b);
Vector3   &operator *(const Vector3 &p, const Matrix4x3 &m);

Matrix4x3 &operator *=( Matrix4x3 &a, const Matrix4x3 &b);
Vector3   &operator *=( Vector3 &p, const Matrix4x3 &m);

//行列式
//矩阵A的行列式detA就是线性变换A下的图形面积或体积的伸缩因子。
float determinant(const Matrix4x3 &m);

//矩阵的逆
	Matrix4x3 inverse(const Matrix4x3 &m);

	//得到矩阵中平移变换的那个向量
	Vector3 getTranslation(const Matrix4x3 &m);
#endif