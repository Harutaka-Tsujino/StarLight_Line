/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#include "ADV.h"

#include <windows.h>

#include "../../../../../SceneManager.h"

ADV::ADV(const LONGLONG& stageTime_ms) :Obj(OT_TRANSPARENCY, 0.0f)
{
	StageData stageData;
	SceneManager::GetInstance().GetStageData(&stageData);

	m_pChapter = new Chapter(_T("Chapter01.txt"), stageTime_ms);
}
