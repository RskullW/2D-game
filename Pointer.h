#pragma once

#include <iostream>

class Pointer
{
public:
	float X, Y;
	
	Pointer(float x = 0, float y = 0) : X(x), Y(y) {}

	inline Pointer operator+ (const Pointer& p2) const
	{
		return Pointer(X + p2.X, Y + p2.Y);
	}

	inline Pointer operator- (const Pointer& p2) const
	{
		return Pointer(X - p2.X, Y - p2.Y);
	}

	inline friend Pointer operator-= (Pointer& p1, const Pointer& p2)
	{
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	inline Pointer operator* (const float scalar) const
	{
		return Pointer(X*scalar, Y*scalar);
	}

	void Log(std::string msg = "")
	{
		std::cout << msg << "(X, Y) = (" << X << ", " << Y << ")\n";
	}
};

