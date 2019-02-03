#ifndef STAR_MANAGER_H_
#define STAR_MANAGER_H_

#include <vector>

#include "../../Obj.h"
#include "../GameCollision/GameCollision.h"
#include "../Enum/STAR_TYPE.h"
#include "../../../../StageSelectScene/Enum/STAGE_KIND.h"
#include "BaseSter/BaseStar.h"
#include "../../../../../SceneManager.h"

class BaseStar;
struct StarPlace;

class StarManager:public Obj
{
public:
	StarManager() :Obj(OT_TRANSPARENCY, 0.5f), m_rGameCollision(GameCollision::GetInstance())
	{
		m_rGameLib.CreateFbx(_T("StarFBX"), "3DModels/EnemyStar/StarNote.fbx");

		const CHAR* pStagePath = ((SceneManager::GetInstance()).GetIsTutorial()) ? "StageData/tutorial.csv" : GetStageFilePath();
		LoadStarData(pStagePath);

		Init();
	}

	~StarManager();

	VOID Init();
	VOID Update();
	VOID Render();

	inline BOOL GetEnds()
	{
		return m_Ends;
	}

	inline const LONGLONG& GetStageTime_ms()
	{
		return m_End_ms;
	}

private:
	VOID RenderProgressBar();

	const CHAR* GetStageFilePath();

	VOID LoadStarData(const char* pFileName);
	VOID Create(const STAR_TYPE& Kind);
	VOID StarDataToAssign(const int& rArrayNum, const StarPlace& rStarInfo);
	VOID SetStar_ms(const std::vector<float>& rDropPerMinuteVec, StarPlace* pStarInfo);

	int m_starCountToLoad = 0;

	std::vector<BaseStar*> m_StarNotes;
	GameCollision& m_rGameCollision;

	BOOL m_Init;			//敵座標のPosを登録するために使う

	BOOL m_isFirstFrame = TRUE;
	BOOL m_ResumesGame = TRUE;

	static const LONGLONG m_WAITING_TIME_ms = 3000;

	LONGLONG m_End_ms = m_WAITING_TIME_ms;	//総再生時間(ms)
	BOOL m_Ends = FALSE;

	FLOAT m_progressRatio = 0;
};

#endif // !STAR_MANAGER_H_
