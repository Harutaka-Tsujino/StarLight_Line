/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#ifndef RESULT_SCENE_OBJ_H
#define RESULT_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"
#include "../../../../Data/ResultData.h"
#include "../DataSaver/DataSaver.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Text.h"

class ResultSceneBack :public Obj
{
public:
	ResultSceneBack() :Obj(OT_BACK, 1.0f)
	{
		Init();
	}

	~ResultSceneBack()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/SaveData/SaveData_Back.png"));
	}

	inline VOID Update() {};

	inline VOID Render()
	{
		RenderHead();

		m_rGameLib.SetCameraTransform();

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
	}

private:
	VOID RenderHead();
};

class ResultDataScore :public Obj
{
public:
	ResultDataScore(INT score, DWORD caseColor) :Obj(OT_TRANSPARENCY, 0.9f), m_SCORE(score), m_CASE_COLOR(caseColor)
	{
		Init();
	}

	~ResultDataScore()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
	}

	inline VOID Update() {};

	VOID Render();

	inline BOOL StagingIsEnd() const
	{
		return m_stagingIsEnd;
	}

	inline VOID SkipStage()
	{
		m_increaseStagingFrameCount = m_INCREASE_STAGING_FRAME_COUNT_MAX;
	}

private:
	inline VOID RenderCase() const
	{
		ObjData scoreCaseData;
		scoreCaseData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.26f, m_Z };		//! 現物合わせ
		scoreCaseData.m_halfScale	= { m_WND_SIZE.m_x * 0.39f, m_WND_SIZE.m_y * 0.11f, 0.0f };		//! 現物合わせ

		scoreCaseData.m_aRGB = m_CASE_COLOR;

		CustomVertex scoreCase[4];
		m_rGameLib.CreateRect(scoreCase, scoreCaseData);
		m_rGameLib.Render(scoreCase, nullptr);
	}

	VOID RenderHead();

	const INT m_SCORE;

	const INT m_INCREASE_STAGING_FRAME_COUNT_MAX = 150;
	INT m_increaseStagingFrameCount = 0;	//! 現物合わせ

	BOOL m_stagingIsEnd = FALSE;

	const DWORD m_CASE_COLOR;
};

class ResultDataStage :public Obj
{
public:
	ResultDataStage(INT stage, INT difficulty, DWORD caseColor) :Obj(OT_TRANSPARENCY, 0.9f), m_CASE_COLOR(caseColor)
	{
		Init();
	}

	~ResultDataStage()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.GetStageData(&m_stageData);
	}

	inline VOID Update() {};

	VOID Render();

private:
	inline VOID RenderCase() const
	{
		ObjData stageCaseData;
		stageCaseData.m_center		= { m_WND_SIZE.m_x * 0.31f, m_WND_SIZE.m_y * 0.69f, m_Z };		//! 現物合わせ
		stageCaseData.m_halfScale	= { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.2f, 0.0f };		//! 現物合わせ

		stageCaseData.m_aRGB = m_CASE_COLOR;

		CustomVertex stageCase[4];
		m_rGameLib.CreateRect(stageCase, stageCaseData);
		m_rGameLib.Render(stageCase, nullptr);
	}

	VOID GetStageStringAndCharsNum(TString* pTString, INT* pCharsNum);

	VOID GetStageLevelAndCharsNum(TString* pTString, INT* pCharsNum, TextFormat* pTextFormat);

	StageData m_stageData;

	const DWORD m_CASE_COLOR;
};

class ResultDataClearStar :public Obj
{
public:
	ResultDataClearStar(INT clearStarsNum, INT clearStarsMax, DWORD caseColor) :Obj(OT_TRANSPARENCY, 0.9f),
		m_CLEAR_STARS_NUM(clearStarsNum), m_CLEAR_STARS_MAX(clearStarsMax), m_CASE_COLOR(caseColor)
	{
		Init();
	}

	~ResultDataClearStar()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_starsVec.resize(m_CLEAR_STARS_MAX);

		m_rGameLib.CreateTex(_T("Star"), _T("2DTextures/Result/StarNote.png"));
	}

	inline VOID Update() {};

	VOID Render();
	
	inline BOOL StagingIsEnd() const
	{
		return m_stagingIsEnd;
	}

	inline VOID StartStaging()
	{
		if (m_stagingCount) return;
		++m_stagingCount;
	}
	
	inline VOID SkipStage()
	{
		m_stagingCount = m_stageCountMax;
	}

