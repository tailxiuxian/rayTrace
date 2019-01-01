#include "rect.h"
#include "aabb.h"

xy_rect::xy_rect(float xmin, float xmax, float ymin, float ymax, float zconstant, matrial* mat)
	:_xmin(xmin)
	,_xmax(xmax)
	,_ymin(ymin)
	,_ymax(ymax)
	,_zconstant(zconstant)
	,_mat(mat)
{}

bool xy_rect::boundingbox(float t0, float t1, aabb& box)
{
	box = aabb(CVec3(_xmin, _ymin, _zconstant - 0.00001f), CVec3(_xmax, _ymax, _zconstant + 0.00001f));
	return true;
}

bool xy_rect::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	float t = (_zconstant - ray.origin().z()) / ray.direction().z();
	if (t < tmin || t > tmax)
	{
		return false;
	}

	float x = ray.origin().x() + t * ray.direction().x();
	float y = ray.origin().y() + t * ray.direction().y();

	if (x < _xmin || x > _xmax || y < _ymin || y > _ymax)
	{
		return false;
	}

	record.t = t;
	record.p = ray.point_at_ray(t);
	record.normal = CVec3(0.0f, 0.0f, 1.0f);
	record.mat_ptr = _mat;
	return true;
}

xz_rect::xz_rect(float xmin, float xmax, float zmin, float zmax, float yconstant, matrial* mat)
	:_xmin(xmin)
	, _xmax(xmax)
	, _zmin(zmin)
	, _zmax(zmax)
	, _yconstant(yconstant)
	, _mat(mat)
{}

bool xz_rect::boundingbox(float t0, float t1, aabb& box)
{
	box = aabb(CVec3(_xmin, _yconstant - 0.00001f, _zmin), CVec3(_xmax, _yconstant + 0.00001f, _zmax));
	return true;
}

bool xz_rect::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	float t = (_yconstant - ray.origin().y()) / ray.direction().y();
	if (t < tmin || t > tmax)
	{
		return false;
	}

	float x = ray.origin().x() + t * ray.direction().x();
	float z = ray.origin().z() + t * ray.direction().z();

	if (x < _xmin || x > _xmax || z < _zmin || z > _zmax)
	{
		return false;
	}

	record.t = t;
	record.p = ray.point_at_ray(t);
	record.normal = CVec3(0.0f, 1.0f, 0.0f);
	record.mat_ptr = _mat;
	return true;
}

yz_rect::yz_rect(float ymin, float ymax, float zmin, float zmax, float xconstant, matrial* mat)
	: _ymin(ymin)
	, _ymax(ymax)
	, _zmin(zmin)
	, _zmax(zmax)
	, _xconstant(xconstant)
	, _mat(mat)
{}

bool yz_rect::boundingbox(float t0, float t1, aabb& box)
{
	box = aabb(CVec3(_xconstant - 0.00001f, _ymin, _zmin), CVec3(_xconstant + 0.00001f, _ymax, _zmax));
	return true;
}

bool yz_rect::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	float t = (_xconstant - ray.origin().x()) / ray.direction().x();
	if (t < tmin || t > tmax)
	{
		return false;
	}

	float y = ray.origin().y() + t * ray.direction().y();
	float z = ray.origin().z() + t * ray.direction().z();

	if (y < _ymin || y > _ymax || z < _zmin || z > _zmax)
	{
		return false;
	}

	record.t = t;
	record.p = ray.point_at_ray(t);
	record.normal = CVec3(1.0f, 0.0f, 0.0f);
	record.mat_ptr = _mat;
	return true;
}

flip_normal::flip_normal(hitable* obj)
	:_obj(obj)
{}

bool flip_normal::boundingbox(float t0, float t1, aabb& box)
{
	return _obj->boundingbox(t0, t1, box);
}

bool flip_normal::hit(CRay& ray, float tmin, float tmax, hit_record& record)
{
	if (_obj->hit(ray, tmin, tmax, record))
	{
		record.normal = -record.normal;
		return true;
	}
	return false;
}