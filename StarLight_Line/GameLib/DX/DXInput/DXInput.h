#ifndef DX_INPUT_H
#define DX_INPUT_H

#include <windows.h>

#include <d3dx9.h>
#include <dinput.h>

#include "InputDev\InputDev.h"
#include "InputDev\Mouse\Mouse.h"
#include "InputDev\Keyboard\Keyboard.h"

class DXInput
{
public:
	DXInput(HWND hWnd) :m_HWND(hWnd)
	{
		Create();

		m_pMouse	= new Mouse(m_HWND,m_pDXInput);
		m_pKeyboard	= new Keyboard(m_HWND, m_pDXInput);
	}

	~DXInput()
	{
		delete m_pMouse;
		delete m_pKeyboard;

		m_pDXInput->Release();
	}

	inline VOID UpdataInputState()						//メインループの始まりで用いる
	{
		m_pMouse->UpdataInputState();
		m_pKeyboard->UpdataInputState();
	}

	inline VOID StorePrevInputState()					//メインループの終わりで用いる
	{
		m_pMouse->StorePrevInputState();
		m_pKeyboard->StorePrevInputState();
	}

	inline BOOL MouseIsPressed(INT key) const
	{
		return m_pMouse->IsPressed(key);
	}

	inline BOOL MouseIsHeld(INT key) const
	{
		return m_pMouse->IsHeld(key);
	}

	inline BOOL MouseIsReleased(INT key) const
	{
		return m_pMouse->IsReleased(key);
	}

	inline BOOL MouseIsNeutral(INT key) const
	{
		return m_pMouse->IsNeutral(key);
	}

	inline BOOL KeyboardIsPressed(INT key) const
	{
		return m_pKeyboard->IsPressed(key);
	}

	inline BOOL KeyboardIsHeld(INT key) const
	{
		return m_pKeyboard->IsHeld(key);
	}

	inline BOOL KeyboardIsReleased(INT key) const
	{
		return m_pKeyboard->IsReleased(key);
	}

	inline BOOL KeyboardIsNeutral(INT key) const
	{
		return m_pKeyboard->IsNeutral(key);
	}

private:
	VOID Create() 
	{
		DirectInput8Create(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION, IID_IDirectInput8,
			(VOID**)&m_pDXInput,
			NULL);
	}

	const HWND m_HWND = nullptr;

	LPDIRECTINPUT8 m_pDXInput = nullptr;

	InputDev* m_pMouse		= nullptr;
	InputDev* m_pKeyboard	= nullptr;
};

#endif // !DX_INPUT_H
