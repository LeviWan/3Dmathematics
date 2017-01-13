

#ifndef __VECTOR3_H_INCLUDED__
#define __VECTOR3_H_INCLUDED__

#include <math.h>
class Vector3
{
public:
	float x, y, z;

	Vector3(){}

	Vector3(const Vector3 &a) :x(a.x), y(a.y), z(a.z){}
	Vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz){}

	//零向量
	void Zero()
	{
		x = y = z = 0.0f;
	}

	//计算单位向量，进行标准化

	void normalize()
	{
		float magsq = x*x + y*y + z*z;    //平发根之前
		if (magsq > 0.0f)  //必须比0大
		{
			float temp = 1 / sqrt(magsq);
			x *= temp;
			y *= temp;
			z *= temp;

		}
	}

	//负向量,运算符的重载
	Vector3 operator-() const { return Vector3(-x, -y, -z); }

	Vector3 operator*(float a /*标量*/) const
	{
		return Vector3(x*a, y*a, z*a);
	}
	Vector3 operator/(float a) const
	{
		float temp = 1.0f / a;
		return Vector3(x*temp, y*temp, z*temp);
	}

	Vector3 operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vector3 operator/=(float a)
	{
		float temp = 1.0f / a;
		x *= temp;
		y *= temp;
		z *= temp;
		return *this;
	}

	Vector3 operator+(const Vector3 &a)const
	{
		return Vector3(x+a.x,y+a.y,z+a.z);
	}

	Vector3 operator+=(const Vector3 &a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	Vector3 operator-=(const Vector3 &a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	Vector3 operator-(const Vector3 &a)const
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}

	//点乘

	float  operator*(const Vector3 &a)const
	{
		return x*a.x + y*a.y + z*a.z;	
	}



};

//计算向量的模
inline float vectorMag(const Vector3 &a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

//非成员函数，实现向量左乘
inline Vector3 operator*(float k, const Vector3 &v)
{
	return Vector3(k*v.x, k*v.y, k*v.z);
}

//计算两点之间的距离
inline float distance(const Vector3 &a, const Vector3 &b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;

	//计算向量的模。也就是大小，距离

	return sqrt(dx*dx+dy*dy+dz*dz);

}

//计算叉乘

inline Vector3 crossProduct(const Vector3&a, const Vector3 &b)
{
	return Vector3(
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x
		);
}
#endif