/**
* @file Renderer.h
* @brief 描画クラスのヘッダ
* @author Harutaka Tsujino
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>

#include <d3dx9.h>

#include "../CustomVertexEditor/Data/CustomVertex.h"
#include "../FbxStorage/FbxRelated/FbxRelated.h"
#include "../FbxStorage/FbxRelated/FbxModel/FbxModel.h"
#include "../../../3DBoard/3DBoard.h"

/**
* @brief FBX(予定)とCustomVertexの描画クラス
*/
class Renderer
{
public:
	Renderer(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~Renderer() {};

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline VOID Render(const FbxRelated& rFBXModel,
		const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_rpDX3D_DEV->SetTransform(D3DTS_WORLD, &rWorld);

		m_rpDX3D_DEV->SetTexture(0, pTexture);

		for (FbxModel* pI : rFBXModel.m_pModel)
		{
			pI->DrawFbx();
		}
	}

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	inline VOID Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_rpDX3D_DEV->SetFVF(
						D3DFVF_XYZRHW |
						D3DFVF_DIFFUSE |
						D3DFVF_TEX1);

		m_rpDX3D_DEV->SetTexture(0, pTexture);

		m_rpDX3D_DEV->DrawPrimitiveUP(
						D3DPT_TRIANGLEFAN,
						2,
						pCustomVertices, sizeof(CustomVertex));
	}

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline VOID Render(const Vertex3D* pVertex,
		const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr)
	{
		/*m_rpDX3D_DEV->SetFVF(
			D3DFVF_XYZ |
			D3DFVF_DIFFUSE |
			D3DFVF_TEX1);*/

		LPDIRECT3DVERTEXBUFFER9 pBuffer = nullptr;

		m_rpDX3D_DEV->SetTransform(D3DTS_WORLD, &rWorld);

		m_rpDX3D_DEV->CreateVertexBuffer(
			4 * sizeof(Vertex3D),
			D3DUSAGE_WRITEONLY,
			D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
			D3DPOOL_MANAGED,
			&pBuffer,
			NULL);

		m_rpDX3D_DEV->SetStreamSource(0, pBuffer, 0, sizeof(Vertex3D));

		m_rpDX3D_DEV->SetTexture(0, pTexture);

		m_rpDX3D_DEV->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

		pBuffer->Release();
	}

	inline VOID Render(const D3DXVECTOR2& topLeft, const TCHAR* pText, UINT format, LPD3DXFONT pFont, DWORD color)
	{
		RECT rect;
		SetRectEmpty(&rect);

		pFont->DrawText(NULL, pText, -1, &rect, format | DT_CALCRECT, color);

		OffsetRect(&rect, static_cast<INT>(topLeft.x), static_cast<INT>(topLeft.y));

		pFont->DrawText(NULL, pText, -1, &rect, format, color);
	}

private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;
};

#endif //! RENDERER_H
