#include "ray.h"

float CRay::hit_sphere(const CVec3& center, float R)
{
	CVec3 vecOC = _origin - center;
	float a = dot_product(_direction, _direction);
	float b = 2.0f * dot_product(vecOC,_direction);
	float c = dot_product(vecOC, vecOC) - R * R;
	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return -1.0f;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}