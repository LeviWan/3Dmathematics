#include <iostream>
#include "Vector3.h"
#include "Matrix4x3.h"
#include "MathUtil.h"
#include <math.h>
#include "RotationMatrix.h"
#include "EulerAngles.h"
using namespace std;


//如果很小很小的话，直接变为0
float to_zero(float n)
{
	return (abs(n) < 0.00001 ? 0 : n);
}

void print_v(Vector3 v)
{
	cout << endl;
	cout << "[" << to_zero(v.x) << "," << to_zero(v.y) << "," << to_zero(v.z) << "]" << endl;
}

void print_m(Matrix4x3 m)
{
	cout << endl;
	cout << "[" << to_zero(m.m11) << "\t" << to_zero(m.m12) << "\t" << to_zero(m.m13) << "]" << endl;
	cout << "[" << to_zero(m.m21) << "\t" << to_zero(m.m22) << "\t" << to_zero(m.m23) << "]" << endl;
	cout << "[" << to_zero(m.m31) << "\t" << to_zero(m.m32) << "\t" << to_zero(m.m33) << "]" << endl;
}
int main()
{


	//Vector3 v1 (10,20,30);
	//print_v(v1);
	//Vector3 v2(v1);  //复制构造函数
	//print_v(v2);

	//Vector3 v3(-v1);
	//print_v(v3);

	//v2.Zero();
	//print_v(v2);

	//Vector3 v4(5, -4, 7);
	//float r = vectorMag(v4);
	//cout << r<<endl;

	//Vector3 v5(-5,0,0.4);
	//Vector3 v6 = v5*-5;
	//print_v(v6);

	//Vector3 v11(12,-5,0);
	// v11.normalize();


	// print_v(v11);

	// Vector3 v12(3,-2,7);
	// Vector3 v13(0,4,-1);

	// cout << v12*v13 << endl;

	// //求夹角
	// double jiajiaoHudu = acos((v12*v13) / (vectorMag(v12)*vectorMag(v13))); //得到的是弧度，还需要转换为角度
	// double jiaodu = jiajiaoHudu * 180 / 3.14159;  //弧度转化角度

	// cout << jiaodu << endl;

	// Vector3 t1(1,3,4);
	// Vector3 t2(2, -5, 8);

	// Vector3 crosst3 = crossProduct(t1,t2);

	// print_v(crosst3);

	/*cout << "hello 矩阵" << endl;

	Matrix4x3 a, b;
	a.m11 = 1; a.m12 = -5; a.m13 = 3;
	a.m21 = 0; a.m22 = -2; a.m23 = 6;
	a.m31 = 7; a.m32 = 2; a.m33 = -4;

	b.m11 = -8; b.m12 = 6; b.m13 = 1;
	b.m21 = 7; b.m22 = 0; b.m23 = -3;
	b.m31 = 2; b.m32 = 4; b.m33 = 5;

	Matrix4x3 r = a*b;
	print_m(r);
	a *= b;
	print_m(a);*/


	//cout << "hello 线性变换---旋转" << endl;

	//Vector3 a(10,0,0);
	//Vector3 b;

	//Matrix4x3 M;
	//M.setRotate(3,kPIOver2); //绕Z轴旋转90度

	//b = a*M;
	//print_v(b);
	////打印可以绕Z轴旋转90的矩阵
	//print_m(M);
	//M.setRotate(3, kPI);
	////打印可以绕Z轴旋转180的矩阵
	//print_m(M);
	//b = a*M;
	//print_v(b);
	////绕X轴旋转-22度的矩阵
	//M.setRotate(1, -22 * kPI / 180);
	//print_m(M);
	////绕X轴旋转30度的矩阵
	//M.setRotate(2, 30 * kPI / 180);
	//print_m(M);


	//cout << "hello 线性变换---缩放" << endl;

	//Vector3 a(10,20,30);
	//print_v(a);
	//Vector3 b(1,2,3);
	//Matrix4x3 ScaleM;
	//ScaleM.setupScale(1,2,3);
	//Vector3 c;
	//c=a*ScaleM;
	//print_m(ScaleM);
	////print_v(c);

	////投影
	//Matrix4x3 M;
	//Vector3 n(0,0,1);
	//M.setuoProject(n);
	//Vector3 p1;
	//p1 = a*M;
	////print_v(p1);

	////简单镜像
	//Matrix4x3 M1,M2,M3;
	//M1.setupReflect(1); //x坐标发生变化
	//Vector3 v1;
	//v1 = a*M1;
	////print_v(v1);

	//M2.setupReflect(2); //y坐标发生变化
	//v1 = a*M2;
	////print_v(v1);

	////任意镜像平面
	//Matrix4x3 M4;
	//Vector3 n11(0,0,1);
	//M4.setupReflect(n11);
	//Vector3 v11;
	//v11 = a*M4;
	////print_v(v11);

	////切变
	//Vector3 a1(10,20,30);
	//Matrix4x3 M41;
	//Vector3 v111;
	//M41.setupShear(1,1,2);
	//v111 = a1*M41;
	//print_v(v111);

	/*cout << "hello 矩阵的行列式" << endl;*/
	//Matrix4x3 M;
	//M.m11 = -4.0f; M.m12 = -3.0f;   M.m13 = 3.0f;
	//M.m21 = 0.0f; M.m22 = 2.0f;    M.m23 = -2.0f;
	//M.m31 = 1.0f; M.m32 = 4.0f;   M.m33 = -1.0f;

	//计算行列式
	//矩阵A的行列式detA就是线性变换A下的图形面积或体积的伸缩因子。
	/*float detM = determinant(M);
	cout << detM << endl;*/

	/*Matrix4x3 r = inverse(M);

	print_m(r);

	Matrix4x3 newM = M*r;
	print_m(newM);*/

	/*cout << "hello 旋转矩阵" << endl;*/

	////绕y轴旋转30度
	//RotationMatrix M;
	//M.m11 = 0.866f; M.m12 = 0.0f;   M.m13 = -0.50f;
	//M.m21 = 0.0f; M.m22 = 1.0f;    M.m23 = 0.0f;
	//M.m31 = 0.50f; M.m32 = 0.0f;   M.m33 = 0.866f;

	//Vector3 v1(10,20,30),v2;
	////v1是惯性坐标系的向量
	//v2=M.insertialToObject(v1);
	//print_v(v2);
	//v2 = M.objectToInsertial(v1);
	//print_v(v2);

	cout << "hello 旋转(欧拉角)" << endl;

	//RotationMatrix M;
	//EulerAngles or(30*kPI/180,0,0);
	//M.setup(or);

	//Vector3 v1(10,20,30),v2;
	////v1是惯性坐标系的向量
	//v2 = M.insertialToObject(v1);
	//print_v(v2);

	RotationMatrix M;
	M.m11 = 0.866f; M.m12 = 0.0f;   M.m13 = -0.50f;
	M.m21 = 0.0f; M.m22 = 1.0f;    M.m23 = 0.0f;
	M.m31 = 0.50f; M.m32 = 0.0f;   M.m33 = 0.866f;

	EulerAngles or1;

	or1.fromRotationMatrix(M);

	cout << "heading:" << or1.heading*180/kPI << "pitch:" << or1.pitch << "bank:" << or1.bank << endl;
	system("pause");
	return 0;
}