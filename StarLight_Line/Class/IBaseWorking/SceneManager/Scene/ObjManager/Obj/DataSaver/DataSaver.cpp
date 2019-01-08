#define _CRT_SECURE_NO_WARNINGS
#include "DataSaver.h"

#include <windows.h>
#include <tchar.h>

#include<fstream>
#include<sstream>
#include<algorithm>
#include <ctime>

#include "../../../../../../Singleton/Singleton.h"
#include "../../../../SceneManager.h"
#include "../../../../Data/StageData.h"
#include "../../../../Data/ResultData.h"
#include "../../../StageSelectScene/Data/StageDetailData.h"
#include "../../../StageSelectScene/Enum/STAGE_KIND.h"
#include "../../../StageSelectScene/Enum/STAGE_LEVEL_KIND.h"
#include "../../../SaveDataScene/Data/PreviewData.h"

VOID DataSaver::LoadData(INT dataNum)
{
	m_currentDataNum = dataNum;
	std::ifstream ifs;
	
	OpenSelectedSaveData(&ifs);

	LoadTime(&ifs);
	
	LoadStageData(&ifs);
}

VOID DataSaver::LoadPreviews()
{
	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		m_currentDataNum = i;

		std::ifstream ifs;

		OpenSelectedSaveData(&ifs);

		PreviewData* pPreviews = &m_previews[i];

		LoadTime(&ifs);
		LoadStageData(&ifs);

		pPreviews->m_totalTime_partHour = static_cast<INT>(m_saveData.m_totalTime_partHour);
		pPreviews->m_totalTime_partMin  = static_cast<INT>(m_saveData.m_totalTime_partMin);

		delete m_previews[i].pLastPlayTm;
		m_previews[i].pLastPlayTm = nullptr;

		tm* lastPlayTime = new tm;
		memcpy(lastPlayTime, m_saveData.pLastPlayTm, sizeof(tm));
		pPreviews->pLastPlayTm = lastPlayTime;

		SingleOutMaxScoreAndStars();
	}
}

VOID DataSaver::Save()
{
	std::ofstream ofs;
	OpenSelectedSaveData(&ofs);

	SaveTime(&ofs);

	UpdateStageDetail();

	auto SaveStageDetail = [&ofs, this](StageDetailData* pStageDetail)
	{
		ofs <<
			pStageDetail->m_score		<< m_SEPARATOR <<
			pStageDetail->m_greenStar	<< m_SEPARATOR <<
			pStageDetail->m_isClear		<< m_SEPARATOR;
	};

	for (INT bsi = 0; bsi < m_BASIC_STAGES_MAX; ++bsi)
	{
		for (INT sli = 0; sli < m_BASIC_LEVELS_MAX; ++sli) SaveStageDetail(&m_basicStageDetails[bsi][sli]);

		ofs << std::endl;
	}

	for (INT sli = 0; sli < m_EXTRA_LEVELS_MAX; ++sli) SaveStageDetail(&m_extraStageDetail[sli]);
}

VOID DataSaver::OpenSelectedSaveData(std::ifstream* pIfs)
{
	switch (m_currentDataNum)
	{
	case 0:
		pIfs->open("SaveData/SaveData1.csv");

		break;

	case 1:
		pIfs->open("SaveData/SaveData2.csv");

		break;

	case 2:
		pIfs->open("SaveData/SaveData3.csv");

		break;

	default:
		break;
	}
}

VOID DataSaver::OpenSelectedSaveData(std::ofstream* pOfs)
{
	switch (m_currentDataNum)
	{
	case 0:
		pOfs->open("SaveData/SaveData1.csv", std::ios::trunc);

		break;

	case 1:
		pOfs->open("SaveData/SaveData2.csv", std::ios::trunc);

		break;

	case 2:
		pOfs->open("SaveData/SaveData3.csv", std::ios::trunc);

		break;

	default:
		break;
	}
}

VOID DataSaver::LoadTime(std::ifstream* pIfs)
{
	std::string str;

	getline(*pIfs, str);
	replace(str.begin(), str.end(), m_SEPARATOR, ' ');
	std::istringstream totalStream(str);
	totalStream >> m_saveData.m_totalTime_partHour >> m_saveData.m_totalTime_partMin;

	getline(*pIfs, str);
	replace(str.begin(), str.end(), m_SEPARATOR, ' ');
	std::istringstream lastPlayStream(str);
	lastPlayStream >> m_saveData.m_endTimeToPlayTime_s;

	time_t currentTime_s = time(nullptr);
	m_saveData.m_playStartSysTime = currentTime_s;

	m_saveData.pLastPlayTm = std::localtime(&currentTime_s);
	ZeroMemory(m_saveData.pLastPlayTm, sizeof(tm));
	m_saveData.pLastPlayTm->tm_year = -1900;

	if (m_saveData.m_endTimeToPlayTime_s) m_saveData.pLastPlayTm = std::localtime(&m_saveData.m_endTimeToPlayTime_s);
}

