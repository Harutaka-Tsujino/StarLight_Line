#ifndef PLAYER_H_
#define PLAYER_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../../../../../SceneManager.h"
#include "../../Obj.h"
#include "../GameCollision/GameCollision.h"
#include "../../../../StageSelectScene/Enum/STAGE_LEVEL_KIND.h"
#include "PlayerResultData/PlayerResultData.h"
#include "PlayerHP/PlayerHP.h"

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

/**
*@brief 自機クラス
*/
class Player :public Obj
{
public:
	Player() :Obj(OT_TRANSPARENCY, 1.0f), m_rGameCollision(GameCollision::GetInstance())
	{
		m_rGameLib.CreateFbx(_T("Eiwi"), "3DModels/Eiwi/Eiwi.fbx");
		Init();
	}

	~Player()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		m_ResultData.JudgeGameFailure(7); //引数は適当
		rSceneManager.SetResultData(m_ResultData.GetResultData());

		m_rGameLib.GetFbx(_T("Eiwi")).Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

private:
	enum HIT_KEY
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	/**
	*@brief 自機の動きを決め,動く範囲を制限する関数
	*/
	VOID RestrictedMoving();

	VOID DecideSpeed(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey);

	/**
	*@brief 生存している場合に、スコアを獲得する関数
	*@param LevelScore 難易度によってスコアを獲得できる
	*/
	VOID ObtainScoreToExist(const INT& LevelScore);

	D3DXVECTOR3 m_Speed;

	static const int m_MAXXARRAYNUM = 4;
	static const int m_MAXYARRAYNUM = 3;

	const FLOAT PLAYER_MOVE_X[m_MAXXARRAYNUM] = { -0.1395f ,-0.0465f ,0.0465f ,0.1395f };
	const FLOAT PLAYER_MOVE_Y[m_MAXYARRAYNUM] = { 0.05f ,0.f ,-0.053f };

	const SurfaceCoordinate m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM] =
	{
		{ { PLAYER_MOVE_Y[0],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[0],PLAYER_MOVE_X[3] }},
		{ { PLAYER_MOVE_Y[1],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[1],PLAYER_MOVE_X[3] }},
		{ { PLAYER_MOVE_Y[2],PLAYER_MOVE_X[0] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[1] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[2] },{ PLAYER_MOVE_Y[2],PLAYER_MOVE_X[3] }}
	};

	const FLOAT m_CAN_MOVE_Z[3] = { 0.15f,0.2f,0.25f };

	CoordinatePoint m_PlayerPoint;
	D3DXVECTOR3 m_PlayerPos;
	D3DXMATRIX m_World;

	INT count;		//生存スコアを手に入れるところで使う

	StageData m_StageData;
	PlayerResultData m_ResultData;
	PlayerHP m_Hp;

	GameCollision& m_rGameCollision;
};

#endif // !PLAYER_H_
