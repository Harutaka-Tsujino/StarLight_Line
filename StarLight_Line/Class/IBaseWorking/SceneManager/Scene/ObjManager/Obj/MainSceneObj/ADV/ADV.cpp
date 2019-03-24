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
#include "../../../../StageSelectScene/Enum/STAGE_KIND.h"

const TCHAR* ADV::GetTextPath()
{
	StageData stageData;
	SceneManager::GetInstance().GetStageData(&stageData);

	//return _T("StageData/Chapter/TAURUS.txt");	//現在このファイルしかないので

	switch (stageData.m_stage)
	{
	case STAGE_TAURUS:
		return _T("StageData/Chapter/TAURUS.txt");

	case STAGE_LIBRA:
		return _T("StageData/Chapter/LIBRA.txt");

	case STAGE_VIRGO:
		return _T("StageData/Chapter/VIRGO.txt");

	case STAGE_ARIES:
		return _T("StageData/Chapter/ARIES.txt");

	case STAGE_GEMINI:
		return _T("StageData/Chapter/GEMINI.txt");

	case STAGE_SCORPIUS:
		return _T("StageData/Chapter/SCORPIUS.txt");

	case STAGE_PISCORPIUS:
		return _T("StageData/Chapter/PISCORPIUS.txt");

	case STAGE_LEO:
		return _T("StageData/Chapter/LEO.txt");

	case STAGE_CAPRICORNUS:
		return _T("StageData/Chapter/CAPRICORNUS.txt");

	case STAGE_AQUARIUS:
		return _T("StageData/Chapter/AQUARIUS.txt");

	case STAGE_SAGITTARIUS:
		return _T("StageData/Chapter/SAGITTARIUS.txt");

	case STAGE_CANCER:
		return _T("StageData/Chapter/CANCER.txt");

	case STAGE_BLACK_HOLE:
		return _T("StageData/Chapter/BLACKHOLE.txt");
	}

	return nullptr;
}
