#include "translate.h"
#include "aabb.h"

translate::translate()
{}

translate::translate(hitable* obj, CVec3 displacement)
	:_obj(obj)
	,_displacement(displacement)
{}

bool translate::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	CRay translate_ray(ray.origin() - _displacement, ray.direction(), ray.get_time());
	if (_obj->hit(translate_ray, tmin, tmax, record))
	{
		record.p += _displacement;
		return true;
	}
	return false;
}

bool translate::boundingbox(float t0, float t1, aabb& box)
{
	aabb temp_box;
	bool bHasBox = _obj->boundingbox(t0, t1, temp_box);
	if (bHasBox)
	{
		box = aabb(temp_box.get_min() + _displacement, temp_box.get_max() + _displacement);
		return true;
	}
	return false;
}