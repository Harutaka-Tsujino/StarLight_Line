#ifndef STAR_MANAGER_H_
#define STAR_MANAGER_H_

#include <vector>

#include "../../Obj.h"
#include "../GameCollision/GameCollision.h"
#include "../Enum/STAR_TYPE.h"
#include "BaseSter/BaseStar.h"

class BaseStar;
struct StarPlace;

class StarManager:public Obj
{
public:
	StarManager() :Obj(OT_TRANSPARENCY, 0.5f), m_rGameCollision(GameCollision::GetInstance())
	{
		LoadStarData("StageData/Stage.csv");
		m_rGameLib.CreateFbx(_T("StarFBX"), "3DModels/EnemyStar/EnemyStar.fbx");

		Init();
	}

	~StarManager();

	VOID Init();
	VOID Update();
	VOID Render();

private:
	VOID LoadStarData(const char* pFileName);
	VOID Create(const STAR_TYPE& Kind);
	VOID StarDataToAssign(const int& rArrayNum, const StarPlace& rStarInfo);
	VOID SetStar_ms(const std::vector<float>& rDropPerMinuteVec, StarPlace* pStarInfo);

	std::vector<BaseStar*> m_StarNotes;
	GameCollision& m_rGameCollision;

	BOOL m_Init;			//敵座標のPosを登録するために使う

	LONGLONG m_End_ms = 0;	//総再生時間(ms)
};

#endif // !STAR_MANAGER_H_
