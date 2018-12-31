#pragma once

#include "vec3.h"

class perlin_noise
{
public:
	perlin_noise();

	void perlin_generate();
	void perlin_generate_perm(int** p);
	void permute(int* p, int n);
	float noise(const CVec3& p) const;
	float trilinear_interp(float value[2][2][2], float u, float v, float w) const;

	static perlin_noise& get_instance();

private:
	float* _ranfloat;
	int* perm_x;
	int* perm_y;
	int* perm_z;
};