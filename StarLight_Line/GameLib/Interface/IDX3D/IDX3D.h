#ifndef I_DX3D_H
#define I_DX3D_H

#include <windows.h>
#include <d3dx9.h>

class IDX3D
{
public:
	virtual const LPDIRECT3DDEVICE9& GetLPDIRECT3DDEVICE9() = 0;
	virtual VOID ChangeWndMode() = 0;	//使用時DX3DDevがロストする可能性がある
};

#endif // !I_DX3D_H