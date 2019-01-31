#include "Timer.h"

VOID Timer::Start()
{
	Reset();
	m_StartTime = std::chrono::system_clock::now();
}

VOID Timer::End()
{
	//Restart();
	m_DiffTime = std::chrono::system_clock::now() - m_StartTime;
}

VOID Timer::Reset()
{
	m_DiffTime = m_DiffTime.zero();
}

VOID Timer::Stop()
{
	if (m_isStoped)
	{
		return;
	}

	m_isStoped = TRUE;

	m_StartTimeBuff = std::chrono::system_clock::now();
}

VOID Timer::Restart()
{
	m_isStoped = FALSE;

	m_StartTime += (std::chrono::system_clock::now() - m_StartTimeBuff);
}

LONGLONG Timer::GetSecond()
{
	End();
	return std::chrono::duration_cast<std::chrono::seconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMilliSecond()
{
	End();
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMicroSecond()
{
	End();
	return std::chrono::duration_cast<std::chrono::microseconds>(m_DiffTime).count();
}
