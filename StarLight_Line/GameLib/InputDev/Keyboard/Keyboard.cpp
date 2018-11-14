#include <windows.h>
#include <dinput.h>

#include "../../Interface/IDXInput/IDXInput.h"
#include "../InputDev.h"
#include "Keyboard.h"

Keyboard::Keyboard(IWnd* pIWnd, IDXInput* pIDXInput) :InputDev(pIWnd, pIDXInput)
{
}

VOID Keyboard::UpdataInputState()
{
	AcquireInputState();
	CheckInputStateDetatils();
}

VOID Keyboard::StorePrevInputState()
{
	memcpy(m_prevDiks, m_diks, sizeof(BYTE) * 256);
}

BOOL Keyboard::IsPressed(INT key)
{
	return(m_details[key] == PRESS);
}

BOOL Keyboard::IsHeld(INT key)
{
	return(m_details[key] == HOLD);
}

BOOL Keyboard::IsReleased(INT key)
{
	return(m_details[key] == RELEASE);
}

BOOL Keyboard::IsNeutral(INT key)
{
	return(m_details[key] == NEUTRAL);
}

VOID Keyboard::Create(LPDIRECTINPUT8 pDXInput)
{
	pDXInput->CreateDevice(
				GUID_SysKeyboard, &m_pDInputDev,
				NULL);

	m_pDInputDev->SetDataFormat(&c_dfDIKeyboard);

	m_pDInputDev->SetCooperativeLevel(
					m_rHWND,
					DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}

VOID Keyboard::AcquireInputState()
{
	m_pDInputDev->Acquire();		//キーボードの状態を取得する権限の取得

	m_pDInputDev->GetDeviceState(	//キーボードの状態を取得
					sizeof(BYTE) * 256,
					m_diks);
}

VOID Keyboard::CheckInputStateDetatils()
{
	BOOL hasInputtedPrev	= FALSE;
	BOOL hasInputtedCurrent = FALSE;

	const INT KEYBOARD_KEYS_MAX = 256;
	ZeroMemory(m_details, sizeof(BOOL) * KEYBOARD_KEYS_MAX * INPUT_DETAILS_MAX);
	for (INT i = 0; i < KEYBOARD_KEYS_MAX; ++i)
	{
		hasInputtedPrev		= m_prevDiks[i] & 0x80;
		hasInputtedCurrent	= m_diks[i] & 0x80;

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
