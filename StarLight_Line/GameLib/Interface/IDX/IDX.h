#ifndef I_DX_H
#define I_DX_H

#include <windows.h>
#include <d3dx9.h>

class IDX
{
public:
	virtual const LPDIRECT3D9& GetLPDIRECT3D9() = 0;
};

#endif // !I_DX_H
