#include "StarManager.h"

#include<fstream>
#include<sstream>
#include<algorithm>

#include "../../../../../SceneManager.h"
#include "BaseSter/DamageStar/DamageStar.h"
#include "BaseSter/ScoreStar/ScoreStar.h"
#include "BaseSter/ClearStar/ClearStar.h"
#include "../../../../../SceneManager.h"
#include "../../../../Enum/SCENE_KIND.h"

VOID StarManager::Init()
{
	m_rGameLib.SetStartTime();

	m_Init = TRUE;
	m_isFirstFrame = TRUE;
	m_ResumesGame = TRUE;

	for (BaseStar* pI : m_StarNotes)
	{
		pI->Init();
	}

	m_rGameLib.CreateTex(_T("ProgressBar"), _T("2DTextures/Main/ProgressBar.png"));
}

VOID StarManager::Update()
{
	SceneManager& rSceneManager = SceneManager::GetInstance();
	
	if (rSceneManager.LatterTransitionStagingIsEnded())
	{
		if (!m_ResumesGame)
		{
			m_rGameLib.RestartTime();

			m_ResumesGame = TRUE;
		}

		if (m_End_ms <= m_rGameLib.GetMilliSecond())
		{
			m_Ends = TRUE;

			if (rSceneManager.GetIsTutorial()) return;

			if (rSceneManager.Get2PlayMode())
			{
				rSceneManager.SetNextScene(SK_2P_RESULT);

				return;
			}

			rSceneManager.SetNextScene(SK_RESULT);

			return;
		}

		for (BaseStar* pI : m_StarNotes)
		{
			pI->Update();
		}

		m_isFirstFrame = FALSE;

		return;
	}

	if(!m_isFirstFrame) m_ResumesGame = FALSE;
}

VOID StarManager::Render()
{
	m_rGameLib.SetCameraPos(0.0f, -2.15f, -1.0f);

	m_rGameLib.SetCameraTransform();

	if (m_Init)
	{
		m_Init = FALSE;

		for (int i = 0;i != m_StarNotes.size();++i)
		{
			m_rGameCollision.ResiterEnemyPoint(
				static_cast<BaseStar*>(m_StarNotes[i])->GetCollisionPos(),
				static_cast<BaseStar*>(m_StarNotes[i])->GetType());
		}
	}

	for (INT sti = SCORE; sti >= DAMAGE; --sti)
	{
		for (INT i = 0; i < m_StarNotes.size(); ++i)
		{
			if (sti != m_StarNotes[i]->GetType()) continue;

			if (m_rGameCollision.GetStarIsCollided(i)) continue;

			m_StarNotes[i]->Render();
		}
	}

	RenderProgressBar();
}

const CHAR* StarManager::GetStageFilePath()
{
	StageData stageData;
	SceneManager::GetInstance().GetStageData(&stageData);

	switch (stageData.m_stage)
	{
	case STAGE_TAURUS:
		return "StageData/TAURUS.csv";

	case STAGE_LIBRA:
		return "StageData/LIBRA.csv";

	case STAGE_VIRGO:
		return "StageData/VIRGO.csv";

	case STAGE_ARIES:
		return "StageData/ARIES.csv";

	case STAGE_GEMINI:
		return "StageData/GEMINI.csv";

	case STAGE_SCORPIUS:
		return "StageData/SCORPIUS.csv";

	case STAGE_PISCORPIUS:
		return "StageData/PISCORPIUS.csv";

	case STAGE_LEO:
		return "StageData/LEO.csv";

	case STAGE_CAPRICORNUS:
		return "StageData/CAPRICORNUS.csv";

	case STAGE_AQUARIUS:
		return "StageData/AQUARIUS.csv";

	case STAGE_SAGITTARIUS:
		return "StageData/SAGITTARIUS.csv";

	case STAGE_CANCER:
		return "StageData/CANCER.csv";

	case STAGE_BLACK_HOLE:
		return "StageData/BLACKHOLE.csv";
	}

	return nullptr;
}

