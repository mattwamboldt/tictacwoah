#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

// Here we define all vector types we may need

class Vector2
{
public:
	static Vector2 Unit(float degrees);

	Vector2();
	Vector2(float x, float y);

	float Length();
	Vector2 Normalize();
	Vector2 operator * (float maginitude);

	float x, y;
};

// The difference between a point and a vector, is that a vector uses floats and has direction
// A point is just a position in space
struct Point
{
	Point() : x(0), y(0) {}
	Point(int inX, int inY) : x(inX), y(inY) {}

	int x;
	int y;

	bool operator==(const Point& rval) const 
	{
		return x == rval.x && y == rval.y;
	}
};

#endif