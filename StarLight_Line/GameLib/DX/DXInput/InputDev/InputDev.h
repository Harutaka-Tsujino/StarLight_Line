#ifndef INPUT_DEV_H
#define INPUT_DEV_H

#include <windows.h>

#include <dinput.h>

class InputDev
{
public:
	InputDev(HWND hWnd) :m_HWND(hWnd) {};

	~InputDev()
	{
		m_pDInputDev->Release();
	}

	virtual VOID UpdataInputState() = 0;			//メインループの始まりで用いる
	virtual VOID StorePrevInputState() = 0;			//メインループの終わりで用いる

	virtual BOOL IsPressed(INT key) const = 0;
	virtual BOOL IsHeld(INT key) const = 0;
	virtual BOOL IsReleased(INT key) const = 0;
	virtual BOOL IsNeutral(INT key) const = 0;

protected:
	enum INPUT_DETAIL
	{
		I_D_PRESS,										//押された瞬間のフレームだけTRUE
		I_D_HOLD,										//押され続けられている間TRUE
		I_D_RELEASE,									//離された瞬間のフレームだけTRUE
		I_D_NEUTRAL,									//前回と現在のフレームで押されていない間TRUE
		I_D_MAX
	};

	virtual VOID AcquireInputState() = 0;
	virtual VOID CheckInputStateDetatils() = 0;

	inline BOOL IsInputted(const BYTE& rKey) const
	{
		return (rKey & 0x80);
	}

	const HWND m_HWND = nullptr;

	LPDIRECTINPUTDEVICE8 m_pDInputDev = nullptr;
};

#endif // !INPUT_DEV_H
