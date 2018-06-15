#include "Vector2.h"


Vector2::Vector2(float x, float y) : x(x), y(y)
{
	cachedMagnitude = -1;
}

Vector2::~Vector2()
{
}

float Vector2::sqrMagnitude()
{
	return x * x + y * y;
}

float Vector2::magnitude()
{
	if (cachedMagnitude < 0)
		cachedMagnitude = sqrt(sqrMagnitude());

	return cachedMagnitude;
}

Vector2 Vector2::normalized()
{
	Vector2 v(x, y);
	v.normalize();
	return v;
}

void Vector2::normalize()
{
	operator*= (1.0f / magnitude());
}

Vector2 Vector2::operator+(const Vector2 & vec) const
{
	Vector2 result;
	result.x = x + vec.x;
	result.y = y + vec.y;
	return result;
}

Vector2 Vector2::operator-(const Vector2 &vec) const
{
	Vector2 result;
	result.x = x - vec.x;
	result.y = y - vec.y;
	return result;
}

Vector2 Vector2::operator*(const float & f) const
{
	Vector2 vec;
	vec.x = x * f;
	vec.y = y * f;
	return vec;
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 &vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2 & Vector2::operator*=(const float & f)
{
	x *= f;
	y *= f;
	return *this;
}
