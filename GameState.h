#pragma once


class GameStateManager;

/// <summary>
/// Base class for all game state
/// </summary>
class GameState
{
public:
	virtual void Initialize(GameStateManager* manager);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void ExitState();
	virtual ~GameState() {};
	bool IsRunning() { return m_isRunning; };
protected:
	bool m_isRunning = false;
};

