#ifndef COLOR_BLENDER_H
#define COLOR_BLENDER_H

#include <windows.h>

#include <d3dx9.h>

class ColorBlender
{
public:
	ColorBlender(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~ColorBlender() {};

	inline VOID DefaultBlendMode() const	//通常合成
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	inline VOID AddtionBlendMode() const	//加算合成
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	VOID DefaultColorBlending() const;		//ウィンドウモードを切り替えた時には再設定する必要がある

private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;
};

#endif // !COLOR_BLENDER_H
