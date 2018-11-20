#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <windows.h>

#include <vector>

#include "../../Singleton/Singleton.h"
#include "../IBaseWorking.h"
#include "Scene\Scene.h"
#include "Scene\Enum\SCENE_KIND.h"
#include "Scene\TitleScene\TitleScene.h"

class SceneManager :public IBaseWorking, public Singleton<SceneManager>
{
public:
	~SceneManager()
	{
		delete m_pScene;
	}

	inline VOID Update()
	{
		m_pScene->Update();
	}

	inline VOID Render()
	{
		m_pScene->Render();
	}

	inline VOID SetCurrentScene(SCENE_KIND currentScene)
	{
		m_currentScene = currentScene;
	}

	inline VOID SetNextScene(SCENE_KIND nextScene)
	{
		m_currentScene = nextScene;
	}

private:
	SceneManager() 
	{
		m_pScene = new TitleScene();
	}
	
	inline VOID Factory();

	Scene* m_pScene = nullptr;

	SCENE_KIND m_currentScene	= SK_TITLE;
	SCENE_KIND m_nextScene		= SK_TITLE;
};

#endif // !SCENE_MANAGER_H
