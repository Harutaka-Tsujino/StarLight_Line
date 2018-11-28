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

	//色の設定
	D3DXVECTOR4 ScoreColor(ColorMax, 0x87 / ColorMax, 0xCE / ColorMax, 0xFA / ColorMax);

	rEnemyStar.SetEmissive(&ScoreColor);

	m_rGameLib.Render(rEnemyStar, MatWorld);
}
