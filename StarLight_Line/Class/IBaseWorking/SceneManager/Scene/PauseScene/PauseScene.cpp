#include "PauseScene.h"

#include <tchar.h>

#include "../ObjManager/Obj/MainSceneObj/ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../ObjManager/Obj/MainSceneObj/ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../ObjManager/Obj/MainSceneObj/ADV/Chapter/Section/Text/Text.h"

VOID PauseScene::Init()
{
	m_ActivatingKey = RESUME_KEY;
	m_rGameLib.CreateTex(_T("PauseBack"), _T("2DTextures/Pause/pause_background.png"));
	m_rGameLib.CreateTex(_T("PauseFrame"), _T("2DTextures/Pause/pause_textframe.png"));
	m_rGameLib.CreateTex(_T("PauseEffect"), _T("2DTextures/Pause/PauseSelectFrame.png"));
}

VOID PauseScene::Update()
{
	if (m_rGameLib.KeyboardIsPressed(DIK_UP) &&
		m_ActivatingKey != RESUME_KEY)
	{
		--m_ActivatingKey;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_DOWN) &&
		m_ActivatingKey != RESTART_KEY)
	{
		++m_ActivatingKey;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_RETURN))
	{
		TransferScene(static_cast<TRANSFER_KEY>(m_ActivatingKey));
	}
}

VOID PauseScene::Render()
{
	RenderPauseBack();

	RenderPauseFrame();

	RenderPauseEffect();

	RenderPauseHead();
	RenderPauseText();
}

VOID PauseScene::RenderPauseBack()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center	 = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 1.f };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 1.f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("PauseBack")));
}

VOID PauseScene::RenderPauseFrame()
{
	const INT VERTEX_NUM = 4;
	const INT MAX_RECT = 4;
	CustomVertex Frame[VERTEX_NUM * MAX_RECT];

	for (int i = 0; i < MAX_RECT; ++i)
	{
		ObjData Data[MAX_RECT];
		Data[i].m_center    = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.35f + (130.f * i), 0.5f };
		Data[i].m_halfScale = { m_WND_SIZE.m_x * 0.4f, m_WND_SIZE.m_y * 0.08f, 0.5f };

		m_rGameLib.CreateRect(&Frame[i * VERTEX_NUM], Data[i]);
		m_rGameLib.Render(&Frame[i * VERTEX_NUM], m_rGameLib.GetTex(_T("PauseFrame")));
	}
}

VOID PauseScene::RenderPauseEffect()
{
	const INT VERTEX_NUM = 4;
	CustomVertex Effect[VERTEX_NUM];

	for (int i = 0; i < 4; ++i)
	{
		if (i != m_ActivatingKey) continue;

		ObjData Data;
		Data.m_center	 = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.35f + (130.f * i), 0.f };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.4f, m_WND_SIZE.m_y * 0.08f, 0.5f };

		m_rGameLib.CreateRect(Effect, Data);
		m_rGameLib.Render(Effect, m_rGameLib.GetTex(_T("PauseEffect")));
	}
}

VOID PauseScene::TransferScene(const TRANSFER_KEY& Key)
{
	SceneManager& rSceneManager = SceneManager::GetInstance();

	switch (Key)
	{
	case RESUME_KEY:
		rSceneManager.SetCanTransferSubScene(TRUE);
		rSceneManager.SetNextScene(SK_GAME);

		break;

	case TITLE_KEY:
		rSceneManager.SetCanTransferSubScene(FALSE);
		rSceneManager.SetNextScene(SK_TITLE);

		break;

	case STAGE_SELECT_KEY:
		rSceneManager.SetCanTransferSubScene(FALSE);
		rSceneManager.SetNextScene(SK_STAGE_SELECT);

		break;

	case RESTART_KEY:
		rSceneManager.SetCanTransferSubScene(FALSE);
		rSceneManager.SetNextScene(SK_GAME);

		break;

	default:
		break;
	}
}

VOID PauseScene::RenderPauseHead()
{
	const D3DXVECTOR2 CENTER_POS = { m_WND_SIZE.m_x *0.5f, m_WND_SIZE.m_y *0.5f };

	TextFormat headFormat;
	headFormat.m_charHalfScale = { 30, 60 };

	//! 真ん中にテキストを持っていくためテキストの半径を求める
	headFormat.m_topLeft = { CENTER_POS.x - 2.0f * headFormat.m_charHalfScale.m_x * 2.5f, 40.0f };

	TString pause(_T("PAUSE"));
	Text pauseText(pause, _T("2DTextures/Fonts/a_9.png"));

	pauseText.Write(headFormat);
}

VOID PauseScene::RenderPauseText()
{
	const D3DXVECTOR2 CENTER_POS = { m_WND_SIZE.m_x *0.5f, m_WND_SIZE.m_y *0.5f };

	TextFormat menuFormat;
	menuFormat.m_charHalfScale = { 24, 36 };
	menuFormat.m_topLeft = { CENTER_POS.x - 2.0f * menuFormat.m_charHalfScale.m_x * 4.0f, 216.0f };

	TString continueStr(_T("CONTINUE"));
	Text continueText(continueStr, _T("2DTextures/Fonts/a_9.png"));

	continueText.Write(menuFormat);

	TString backToTitle(_T("BACK TO TITLE"));
	Text backToTitleText(backToTitle, _T("2DTextures/Fonts/a_9.png"));

	menuFormat.m_topLeft.x = CENTER_POS.x - 2.0f * menuFormat.m_charHalfScale.m_x * 6.5f;
	menuFormat.m_topLeft.y += 130.0f;
	backToTitleText.Write(menuFormat);

	TString backToStageselect(_T("BACK TO STAGESELECT"));
	Text backToStageselectText(backToStageselect, _T("2DTextures/Fonts/a_9.png"));

	menuFormat.m_topLeft.x = CENTER_POS.x - 2.0f * menuFormat.m_charHalfScale.m_x * 9.5f;
	menuFormat.m_topLeft.y += 130.0f;
	backToStageselectText.Write(menuFormat);

	TString restart(_T("RESTART"));
	Text restartText(restart, _T("2DTextures/Fonts/a_9.png"));

	menuFormat.m_topLeft.x = CENTER_POS.x - 2.0f * menuFormat.m_charHalfScale.m_x * 3.5f;
	menuFormat.m_topLeft.y += 130.0f;
	restartText.Write(menuFormat);
}
