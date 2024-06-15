#include "Scene.h"
#include "algorithm"
#include <iostream>

void Scene::Add(GameObject* object, RenderLayer renderLayer)
{
	m_renderingContainer[renderLayer].push_back(object);

	std::sort(m_renderingContainer[renderLayer].begin(),
		m_renderingContainer[renderLayer].end(),
		[](GameObject* a, GameObject* b) {
			return a->GetRenderOrder() < a->GetRenderOrder();
		});
}


void Scene::Add(UIBase* UIElement)
{
	m_UIContainer.push_back(UIElement);
}

void Scene::Render()
{
	//Render objects
	for (int i=0;i<static_cast<int>(RenderLayer::COUNT); i++)
	{
		auto layer = static_cast<RenderLayer>(i);

		for (int j = 0; j < m_renderingContainer[layer].size(); j++)
		{
			if (!m_renderingContainer[layer][j]->IsActive()) continue;
			m_renderingContainer[layer][j]->Render();
		}
	}

	//Render text and UI
	for (auto element : m_UIContainer)
	{
		element->Render();
	}
}

void Scene::Remove(GameObject* object, RenderLayer renderLayer)
{
	auto& container = m_renderingContainer[renderLayer];
	auto it = std::find_if(container.begin(),container.end(),
		[object](GameObject* foundObj) 
		{
			return (foundObj->GetID() == object->GetID());
		});
	if (it != container.end())
	{
		container.erase(it);
	}
}


void Scene::RemoveAll(RenderLayer renderLayer)
{
	m_renderingContainer[renderLayer].clear();
}

void Scene::Remove(UIBase* UIElement)
{
	auto& container = m_UIContainer;
	auto it = std::find_if(container.begin(), container.end(),
		[UIElement](UIBase* foundObj)
		{
			return (foundObj->GetID() == UIElement->GetID());
		});
	if (it != container.end())
	{
		container.erase(it);
	}
}