VOID DataSaver::LoadStageData(std::ifstream* pIfs)
{
	std::string str;

	auto LoadStageDetail = [](std::istringstream* pStream ,StageDetailData* pStageDetail)
	{
		*pStream >> pStageDetail->m_score;
		*pStream >> pStageDetail->m_greenStar;
		*pStream >> pStageDetail->m_isClear;
	};

	for (INT bsi = 0; bsi < m_BASIC_STAGES_MAX; ++bsi)
	{
		getline(*pIfs, str);
		replace(str.begin(), str.end(), m_SEPARATOR, ' ');
		std::istringstream stageStream(str);

		for (INT sli = 0; sli < m_BASIC_LEVELS_MAX; ++sli)
		{
			StageDetailData* pStageDetail = &m_basicStageDetails[bsi][sli];

			LoadStageDetail(&stageStream, pStageDetail);
		}
	}

	getline(*pIfs, str);
	replace(str.begin(), str.end(), m_SEPARATOR, ' ');
	std::istringstream stageStream(str);

	for (INT sli = 0; sli < m_EXTRA_LEVELS_MAX; ++sli)
	{
		StageDetailData* pStageDetail = &m_extraStageDetail[sli];

		LoadStageDetail(&stageStream, pStageDetail);
	}
}

VOID DataSaver::SaveTime(std::ofstream* pOfs)
{
	time_t currentTime_s = time(nullptr);
	time_t playTime_s = currentTime_s - m_saveData.m_playStartSysTime;
	m_saveData.m_playStartSysTime = currentTime_s;

	const INT ONE_HOUR_TO_SECONDS = 3600;
	playTime_s += m_saveData.m_totalTime_partHour * ONE_HOUR_TO_SECONDS;

	const INT ONE_MINUTE_TO_SECONDS = 60;
	playTime_s += m_saveData.m_totalTime_partMin * ONE_MINUTE_TO_SECONDS;

	m_saveData.m_endTimeToPlayTime_s = currentTime_s;

	time_t playTimeHourPart		= playTime_s / ONE_HOUR_TO_SECONDS;
	time_t playTimeMinutePart	= (playTime_s % ONE_HOUR_TO_SECONDS) / ONE_MINUTE_TO_SECONDS;

	*pOfs << playTimeHourPart << m_SEPARATOR << playTimeMinutePart << m_SEPARATOR << std::endl;
	*pOfs << currentTime_s	  << m_SEPARATOR << std::endl;
}

VOID DataSaver::UpdateStageDetail()
{
	SceneManager& rSceneManager = SceneManager::GetInstance();

	StageData stageData;
	rSceneManager.GetStageData(&stageData);

	ResultData resultData;
	rSceneManager.GetResultData(&resultData);

	StageDetailData* pStageDetail = (stageData.m_stage == STAGE_BLACK_HOLE) ?
									 &m_extraStageDetail[stageData.m_level - SLK_HARD] :
									 &m_basicStageDetails[stageData.m_stage][stageData.m_level];

	pStageDetail->m_greenStar = (resultData.m_clearStarsNum > pStageDetail->m_greenStar) ?
								 resultData.m_clearStarsNum : pStageDetail->m_greenStar;

	pStageDetail->m_isClear = (resultData.m_isFailed) ? pStageDetail->m_isClear : TRUE;


	pStageDetail->m_score = (resultData.m_score > pStageDetail->m_score) ?
							 resultData.m_score : pStageDetail->m_score;
}

VOID DataSaver::SingleOutMaxScoreAndStars()
{
	PreviewData* pPreviews = &m_previews[m_currentDataNum];

	for (INT bsi = 0; bsi < m_BASIC_STAGES_MAX; ++bsi)
	{
		for (INT sli = 0; sli < m_BASIC_LEVELS_MAX; ++sli)
		{
			StageDetailData* pStageDetail = &m_basicStageDetails[bsi][sli];

			pPreviews->m_maxScore = max(pPreviews->m_maxScore, pStageDetail->m_score);

			pPreviews->m_clearNum += ((pStageDetail->m_isClear) ? 1 : 0);
		}
	}

	for (INT sli = 0; sli < m_EXTRA_LEVELS_MAX; ++sli)
	{
		StageDetailData* pStageDetail = &m_extraStageDetail[sli];

		pPreviews->m_maxScore = max(pPreviews->m_maxScore, pStageDetail->m_score);

		pPreviews->m_clearNum += ((pStageDetail->m_isClear) ? 1 : 0);
	}
}
