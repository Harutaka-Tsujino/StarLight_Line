/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#include "StageSelectSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../../../Enum/SCENE_KIND.h"
#include "../../../../SceneManager.h"

const FLOAT StageSelectSceneStageList::m_ICONS_CIRCLE_RADIUS_MAX = 230.0f;

const FLOAT StageSelectSceneStageList::m_BLACK_HOLE_RADIUSU_MIN = 100.0f;

VOID StageSelectSceneStageList::Update()
{
	if (m_isDecided) return;

	if (UpKeyIsPressed() &&
		!m_backIsSelected &&
		!m_blackHoleIsSelected)
	{
		m_blackHoleIsSelected = TRUE;

		m_lengthMulti = -1.0f;
	}

	if (UpKeyIsPressed() &&
		m_backIsSelected &&
		!m_blackHoleIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = FALSE;
	}

	if (DownKeyIsPressed() &&
		!m_backIsSelected &&
		m_blackHoleIsSelected)
	{
		m_blackHoleIsSelected = FALSE;

		m_lengthMulti = 1.0f;
	}

	SceneManager& rSceneManager = SceneManager::GetInstance();

	if (ReturnKeyIsPressed() &&
		m_backIsSelected &&
		!m_blackHoleIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		rSceneManager.SetNextScene(SK_TITLE);

		return;
	}

	if (ReturnKeyIsPressed() &&
		!m_backIsSelected &&
		m_blackHoleIsSelected &&
		m_blackHoleStagingEnds)
	{
		m_lengthMulti = 0.0f;

		m_isDecided = TRUE;
	}

	if (m_backIsSelected || m_blackHoleIsSelected) return;

	if (ReturnKeyIsPressed()	&&
		m_deg == 0.0f			&&
		m_lengthMulti == 0.0f)
	{
		m_lengthMulti = -1.0f;

		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		return;
	}

	if (m_lengthMulti != 0.0f) return;

	if (DownKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = TRUE;

		return;
	}

	const FLOAT ROTATE_SPEED = 1.5f;

	if (m_deg > 0.0f) m_deg += ROTATE_SPEED;		//! すでに回転されていたらさらに回転させる
	if (m_deg < 0.0f) m_deg += -ROTATE_SPEED;

	if (m_deg != 0) return;

	if (RightKeyIsPressed())
	{
		m_deg = ROTATE_SPEED;	//! 回転の起動

		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		return;
	}

	if (LeftKeyIsPressed())
	{
		m_deg = -ROTATE_SPEED;

		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		return;
	}
}

