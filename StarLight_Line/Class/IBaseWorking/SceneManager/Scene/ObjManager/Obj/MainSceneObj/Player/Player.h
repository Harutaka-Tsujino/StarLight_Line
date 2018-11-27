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
*@brief ���@�N���X
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
	*@brief ���@�̓��������߂�֐�
	*@param PrevPoint ���@�������O�̍��W��ۑ������l
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