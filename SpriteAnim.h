#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Animation.h"

class SpriteAnim
	: public Animation
{
public:
	SpriteAnim(bool repeat = 1);

	virtual void Update(float dt);
	void Draw(float x, float y, int spritW, int spriH, float scaleX = 1.0f, float scaleY = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void setProps(std::string textureID, int sRow, int fCount, int animSpeed);

	void SetSpriteRow(int row) { m_SpriteRow = row; }
	void IncrementSpriteRow() { m_SpriteRow++; }
	void DecrementSpriteRow() { m_SpriteRow--;}

	int GetCurFrame() { return m_CurFrame; }
	int GetSpriteRow() { return m_SpriteRow; }

private:
	int m_SpriteRow, m_animSpeed, m_frameCount;
	std::string m_textureID;
};



