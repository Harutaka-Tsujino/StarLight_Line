#include <windows.h>
#include <dinput.h>

#include "Mouse.h"

VOID Mouse::UpdataInputState()
{
	AcquireInputState();
	CheckInputStateDetatils();
}

VOID Mouse::Create(LPDIRECTINPUT8 pDXInput)
{
	pDXInput->CreateDevice(
				GUID_SysMouse,
				&m_pDInputDev,
				NULL);

	m_pDInputDev->SetDataFormat(&c_dfDIMouse);

	m_pDInputDev->SetCooperativeLevel(
					m_rHWND,
					DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD mouseProp;
	mouseProp.diph.dwSize		= sizeof(DIPROPDWORD);
	mouseProp.diph.dwHeaderSize = sizeof(mouseProp.diph);
	mouseProp.diph.dwObj		= 0;
	mouseProp.diph.dwHow		= DIPH_DEVICE;
	mouseProp.dwData			= DIPROPAXISMODE_REL;

	m_pDInputDev->SetProperty(DIPROP_AXISMODE, &mouseProp.diph);
}

inline VOID Mouse::AcquireInputState()
{
	m_pDInputDev->Acquire();						//マウスの状態を取得する権限の取得

	GetCursorPos(&m_cursorRelativePos);				//ここではまだディスプレイ基準の絶対座標
	ScreenToClient(m_rHWND, &m_cursorRelativePos);	//ここでウィンドウ基準の相対座標に変換

	m_pDInputDev->GetDeviceState(					//マウスの状態を取得
					sizeof(DIMOUSESTATE),
					&m_state);
}

VOID Mouse::CheckInputStateDetatils()
{
	BOOL hasInputtedPrev	= FALSE;
	BOOL hasInputtedCurrent = FALSE;

	ZeroMemory(&m_details, sizeof(BOOL) * DIM::DIM_MAX * INPUT_DETAILS_MAX);
	for (INT i = 0; i < DIM_MAX; ++i)
	{
		hasInputtedPrev		= m_prevState.rgbButtons[i] & 0x80;
		hasInputtedCurrent	= m_state.rgbButtons[i] & 0x80;

		if (!hasInputtedPrev && hasInputtedCurrent)
		{
			m_details[i] = PRESS;
		}

		if (hasInputtedPrev && hasInputtedCurrent)
		{
			m_details[i] = HOLD;
		}

		if (hasInputtedPrev && !hasInputtedCurrent)
		{
			m_details[i] = RELEASE;
		}

		if (!hasInputtedPrev && !hasInputtedCurrent)
		{
			m_details[i] = NEUTRAL;
		}
	}
}
