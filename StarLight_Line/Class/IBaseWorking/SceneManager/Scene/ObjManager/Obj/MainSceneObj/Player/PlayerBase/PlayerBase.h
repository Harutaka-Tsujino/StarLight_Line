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
	PlayerBase() :Obj(OT_TRANSPARENCY, 1.0f), m_rGameCollision(GameCollision::GetInstance())
	{
		m_PlayerPoint = { 0, 0, 0 };
		m_PlayerPos = { 0.0f, 0.0f, 0.0f };
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

	static const FLOAT MOVE_X_LENGTH;
	static const FLOAT MOVE_X_MIDDLE_MULTI;

	static const FLOAT PLAYER_MOVE_X[m_MAXXARRAYNUM];

	static const FLOAT MOVE_Y_LENGTH;
	static const FLOAT MOVE_Y_BASE_POS;

	static const FLOAT PLAYER_MOVE_Y[m_MAXYARRAYNUM];

	static const SurfaceCoordinate m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM];

	CoordinatePoint m_PlayerPoint;
	D3DXVECTOR3 m_PlayerPos;
	D3DXMATRIX m_World;

	INT m_EffectAddtionalRotateSpeed = 0;
	INT m_AdditionalFlashMulti = 0;

	GameCollision& m_rGameCollision;
};

#endif // !PLAYER_BASE_H_
