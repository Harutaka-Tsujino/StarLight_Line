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
	DefaultLight();

	D3DXMATRIX MatWorld;
	
	ConvertLocalToWorld(&MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//êFÇÃê›íË
	D3DXVECTOR4 ScoreColor(ColorMax / ColorMax, 0 / ColorMax, 0 / ColorMax, ColorMax / ColorMax);

	rEnemyStar.SetEmissive(&ScoreColor);

	m_rGameLib.Render(rEnemyStar, MatWorld);
}
