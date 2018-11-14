#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <dinput.h>

#include "../../Interface/IDXInput/IDXInput.h"
#include "../InputDev.h"

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
	Mouse(IWnd* pIWnd, IDXInput* pIDXInput);
	~Mouse() {};

	VOID UpdataInputState();					//メインループの始まりで用いる
	VOID StorePrevInputState();					//メインループの終わりで用いる

	BOOL IsPressed(INT key);
	BOOL IsHeld(INT key);
	BOOL IsReleased(INT key);
	BOOL IsNeutral(INT key);

private:
	VOID Create(LPDIRECTINPUT8 pDXInput);		//基底クラスのコンストラクタでCreate(LPDIRECTINPUT8 pDXInput)を呼ぶ

	VOID AcquireInputState();
	VOID CheckInputStateDetatils();				//AcquireInputState()を読んだ後に用いる

	DIMOUSESTATE m_state;
	DIMOUSESTATE m_prevState;

	POINT m_cursorRelativePos;					//カーソルのウィンドウ基準の相対座標

	InputDetatail m_details[DIM_MAX];
};

#endif // !MOUSE_H
