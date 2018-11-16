#ifndef DX_H
#define DX_H

#include <windows.h>

#include <d3dx9.h>

#include "../Wnd/Wnd.h"
#include "DX3D\DX3D.h"
#include "DXInput\DXInput.h"

class DX
{
public:
	DX(HWND hWnd, SurfaceVal wndSize) :m_HWND(hWnd)
	{
		Create();

		m_pDX3D = new DX3D(m_HWND, wndSize, m_pD3D);

		m_pDXInput = new DXInput(m_HWND);
	}

	~DX()
	{
		delete m_pDX3D;

		delete m_pDXInput;

		m_pD3D->Release();
	}

	inline VOID UpdataInputState()						//メインループの始まりで用いる
	{
		m_pDXInput->UpdataInputState();
	}

	inline VOID StorePrevInputState()					//メインループの終わりで用いる
	{
		m_pDXInput->StorePrevInputState();
	}

	inline BOOL MouseIsPressed(INT key) const
	{
		return m_pDXInput->MouseIsPressed(key);
	}

	inline BOOL MouseIsHeld(INT key) const
	{
		return m_pDXInput->MouseIsHeld(key);
	}

	inline BOOL MouseIsReleased(INT key) const
	{
		return m_pDXInput->MouseIsReleased(key);
	}

	inline BOOL MouseIsNeutral(INT key) const
	{
		return m_pDXInput->MouseIsNeutral(key);
	}

	inline BOOL KeyboardIsPressed(INT key) const
	{
		return m_pDXInput->KeyboardIsPressed(key);
	}

	inline BOOL KeyboardIsHeld(INT key) const
	{
		return m_pDXInput->KeyboardIsHeld(key);
	}

	inline BOOL KeyboardIsReleased(INT key) const
	{
		return m_pDXInput->KeyboardIsReleased(key);
	}

	inline BOOL KeyboardIsNeutral(INT key) const
	{
		return m_pDXInput->KeyboardIsNeutral(key);
	}

private:
	VOID Create();	//他DX機能の基盤となるので初めに生成する

	const HWND m_HWND = nullptr;

	LPDIRECT3D9 m_pD3D = nullptr;

	DX3D* m_pDX3D = nullptr;

	DXInput* m_pDXInput = nullptr;
};

#endif // !DX_H
