#include "ScoreStar.h"

VOID ScoreStar::Render()
{
	if (ShouldCulling()) return;

	ConvertLocalToWorld(&m_MatWorld);

	//色の設定
	static const D3DXVECTOR4 SCORE_COLOR(250.0f/ColorMax, 0x87 / ColorMax, 0xCE / ColorMax, 0xFA / ColorMax);
	m_rEnemyStar.SetEmissive(&SCORE_COLOR);

	m_rGameLib.Render(m_rEnemyStar, m_MatWorld);
}
