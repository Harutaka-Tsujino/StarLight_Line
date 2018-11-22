#include "TitleSceneObj.h"

#include <windows.h>

#include "../Obj.h"
#include "../../../../../../../GameLib/GameLib.h"
#include "../../../../SceneManager.h"
#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"
#include "../../../Enum/SCENE_KIND.h"

VOID TitleMenu::Render()
{
	if (!m_isActive) return;

	ObjData data;
	CustomVertex menu[4];
	const FLOAT CENTER_MENU_SCALE_MULTI = 1.5f;

	for (INT i = 0; i < MK_MAX; ++i)
	{
		data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * (0.65f + 0.07f * i), 0.98f };
		data.m_halfScale.x = m_WND_SIZE.m_x * 0.055f;
		data.m_halfScale.y = m_WND_SIZE.m_y * 0.029f;
		if (i == m_CENTER_MENU) data.m_halfScale *= CENTER_MENU_SCALE_MULTI;

		data.m_aRGB = D3DCOLOR_ARGB(200, 255, 255, 255);

		m_rGameLib.CreateRect(menu, data);

		switch (m_menuReel[i])
		{
		case MK_NEW_GAME:
			m_rGameLib.Render(menu, m_rGameLib.GetTex(_T("NewGame")));

			break;

		case MK_LOAD_GAME:
			m_rGameLib.Render(menu, m_rGameLib.GetTex(_T("LoadGame")));

			break;

		case MK_END_GAME:
			m_rGameLib.Render(menu, m_rGameLib.GetTex(_T("EndGame")));

			break;

		default:
			break;
		}
	}
}

VOID TitleMenu::SelectMenu()
{
	if (m_rGameLib.KeyboardIsPressed(DIK_W) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD8) ||
		m_rGameLib.KeyboardIsPressed(DIK_UP))
	{
		RotateMenuUp();
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_S) ||
		m_rGameLib.KeyboardIsPressed(DIK_NUMPAD2) ||
		m_rGameLib.KeyboardIsPressed(DIK_DOWN))
	{
		RotateMenuDown();
	}

	if (!m_rGameLib.KeyboardIsPressed(DIK_RETURN)) return;

	SceneManager& rSceneManager = SceneManager::GetInstance();
	switch (m_menuReel[m_CENTER_MENU])
	{
	case MK_NEW_GAME:
		rSceneManager.SetNextScene(SK_GAME);

		break;

	case MK_LOAD_GAME:
		rSceneManager.SetNextScene(SK_GAME);

		break;

	case MK_END_GAME:
		rSceneManager.SetNextScene(SK_GAME);

		break;

	default:
		break;
	}
}

VOID TitleCometEffect::Render()
{
	m_isInitInFrame = FALSE;

	m_rGameLib.AddtionBlendMode();

	const INT EFFECT_DATAS_MAX = 20;
	static EffectData effectDatas[EFFECT_DATAS_MAX];

	const D3DXVECTOR3 ROTATE_RELATIVE_POS(0.0f, 0.0f, 0.0f);

	const INT TOP = 0;
	const INT BOTTOM = 3;

	for (INT i = 0; i < EFFECT_DATAS_MAX; ++i)
	{
		D3DXVec3Add(
			&effectDatas[i].m_data.m_center,
			&effectDatas[i].m_data.m_center,
			&effectDatas[i].m_movement);

		m_rGameLib.CreateRect(effectDatas[i].m_vertices, effectDatas[i].m_data);

		if (effectDatas[i].m_vertices[BOTTOM].m_pos.y > 0.0f &&
			effectDatas[i].m_vertices[TOP].m_pos.y < m_WND_SIZE.m_y)
		{
			m_rGameLib.Render(effectDatas[i].m_vertices, m_rGameLib.GetTex(_T("Comet")));

			m_rGameLib.SetRectARGB(effectDatas[i].m_vertices, D3DCOLOR_ARGB(230, 255, 255, 255));
			m_rGameLib.Render(effectDatas[i].m_vertices, m_rGameLib.GetTex(_T("OverComet")));

			continue;
		}

		if (effectDatas[i].m_vertices[0].m_pos.y > m_WND_SIZE.m_y) effectDatas[i].m_isInit = FALSE;

		InitEffect(&effectDatas[i]);
	}

	m_rGameLib.DefaultBlendMode();
}

