#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <windows.h>
#include <dinput.h>

#include "../../Interface/IDXInput/IDXInput.h"
#include "../../Interface/IWnd/IWnd.h"
#include "../InputDev.h"

class Keyboard :public InputDev
{
public:
	Keyboard(IWnd* pIWnd, IDXInput* pIDXInput) :InputDev(pIWnd, pIDXInput) {};
	~Keyboard() {};

	VOID UpdataInputState()				//メインループの始まりで用いる
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
		return(m_details[key] == PRESS);
	}

	inline BOOL IsHeld(INT key) const
	{
		return(m_details[key] == HOLD);
	}

	inline BOOL IsReleased(INT key) const
	{
		return(m_details[key] == RELEASE);
	}

	inline BOOL IsNeutral(INT key) const
	{
		return(m_details[key] == NEUTRAL);
	}

private:
	VOID Create(LPDIRECTINPUT8 pDXInput);

	inline VOID AcquireInputState();
	VOID CheckInputStateDetatils();

	BYTE m_diks[256];					//現在ののフレームでキーが押されていた場合上位ビットが立つ
	BYTE m_prevDiks[256];				//前回のフレームでキーが押されていた場合上位ビットが立つ

	InputDetatail m_details[256];
};

#endif // !KEYBOARD_H

