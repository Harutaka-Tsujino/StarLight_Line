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
	ResultTwoPlayerFrame() :Obj(OT_UI, 0.9f)
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

	VOID PlayerTextRender();
	VOID FrameRender();
};

class ResultTwoPlayerScore :public Obj
{
public:
	ResultTwoPlayerScore() :Obj(OT_UI, 0.9f)
	{
		Init();
	}

	~ResultTwoPlayerScore() 
	{
		m_rGameLib.ReleaseTex();
	};

	VOID Init()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
		{
			m_Score[i] = rSceneManager.Get2PModeScore(i);
		}

		m_rGameLib.CreateTex(_T("CheckStar"), _T("2DTextures/Result/StarNoteWhite.png"));
	}

	VOID Update();
	VOID Render();

private:
	inline VOID SkipStage()
	{
		for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
		{
			m_increaseStagingFrameCount[i] = m_INCREASE_STAGING_FRAME_COUNT_MAX;
		}
	}

	VOID ScoreRender();

	VOID RenderDraw();

	VOID RenderWinner();

	VOID RenderLoser();

	VOID RenderCheckStar();

	INT m_Score[Joycon::MAX_CONTROLLER];

	ObjData m_checkStarData[Joycon::MAX_CONTROLLER];

	const INT m_INCREASE_STAGING_FRAME_COUNT_MAX = 150;
	INT m_increaseStagingFrameCount[Joycon::MAX_CONTROLLER] = { 0,0 };	//! 現物合わせ

	BOOL m_stagingIsEnd = FALSE;
	BOOL m_pushButton[Joycon::MAX_CONTROLLER] = { FALSE,FALSE };
};

class ResultTwoPlayerStage :public Obj
{
public:
	ResultTwoPlayerStage() :Obj(OT_TRANSPARENCY, 0.f)
	{
		Init();
	}

	~ResultTwoPlayerStage()
	{

	}

	VOID Init()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.GetStageData(&m_stageData);
	}

	VOID Update() {};
	VOID Render();

private:
	VOID GetStageStringAndCharsNum(TString* pTString, INT* pCharsNum);

	VOID GetStageLevelAndCharsNum(TString* pTString, INT* pCharsNum, TextFormat* pTextFormat);

	StageData m_stageData;
};

#endif // !RESULT_TWO_PLAYER_OBJ_H_
