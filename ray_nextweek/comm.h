#pragma once

#include "vec3.h"
#include "ray.h"
#include "aabb.h"

CVec3 color(CRay r, hitable* world, int depth);
float randf();
CVec3 random_vec_in_sphere();
CVec3 reflect(CVec3 in, CVec3 normal);
bool refract(CVec3 in, CVec3& normal, float n_over_nt, CVec3& refracted);
float schlick(float cosine, float refraction);
float ffmin(float a, float b);
float ffmax(float a, float b);
aabb surronding_box(aabb box0, aabb box1);

struct SPixelColor
{
	int ir;
	int ig;
	int ib;
};