#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IWnd/IWnd.h"
#include "D3DPP.h"

D3DPP::D3DPP(IWnd* pIWnd)
{
	InitD3DPP(pIWnd);
}

D3DPRESENT_PARAMETERS* D3DPP::GetD3DPRESENT_PARAMETERS()
{
	return &m_usingD3DPP;
}

VOID D3DPP::SwitchD3DPPWndMode()
{
	m_usingD3DPP = (m_usingD3DPP.Windowed) ? m_fullScreenD3DPP : m_windowD3DPP;
}

VOID D3DPP::InitD3DPP(IWnd* pIWnd)
{
	ZeroMemory(&m_windowD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	ZeroMemory(&m_fullScreenD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	
	m_fullScreenD3DPP.BackBufferFormat			= m_windowD3DPP.BackBufferFormat		= D3DFMT_X8R8G8B8;
	m_fullScreenD3DPP.BackBufferCount			= m_windowD3DPP.BackBufferCount			= 1;
	m_fullScreenD3DPP.SwapEffect				= m_windowD3DPP.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_fullScreenD3DPP.EnableAutoDepthStencil	= m_windowD3DPP.EnableAutoDepthStencil	= TRUE;
	m_fullScreenD3DPP.AutoDepthStencilFormat	= m_windowD3DPP.AutoDepthStencilFormat	= D3DFMT_D16;

	const D3DXVECTOR2 WND_SIZE = pIWnd->GetWndSize();
	m_fullScreenD3DPP.BackBufferWidth		= (INT)WND_SIZE.x;
	m_fullScreenD3DPP.BackBufferHeight		= (INT)WND_SIZE.y;
	m_fullScreenD3DPP.hDeviceWindow			= pIWnd->GetHWND();
	m_fullScreenD3DPP.PresentationInterval	= D3DPRESENT_INTERVAL_DEFAULT;
	m_fullScreenD3DPP.Windowed				= FALSE;

	m_windowD3DPP.Windowed = TRUE;

	m_usingD3DPP = m_windowD3DPP;
}
