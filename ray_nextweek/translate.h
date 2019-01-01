#pragma once

#include "ray.h"

class translate : public hitable
{
public:
	translate();
	translate(hitable* obj, CVec3 displacement);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	CVec3 _displacement;
	hitable* _obj;
};