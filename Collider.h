#pragma once

#include <SDL2/SDL.h>

class Collider
{
public:
	inline SDL_Rect Get() { return m_Box; }
	inline void SetBuff(int x, int y, int w, int h) { m_Buff = { x,y,w,h }; }
	void Set(int x, int y, int w, int h)
	{
		m_Box = { x - m_Buff.x, y - m_Buff.y, w - m_Buff.w, h - m_Buff.h };
	}
private:
	SDL_Rect m_Box;
	SDL_Rect m_Buff;
};

