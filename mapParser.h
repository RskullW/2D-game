#pragma once
#include <string>
#include <map>
#include "Map.h"
#include "TileLayer.h"
#include "tinyxml.h"

class mapParser
{
public:
	static mapParser* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new mapParser();
	}
	inline Map* GetMaps(std::string id) { return m_MapDict[id]; };
	bool load(const char* mapString);
	void Clean();

private:
	bool Parse(std::string id, std::string source);
	Tileset ParseTileSet(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);
private:
	mapParser() {}
	static mapParser* s_Instance;
	std::map<std::string, Map*> m_MapDict;
};

