#pragma once

#include "ray.h"
#include "aabb.h"

class Chitlist : public hitable
{
public:
	Chitlist()
		:_list(NULL)
		,_size(0)
	{};

	Chitlist(hitable** list, int size) 
		:_list(list)
		,_size(size)
	{};

	virtual ~Chitlist() {};

	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	hitable** _list;
	int _size;
};