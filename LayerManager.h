#pragma once
#include "Singleton.h"
#include "Global.h"
#include <map>

class GameObject;

class LayerManager : public Singleton<LayerManager>
{
public:
	void SetLayer(GameObject* object, Layer layer);
	Layer GetLayer(GameObject* object);
private:
	std::map<Layer, GameObject*> m_layerContainer;
};

