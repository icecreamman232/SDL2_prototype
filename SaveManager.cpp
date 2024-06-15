#include "SaveManager.h"
#include <iostream>

void SaveManager::SaveToFile()
{
	if (!m_fileStream.is_open())
	{
		m_fileStream.open(m_savePath + "/save.txt", std::ios::out);
	}


	if(!m_fileStream)
	{
		std::cerr << "Failed to open file for writing: " << m_savePath + "/save.txt" << std::endl;
		return;
	}

	m_fileStream << "EnemyKilled," << m_data.NumberEnemeKilled << "\n";
	m_fileStream << "CoinAmount," << m_data.CoinAmount << "\n";

	m_fileStream.close();
}

void SaveManager::LoadFromFile()
{
	std::ifstream fileStream(m_savePath + "/save.txt");

	if (!fileStream)
	{
		std::cerr << "Failed to open file for writing: " << m_savePath + "/save.txt" << std::endl;
		return;
	}

	std::string line;

	while (std::getline(fileStream,line))
	{
		std::string key;
		std::string value;
		std::istringstream iss(line);
		if (std::getline(iss, key, ',') && std::getline(iss, value))
		{
			if (key == "EnemyKilled")
			{
				m_data.NumberEnemeKilled = std::stoi(value);
			}
			else if (key == "CoinAmount")
			{
				m_data.CoinAmount = std::stoi(value);
			}
		}
	}
	fileStream.close();
}

SaveData* SaveManager::GetData()
{
	return &m_data;
}

void SaveManager::SaveEnemyKilledNumber(int number)
{
	m_data.NumberEnemeKilled = number;
}

void SaveManager::SaveCoinAmount(int number)
{
	m_data.CoinAmount = number;
}

SaveManager::~SaveManager()
{
	if (m_fileStream.is_open())
	{
		m_fileStream.close();
	}
}
