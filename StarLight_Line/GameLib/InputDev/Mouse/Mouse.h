#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <dinput.h>

#include "../../Interface/IWnd/IWnd.h"
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
	Mouse(IWnd* pIWnd, IDXInput* pIDXInput) : InputDev(pIWnd, pIDXInput) {};
	~Mouse() {};

	VOID UpdataInputState();					//メインループの始まりで用いる

	inline VOID StorePrevInputState()			//メインループの終わりで用いる
	{
		memcpy(&m_prevState, &m_state, sizeof(DIMOUSESTATE));
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
	VOID Create(LPDIRECTINPUT8 pDXInput);		//基底クラスのコンストラクタでCreate(LPDIRECTINPUT8 pDXInput)を呼ぶ

	inline VOID AcquireInputState();
	VOID CheckInputStateDetatils();				//AcquireInputState()を読んだ後に用いる

	DIMOUSESTATE m_state;
	DIMOUSESTATE m_prevState;

	POINT m_cursorRelativePos;					//カーソルのウィンドウ基準の相対座標

	InputDetatail m_details[DIM_MAX];
};

#endif // !MOUSE_H
