#include <time.h>
#include "comm.h"
#include "material.h"
#include "vec3.h"

const int MAX_SCATTER_DEPTH = 50;

CVec3 color(CRay r, hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		CRay ray_scattered;
		CVec3 attenuation;
		CVec3 emitted = rec.mat_ptr->emit(0.0f, 0.0f, rec.p);
		if (depth < MAX_SCATTER_DEPTH && rec.mat_ptr->scatter(r, rec, attenuation, ray_scattered))
		{
			return emitted + attenuation * color(ray_scattered, world, depth + 1);
		}
		else
		{
			return emitted;
		}
	}
	else
	{
		//CVec3 unit_direction = unit_vector(r.direction());
		//float t = (1.0f + unit_direction.y()) / 2.0f;
		//return CVec3(1.0f, 1.0f, 1.0f) * (1.0f - t) + CVec3(0.5f, 0.7f, 1.0f) * t;
		return CVec3(0.0f, 0.0f, 0.0f);
	}
}

float randf()
{
	static bool is_inited = false;
	if (!is_inited)
	{
		srand((unsigned)time(NULL));
		is_inited = true;
	}

	return (float)rand() / (float)(RAND_MAX + 1);
}

CVec3 random_vec_in_sphere()
{
	CVec3 p;
	do {
		p = CVec3(randf(), randf(), randf()) * 2.0f - CVec3(1.0f, 1.0f, 1.0f);
	} while (p.squared_lenght() >= 1.0f);
	return p;
}

CVec3 reflect(CVec3 in, CVec3 normal)
{
	return in - 2.0f * dot_product(in, normal) * normal;
}

bool refract(CVec3 in, CVec3& normal, float n_over_nt, CVec3& refracted)
{
	CVec3 uin = unit_vector(in);
	float dt = dot_product(uin, normal);
	float discriminant = 1.0f - n_over_nt * n_over_nt *(1.0f - dt * dt);
	if (discriminant > 0.0f)
	{
		refracted = n_over_nt * (uin - normal * dt) - normal * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

float schlick(float cosine, float refraction)
{
	float r0 = (1.0f - refraction) / (1.0f + refraction);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * pow((1 - cosine), 5);
}

float ffmin(float a, float b)
{
	return a < b ? a : b;
}

float ffmax(float a, float b)
{
	return a > b ? a : b;
}

aabb surronding_box(aabb box0, aabb box1)
{
	return aabb( CVec3(ffmin(box0.get_min().x(), box1.get_min().x()),
					ffmin(box0.get_min().y(), box1.get_min().y()),
					ffmin(box0.get_min().z(), box1.get_min().z())
					),
				CVec3(ffmax(box0.get_max().x(), box1.get_max().x()),
					ffmax(box0.get_max().y(), box1.get_max().y()),
					ffmax(box0.get_max().z(), box1.get_max().z())
				));
}