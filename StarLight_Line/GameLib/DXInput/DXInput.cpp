#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>

#include "../Interface/IWnd/IWnd.h"
#include "DXInput.h"

DXInput::DXInput(IWnd* pIWnd) :m_rHWND(pIWnd->GetHWND())
{
	Create();
}

DXInput::~DXInput()
{
	m_pDXInput->Release();
}

VOID DXInput::Create()
{
	DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8,
		(VOID**)&m_pDXInput,
		NULL);
}
