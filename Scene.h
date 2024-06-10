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
	void Add(GameObject* object, RenderLayer renderLayer);
	void Add(UIBase* UIElement);

	void Render();
	void Remove(GameObject* object, RenderLayer rendeLayer);
	void Remove(UIBase* UIElement);
private:
	std::map<RenderLayer, std::vector<GameObject*>> m_renderingContainer;
	std::vector<UIBase*> m_UIContainer;
};