private:
	struct Stars
	{
	public:
		Stars()
		{
			m_objData.m_aRGB = 0x88555555;	//! 現物合わせ
		}
		
		INT m_alphaCount = 0;

		ObjData m_objData;

		CustomVertex m_customVertices[4];
	};

	inline VOID RenderCase() const
	{
		ObjData starCaseData;
		starCaseData.m_center		= { m_WND_SIZE.m_x * 0.74f, m_WND_SIZE.m_y * 0.69f, m_Z };	//! 現物合わせ
		starCaseData.m_halfScale	= { m_WND_SIZE.m_x * 0.15f, m_WND_SIZE.m_y * 0.2f, 0.0f };	//! 現物合わせ

		starCaseData.m_aRGB = m_CASE_COLOR;

		CustomVertex starCase[4];
		m_rGameLib.CreateRect(starCase, starCaseData);
		m_rGameLib.Render(starCase, nullptr);
	}

	VOID RenderHead();

	const INT m_CLEAR_STARS_MAX = NULL;
	const INT m_CLEAR_STARS_NUM = NULL;
	std::vector<Stars> m_starsVec;

	const DWORD m_CASE_COLOR;

	INT m_stageCountMax = NULL;
	INT m_stagingCount = 0;

	BOOL m_stagingIsEnd = FALSE;
};

class ResultSceneResultData :public Obj
{
public:
	ResultSceneResultData() :Obj(OT_TRANSPARENCY, 0.8f)
	{
		Init();
	}

	~ResultSceneResultData()
	{
		delete m_pResultDataClearStar;

		delete m_pResultDataStage;

		delete m_pResultDataScore;

		m_rGameLib.CreateTex(_T("Result"), _T("2DTextures/Result/ResultFont.png"));
	}

	inline VOID Init()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		ResultData resultData;
		rSceneManager.GetResultData(&resultData);

		m_pResultDataScore = new ResultDataScore(resultData.m_score, m_CASE_COLOR);												//テスト用

		m_pResultDataStage = new ResultDataStage(NULL, NULL, m_CASE_COLOR);														//未対応

		m_pResultDataClearStar = new ResultDataClearStar(resultData.m_clearStarsNum, resultData.m_clearStarMax, m_CASE_COLOR);	//テスト用
	}

	inline VOID Update() 
	{
		if (!m_rGameLib.KeyboardAnyKeyIsPressed()) return;

		if (!m_pResultDataScore->StagingIsEnd())
		{
			m_pResultDataScore->SkipStage();

			return;
		}

		if (!m_pResultDataClearStar->StagingIsEnd())
		{
			m_pResultDataClearStar->SkipStage();

			return;
		}
	}

	inline VOID Render()
	{
		m_pResultDataScore->Render();
		m_pResultDataStage->Render();

		m_pResultDataClearStar->Render();

		const INT STAGING_GAP_FRAME = 30;
		if (m_pResultDataScore->StagingIsEnd()) ++m_stagingGapFrameCount;
		if (m_stagingGapFrameCount < STAGING_GAP_FRAME) return;

		m_stagingGapFrameCount = STAGING_GAP_FRAME;

		m_pResultDataClearStar->StartStaging();
	}

	inline BOOL StagingIsEnd() const
	{
		return m_pResultDataClearStar->StagingIsEnd();
	}

private:
	INT m_stagingGapFrameCount = 0;

	const DWORD m_CASE_COLOR = 0x66808080;

	ResultDataScore* m_pResultDataScore = nullptr;

	ResultDataStage* m_pResultDataStage = nullptr;

	ResultDataClearStar* m_pResultDataClearStar = nullptr;
};

class ResultSceneResultFont :public Obj
{
public:
	ResultSceneResultFont(BOOL isFailed) :Obj(OT_TRANSPARENCY, 0.8f), m_IS_FAILED(isFailed)
	{
		Init();
	}

	~ResultSceneResultFont()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.AddSoundFile(_T("Sounds/Result/clear.mp3"), _T("Clear"));
		m_rGameLib.AddSoundFile(_T("Sounds/Result/failed.mp3"), _T("Failed"));
		m_rGameLib.CreateTex(_T("ResultFont"), _T("2DTextures/Result/ResultFont.png"));
	}

	inline VOID Update() {};

	VOID Render();

private:
	inline VOID DarkenFontAround()
	{	
		ObjData blackMaskData;
		blackMaskData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };
		blackMaskData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex blackMask[4];
		m_rGameLib.CreateRect(blackMask, blackMaskData);

		INT alpha = static_cast<INT>(230 * static_cast<FLOAT>(m_alphaCount) / m_ADDITIONAL_ALPHA_FRAME);
		m_rGameLib.SetTopBottomARGB(blackMask, 
									D3DCOLOR_ARGB(alpha, 0, 0, 0), 
									D3DCOLOR_ARGB(static_cast<BYTE>(alpha * 0.7f), 0, 0, 0));

		m_rGameLib.Render(blackMask, nullptr);
	}

	const BOOL m_IS_FAILED;

	const INT m_ADDITIONAL_ALPHA_FRAME = 120;
	INT m_alphaCount = 0;
};

