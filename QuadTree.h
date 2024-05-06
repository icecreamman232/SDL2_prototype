#pragma once
#include <vector>
#include "GameObject.h"

class QuadTree
{

public:
	QuadTree(const SDL_FRect& m_bounds, Uint8 r,Uint8 g, Uint8 b);
	void Insert(GameObject& gameObject);
	void Split();
	void Render(SDL_Renderer* renderer);
	void Update();
	void Remove(GameObject* gameObject);
	std::vector<GameObject*> CheckCollision(GameObject& targer);

private:
	static const int MAX_GAME_OBJECTS = 4;

	Uint8 red;
	Uint8 green;
	Uint8 blue;

	std::vector<GameObject> m_gameObjectList;
	std::vector<QuadTree> m_childNodeList;
	SDL_FRect m_bounds;

	bool Contain(GameObject& gameObject);
};

