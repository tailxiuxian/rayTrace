#pragma once

#include "ray.h"

class moving_sphere : public hitable {
public:
	moving_sphere(CVec3 center_begin, CVec3 center_end, float time_begin, float time_end, float radius, matrial* mat);
	~moving_sphere();

	CVec3 center(float time);

	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	CVec3 _center_begin;
	CVec3 _center_end;
	float _time_begin;
	float _time_end;
	float _radius;
	matrial* _mat;
};