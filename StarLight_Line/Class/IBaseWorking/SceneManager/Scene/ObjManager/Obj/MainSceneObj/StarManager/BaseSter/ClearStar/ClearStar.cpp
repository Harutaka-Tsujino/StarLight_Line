#include "ClearStar.h"

VOID ClearStar::Init()
{
	//ConvertLocalToWorld(&m_MatWorld);
}

VOID ClearStar::Update()
{
	m_rGameLib.SetEndTime();
	TransScreenPosByTime(m_rGameLib.GetMilliSecond());
}

VOID ClearStar::Render()
{
	DefaultLight();

	if (m_Info.m_CollisionPos.y < -m_STAR_HALF_SCALE || m_Info.m_CollisionPos.y > m_WND_SIZE.m_y + m_STAR_HALF_SCALE) return;

	ConvertLocalToWorld(&m_MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 ClearColor(ColorMax / ColorMax, 0x98 / ColorMax, 0xFB / ColorMax, 0x98 / ColorMax);

	rEnemyStar.SetEmissive(&ClearColor);

	m_rGameLib.Render(rEnemyStar, m_MatWorld);
}
