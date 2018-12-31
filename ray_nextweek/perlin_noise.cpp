#include "perlin_noise.h"
#include "comm.h"

perlin_noise& perlin_noise::get_instance()
{
	static perlin_noise g_perlin_noise;
	return g_perlin_noise;
}

perlin_noise::perlin_noise()
{
	perlin_generate();
	perlin_generate_perm(&perm_x);
	perlin_generate_perm(&perm_y);
	perlin_generate_perm(&perm_z);
}

void perlin_noise::perlin_generate()
{
	_ranfloat = new float[256];
	for (int i = 0; i < 256; i++)
	{
		_ranfloat[i] = randf();
	}
}

void perlin_noise::perlin_generate_perm(int** p)
{
	*(p) = new int[256];
	for (int i = 0; i < 256; i++)
	{
		(*p)[i] = i;
	}
	permute((*p), 256);
}

void perlin_noise::permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = int(randf() * (i + 1));
		int temp = p[target];
		p[target] = p[i];
		p[i] = temp;
	}
}

float perlin_noise::noise(const CVec3& p) const
{
	float u = p.x() - floor(p.x());
	float v = p.y() - floor(p.y());
	float w = p.z() - floor(p.z());
	int i = int(p.x());
	int j = int(p.y());
	int k = int(p.z());
	float value[2][2][2];
	for (int di = 0; di < 2; di++)
		for (int dj = 0; dj < 2; dj++)
			for (int dk = 0; dk < 2; dk++)
			{
				value[di][dj][dk] = _ranfloat[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
			}

	return trilinear_interp(value, u, v, w);
}

float perlin_noise::trilinear_interp(float value[2][2][2], float u, float v, float w) const
{
	float accum = 0.0f;
	for(int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				accum += (i * u + (1 - u)*(1 - i)) * (j * v + (1 - v)*(1 - j)) * (k * w + (1 - w)*(1 - k)) * value[i][j][k];
			}

	return accum;
}