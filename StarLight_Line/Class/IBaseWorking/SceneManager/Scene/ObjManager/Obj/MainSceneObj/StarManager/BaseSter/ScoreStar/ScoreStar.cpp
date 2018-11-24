#include "ScoreStar.h"

VOID ScoreStar::Init()
{
	InitBaseStar();
}

VOID ScoreStar::Update()
{
	m_rGameLib.SetEndTime();
	FollingStarPosYTime(m_rGameLib.GetMilliSecond());
}

VOID ScoreStar::Render()
{
	//m_pGameManager->SetTransForm();

	DefaultLight();

	D3DXMATRIX MatWorld;
	
	ConvertLocalToWorld(&MatWorld);

	//FbxRelated* pModel = m_FBXStorage->GetFBX(_T("StarFBX"));

	////F‚ÌÝ’è
	//D3DXVECTOR4 ScoreColor(ColorMax / ColorMax, 0 / ColorMax, 0 / ColorMax, ColorMax / ColorMax);

	//pModel->SetEmissive(&ScoreColor);

	//m_pGameManager->Render(pModel, &MatWorld);
}
