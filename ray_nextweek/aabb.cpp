#include "aabb.h"
#include "comm.h"

aabb::aabb()
{

}

aabb::aabb(CVec3 min, CVec3 max)
{
	_min = min;
	_max = max;
}

bool aabb::hit(CRay &ray, float tmin, float tmax)
{
	for (int i = 0; i < 3; i++)
	{
		float fDiv = 1.0f / ray.direction()[i];
		float tempt0 = (_min[i] - ray.origin()[i]) * fDiv;
		float tempt1 = (_max[i] - ray.origin()[i]) * fDiv;

		float t0 = ffmin(tempt0, tempt1);
		float t1 = ffmax(tempt0, tempt1);

		tmin = ffmax(tmin, t0);
		tmax = ffmin(tmax, t1);
		if (tmin >= tmax)
		{
			return false;
		}
	}
	return true;
}

CVec3& aabb::get_min() { return _min; }
CVec3& aabb::get_max() { return _max; }