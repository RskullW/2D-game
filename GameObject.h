#pragma once
#include "IOobject.h"
#include "Transform.h"
#include <SDL2/SDL.h>
#include <string>
#include "Pointer.h"

struct Properties
{
	std::string TextureID;
	int W, H;
	float X, Y;
	SDL_RendererFlip Flip;

	Properties(std::string texture, int x, int y, int w, int h, SDL_RendererFlip argFlip = SDL_FLIP_NONE)
	{
		TextureID = texture;
		X = x;
		Y = y;
		W = w;
		H = h;
		Flip = argFlip;
	}
};
class GameObject:
	public IOobject
{
public:
	GameObject(Properties* props) : m_pTextureID(props->TextureID), m_W(props->W), m_H(props->H), m_sFlip(props->Flip)
	{
		m_pTransform = new Transform(props->X, props->Y);
		
		float px = (props->X + props->W) / 2;
		float py = (props->Y + props->H) / 2;
		m_Origin = new Pointer(px, py);
	}

	inline Pointer* GetOrigin() { return m_Origin; }
	virtual void Draw() = 0;
	virtual void Update(float temp) = 0;
	virtual void Clean() = 0;

protected:
	Pointer* m_Origin;
	Transform* m_pTransform;
	int m_W, m_H;
	std::string m_pTextureID;
	SDL_RendererFlip m_sFlip;
};

