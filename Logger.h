#pragma once
#include "Singleton.h"
#include <windows.h>

class Logger : public Singleton<Logger>
{
public:
	void Initialize();
	void LogMessage(const char* funcName, const char* file, int line, const char* message);
	HANDLE hConsole;
};

#define DebugLog(message) Logger::Instance().LogMessage(__FUNCTION__,__FILE__,__LINE__,message);

