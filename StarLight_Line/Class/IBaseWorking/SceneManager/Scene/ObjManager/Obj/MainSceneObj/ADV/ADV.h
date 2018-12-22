/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef ADV_H
#define ADV_H

#include <windows.h>
#include <tchar.h>

#include "../../Obj.h"
#include "../../../../../Data/StageData.h"
#include "../../../../../SceneManager.h"
#include "Chapter\Chapter.h"

class ADV :public Obj
{
public:
	ADV() :Obj(OT_TRANSPARENCY, 0.0f)
	{
		SceneManager& rSceneManager = SceneManager::GetInstance();

		StageData stageData;
		rSceneManager.GetStageData(&stageData);

		//m_pChapter = new Chapter(stageData)
	}

	~ADV()
	{
		delete m_pChapter;
	}

	inline VOID Update()
	{
		m_pChapter->Update();
	}

	inline VOID Render()
	{
		m_pChapter->Render();
	}

private:
	ADV & operator=(const ADV&) = delete;
	ADV(const ADV&) = delete;

	Chapter* m_pChapter = nullptr;
};

#endif //! ADV_H
