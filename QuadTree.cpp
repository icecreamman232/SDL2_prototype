#include "QuadTree.h"


QuadTree::QuadTree(const SDL_FRect& bounds, Uint8 r, Uint8 g, Uint8 b)
{
	m_bounds = bounds;
	red = r;
	green = g;
	blue = b;
}

/// <summary>
/// Check if game object is in node bounds/region
/// </summary>
/// <param name="gameObject">Game object to be checked</param>
/// <returns>Return true if game object is in the bounds</returns>
bool QuadTree::Contain(GameObject& gameObject)
{
	if (gameObject.Rect().x >= m_bounds.x
		&& gameObject.Rect().y >= m_bounds.y
		&& gameObject.Rect().x < m_bounds.x + m_bounds.w
		&& gameObject.Rect().y < m_bounds.y + m_bounds.h)
	{
		return true;
	}

	return false;
}

void QuadTree::Insert(GameObject& gameObject)
{
	//If game object is not in the region, we wont insert it to the node
	if (!Contain(gameObject))
	{
		return;
	}

	if (m_gameObjectList.size() < MAX_GAME_OBJECTS)
	{
		m_gameObjectList.push_back(gameObject);
	}
	//If this node region has no space, 
	//we slit the node into small node and distribute game objects to new child nodes
	else 
	{
		if (m_childNodeList.empty())
		{
			Split();
		}
		for (auto& child : m_childNodeList)
		{
			child.Insert(gameObject);
		}
	}
}

void QuadTree::Split()
{
	float childNodeWidth = m_bounds.w / 2;
	float childNodeHeight = m_bounds.h / 2;
	float childX = m_bounds.x;
	float childY = m_bounds.y;


	m_childNodeList.emplace_back(SDL_FRect { childX , childY , childNodeWidth, childNodeHeight },rand() % 255,rand()%255, rand()%255);
	m_childNodeList.emplace_back(SDL_FRect{ childX + childNodeWidth , childY , childNodeWidth, childNodeHeight }, rand() % 255, rand() % 255, rand() % 255);
	m_childNodeList.emplace_back(SDL_FRect{ childX , childY + childNodeHeight , childNodeWidth, childNodeHeight }, rand() % 255, rand() % 255, rand() % 255);
	m_childNodeList.emplace_back(SDL_FRect{ childX + childNodeWidth, childY + childNodeHeight, childNodeWidth, childNodeHeight },rand()%255,rand()%255, rand()%255);
}

void QuadTree::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	SDL_RenderDrawRectF(renderer, &m_bounds);

	if (!m_childNodeList.empty()) {
		for (auto& subnode : m_childNodeList)
		{
			subnode.Render(renderer);
		}	
	}
}

std::vector<GameObject*> QuadTree::CheckCollision(GameObject& target)
{
	std::vector<GameObject*> objectInRange;

	if (!Contain(target))
	{
		return objectInRange;
	}

	for (auto object : m_gameObjectList)
	{
		if (object.IsCollideWith(&target))
		{
			objectInRange.push_back(&object);
		}
	}

	//This node has childrens, we need to check collision with them as well
	if (!m_childNodeList.empty())
	{
		for (auto child: m_childNodeList)
		{
			auto subObjectInRange = child.CheckCollision(target);
			objectInRange.insert(objectInRange.end(), subObjectInRange.begin(), subObjectInRange.end());
		}
	}

	return objectInRange;
}
