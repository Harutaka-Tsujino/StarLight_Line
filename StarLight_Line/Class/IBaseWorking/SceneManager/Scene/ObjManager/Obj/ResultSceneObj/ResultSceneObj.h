#ifndef RESULT_SCENE_OBJ_H
#define RESULT_SCENE_OBJ_H

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"

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
		m_rGameLib.SetCameraTransform();

		ObjData data;
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
	}
};

class ResultDataScore :public Obj
{
public:
	ResultDataScore(INT score) :Obj(OT_TRANSPARENCY, 0.9f), m_SCORE(score)
	{
		Init();
	}

	~ResultDataScore()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init()
	{
		m_digitsNum = static_cast<INT>(log10(m_SCORE) + 1);

		m_digitScoresVec.resize(m_digitsNum);

		m_rGameLib.CreateTex(_T("Nums"), _T("2DTextures/Result/Nums.png"));
	}

	inline VOID Update() {};

	VOID Render();

	inline BOOL StagingIsEnd() const
	{
		return m_stagingIsEnd;
	}

	inline VOID SkipStage()
	{
		m_increaseStageCount = m_INCREASE_STAGE_MAX;
	}

private:
	struct DigitScore
	{
	public:
		INT m_num = 0;

		ObjData m_objData;

		CustomVertex m_customVertices[4];
	};

	const INT m_SCORE;
	INT m_digitsNum = NULL;
	std::vector<DigitScore> m_digitScoresVec;

	const INT m_INCREASE_STAGE_MAX = 150;
	INT m_increaseStageCount = -70;	//! 現物合わせ

	BOOL m_stagingIsEnd = FALSE;
};

class ResultDataStage :public Obj
{
public:
	ResultDataStage(INT stage, INT difficulty) :Obj(OT_TRANSPARENCY, 0.9f)
	{
		Init();
	}

	~ResultDataStage()
	{
		m_rGameLib.ReleaseTex();
	}

	inline VOID Init() const
	{
		//m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/SaveData/SaveData_Back.png"));
	}

	inline VOID Update() {};

	inline VOID Render()
	{
		ObjData backData;
		backData.m_center		= { m_WND_SIZE.m_x * 0.31f, m_WND_SIZE.m_y * 0.69f, m_Z };	//! 現物合わせ
		backData.m_halfScale	= { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.2f, 0.0f };	//! 現物合わせ

		backData.m_aRGB = 0x66808080;														//! 現物合わせ

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, backData);

		m_rGameLib.Render(back, nullptr);

		/*ObjData stageData;
		stageData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		stageData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex stage[4];
		m_rGameLib.CreateRect(stage, stageData);
		m_rGameLib.Render(stage, m_rGameLib.GetTex(_T("Back")));

		ObjData difficultyData;
		difficultyData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
		difficultyData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

		CustomVertex difficulty[4];
		m_rGameLib.CreateRect(difficulty, difficultyData);
		m_rGameLib.Render(difficulty, m_rGameLib.GetTex(_T("Back")));*/
	}
};

class ResultDataClearStar :public Obj
{
public:
	ResultDataClearStar(INT clearStarsNum, INT clearStarsMax) :Obj(OT_TRANSPARENCY, 0.9f),
		m_CLEAR_STARS_NUM(clearStarsNum), m_CLEAR_STARS_MAX(clearStarsMax)
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
		m_stagingCount = m_StageCountMax;
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

	const INT m_CLEAR_STARS_MAX = NULL;
	const INT m_CLEAR_STARS_NUM = NULL;

	std::vector<Stars> m_starsVec;

	INT m_StageCountMax = NULL;
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
		m_pResultDataScore = new ResultDataScore(123571113);	//テスト用

		m_pResultDataStage = new ResultDataStage(NULL, NULL);	//未対応

		m_pResultDataClearStar = new ResultDataClearStar(7, 8);	//テスト用
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

		const INT STAGING_GAP_FRAME = 30;
		if (m_pResultDataScore->StagingIsEnd())
		{
			m_stagingGapFrameCount = (m_stagingGapFrameCount >= STAGING_GAP_FRAME) ? STAGING_GAP_FRAME : ++m_stagingGapFrameCount;
		}

		if(m_stagingGapFrameCount >= STAGING_GAP_FRAME)	m_pResultDataClearStar->StartStaging();

		m_pResultDataClearStar->Render();
	}

	inline BOOL StagingIsEnd() const
	{
		return m_pResultDataClearStar->StagingIsEnd();
	}

private:
	INT m_stagingGapFrameCount = 0;

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
		m_rGameLib.CreateTex(_T("ResultFont"), _T("2DTextures/Result/ResultFont.png"));
	}

	inline VOID Update() {};

	VOID Render();

private:
	const BOOL m_IS_FAILED;

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

	inline VOID Update() 
	{
		if (UpKeyIsPressed() || DownKeyIsPressed()) m_isSelectedYes = !m_isSelectedYes;

		if (!m_rGameLib.KeyboardIsPressed(DIK_RETURN)) return;

		SceneManager& rSceneManager = SceneManager::GetInstance();
	
		rSceneManager.SetNextScene(SK_STAGE_SELECT);
	}

	VOID Render();

private:
	BOOL m_isSelectedYes = TRUE;
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
	}

	inline VOID Init()
	{
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

		m_stagingGapFrameCount = (m_stagingGapFrameCount >= m_STAGING_GAP_FRAME) ? m_STAGING_GAP_FRAME : ++m_stagingGapFrameCount;
		if (!(m_stagingGapFrameCount >= m_STAGING_GAP_FRAME)) return;
			
		m_pResultSceneResultFont->Render();

		if(m_countUntilShowContinue) m_pResultSceneContinue->Render();

		//m_countUntilShowContinue = (m_countUntilShowContinue >= m_CONTINUE_FLAME_LATENT_FRAME) ? m_CONTINUE_FLAME_LATENT_FRAME : ++m_countUntilShowContinue;
		//if (m_countUntilShowContinue >= m_CONTINUE_FLAME_LATENT_FRAME) m_pResultSceneContinue->Render();
	}

private:
	BOOL m_isFailed = FALSE;

	const INT m_STAGING_GAP_FRAME = 60;
	INT m_stagingGapFrameCount = 0;

	const INT m_CONTINUE_FLAME_LATENT_FRAME = 150;
	INT m_countUntilShowContinue = 0;

	ResultSceneResultData* m_pResultSceneResultData = nullptr;

	ResultSceneResultFont* m_pResultSceneResultFont = nullptr;

	ResultSceneContinue* m_pResultSceneContinue = nullptr;
};

#endif //! RESULT_SCENE_OBJ_H
