#ifndef GAME_COLLISION_H_
#define GAME_COLLISION_H_

#include <map>
#include <vector>

#include "../../../../../../../../GameLib/GameLib.h"
#include "../../../../../../../Singleton/Singleton.h"

#include "../Enum/STAR_TYPE.h"

#include <crtdbg.h>

#include <cstdio>
#include <cstdlib>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

struct StarCollisionData
{
public:
	STAR_TYPE m_Type = static_cast<STAR_TYPE>(NULL);
	const D3DXVECTOR3* m_Point;
	BOOL m_IsCollided =  FALSE;
};

class GameCollision :public Singleton<GameCollision>
{
public:
	friend class Singleton<GameCollision>;

	~GameCollision()
	{
		ReleaseEnemyPoint();
		ReleaseVertices(); //! 現在未使用
	}

	inline VOID ResiterVertices(TCHAR* pKey, CustomVertex* pVertex)
	{
		m_Vertex[pKey] = pVertex;
	}

	inline VOID ReleaseVertices()
	{
		/*for (auto i : m_Vertex)
		{
			delete i.second;
		}*/

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
		for (auto i : m_Enemy)
		{
			delete i;
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

			if (m_Enemy[i]->m_IsCollided) continue;

			if (!CollidesStar(pKey, i, aRadius, bRadius)) continue;

			return m_Enemy[i]->m_IsCollided =  TRUE;
		}

		return FALSE;
	}

	inline BOOL CollidesStar(const TCHAR* pKey, const INT& StarNum,
		const FLOAT& aRadius, const FLOAT& bRadius)
	{
		D3DXVECTOR3 PlayerScreenPos(m_rGameLib.TransScreen(*m_PlayerPoint[pKey]));
		D3DXVECTOR3 EnemyScreenPos = { m_Enemy[StarNum]->m_Point->x,m_Enemy[StarNum]->m_Point->y,m_Enemy[StarNum]->m_Point->z };

		const FLOAT WND_Y_SIZE = static_cast<FLOAT>(m_rGameLib.GetWndSize().m_y);

		if ((2 * -bRadius > EnemyScreenPos.y) || EnemyScreenPos.y > WND_Y_SIZE + 2 * bRadius) return FALSE;

		FLOAT playerRadius = 38.f - 30.0f * (1.0f - (PlayerScreenPos.y / WND_Y_SIZE));

		ObjData obj;
		obj.m_center = PlayerScreenPos;

		const FLOAT halfScale = 20.0f;
		obj.m_halfScale = { playerRadius, playerRadius, 0.0f };

		CustomVertex vertex[4];

		m_rGameLib.CreateRect(vertex, obj);

		m_rGameLib.Render(vertex);

		//PlayerScreenPos.x += 10.0f;

		return m_rGameLib.CollidesCircles(&PlayerScreenPos, &EnemyScreenPos, playerRadius, bRadius);
	}

	inline BOOL CollidesRects(const TCHAR* KeyA, const TCHAR* KeyB)
	{
		return m_rGameLib.CollidesRects(m_Vertex[KeyA], m_Vertex[KeyB]);
	}

	BOOL GetStarIsCollided(INT elementNum)
	{
		return m_Enemy[elementNum]->m_IsCollided;
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
