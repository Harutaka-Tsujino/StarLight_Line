#ifndef WND_H
#define WND_H

#include <windows.h>

struct SurfaceVal
{
public:
	int m_x = 0;
	int m_y = 0;
};

class Wnd
{
public:
	Wnd(const HINSTANCE hInst, const TCHAR* pAppName);                                      //WinMainからHINSTANCEを取得 Crate()を呼ぶ
	~Wnd() {};

	inline const HWND& GetHWND() const
	{
		return m_hWnd;
	}

	inline const MSG& GetMSG() const
	{
		return m_msg;
	}

	inline SurfaceVal GetWndSize() const
	{
		return m_WND_SIZE;
	}

	inline BOOL IsPostedQuitMessage() const
	{
		if (m_msg.message == WM_QUIT) return TRUE;

		return FALSE;
	}

	BOOL ExistsWinMSG();

private:
	VOID Create(const HINSTANCE hInst, const TCHAR* pAppName);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);    //ウィンドウを生成するときにProcの関数ポインタが必要なのでstatic
																							//IDX3D経由でDX3DのメソッドToggleWndMode()を呼ぶ
	HWND m_hWnd = nullptr;

	MSG m_msg;

	const SurfaceVal m_WND_SIZE = { 1280, 720 };
};

#endif // !WND_H