VOID StageSelectSceneStageList::Render()
{
	if (m_isDecided) m_rGameLib.AddtionBlendMode();

	const FLOAT DEG_GAP = -360.0f / m_STAGE_ICONS_MAX;										//! アイコンとアイコンの角度

	const INT DECIDE_STAGE_FRAMES = 60;
	m_iconsCircleRadius += m_lengthMulti * m_ICONS_CIRCLE_RADIUS_MAX / DECIDE_STAGE_FRAMES;		//! DECIDE_STAGE_FRAMESで半径が最大値に達する
	m_iconsCircleRadius = min(max(m_iconsCircleRadius, 0), m_ICONS_CIRCLE_RADIUS_MAX);

	if (m_iconsCircleRadius == m_ICONS_CIRCLE_RADIUS_MAX ||
		!m_iconsCircleRadius &&
		!m_blackHoleIsSelected)
	{
		m_lengthMulti = 0.0f;

		m_isDecided = !m_iconsCircleRadius;
	}

	BYTE alpha = NULL;

	const RectSize ILLUST_SIZE = { 2048, 1024 };
	const FLOAT ICON_ILLUST_SIZE = 300.0f;
	const INT ICONS_ILLUST_ROWS_MAX = 6;

	StageIconData stageIconDatas[m_STAGE_ICONS_MAX];
	CustomVertex stageIcon[4];

	for (int i = 0; i < m_STAGE_ICONS_MAX; ++i)
	{
		if ((i != m_selectingStage || m_blackHoleIsSelected) && m_isDecided ) continue;;

		RotateIconsCenter(stageIconDatas, i, DEG_GAP, m_iconsCircleRadius);
		
		SetHalfScaleByRadius(stageIconDatas, i, m_iconsCircleRadius, m_ICONS_CIRCLE_RADIUS_MAX);

		if (i != m_selectingStage || m_blackHoleIsSelected)
		{
			alpha = static_cast<BYTE>(255 * (m_iconsCircleRadius / m_ICONS_CIRCLE_RADIUS_MAX));

			stageIconDatas[i].m_objData.m_aRGB = D3DCOLOR_ARGB(alpha, 255, 255, 255);
		}

		stageIconDatas[i].m_objData.m_texUV =
		{
			ICON_ILLUST_SIZE * (i % ICONS_ILLUST_ROWS_MAX)		/ ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / ICONS_ILLUST_ROWS_MAX)		/ ILLUST_SIZE.m_y,
			ICON_ILLUST_SIZE * (i % ICONS_ILLUST_ROWS_MAX + 1)	/ ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / ICONS_ILLUST_ROWS_MAX + 1)	/ ILLUST_SIZE.m_y
		};

		m_rGameLib.CreateRect(stageIcon, stageIconDatas[i].m_objData);

		m_rGameLib.Render(stageIcon, m_rGameLib.GetTex(_T("Icons")));

		if (m_deg != DEG_GAP && m_deg != -DEG_GAP) continue;
		m_selectingStage -= static_cast<INT>(m_deg / DEG_GAP);												//! 角度が60を超えるとm_selectingStageを次の値に変える
		m_deg = 0.0f;

		if (m_selectingStage < 0) m_selectingStage = m_STAGE_ICONS_MAX + m_selectingStage;					//! m_selectingStageがマイナスに行ったときの対処
		m_selectingStage %= m_STAGE_ICONS_MAX;
	}

	RenderBlackHole();

	m_rGameLib.DefaultBlendMode();

	if (m_iconsCircleRadius != 0.0f) RenderBackButton(m_iconsCircleRadius);
}

VOID StageSelectSceneStageList::RenderBackButton(FLOAT iconsCircleRadius) const
{
	ObjData backButtonData;
	backButtonData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.96f, m_Z };	//! 現物合わせ
	backButtonData.m_halfScale	= { m_WND_SIZE.m_x * 0.05f, m_WND_SIZE.m_y * 0.04f, 0.0f };	//! 現物合わせ

	backButtonData.m_aRGB = D3DCOLOR_ARGB(
		static_cast<UCHAR>(iconsCircleRadius),
		255, 255, 255);

	backButtonData.m_texUV =
	{
		-(m_backIsSelected - 1) / 2.0f,
		0.0f,
		(!m_backIsSelected + 1.0f) / 2.0f,
		1.0f
	};

	CustomVertex backButton[4];
	m_rGameLib.CreateRect(backButton, backButtonData);

	m_rGameLib.Render(backButton, m_rGameLib.GetTex(_T("BackButton")));
}

VOID StageSelectSceneLevelSelecter::Update()
{
	m_shouldActivateStageSelect = FALSE;

	if (m_alpha < 255) return;

	if (UpKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = TRUE;

		return;
	}

	if (DownKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = FALSE;

		return;
	}

	if (ReturnKeyIsPressed() && m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		m_shouldActivateStageSelect = TRUE;

		return;
	}

	if (m_backIsSelected) return;

	if (RightKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		if (m_blackHoleIsSelected)
		{
			m_level = (m_level < SLK_HARD) ? m_level + 2 : SLK_HARD;

			return;
		}

		m_level = (m_level < SLK_HARD) ? ++m_level : SLK_HARD;

		return;
	}

	if (LeftKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		if (m_blackHoleIsSelected)
		{
			m_level = (m_level > SLK_EASY) ? m_level - 2 : SLK_EASY;

			return;
		}

		m_level = (m_level > SLK_EASY) ? --m_level : SLK_EASY;

		return;
	}

	if (ReturnKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.SetNextScene(SK_GAME);
	}
}

