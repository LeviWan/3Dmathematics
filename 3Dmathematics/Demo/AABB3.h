#ifndef __AABB3_H_INCLUDED__
#define __AABB3_H_INCLUDED__

#include "Vector3.h"
class Vector3;

class AABB3
{
	//AABB八个顶点中最小的顶点和最大的顶点
	Vector3 min;
	Vector3 max;
	//计算AABB的大小
	Vector3 size() const { return max - min; }
	//计算AABBx，y，z的大小
	float xSize() { return max.x - min.x; }
	float ySize() { return max.y - min.y; }
	float zSize() { return max.z - min.z; }

	//计算AABB的中心店
	Vector3 center() { return (min + max)*0.5f; }


};



#endif