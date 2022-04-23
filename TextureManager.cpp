#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"
#include "tinyxml.h"
#include "soundGame.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::ParseSounds(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error())
    {
        SDL_Log("Error load music");
        return false;
    }

    TiXmlElement* root = xml.RootElement();

    for (TiXmlElement* e = root->FirstChildElement(); e!=nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("effect")) {
            soundGame::GetInstance()->loadEffect(e->Attribute("id"), e->Attribute("source"));
            continue;
        }

        if (e->Value() == std::string("music")) {
            soundGame::GetInstance()->loadMusic(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
    }

    return true;
}

void TextureManager::clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;

	for (it = m_pTexture.begin(); it != m_pTexture.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
	}

    soundGame::GetInstance()->clean();

	m_pTexture.clear();
}

bool TextureManager::ParseTextures(std::string source)
{
	TiXmlDocument xml;

	xml.LoadFile(source);

	if (xml.Error())
	{
		SDL_Log("Failed to loaded\n");
		return 0;
	}
	
	TiXmlElement* root = xml.RootElement();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("texture"))
		{
			std::string id = e->Attribute("id");
			std::string src = e->Attribute("source");
			load(id, src);
		}
	}

	return 1;
}
bool TextureManager::load(std::string id, std::string filename)
{
	SDL_Surface* m_tSurface = IMG_Load(filename.c_str());

	if (m_tSurface == 0)
	{
		SDL_Log("Failed to load surface: %s. Way texture: %s", SDL_GetError(), filename.c_str());
		return false;
	}

	SDL_Texture* m_tTexture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), m_tSurface);

	if (m_tTexture == 0)
	{
		SDL_Log("Failed to load texture: %s. Way texture: %s", SDL_GetError(), filename.c_str());
		return false;
	}

	m_pTexture[id] = m_tTexture;
	return true;
}
void TextureManager::Draw(std::string id, int x, int y, int w, int h, float scaleX, float scaleY, float scroll, SDL_RendererFlip flip)
{
	SDL_Rect source = { 0, 0, w, h };

	Vector2D tempCamera = Camera::GetInstance()->GetPosition()*scroll;
	SDL_Rect dest = { int(x - tempCamera.X), int(y - tempCamera.Y), int(w*scaleX), int(h*scaleY) };

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_pTexture[id], &source, &dest, 0, nullptr, flip);
}
void TextureManager::DrawFrame(std::string id, int x, int y, int w, int h, int r, int f, SDL_RendererFlip flip)
{
	SDL_Rect source = { w * f, h * r, w, h };
	Vector2D tempCamera = Camera::GetInstance()->GetPosition();
	SDL_Rect dest = { int(x-tempCamera.X), int(y-tempCamera.Y), w, h };
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_pTexture[id], &source, &dest, 0, nullptr, flip);
}
void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(m_pTexture[id]);
	m_pTexture.erase(id);
}

void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip FLIP)
{
	SDL_Rect source = { tilesize * frame, tilesize *row, tilesize, tilesize };
	Vector2D tempCamera = Camera::GetInstance()->GetPosition();
	SDL_Rect dest = { int(x - tempCamera.X), int(y - tempCamera.Y), tilesize, tilesize };

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_pTexture[tilesetID], &source, &dest, 0, 0, FLIP);

}
