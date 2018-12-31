#pragma once

#include "ray.h"
#include "comm.h"
#include "texture.h"

class matrial
{
public:
	virtual bool scatter(CRay& ray_in, hit_record& rec, CVec3& attenuation, CRay& ray_scatter) = 0;
};

class lambertian : public matrial
{
public:
	lambertian(texture* tex)
		:_tex(tex)
	{}

	virtual ~lambertian() {};

	virtual bool scatter(CRay& ray_in, hit_record& rec, CVec3& attenuation, CRay& ray_scatter)
	{
		CVec3 vecRand = rec.normal + random_vec_in_sphere();
		ray_scatter = CRay(rec.p, vecRand, ray_in.get_time());
		attenuation = _tex->color(0,0,rec.p);
		return true;
	}

private:
	texture* _tex;
};

class metal : public matrial
{
public:
	metal(CVec3 vec, float fuzz)
		:_albedo(vec)
	{
		if (fuzz < 1.0f)
		{
			_fuzz = fuzz;
		}

		_fuzz = 1.0f;
	}

	virtual ~metal() {};

	virtual bool scatter(CRay& ray_in, hit_record& rec, CVec3& attenuation, CRay& ray_scatter)
	{
		CVec3 out_direction = reflect(ray_in.direction(), rec.normal);
		CVec3 disturb = _fuzz * random_vec_in_sphere();
		out_direction += disturb;
		ray_scatter = CRay(rec.p, out_direction, ray_in.get_time());
		attenuation = _albedo;
		return true;
	}

private:
	CVec3 _albedo;
	float _fuzz;
};

class dielectric : public matrial
{
public:
	dielectric(float r)
		:_refraction(r)
	{};

	virtual ~dielectric() {};

	virtual bool scatter(CRay& ray_in, hit_record& rec, CVec3& attenuation, CRay& ray_scatter)
	{
		attenuation = CVec3(1.0f, 1.0f, 1.0f);
		CVec3 reflected = reflect(ray_in.direction(), rec.normal);
		CVec3 out_normal;
		float r;
		float reflect_prob;
		float cosine;
		if (dot_product(rec.normal, ray_in.direction()) > 0)
		{
			out_normal = -rec.normal;
			r = _refraction;
			cosine = _refraction * dot_product(ray_in.direction(), rec.normal) / ray_in.direction().length();
		}
		else
		{
			out_normal = rec.normal;
			r = 1.0f / _refraction;
			cosine = -dot_product(ray_in.direction(), rec.normal) / ray_in.direction().length();
		}

		CVec3 refracted;
		if (refract(ray_in.direction(), out_normal, r, refracted))
		{
			reflect_prob = schlick(cosine, _refraction);
		}
		else
		{
			reflect_prob = 1.0f;
		}

		if (randf() < reflect_prob)
		{
			ray_scatter = CRay(rec.p, reflected, ray_in.get_time());
		}
		else
		{
			ray_scatter = CRay(rec.p, refracted, ray_in.get_time());
		}
		return true;
	}

private:
	float _refraction;
};