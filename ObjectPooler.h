#pragma once
#include <vector>
#include "GameObject.h"
#include <string>


 class ObjectPooler
{
public:
	ObjectPooler(int number, std::string generalName, SDL_Texture* texture, int width, int height);
	virtual ~ObjectPooler();
	GameObject* GetPooledGameObject();
	void ReleasePooledGameObject(GameObject* object);
private:
	std::vector<GameObject*> m_pool;
	std::vector<GameObject*> m_activeList;

	//General data of pooled game object
	std::string m_generalName;
	SDL_Texture* m_texture;
	int m_width;
	int m_height;
	int m_number;
};

