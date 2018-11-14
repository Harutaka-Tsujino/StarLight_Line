#ifndef DX_H
#define DX_H

#include <windows.h>
#include <d3dx9.h>

class DX
{
public:
	DX();									//Create()を呼ぶ
	~DX();

	const LPDIRECT3D9& GetLPDIRECT3D9();

private:
	VOID Create();							//他DX機能の基盤となるので初めに生成する

	LPDIRECT3D9 m_pD3D = nullptr;
};

#endif // !DX_H
