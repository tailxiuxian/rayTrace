#include "constant_medium.h"
#include "material.h"

constant_medium::constant_medium()
{}

constant_medium::constant_medium(hitable* obj, float density, texture* tex)
	:_obj(obj)
	,_density(density)
{
	_mat_ptr = new istropic(tex);
}

bool constant_medium::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	hit_record rec1, rec2;
	if (_obj->hit(ray, -FLT_MAX, FLT_MAX, rec1))
	{
		if (_obj->hit(ray, rec1.t + 0.0001f, FLT_MAX, rec2))
		{
			if (rec1.t < tmin)
			{
				rec1.t = tmin;
			}

			if (rec2.t > tmax)
			{
				rec2.t = tmax;
			}

			if (rec1.t >= rec2.t)
			{
				return false;
			}

			if (rec1.t < 0.0f)
			{
				rec1.t = 0.0f;
			}

			float distance_in_obj = (rec2.t - rec1.t) * ray.direction().length();
			float hit_distance = -(1.0f / _density) * log(randf());
			if (hit_distance < distance_in_obj)
			{
				record.t = rec1.t + hit_distance / ray.direction().length();
				record.p = ray.point_at_ray(record.t);
				record.normal = CVec3(1.0f, 0.0f, 0.0f);
				record.mat_ptr = _mat_ptr;
				return true;
			}
		}
	}
	return false;
}

bool constant_medium::boundingbox(float t0, float t1, aabb& box)
{
	return _obj->boundingbox(t0, t1, box);
}