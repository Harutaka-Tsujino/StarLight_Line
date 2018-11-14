#ifndef WND_H
#define WND_H

#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IDX3D/IDX3D.h"

class Wnd
{
public:
	Wnd(const HINSTANCE hInst, const TCHAR* pAppName, IDX3D* pIDX3D);						//WinMainからHINSTANCEを取得 Crate()を呼ぶ
	~Wnd() {};

	const HWND& GetHWND();
	const MSG& GetMSG();
	D3DXVECTOR2 GetWndSize();

	BOOL ExistsWinMSG();

private:
	VOID Create(const HINSTANCE hInst, const TCHAR* pAppName);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);	//ウィンドウを生成するときにProcの関数ポインタが必要なのでstatic
																							//IDX3D経由でDX3DのメソッドChangeWndMode()を呼ぶ
	HWND m_hWnd = nullptr;

	MSG m_msg;

	static IDX3D* m_pIDX3D;																	//WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)で用いるのでstatic

	const D3DXVECTOR2 m_WND_SIZE = { 1280.0f, 720.0f };
};

#endif // !WND_H
