#include "StageSelectSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../../../Enum/SCENE_KIND.h"
#include "../../../../SceneManager.h"

VOID StageSelectSceneStageList::Update()
{
	SceneManager& rSceneManager = SceneManager::GetInstance();

	if ((m_rGameLib.KeyboardIsPressed(DIK_W) ||
		m_rGameLib.KeyboardIsPressed(DIK_UP) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD8)) &&
		m_backIsSelected)
	{
		m_backIsSelected = FALSE;
	}

	if (m_backIsSelected &&
		(m_rGameLib.KeyboardIsPressed(DIK_RETURN) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPADENTER)))
	{
		rSceneManager.SetNextScene(SK_TITLE);

		return;
	}

	if (m_backIsSelected) return;

	if ((m_rGameLib.KeyboardIsPressed(DIK_RETURN) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPADENTER)) &&
		m_deg == 0.0f &&
		m_lengthMulti == 0.0f)
	{
		m_lengthMulti = -1.0f;

		return;
	}

	if (m_lengthMulti != 0.0f || m_isDecided) return;

	if ((m_rGameLib.KeyboardIsPressed(DIK_S)	||
		m_rGameLib.KeyboardIsPressed(DIK_DOWN)	||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD2)))
	{
		m_backIsSelected = TRUE;

		return;
	}

	const FLOAT ROTATE_SPEED = 1.5f;
	m_deg +=	ROTATE_SPEED * (m_deg > 0.0f) -
				ROTATE_SPEED * (m_deg < 0.0f);

	if (m_deg != 0) return;

	m_deg = ROTATE_SPEED * (m_rGameLib.KeyboardIsHeld(DIK_D) ||
							m_rGameLib.KeyboardIsHeld(DIK_RIGHT) ||
							m_rGameLib.KeyboardIsHeld(DIK_NUMPAD6)) -
			ROTATE_SPEED * (m_rGameLib.KeyboardIsHeld(DIK_A) ||
							m_rGameLib.KeyboardIsHeld(DIK_LEFT) ||
							m_rGameLib.KeyboardIsHeld(DIK_NUMPAD4));
}

VOID StageSelectSceneStageList::Render()
{
	if (m_isDecided) m_rGameLib.AddtionBlendMode();

	const D3DXVECTOR3 ICONS_CENTER = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.4f, m_Z };
	const FLOAT ICONS_CIRCULE_RADIUS_MAX = 230.0f;
	static FLOAT iconsCirculeRadius = ICONS_CIRCULE_RADIUS_MAX;

	const INT DECIDE_STAGE_FRAMES = 60;
	iconsCirculeRadius += m_lengthMulti * ICONS_CIRCULE_RADIUS_MAX / DECIDE_STAGE_FRAMES;
	iconsCirculeRadius = min(max(iconsCirculeRadius, 0), ICONS_CIRCULE_RADIUS_MAX);

	if (iconsCirculeRadius == ICONS_CIRCULE_RADIUS_MAX ||
		!iconsCirculeRadius)
	{
		m_lengthMulti = 0.0f;

		m_isDecided = !iconsCirculeRadius;
	}

	D3DXMATRIX rotate;
	const FLOAT DEG_GAP = 360.0f / m_STAGE_ICONS_MAX;
	FLOAT* pDeg = nullptr;

	D3DXVECTOR3* pCenter = nullptr;
	FLOAT halfScale = 0.0f;

	const RectSize ILLUST_SIZE = { 2048, 1024 };
	const FLOAT ICON_ILLUST_SIZE = 303.0f;

	StageIconData stageIconDatas[m_STAGE_ICONS_MAX];
	CustomVertex stageIcon[4];

	for (int i = 0; i < m_STAGE_ICONS_MAX; ++i)
	{
		if (i != m_selectingStage && m_isDecided) continue;

		pDeg = &stageIconDatas[i].m_deg;
		*pDeg = DEG_GAP * (i - m_selectingStage) + m_deg;
		D3DXMatrixRotationZ(&rotate, D3DXToRadian(*pDeg));

		pCenter = &stageIconDatas[i].m_objData.m_center;
		pCenter->y = iconsCirculeRadius;
		D3DXVec3TransformCoord(pCenter, pCenter, &rotate);
		*pCenter += ICONS_CENTER;
		if (i == m_selectingStage) pCenter->z -= 0.1f;

		halfScale = (17.5f + (ICONS_CIRCULE_RADIUS_MAX - iconsCirculeRadius) * 0.01f)
			* (cos(D3DXToRadian(*pDeg)) + 2.0f);
		stageIconDatas[i].m_objData.m_halfScale = { halfScale, halfScale, 0.0f };

		stageIconDatas[i].m_objData.m_texUV =
		{
			ICON_ILLUST_SIZE * (i % 6)		/ ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / 6)		/ ILLUST_SIZE.m_y,
			ICON_ILLUST_SIZE * (i % 6 + 1)	/ ILLUST_SIZE.m_x,
			ICON_ILLUST_SIZE * (i / 6 + 1)	/ ILLUST_SIZE.m_y
		};

		m_rGameLib.CreateRect(stageIcon, stageIconDatas[i].m_objData);

		m_rGameLib.Render(stageIcon, m_rGameLib.GetTex(_T("Icons")));

		if (m_deg != DEG_GAP && m_deg != -DEG_GAP) continue;
		m_selectingStage -= static_cast<INT>(m_deg / DEG_GAP);
		m_deg = 0.0f;

		if (m_selectingStage < 0) m_selectingStage = m_STAGE_ICONS_MAX + m_selectingStage;
		m_selectingStage %= m_STAGE_ICONS_MAX;
	}

	m_rGameLib.DefaultBlendMode();

	if (iconsCirculeRadius == 0.0f) return;

	ObjData backButtonData;
	backButtonData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.96f, m_Z };
	backButtonData.m_halfScale	= { m_WND_SIZE.m_x * 0.05f, m_WND_SIZE.m_y * 0.04f, 0.0f };

	backButtonData.m_aRGB = D3DCOLOR_ARGB(
							static_cast<UCHAR>(iconsCirculeRadius),
							255, 255, 255);

	backButtonData.m_texUV =
	{
		-(m_backIsSelected -1) / 2.0f,
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

	if (!m_rIsDecided)
	{
		m_sceneTranlationAlpha = 0;

		return;
	}

	//if (m_sceneTranlationAlpha) return;

	if ((m_rGameLib.KeyboardIsPressed(DIK_W) ||
		m_rGameLib.KeyboardIsPressed(DIK_UP) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD8)))
	{
		m_backIsSelected = TRUE;

		return;
	}

	if ((m_rGameLib.KeyboardIsPressed(DIK_S)	||
		m_rGameLib.KeyboardIsPressed(DIK_DOWN)	||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD2)))
	{
		m_backIsSelected = FALSE;

		return;
	}

	if (m_backIsSelected &&
		(m_rGameLib.KeyboardIsPressed(DIK_RETURN) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPADENTER)))
	{
		m_shouldActivateStageSelect = TRUE;

		return;
	}

	if (m_backIsSelected) return;

	if (m_rGameLib.KeyboardIsPressed(DIK_D)		||
		m_rGameLib.KeyboardIsPressed(DIK_RIGHT) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD6))
	{
		m_level = (m_level < SLK_HARD) ? ++m_level : SLK_HARD;

		return;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_A)		||
		m_rGameLib.KeyboardIsPressed(DIK_LEFT)  ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD4))
	{
		m_level = (m_level > SLK_EASY) ? --m_level : SLK_EASY;

		return;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_RETURN))
	{
		//ステージの決定
		m_sceneTranlationAlpha = 1;
	}
}

