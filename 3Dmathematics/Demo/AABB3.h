#ifndef __AABB3_H_INCLUDED__
#define __AABB3_H_INCLUDED__

#include "Vector3.h"
class Vector3;

class AABB3
{
	//AABB�˸���������С�Ķ�������Ķ���
	Vector3 min;
	Vector3 max;
	//����AABB�Ĵ�С
	Vector3 size() const { return max - min; }
	//����AABBx��y��z�Ĵ�С
	float xSize() { return max.x - min.x; }
	float ySize() { return max.y - min.y; }
	float zSize() { return max.z - min.z; }

	//����AABB�����ĵ�
	Vector3 center() { return (min + max)*0.5f; }


};



#endif