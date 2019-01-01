#pragma once

#include "ray.h"

class xy_rect : public hitable
{
public:
	xy_rect(float xmin, float xmax, float ymin, float ymax, float zconstant, matrial* mat);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	float _xmin;
	float _xmax;
	float _ymin;
	float _ymax;
	float _zconstant;
	matrial* _mat;
};

class xz_rect : public hitable
{
public:
	xz_rect(float xmin, float xmax, float zmin, float zmax, float yconstant, matrial* mat);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	float _xmin;
	float _xmax;
	float _zmin;
	float _zmax;
	float _yconstant;
	matrial* _mat;
};

class yz_rect : public hitable
{
public:
	yz_rect(float ymin, float ymax, float zmin, float zmax, float xconstant, matrial* mat);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	float _ymin;
	float _ymax;
	float _zmin;
	float _zmax;
	float _xconstant;
	matrial* _mat;
};

class flip_normal : public hitable
{
public:
	flip_normal(hitable* obj);
	virtual bool hit(CRay& ray, float tmin, float tmax, hit_record& record);
	virtual bool boundingbox(float t0, float t1, aabb& box);

private:
	hitable * _obj;
};