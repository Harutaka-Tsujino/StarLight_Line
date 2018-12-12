#ifndef GAME_COLLISION_H_
#define GAME_COLLISION_H_

#include <map>
#include <vector>

#include "../../../../../../../../GameLib/GameLib.h"
#include "../../../../../../../Singleton/Singleton.h"

#include "../Enum/STAR_TYPE.h"

struct StarCollisionData
{
public:
	STAR_TYPE m_Type;
	const D3DXVECTOR3* m_Point;
	BOOL m_IsCollided =  FALSE;
};

class GameCollision :public Singleton<GameCollision>
{
public:
	friend class Singleton<GameCollision>;

	~GameCollision()
	{
	}

	inline VOID ResiterVertices(TCHAR* pKey, CustomVertex* pVertex)
	{
		m_Vertex[pKey] = pVertex;
	}

	inline VOID ReleaseVertices()
	{
		m_Vertex.clear();
	}
	
	inline VOID ResiterPlayerPoint(const TCHAR* pKey, const D3DXVECTOR3* pPoint)
	{
		m_PlayerPoint[pKey] = pPoint;
	}

	inline VOID ResiterEnemyPoint(const D3DXVECTOR3* Point, const STAR_TYPE& Type)
	{
		StarCollisionData* Buff = new StarCollisionData();
		Buff->m_Point = Point;
		Buff->m_Type = Type;
		m_Enemy.push_back(Buff);
	}

	inline VOID ReleaseEnemyPoint()
	{
		for (int i = 0;i != m_Enemy.size();++i)
		{
			delete m_Enemy[i];
			m_Enemy[i] = nullptr;
		}

		m_Enemy.clear();
	}

	inline VOID ReleasePlayerPoint()
	{
		m_PlayerPoint.clear();
	}

	BOOL HitSomething(const TCHAR* pKey, const STAR_TYPE& Type,
		const FLOAT& aRadius, const FLOAT& bRadius)
	{
		for (int i = 0;i != m_Enemy.size();++i)
		{
			if (m_Enemy[i]->m_Type != Type) continue;

			if (!CollidesStar(pKey, i, aRadius, bRadius)) continue;

			if (m_Enemy[i]->m_IsCollided) return FALSE;

			return m_Enemy[i]->m_IsCollided =  TRUE;
		}

		return FALSE;
	}

	inline BOOL CollidesStar(const TCHAR* pKey, const INT& StarNum,
		const FLOAT& aRadius, const FLOAT& bRadius)
	{
		D3DXVECTOR3 PlayerScreenPos = m_rGameLib.TransScreen(*m_PlayerPoint[pKey]);
		D3DXVECTOR3 EnemyScreenPos  = m_rGameLib.TransScreen(*m_Enemy[StarNum]->m_Point);

		if ((-bRadius > EnemyScreenPos.y) || EnemyScreenPos.y > m_rGameLib.GetWndSize().m_y + bRadius) return FALSE;

		return m_rGameLib.CollidesCircles(&PlayerScreenPos, &EnemyScreenPos, aRadius, bRadius);
	}

	inline BOOL CollidesRects(const TCHAR* KeyA, const TCHAR* KeyB)
	{
		return m_rGameLib.CollidesRects(m_Vertex[KeyA], m_Vertex[KeyB]);
	}

private:
	GameCollision() :m_rGameLib(GameLib::GetInstance())
	{
	}

	GameLib& m_rGameLib;

	std::map<const TCHAR*, const CustomVertex*> m_Vertex;
	std::map<const TCHAR*, const D3DXVECTOR3*> m_PlayerPoint;
	std::vector<StarCollisionData*> m_Enemy;
	
};

#endif // !GAME_COLLISION_H_
