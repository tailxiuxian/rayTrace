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
	_ranvec3 = new CVec3[256];
	for (int i = 0; i < 256; i++)
	{
		_ranvec3[i] = CVec3( 2.0f * randf() - 1.0f, 2.0f * randf() - 1.0f, 2.0f * randf() - 1.0f);
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
	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());

	CVec3 value[2][2][2];
	for (int di = 0; di < 2; di++)
		for (int dj = 0; dj < 2; dj++)
			for (int dk = 0; dk < 2; dk++)
			{
				value[di][dj][dk] = _ranvec3[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
			}

	return trilinear_interp(value, u, v, w);
}

float perlin_noise::trilinear_interp(const CVec3 value[2][2][2], float u, float v, float w) const
{
	float accum = 0.0f;
	
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);

	for(int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				CVec3 weight(u - i, v - j, w - k);
				accum += (i * uu + (1 - uu)*(1 - i)) * (j * vv + (1 - vv)*(1 - j)) * (k * ww + (1 - ww)*(1 - k)) * dot_product(value[i][j][k], weight);
			}

	return accum;
}

float perlin_noise::turb(const CVec3& p, int depth)
{
	CVec3 temp_p = p;
	float weight = 1.0f;
	float accum = 0.0f;
	for (int i = 0; i < depth; i++)
	{
		accum += weight * noise(temp_p);
		temp_p *= 2.0f;
		weight *= 0.5f;
	}
	return fabs(accum);
}