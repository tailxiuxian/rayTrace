#pragma once

#include "ray.h"

class texture;

class constant_medium : public hitable
{
public:
	constant_medium();
	constant_medium(hitable* obj, float density, texture* tex);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	float _density;
	hitable* _obj;
	matrial* _mat_ptr;
};