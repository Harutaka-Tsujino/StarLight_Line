#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IWnd/IWnd.h"
#include "D3DPP.h"

D3DPRESENT_PARAMETERS D3DPP::ToggleD3DPPWndMode()
{
	m_isWindow = !m_isWindow;

	D3DPRESENT_PARAMETERS D3DPP;
	InitD3DPP(&D3DPP);

	return D3DPP;
}

VOID D3DPP::InitD3DPP(D3DPRESENT_PARAMETERS* pD3DPP)
{
	ZeroMemory(pD3DPP, sizeof(D3DPRESENT_PARAMETERS));

	pD3DPP->Windowed				= m_isWindow;
	pD3DPP->BackBufferFormat		= D3DFMT_X8R8G8B8;
	pD3DPP->BackBufferCount			= 1;
	pD3DPP->SwapEffect				= D3DSWAPEFFECT_DISCARD;
	pD3DPP->EnableAutoDepthStencil	= TRUE;
	pD3DPP->AutoDepthStencilFormat	= D3DFMT_D16;

	if (m_isWindow) return;

	pD3DPP->BackBufferWidth			= m_WND_SIZE.m_x;
	pD3DPP->BackBufferHeight		= m_WND_SIZE.m_y;
	pD3DPP->hDeviceWindow			= m_rHWND;
	pD3DPP->PresentationInterval	= D3DPRESENT_INTERVAL_DEFAULT;
}
