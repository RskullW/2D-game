#pragma once
#include <SDL2/SDL.h>
#include <string>

class Animation
{
public:
	Animation(bool repeat = true) : m_Repeat(repeat) { m_Ended = 0; };

	virtual void Update(float dt) = 0;
	inline bool getEnded() { return m_Ended; }
protected:
	bool m_Repeat;
	bool m_Ended;
	int m_CurFrame;
};

