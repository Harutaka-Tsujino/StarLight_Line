#include "PauseScene.h"

VOID PauseScene::Init()
{
	m_ActivatingKey = RESUME_KEY;
	m_rGameLib.CreateTex(_T("PauseBack"), _T("2DTextures/Pause/pause_background.png"));
	m_rGameLib.CreateTex(_T("PauseFrame"), _T("2DTextures/Pause/pause_textframe.png"));
	m_rGameLib.CreateTex(_T("PauseEffect"), _T("2DTextures/Pause/RedFrame.png"));
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
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.43f, m_WND_SIZE.m_y * 0.083f, 0.f };

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
