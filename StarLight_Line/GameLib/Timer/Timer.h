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

	VOID Start();					//タイマー開始
	VOID End();						//タイムカウントを終了
	VOID Reset();					//タイマーリセット
	LONGLONG GetSecond();			//秒を取得
	LONGLONG GetMilliSecond();		//ミリ秒取得
	LONGLONG GetMicroSecond();		//マイクロ秒取得

private:
	typedef std::chrono::duration<
		std::chrono::system_clock::rep,
		std::chrono::system_clock::period> DebugDiffTime;

	std::chrono::system_clock::time_point	m_StartTime;	//!< 計測開始時間.
	DebugDiffTime m_DiffTime;								//!< 計測時間.
};

#endif // !TIMER_H_
