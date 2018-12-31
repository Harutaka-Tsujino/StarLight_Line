#ifndef DATA_SAVER_H
#define DATA_SAVER_H

#include <windows.h>
#include <tchar.h>

#include<fstream>
#include<sstream>
#include<algorithm>

#include "../../../../../../Singleton/Singleton.h"
#include "../../../../SceneManager.h"
#include "../../../../Data/StageData.h"
#include "../../../../Data/ResultData.h"
#include "../../../StageSelectScene/Data/StageDetailData.h"
#include "../../../StageSelectScene/Enum/STAGE_KIND.h"
#include "../../../StageSelectScene/Enum/STAGE_LEVEL_KIND.h"
#include "../../../SaveDataScene/Data/PreviewData.h"

class DataSaver :public Singleton<DataSaver>
{
public:
	friend class Singleton<DataSaver>;

	~DataSaver() 
	{
		for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
		{
			delete m_previews[i].pLastPlayTm;
		}
	}

	VOID LoadData(INT dataNum);

	VOID LoadPreviews();

	VOID Save();

	inline const PreviewData* GetPreviewDatas()
	{
		LoadPreviews();

		return m_previews;
	}

	inline const StageDetailData* GetStageDetailData(INT stageNum,INT level) const
	{
		const StageDetailData* pSTAGE_DETAIL = (stageNum == STAGE_BLACK_HOLE) ?
												&m_extraStageDetail[level - SLK_HARD] :
												&m_basicStageDetails[stageNum][level];

		return pSTAGE_DETAIL;
	}

private:
	struct SaveData
	{
	public:
		time_t m_totalTime_partHour = NULL;
		time_t m_totalTime_partMin	= NULL;

		time_t m_endTimeToPlayTime_s = NULL;

		time_t m_playStartSysTime = NULL;

		tm* pLastPlayTm = nullptr;
	};

	DataSaver() {};

	VOID OpenSelectedSaveData(std::ifstream* pIfs);
	VOID OpenSelectedSaveData(std::ofstream* pOfs);

	VOID LoadTime(std::ifstream* pIfs);

	VOID LoadStageData(std::ifstream* pIfs);

	VOID SaveTime(std::ofstream* pOfs);
	VOID UpdateStageDetail();

	VOID SingleOutMaxScoreAndStars();

	SaveData m_saveData;

	static const INT m_SAVE_DATAS_MAX = 3;
	PreviewData m_previews[m_SAVE_DATAS_MAX];

	const CHAR m_SEPARATOR = ',';

	static const INT m_BASIC_STAGES_MAX = STAGE_MAX - 1;
	static const INT m_BASIC_LEVELS_MAX = SLK_MAX - 1;
	StageDetailData m_basicStageDetails[m_BASIC_STAGES_MAX][m_BASIC_LEVELS_MAX];

	static const INT m_EXTRA_LEVELS_MAX = 2;
	StageDetailData m_extraStageDetail[m_EXTRA_LEVELS_MAX];

	INT m_currentDataNum = NULL;
};

#endif // !DATA_SAVER_H
