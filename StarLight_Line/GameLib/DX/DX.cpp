#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>

#include"DX.h"

DX::DX()
{
	Create();
}

DX::~DX()
{
	m_pD3D->Release();
}

const LPDIRECT3D9& DX::GetLPDIRECT3D9()
{
	return m_pD3D;
}

VOID DX::Create()
{
	if (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))
	{
		return;
	}

	MessageBox(
		0, 
		_T("Direct3Dの作成に失敗しました"),
		NULL,
		MB_OK);
}
