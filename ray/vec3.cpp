#include "vec3.h"

CVec3& CVec3::operator+=(CVec3& vec)
{
	value[0] += vec.value[0];
	value[1] += vec.value[1];
	value[2] += vec.value[2];
	return *this;
};

CVec3& CVec3::operator-=(CVec3& vec)
{
	value[0] -= vec.value[0];
	value[1] -= vec.value[1];
	value[2] -= vec.value[2];
	return *this;
}

CVec3& CVec3::operator*=(CVec3& vec)
{
	value[0] *= vec.value[0];
	value[1] *= vec.value[1];
	value[2] *= vec.value[2];
	return *this;
}

CVec3& CVec3::operator/=(CVec3& vec)
{
	value[0] /= vec.value[0];
	value[1] /= vec.value[1];
	value[2] /= vec.value[2];
	return *this;
}

CVec3 CVec3::operator*(float t)
{
	return CVec3(value[0] * t, value[1] * t, value[2] * t);
}

CVec3 CVec3::operator/(float t)
{
	float k = 1.0f / t;

	return CVec3(value[0] * k, value[1] * k, value[2] * k);
}

CVec3& CVec3::operator*=(float t)
{
	value[0] *= t;
	value[1] *= t;
	value[2] *= t;
	return *this;
}

CVec3& CVec3::operator/=(float t)
{
	float k = 1.0f / t;

	value[0] *= k;
	value[1] *= k;
	value[2] *= k;
	return *this;
}

void CVec3::make_unit_vector()
{
	float k = 1.0f / length();

	value[0] *= k;
	value[1] *= k;
	value[2] *= k;
}

float dot_product(const CVec3& vec1, const CVec3& vec2)
{
	return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

CVec3 cross_product(const CVec3& vec1, const CVec3& vec2)
{
	return CVec3( (vec1.y() * vec2.z() - vec1.z() * vec2.y()),
				( -(vec1.x() * vec2.z()) - vec1.z() * vec2.x()),
				(vec1.x() * vec2.y() - vec1.y() * vec2.x())
		);
}

CVec3 operator+(const CVec3& vec1, const CVec3& vec2)
{
	return CVec3(vec1.x() + vec2.x(), vec1.y() + vec2.y(), vec1.z() + vec2.z());
}

CVec3 operator-(const CVec3& vec1, const CVec3& vec2)
{
	return CVec3(vec1.x() - vec2.x(), vec1.y() - vec2.y(), vec1.z() - vec2.z());
}

CVec3 operator*(const CVec3& vec1, const CVec3& vec2)
{
	return CVec3(vec1.x() * vec2.x(), vec1.y() * vec2.y(), vec1.z() * vec2.z());
}

CVec3 operator*(const float t, const CVec3& vec)
{
	return CVec3(t * vec.x(), t * vec.y(), t * vec.z());
}

CVec3 unit_vector(const CVec3& vec)
{
	float k = 1.0f / vec.length();

	return CVec3(vec.x() * k, vec.y() * k, vec.z() * k);
}