VOID StageSelectSceneLevelSelecter::Render()
{
	m_alpha += 10 * ((m_rStageIsDecided) ? 1 : -1);
	m_alpha = min(max(m_alpha, 0), 255);

	if (!m_alpha)
	{
		m_backIsSelected = FALSE;

		return;
	}

	RenderBack();

	RenderTarget();

	RenderBackButton();
}

VOID StageSelectSceneLevelSelecter::RenderBack() const
{
	ObjData backData;
	backData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	backData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	backData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, backData);
	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("LevelBack")));
}

VOID StageSelectSceneLevelSelecter::RenderTarget() const
{
	ObjData levelData;

	for (INT i = 0; i < SLK_EXTREME; ++i)
	{
		if (m_blackHoleIsSelected && i == SLK_NORMAL) continue;

		levelData.m_center	  = { m_WND_SIZE.m_x * 0.262f + m_WND_SIZE.m_x * 0.238f * i, m_WND_SIZE.m_y * 0.727f, m_Z };
		levelData.m_halfScale = { m_WND_SIZE.m_x * 0.06f, m_WND_SIZE.m_y * 0.034f, 0.0f };

		levelData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

		INT levelNum = i;
		if (m_blackHoleIsSelected) levelNum = (levelNum == SLK_EASY) ? SLK_HARD : SLK_EXTREME;

		const D3DXVECTOR2 ILLUST_SCALE = { 1024.0f, 64.0f };
		const D3DXVECTOR2 LEVEL_SCALE  = { 150.0f,50.0f };

		levelData.m_texUV =
		{
			LEVEL_SCALE.x * levelNum / ILLUST_SCALE.x,
			0.0f,
			LEVEL_SCALE.x * (levelNum + 1) / ILLUST_SCALE.x,
			LEVEL_SCALE.y / ILLUST_SCALE.y
		};

		CustomVertex level[4];
		m_rGameLib.CreateRect(level, levelData);

		m_rGameLib.Render(level, m_rGameLib.GetTex(_T("LevelTexts")));

		if (i != m_level || m_backIsSelected) continue;

		levelData.m_halfScale.x *= 1.03f;
		levelData.m_halfScale.y *= 1.09f;

		levelData.m_texUV.m_startTU = LEVEL_SCALE.x * (SLK_EXTREME + 1) / ILLUST_SCALE.x;
		levelData.m_texUV.m_endTU	= levelData.m_texUV.m_startTU + LEVEL_SCALE.x / ILLUST_SCALE.x;

		m_rGameLib.CreateRect(level, levelData);

		m_rGameLib.AddtionBlendMode();
		m_rGameLib.Render(level, m_rGameLib.GetTex(_T("LevelTexts")));
		m_rGameLib.DefaultBlendMode();
	}
}

VOID StageSelectSceneLevelSelecter::RenderBackButton() const
{
	ObjData backButtonData;
	backButtonData.m_center		= { m_WND_SIZE.m_x * 0.14f, m_WND_SIZE.m_y * 0.17f, m_Z };										//! 現物合わせ
	backButtonData.m_halfScale	= { m_WND_SIZE.m_y * 0.05f, m_WND_SIZE.m_y * 0.05f, 0.0f };										//! 現物合わせ

	backButtonData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

	const D3DXVECTOR2 ILLUST_SCALE		= { 300.0f, 150.0f };
	const D3DXVECTOR2 BACK_BUTTON_SCALE = { 150.0f, 150.0f };

	backButtonData.m_texUV =
	{
		BACK_BUTTON_SCALE.x * ((m_backIsSelected) ? 1 : 0) / ILLUST_SCALE.x,
		0.0f,
		BACK_BUTTON_SCALE.x * ((m_backIsSelected) ? 2 : 1) / ILLUST_SCALE.x,
		BACK_BUTTON_SCALE.y / ILLUST_SCALE.y
	};

	CustomVertex backButton[4];
	m_rGameLib.CreateRect(backButton, backButtonData);

	m_rGameLib.Render(backButton, m_rGameLib.GetTex(_T("LevelBackButton")));
}
