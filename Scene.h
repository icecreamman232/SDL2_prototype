#pragma once
#include "Global.h"
#include <map>
#include <vector>
#include "GameObject.h"
#include "UIBase.h"

using namespace Render;

class Scene
{
public:
	void Initialize();
	void Add(GameObject* object, RenderLayer renderLayer);

	//TODO:Add text and UI to separated layer and container and render calls
	void Add(UIBase* UIElement);

	void Render();
	void Remove(GameObject* object, RenderLayer rendeLayer);
private:
	std::map<RenderLayer, std::vector<GameObject*>> m_renderingContainer;
	std::vector<UIBase*> m_UIContainer;
};

