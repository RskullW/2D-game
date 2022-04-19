#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets):
	m_TileSets(tilesets), m_TileSize(tilesize), m_Column(colcount), m_Row(rowcount), m_Tilemap(tilemap)
{
	for (unsigned int i = 0; i < m_TileSets.size(); ++i)
	{
		TextureManager::GetInstance()->load(m_TileSets[i].name, "../Assets/maps/" + m_TileSets[i].source);
	}

}

void TileLayer::Render()
{
	for (unsigned int i = 0; i < m_Row; ++i)
	{
		for (unsigned int j = 0; j < m_Column; ++j)
		{
			int tileID = m_Tilemap[i][j];

			if (tileID == 0)
			{
				continue;
			}

			else
			{
				int index = 0;
				if (m_TileSets.size() > 1)
				{
					for (unsigned int k = 1; k < m_TileSets.size(); ++k)
					{
						if (tileID >= m_TileSets[k].First && tileID <= m_TileSets[k].Last)
						{
							tileID = tileID + m_TileSets[k].tilecount - m_TileSets[k].Last;
							index = k;
							break;
						}
					}
				}

				Tileset ts = m_TileSets[index];
				int tileRow = tileID / ts.column;
				int tileCol = tileID - tileRow * ts.column - 1;

				if (tileID % ts.column == 0)
				{
					tileRow--;
					tileCol = ts.column - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.name, ts.tilesize, j * ts.tilesize, i * ts.tilesize, tileRow, tileCol);

			}
		}
	}
}

void TileLayer::Update()
{

}
