#include "3DBoard.h"

VOID Board3D::CreateRect(Vertex3D* p3DVertices, const D3DXVECTOR3& rHalfScale, const D3DXVECTOR3& rCenter,
	DWORD aRGB, FLOAT startTU, FLOAT startTV, FLOAT endTU, FLOAT endTV)
{
	const INT m_RECT_VERTICES_NUM = 4;

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		p3DVertices[i].m_Pos = rCenter;
		p3DVertices[i].m_Pos.x += (i % 3) ? rHalfScale.x : -rHalfScale.x;
		p3DVertices[i].m_Pos.y += (i / 2) ? rHalfScale.y : -rHalfScale.y;

		p3DVertices[i].m_Color = aRGB;

		p3DVertices[i].m_Tu = (i % 3) ? endTU : startTU;
		p3DVertices[i].m_Tv = (i / 2) ? endTV : startTV;

		p3DVertices[i].m_Normal.x = 0.f;
		p3DVertices[i].m_Normal.y = 0.f;
		p3DVertices[i].m_Normal.z = -1.f;
	}
}

VOID Board3D::CreateRect(Vertex3D* p3DVertices, const ObjData& rObjData)
{
	CreateRect(
		p3DVertices,
		rObjData.m_halfScale, rObjData.m_center,
		rObjData.m_aRGB,
		rObjData.m_texUV.m_startTU, rObjData.m_texUV.m_startTV,
		rObjData.m_texUV.m_endTU, rObjData.m_texUV.m_endTV
	);
}
