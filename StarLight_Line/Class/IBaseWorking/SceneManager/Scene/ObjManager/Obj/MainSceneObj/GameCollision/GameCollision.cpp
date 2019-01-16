#include "GameCollision.h"

BOOL GameCollision::Hit1PMode(const TCHAR* pKey, int Loop)
{
	const FLOAT WND_Y_SIZE = static_cast<FLOAT>(m_rGameLib.GetWndSize().m_y);
	const FLOAT STAR_HALF_SCALE = 50.0f;

	if (m_Enemy[Loop]->m_IsCollided) return FALSE;

	//当たることのない星は判定をとらないようにする
	if (m_Enemy[Loop]->m_Point->y < -STAR_HALF_SCALE - WND_Y_SIZE * 0.3f || m_Enemy[Loop]->m_Point->y > 2.5f * WND_Y_SIZE + STAR_HALF_SCALE) return FALSE;

	if (!CollidesStar(pKey, Loop)) return FALSE;

	D3DXVECTOR3 PlayerScreenPos(m_rGameLib.TransScreen(*m_PlayerPoint[pKey]));
	PlayerScreenPos.z = 0.0f;

	rEffectManager.CreateEffect(PlayerScreenPos, m_Enemy[Loop]->m_Type);

	return  m_Enemy[Loop]->m_IsCollided = TRUE;
}

BOOL GameCollision::Hit2PMode(const TCHAR* pKey, int Loop)
{
	const FLOAT WND_Y_SIZE = static_cast<FLOAT>(m_rGameLib.GetWndSize().m_y);
	const FLOAT STAR_HALF_SCALE = 50.0f;

	//次のフレームでは絶対にフラグがTRUEになるので&&にしている
	if (m_Enemy[Loop]->m_IsCollided && m_Enemy[Loop]->m_Is2PCollided) return FALSE;

	//当たることのない星は判定をとらないようにする
	if (m_Enemy[Loop]->m_Point->y < -STAR_HALF_SCALE - WND_Y_SIZE * 0.3f || m_Enemy[Loop]->m_Point->y > 2.5f * WND_Y_SIZE + STAR_HALF_SCALE) return FALSE;

	if (!CollidesStar(pKey, Loop)) return FALSE;

	D3DXVECTOR3 PlayerScreenPos(m_rGameLib.TransScreen(*m_PlayerPoint[pKey]));
	PlayerScreenPos.z = 0.0f;

	rEffectManager.CreateEffect(PlayerScreenPos, m_Enemy[Loop]->m_Type);

	if (pKey == _T("PlayerOne")) return m_Enemy[Loop]->m_IsCollided = TRUE;
	
	return m_Enemy[Loop]->m_Is2PCollided = TRUE;
}
