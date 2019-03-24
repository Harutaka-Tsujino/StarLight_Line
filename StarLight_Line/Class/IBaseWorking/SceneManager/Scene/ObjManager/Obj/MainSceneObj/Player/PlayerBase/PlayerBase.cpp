#include "PlayerBase.h"

const FLOAT PlayerBase::MOVE_X_LENGTH = 1.21f;
const FLOAT PlayerBase::MOVE_X_MIDDLE_MULTI = 0.33f;

const FLOAT PlayerBase::PLAYER_MOVE_X[m_MAXXARRAYNUM] =
{
	-MOVE_X_LENGTH ,
	-MOVE_X_LENGTH * MOVE_X_MIDDLE_MULTI ,
	MOVE_X_LENGTH * MOVE_X_MIDDLE_MULTI ,
	MOVE_X_LENGTH
};

const FLOAT PlayerBase::MOVE_Y_LENGTH = 0.7f;
const FLOAT PlayerBase::MOVE_Y_BASE_POS = -0.88f;

const FLOAT PlayerBase::PLAYER_MOVE_Y[m_MAXYARRAYNUM] =
{
	MOVE_Y_BASE_POS + MOVE_Y_LENGTH ,
	MOVE_Y_BASE_POS ,
	MOVE_Y_BASE_POS - MOVE_Y_LENGTH + 0.05f
};

const SurfaceCoordinate PlayerBase::m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM] =
{
	{ { PLAYER_MOVE_Y[0],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[3] } },
	{ { PLAYER_MOVE_Y[1],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[3] } },
	{ { PLAYER_MOVE_Y[2],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[3] } }
};

VOID PlayerBase::DefaultLight()
{
	D3DXVECTOR3 vecDirection(-0.5f, -0.5f, -1.0f);
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;

	light.Diffuse.r = 0.8f;
	light.Diffuse.g = 0.8f;
	light.Diffuse.b = 0.8f;

	light.Ambient.r = 0.5f;
	light.Ambient.b = 0.5f;
	light.Ambient.g = 0.5f;

	light.Specular.r = 0.5f;
	light.Specular.b = 0.5f;
	light.Specular.g = 0.5f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);

	m_rGameLib.SetLight(light, 0);
}

VOID PlayerBase::RestrictedMoving()
{
	SurfaceCoordinate NextPos;
	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	NextPos.y = m_BasePos[*pPoY][*pPoX].y;
	NextPos.x = m_BasePos[*pPoY][*pPoX].x;

	//動かす
	m_PlayerPos.x += m_Speed.x;
	m_PlayerPos.y += m_Speed.y;

	//制限をかける
	m_PlayerPos.x = (m_Speed.x > 0) ? min(NextPos.x, m_PlayerPos.x) : max(NextPos.x, m_PlayerPos.x);
	m_PlayerPos.y = (m_Speed.y > 0) ? min(NextPos.y, m_PlayerPos.y) : max(NextPos.y, m_PlayerPos.y);

	if (NextPos.y == m_PlayerPos.y && NextPos.x == m_PlayerPos.x)
	{
		m_Speed.x = 0.0f;
		m_Speed.y = 0.0f;
	}
}

VOID PlayerBase::DecideSpeed(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey)
{
	memcpy(PrevPoint, &m_PlayerPoint, sizeof(CoordinatePoint));

	switch (HitKey)
	{
	case UP:
		if (m_Speed.x) break;

		--m_PlayerPoint.y;

		break;

	case DOWN:
		if (m_Speed.x) break;

		++m_PlayerPoint.y;

		break;

	case LEFT:
		if (m_Speed.y) break;

		--m_PlayerPoint.x;
		break;

	case RIGHT:
		if (m_Speed.y) break;

		++m_PlayerPoint.x;
		break;
	}

	const float FRAMENUM = 15.f;	//何フレームで割るか(自機のスピードの)

	if (HitKey == UP || HitKey == DOWN)
	{
		m_Speed.y = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y - m_PlayerPos.y) / FRAMENUM;

		return;
	}

	if (HitKey == LEFT || HitKey == RIGHT)
	{
		m_Speed.x = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x - m_PlayerPos.x) / FRAMENUM;

		return;
	}
}
