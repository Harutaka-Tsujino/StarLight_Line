/**
* @brief 描画を行うクラスのヘッダ
* @author Harutaka Tsujino
*/
#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>

#include <d3dx9.h>

#include "../../../../Struct/CustomVertex/CustomVertex.h"

/**
* @class Renderer
* @brief 描画を行う
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
	* @detail　rMatWorldをSetTransform,pTextureをセットした後 FbxRelatedのメソッドを用い描画する
	*/
	//inline VOID Render(const FbxRelated& rFBXModel
	//, const D3DXMATRIX& pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const;

	/**
	* @brief 2Dの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	* @detail pTextureをセットした後、DrawPrimitiveUpを用い描画する
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

public:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;
};

#endif // !RENDERER_H
