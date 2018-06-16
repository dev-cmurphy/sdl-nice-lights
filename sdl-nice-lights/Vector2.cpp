#include "Vector2.h"


Vector2::Vector2(std::bitset<64> bits)
{
	int ix, iy;

	// splits
	// 32 bit pour x et y
	// le premier bit est le signe

	if (bits[31]) { // si le x est négatif 
		bits[31] = 0;
		ix = (int)(bits << 32 >> 32).to_ulong();
		ix *= -1;
	}
	else {
		ix = (int)(bits << 32 >> 32).to_ulong();
	}

	//pour avoir le y
	bits >>= 32;

	if (bits[31]) { 
		bits[31] = 0;
		iy = (int)(bits).to_ulong();
		iy *= -1;
	}
	else {
		iy = (int)(bits).to_ulong();
	}

	x = ix;
	y = iy;
}

Vector2::Vector2(float fx, float fy) : x(fx), y(fy)
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

Vector2 Vector2::operator/(const float &f) const
{
	Vector2 vec;
	vec.x = x / f;
	vec.y = y / f;
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

Vector2 & Vector2::operator/=(const float &f)
{
	x /= f;
	y /= f;
	return *this;
}

std::bitset<64> Vector2::toBitset()
{
	std::bitset<64> data;
	int ix, iy;
	ix = x;
	iy = y;

	// splits
	// 32 bit pour x et y
	// le premier bit est le signe

	if (iy >= 0) {
		data |= iy;
		data[31] = 0; 
	}
	else  {
		data |= -iy;
		data[31] = 1;
	}

	// on fait de la place pour le x
	data <<= 32;

	if (ix >= 0) {
		data |= ix;
		data[31] = 0;
	}
	else {
		data |= -ix;
		data[31] = 1;
	}

	return data;
}
