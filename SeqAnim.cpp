#include <iostream>
#include "SeqAnim.h"
#include "tinyxml.h"
#include "TextureManager.h"

SeqAnim::SeqAnim(bool repeat) :Animation(repeat) {}

void SeqAnim::DrawFrame(float x, float y, float scaleX, float scaleY, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->Draw(m_CurrentSeq.textureID[m_CurFrame], x, y, m_CurrentSeq.w, m_CurrentSeq.h, scaleX, scaleY, flip);
}

void SeqAnim::Update(float dt)
{
	if (m_Repeat || !m_Ended)
	{
		m_Ended = 0;
		m_CurFrame = (SDL_GetTicks() / m_CurrentSeq.speed) % m_CurrentSeq.frameCount;
	}

	if (!m_Repeat && m_CurFrame == (m_CurrentSeq.frameCount - 1))
	{
		m_Ended = 1;
		m_CurFrame = (m_CurrentSeq.frameCount - 1);
	}
}

void SeqAnim::SetCurrentSeq(std::string seqID)
{
	if (m_seqMap.count(seqID) > 0)
	{
		m_CurrentSeq = m_seqMap[seqID];
	}

	else
	{
		std::cout << "Animation is not matching: " << seqID << '\n';
	}
}

void SeqAnim::Parse(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cout << "Failed to load animation: " << source << '\n';
	}

	TiXmlElement* root = xml.RootElement();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("sequence"))
		{
			Sequence seq;
			std::string seqID = e->Attribute("id");
			e->Attribute("speed", &seq.speed);
			e->Attribute("width", &seq.w);
			e->Attribute("height", &seq.h);
			e->Attribute("frameCount", &seq.frameCount);

			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
			{
				seq.textureID.push_back(frame->Attribute("textureID"));
			}
			m_seqMap[seqID] = seq;
		}
	}
}