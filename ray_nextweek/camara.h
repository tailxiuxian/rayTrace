#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "vec3.h"
#include "ray.h"

class CCamara
{
public:
	CCamara(CVec3 lookfrom, CVec3 lookat, CVec3 vup, float fov, float aspect, float aperture, float focus_dist, float time_begin, float time_end) 
	{
		_lens_radius = aperture / 2;
		float theta = fov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		_origin = lookfrom;
		_w = unit_vector(lookfrom - lookat);
		_u = unit_vector(cross_product(vup, _w));
		_v = cross_product(_w, _u);

		_low_left_cornor = - half_width * focus_dist*_u - half_height * focus_dist * _v - focus_dist * _w;
		_horizon = 2 * half_width*focus_dist*_u;
		_vertical = 2 * half_height*focus_dist*_v;

		_time_begin = time_begin;
		_time_end = time_end;
	};
	
	virtual ~CCamara() {};

	CRay get_ray(float u, float v)
	{
		CVec3 rd = _lens_radius * random_in_uint_disk();
		CVec3 offset = _u * rd.x() + _v * rd.y();
		float time = _time_begin + randf() * (_time_end - _time_begin);
		return CRay(_origin + offset, _low_left_cornor + u * _horizon + v * _vertical - offset, time);
	}

	static CVec3 random_in_uint_disk()
	{
		CVec3 p;
		do {
			p = 2.0f * CVec3(randf(), randf(), 0) - CVec3(1, 1, 0);
		} while (p.squared_lenght() >= 1.0f);
		return p;
	}

private:
	CVec3 _origin;
	CVec3 _horizon;
	CVec3 _vertical;
	CVec3 _low_left_cornor;
	CVec3 _u, _v, _w;
	float _lens_radius;
	float _time_begin;
	float _time_end;
};