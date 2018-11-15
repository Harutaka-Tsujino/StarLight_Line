#ifndef INPUT_DEV_H
#define INPUT_DEV_H

#include <windows.h>
#include <dinput.h>

#include "../Interface/IWnd/IWnd.h"
#include "../Interface/IDXInput/IDXInput.h"

class InputDev
{
public:
	InputDev(IWnd* pIWnd, IDXInput* pIDXInput);		//Createを呼ぶ
	~InputDev();

	virtual VOID UpdataInputState() = 0;			//メインループの始まりで用いる
	virtual inline VOID StorePrevInputState() = 0;	//メインループの終わりで用いる

	virtual inline BOOL IsPressed(INT key) const = 0;
	virtual inline BOOL IsHeld(INT key) const = 0;
	virtual inline BOOL IsReleased(INT key) const = 0;
	virtual inline BOOL IsNeutral(INT key) const = 0;

protected:
	enum InputDetatail
	{
		PRESS,										//押された瞬間のフレームだけTRUE
		HOLD,										//押され続けられている間TRUE
		RELEASE,									//離された瞬間のフレームだけTRUE
		NEUTRAL,									//前回と現在のフレームで押されていない間TRUE
		INPUT_DETAILS_MAX
	};

	virtual VOID Create(LPDIRECTINPUT8 pDXInput) = 0;

	virtual inline VOID AcquireInputState() = 0;
	virtual VOID CheckInputStateDetatils() = 0;

	LPDIRECTINPUTDEVICE8 m_pDInputDev = nullptr;

	const HWND& m_rHWND;
};

#endif // !INPUT_DEV_H
