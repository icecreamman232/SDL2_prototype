#include "ObjectPooler.h"

ObjectPooler::ObjectPooler(int number, std::string generalName, SDL_Texture* texture,int width, int height)
{
	m_number = number;
	m_generalName = generalName;
	m_texture = texture;
	m_width = width;
	m_height = height;

	for (int i = 0; i < number; i++)
	{
		std::string name = generalName + std::to_string(i);
		GameObject* newObject = new GameObject(name.c_str(), texture, width, height);
		newObject->SetActive(false);
		m_pool.push_back(newObject);
	}
}

ObjectPooler::~ObjectPooler()
{
	// Cleanup the objects in the pool
	for (GameObject* object : m_pool) 
	{
		delete object;
	}
}

GameObject* ObjectPooler::GetPooledGameObject()
{
	if (!m_pool.empty())
	{
		GameObject* object = m_pool.back();
		m_pool.pop_back();
		m_activeList.push_back(object);
		object->SetActive(true);
		return object;
	}
	else 
	{
		std::string name = m_generalName + std::to_string(m_number);
		m_number++;
		GameObject* object = new GameObject(name.c_str(), m_texture, m_width, m_height);
		m_activeList.push_back(object);
		object->SetActive(true);
		return object;
	}
}

void ObjectPooler::ReleasePooledGameObject(GameObject* object)
{
	auto it = std::find(m_activeList.begin(), m_activeList.end(), object);
	if (it != m_activeList.end()) {
		m_activeList.erase(it);
		//TODO: Reset game object before returning it to pool
		//object->reset();
		m_pool.push_back(object);
	}
}
