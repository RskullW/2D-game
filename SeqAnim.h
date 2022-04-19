#pragma once

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Animation.h"

struct Sequence
{
	int speed;
	int frameCount;
	int w;
	int h;
	std::vector<std::string> textureID;
};
class SeqAnim
	: public Animation
{
public:
	SeqAnim(bool repeat = true);

	virtual void Update(float dt);
	void Parse(std::string source);
	void SetCurrentSeq(std::string seqID);
	void setRepeat(bool repeat) { m_Repeat = repeat; }
	void DrawFrame(float x, float y, float scaleX = 1, float scaleY = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	Sequence m_CurrentSeq;
	std::map<std::string, Sequence> m_seqMap;

};

