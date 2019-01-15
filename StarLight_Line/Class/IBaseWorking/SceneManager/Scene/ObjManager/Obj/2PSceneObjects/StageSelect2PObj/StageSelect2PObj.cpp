#include "StageSelect2PObj.h"

VOID StageSelectTwoPlayerSceneStageList::Update()
{
	if (m_isDecided) return;

	if ((m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::UP_TILT) ||
		 m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::UP_TILT))&&
		 m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = FALSE;
	}

	if ((m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::DOWN_TILT) ||
		 m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::DOWN_TILT))&&
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

	if ((m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON) ||
		 m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON)) &&
		!m_backIsSelected)
	{
		m_lengthMulti = 0.0f;

		m_isDecided = TRUE;
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

	if (m_rGameLib.HoldJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::LEFT_TILT)||
		m_rGameLib.HoldJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::LEFT_TILT))
	{
		m_deg = ROTATE_SPEED;	//! 回転の起動

		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		return;
	}

	if (m_rGameLib.HoldJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_TILT) ||
		m_rGameLib.HoldJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::RIGHT_TILT))
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

		if (m_deg != DEG_GAP && m_deg != -DEG_GAP) continue;
		m_selectingStage -= static_cast<INT>(m_deg / DEG_GAP);												//! 角度が60を超えるとm_selectingStageを次の値に変える
		m_deg = 0.0f;

		if (m_selectingStage < 0) m_selectingStage = m_STAGE_ICONS_MAX + m_selectingStage;					//! m_selectingStageがマイナスに行ったときの対処
		m_selectingStage %= m_STAGE_ICONS_MAX;
	}

	m_rGameLib.DefaultBlendMode();

	if (iconsCircleRadius != 0.0f) RenderBackButton(iconsCircleRadius);
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

VOID StageSelectTwoPlayerSceneLevelSelecter::Update()
{
	m_shouldActivateStageSelect = FALSE;

	if (m_alpha < 255) return;

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::UP_TILT) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::UP_TILT))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = TRUE;

		return;
	}

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::DOWN_TILT) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER, Joycon::DOWN_TILT))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_backIsSelected = FALSE;

		return;
	}

	if ((m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::LEFT_BUTTON) ||
		m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON))   && 
		m_backIsSelected)
	{
		m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

		m_shouldActivateStageSelect = TRUE;

		return;
	}

	if (m_backIsSelected) return;

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::LEFT_TILT) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER,Joycon::LEFT_TILT))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_level = (m_level < SLK_HARD) ? ++m_level : SLK_HARD;

		return;
	}

	if (m_rGameLib.PushJoyconAnalogStick(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_TILT) ||
		m_rGameLib.PushJoyconAnalogStick(Joycon::RIGHT_CONTROLLER,Joycon::RIGHT_TILT))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		m_level = (m_level > SLK_EASY) ? --m_level : SLK_EASY;

		return;
	}

	if (m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::LEFT_BUTTON) ||
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

	ObjData targetData;
	targetData.m_center = { m_WND_SIZE.m_x * 0.262f + m_WND_SIZE.m_x * 0.238f * m_level, m_WND_SIZE.m_y * 0.657f, m_Z };	//! 現物合わせ
	targetData.m_halfScale = { m_WND_SIZE.m_y * 0.017f, m_WND_SIZE.m_y * 0.017f, 0.0f };										//! 現物合わせ

	targetData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

	targetData.m_deg.z = 90.0f;

	if (m_backIsSelected)
	{
		targetData.m_center = { m_WND_SIZE.m_x * 0.1865f, m_WND_SIZE.m_y * 0.17f, m_Z };										//! 現物合わせ
		targetData.m_deg.z = 180.0f;
	}

	CustomVertex target[4];
	m_rGameLib.CreateRect(target, targetData);

	m_rGameLib.Render(target, m_rGameLib.GetTex(_T("LevelTarget")));
}

VOID StageSelectTwoPlayerSceneLevelSelecter::RenderBackButton() const
{
	ObjData backButtonData;
	backButtonData.m_center = { m_WND_SIZE.m_x * 0.14f, m_WND_SIZE.m_y * 0.17f, m_Z };										//! 現物合わせ
	backButtonData.m_halfScale = { m_WND_SIZE.m_y * 0.05f, m_WND_SIZE.m_y * 0.05f, 0.0f };										//! 現物合わせ

	backButtonData.m_aRGB = D3DCOLOR_ARGB(m_alpha, 255, 255, 255);

	CustomVertex backButton[4];
	m_rGameLib.CreateRect(backButton, backButtonData);

	m_rGameLib.Render(backButton, m_rGameLib.GetTex(_T("LevelBackButton")));
}
