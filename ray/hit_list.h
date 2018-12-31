#pragma once

#include "ray.h"

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

private:
	hitable** _list;
	int _size;
};