﻿#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <windows.h>

#include <dinput.h>

#include "../InputDev.h"

#include <crtdbg.h>

#include <cstdio>
#include <cstdlib>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

class Keyboard :public InputDev
{
public:
	Keyboard(HWND hWnd, LPDIRECTINPUT8 pDXInput) : InputDev(hWnd)
	{
		Create(pDXInput);
	};

	~Keyboard() {};

	inline VOID UpdataInputState()		//メインループの始まりで用いる
	{
		AcquireInputState();
		CheckInputStateDetatils();
	}

	inline VOID StorePrevInputState()	//メインループの終わりで用いる
	{
		memcpy(m_prevDiks, m_diks, sizeof(DIMOUSESTATE));
	}

	inline BOOL IsPressed(INT key) const
	{
		return (m_details[key] == I_D_PRESS);
	}

	inline BOOL IsHeld(INT key) const
	{
		return (m_details[key] == I_D_HOLD);
	}

	inline BOOL IsReleased(INT key) const
	{
		return (m_details[key] == I_D_RELEASE);
	}

	inline BOOL IsNeutral(INT key) const
	{
		return (m_details[key] == I_D_NEUTRAL);
	}

private:
	VOID Create(LPDIRECTINPUT8 pDXInput);

	inline VOID AcquireInputState()
	{
		*m_pDInputDev;

		m_pDInputDev->Acquire();		//キーボードの状態を取得する権限の取得

		m_pDInputDev->GetDeviceState(	//キーボードの状態を取得
						sizeof(BYTE) * 256,
						m_diks);
	}

	VOID CheckInputStateDetatils();		//AcquireInputState()を読んだ後に用いる

	BYTE m_diks[256];					//現在ののフレームでキーが押されていた場合上位ビットが立つ
	BYTE m_prevDiks[256];				//前回のフレームでキーが押されていた場合上位ビットが立つ

	INPUT_DETAIL m_details[256];
};

#endif // !KEYBOARD_H

