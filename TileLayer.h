#pragma once

#include "Layer.h"
#include <string>
#include <vector>

struct Tileset
{
	int First, Last,row, column, tilecount, tilesize;
	std::string name, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer:
	public Layer
{
public:
	TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return m_Tilemap; }
private:

	int m_TileSize, m_Row, m_Column;
	TileMap m_Tilemap;
	TilesetList m_TileSets;

};

