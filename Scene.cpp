#include "Scene.h"
#include "algorithm"
#include <iostream>

void Scene::Initialize()
{

}

void Scene::Add(GameObject* object, RenderLayer renderLayer)
{
	m_renderingContainer[renderLayer].push_back(object);

	std::sort(m_renderingContainer[renderLayer].begin(),
		m_renderingContainer[renderLayer].end(),
		[](GameObject* a, GameObject* b) {
			return a->GetRenderOrder() < a->GetRenderOrder();
		});
}

void Scene::Render()
{
	for (int i=0;i<static_cast<int>(RenderLayer::COUNT); i++)
	{
		auto layer = static_cast<RenderLayer>(i);

		for (int j = 0; j < m_renderingContainer[layer].size(); j++)
		{
			m_renderingContainer[layer][j]->Render();
		}
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

