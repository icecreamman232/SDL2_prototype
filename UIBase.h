#pragma once
#include <string>

/// <summary>
/// Base class for all UI element. Mean to be inherited.
/// </summary>
class UIBase
{
public:
	virtual void Render() {};
	virtual void Update() {};
	inline int GetID() { return m_id; };
	inline void SetActive(bool value) { m_isActive = value; };
protected:
	bool m_isActive = true;
	std::string m_name;
	int m_id;
	static int  s_next_UIID;
};


