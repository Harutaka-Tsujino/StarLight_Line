#ifndef DX3D_H
#define DX3D_H

#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IWnd/IWnd.h"
#include "../Interface/IDX/IDX.h"
#include "../Interface/ID3DPP/ID3DPP.h"

class DX3D
{
public:
	DX3D(IWnd* pIWnd, IDX* pIDX, ID3DPP* pID3DPP);		//Create(LPDIRECT3D9) InitViewPort()を呼ぶ
	~DX3D();

	const LPDIRECT3DDEVICE9& GetLPDIRECT3DDEVICE9();	

	VOID PrepareRendering();							//メインループの始まりで用いる
	VOID CleanUpRendering();							//メインループの終わりで用いる

	VOID ChangeWndMode();								//使用時DX3DDevがロストする可能性がある

private:
	VOID Create(LPDIRECT3D9 pD3D);						//先にDXクラスを生成しなければいけない

	VOID OnFailedChangeWndMode(HRESULT resetRetVal);	//先に引数をFAILEDマクロで調べた後呼ぶ 呼んだあとはreturnする

	VOID InitViewPort();								//描画する距離の初期化を行う

	VOID DefaultColorBlending();						//ウィンドウモードを切り替えた時には再設定する必要がある

	LPDIRECT3DDEVICE9 m_pDX3DDev = nullptr;

	ID3DPP* m_pID3DPP = nullptr;

	const HWND& m_rHWND;

	D3DPRESENT_PARAMETERS* m_pD3DPP;					//毎回取得しなくてもいいように保存　メンバイニシャライザで初期化
};

#endif // !DX3D_H
