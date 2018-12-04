#ifndef PLAYER_H_
#define PLAYER_H_

#include <Windows.h>

#include "../../Obj.h"
#include "PlayerScore/PlayerScore.h"

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
	Player() :Obj(OT_TRANSPARENCY,1.0f)
	{
		m_rGameLib.CreateFbx(_T("Eiwi"), "3DModels/Eiwi/Eiwi.fbx");
		Init();
	}

	~Player() {};
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

	SurfaceCoordinate m_Speed;

	static const int m_MAXXARRAYNUM = 4;
	static const int m_MAXYARRAYNUM = 3;

	const SurfaceCoordinate m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM] =
	{
		{ {0.1f,-0.1f},	{0.1f,-0.05f} ,	{0.1f,0.f},	{0.1f,0.05f}},
		{ {0.05f,-0.1f},{0.05f,-0.05f},	{0.05f,0.f},{0.05f,0.05f}},
		{ {0.f,-0.1f},	{0.f,-0.05f},	{0.f,0.f},	{0.f,0.05f}	}
	};

	CoordinatePoint m_PlayerPoint;
	SurfaceCoordinate m_PlayerPos;

	static INT count;		//生存スコアを手に入れるところで使う

	PlayerScore m_Score;
	INT m_Hp = 5;
};

#endif // !PLAYER_H_