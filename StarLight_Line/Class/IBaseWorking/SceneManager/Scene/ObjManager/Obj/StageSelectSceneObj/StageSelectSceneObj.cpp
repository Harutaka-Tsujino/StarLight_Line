#include "StageSelectSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../../../Enum/SCENE_KIND.h"
#include "../../../../SceneManager.h"

VOID StageSelectSceneStageList::Update()
{
	if ((m_rGameLib.KeyboardIsPressed(DIK_RETURN) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPADENTER)) &&
		m_deg == 0.0f &&
		m_lengthMulti == 0.0f)
	{
		m_lengthMulti = -1.0f;

		return;
	}

	if ((m_rGameLib.KeyboardIsPressed(DIK_BACK) ||
		m_rGameLib.KeyboardIsPressed(DIK_ESCAPE)) &&
		m_isDecided &&
		m_lengthMulti == 0.0f)
	{
		m_lengthMulti = 1.0f;

		m_isDecided = FALSE;

		return;
	}

	SceneManager& rSceneManager = SceneManager::GetInstance();

	if ((m_rGameLib.KeyboardIsPressed(DIK_BACK) ||
		m_rGameLib.KeyboardIsPressed(DIK_ESCAPE)) &&
		m_lengthMulti == 0.0f)
	{
		rSceneManager.SetNextScene(SK_TITLE);
	}

	if (m_lengthMulti != 0.0f || m_isDecided) return;

	const FLOAT ROTATE_SPEED = 1.5f;
	m_deg += ROTATE_SPEED * (m_deg > 0.0f) -
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
	const D3DXVECTOR3 ICONS_CENTER = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	const FLOAT ICONS_CIRCULE_RADIUS_MAX = 250.0f;
	static FLOAT iconsCirculeRadius = ICONS_CIRCULE_RADIUS_MAX;

	const INT DECIDE_STAGE_FRAMES = 60;
	iconsCirculeRadius += m_lengthMulti * ICONS_CIRCULE_RADIUS_MAX / DECIDE_STAGE_FRAMES;
	iconsCirculeRadius = min(max(iconsCirculeRadius, 0), ICONS_CIRCULE_RADIUS_MAX);

	if (iconsCirculeRadius == ICONS_CIRCULE_RADIUS_MAX ||
		iconsCirculeRadius == 0.0f) m_lengthMulti = 0.0f;
	if (!iconsCirculeRadius) m_isDecided = TRUE;

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
}

VOID StageSelectSceneLevelSelecter::Render()
{
	ObjData backData;
	backData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	backData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	static INT alpha = 0;
	alpha += 10 * ((m_rIsDecided) ? 1 : -1);
	if (alpha >= 255)	alpha = 255;
	if (alpha <= 0)		alpha = 0;
	backData.m_aRGB = D3DCOLOR_ARGB(static_cast<UCHAR>(alpha), 255, 255, 255);

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, backData);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("LevelBack")));

	ObjData selectData;
	selectData.m_center		= { m_WND_SIZE.m_x * 0.22f + m_WND_SIZE.m_x * 0.28f * m_level, m_WND_SIZE.m_y * 0.7f, m_Z };
	selectData.m_halfScale	= { m_WND_SIZE.m_x * 0.1f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	selectData.m_aRGB = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	CustomVertex select[4];
	m_rGameLib.CreateRect(select, selectData);

	m_rGameLib.Render(select, m_rGameLib.GetTex(_T("LevelSelectFrame")));
}
