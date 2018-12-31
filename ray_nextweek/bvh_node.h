#pragma once

#include "ray.h"
#include "aabb.h"

class Chitlist;

class bvh_node : public hitable
{
public:
	bvh_node();
	bvh_node(hitable** l, int size, float time0, float time1);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);
private:
	hitable * _left;
	hitable * _right;
	aabb _box;
};