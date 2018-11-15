#ifndef DX_INPUT_H
#define DX_INPUT_H

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>

#include "../Interface/IDXInput/IDXInput.h"
#include "../Interface/IWnd/IWnd.h"

class DXInput :public IDXInput
{
public:
	DXInput(IWnd* pIWnd);				//Create()を呼ぶ
	~DXInput();

	inline const LPDIRECTINPUT8& GetLPDIRECTINPUT8() const
	{
		return m_pDXInput;
	}

private:
	VOID Create();

	LPDIRECTINPUT8 m_pDXInput = nullptr;

	const HWND& m_rHWND;
};

#endif // !DX_INPUT_H
