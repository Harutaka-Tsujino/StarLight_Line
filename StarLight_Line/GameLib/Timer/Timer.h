#ifndef TIMER_H_
#define TIMER_H_

#include <Windows.h>
#include <chrono>

/**
 *@file Timer.h
 *@brief 時間を計るクラスのヘッダ
 *@author tatsuya-kinoshita
 */

/**
 *@brief 
 */
class Timer
{
public:
	Timer() {};
	~Timer() {};

	VOID Start();					
	VOID End();						
	VOID Reset();					
	VOID Stop();					
	VOID Restart();					//経過時間分スタート時間をたしていく
	LONGLONG GetSecond();			//秒を取得
	LONGLONG GetMilliSecond();		//ミリ秒取得
	LONGLONG GetMicroSecond();		//マイクロ秒取得

private:
	typedef std::chrono::duration<
		std::chrono::system_clock::rep,
		std::chrono::system_clock::period> DebugDiffTime;

	std::chrono::system_clock::time_point	m_StartTime;	//!< 計測開始時間.
	std::chrono::system_clock::time_point	m_StartTimeBuff;
	DebugDiffTime m_DiffTime;								//!< 計測時間.
	BOOL m_isStoped = FALSE;
};

#endif // !TIMER_H_
