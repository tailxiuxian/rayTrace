#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

class CVec3
{
public:
	CVec3() 
	{
		value[0] = 0.0f;
		value[1] = 0.0f;
		value[2] = 0.0f;
	};

	CVec3(float x, float y, float z)
	{
		value[0] = x;
		value[1] = y;
		value[2] = z;
	}

	CVec3(const CVec3& vec)
	{
		value[0] = vec.value[0];
		value[1] = vec.value[1];
		value[2] = vec.value[2];
	}

	virtual ~CVec3() {}

	inline float x() const { return value[0]; }
	inline float y() const { return value[1]; }
	inline float z() const { return value[2]; }
	inline float r() const { return value[0]; }
	inline float g() const { return value[1]; }
	inline float b() const { return value[2]; }

	inline float length() const { return sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]); }
	inline float squared_lenght() const { return value[0] * value[0] + value[1] * value[1] + value[2] * value[2]; }
	inline void make_unit_vector();

	inline const CVec3& operator+() const { return *this; }
	inline CVec3 operator-() const { return CVec3(-value[0], -value[1], -value[2]); }
	inline float operator[](int i) const { return value[i]; }
	inline float& operator[](int i) { return value[i]; }
	
	CVec3& operator+=(CVec3& vec);
	CVec3& operator-=(CVec3& vec);
	CVec3& operator*=(CVec3& vec);
	CVec3& operator/=(CVec3& vec);
	
	CVec3 operator*(float t);
	CVec3 operator/(float t);
	CVec3& operator*=(float t);
	CVec3& operator/=(float t);

private:
	float value[3];
};

CVec3 operator+(const CVec3& vec1, const CVec3& vec2);
CVec3 operator-(const CVec3& vec1, const CVec3& vec2);
CVec3 operator*(const CVec3& vec1, const CVec3& vec2);

CVec3 operator*(const float t, const CVec3& vec);

CVec3 unit_vector(const CVec3& vec);

float dot_product(const CVec3& vec1, const CVec3& vec2);
CVec3 cross_product(const CVec3& vec1, const CVec3& vec2);