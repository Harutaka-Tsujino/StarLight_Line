#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IDX3D/IDX3D.h"
#include "Wnd.h"

IDX3D* Wnd::m_pIDX3D = nullptr;

Wnd::Wnd(const HINSTANCE hInst, const TCHAR* pAppName, IDX3D* pIDX3D)
{
	m_pIDX3D = pIDX3D;

	ZeroMemory(&m_msg, sizeof(MSG));

	Create(hInst, pAppName);
}

const HWND& Wnd::GetHWND()
{
	return m_hWnd;
}

const MSG& Wnd::GetMSG()
{
	return m_msg;
}

D3DXVECTOR2 Wnd::GetWndSize()
{
	return m_WND_SIZE;
}

BOOL Wnd::ExistsWinMSG()
{
	if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);

		return FALSE;
	}

	return TRUE;
}

VOID Wnd::Create(const HINSTANCE hInst, const TCHAR* pAppName)
{
	WNDCLASSEX wndclass;
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInst;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= pAppName;
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	m_hWnd = CreateWindow(
				pAppName,pAppName,
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, 
				(INT)m_WND_SIZE.x, (INT)m_WND_SIZE.y, 
				NULL, NULL, 
				hInst,
				NULL);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return;
}

LRESULT CALLBACK Wnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:										//ウィンドウの終了ボタンが押された時
		PostQuitMessage(0);									//プログラムの終了メッセージを投げる

		break;

	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)PostQuitMessage(0);			//プログラムの終了メッセージを投げる

		break;

	case WM_SYSKEYDOWN:										// Alt + 特殊キーの処理に使う
		if (wParam == VK_RETURN)m_pIDX3D->ChangeWndMode();	//デバイスロストの危険性あり
	
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
