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
	float trilinear_interp(const CVec3 value[2][2][2], float u, float v, float w) const;
	float turb(const CVec3& p, int depth = 7);

	static perlin_noise& get_instance();

private:
	CVec3* _ranvec3;
	int* perm_x;
	int* perm_y;
	int* perm_z;
};