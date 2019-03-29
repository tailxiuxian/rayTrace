#pragma once

#include "vec3.h"
#include "ray.h"

CVec3 color(CRay r, hitable* world, int depth);
float randf();
CVec3 random_vec_in_sphere();
CVec3 reflect(CVec3 in, CVec3 normal);
bool refract(CVec3 in, CVec3& normal, float n_over_nt, CVec3& refracted);
float schlick(float cosine, float refraction);

struct SPixelColor
{
	int ir;
	int ig;
	int ib;
};