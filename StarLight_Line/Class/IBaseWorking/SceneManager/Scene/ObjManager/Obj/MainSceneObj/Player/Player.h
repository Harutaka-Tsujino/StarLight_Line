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
	VOID CanMovePos(const CoordinatePoint& PrevPoint);

	SurfaceCoordinate m_Speed;

	static const int m_MaxXArrayNum = 4;
	static const int m_MaxYArrayNum = 3;

	const SurfaceCoordinate m_BasePos[m_MaxYArrayNum][m_MaxXArrayNum] =
	{
		{ {0.005f,(-0.005f)},	{0.005f,(-0.0025f)} ,	{0.005f,0.f},	{0.005f,0.0025f}	},
		{ {0.0025f,(-0.005f)},	{0.0025f,(-0.0025f)},	{0.0025f,0.f},	{0.0025f,0.0025f}	},
		{ {0.f,(-0.005f)},		{0.f,(-0.0025f)},		{0.f,0.f},		{0.f,0.0025f}		}
	};

	CoordinatePoint m_PlayerPoint;
	SurfaceCoordinate m_PlayerPos;
};

#endif // !PLAYER_H_