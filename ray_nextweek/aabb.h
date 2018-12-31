#pragma once

#include "vec3.h"

class CRay;

// ·½ÌåµÄAABB

class aabb
{
public:
	aabb();
	aabb(CVec3 min, CVec3 max) ;
	bool hit(CRay &ray, float tmin, float tmax);
	CVec3& get_min();
	CVec3& get_max();

private:
	CVec3 _min;
	CVec3 _max;
};