#pragma once
#include "UIImage.h"
#include "Selectable.h"
#include "BMTextRenderer.h"
#include <functional>

class MenuButton : public UIImage, public Selectable
{
public:
	void Init(std::string name, Render::TEXTURE_ID textureID, int x, int y, int width, int height, int spriteFrame = 0) override;
	void CleanUp();
	void Update() override;
	void OnMouseLeftClick() override;

	void SetButtonTextSize(float size);
	void SetButtonTextSpacing(float spacing);
	void SetTextPosition(float x, float y);

	using CallbackFunction = std::function<void()>;
	void SetCallBack(CallbackFunction callback);
private:

	bool m_shouldUpdate = false;
	CallbackFunction m_callback;
	BMTextRenderer m_btnText;
};

