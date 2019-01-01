#pragma once

#include "ray.h"
#include "aabb.h"

class rotate_y : public hitable
{
public:
	rotate_y();
	rotate_y(hitable* obj, float angle);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	float _sinradian;
	float _cosradian;
	float _radian;
	hitable* _obj;
	bool _bHasBox;
	aabb _box;
};