VOID StageSelectSceneLevelSelecter::Render()
{
	ObjData backData;
	backData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	backData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	static INT alpha = 0;
	alpha += 10 * ((m_rIsDecided) ? 1 : -1);
	alpha = min(max(alpha, 0), 255);

	if (!alpha)
	{
		m_backIsSelected = FALSE;	//! 0か1しか入れてはいけない

		return;
	}

	backData.m_aRGB = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, backData);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("LevelBack")));

	ObjData selectData;
	selectData.m_center		= { m_WND_SIZE.m_x * 0.22f + m_WND_SIZE.m_x * 0.28f * m_level, m_WND_SIZE.m_y * 0.7f, m_Z };
	selectData.m_halfScale	= { m_WND_SIZE.m_x * 0.1f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	selectData.m_aRGB = D3DCOLOR_ARGB(alpha * -(m_backIsSelected - 1), 255, 255, 255);	//! 安全な計算を行うためのフラグ反転

	CustomVertex select[4];
	m_rGameLib.CreateRect(select, selectData);

	m_rGameLib.Render(select, m_rGameLib.GetTex(_T("LevelSelectFrame")));

	ObjData backButtonData;
	backButtonData.m_center		= { m_WND_SIZE.m_x * 0.14f, m_WND_SIZE.m_y * 0.17f, m_Z };
	backButtonData.m_halfScale	= { m_WND_SIZE.m_y * 0.05f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	backButtonData.m_aRGB = D3DCOLOR_ARGB(alpha, 255 * m_backIsSelected, 255 * m_backIsSelected, 255 * m_backIsSelected);
	
	CustomVertex backButton[4];
	m_rGameLib.CreateRect(backButton, backButtonData);

	m_rGameLib.Render(backButton, m_rGameLib.GetTex(_T("LevelBackButton")));

	if (!m_sceneTranlationAlpha) return;

	ObjData sceneTranslationData;
	sceneTranslationData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	sceneTranslationData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	sceneTranslationData.m_aRGB = D3DCOLOR_ARGB(m_sceneTranlationAlpha, 255, 255, 255);

	CustomVertex sceneTranslation[4];
	m_rGameLib.CreateRect(sceneTranslation, sceneTranslationData);

	m_rGameLib.Render(sceneTranslation, nullptr);

	m_sceneTranlationAlpha += 2 * ((m_sceneTranlationAlpha) ? 1 : -1);
	m_sceneTranlationAlpha = min(max(m_sceneTranlationAlpha, 0), 255);
}
