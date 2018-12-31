#include "hit_list.h"
#include "comm.h"

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

bool Chitlist::boundingbox(float t0, float t1, aabb& box)
{
	if (_size == 0)
	{
		return false;
	}

	if (_size == 1)
	{
		return _list[0]->boundingbox(t0, t1, box);
	}
	
	aabb temp_box;
	for (int i = 0; i < _size; i++)
	{
		if (_list[i]->boundingbox(t0, t1, temp_box))
		{
			if (i == 0)
			{
				box = temp_box;
			}
			else
			{
				box = surronding_box(box, temp_box);
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}