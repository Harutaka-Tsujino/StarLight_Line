#ifndef I_WND_H
#define I_WND_H

#include <windows.h>

struct SurfaceVal
{
public:
	INT m_x = 0;
	INT m_y = 0;
};

class IWnd
{
public:
	virtual inline const HWND& GetHWND() const = 0;
	virtual inline SurfaceVal GetWndSize() const = 0;
};

#endif // !I_WND_H
