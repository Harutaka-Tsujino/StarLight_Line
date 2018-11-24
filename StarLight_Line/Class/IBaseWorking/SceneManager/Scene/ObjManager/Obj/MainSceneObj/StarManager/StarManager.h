#ifndef STAR_MANAGER_H_
#define STAR_MANAGER_H_

#include <vector>

#include "BaseSter/BaseStar.h"
#include "../../Obj.h"

class BaseStar;
struct StarPlace;

class StarManager:public Obj
{
public:
	StarManager() :Obj(OT_TRANSPARENCY, 0.5f)
	{
		LoadStarData("StageData/otamesi.csv");
		Init();
	}

	~StarManager();

	VOID Init();
	VOID Update();
	VOID Render();

private:
	VOID LoadStarData(const char* pFileName);
	VOID Create(const int &rKind);
	VOID StarDataToAssign(const int& rArrayNum, const StarPlace& rStarInfo);

	std::vector<BaseStar*> m_StarNotes;
};

#endif // !STAR_MANAGER_H_