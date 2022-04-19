#include "mapParser.h"

mapParser* mapParser::s_Instance = nullptr;

bool mapParser::load(const char* mapString)
{
	return Parse("MAP", mapString);
}

Tileset mapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
	Tileset tileset;
	tileset.name = xmlTileSet->Attribute("name");
	xmlTileSet->Attribute("firstgid", &tileset.First);

	xmlTileSet->Attribute("tilecount", &tileset.tilecount);
	tileset.Last = (tileset.First + tileset.tilecount) - 1;

	xmlTileSet->Attribute("columns", &tileset.column);
	tileset.row = tileset.tilecount / tileset.column;
	xmlTileSet->Attribute("tilewidth", &tileset.tilesize);

	TiXmlElement* image = xmlTileSet->FirstChildElement();
	tileset.source = image->Attribute("source");

	return tileset;
}

TileLayer* mapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
	TiXmlElement* data = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			data = e;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
	
	for (int row = 0; row < rowcount; ++row)
	{
		for (int col = 0; col < colcount; ++col)
		{
			getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good())
				break;
		}
	}

	return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

bool mapParser::Parse(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cerr << "Failed to load: " << source << '\n';
		return false;
	}

	TiXmlElement* root = xml.RootElement();

	int rowcount, colcount, tilesize = 0;

	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);

	TilesetList tilesets;

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileSet(e));
		}
	}

	Map* gamemap = new Map();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayers.push_back(tilelayer);
		}
	}

	m_MapDict[id] = gamemap;

	return true;
}

void mapParser::Clean()
{
	std::map<std::string, Map*>::iterator it;

	for (it = m_MapDict.begin(); it != m_MapDict.end(); ++it)
	{
		it->second = nullptr;
	}

	m_MapDict.clear();
}