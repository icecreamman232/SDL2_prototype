#pragma once
#include "Singleton.h"
#include <string>
#include <fstream>
#include <sstream>

struct SaveData
{
	int NumberEnemeKilled;
	int CoinAmount;
};


class SaveManager : public Singleton<SaveManager>
{
public:
	void SaveToFile();
	void LoadFromFile();
	SaveData* GetData();
	void SaveEnemyKilledNumber(int number);
	void SaveCoinAmount(int number);

	~SaveManager() override;
private:
	std::ofstream m_fileStream;
	SaveData m_data;
	std::string m_savePath = "Asset/Save";
};


