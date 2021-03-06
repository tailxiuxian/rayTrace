#pragma once

#include "vec3.h"

class aabb;
class matrial;

class CRay
{
public:
	CRay() {};

	CRay(CVec3 origin, CVec3 direction, float time)
		:_origin(origin)
		,_direction(direction)
		,_time(time)
	{};

	virtual ~CRay() {};

	CVec3 origin() const { return _origin;  }
	CVec3 direction() const { return _direction; }
	CVec3 point_at_ray(float t) { return _origin + _direction * t; }
	float get_time() { return _time;  }

private:
	CVec3 _origin;
	CVec3 _direction;
	float _time;
};

struct hit_record
{
	float t;
	CVec3 p;
	CVec3 normal;
	matrial* mat_ptr;
};

class hitable
{
public:
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record) = 0;
	virtual bool boundingbox(float t0, float t1, aabb& box) = 0;
};