#pragma once

#include "ray.h"

class box : public hitable
{
public:
	box();
	box(CVec3 pmin, CVec3 pmax, matrial* mat_ptr);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	CVec3 _pmin;
	CVec3 _pmax;
	hitable * _panel_list;
};