#pragma once
class ExpController
{
public:

	inline void AddXP(int xp) { m_curXP += xp; };
	inline void SetCurrentXP(int xp) { m_curXP = xp; };
	inline int GetCurrentXP() { return m_curXP; };

private:
	int m_curXP;

};

