﻿#include "StageSelect2PObj.h"

VOID StageSelectTwoPlayerSceneStageList::Update()
{
	if (m_isDecided) return;

	if ((m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::UP_DIRECTION) ||
		 m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::UP_DIRECTION))&&
		 m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = FALSE;
	}

	if ((m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::DOWN_DIRECTION) ||
		 m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::DOWN_DIRECTION))&&
		!m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_lengthMulti = 1.0f;

		m_backIsSelected = TRUE;
	}

	SceneManager& rSceneManager = SceneManager::GetInstance();

	if ((m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON) ||
		 m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON)) &&
		 m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		rSceneManager.SetNextScene(SK_TITLE);

		return;
	}

	if (m_backIsSelected) return;

	if ((m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON) ||
		 m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON)) &&
		 m_deg == 0.0f			&&
		 m_lengthMulti == 0.0f)
	{
		m_lengthMulti = -1.0f;

		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		return;
	}

	if (m_lengthMulti != 0.0f) return;

	const FLOAT ROTATE_SPEED = 1.5f;

	if (m_deg > 0.0f) m_deg += ROTATE_SPEED;		//! すでに回転されていたらさらに回転させる
	if (m_deg < 0.0f) m_deg += -ROTATE_SPEED;

	if (m_deg != 0) return;

	if (m_rGameLib.HoldJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_DIRECTION) ||
		m_rGameLib.HoldJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::RIGHT_DIRECTION))
	{
		m_deg = ROTATE_SPEED;	//! 回転の起動

		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		return;
	}
		
	if (m_rGameLib.HoldJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::LEFT_DIRECTION) ||
		m_rGameLib.HoldJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::LEFT_DIRECTION))
	{
		m_deg = -ROTATE_SPEED;

		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		return;
	}
}

VOID StageSelectTwoPlayerSceneStageList::Render()
{
	if (m_isDecided) m_rGameLib.AddtionBlendMode();

	const FLOAT ICONS_CIRCLE_RADIUS_MAX = 230.0f;											//! 複数のアイコンがなす円の半径の最大値
	static FLOAT iconsCircleRadius = ICONS_CIRCLE_RADIUS_MAX;								//! 複数のアイコンがなす円の半径

	const FLOAT DEG_GAP = -360.0f / m_STAGE_ICONS_MAX;										//! アイコンとアイコンの角度

	const INT DECIDE_STAGE_FRAMES = 60;
	iconsCircleRadius += m_lengthMulti * ICONS_CIRCLE_RADIUS_MAX / DECIDE_STAGE_FRAMES;		//! DECIDE_STAGE_FRAMESで半径が最大値に達する
	iconsCircleRadius = min(max(iconsCircleRadius, 0), ICONS_CIRCLE_RADIUS_MAX);

	if (iconsCircleRadius == ICONS_CIRCLE_RADIUS_MAX ||
		!iconsCircleRadius)
	{
		m_lengthMulti = 0.0f;

		m_isDecided = !iconsCircleRadius;
	}

	RenderZodiacs();

	BYTE alpha = NULL;

	const RectSize ILLUST_SIZE = { 2048, 1024 };
	const FLOAT ICON_ILLUST_SIZE = 300.0f;
	const INT ICONS_ILLUST_ROWS_MAX = 6;

	StageIconData stageIconDatas[m_STAGE_ICONS_MAX];
	CustomVertex stageIcon[4];

	for (int i = 0; i < m_STAGE_ICONS_MAX; ++i)
	{
		if ((i != m_selectingStage) && m_isDecided) continue;;

		RotateIconsCenter(stageIconDatas, i, DEG_GAP, iconsCircleRadius);

		SetHalfScaleByRadius(stageIconDatas, i, iconsCircleRadius, ICONS_CIRCLE_RADIUS_MAX);

		if (i != m_selectingStage)
		{
			alpha = static_cast<BYTE>(255 * (iconsCircleRadius / ICONS_CIRCLE_RADIUS_MAX));

			stageIconDatas[i].m_objData.m_aRGB = D3DCOLOR_ARGB(alpha, 255, 255, 255);
		}

		stageIconDatas[i].m_objData.m_texUV =
		{
			ICON_ILLUST_SIZE * (i % ICONS_ILLUST_ROWS_MAX) / ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / ICONS_ILLUST_ROWS_MAX) / ILLUST_SIZE.m_y,
			ICON_ILLUST_SIZE * (i % ICONS_ILLUST_ROWS_MAX + 1) / ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / ICONS_ILLUST_ROWS_MAX + 1) / ILLUST_SIZE.m_y
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

	m_rGameLib.DefaultBlendMode();

	RenderStageName();

	if (iconsCircleRadius != 0.0f) RenderBackButton(iconsCircleRadius);
}

