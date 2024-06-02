#pragma once
#include "AssetManager.h"
#include "GameObject.h"

class IItem : public GameObject
{
public:
	IItem();
	void Initialize(const char* name, TEXTURE_ID textureID, float initX, float initY, int width, int height, int order = 0);
	void PickedUp();
protected:
	static int s_nextID;
	bool m_isInitialized;
	bool m_isPickedUp;
};

