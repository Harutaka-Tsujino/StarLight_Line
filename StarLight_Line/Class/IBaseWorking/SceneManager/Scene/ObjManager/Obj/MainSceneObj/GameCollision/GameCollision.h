#ifndef GAME_COLLISION_H_
#define GAME_COLLISION_H_

#include <windows.h>

#include <map>
#include <vector>

#include "../../../../../../../../GameLib/GameLib.h"
#include "../../../../../../../Singleton/Singleton.h"
#include "../../../../../../../../GameLib/EffectManager/EffectManager.h"
#include "../../../../../../../../GameLib/EffectManager/Effect/Effects/Enum/EFFECT_ID.h"
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
		m_Enemy.shrink_to_fit();
	}

	inline VOID ReleasePlayerPoint()
	{
		m_PlayerPoint.clear();
	}

	inline BOOL HitSomething(const TCHAR* pKey, const STAR_TYPE& Type,
		const FLOAT& aRadius, const FLOAT& bRadius)
	{
		const FLOAT WND_Y_SIZE = static_cast<FLOAT>(m_rGameLib.GetWndSize().m_y);
		const FLOAT STAR_HALF_SCALE = 50.0f;

		for (int i = 0;i != m_Enemy.size();++i)
		{
			if (m_Enemy[i]->m_Type != Type) continue;

			if (m_Enemy[i]->m_IsCollided) continue;

			//当たることのない星は判定をとらないようにする
			if (m_Enemy[i]->m_Point->y < -STAR_HALF_SCALE - WND_Y_SIZE * 0.3f || m_Enemy[i]->m_Point->y > 2.5f * WND_Y_SIZE + STAR_HALF_SCALE) continue;

			if (!CollidesStar(pKey, i, aRadius, bRadius)) continue;

			D3DXVECTOR3 PlayerScreenPos(m_rGameLib.TransScreen(*m_PlayerPoint[pKey]));
			PlayerScreenPos.z = 0.0f;

			rEffectManager.CreateEffect(PlayerScreenPos, m_Enemy[i]->m_Type);
	
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

		FLOAT playerRadius = 38.0f - 26.0f * (1.0f - (PlayerScreenPos.y / WND_Y_SIZE));
		FLOAT enemyRadius  = 50.0f - 33.0f * (1.0f - (EnemyScreenPos.y / WND_Y_SIZE));

		return m_rGameLib.CollidesCircles(&PlayerScreenPos, &EnemyScreenPos, playerRadius, enemyRadius);
	}

	inline BOOL CollidesRects(const TCHAR* KeyA, const TCHAR* KeyB)
	{
		return m_rGameLib.CollidesRects(m_Vertex[KeyA], m_Vertex[KeyB]);
	}

	inline BOOL GetStarIsCollided(INT elementNum)
	{
		return m_Enemy[elementNum]->m_IsCollided;
	}
	
private:
	GameCollision() :m_rGameLib(GameLib::GetInstance()), rEffectManager(EffectManager::GetInstance())
	{
	}

	GameLib& m_rGameLib;

	std::map<const TCHAR*, const CustomVertex*> m_Vertex;
	std::map<const TCHAR*, const D3DXVECTOR3*> m_PlayerPoint;
	std::vector<StarCollisionData*> m_Enemy;

	EffectManager& rEffectManager;
};

#endif // !GAME_COLLISION_H_
