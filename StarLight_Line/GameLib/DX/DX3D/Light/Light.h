#ifndef LIGHT_H
#define LIGHT_H

#include <windows.h>

#include <d3dx9.h>

class Light
{
public:
	Light(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~Light() {};

	inline VOID SetLight(const D3DLIGHT9& rLight, DWORD index) const
	{
		m_rpDX3D_DEV->SetLight(index, &rLight);
		m_rpDX3D_DEV->LightEnable(index, TRUE);
	}

	inline VOID OnLight(DWORD index) const
	{
		m_rpDX3D_DEV->LightEnable(index, TRUE);
	}

	inline VOID OffLight(DWORD index) const
	{
		m_rpDX3D_DEV->LightEnable(index, FALSE);
	}

	inline VOID EnableLighting() const
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	inline VOID DisableLighting() const
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	inline VOID ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_AMBIENT, aRGB);
	}

	inline VOID EnableSpecular() const
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	}

	inline VOID DisaableSpecular() const
	{
		m_rpDX3D_DEV->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	}

	VOID DefaultLighting() const	//ウィンドウモードを切り替えた時には再設定する必要がある
	{
		EnableLighting();
		EnableSpecular();
	}

private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;
};

#endif // !LIGHT_H
