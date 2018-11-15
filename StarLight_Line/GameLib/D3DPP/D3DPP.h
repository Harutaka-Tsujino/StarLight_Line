#ifndef D3DPP_H
#define D3DPP_H

#include <windows.h>
#include <d3dx9.h>

#include "../Interface/ID3DPP/ID3DPP.h"
#include "../Interface/IWnd/IWnd.h"

class D3DPP :public ID3DPP
{
public:
	D3DPP(IWnd* pIWnd) :m_WND_SIZE(pIWnd->GetWndSize()), m_rHWND(pIWnd->GetHWND()) {};	//InitD3DPP(HWND)をよぶ
	~D3DPP() {};

	inline D3DPRESENT_PARAMETERS GetD3DPRESENT_PARAMETERS()								//DX3DDevを作成するときとウィンドウモードを切り替えるときに用いる
	{
		D3DPRESENT_PARAMETERS D3DPP;
		InitD3DPP(&D3DPP);

		return D3DPP;
	}

	D3DPRESENT_PARAMETERS ToggleD3DPPWndMode();											//切り替えた後にD3DPPを再度入手する必要はない

private:
	VOID InitD3DPP(D3DPRESENT_PARAMETERS* pD3DPP);

	const SurfaceVal m_WND_SIZE;

	const HWND& m_rHWND;

	BOOL m_isWindow = TRUE;
};

#endif // !D3DPP_H
