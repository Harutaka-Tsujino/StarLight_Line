#ifndef D3DPP_H
#define D3DPP_H

#include <windows.h>

#include <d3dx9.h>

#include "../../../../Struct/SurfaceVal/SurfaceVal.h"

class D3DPP
{
public:
	D3DPP(HWND hWnd, SurfaceVal wndSize) :m_WND_SIZE(wndSize), m_HWND(hWnd) {};	//InitD3DPP(HWND)をよぶ
	~D3DPP() {};

	inline D3DPRESENT_PARAMETERS GetD3DPRESENT_PARAMETERS()						//DX3DDevを作成するときとウィンドウモードを切り替えるときに用いる
	{
		D3DPRESENT_PARAMETERS D3DPP;
		InitD3DPP(&D3DPP);

		return D3DPP;
	}

	inline D3DPRESENT_PARAMETERS ToggleD3DPPWndMode()							//切り替えた後にD3DPPを再度入手する必要はない
	{
		m_isWindow = !m_isWindow;

		D3DPRESENT_PARAMETERS D3DPP;
		InitD3DPP(&D3DPP);

		return D3DPP;
	}

private:
	VOID InitD3DPP(D3DPRESENT_PARAMETERS* pD3DPP);

	const HWND m_HWND = nullptr;

	const SurfaceVal m_WND_SIZE;

	BOOL m_isWindow = TRUE;
};

#endif // !D3DPP_H
