﻿#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <windows.h>

#include <vector>

#include "../../Singleton/Singleton.h"
#include "../IBaseWorking.h"
#include "Scene\Scene.h"
#include "Scene\Enum\SCENE_KIND.h"
#include "Scene\TitleScene\TitleScene.h"
#include "../../../GameLib/GameLib.h"
#include "../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"
#include "Struct\StageData.h"
#include "Struct\ResultData.h"

class SceneManager :public IBaseWorking, public Singleton<SceneManager>
{
public:
	friend class Singleton<SceneManager>;

	~SceneManager()
	{
		delete m_pScene;
	}

	inline VOID Update()
	{
		if (m_isRequestedChangeResent) return;

		m_pScene->Update();
	}

	inline VOID Render()
	{
		m_pScene->Render();

		StageTransition();
	}

	inline VOID SetCurrentScene(SCENE_KIND currentScene)
	{
		m_currentScene = currentScene;
	}

	inline VOID SetNextScene(SCENE_KIND nextScene)
	{
		m_nextScene = nextScene;

		m_isRequestedChangeResent = TRUE;
	}

	VOID Factory();

	inline BOOL LatterTransitionStagingIsEnded()
	{
		if(!m_transitionStagingAlpha || m_isRequestedChangeResent) return TRUE;

		return FALSE;
	}

	inline VOID SetStageData(StageData stageData)
	{
		m_stageData = stageData;
	}

	inline VOID SetResultData(ResultData resultData)
	{
		m_resultData = resultData;
	}

	inline VOID GetStageData(StageData* pStageData) const
	{
		*pStageData = m_stageData;
	}

	inline VOID GetResultData(ResultData* pResultData) const
	{
		*pResultData = m_resultData;
	}

private:
	SceneManager() 
	{
		m_pScene = new TitleScene();
	}

	VOID StageTransition();

	Scene* m_pScene = nullptr;

	SCENE_KIND m_currentScene	= SK_TITLE;
	SCENE_KIND m_nextScene		= SK_TITLE;

	BOOL m_isRequestedChangeResent = FALSE;

	INT m_transitionStagingAlpha = 0;

	StageData m_stageData;
	ResultData m_resultData;
};

#endif // !SCENE_MANAGER_H
