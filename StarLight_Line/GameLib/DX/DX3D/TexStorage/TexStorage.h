#ifndef TEX_STORAGE_H
#define TEX_STORAGE_H

#include <windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

class TexStorage
{
public:
	TexStorage(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};
	~TexStorage()
	{ 
		m_pTexMap.clear();
	};

	inline VOID CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		D3DXCreateTextureFromFile(
			m_rpDX3D_DEV, 
			pTexPath, 
			&m_pTexMap[pTexKey]);
	}

	inline VOID ReleaseTex()
	{
		m_pTexMap.clear();
	}

	inline const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey)
	{
		return m_pTexMap[pTexKey];
	}

private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;

	std::map<const TCHAR*, LPDIRECT3DTEXTURE9> m_pTexMap;
};

#endif // !TEX_STORAGE_H
