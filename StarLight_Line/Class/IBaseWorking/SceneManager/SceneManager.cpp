#include "SceneManager.h"

#include <windows.h>

#include "Scene\Scene.h"
#include "Scene\Enum\SCENE_KIND.h"
#include "Scene\TitleScene\TitleScene.h"

inline VOID SceneManager::Factory()
{
	if (m_currentScene == m_nextScene)
	{
		return;
	}

	switch (m_nextScene)
	{
	case SK_TITLE:
		m_pScene = new TitleScene();

		break;

	case SK_GAME:
		m_pScene = new TitleScene();

		break;

	default:
		break;
	}
}
