#ifndef DX3D_H
#define DX3D_H

#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IDX3D/IDX3D.h"
#include "../Interface/IWnd/IWnd.h"
#include "../Interface/IDX/IDX.h"
#include "../Interface/ID3DPP/ID3DPP.h"

class DX3D :public IDX3D
{
public:
	DX3D(IWnd* pIWnd, IDX* pIDX, ID3DPP* pID3DPP);		//Create(LPDIRECT3D9) InitViewPort()を呼ぶ
	~DX3D();

	inline const LPDIRECT3DDEVICE9& GetLPDIRECT3DDEVICE9() const
	{
		return m_pDX3DDev;
	}

	inline VOID PrepareRendering();						//メインループの始まりで用いる
	inline VOID CleanUpRendering();						//メインループの終わりで用いる
	
	VOID ToggleWndMode();								//使用時DX3DDevがロストする可能性がある

private:
	VOID Create(LPDIRECT3D9 pD3D);						//先にDXクラスを生成しなければいけない

	VOID OnFailedChangeWndMode(HRESULT resetRetVal);	//先に引数をFAILEDマクロで調べた後呼ぶ 呼んだあとはreturnする

	inline VOID InitViewPort();							//描画する距離の初期化を行う

	VOID DefaultColorBlending();						//ウィンドウモードを切り替えた時には再設定する必要がある

	LPDIRECT3DDEVICE9 m_pDX3DDev = nullptr;

	ID3DPP* m_pID3DPP = nullptr;

	const HWND& m_rHWND;
};

#endif // !DX3D_H
