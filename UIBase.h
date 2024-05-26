#pragma once

/// <summary>
/// Base class for all UI element. Mean to be inherited.
/// </summary>
class UIBase
{
public:
	virtual void Render() {};
	virtual void Update() {};
protected:
};

