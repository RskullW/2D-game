#pragma once
class IOobject
{
public:
	virtual void Draw() = 0;
	virtual void Update(float temp) = 0;
	virtual void Clean() = 0;

};