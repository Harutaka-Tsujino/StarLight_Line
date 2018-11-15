#ifndef DX_H
#define DX_H

#include <windows.h>
#include <d3dx9.h>

#include "../Interface/IDX/IDX.h" 

class DX :public IDX
{
public:
	DX();
	~DX();

	inline const LPDIRECT3D9& GetLPDIRECT3D9() const
	{
		return m_pD3D;
	}

private:
	VOID Create();							//他DX機能の基盤となるので初めに生成する

	LPDIRECT3D9 m_pD3D = nullptr;
};

#endif // !DX_H
