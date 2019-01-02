#include "bvh_node.h"
#include "comm.h"

static int box_x_compare(const void* a, const void* b)
{
	hitable* ah = *((hitable**)a);
	hitable* bh = *((hitable**)b);

	aabb boxa, boxb;
	if (ah->boundingbox(0, 0, boxa) == false || bh->boundingbox(0, 0, boxb) == false)
	{
		printf("%s,no boundingbox for a bvh node\n", __FUNCTION__);
	}

	if (boxa.get_min().x() - boxb.get_min().x() < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

static int box_y_compare(const void* a, const void* b)
{
	hitable* ah = *((hitable**)a);
	hitable* bh = *((hitable**)b);

	aabb boxa, boxb;
	if (ah->boundingbox(0, 0, boxa) == false || bh->boundingbox(0, 0, boxb) == false)
	{
		printf("%s,no boundingbox for a bvh node\n", __FUNCTION__);
	}

	if (boxa.get_min().y() - boxb.get_min().y() < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

static int box_z_compare(const void* a, const void* b)
{
	hitable* ah = *((hitable**)a);
	hitable* bh = *((hitable**)b);

	aabb boxa, boxb;
	if (ah->boundingbox(0, 0, boxa) == false || bh->boundingbox(0, 0, boxb) == false)
	{
		printf("%s,no boundingbox for a bvh node\n", __FUNCTION__);
	}

	if (boxa.get_min().z() - boxb.get_min().z() < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

bvh_node::bvh_node()
{

}

bvh_node::bvh_node(hitable** l, int size, float time0, float time1)
{
	if (size == 0)
	{
		return;
	}

	int iRandAxis = int(3 * randf());
	if (iRandAxis <= 0)
	{
		qsort(l, size, sizeof(l[0]), box_x_compare);
	}
	else if (iRandAxis <= 2)
	{
		qsort(l, size, sizeof(l[0]), box_y_compare);
	}
	else if (iRandAxis <= 3)
	{
		qsort(l, size, sizeof(l[0]), box_z_compare);
	}

	if (size == 1)
	{
		_left = _right = l[0];
	}
	else if (size == 2)
	{
		_left = l[0];
		_right = l[1];
	}
	else
	{
		_left = new bvh_node(l, size / 2, time0, time1);
		_right = new bvh_node(l + size / 2, size - size / 2, time0, time1);
	}

	aabb boxleft, boxright;
	if (_left->boundingbox(time0, time1, boxleft) == false || _right->boundingbox(time0, time1, boxright) == false)
	{
		printf("%s,no boundingbox for a bvh node\n", __FUNCTION__);
	}

	_box = surronding_box(boxleft, boxright);
}

bool bvh_node::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	if (_box.hit(ray, tmin, tmax))
	{
		hit_record rec_left, rec_right;
		bool left_hit = _left->hit(ray, tmin, tmax, rec_left);
		bool right_hit = _right->hit(ray, tmin, tmax, rec_right);

		if (left_hit && right_hit)
		{
			if (rec_left.t < rec_right.t)
			{
				record = rec_left;
			}
			else
			{
				record = rec_right;
			}
			return true;
		}
		else if (left_hit)
		{
			record = rec_left;
			return true;
		}
		else if (right_hit)
		{
			record = rec_right;
			return true;
		}

		return false;
	}
	else
	{
		return false;
	}
}

bool bvh_node::boundingbox(float t0, float t1, aabb& box)
{
	box = _box;
	return true;
}