#ifndef PLAYER_H_
#define PLAYER_H_

#include <Windows.h>

#include "../../Obj.h"

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
		m_rGameLib.CreateTex(_T("PlayerTex"), _T("2DTextures/YellowAlpha58.png"));
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
	*@brief 自機の動きを決める関数
	*@param PrevPoint 自機が動く前の座標を保存した値
	*/
	VOID CanMovePos(const CoordinatePoint& PrevPoint);

	VOID CanMovePoint(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey);

	SurfaceCoordinate m_Speed;

	static const int m_MAXXARRAYNUM = 4;
	static const int m_MAXYARRAYNUM = 3;

	const SurfaceCoordinate m_BasePos[m_MAXYARRAYNUM][m_MAXXARRAYNUM] =
	{
		{ {0.005f,-0.005f},		{0.005f,-0.0025f} ,	{0.005f,0.f},	{0.005f,0.0025f}	},
		{ {0.0025f,-0.005f},	{0.0025f,-0.0025f},	{0.0025f,0.f},	{0.0025f,0.0025f}	},
		{ {0.f,-0.005f},		{0.f,-0.0025f},		{0.f,0.f},		{0.f,0.0025f}		}
	};

	CoordinatePoint m_PlayerPoint;
	SurfaceCoordinate m_PlayerPos;
};

#endif // !PLAYER_H_