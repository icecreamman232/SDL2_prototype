#pragma once

class ExpController
{
public:


	inline void AddXP(int xp) { m_curXP += xp; };
	inline void SetCurrentXP(int xp) { m_curXP = xp; };
	inline void SetMaxXP(int maxXP) { m_maxXP = maxXP; };
	inline int GetCurrentXP() { return m_curXP; };
	inline float GetXPPercent() { return ( static_cast<float>(m_curXP) / m_maxXP); };
private:
	int m_curXP;
	int m_maxXP;
};

