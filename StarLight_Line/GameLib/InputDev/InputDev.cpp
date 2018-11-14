#include <windows.h>
#include <dinput.h>

#include "../Interface/IDXInput/IDXInput.h"
#include "InputDev.h"

InputDev::InputDev(IWnd* pIWnd, IDXInput* pIDXInput) :m_rHWND(pIWnd->GetHWND())
{
	Create(pIDXInput->GetLPDIRECTINPUT8());
}

InputDev::~InputDev()
{
	m_pDInputDev->Release();
}
