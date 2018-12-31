#include "moving_sphere.h"
#include "aabb.h"
#include "comm.h"

moving_sphere::moving_sphere(CVec3 center_begin, CVec3 center_end, float time_begin, float time_end, float radius, matrial* mat)
	: _center_begin(center_begin)
	, _center_end(center_end)
	, _time_begin(time_begin)
	, _time_end(time_end)
	, _radius(radius)
	, _mat(mat)
{};

moving_sphere::~moving_sphere()
{};

CVec3 moving_sphere::center(float time)
{
	float k = (time - _time_begin) / (_time_end - _time_begin);
	return _center_begin + k * (_center_end - _center_begin);
}

bool moving_sphere::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	float time = ray.get_time();
	CVec3 vec_center = center(time);
	CVec3 vecOC = ray.origin() - vec_center;
	float a = dot_product(ray.direction(), ray.direction());
	float b = 2.0f * dot_product(vecOC, ray.direction());
	float c = dot_product(vecOC, vecOC) - _radius * _radius;
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
		record.normal = (record.p - vec_center) / _radius;
		record.mat_ptr = _mat;
		return true;
	}
}

bool moving_sphere::boundingbox(float t0, float t1, aabb& box)
{
	box = surronding_box(aabb(center(_time_begin) - _radius, center(_time_begin) + _radius), aabb(center(_time_end) - _radius, center(_time_end) + _radius));
	return true;
}