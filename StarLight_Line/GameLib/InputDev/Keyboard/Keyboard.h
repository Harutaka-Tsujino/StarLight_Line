#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <windows.h>
#include <dinput.h>

#include "../../Interface/IDXInput/IDXInput.h"
#include "../InputDev.h"

class Keyboard :public InputDev
{
public:
	Keyboard(IWnd* pIWnd, IDXInput* pIDXInput);
	~Keyboard() {};

	VOID UpdataInputState();
	VOID StorePrevInputState();

	BOOL IsPressed(INT key);
	BOOL IsHeld(INT key);
	BOOL IsReleased(INT key);
	BOOL IsNeutral(INT key);

private:
	VOID Create(LPDIRECTINPUT8 pDXInput);

	VOID AcquireInputState();
	VOID CheckInputStateDetatils();

	BYTE m_diks[256];		//現在ののフレームでキーが押されていた場合上位ビットが立つ
	BYTE m_prevDiks[256];	//前回のフレームでキーが押されていた場合上位ビットが立つ

	InputDetatail m_details[256];
};

#endif // !KEYBOARD_H

