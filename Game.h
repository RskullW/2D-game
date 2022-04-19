#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Map.h"
#include <iostream>
#include "GameObject.h"
#include "menu.h"

#define MAP_WIDTH 8160//10384
#define MAP_HEIGHT 1024//640
#define SCREEN_WIDTH 960//1280
#define SCREEN_HEIGHT 640//480
#define VIEW_WIDTH 480
#define VIEW_HEIGHT 320
class Game
{
public:
	static Game* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr)? s_Instance : new Game();
	}

	void init(const char*, int xpos, int ypos, int w, int h, bool fullscreen);
	void Update();
	void renderer();
	void clean();
	void handleEvents();
	inline void set_mbRunning(bool running) { m_bRunning = running; }
	inline bool running() { return m_bRunning; }
	inline SDL_Renderer* GetRenderer() { return m_pRenderer; }
	inline Map* GetMap() { return m_LevelMap; }

private:
	Game() {};
	bool m_bRunning = 1;
	Map* m_LevelMap;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	static Game* s_Instance;

	std::vector<GameObject*> m_GameObjects;
};