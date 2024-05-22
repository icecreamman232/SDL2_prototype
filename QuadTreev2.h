#pragma once
#include <vector>
#include "GameObject.h"
#include "SDL.h"

class QuadTreev2
{

public:
	static const int MAX_DEPTH = 5;
	static const int LIMIT_OBJECT = 4;

	//F**k my brain. 
	// I cant remember whether is east on the left or west is on the right so I use top,left,bot,right
	QuadTreev2* topleft;
	QuadTreev2* topright;
	QuadTreev2* botleft;
	QuadTreev2* botright;
	std::vector<GameObject*> objectList;

	int TreeID;
	bool IsLeaf;
	int Depth;

	QuadTreev2(const SDL_FRect& bounds,int depth,int id);
	~QuadTreev2();
	void Insert(GameObject* object);
	bool Contains(GameObject* object);
	void Remove(GameObject* object);
	void Update(GameObject* object);
	std::vector<QuadTreev2*> GetLeaves(GameObject* object);
	void Render(SDL_Renderer* render);

	std::vector<GameObject*> GetAllCollisions(GameObject* object1);
	GameObject* GetCollision(GameObject* object, Layer targetLayer = Layer::DEFAULT);

private:

	
	SDL_FRect m_bounds;

};

