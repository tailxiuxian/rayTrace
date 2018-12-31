#include "texture.h"
#include "perlin_noise.h"

constant_texture::constant_texture()
{}

constant_texture::constant_texture(CVec3 color)
	:_color(color)
{}

CVec3 constant_texture::color(float u, float v, const CVec3& p)
{
	return _color;
}

checker_texture::checker_texture(CVec3 color_odd, CVec3 color_even)
	:_color_odd(color_odd)
	,_color_even(color_even)
{}

CVec3 checker_texture::color(float u, float v, const CVec3& p)
{
	float sinres = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
	if (sinres < 0.0f)
	{
		return _color_odd;
	}
	else
	{
		return _color_even;
	}
}

noise_texture::noise_texture()
{}
noise_texture::noise_texture(float scale)
	:_scale(scale)
{}

CVec3 noise_texture::color(float u, float v, const CVec3& p)
{
	//return CVec3(1.0f, 1.0f, 1.0f) * perlin_noise::get_instance().turb(p);

	return CVec3(1.0f, 1.0f, 1.0f) * 0.5f * (1.0f + sin(_scale * p.z() + 10.0f * perlin_noise::get_instance().noise(p)));
}