#ifndef MAIN_TWO_PLAYER_OBJ_H_
#define MAIN_TWO_PLAYER_OBJ_H_

#include <Windows.h>

#include "../../Obj.h"

class ScoreFrameforTwoPlayer :public Obj
{
public:
	ScoreFrameforTwoPlayer() :Obj(OT_UI, 1.0f)
	{
		Init();
	}

	~ScoreFrameforTwoPlayer()
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init()
	{
		m_rGameLib.CreateTex(_T("ScoreFrame"), _T("2DTextures/Main/main_scoreframe.png"));
	}

	VOID Update() {};

	VOID Render()
	{
		m_rGameLib.SetCameraTransform();

		ObjData data;
		CustomVertex back[4];

		for (int i = 0;i < 2;++i)
		{
			data.m_center = { m_WND_SIZE.m_x * (0.25f + (0.5f * i)), m_WND_SIZE.m_y * 0.9f, 0.005f };
			data.m_halfScale = { m_WND_SIZE.m_x * 0.18f, m_WND_SIZE.m_y * 0.055f, 0.0f };

			m_rGameLib.CreateRect(back, data);
			m_rGameLib.Render(back, m_rGameLib.GetTex(_T("ScoreFrame")));
		}
	}
};

#endif // !MAIN_TWO_PLAYER_OBJ_H_
