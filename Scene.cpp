#include "Scene.h"

void Scene::Initialize()
{

}

void Scene::Add(GameObject* object, RenderLayer renderLayer)
{
	m_renderingContainer[renderLayer].push_back(object);
}

