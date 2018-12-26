#include "ScoreStar.h"

VOID ScoreStar::Render()
{
	DefaultLight();

	if (m_Info.m_CollisionPos.y < -m_STAR_HALF_SCALE || m_Info.m_CollisionPos.y > m_WND_SIZE.m_y + m_STAR_HALF_SCALE) return;
	
	ConvertLocalToWorld(&m_MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 VertexColor(180.0f / ColorMax, 0 / ColorMax, 0 / ColorMax, 0 / ColorMax);
	rEnemyStar.SetDiffuse(&VertexColor);
	rEnemyStar.SetAmbient(&VertexColor);

	D3DXVECTOR4 SpecularColor(180.0f / ColorMax, 80 / ColorMax, 80 / ColorMax, 40 / ColorMax);
	rEnemyStar.SetSpecular(&SpecularColor);
	rEnemyStar.SetPower(1.0f);

	D3DXVECTOR4 ScoreColor(250.0f/ColorMax, 0x87 / ColorMax, 0xCE / ColorMax, 0xFA / ColorMax);
	rEnemyStar.SetEmissive(&ScoreColor);

	m_rGameLib.Render(rEnemyStar, m_MatWorld);
}
