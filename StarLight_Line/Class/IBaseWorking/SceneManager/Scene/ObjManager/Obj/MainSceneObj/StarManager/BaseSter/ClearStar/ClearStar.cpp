#include "ClearStar.h"

VOID ClearStar::Render()
{
	if (ShouldCulling()) return;

	ConvertLocalToWorld(&m_MatWorld);

	//色の設定
	static const D3DXVECTOR4 CLEAR_COLOR(ColorMax / ColorMax, 0x98 / ColorMax, 0xFB / ColorMax, 0x98 / ColorMax);
	m_rEnemyStar.SetEmissive(&CLEAR_COLOR);

	m_rGameLib.Render(m_rEnemyStar, m_MatWorld);
}
