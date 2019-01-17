#ifndef RESULT_TWO_PLAYER_OBJ_H_
#define RESULT_TWO_PLAYER_OBJ_H_

#include "../../../../../SceneManager.h"
#include "../../Obj.h"
#include "../../MainSceneObj/ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../../MainSceneObj/ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../../MainSceneObj/ADV/Chapter/Section/Text/Text.h"

class ResultTwoPlayerBack:public Obj
{
public:
	ResultTwoPlayerBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~ResultTwoPlayerBack()
	{
		m_rGameLib.ReleaseTex();
	}

	VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/SaveData/SaveData_Back.png"));
	}

	VOID Update() {};
	
	VOID Render()
	{
		m_rGameLib.SetCameraTransform();

		TextRender();

		ObjData data;
		data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		data.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
	}

private:
	VOID TextRender();	//resultの文字を描画
};

class ResultTwoPlayerFrame :public Obj
{
public:
	ResultTwoPlayerFrame() :Obj(OT_UI, 0.9)
	{
		Init();
	}

	~ResultTwoPlayerFrame()
	{

	}

	VOID Init() {};
	VOID Update() {};

	VOID Render()
	{
		PlayerTextRender();

		FrameRender();
	}

private:
	const INT PLAYER_TYPE_MAX = 2;

	VOID FrameRender();

	VOID PlayerTextRender();
};

class ResultTwoPlayerScore :public Obj
{
public:
	ResultTwoPlayerScore() :Obj(OT_UI, 0.9f)
	{
		Init();
	}

	~ResultTwoPlayerScore();

	VOID Init()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
		{
			m_Score[i] = rSceneManager.Get2PModeScore(i);
		}
	}

	VOID Update();
	VOID Render();

private:
	INT m_Score[Joycon::MAX_CONTROLLER];
};

#endif // !RESULT_TWO_PLAYER_OBJ_H_
