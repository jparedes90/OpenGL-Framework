#include "Logger.h"
using namespace std;

Log::LogLevel Log::m_currentLogLevel = Log::LogLevel::TRACE;

void Log::Error(const string& msg)
{
	if (m_currentLogLevel <= ERR)
	{
		cerr << "!! ERROR: " << msg << endl;
	}
}

void Log::Warning(const string& msg)
{
	if (m_currentLogLevel <= WARN)
	{
		cerr << "! WARN : " << msg << endl;
	}
}

void Log::Info(const string& msg)
{
	if (m_currentLogLevel <= INFO)
	{
		cout << "+ Info: " << msg << endl;
	}
}

void Log::Debug(const string& msg)
{
	if (m_currentLogLevel <= DEBUG)
	{
		cout << "- Debug: " << msg << endl;
	}
}

void Log::Trace(const string& msg)
{
	if (m_currentLogLevel <= TRACE)
	{
		cout << ". Trace: " << msg << endl;
	}
}