#include "Timer.h"

__int64 Timer::m_prevFrame = 0;
__int64 Timer::m_currentFrame = 0;
__int64 Timer::m_freq = 0;
float Timer::m_deltaTime = 0;
float Timer::MAX_REFRESH_TIME = 1.0f / 6.0f;

void Timer::Update()
{
	m_deltaTime = 0.0f;
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentFrame);
	int deltaTicks = (int)(m_currentFrame - m_prevFrame);
	m_deltaTime = ((float)deltaTicks/(float)m_freq);
	m_prevFrame = m_currentFrame;

	if (m_deltaTime < 0.0f)
	{
		m_deltaTime = 0.0f;
	}
	else if (m_deltaTime > MAX_REFRESH_TIME)
	{
		m_deltaTime = MAX_REFRESH_TIME;
	}
}

float Timer::GetDeltaTime()
{
	return m_deltaTime;
}