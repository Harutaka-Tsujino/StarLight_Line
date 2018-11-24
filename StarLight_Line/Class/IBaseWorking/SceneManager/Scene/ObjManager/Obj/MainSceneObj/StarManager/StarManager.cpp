#include "StarManager.h"

#include<fstream>
#include<sstream>
#include<algorithm>

#include "BaseSter/DamageStar/DamageStar.h"
#include "BaseSter/ScoreStar/ScoreStar.h"

VOID StarManager::Init()
{
	for (int i = 0;i != m_StarNotes.size();++i)
	{
		(static_cast<BaseStar*>(m_StarNotes[i]))->Init();
	}
}

VOID StarManager::Update()
{
	for (int i = 0;i != m_StarNotes.size();++i)
	{
		(static_cast<BaseStar*>(m_StarNotes[i]))->Update();
	}
}

VOID StarManager::Render()
{
	for (int i = 0;i != m_StarNotes.size();++i)
	{
		(static_cast<BaseStar*>(m_StarNotes[i]))->Render();
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
		pBase = (BaseStar*)new DamageStar();
		m_StarNotes.push_back(pBase);

		break;

	case 2:
		pBase = (BaseStar*)new ScoreStar();
		m_StarNotes.push_back(pBase);

		break;
	}
}

VOID StarManager::StarDataToAssign(const int& rArrayNum,const StarPlace& rStarPlace)
{
	((BaseStar*)m_StarNotes[rArrayNum])->SetStarInfo(rStarPlace);
	((BaseStar*)m_StarNotes[rArrayNum])->PosOfStarYCoordinate();
}

StarManager::~StarManager()
{

}
