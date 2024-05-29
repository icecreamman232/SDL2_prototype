#include "ExpController.h"

void ExpController::Initialize(int multiple)
{
	//There's original max xp for each level at scale of level 1
	//In new round, there's multiply factor will be multiply with 
	// this array of max xp to get new max xp for this level


	m_multipleFactor = multiple;
	m_curXP = 0;
	m_curLevel = 0;


	//Mutiply new factor to max xp array
	for (int i = 0; i < m_originalXPArray.size(); i++)
	{
		m_curMaxXPPerLevel[i] = m_originalXPArray[i];
		m_curMaxXPPerLevel[i] *= m_multipleFactor;
	}
}

void ExpController::AddXP(int xp)
{
	m_curXP += xp;
	if (m_curXP >= m_curMaxXPPerLevel[m_curLevel])
	{
		LevelUp();
		m_curXP = 0;
	}
}

void ExpController::LevelUp()
{
	m_curLevel++;
	if (m_curLevel > m_curMaxXPPerLevel.size())
	{
		m_curLevel = m_curMaxXPPerLevel.size() - 1;
	}
}