VOID StageSelectTwoPlayerSceneStageList::RenderZodiacs()
{
	if (m_deg != 0.0f)
	{
		return;
	}

	ObjData obj;
	obj.m_center = { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.65f, m_Z };
	obj.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	const D3DXVECTOR2 ILLUST_SCALE = { 1280.0f,720.0f };
	const D3DXVECTOR2 TEX_SCALE = { 8192.0f,2048.0f };

	const INT ILLUST_ROWS_MAX = 6;

	obj.m_texUV =
	{
		ILLUST_SCALE.x * (m_selectingStage % ILLUST_ROWS_MAX) / TEX_SCALE.x,
		ILLUST_SCALE.y * (m_selectingStage / ILLUST_ROWS_MAX) / TEX_SCALE.y,
		ILLUST_SCALE.x * (m_selectingStage % ILLUST_ROWS_MAX + 1) / TEX_SCALE.x,
		ILLUST_SCALE.y * (m_selectingStage / ILLUST_ROWS_MAX + 1) / TEX_SCALE.y
	};

	obj.m_aRGB = 0x99FFFFFF;

	m_rGameLib.CreateAndRenderRect(obj, m_rGameLib.GetTex(_T("Zodiacs")));
}

VOID StageSelectTwoPlayerSceneStageList::RenderBackButton(FLOAT iconsCircleRadius) const
{
	ObjData backButtonData;
	backButtonData.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.96f, m_Z };	//! 現物合わせ
	backButtonData.m_halfScale = { m_WND_SIZE.m_x * 0.05f, m_WND_SIZE.m_y * 0.04f, 0.0f };	//! 現物合わせ

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

VOID StageSelectTwoPlayerSceneStageList::RenderStageName()
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

VOID StageSelectTwoPlayerSceneStageList::RenderSelectIconStaging(INT loopItr, ObjData* pObjData)
{
	if (loopItr == m_selectingStage)
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

VOID StageSelectTwoPlayerSceneStageList::GetStageStringAndCharsNum(TString* pTString, INT* pCharsNum)
{
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

VOID StageSelectTwoPlayerSceneLevelSelecter::Update()
{
	m_shouldActivateStageSelect = FALSE;

	if (m_alpha < 255) return;

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::UP_DIRECTION) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::UP_DIRECTION))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = TRUE;

		return;
	}

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::DOWN_DIRECTION) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::DOWN_DIRECTION))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = FALSE;

		return;
	}

	if ((m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON) ||
		m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON))   && 
		m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		m_shouldActivateStageSelect = TRUE;

		return;
	}

	if (m_backIsSelected) return;

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_DIRECTION) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER,Joycon::RIGHT_DIRECTION))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_level = (m_level < SLK_HARD) ? ++m_level : SLK_HARD;

		return;
	}

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::LEFT_DIRECTION) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER,Joycon::LEFT_DIRECTION))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_level = (m_level > SLK_EASY) ? --m_level : SLK_EASY;

		return;
	}

	if (m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON) ||
		m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.SetNextScene(SK_2P_GAME);
	}
}

VOID StageSelectTwoPlayerSceneLevelSelecter::Render()
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

VOID StageSelectTwoPlayerSceneLevelSelecter::RenderBack() const
{
	ObjData backData;
	backData.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	backData.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	backData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, backData);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("LevelBack")));
}

VOID StageSelectTwoPlayerSceneLevelSelecter::RenderTarget() const
{
	ObjData levelData;

	for (INT i = 0; i < SLK_EXTREME; ++i)
	{
		levelData.m_center = { m_WND_SIZE.m_x * 0.262f + m_WND_SIZE.m_x * 0.238f * i, m_WND_SIZE.m_y * 0.727f, m_Z };
		levelData.m_halfScale = { m_WND_SIZE.m_x * 0.06f, m_WND_SIZE.m_y * 0.034f, 0.0f };

		levelData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

		const D3DXVECTOR2 ILLUST_SCALE = { 1024.0f, 64.0f };
		const D3DXVECTOR2 LEVEL_SCALE = { 150.0f,50.0f };

		levelData.m_texUV =
		{
			LEVEL_SCALE.x * i / ILLUST_SCALE.x,
			0.0f,
			LEVEL_SCALE.x * (i + 1) / ILLUST_SCALE.x,
			LEVEL_SCALE.y / ILLUST_SCALE.y
		};

		CustomVertex level[4];
		m_rGameLib.CreateRect(level, levelData);

		m_rGameLib.Render(level, m_rGameLib.GetTex(_T("LevelTexts")));

		if (i != m_level || m_backIsSelected) continue;

		levelData.m_halfScale.x *= 1.03f;
		levelData.m_halfScale.y *= 1.09f;

		levelData.m_texUV.m_startTU = LEVEL_SCALE.x * (SLK_EXTREME + 1) / ILLUST_SCALE.x;
		levelData.m_texUV.m_endTU = levelData.m_texUV.m_startTU + LEVEL_SCALE.x / ILLUST_SCALE.x;

		m_rGameLib.CreateRect(level, levelData);

		m_rGameLib.AddtionBlendMode();
		m_rGameLib.Render(level, m_rGameLib.GetTex(_T("LevelTexts")));
		m_rGameLib.DefaultBlendMode();
	}
}

VOID StageSelectTwoPlayerSceneLevelSelecter::RenderBackButton() const
{
	ObjData backButtonData;
	
	backButtonData.m_center = { m_WND_SIZE.m_x * 0.14f, m_WND_SIZE.m_y * 0.17f, m_Z };										//! 現物合わせ
	backButtonData.m_halfScale = { m_WND_SIZE.m_y * 0.05f, m_WND_SIZE.m_y * 0.05f, 0.0f };										//! 現物合わせ

	backButtonData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

	const D3DXVECTOR2 ILLUST_SCALE = { 300.0f, 150.0f };
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
