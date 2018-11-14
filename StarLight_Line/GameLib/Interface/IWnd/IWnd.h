#ifndef I_WND_H
#define I_WND_H

#include <windows.h>
#include <d3dx9.h>

class IWnd
{
public:
	virtual const HWND& GetHWND() = 0;
	virtual D3DXVECTOR2 GetWndSize() = 0;
};

#endif // !I_WND_H
