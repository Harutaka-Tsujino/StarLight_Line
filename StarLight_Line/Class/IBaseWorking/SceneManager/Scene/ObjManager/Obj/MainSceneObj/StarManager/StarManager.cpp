#include "StarManager.h"

#include<fstream>
#include<sstream>
#include<algorithm>

#include "BaseSter/DamageStar/DamageStar.h"
#include "BaseSter/ScoreStar/ScoreStar.h"
#include "BaseSter/ClearStar/ClearStar.h"

VOID StarManager::Init()
{
	m_rGameLib.SetStartTime();

	m_Init = TRUE;

	for (BaseStar* pI : m_StarNotes)
	{
		pI->Init();
	}
}

VOID StarManager::Update()
{
	for (BaseStar* pI : m_StarNotes)
	{
		pI->Update();
	}
}

VOID StarManager::Render()
{
	m_rGameLib.SetCameraTransform();

	for (BaseStar* pI : m_StarNotes)
	{
		pI->Render();
	}

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
		
		SetStarMMsec(DropPerMinute, &StarInfo);

		StarDataToAssign(cnt, StarInfo);

		cnt++;
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

	m_StarNotes.push_back(pBase);
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

	m_rGameLib.ReleaseTex();
}

VOID StarManager::SetStarMMsec(const std::vector<float>& rDropPerMinuteVec, StarPlace* pStarInfo)
{
	const INT BEATS_NUM_IN_MEASURE = 4;

	const FLOAT SEC_TO_MMSEC_MULTI = 1000.0f;
	const FLOAT MINUTE_TO_MMSEC = 60.0f * SEC_TO_MMSEC_MULTI;

	FLOAT formarBPM = 0;

	LONGLONG* pStartMMSec = &pStarInfo->m_Time;
	*pStartMMSec = 0;

	for (INT i = 0; i < pStarInfo->m_Measure - 1; ++i)
	{
		formarBPM = rDropPerMinuteVec[i];
		*pStartMMSec += static_cast<LONGLONG>((BEATS_NUM_IN_MEASURE / formarBPM) * BEATS_NUM_IN_MEASURE * MINUTE_TO_MMSEC);
	}

	const FLOAT ONE_BEATS_TAKES_MMSEC = (BEATS_NUM_IN_MEASURE / pStarInfo->m_DropPerMinute) * MINUTE_TO_MMSEC;

	*pStartMMSec += static_cast<LONGLONG>(ONE_BEATS_TAKES_MMSEC * (pStarInfo->m_Beat - 1));

	*pStartMMSec += static_cast<LONGLONG>(ONE_BEATS_TAKES_MMSEC * (0.5f / pStarInfo->m_StarsNumInNote));				//! 第一ラインは半ラインずれた位置にある
	*pStartMMSec += static_cast<LONGLONG>(ONE_BEATS_TAKES_MMSEC * (pStarInfo->m_Line / pStarInfo->m_StarsNumInNote));	//! ゲームが始まった瞬間に星が流れるのでずらす
}
