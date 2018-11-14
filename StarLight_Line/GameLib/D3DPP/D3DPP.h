#ifndef D3DPP_H
#define D3DPP_H

#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IWnd/IWnd.h"

class D3DPP
{
public:
	D3DPP(IWnd* pIWnd);											//InitD3DPP(HWND)をよぶ
	~D3DPP() {};

	D3DPRESENT_PARAMETERS* GetD3DPRESENT_PARAMETERS();			//DX3DDevを作成するときとウィンドウモードを切り替えるときに用いる 3DDevのResetメソッドで非constのポインタを渡す必要がある

	VOID SwitchD3DPPWndMode();									//切り替えた後にD3DPPを再度入手する必要はない

private:
	VOID InitD3DPP(IWnd* pIWnd);

	D3DPRESENT_PARAMETERS m_usingD3DPP;							//m_usingD3DPPを作ることで切替時にウィンドウモードを考慮しなくてもよい
	D3DPRESENT_PARAMETERS m_windowD3DPP;
	D3DPRESENT_PARAMETERS m_fullScreenD3DPP;
};

#endif // !D3DPP_H
