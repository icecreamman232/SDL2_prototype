#pragma once

/// <summary>
/// Base class for all UI element. Mean to be inherited.
/// </summary>
class UIBase
{
public:
	virtual void Render() {};
	virtual void Update() {};
	inline int GetID() { return m_id; };
protected:
	int m_id;
	static int  s_next_UIID;
};


