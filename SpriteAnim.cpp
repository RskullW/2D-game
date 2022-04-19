#include "SpriteAnim.h"
#include "TextureManager.h"

SpriteAnim::SpriteAnim(bool repeat): Animation(repeat) {}

void SpriteAnim::Draw(float x, float y, int w, int h, float scaleX, float scaleY, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(m_textureID, x, y, w, h, m_SpriteRow, m_CurFrame, flip);
}

void SpriteAnim::Update(float dt)
{
	m_CurFrame = (SDL_GetTicks() / m_animSpeed) % m_frameCount;
}

void SpriteAnim::setProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
	m_animSpeed = speed;
	m_textureID = textureID;
	m_SpriteRow = spriteRow;
	m_frameCount = frameCount;
}