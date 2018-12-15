#include "ScoreStar.h"

VOID ScoreStar::Init()
{
	
}

VOID ScoreStar::Update()
{
	m_rGameLib.SetEndTime();
	TransScreenPosByTime(m_rGameLib.GetMilliSecond());
}

VOID ScoreStar::Render()
{
	DefaultLight();

	if (m_Info.m_Pos.y < -m_STAR_HALF_SCALE || m_Info.m_Pos.y > m_WND_SIZE.m_y + m_STAR_HALF_SCALE) return;
	
	ConvertLocalToWorld(&m_MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 ScoreColor(ColorMax, 0x87 / ColorMax, 0xCE / ColorMax, 0xFA / ColorMax);

	rEnemyStar.SetEmissive(&ScoreColor);

	m_rGameLib.Render(rEnemyStar, m_MatWorld);
}
