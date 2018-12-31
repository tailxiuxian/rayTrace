#pragma once

#include "ray.h"

class CSphere : public hitable
{
public:
	CSphere(CVec3 center, float r, matrial* mat)
		:_center(center)
		,_r(r)
		,_mat(mat)
	{}

	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	CVec3 _center;
	float _r;
	matrial* _mat;
};