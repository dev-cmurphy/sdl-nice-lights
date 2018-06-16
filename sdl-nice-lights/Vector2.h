#pragma once
#include <math.h>
#include <bitset>

class Vector2
{
public:
	Vector2(std::bitset<64>);
	Vector2(float x = 0, float y = 0);
	~Vector2();
	float x, y;

	float sqrMagnitude();
	float magnitude();

	Vector2 normalized();
	void normalize();

	Vector2 operator+(const Vector2&) const;
	Vector2 operator-(const Vector2&) const;
	Vector2 operator*(const float&) const;
	Vector2 operator/(const float&) const;
	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(const float&);
	Vector2& operator/=(const float&);

	std::bitset<64> toBitset();

private:
	// cached
	float cachedMagnitude; 
};

