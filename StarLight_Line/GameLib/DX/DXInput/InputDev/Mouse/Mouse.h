﻿#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>

#include <dinput.h>

#include "../InputDev.h"

#include <crtdbg.h>

#include <cstdio>
#include <cstdlib>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

enum DIM
{
	DIM_RIGHT,
	DIM_LEFT,
	DIM_SUB_1,
	DIM_SUB_2,
	DIM_MAX
};

class Mouse :public InputDev
{
public:
	Mouse(HWND hWnd, LPDIRECTINPUT8 pDXInput) : InputDev(hWnd)
	{
		Create(pDXInput);
	};

	~Mouse() {};

	inline VOID UpdataInputState()						//メインループの始まりで用いる
	{
		AcquireInputState();
		CheckInputStateDetatils();
	}

	inline VOID StorePrevInputState()					//メインループの終わりで用いる
	{
		memcpy(&m_prevState, &m_state, sizeof(DIMOUSESTATE));
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
	VOID Create(LPDIRECTINPUT8 pDXInput);				//基底クラスのコンストラクタでCreate(LPDIRECTINPUT8 pDXInput)を呼ぶ

	inline VOID AcquireInputState()
	{
		m_pDInputDev->Acquire();						//マウスの状態を取得する権限の取得

		GetCursorPos(&m_cursorRelativePos);				//ここではまだディスプレイ基準の絶対座標
		ScreenToClient(m_HWND, &m_cursorRelativePos);	//ここでウィンドウ基準の相対座標に変換

		m_pDInputDev->GetDeviceState(					//マウスの状態を取得
						sizeof(DIMOUSESTATE),
						&m_state);
	}

	VOID CheckInputStateDetatils();						//AcquireInputState()を読んだ後に用いる

	DIMOUSESTATE m_state;
	DIMOUSESTATE m_prevState;

	POINT m_cursorRelativePos;							//カーソルのウィンドウ基準の相対座標

	INPUT_DETAIL m_details[DIM_MAX];
};

#endif // !MOUSE_H
