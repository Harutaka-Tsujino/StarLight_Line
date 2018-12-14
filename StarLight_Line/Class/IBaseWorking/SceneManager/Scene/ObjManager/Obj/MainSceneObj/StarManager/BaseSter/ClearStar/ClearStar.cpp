#include "ClearStar.h"

VOID ClearStar::Init()
{
	
}

VOID ClearStar::Update()
{
	m_rGameLib.SetEndTime();
	PosOfStarYCoordinate(m_rGameLib.GetMilliSecond());
}

VOID ClearStar::Render()
{
	DefaultLight();

	ConvertLocalToWorld(&m_MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 ClearColor(ColorMax, 0x98 / ColorMax, 0xFB / ColorMax, 0x98 / ColorMax);

	rEnemyStar.SetEmissive(&ClearColor);

	m_rGameLib.Render(rEnemyStar, m_MatWorld);
}
