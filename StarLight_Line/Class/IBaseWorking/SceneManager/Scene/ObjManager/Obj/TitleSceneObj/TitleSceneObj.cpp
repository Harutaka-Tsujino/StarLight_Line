/// @file TitleSceneObj.cpp
/// <summary>
/// タイトルシーンで用いるオブジェクト継承クラスのソース
/// </summary>
/// @author Harutaka-Tsujino

#include "TitleSceneObj.h"

#include <windows.h>
#include <tchar.h>

#include "../Obj.h"
#include "../../../../../../../GameLib/GameLib.h"
#include "../../../../SceneManager.h"
#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"
#include "../../../Enum/SCENE_KIND.h"

VOID TitleLogo::Render()
{
	m_rGameLib.AddtionBlendMode();

	static INT frameCount = 0;

	if (frameCount == 1) { m_rGameLib.OneShotStartSound(_T("TeamLogo")); };

	const INT FRAME_COUNT_MAX = 40;
	FLOAT frameProgressRate = static_cast<FLOAT>(frameCount) / FRAME_COUNT_MAX;

	FLOAT halfScaleYWndMulti = 0.29f;
	FLOAT centerYWndMultiply = 0.5f - halfScaleYWndMulti;

	ObjData data;
	data.m_halfScale	= { m_WND_SIZE.m_x * halfScaleYWndMulti * frameProgressRate, m_WND_SIZE.m_y * 0.2f, 0.0f };	//! 現物合わせ
	data.m_center		= { m_WND_SIZE.m_x * centerYWndMultiply + data.m_halfScale.x, m_WND_SIZE.m_y * 0.3f, m_Z };	//! 現物合わせ

	const INT DEFAULT_ALPHA_MAX = 90;
	data.m_aRGB = D3DCOLOR_ARGB(static_cast<INT>(DEFAULT_ALPHA_MAX * frameProgressRate), 255, 255, 255);

	if (frameCount >= FRAME_COUNT_MAX)
	{
		static INT additionalAlphaCount = 0;
		data.m_aRGB = D3DCOLOR_ARGB(DEFAULT_ALPHA_MAX + additionalAlphaCount, 255, 255, 255);

		INT additionalAlphaCountMax = 230 - DEFAULT_ALPHA_MAX;
		additionalAlphaCount = (additionalAlphaCount >= additionalAlphaCountMax) ? additionalAlphaCountMax : additionalAlphaCount += 2;
	}

	data.m_texUV.m_endTU = frameProgressRate;

	CustomVertex logo[4];
	m_rGameLib.CreateRect(logo, data);	

	m_rGameLib.Render(logo, m_rGameLib.GetTex(_T("Logo")));

	frameCount = (frameCount >= FRAME_COUNT_MAX) ? FRAME_COUNT_MAX : ++frameCount;

	m_rGameLib.DefaultBlendMode();
}

VOID TitleMenu::Render()
{
	if (!m_isActive) return;

	if (!m_isSelected)
	{
		SelectModeRender();

		return;
	}

	if (m_is2P)
	{
		ConnectPromptRender();
		ConnectJoyconRender();

		return;
	}

	ObjData data;
	CustomVertex menu[4];
	const FLOAT CENTER_MENU_SCALE_MULTI = 1.5f;

	for (INT i = 0; i < MK_MAX; ++i)
	{
		data.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * (0.68f + 0.07f * i), m_Z };	//! 現物合わせ
		data.m_halfScale	= { m_WND_SIZE.m_x * 0.06f, m_WND_SIZE.m_y * 0.033f ,0.0f };			//! 現物合わせ
		if (i == m_CENTER_MENU) data.m_halfScale *= CENTER_MENU_SCALE_MULTI;

		data.m_aRGB = D3DCOLOR_ARGB(200, 255, 255, 255);											//! 現物合わせ

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

VOID TitleMenu::ConnectPromptRender()
{
	ObjData Data;
	CustomVertex Prompt[4];

	Data.m_center = { m_WND_SIZE.m_x * 0.5f,m_WND_SIZE.m_y * 0.6f,m_Z };
	Data.m_halfScale = { m_WND_SIZE.m_x *0.3f,m_WND_SIZE.m_y * 0.1f,0.f };

	m_rGameLib.CreateRect(Prompt, Data);

	m_rGameLib.Render(Prompt, m_rGameLib.GetTex(_T("ConnectionPrompt")));
}

VOID TitleMenu::ConnectJoyconRender()
{
	ObjData Data;
	CustomVertex ConnectJoycon[4];

	for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
	{
		if (!m_rGameLib.GetIsConnectJoycon(static_cast<Joycon::CONTROLLER_TYPE>(i))) continue;

		Data.m_center = { m_WND_SIZE.m_x * (0.4f + 0.2f * i),m_WND_SIZE.m_y * 0.8f,m_Z };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.05f,m_WND_SIZE.m_y * 0.1f,0.f };
		
		const FLOAT TU_MAX = 128.f;
		Data.m_texUV.m_startTU = (i * (TU_MAX / 2)) / TU_MAX;
		Data.m_texUV.m_endTU = (i + 1)* (TU_MAX / 2) / TU_MAX;

		m_rGameLib.CreateRect(ConnectJoycon, Data);

		m_rGameLib.Render(ConnectJoycon, m_rGameLib.GetTex(_T("JoyCon")));
	}
}

