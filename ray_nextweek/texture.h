#pragma once

#include "vec3.h"

class texture
{
public:
	virtual CVec3 color(float u, float v, const CVec3& p) = 0;
};

class constant_texture : public texture
{
public:
	constant_texture();
	constant_texture(CVec3 color);
	virtual CVec3 color(float u, float v, const CVec3& p);

private:
	CVec3 _color;
};

class checker_texture : public texture
{
public:
	checker_texture(CVec3 color_odd, CVec3 color_even);
	virtual CVec3 color(float u, float v, const CVec3& p);

private:
	CVec3 _color_odd;
	CVec3 _color_even;
};

class noise_texture : public texture
{
public:
	noise_texture();
	virtual CVec3 color(float u, float v, const CVec3& p);
};