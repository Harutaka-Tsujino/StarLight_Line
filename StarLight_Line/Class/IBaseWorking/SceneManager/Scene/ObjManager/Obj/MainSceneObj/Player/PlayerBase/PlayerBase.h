#ifndef PLAYER_BASE_H_
#define PLAYER_BASE_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../../../../../../SceneManager.h"
#include "../../../Obj.h"
#include "../../GameCollision/GameCollision.h"
#include "../../../../../StageSelectScene/Enum/STAGE_LEVEL_KIND.h"
#include "../PlayerHP/PlayerHP.h"
#include "../PlayerResultData/PlayerResultData.h"

struct SurfaceCoordinate
{
public:
	float y;
	float x;
};

struct CoordinatePoint
{
public:
	int x;
	int y;
	int z;
};

class PlayerBase :public Obj
{
public:
	PlayerBase():Obj(OT_TRANSPARENCY, 1.0f), m_rGameCollision(GameCollision::GetInstance())
	{
	}

	virtual ~PlayerBase()
	{	
	}

	virtual VOID Init() {}
	virtual VOID Update() {}
	virtual VOID Render() {};

protected:
	enum HIT_KEY
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	VOID DefaultLight();

	/**
	*@brief 自機の動きを決め,動く範囲を制限する関数
	*/
	VOID RestrictedMoving();

	VOID DecideSpeed(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey);


	D3DXVECTOR3 m_Speed;

	static const int m_MAXXARRAYNUM = 4;
	static const int m_MAXYARRAYNUM = 3;

	const FLOAT MOVE_X_LENGTH = 1.21f;
	const FLOAT MOVE_X_MIDDLE_MULTI = 0.33f;

	const FLOAT PLAYER_MOVE_X[m_MAXXARRAYNUM] =
	{
		-MOVE_X_LENGTH ,
		-MOVE_X_LENGTH * MOVE_X_MIDDLE_MULTI ,
		MOVE_X_LENGTH * MOVE_X_MIDDLE_MULTI ,
		MOVE_X_LENGTH
	};

	const FLOAT MOVE_Y_LENGTH = 0.7f;
	const FLOAT MOVE_Y_BASE_POS = -0.88f;

	const FLOAT PLAYER_MOVE_Y[m_MAXYARRAYNUM] =
	{
		MOVE_Y_BASE_POS + MOVE_Y_LENGTH ,
		MOVE_Y_BASE_POS ,
		MOVE_Y_BASE_POS - MOVE_Y_LENGTH + 0.05f
	};

	const SurfaceCoordinate m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM] =
	{
		{ { PLAYER_MOVE_Y[0],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[3] } },
		{ { PLAYER_MOVE_Y[1],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[3] } },
		{ { PLAYER_MOVE_Y[2],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[3] } }
	};

	CoordinatePoint m_PlayerPoint;
	D3DXVECTOR3 m_PlayerPos;
	D3DXMATRIX m_World;

	INT m_EffectAddtionalRotateSpeed = 0;
	INT m_AdditionalFlashMulti = 0;

	GameCollision& m_rGameCollision;
};

#endif // !PLAYER_BASE_H_