VOID TitleCometEffect::InitEffect(EffectData* pEffectDatas)
{
	if (!m_rGameLib.KeyboardAnyKeyIsPressed() || pEffectDatas->m_isInit || m_isInitInFrame) return;

	m_isInitInFrame = TRUE;

	static const INT EFFECT_COLORS_MAX = 11;
	static const DWORD EFFECT_COLORS[EFFECT_COLORS_MAX] =
	{
		D3DCOLOR_ARGB(255, 63, 255, 20),
		D3DCOLOR_ARGB(255, 20, 255, 95),
		D3DCOLOR_ARGB(255, 20, 255, 212),
		D3DCOLOR_ARGB(255, 20, 181, 255),
		D3DCOLOR_ARGB(255, 20, 63, 255),
		D3DCOLOR_ARGB(255, 95, 20, 255),
		D3DCOLOR_ARGB(255, 212, 20, 255),
		D3DCOLOR_ARGB(255, 255, 20, 181),
		D3DCOLOR_ARGB(255, 255, 20, 63),
		D3DCOLOR_ARGB(255, 255, 95, 20),
		D3DCOLOR_ARGB(255, 255, 212, 20),
	};

	pEffectDatas->m_data.m_center = {
		static_cast<float>(rand() % m_WND_SIZE.m_x + m_WND_SIZE.m_x * 1.5f),
		-static_cast<float>(rand() % (m_WND_SIZE.m_y * 2) + m_WND_SIZE.m_y * 1.0f),
		0.99f };
	pEffectDatas->m_data.m_halfScale = { m_WND_SIZE.m_x * 0.0035f, m_WND_SIZE.m_y * 0.6f, 0.0f };

	pEffectDatas->m_data.m_aRGB = EFFECT_COLORS[rand() % EFFECT_COLORS_MAX];

	pEffectDatas->m_data.m_deg.z = 45.0f;
	const D3DXVECTOR3 MOVEMENT(0.0f, 30.0f, 0.0f);
	D3DXMATRIX rotate;
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(pEffectDatas->m_data.m_deg.z));
	D3DXVec3TransformCoord(
		&pEffectDatas->m_movement,
		&MOVEMENT,
		&rotate);

	pEffectDatas->m_isInit = TRUE;
}

VOID TitleSmallStarEffect::Render()
{
	m_rGameLib.AddtionBlendMode();

	const INT EFFECTS_MAX = 150;
	static EffectData effectDatas[EFFECTS_MAX];

	for (int i = 0; i < EFFECTS_MAX; ++i)
	{
		InitEffect(&effectDatas[i]);

		CustomVertex OverEffect[4];
		memcpy(
			OverEffect,
			effectDatas[i].m_vertices,
			sizeof(CustomVertex) * 4);

		const D3DXVECTOR2 OVER_EFFECT_SCALE_MULTI(3.0f, 3.0f);
		m_rGameLib.RescaleRect(OverEffect, OVER_EFFECT_SCALE_MULTI);

		DWORD OverEffectARGB = D3DCOLOR_ARGB(250, 255, 255, 255);
		m_rGameLib.SetRectARGB(OverEffect, OverEffectARGB);

		m_rGameLib.Render(OverEffect, m_rGameLib.GetTex(_T("OverSmallStar")));

		effectDatas[i].m_data.m_aRGB = D3DCOLOR_ARGB(
			effectDatas[i].m_flashCnt,
			static_cast<int>(effectDatas[i].m_aRGB.x),
			static_cast<int>(effectDatas[i].m_aRGB.y),
			static_cast<int>(effectDatas[i].m_aRGB.z));

		m_rGameLib.CreateRect(effectDatas[i].m_vertices, effectDatas[i].m_data);
		m_rGameLib.Render(effectDatas[i].m_vertices, m_rGameLib.GetTex(_T("SmallStar")));

		CntFlashCnt(&effectDatas[i]);
	}

	m_rGameLib.DefaultBlendMode();
}

VOID TitleSmallStarEffect::InitEffect(EffectData* pEffectDatas) const
{
	if (pEffectDatas->m_flashCnt != pEffectDatas->m_INIT_CNT) return;

	const INT EFFECT_COLORS_MAX = 11;
	const D3DXVECTOR4 EFFECT_COLORS[EFFECT_COLORS_MAX] =
	{
		{ 255, 63, 255, 20 },
		{ 255, 20, 255, 95 },
		{ 255, 20, 255, 212 },
		{ 255, 20, 181, 255 },
		{ 255, 20, 63, 255 },
		{ 255, 95, 20, 255 },
		{ 255, 212,20, 255 },
		{ 255, 255, 20, 181 },
		{ 255, 255, 20, 63 },
		{ 255, 255, 95, 20 },
		{ 255, 255, 212, 20 },
	};

	pEffectDatas->m_flashCnt = rand() % (m_FLASH_CNT_MAX - m_FLASH_CNT_MIN) + m_FLASH_CNT_MIN;
	pEffectDatas->m_isIncrease = rand() % TRUE;

	pEffectDatas->m_data.m_center = {
		(FLOAT)(rand() % m_WND_SIZE.m_x),
		(FLOAT)(rand() % m_WND_SIZE.m_y),
		0.991f };
	FLOAT halfScale = 0.5f;
	if (rand() % 2) halfScale = 1.0f;
	pEffectDatas->m_data.m_halfScale = { halfScale,halfScale,0.0f };

	INT selectedARGB = rand() % EFFECT_COLORS_MAX;
	pEffectDatas->m_aRGB.x = EFFECT_COLORS[selectedARGB].x;
	pEffectDatas->m_aRGB.y = EFFECT_COLORS[selectedARGB].y;
	pEffectDatas->m_aRGB.z = EFFECT_COLORS[selectedARGB].z;
}
