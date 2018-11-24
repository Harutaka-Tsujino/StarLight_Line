#include "SceneManager.h"

#include <windows.h>

#include "Scene\Scene.h"
#include "Scene\Enum\SCENE_KIND.h"
#include "Scene\TitleScene\TitleScene.h"
#include "Scene\StageSelectScene\StageSelectScene.h"

VOID SceneManager::Factory()
{
	if (m_currentScene == m_nextScene || m_isRequestedChangeResent) return;

	m_currentScene = m_nextScene;

	switch (m_nextScene)
	{
	case SK_TITLE:
		delete m_pScene;

		m_pScene = new TitleScene();

		break;

	case SK_GAME:
		delete m_pScene;

		m_pScene = new TitleScene();

		break;

	case SK_STAGE_SELECT:
		delete m_pScene;

		m_pScene = new StageSelectScene();

	default:
		break;
	}
}
