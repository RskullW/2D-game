#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <map>

class TextureManager
{
public:
	static TextureManager * GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
	}

	void Drop(std::string id);
	void clean();
	void DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip FLIP = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int w, int h, int r, int f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(std::string id, int x, int y, int w, int h, float scaleX = 1, float scaleY = 1, float scroll = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* getTexture(std::string m_idTexture){return m_pTexture[m_idTexture];}
	bool load(std::string id, std::string filename);
	bool ParseTextures(std::string source);

    bool ParseSounds(std::string source);

private:
	TextureManager() {};
	static TextureManager* s_Instance;
	std::map<std::string, SDL_Texture*> m_pTexture;
};
