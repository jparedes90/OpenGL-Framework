#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <iostream>
#include <string>
#include <fstream>


#ifdef _WIN32
#include <Windows.h>
#undef DEBUG
#endif

#include <stdlib.h>

class Log
{
public:
	enum LogLevel
	{
		TRACE = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERR = 4,
	};
	static LogLevel m_currentLogLevel;

	static void Error(const std::string& msg);
	static void Warning(const std::string& msg);
	static void Info(const std::string& msg);
	static void Debug(const std::string& msg);
	static void Trace(const std::string& msg);
};

#endif