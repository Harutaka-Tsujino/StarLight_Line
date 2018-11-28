#include "StarManager.h"

#include<fstream>
#include<sstream>
#include<algorithm>

#include "BaseSter/DamageStar/DamageStar.h"
#include "BaseSter/ScoreStar/ScoreStar.h"
#include "BaseSter/ClearStar/ClearStar.h"

VOID StarManager::Init()
{
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
}

VOID StarManager::LoadStarData(const char* pFileName)
{
	std::ifstream ifs(pFileName);
	std::string str;

	static int cnt;
	cnt = 0;

	while (getline(ifs, str))
	{
		replace(str.begin(), str.end(), ',', ' ');
		std::stringstream stream(str);

		int Kind;

		stream >> Kind;

		Create(Kind);

		StarPlace StarInfo;

		stream >> StarInfo.m_DropPerMinute >> StarInfo.m_Division >> StarInfo.m_StarsNumInDivision >> StarInfo.m_Pos.x;

		StarDataToAssign(cnt, StarInfo);

		cnt++;
	}

}

VOID StarManager::Create(const int& rKind)
{
	BaseStar* pBase = nullptr;

	switch (rKind)
	{
	case 1:
		pBase = static_cast<BaseStar*>(new DamageStar());
		m_StarNotes.push_back(pBase);

		break;

	case 2:
		pBase = static_cast<BaseStar*>(new ScoreStar());
		m_StarNotes.push_back(pBase);

		break;

	case 3:
		pBase = static_cast<BaseStar*>(new ClearStar());
		m_StarNotes.push_back(pBase);

		break;
	}
}

VOID StarManager::StarDataToAssign(const int& rArrayNum,const StarPlace& rStarPlace)
{
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->SetStarInfo(rStarPlace);
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->FallStarPosYTime();
}

StarManager::~StarManager()
{

}
