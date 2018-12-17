#ifndef PLAYER_H_
#define PLAYER_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../../../../../SceneManager.h"
#include "../../Obj.h"
#include "../GameCollision/GameCollision.h"
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
		m_rGameLib.GetFbx(_T("Eiwi")).Release();
	};

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

	VOID SetIsClearedJudged();

	SurfaceCoordinate m_Speed;

	static const int m_MAXXARRAYNUM = 4;
	static const int m_MAXYARRAYNUM = 3;

	const SurfaceCoordinate m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM] =
	{
		{ { 0.05f,-0.1f},	{ 0.05f,-0.05f} ,	{ 0.05f,0.f},	{ 0.05f,0.05f}},
		{ { 0.f,-0.1f},		{ 0.f,-0.05f},		{ 0.f,0.f},		{ 0.f,0.05f}},
		{ { -0.05f,-0.1f},	{ -0.05f,-0.05f},	{ -0.05f,0.f},	{ -0.05f,0.05f}	}
	};

	CoordinatePoint m_PlayerPoint;
	D3DXVECTOR3 m_PlayerPos;
	D3DXMATRIX m_World;

	INT count;		//生存スコアを手に入れるところで使う

	PlayerResultData m_Data;
	PlayerHP m_Hp;

	GameCollision& m_rGameCollision;
};

#endif // !PLAYER_H_
