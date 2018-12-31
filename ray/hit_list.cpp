#include "hit_list.h"

bool Chitlist::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	if (_size == 0 || _list == NULL)
	{
		return false;
	}

	hit_record temp;
	float tclose = FLT_MAX;
	bool hit = false;
	for (int i = 0; i < _size; i++)
	{
		if (_list[i]->hit(ray, tmin, tclose, temp))
		{
			hit = true;
			tclose = temp.t;
			record = temp;
		}
	}
	return hit;
}