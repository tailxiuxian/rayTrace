#include "sphere.h"

bool CSphere::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	CVec3 vecOC = ray.origin() - _center;
	float a = dot_product(ray.direction(), ray.direction());
	float b = 2.0f * dot_product(vecOC, ray.direction());
	float c = dot_product(vecOC, vecOC) - _r * _r;
	float discriminant = b * b - 4.0f * a * c;
	if (discriminant <= 0.0f)
	{
		return false;
	}
	else
	{
		float t = (-b - sqrt(discriminant)) / (2.0f * a);
		if (t >= tmax || t <= tmin)
		{
			t = (-b + sqrt(discriminant)) / (2.0f * a);
			if (t >= tmax || t <= tmin)
			{
				return false;
			}
		}
		record.t = t;
		record.p = ray.point_at_ray(t);
		record.normal = (record.p - _center) / _r;
		record.mat_ptr = _mat;
		return true;
	}
}