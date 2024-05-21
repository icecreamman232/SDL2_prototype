#include "Scene.h"
#include "algorithm"

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

