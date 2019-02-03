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

	RenderZodiacs();

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
		
		RenderSelectIconStaging(i, &stageIconDatas[i].m_objData);

		if (m_deg != DEG_GAP && m_deg != -DEG_GAP) continue;
		m_selectingStage -= static_cast<INT>(m_deg / DEG_GAP);												//! 角度が60を超えるとm_selectingStageを次の値に変える
		m_deg = 0.0f;

		if (m_selectingStage < 0) m_selectingStage = m_STAGE_ICONS_MAX + m_selectingStage;					//! m_selectingStageがマイナスに行ったときの対処
		m_selectingStage %= m_STAGE_ICONS_MAX;
	}

	RenderBlackHole();

	m_rGameLib.DefaultBlendMode();

	RenderStageName();

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

VOID StageSelectSceneStageList::RenderSelectIconStaging(INT loopItr, ObjData* pObjData)
{
	if (loopItr == m_selectingStage && !m_blackHoleIsSelected && m_deg == 0.0f)
	{
		CustomVertex vertices[4];

		m_rGameLib.AddtionBlendMode();

		pObjData->m_aRGB = 0xFFFFFF00;
		m_rGameLib.CreateRect(vertices, *pObjData);

		static INT selectIconFlashFrameCnt = 0;
		m_rGameLib.FlashRect(vertices, &selectIconFlashFrameCnt, 120, 190, 70);

		m_rGameLib.Render(vertices, m_rGameLib.GetTex(_T("Icons")));

		m_rGameLib.DefaultBlendMode();
	}
}

VOID StageSelectSceneStageList::RenderBlackHole()
{
	static ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.4f, m_Z };

	const FLOAT BLACK_HOLE_RADIUSU_MAX = 540.0f;

	const INT DECIDE_STAGE_FRAMES = 60;

	auto StageBlackHole = [&, this]()
	{
		if (!m_blackHoleIsSelected)
		{
			if (m_lengthMulti == 0 && !m_isDecided) m_blackHoleAlpha += (255 / 60);

			m_blackHoleAlpha += static_cast<INT>(m_lengthMulti * (255 / 60));

			m_blackHoleRadius -= BLACK_HOLE_RADIUSU_MAX / DECIDE_STAGE_FRAMES;

			return;
		}

		m_blackHoleRadius += BLACK_HOLE_RADIUSU_MAX / DECIDE_STAGE_FRAMES;
	};

	StageBlackHole();

	m_blackHoleRadius = min(max(m_blackHoleRadius, m_BLACK_HOLE_RADIUSU_MIN), BLACK_HOLE_RADIUSU_MAX);

	m_blackHoleStagingEnds = FALSE;

	if (m_blackHoleRadius == BLACK_HOLE_RADIUSU_MAX) m_blackHoleStagingEnds = TRUE;

	data.m_halfScale = { m_blackHoleRadius, m_blackHoleRadius, 0.0f };

	m_blackHoleAlpha = min(max(m_blackHoleAlpha, 0), 255);
	data.m_aRGB = D3DCOLOR_ARGB(m_blackHoleAlpha, 255, 255, 255);

	data.m_deg.z += 0.25f;

	CustomVertex blackHole[4];
	m_rGameLib.CreateRect(blackHole, data);
	m_rGameLib.Render(blackHole, m_rGameLib.GetTex(_T("BlackHoleIcon")));
}

VOID StageSelectSceneStageList::RenderStageName()
{
	TString stageString;
	INT stageCharsNum = 0;

	GetStageStringAndCharsNum(&stageString, &stageCharsNum);

	Text stageText(stageString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 22, 33 };
	txtFormat.m_topLeft = { 640.0f - 2.0f * txtFormat.m_charHalfScale.m_x * stageCharsNum * 0.5f, 580.0f };

	stageText.Write(txtFormat);
}

VOID StageSelectSceneStageList::GetStageStringAndCharsNum(TString* pTString, INT* pCharsNum)
{
	if (m_blackHoleIsSelected)
	{
		pTString->WriteInAll(_T("BLACK HOLE"));
		*pCharsNum = 10;

		return;
	}

	switch (m_selectingStage)
	{
	case STAGE_TAURUS:

		pTString->WriteInAll(_T("TAURUS"));
		*pCharsNum = 6;

		break;

	case STAGE_LIBRA:

		pTString->WriteInAll(_T("LIBRA"));
		*pCharsNum = 5;

		break;

	case STAGE_VIRGO:

		pTString->WriteInAll(_T("VIRGO"));
		*pCharsNum = 5;

		break;

	case STAGE_ARIES:

		pTString->WriteInAll(_T("ARIES"));
		*pCharsNum = 5;

		break;

	case STAGE_GEMINI:

		pTString->WriteInAll(_T("GEMINI"));
		*pCharsNum = 6;

		break;

	case STAGE_SCORPIUS:

		pTString->WriteInAll(_T("SCORPIUS"));
		*pCharsNum = 8;

		break;

	case STAGE_PISCORPIUS:

		pTString->WriteInAll(_T("PISCORPIUS"));
		*pCharsNum = 10;

		break;

	case STAGE_LEO:

		pTString->WriteInAll(_T("LEO"));
		*pCharsNum = 3;

		break;

	case STAGE_CAPRICORNUS:

		pTString->WriteInAll(_T("CAPRICORNUS"));
		*pCharsNum = 11;

		break;

	case STAGE_AQUARIUS:

		pTString->WriteInAll(_T("AQUARIUS"));
		*pCharsNum = 8;

		break;

	case STAGE_SAGITTARIUS:

		pTString->WriteInAll(_T("SAGITTARIUS"));
		*pCharsNum = 11;

		break;

	case STAGE_CANCER:

		pTString->WriteInAll(_T("CANCER"));
		*pCharsNum = 6;

		break;

	default:

		break;
	}
}

VOID StageSelectSceneStageList::RenderZodiacs()
{
	if (m_blackHoleIsSelected || m_deg != 0.0f)
	{
		return;
	}
	
	ObjData obj;
	obj.m_center	= { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.65f, m_Z };
	obj.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	const D3DXVECTOR2 ILLUST_SCALE = { 1280.0f,720.0f };
	const D3DXVECTOR2 TEX_SCALE	 = { 8192.0f,2048.0f };

	const INT ILLUST_ROWS_MAX = 6;

	obj.m_texUV =
	{
		ILLUST_SCALE.x * (m_selectingStage % ILLUST_ROWS_MAX)	  / TEX_SCALE.x,
		ILLUST_SCALE.y * (m_selectingStage / ILLUST_ROWS_MAX)	  / TEX_SCALE.y,
		ILLUST_SCALE.x * (m_selectingStage % ILLUST_ROWS_MAX + 1) / TEX_SCALE.x,
		ILLUST_SCALE.y * (m_selectingStage / ILLUST_ROWS_MAX + 1) / TEX_SCALE.y
	};

	obj.m_aRGB = 0x99FFFFFF;

	m_rGameLib.CreateAndRenderRect(obj, m_rGameLib.GetTex(_T("Zodiacs")));
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
