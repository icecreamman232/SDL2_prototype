#pragma once
#include <vector>

class ExpController
{
public:
	void Initialize(int multiple);
	void AddXP(int xp);
	inline int GetCurrentXP() { return m_curXP; };
	inline int GetMaxXP() { return m_curMaxXPPerLevel[m_curLevel]; };
	inline float GetXPPercent() { return ( static_cast<float>(m_curXP) / m_curMaxXPPerLevel[m_curLevel]); };
	inline int GetCurrentLv() { return m_curLevel; };
private:

	void LevelUp();

	int m_curXP;
	int m_multipleFactor;

	int m_curLevel;
	std::vector<int> m_originalXPArray = {5,10,15,
								          25,35,45,
								          65,85,125};
	std::vector<int> m_curMaxXPPerLevel = {5,10,15,
								           25,35,45,
								           65,85,125 };
};