VOID TitleMenu::SelectModeRender()
{
	ObjData Data;
	CustomVertex Menu[4];

	for (int i = 0;i < PM_MAX;++i)
	{
		Data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * (0.68f + 0.09f * i), m_Z };	//! 現物合わせ
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.06f, m_WND_SIZE.m_y * 0.033f ,0.0f };			//! 現物合わせ

		if (i == m_mode) Data.m_halfScale *= 1.25f;

		const FLOAT TV_MAX = 128.f;
		Data.m_texUV.m_startTV = (i * (TV_MAX / 2)) / TV_MAX;
		Data.m_texUV.m_endTV = (i + 1)* (TV_MAX / 2) / TV_MAX;

		m_rGameLib.CreateRect(Menu, Data);

		m_rGameLib.Render(Menu, m_rGameLib.GetTex(_T("PlayStyle")));
	}
}

VOID TitleMenu::SelectMode()
{
	static BOOL isFirstFrame = TRUE;
	if (isFirstFrame)	//!	PRESS ANY KEYが表示されているときEnterを入力したらそのままメニューを選んでしまうので一度return
	{
		isFirstFrame = FALSE;

		return;
	}

	if (UpKeyIsPressed())
	{
		m_mode = PM_1P;
	}

	if (DownKeyIsPressed())
	{
		m_mode = PM_2P;
	}

	if (!ReturnKeyIsPressed()) return;

	m_isSelected = (m_mode == PM_1P) ? TRUE : FALSE;

	if (!m_isSelected)
	{
		m_is2P = TRUE;
		m_isSelected = TRUE;
	}
}

VOID TitleMenu::Transfar2PWhenJoyconIsConnected()
{
	static BOOL isFirstFrame = TRUE;

	if (isFirstFrame)
	{
		m_JoyconThread = std::thread(&TitleMenu::CheakConnectJoycon, this);
		isFirstFrame = FALSE;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_BACK))
	{
		isFirstFrame = TRUE;
		m_is2P = FALSE;
		m_isSelected = FALSE;
		m_JoyconThread.join();
	}

	if (m_rGameLib.GetIsConnectJoycon(Joycon::LEFT_CONTROLLER) &&
		m_rGameLib.GetIsConnectJoycon(Joycon::RIGHT_CONTROLLER))
	{
		static int count = 0;
		count++;

		if (count <= 60) return;
	
		isFirstFrame = TRUE;

		m_JoyconThread.join();
		SceneManager& rSceneManager = SceneManager::GetInstance();
		rSceneManager.SetNextScene(SK_2P_STAGE_SELECT);
		count = 0;	
	}
}

VOID TitleMenu::SelectMenu()
{
	static BOOL isFirstFrame = TRUE;
	if (isFirstFrame)	//!	PRESS ANY KEYが表示されているときEnterを入力したらそのままメニューを選んでしまうので一度return
	{
		isFirstFrame = FALSE;

		return;
	}

	if (UpKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		RotateMenuDown();
	}

	if (DownKeyIsPressed())
	{
		m_rGameLib.OneShotSimultaneousSound(_T("ChangeStage"));

		RotateMenuUp();
	}

	if (!ReturnKeyIsPressed()) return;

	m_rGameLib.OneShotSimultaneousSound(_T("SelectMenu"));

	SceneManager& rSceneManager = SceneManager::GetInstance();
	switch (m_menuReel[m_CENTER_MENU])
	{
	case MK_NEW_GAME:
		rSceneManager.SetNextScene(SK_TUTORIAL);

		break;

	case MK_LOAD_GAME:
		rSceneManager.SetNextScene(SK_SAVE_DATA);

		break;

	case MK_END_GAME:
		rSceneManager.SetNextScene(SK_END);

		break;

	default:
		break;
	}
}

