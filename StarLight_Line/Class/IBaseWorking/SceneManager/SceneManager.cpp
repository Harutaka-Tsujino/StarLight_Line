#include "SceneManager.h"

#include <windows.h>

#include "Scene\Scene.h"
#include "Scene\Enum\SCENE_KIND.h"
#include "Scene\TitleScene\TitleScene.h"
#include "Scene\StageSelectScene\StageSelectScene.h"
#include "Scene\SaveDataScene\SaveDataScene.h"
#include "Scene\MainScene\MainScene.h"
#include "Scene\ResultScene\ResultScene.h"
#include "Scene\EndScene\EndScene.h"
#include "Scene\PauseScene\PauseScene.h"

VOID SceneManager::Factory()
{
	if (m_currentScene == m_nextScene || m_isRequestedChangeResent) return;

	TurnOffBGM();
	InitBGM();
	TurnOnBGM();

	m_currentScene = m_nextScene;
	SafeRelease(&m_pSubScene);

	switch (m_nextScene)
	{
	case SK_TITLE:
		delete m_pScene;

		m_pScene = new TitleScene();

		break;

	case SK_GAME:
		if (!m_CanTransferSubScene)
		{
			delete m_pScene;
		
			m_pScene = new MainScene();
			return;
		}

		break;

	case SK_PAUSE:
		m_pSubScene = new PauseScene();

		break;

	case SK_STAGE_SELECT:
		delete m_pScene;

		m_pScene = new StageSelectScene();

		break;

	case SK_SAVE_DATA:
		delete m_pScene;

		m_pScene = new SaveDataScene();

		break;

	case SK_RESULT:
		delete m_pScene;

		m_pScene = new ResultScene();

		break;
		
	case SK_END:
		delete m_pScene;

		m_pScene = new EndScene();

		break;

	default:
		break;
	}
}

VOID SceneManager::StageTransition()
{
	GameLib& rGameLib = GameLib::GetInstance();

	ObjData data;
	const RectSize WND_SIZE = rGameLib.GetWndSize();
	data.m_center		= { WND_SIZE.m_x * 0.5f, WND_SIZE.m_y * 0.5f, 0.0f };
	data.m_halfScale	= { WND_SIZE.m_x * 0.5f, WND_SIZE.m_y * 0.5f, 0.0f };

	m_transitionStagingAlpha += 4 * ((m_isRequestedChangeResent) ? 1 : -1);

	if (m_transitionStagingAlpha >= 255)
	{
		m_transitionStagingAlpha = 255;

		m_isRequestedChangeResent = FALSE;
	}

	if (m_transitionStagingAlpha <= 0) m_transitionStagingAlpha = 0;

	data.m_aRGB = D3DCOLOR_ARGB(static_cast<UCHAR>(m_transitionStagingAlpha), 0, 0, 0);

	if (m_SceneTransitionMode)
	{
		rGameLib.AddtionBlendMode();
		data.m_aRGB = D3DCOLOR_ARGB(static_cast<UCHAR>(m_transitionStagingAlpha), 255, 255, 255);

	}
	
	CustomVertex cover[4];
	rGameLib.CreateRect(cover, data);

	rGameLib.Render(cover);

	rGameLib.DefaultBlendMode();
}

VOID SceneManager::InitBGM()
{
	const TCHAR* pBGM_PATH[SK_MAX] =
	{
		_T("Sounds/Title/titlesave.mp3")	,
		_T("Sounds/StageSelect/Stage.mp3")	,
		_T("Sounds/Stage/Leo/leo.mp3")		,
		_T("Sounds/Title/titlesave.mp3")	,
		_T("Sounds/Result/result.mp3")		,
		_T("Sounds/Title/titlesave.mp3")	,
	};

	static BOOL bGMInits[SK_MAX] =
	{
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
	};

	if (bGMInits[m_nextScene]) return;

	bGMInits[m_nextScene] = TRUE;

	GameLib& rGameLib = GameLib::GetInstance();

	rGameLib.AddSoundFile(pBGM_PATH[m_nextScene], m_pBGM_KEY[m_nextScene]);
}
