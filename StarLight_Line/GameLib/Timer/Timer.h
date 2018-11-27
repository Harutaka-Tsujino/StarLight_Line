#ifndef TIMER_H_
#define TIMER_H_

#include <Windows.h>
#include <chrono>

/**
 *@file Timer.h
 *@brief ���Ԃ��v��N���X�̃w�b�_
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

	VOID Start();					//�^�C�}�[�J�n
	VOID End();						//�^�C���J�E���g���I��
	VOID Reset();					//�^�C�}�[���Z�b�g
	LONGLONG GetSecond();			//�b���擾
	LONGLONG GetMilliSecond();		//�~���b�擾
	LONGLONG GetMicroSecond();		//�}�C�N���b�擾

private:
	typedef std::chrono::duration<
		std::chrono::system_clock::rep,
		std::chrono::system_clock::period> DebugDiffTime;

	std::chrono::system_clock::time_point	m_StartTime;	//!< �v���J�n����.
	DebugDiffTime m_DiffTime;								//!< �v������.
};

#endif // !TIMER_H_
