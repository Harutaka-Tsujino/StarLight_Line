#include "StageProgress.h"

VOID StageProgress::Update()
{
	m_pADV->Update();

	if (m_pADV->IsActive())
	{
		return;
	}

	for (auto i : m_pObjs)
	{
		i->Update();
	}

	m_pStarManager->Update();
	m_pPlayer->Update();
}

VOID StageProgress::Render()
{
	m_pADV->Render();

	if (m_pADV->IsActive())
	{
		return;
	}

	for (auto i : m_pObjs)
	{
		i->Render();
	}

	m_pStarManager->Render();
	m_pPlayer->Render();
}
