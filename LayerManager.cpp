#include "LayerManager.h"

void LayerManager::SetLayer(GameObject* object, Layer layer)
{
	m_layerContainer[layer] = object;
}

Layer LayerManager::GetLayer(GameObject* object)
{
    for (const auto& layerPair : m_layerContainer)
    {
        if (layerPair.second == object)
        {
            return layerPair.first;
        }
    }
}


