#pragma once
#include "Global.h"
#include <map>
#include <vector>
#include "GameObject.h"

using namespace Render;

class Scene
{
public:
	void Initialize();
	void Add(GameObject* object, RenderLayer renderLayer);
	void Render();
	void Remove(GameObject* object, RenderLayer rendeLayer);
private:
	std::map<RenderLayer, std::vector<GameObject*>> m_renderingContainer;
};

