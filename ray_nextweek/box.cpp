#include "box.h"
#include "rect.h"
#include "material.h"
#include "hit_list.h"

box::box()
{}

box::box(CVec3 pmin, CVec3 pmax, matrial* mat_ptr)
	:_pmin(pmin)
	,_pmax(pmax)
{
	hitable **list = new hitable*[6];

	list[0] = new flip_normal(new yz_rect(_pmin.y(), _pmax.y(), _pmin.z(), _pmax.z(), _pmin.x(), mat_ptr));
	list[1] = new yz_rect(_pmin.y(), _pmax.y(), _pmin.z(), _pmax.z(), _pmax.x(), mat_ptr);
	list[2] = new flip_normal(new xy_rect(_pmin.x(), _pmax.x(), _pmin.y(), _pmax.y(), _pmin.z(), mat_ptr));
	list[3] = new xy_rect(_pmin.x(), _pmax.x(), _pmin.y(), _pmax.y(), _pmax.z(), mat_ptr);
	list[4] = new flip_normal(new xz_rect(_pmin.x(), _pmax.x(), _pmin.z(), _pmax.z(), _pmin.y(), mat_ptr));
	list[5] = new xz_rect(_pmin.x(), _pmax.x(), _pmin.z(), _pmax.z(), _pmax.y(), mat_ptr);

	_panel_list = new Chitlist(list, 6);
}

bool box::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	return _panel_list->hit(ray, tmin, tmax, record);
}

bool box::boundingbox(float t0, float t1, aabb& box)
{
	box = aabb(_pmin,_pmax);
	return true;
}