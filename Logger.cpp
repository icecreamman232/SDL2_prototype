#include "Logger.h"
#include <iostream>

void Logger::Initialize()
{
	//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::LogMessage(const char* funcName, const char* file, int line, const char* message)
{
    std::cout << message << "([" << file << "]:" << line << " in " << funcName << ")" << std::endl;
    //SetConsoleTextAttribute(hConsole, 1);
    //SetConsoleTextAttribute(hConsole, 7);
}
