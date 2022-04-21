#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() 
{
	m_CollisionLayer = (TileLayer*)Game::GetInstance()->GetMap()->GetMapLayers().back();
    m_CollisionDamage = (TileLayer*)Game::GetInstance()->GetMap()->GetMapLayers().front();

	m_LayerTileMap = m_CollisionLayer->GetTileMap();
    m_LayerTileMapDamage = m_CollisionDamage->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	bool x_laps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_laps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

	return (x_laps && y_laps);
}
bool CollisionHandler::MapCollision(SDL_Rect a)
{
	int tileSize = 32, rowCount = 20, colCount = 337;

	int leftTile = a.x / tileSize, rightTile = (a.x + a.w)/tileSize;
	int topTile = a.y / tileSize, bottomTile = (a.y + a.h) / tileSize;

	if (leftTile < 0) leftTile = 0;
	if (rightTile > colCount) rightTile = colCount;
	if (topTile < 0) topTile = 0;
	if (bottomTile > rowCount) bottomTile = rowCount;

	for (int i = leftTile; i <= rightTile; ++i)
	{
		for (int j = topTile; j <= bottomTile; ++j)
		{
			if (m_LayerTileMap[j][i] > 0)
				return true;
		}
	}
	
	return false;
}

bool CollisionHandler::MapCollisionDamage(SDL_Rect a)
{
    int tileSize = 32, rowCount = 20, colCount = 337;

    int leftTile = a.x / tileSize, rightTile = (a.x + a.w)/tileSize;
    int topTile = a.y / tileSize, bottomTile = (a.y + a.h) / tileSize;

    if (leftTile < 0) leftTile = 0;
    if (rightTile > colCount) rightTile = colCount;
    if (topTile < 0) topTile = 0;
    if (bottomTile > rowCount) bottomTile = rowCount;

    for (int i = leftTile; i <= rightTile; ++i)
    {
        for (int j = topTile; j <= bottomTile; ++j)
        {
            if (m_LayerTileMapDamage[j][i] > 0)
                return true;
        }
    }

    return false;
}