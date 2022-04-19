#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "TileLayer.h"
#include "Map.h"
#include "Game.h"

class CollisionHandler
{
public:
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);

	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler; }

private:
	CollisionHandler();
	static CollisionHandler* s_Instance;
	TileMap m_LayerTileMap;
	TileLayer* m_CollisionLayer;
};