VOID StarManager::LoadStarData(const char* pFileName)
{
	std::ifstream ifs(pFileName);
	std::string str;

	static int cnt;
	cnt = 0;

	getline(ifs, str);

	int Measures = atoi(str.data());
	std::vector<float> DropPerMinute;

	for (int i = 0;i < Measures;++i)
	{
		getline(ifs, str);
		DropPerMinute.push_back(static_cast<float>(atof(str.data())));
	}

	//ファイルにあるゲームに必要のない情報のから読みをする
	getline(ifs, str);
	replace(str.begin(), str.end(), ',', ' ');
	std::stringstream starsNumsStream(str);

	int starsNums = 0;

	for (int i = 0; i < 3; ++i)
	{
		int starsNum = 0;

		starsNumsStream >> starsNum;

		starsNums += starsNum;
	}

	m_StarNotes.resize(starsNums, nullptr);

	while (getline(ifs, str))
	{
		replace(str.begin(), str.end(), ',', ' ');
		std::stringstream stream(str);

		int Kind;
		stream >> Kind;

		Create(static_cast<STAR_TYPE>(Kind));

		StarPlace StarInfo;
		StarInfo.m_Type = static_cast<STAR_TYPE>(Kind);

		stream >>
			StarInfo.m_Measure >>
			StarInfo.m_Beat >>
			StarInfo.m_StarsNumInNote >>
			StarInfo.m_Line >>
			StarInfo.m_screenXBasePos >>
			StarInfo.m_XMovementDeg;

		StarInfo.m_DropPerMinute = DropPerMinute[StarInfo.m_Measure - 1];
		
		SetStar_ms(DropPerMinute, &StarInfo);

		StarDataToAssign(cnt, StarInfo);

		cnt++;
	}

	const INT BEATS_NUM_IN_MEASURE = 4;

	const FLOAT SEC_TO__ms_MULTI = 1000.0f;
	const FLOAT MINUTE_TO__ms = 60.0f * SEC_TO__ms_MULTI;

	for (auto i : DropPerMinute)
	{
		m_End_ms += static_cast<LONGLONG>(BEATS_NUM_IN_MEASURE / i * MINUTE_TO__ms);
	}
}

VOID StarManager::Create(const STAR_TYPE& Kind)
{
	BaseStar* pBase = nullptr;

	switch (Kind)
	{
	case DAMAGE:
		pBase = static_cast<BaseStar*>(new DamageStar());

		break;

	case SCORE:
		pBase = static_cast<BaseStar*>(new ScoreStar());

		break;

	case CLEAR:
		pBase = static_cast<BaseStar*>(new ClearStar());

		break;
	}

	m_StarNotes[m_starCountToLoad] = pBase;

	++m_starCountToLoad;
}

VOID StarManager::StarDataToAssign(const int& rArrayNum,const StarPlace& rStarPlace)
{
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->SetStarInfo(rStarPlace);
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->SetType(rStarPlace.m_Type);
}

StarManager::~StarManager()
{
	for (auto i : m_StarNotes)
	{
		delete i;
	}
	m_StarNotes.clear();

	m_rGameCollision.ReleaseEnemyPoint();

	m_rGameLib.ReleaseTex();
}

VOID StarManager::SetStar_ms(const std::vector<float>& rDropPerMinuteVec, StarPlace* pStarInfo)
{
	const INT BEATS_NUM_IN_MEASURE = 4;

	const FLOAT SEC_TO__ms_MULTI = 1000.0f;
	const FLOAT MINUTE_TO__ms = 60.0f * SEC_TO__ms_MULTI;

	FLOAT formarBPM = 0;
	
	LONGLONG* pStart_ms = &pStarInfo->m_Time;
	*pStart_ms = m_WAITING_TIME_ms;

	for (INT i = 0; i < pStarInfo->m_Measure - 1; ++i)
	{
		formarBPM = rDropPerMinuteVec[i];
		*pStart_ms += static_cast<LONGLONG>((BEATS_NUM_IN_MEASURE / formarBPM) * MINUTE_TO__ms);
	}

	const FLOAT ONE_BEATS_TAKES__ms = (1 / pStarInfo->m_DropPerMinute) * MINUTE_TO__ms;

	*pStart_ms += static_cast<LONGLONG>(ONE_BEATS_TAKES__ms * (pStarInfo->m_Beat - 1));

	*pStart_ms += static_cast<LONGLONG>(ONE_BEATS_TAKES__ms * (0.5f / pStarInfo->m_StarsNumInNote));	//! 第一ラインは半ラインずれた位置にある
	*pStart_ms += static_cast<LONGLONG>(ONE_BEATS_TAKES__ms * ((pStarInfo->m_Line - 1) / pStarInfo->m_StarsNumInNote));
}

VOID StarManager::RenderProgressBar()
{
	if (!m_rGameLib.GetTimeIsStoped())
	{
		m_progressRatio = static_cast<FLOAT>(m_rGameLib.GetMilliSecond()) / m_End_ms;
	}

	ObjData barData;
	barData.m_center	  = { m_WND_SIZE.m_x * 0.5f * m_progressRatio, m_WND_SIZE.m_y * 0.975f, m_Z };
	barData.m_halfScale	  = { m_WND_SIZE.m_x * 0.5f * m_progressRatio, m_WND_SIZE.m_y * 0.01125f, 0.0f };

	CustomVertex bar[4];
	m_rGameLib.CreateRect(bar, barData);

	m_rGameLib.SetTopBottomARGB(bar, 0xEEFFFF99, 0xEECCFF99);

	static INT frashCnt = 0;
	m_rGameLib.FlashRect(bar, &frashCnt, 120, 240, 160);

	m_rGameLib.Render(bar);

	ObjData frameData;
	frameData.m_center	  = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.975f, m_Z };
	frameData.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.025f, 0.0f };

	frameData.m_aRGB = 0xCCFFFFFF;

	m_rGameLib.CreateAndRenderRect(frameData, m_rGameLib.GetTex(_T("ProgressBar")));
}
