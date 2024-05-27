#include "QuadTreev2.h"
#include <iostream>

using namespace General;

QuadTreev2::QuadTreev2(const SDL_FRect& bounds, int depth, int id)
{
	m_bounds = bounds;
	Depth = depth;
	IsLeaf = true;
	TreeID = id;

	topleft = nullptr;
	topright = nullptr;
	botleft = nullptr;
	botright = nullptr;
}

QuadTreev2::~QuadTreev2()
{
	if (!IsLeaf)
	{
		delete topleft;
		delete topright;
		delete botleft;
		delete botright;
	}
}

void QuadTreev2::Insert(GameObject* object)
{
	//If this is not leaf, we go down further to insert in the leaf
	if (!IsLeaf)
	{
		if (topleft->Contains(object))
		{
			topleft->Insert(object);
		}
		if (topright->Contains(object))
		{
			topright->Insert(object);
		}
		if (botright->Contains(object))
		{
			botright->Insert(object);
		}
		if (botleft->Contains(object))
		{
			botleft->Insert(object);
		}
	}
	else 
	{
		objectList.push_back(object);
		//Number of object in this leaf is more than limit, we split this leaf into 4 smaller leaves
		if (objectList.size() > LIMIT_OBJECT)
		{
			//If we reached max of quadtree, we stop dividing
			if (Depth >= MAX_DEPTH)
			{
				return;
			}

			IsLeaf = false;


			float childNodeWidth = m_bounds.w / 2;
			float childNodeHeight = m_bounds.h / 2;
			float childX = m_bounds.x;
			float childY = m_bounds.y;

			//Start at top-left following SDL_FRect format
			topleft = new QuadTreev2(SDL_FRect{ childX, childY, childNodeWidth, childNodeHeight }, Depth + 1, Depth + 1);
			topright = new QuadTreev2(SDL_FRect{ childX + childNodeWidth, childY, childNodeWidth, childNodeHeight }, Depth + 1, Depth + 1 + 1);
			botright = new QuadTreev2(SDL_FRect{ childX + childNodeWidth, childY + childNodeHeight, childNodeWidth, childNodeHeight }, Depth + 1, Depth + 1 + 2);
			botleft = new QuadTreev2(SDL_FRect{ childX, childY + childNodeHeight, childNodeWidth, childNodeHeight }, Depth + 1, Depth + 1 + 3);
			

			//Insert all objects to leaves and clear the list
			for (int i = 0; i < objectList.size(); i++)
			{
				if (topleft->Contains(objectList[i]))
				{
					topleft->Insert(objectList[i]);
				}
				if (topright->Contains(objectList[i]))
				{
					topright->Insert(objectList[i]);
				}
				if (botright->Contains(objectList[i]))
				{
					botright->Insert(objectList[i]);
				}
				if (botleft->Contains(objectList[i]))
				{
					botleft->Insert(objectList[i]);
				}
			}

			objectList.clear();
		}
	}

}

bool QuadTreev2::Contains(GameObject* object)
{
	if (object->Rect().x >= m_bounds.x
		&& object->Rect().y >= m_bounds.y
		&& object->Rect().x < m_bounds.x + m_bounds.w
		&& object->Rect().y < m_bounds.y + m_bounds.h)
	{
		return true;
	}
	return false;
}

void QuadTreev2::Remove(GameObject* object)
{
	if (!IsLeaf)
	{
		std::vector<QuadTreev2*> leavesToBeRemoved = GetLeaves(object);
		for (int i = 0; i < leavesToBeRemoved.size(); i++)
		{
			leavesToBeRemoved[i]->Remove(object);
		}
	}
	else 
	{
		for (int j = 0; j < objectList.size(); j++)
		{
			if (objectList[j] == object) 
			{
				objectList.erase(objectList.begin() +j);
			}
		}
	}
}

/// <summary>
/// Get all object has been collided
/// </summary>
/// <param name="object"></param>
/// <returns></returns>
std::vector<GameObject*> QuadTreev2::GetAllCollisions(GameObject* object)
{
	std::vector<GameObject*> collisionList;

	std::vector<QuadTreev2*> leaves = GetLeaves(object);
	for (int i = 0; i < leaves.size(); i++)
	{
		QuadTreev2* curLeaf = leaves[i];
		for (int j = 0; j < curLeaf->objectList.size(); j++)
		{
			if (curLeaf->objectList[j]->GetName() == object->GetName()) 
			{
				continue;
			}
			if (curLeaf->objectList[j]->IsCollideWith(object))
			{
				collisionList.push_back(curLeaf->objectList[j]);
			}
		}
	}
	return collisionList;
}

/// <summary>
/// Get first object collided.
/// </summary>
/// <param name="object"></param>
/// <returns></returns>
GameObject* QuadTreev2::GetCollision(GameObject* object, Layer targetLayer)
{
	std::vector<QuadTreev2*> leaves = GetLeaves(object);
	for (int i = 0; i < leaves.size(); i++)
	{
		QuadTreev2* curLeaf = leaves[i];
		for (int j = 0; j < curLeaf->objectList.size(); j++)
		{
			if (curLeaf->objectList[j]->GetName() == object->GetName())
			{
				continue;
			}
			if (curLeaf->objectList[j]->IsCollideWith(object) 
				//check if object is in layer combination
				&& (targetLayer & curLeaf->objectList[j]->GetLayer()) != 0)
			{
				return curLeaf->objectList[j];
			}
		}
	}

	return nullptr;
}


/// <summary>
/// Get all leaves that contain this object. One object can be contained by many leaves at a time.
/// </summary>
/// <param name="object"></param>
/// <returns></returns>
std::vector<QuadTreev2*> QuadTreev2::GetLeaves(GameObject* object)
{
	std::vector<QuadTreev2*> leaves;

	if (!IsLeaf)
	{
		if (topleft->Contains(object))
		{
			std::vector<QuadTreev2*> newLeaves = topleft->GetLeaves(object);
			leaves.insert(leaves.end(), newLeaves.begin(), newLeaves.end());
		}
		if (topright->Contains(object))
		{
			std::vector<QuadTreev2*> newLeaves = topright->GetLeaves(object);
			leaves.insert(leaves.end(), newLeaves.begin(), newLeaves.end());
		}
		if (botright->Contains(object))
		{
			std::vector<QuadTreev2*> newLeaves = botright->GetLeaves(object);
			leaves.insert(leaves.end(), newLeaves.begin(), newLeaves.end());
		}
		if (botleft->Contains(object))
		{
			std::vector<QuadTreev2*> newLeaves = botleft->GetLeaves(object);
			leaves.insert(leaves.end(), newLeaves.begin(), newLeaves.end());
		}
	}
	else 
	{
		leaves.push_back(this);
	}

	return leaves;
}

void QuadTreev2::Render(SDL_Renderer* render)
{
	return;
	if (IsLeaf)
	{
		SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		SDL_RenderDrawRectF(render, &m_bounds);
	}
	else 
	{
		if (topleft != nullptr)
		{
			topleft->Render(render);
		}
		if (topright != nullptr)
		{
			topright->Render(render);
		}
		if (botright != nullptr)
		{
			botright->Render(render);
		}
		if (botleft != nullptr)
		{
			botleft->Render(render);
		}		
	}
}
