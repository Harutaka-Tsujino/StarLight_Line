/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef STAGE_PROGRESS_H
#define STAGE_PROGRESS_H

#include <windows.h>
#include <tchar.h>

#include <array>

#include "../../Obj.h"
#include "../ADV/ADV.h"
#include "../StarManager/StarManager.h"
#include "../Player/Player.h"
#include "../MainSceneObject.h"

class StageProgress :public Obj
{
public:
	StageProgress() :Obj(OT_TRANSPARENCY, 0.0f)
	{
		m_pObjs[0] = static_cast<Obj*>(new PlayerLifeFrame());
		m_pObjs[1] = static_cast<Obj*>(new PlayerScoreFrame());
		m_pObjs[2] = static_cast<Obj*>(new PlayerClearStarObj());

		m_pStarManager = new StarManager();
		m_pADV = new ADV(m_pStarManager->GetStageTime_ms());
		m_pPlayer = new Player();
	}

	~StageProgress()
	{
		delete m_pPlayer;
		delete m_pADV;
		delete m_pStarManager;

		for (auto i : m_pObjs)
		{
			delete i;
		}
	}

	VOID Update();

	VOID Render();

private:
	StageProgress & operator=(const StageProgress&) = delete;
	StageProgress(const StageProgress&) = delete;

	ADV* m_pADV					= nullptr;
	StarManager* m_pStarManager = nullptr;
	Player* m_pPlayer			= nullptr;

	std::array<Obj*, 3> m_pObjs;
};

#endif // !STAGE_PROGRESS_H
