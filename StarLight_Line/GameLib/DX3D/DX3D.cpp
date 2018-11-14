#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>

#include "../Interface/IWnd/IWnd.h"
#include "../Interface/IDX/IDX.h"
#include "../Interface/ID3DPP/ID3DPP.h"
#include "DX3D.h"

DX3D::DX3D(IWnd* pIWnd, IDX* pIDX, ID3DPP* pID3DPP) :m_rHWND(pIWnd->GetHWND())
{
	m_pID3DPP = pID3DPP;
	m_pD3DPP = m_pID3DPP->GetD3DPRESENT_PARAMETERS();

	Create(pIDX->GetLPDIRECT3D9());

	DefaultColorBlending();

	InitViewPort();
}

DX3D::~DX3D()
{
	m_pDX3DDev->Release();
}

const LPDIRECT3DDEVICE9& DX3D::GetLPDIRECT3DDEVICE9()
{
	return m_pDX3DDev;
}

VOID DX3D::PrepareRendering()
{
	m_pDX3DDev->Clear(
				0, 
				NULL, 
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				D3DCOLOR_XRGB(0, 0, 0),	//画面をクリアするときの色
				1.f,
				0);

	m_pDX3DDev->BeginScene();
}

VOID DX3D::CleanUpRendering()
{
	m_pDX3DDev->EndScene();
	m_pDX3DDev->Present(
					NULL,
					NULL,
					NULL,
					NULL);
}

VOID DX3D::ChangeWndMode()
{
	m_pID3DPP->SwitchD3DPPWndMode();

	HRESULT hr = m_pDX3DDev->Reset(m_pD3DPP);	//スワップチェーンのタイプ、サイズ、およびフォーマットをリセット
	if (FAILED(hr))
	{
		OnFailedChangeWndMode(hr);

		return;
	}

	LONG overlapWindowStyle	= (m_pD3DPP->Windowed) ? WS_OVERLAPPEDWINDOW : WS_POPUP;
	LONG windowStyle		= overlapWindowStyle | WS_VISIBLE;

	SetWindowLong(
		m_rHWND,
		GWL_STYLE,
		windowStyle);

	DefaultColorBlending();
	InitViewPort();
}

VOID DX3D::Create(LPDIRECT3D9 pD3D)
{
	if (pD3D->CreateDevice(	//描画をハードウェアに依存させる 軽い
				D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
				m_rHWND,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
				m_pD3DPP,
				&m_pDX3DDev))
	{
		return;
	}

	MessageBox(0, 
		_T("HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します"),
		NULL, 
		MB_OK);

	if (pD3D->CreateDevice(	//描画をソフトウェアに依存させる 重い
				D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
				m_rHWND,
				D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
				m_pD3DPP, 
				&m_pDX3DDev))
	{
		return;
	}

	MessageBox(0,
		_T("DIRECT3Dデバイスの作成に失敗しました"),
		NULL, 
		MB_OK);

	DestroyWindow(m_rHWND);	//WM_DESTROYをWndProcに投げる
}

VOID DX3D::OnFailedChangeWndMode(HRESULT resetRetVal)
{
	if (resetRetVal == D3DERR_DEVICELOST)
	{
		return;								//デバイスがロストとしたときの対処
	}

	DestroyWindow(m_rHWND);					//WM_DESTROYをWndProcに投げる
}

VOID DX3D::InitViewPort()
{
	D3DVIEWPORT9 viewPort;
	viewPort.Width	= m_pD3DPP->BackBufferWidth;
	viewPort.Height = m_pD3DPP->BackBufferHeight;
	viewPort.MinZ	= 0.0f;
	viewPort.MaxZ	= 1.0f;
	viewPort.X		= 0;
	viewPort.Y		= 0;
	m_pDX3DDev->SetViewport(&viewPort);
}

VOID DX3D::DefaultColorBlending()
{
	m_pDX3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pDX3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDX3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDX3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDX3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	m_pDX3DDev->SetRenderState(D3DRS_ALPHAREF, 0x00);

	m_pDX3DDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDX3DDev->SetRenderState(D3DRS_AMBIENT, 0x66666666);
	m_pDX3DDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	m_pDX3DDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	m_pDX3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pDX3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDX3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	
	m_pDX3DDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDX3DDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
}
