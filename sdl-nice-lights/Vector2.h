#pragma once
#include <math.h>

class Vector2
{
public:
	Vector2(float x = 0, float y = 0);
	~Vector2();
	float x, y;

	float sqrMagnitude();
	float magnitude();

	Vector2 operator+(const Vector2&) const;
	Vector2 operator*(const float&) const;
	Vector2& operator+=(const Vector2&);
	Vector2& operator*=(const float&);

private:
	// cached
	float cachedMagnitude; 
};

