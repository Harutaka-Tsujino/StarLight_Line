#ifndef INPUT_DEV_H
#define INPUT_DEV_H

#include <windows.h>
#include <dinput.h>

#include "../Interface/IWnd/IWnd.h"
#include "../Interface/IDXInput/IDXInput.h"

class InputDev
{
public:
	InputDev(IWnd* pIWnd,IDXInput* pIDXInput);	//Createを呼ぶ
	~InputDev();

	virtual VOID UpdataInputState() = 0;		//メインループの始まりで用いる
	virtual VOID StorePrevInputState() = 0;		//メインループの終わりで用いる

	virtual BOOL IsPressed(INT key) = 0;
	virtual BOOL IsHeld(INT key) = 0;
	virtual BOOL IsReleased(INT key) = 0;
	virtual BOOL IsNeutral(INT key) = 0;

 protected:
	 enum InputDetatail
	 {
		 PRESS,									//押された瞬間のフレームだけTRUE
		 HOLD,									//押され続けられている間TRUE
		 RELEASE,								//離された瞬間のフレームだけTRUE
		 NEUTRAL,								//前回と現在のフレームで押されていない間TRUE
		 INPUT_DETAILS_MAX
	};

	virtual VOID Create(LPDIRECTINPUT8 pDXInput) = 0;

	virtual VOID AcquireInputState() = 0;
	virtual VOID CheckInputStateDetatils() = 0;

	LPDIRECTINPUTDEVICE8 m_pDInputDev = nullptr;

	const HWND& m_rHWND;
};

#endif // !INPUT_DEV_H
