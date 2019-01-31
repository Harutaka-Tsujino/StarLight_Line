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

#include "../../Obj.h"
#include "../ADV/ADV.h"
#include "../StarManager/StarManager.h"
#include "../Player/Player.h"

class StageProgress :public Obj
{
public:
	StageProgress() :Obj(OT_TRANSPARENCY, 0.0f)
	{
		m_pStarManager = new StarManager();
		m_pADV = new ADV(m_pStarManager->GetStageTime_ms());
		m_pPlayer = new Player();
	}

	~StageProgress()
	{
		delete m_pPlayer;
		delete m_pADV;
		delete m_pStarManager;
	}

	inline VOID Update()
	{
		m_pADV->Update();

		if (m_pADV->IsActive())
		{
			return;
		}

		m_pStarManager->Update();
		m_pPlayer->Update();
	}

	inline VOID Render()
	{
		m_pADV->Render();

		if (m_pADV->IsActive())
		{
			return;
		}

		m_pStarManager->Render();
		m_pPlayer->Render();
	}

private:
	StageProgress & operator=(const StageProgress&) = delete;
	StageProgress(const StageProgress&) = delete;

	ADV* m_pADV					= nullptr;
	StarManager* m_pStarManager = nullptr;
	Player* m_pPlayer			= nullptr;
};

#endif // !STAGE_PROGRESS_H