VOID TitleCometEffect::Render()
{
	m_isInitInFrame = FALSE;

	m_rGameLib.AddtionBlendMode();

	const INT EFFECT_DATAS_MAX = 4;
	static EffectData effectDatas[EFFECT_DATAS_MAX];

	const D3DXVECTOR3 ROTATE_RELATIVE_POS(0.0f, 0.0f, 0.0f);

	FLOAT effectTop		= 0;
	FLOAT effectBottom	= 0;

	for (INT i = 0; i < EFFECT_DATAS_MAX; ++i)
	{
		D3DXVec3Add(
			&effectDatas[i].m_data.m_center,
			&effectDatas[i].m_data.m_center,
			&effectDatas[i].m_movement);

		m_rGameLib.CreateRect(effectDatas[i].m_vertices, effectDatas[i].m_data);

		effectTop		= effectDatas[i].m_vertices[0].m_pos.y;
		effectBottom	= effectDatas[i].m_vertices[3].m_pos.y;

		if (effectBottom > 0.0f && effectTop < m_WND_SIZE.m_y)										//! 画面内にいれば描画する
		{
			m_rGameLib.Render(effectDatas[i].m_vertices, m_rGameLib.GetTex(_T("Comet")));

			m_rGameLib.SetRectARGB(effectDatas[i].m_vertices, D3DCOLOR_ARGB(230, 255, 255, 255));	//! 現物合わせ
			m_rGameLib.Render(effectDatas[i].m_vertices, m_rGameLib.GetTex(_T("OverComet")));

			continue;
		}

		if (effectTop > m_WND_SIZE.m_y) effectDatas[i].m_isInit = FALSE;							//! 画面の下までエフェクトが動いたら初期化する

		InitEffect(&effectDatas[i]);
	}

	m_rGameLib.DefaultBlendMode();
}

VOID TitleCometEffect::InitEffect(EffectData* pEffectDatas)
{
	if (!m_rGameLib.KeyboardAnyKeyIsPressed()	||													//! ボタンが押されないとエフェクトを流さないまた一つしか一フレームに初期化しない
		pEffectDatas->m_isInit					|| 
		m_isInitInFrame) return;

	m_isInitInFrame = TRUE;

	static const INT EFFECT_COLORS_MAX = 11;
	static const DWORD EFFECT_COLORS[EFFECT_COLORS_MAX] =											//! ビビッドカラー
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

	pEffectDatas->m_data.m_center = {																//! エフェクトの初期位置は乱数を用いて画面の範囲で決定する
		static_cast<float>(rand() % m_WND_SIZE.m_x + m_WND_SIZE.m_x * 1.5f),
		-static_cast<float>(rand() % (m_WND_SIZE.m_y * 2) + m_WND_SIZE.m_y * 1.0f),
		m_Z };
	pEffectDatas->m_data.m_halfScale = { m_WND_SIZE.m_x * 0.003f, m_WND_SIZE.m_y * 1.8f, 0.0f };	//! 現物合わせ

	pEffectDatas->m_data.m_aRGB = EFFECT_COLORS[rand() % EFFECT_COLORS_MAX];

	pEffectDatas->m_data.m_deg.z = 45.0f;															//! 星の入射角
	const D3DXVECTOR3 MOVEMENT(0.0f, 30.0f, 0.0f);													//! 後でこれを星の入射角分回転させて入射角度と移動方向を合わせる
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

		const D3DXVECTOR2 OVER_EFFECT_SCALE_MULTI(3.0f, 3.0f);		//! 現物合わせ
		m_rGameLib.RescaleRect(OverEffect, OVER_EFFECT_SCALE_MULTI);

		DWORD OverEffectARGB = D3DCOLOR_ARGB(250, 255, 255, 255);	//! 現物合わせ
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

	pEffectDatas->m_flashCnt = rand() % (m_FLASH_CNT_MAX - m_FLASH_CNT_MIN) + m_FLASH_CNT_MIN;	//! 乱数の最低値をm_FLASH_CNT_MINにするため
	pEffectDatas->m_isIncrease = rand() % TRUE;

	pEffectDatas->m_data.m_center = {															//! エフェクトの表示位置を座標で決める
		static_cast<FLOAT>(rand() % m_WND_SIZE.m_x),
		static_cast<FLOAT>(rand() % m_WND_SIZE.m_y),
		m_Z };
	FLOAT halfScale = 1.0f;
	if (rand() % 2) halfScale = 1.5f;															//! 1/2の確率で大きさが変わる
	pEffectDatas->m_data.m_halfScale = { halfScale, halfScale, 0.0f };

	const INT EFFECT_COLORS_MAX = 11;
	const D3DXVECTOR4 EFFECT_COLORS[EFFECT_COLORS_MAX] =										//! ビビッドカラー
	{
		{ 255, 63,	255,	20 },
		{ 255, 20,	255,	95 },
		{ 255, 20,	255,	212 },
		{ 255, 20,	181,	255 },
		{ 255, 20,	63,		255 },
		{ 255, 95,	20,		255 },
		{ 255, 212, 20,		255 },
		{ 255, 255, 20,		181 },
		{ 255, 255, 20,		63 },
		{ 255, 255, 95,		20 },
		{ 255, 255, 212,	20 },
	};
	INT selectedARGB = rand() % EFFECT_COLORS_MAX;
	pEffectDatas->m_aRGB.x = EFFECT_COLORS[selectedARGB].x;
	pEffectDatas->m_aRGB.y = EFFECT_COLORS[selectedARGB].y;
	pEffectDatas->m_aRGB.z = EFFECT_COLORS[selectedARGB].z;
}