class ResultSceneContinue :public Obj
{
public:
	ResultSceneContinue() :Obj(OT_TRANSPARENCY, 0.7f)
	{
		Init();
	}

	~ResultSceneContinue()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_rGameLib.CreateTex(_T("ContinueFrame"), _T("2DTextures/Result/Result_ContinueFrame.png"));
		m_rGameLib.CreateTex(_T("YesNo"), _T("2DTextures/Result/YesNo.png"));
		m_rGameLib.CreateTex(_T("Target"), _T("2DTextures/Result/Target.png"));
	}

	VOID Update();

	VOID Render();

private:
	BOOL m_isSelectedYes = TRUE;

	inline VOID RenderFrame() const
	{
		ObjData ContinueFrameData;
		ContinueFrameData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };
		ContinueFrameData.m_halfScale	= { m_WND_SIZE.m_x * 0.28f, m_WND_SIZE.m_y * 0.38f, 0.0f };	//! 現物合わせ

		CustomVertex ContinueFrame[4];
		m_rGameLib.CreateRect(ContinueFrame, ContinueFrameData);

		m_rGameLib.Render(ContinueFrame, m_rGameLib.GetTex(_T("ContinueFrame")));
	}

	VOID RenderTexts() const;

	inline VOID RenderTarget()
	{
		ObjData targetData;

		const FLOAT CENTER_Y_WND_MULTI_BASE = 0.523f;
		FLOAT centerYWndMulti = (m_isSelectedYes) ? CENTER_Y_WND_MULTI_BASE : CENTER_Y_WND_MULTI_BASE + 0.158f;
		targetData.m_center = { m_WND_SIZE.m_x * 0.4f, m_WND_SIZE.m_y * centerYWndMulti, 0.0f }; //! 現物合わせ

		const FLOAT TARGET_HALF_SCALE = m_WND_SIZE.m_x * 0.02f;
		targetData.m_halfScale = { TARGET_HALF_SCALE, TARGET_HALF_SCALE, 0.0f };

		CustomVertex target[4];
		m_rGameLib.CreateRect(target, targetData);

		m_rGameLib.Render(target, m_rGameLib.GetTex(_T("Target")));
	}
};

class ResultSceneResult :public Obj
{
public:
	ResultSceneResult() :Obj(OT_TRANSPARENCY, 0.8f)
	{
		Init();
	}

	~ResultSceneResult()
	{
		delete m_pResultSceneContinue;
		delete m_pResultSceneResultFont;
		delete m_pResultSceneResultData;
		m_rGameLib.ReleaseTex();

		if ((SceneManager::GetInstance()).GetIsTutorial())
		{
			SceneManager::GetInstance().SetIsTutorial(FALSE);

			return;
		}

		DataSaver& rDataSaver = DataSaver::GetInstance();
		rDataSaver.Save();
	}

	inline VOID Init()
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		ResultData resultData;
		rSceneManager.GetResultData(&resultData);

		m_isFailed = resultData.m_isFailed;

		m_pResultSceneResultData = new ResultSceneResultData();

		m_pResultSceneResultFont = new ResultSceneResultFont(m_isFailed);

		m_pResultSceneContinue = new ResultSceneContinue();

		m_rGameLib.CreateTex(_T("ResultFont"), _T("2DTextures/Result/ResultFont.png"));
	}

	VOID Update();

	inline VOID Render()
	{
		m_pResultSceneResultData->Render();

		if (!m_pResultSceneResultData->StagingIsEnd()) return;

		++m_stagingGapFrameCount;

		if (m_stagingGapFrameCount < m_STAGING_GAP_FRAME) return;
			
		m_stagingGapFrameCount = m_STAGING_GAP_FRAME;

		m_pResultSceneResultFont->Render();

		if (m_shouldShowContinue && m_isFailed && !SceneManager::GetInstance().GetIsTutorial())
		{
			m_pResultSceneContinue->Render();
		}
	}

private:
	BOOL m_isFailed = FALSE;

	const INT m_STAGING_GAP_FRAME = 150;
	INT m_stagingGapFrameCount = 0;

	BOOL m_shouldShowContinue = FALSE;

	ResultSceneResultData* m_pResultSceneResultData = nullptr;

	ResultSceneResultFont* m_pResultSceneResultFont = nullptr;

	ResultSceneContinue* m_pResultSceneContinue = nullptr;
};

#endif //! RESULT_SCENE_OBJ_H
