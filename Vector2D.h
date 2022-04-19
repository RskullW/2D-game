#pragma once
#include <iostream>

class Vector2D
{
public:
	float X, Y;

public:
	Vector2D(float x = 0, float y = 0) :X(x), Y(y) {};

public:
	inline Vector2D operator+(const Vector2D& left)
	{
		return Vector2D(X + left.X, Y + left.Y);
	}

	inline Vector2D operator-(const Vector2D& left)
	{
		return Vector2D(X - left.X, Y - left.Y);
	}
	
	inline Vector2D operator*(const float scalar)
	{
		return Vector2D(X * scalar, Y * scalar);
	}

	void Log(std::string msg = "")
	{
		std::cout << msg << "(X, Y) = (" << X << ", " << Y << ")\n";
	}
};

