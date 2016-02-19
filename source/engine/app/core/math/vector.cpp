#include "vector.h"
#include <math.h>
#include "SDL/SDL.h"

Vector2 Vector2::Unit(float degrees)
{
	float radians = (float)(degrees * M_PI / 180.0);
	return Vector2(cos(radians), sin(radians));
}

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Normalize()
{
	float mag = Length();
	return Vector2(x / mag, y / mag);
}

Vector2 Vector2::operator * (float maginitude)
{
	return Vector2(x*maginitude, y* maginitude);
}