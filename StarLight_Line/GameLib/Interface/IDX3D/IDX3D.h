#ifndef I_DX3D_H
#define I_DX3D_H

#include <windows.h>
#include <d3dx9.h>

class IDX3D
{
public:
	virtual inline const LPDIRECT3DDEVICE9& GetLPDIRECT3DDEVICE9() const = 0;
};

#endif // !I_DX3D_H
