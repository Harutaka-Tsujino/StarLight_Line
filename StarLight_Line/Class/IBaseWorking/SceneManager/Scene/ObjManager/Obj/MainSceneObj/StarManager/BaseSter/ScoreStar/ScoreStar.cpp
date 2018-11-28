#include "ScoreStar.h"

VOID ScoreStar::Init()
{
	InitBaseStar();
}

VOID ScoreStar::Update()
{
	m_rGameLib.SetEndTime();
	PosOfStarYCoordinate(m_rGameLib.GetMilliSecond());
}

VOID ScoreStar::Render()
{
	DefaultLight();

	D3DXMATRIX MatWorld;
	
	ConvertLocalToWorld(&MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//êFÇÃê›íË
	D3DXVECTOR4 ScoreColor(ColorMax, 0.f, 0.f, ColorMax);

	rEnemyStar.SetEmissive(&ScoreColor);

	m_rGameLib.Render(rEnemyStar, MatWorld);
}
