#ifndef COLLISION_H_
#define COLLISION_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../GameLib.h"

class Collision
{
public:
	Collision() {}
	~Collision() {}

	inline BOOL CollidesCircles(const CustomVertex* pA, const CustomVertex* pB) const
	{
		D3DXVECTOR3 aSidelVec = pA[1].m_pos - pA[0].m_pos;
		FLOAT aRadius = D3DXVec3Length(&aSidelVec) / 2;
		D3DXVECTOR3 aCenterVec = pA[0].m_pos + (pA[2].m_pos - pA[0].m_pos) / 2;

		D3DXVECTOR3 bSidelVec = pB[1].m_pos - pB[0].m_pos;
		FLOAT bRadius = D3DXVec3Length(&bSidelVec) / 2;
		D3DXVECTOR3 bCenterVec = pB[0].m_pos + (pB[2].m_pos - pB[0].m_pos) / 2;

		D3DXVECTOR3 distanceVec = aCenterVec - bCenterVec;
		FLOAT distance = D3DXVec3Length(&distanceVec);

		if (distance < aRadius + bRadius) return TRUE;

		return FALSE;
	}

	inline BOOL CollidesRects(const CustomVertex* pObjA, const CustomVertex* pObjB) const
	{
		if ((pObjA[0].m_pos.x <= pObjB[0].m_pos.x && pObjB[0].m_pos.x <= pObjA[1].m_pos.x) ||
			(pObjA[0].m_pos.x <= pObjB[1].m_pos.x && pObjB[1].m_pos.x <= pObjA[1].m_pos.x) ||
			(pObjB[0].m_pos.x <= pObjA[0].m_pos.x && pObjA[1].m_pos.x <= pObjB[1].m_pos.x))
		{
			if ((pObjA[0].m_pos.y <= pObjB[0].m_pos.y && pObjB[0].m_pos.y <= pObjA[3].m_pos.y) ||
				(pObjA[0].m_pos.y <= pObjB[3].m_pos.y && pObjB[3].m_pos.y <= pObjA[3].m_pos.y) ||
				(pObjB[0].m_pos.y <= pObjA[0].m_pos.y && pObjA[3].m_pos.y <= pObjB[3].m_pos.y))
			{
				return TRUE;
			}
		}

		return FALSE;
	}
};

#endif // !COLLISION_H_
