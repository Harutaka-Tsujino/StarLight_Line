#ifndef FONT_H
#define FONT_H

#include <windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

class Font
{
public:
	Font(const LPDIRECT3DDEVICE9& rpDX3DDev) :m_rpDX3D_DEV(rpDX3DDev) {};

	~Font() 
	{
		Release();
	}

	inline VOID Release()
	{
		for (auto i : m_fonts)
		{
			i.second->Release();
		}
	}

	inline VOID Erase(const TCHAR* pFontKey)
	{
		if (Exists(pFontKey)) return;

		m_fonts[pFontKey]->Release();
		m_fonts.erase(pFontKey);
	}

	inline VOID Create(const TCHAR* pKey,D3DXVECTOR2 scale, const TCHAR* pFontName, UINT thickness = 0)
	{
		if (Exists(pKey)) return;

		D3DXCreateFont(
			m_rpDX3D_DEV,
			static_cast<INT>(scale.y), static_cast<INT>(scale.x), 
			thickness, 
			0, 
			0, 
			SHIFTJIS_CHARSET, 
			0, 
			0, 
			0, 
			pFontName, 
			&m_fonts[pKey]);
	}

	inline BOOL Exists(const TCHAR* pKey)
	{
		return (m_fonts[pKey] != nullptr);
	}

	inline const LPD3DXFONT Get(const TCHAR* pKey)
	{
		return m_fonts[pKey];
	}

private:
	const LPDIRECT3DDEVICE9& m_rpDX3D_DEV = nullptr;

	std::map<const TCHAR*, LPD3DXFONT> m_fonts;
};

#endif //! FONT_H
