#ifndef COLLISION_H_
#define COLLISION_H_

#include <Windows.h>

#include <map>
#include <vector>

#include <d3dx9.h>

#include "../GameLib.h"

//衝突判定クラス
class Collision
{
public:
	Collision() {}
	~Collision() {}

	inline BOOL CollidesCircles(const D3DXVECTOR3* pA, const D3DXVECTOR3* pB,
								const FLOAT& aRadius, const FLOAT& bRadius) const
	{
		D3DXVECTOR2 AVec2(pA->x,pA->y);
		D3DXVECTOR2 BVec2(pB->x,pB->y);

		D3DXVECTOR2 DistanceVec = AVec2 - BVec2;
		FLOAT Distance = D3DXVec2Length(&DistanceVec);

		if (Distance <= aRadius + bRadius) return TRUE;

		return FALSE;
	}

	//球同士の衝突判定
	inline BOOL CollidesCircles(const CustomVertex* pA, const CustomVertex* pB) const
	{
		//pAについての計算
		D3DXVECTOR3 aSide = pA[1].m_pos - pA[0].m_pos;
		FLOAT aRadius = D3DXVec3Length(&aSide) / 2;
		D3DXVECTOR3 aCenter = pA[0].m_pos + (pA[2].m_pos - pA[0].m_pos) / 2;

		//pBについての計算
		D3DXVECTOR3 bSide = pB[1].m_pos - pB[0].m_pos;
		FLOAT bRadius = D3DXVec3Length(&bSide) / 2;
		D3DXVECTOR3 bCenter = pB[0].m_pos + (pB[2].m_pos - pB[0].m_pos) / 2;

		//aとbの距離の算出
		D3DXVECTOR3 distanceVec = aCenter - bCenter;
		FLOAT distance = D3DXVec3Length(&distanceVec);

		if (distance < aRadius + bRadius) return TRUE;

		return FALSE;
	}

	//矩形同士の衝突判定
	inline BOOL CollidesRects(const CustomVertex* pObjA, const CustomVertex* pObjB) const
	{
		BOOL collidesX =
			(pObjA[0].m_pos.x <= pObjB[0].m_pos.x && pObjB[0].m_pos.x <= pObjA[1].m_pos.x) ||
			(pObjA[0].m_pos.x <= pObjB[1].m_pos.x && pObjB[1].m_pos.x <= pObjA[1].m_pos.x) ||
			(pObjB[0].m_pos.x <= pObjA[0].m_pos.x && pObjA[1].m_pos.x <= pObjB[1].m_pos.x);

		BOOL collidesY =
			(pObjA[0].m_pos.y <= pObjB[0].m_pos.y && pObjB[0].m_pos.y <= pObjA[3].m_pos.y) ||
			(pObjA[0].m_pos.y <= pObjB[3].m_pos.y && pObjB[3].m_pos.y <= pObjA[3].m_pos.y) ||
			(pObjB[0].m_pos.y <= pObjA[0].m_pos.y && pObjA[3].m_pos.y <= pObjB[3].m_pos.y);

		if (collidesX && collidesY) return TRUE;

		return FALSE;
	}

};

#endif // !COLLISION_H_
