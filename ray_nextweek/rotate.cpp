#include "rotate.h"
#define _USE_MATH_DEFINES
#include <math.h>

rotate_y::rotate_y()
{}

rotate_y::rotate_y(hitable* obj, float angle)
	:_obj(obj)
{
	_radian = (M_PI / 180.0f) * angle;
	_sinradian = sin(_radian);
	_cosradian = cos(_radian);
	_bHasBox = _obj->boundingbox(0, 1, _box);
	if (_bHasBox)
	{
		CVec3 vec_min(FLT_MAX, FLT_MAX, FLT_MAX);
		CVec3 vec_max(FLT_MIN, FLT_MIN, FLT_MIN);

		for(int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
				{
					float x = i * _box.get_min().x() + (1 - i) * _box.get_max().x();
					float y = j * _box.get_min().y() + (1 - j) * _box.get_max().y();
					float z = k * _box.get_min().z() + (1 - k) * _box.get_max().z();
					float new_x = x * _cosradian + z * _sinradian;
					float new_z = -_sinradian * x + z * _cosradian;

					CVec3 temp(new_x, y, new_z);
					for (i = 0; i < 3; i++)
					{
						if (temp[i] < vec_min[i])
						{
							vec_min[i] = temp[i];
						}
						
						if (temp[i] > vec_max[i])
						{
							vec_max[i] = temp[i];
						}
					}
				}

		_box = aabb(vec_min, vec_max);
	}
}

bool rotate_y::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	CVec3 rotate_origin = ray.origin();
	CVec3 rotate_direction = ray.direction();

	rotate_origin[0] = ray.origin()[0] * _cosradian - ray.origin()[2] * _sinradian;
	rotate_origin[2] = ray.origin()[2] * _sinradian + ray.origin()[2] * _cosradian;
	rotate_direction[0] = ray.direction()[0] * _cosradian - ray.direction()[2] * _sinradian;
	rotate_direction[2] = ray.direction()[2] * _sinradian + ray.direction()[2] * _cosradian;

	CRay rotate_ray(rotate_origin, rotate_direction, ray.get_time());
	if (_obj->hit(rotate_ray, tmin, tmax, record))
	{
		CVec3 hit_point = record.p;
		CVec3 normal = record.normal;

		record.p[0] = hit_point[0] * _cosradian + hit_point[2] * _sinradian;
		record.p[2] = -_sinradian * hit_point[0] + hit_point[2] * _cosradian;
		record.normal[0] = normal[0] * _cosradian + normal[2] * _sinradian;
		record.normal[2] = -_sinradian * normal[0] + normal[2] * _cosradian;
		return true;
	}
	return false;
}

bool rotate_y::boundingbox(float t0, float t1, aabb& box)
{
	box = _box;
	return _bHasBox;
}