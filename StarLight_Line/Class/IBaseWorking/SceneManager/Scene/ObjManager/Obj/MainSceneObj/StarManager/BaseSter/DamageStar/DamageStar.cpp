#include"DamageStar.h"

VOID DamageStar::Render()
{
	if (ShouldCulling()) return;

	ConvertLocalToWorld(&m_MatWorld);

	//色の設定
	static const D3DXVECTOR4 DAMAGE_COLOR(ColorMax / ColorMax, ColorMax / ColorMax, ColorMax / ColorMax, ColorMax / ColorMax);
	m_rEnemyStar.SetEmissive(&DAMAGE_COLOR);

	m_rGameLib.Render(m_rEnemyStar, m_MatWorld);
}
