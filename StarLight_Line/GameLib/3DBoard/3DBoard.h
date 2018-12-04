#ifndef BOARD_3D_H_
#define BOARD_3D_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../DX/DX3D/CustomVertexEditor/Data/ObjData.h"

/**
* @brief 3Dを描画するにあたって必要な頂点情報
*/
struct Vertex3D
{
public:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Normal;
	DWORD		m_Color;
	FLOAT		m_Tu;
	FLOAT		m_Tv;
};

class Board3D
{
public:
	Board3D() {}
	~Board3D() {}

	VOID CreateRect(Vertex3D* p3DVertices, const D3DXVECTOR3& rHalfScale, const D3DXVECTOR3& rCenter,
		DWORD aRGB = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	VOID CreateRect(Vertex3D* p3DVertices, const ObjData& rObjData);
};


#endif // !BOARD_3D_H_
