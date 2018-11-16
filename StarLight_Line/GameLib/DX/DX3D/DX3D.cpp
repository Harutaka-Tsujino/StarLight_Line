#include "DX3D.h"

#include <windows.h>
#include <tchar.h>

#include <d3dx9.h>

VOID DX3D::ToggleWndMode()
{
	D3DPRESENT_PARAMETERS D3DPP = m_D3DPP->ToggleD3DPPWndMode();

	HRESULT hr = m_pDX3DDev->Reset(&D3DPP);	//スワップチェーンのタイプ、サイズ、およびフォーマットをリセット
	if (FAILED(hr))
	{
		OnFailedChangeWndMode(hr);

		return;
	}

	LONG overlapWindowStyle	= (D3DPP.Windowed) ? WS_OVERLAPPEDWINDOW : WS_POPUP;
	LONG windowStyle		= overlapWindowStyle | WS_VISIBLE;

	SetWindowLong(
		m_HWND,
		GWL_STYLE,
		windowStyle);

	m_pColorBlender->DefaultColorBlending();

	InitViewPort();
}

VOID DX3D::Create(LPDIRECT3D9 pD3D)
{
	D3DPRESENT_PARAMETERS D3DPP = m_D3DPP->ToggleD3DPPWndMode();

	if (pD3D->CreateDevice(	//描画をハードウェアに依存させる 軽い
				D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
				m_HWND,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
				&D3DPP,
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
				m_HWND,
				D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
				&D3DPP,
				&m_pDX3DDev))
	{
		return;
	}

	MessageBox(0,
		_T("DIRECT3Dデバイスの作成に失敗しました"),
		NULL, 
		MB_OK);

	DestroyWindow(m_HWND);	//WM_DESTROYをWndProcに投げる
}

VOID DX3D::OnFailedChangeWndMode(HRESULT resetRetVal)
{
	if (resetRetVal == D3DERR_DEVICELOST)
	{
		return;				//デバイスがロストとしたときの対処
	}

	DestroyWindow(m_HWND);	//WM_DESTROYをWndProcに投げる
}

inline VOID DX3D::InitViewPort()
{
	D3DPRESENT_PARAMETERS D3DPP = m_D3DPP->GetD3DPRESENT_PARAMETERS();

	D3DVIEWPORT9 viewPort;
	viewPort.Width	= D3DPP.BackBufferWidth;
	viewPort.Height = D3DPP.BackBufferHeight;
	viewPort.MinZ	= 0.0f;
	viewPort.MaxZ	= 1.0f;
	viewPort.X		= 0;
	viewPort.Y		= 0;
	m_pDX3DDev->SetViewport(&viewPort);
}
