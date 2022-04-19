#pragma once
#include "Layer.h"
#include <vector>
class Map:
	public Layer
{
public:
	void Render()
	{
		for (unsigned int i = 0; i < m_MapLayers.size(); ++i)
		{
			m_MapLayers[i]->Render();
		}
	}

	void Update()
	{
		for (unsigned int i = 0; i < m_MapLayers.size(); ++i)
		{
			m_MapLayers[i]->Render();
		}
	}

	std::vector<Layer*> GetMapLayers() { return m_MapLayers; }
private:
	friend class mapParser;
	std::vector<Layer*> m_MapLayers;
};

