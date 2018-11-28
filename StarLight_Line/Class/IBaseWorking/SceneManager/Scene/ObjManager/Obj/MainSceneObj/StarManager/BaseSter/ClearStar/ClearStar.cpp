#include "ClearStar.h"

VOID ClearStar::Init()
{
	InitBaseStar();
}

VOID ClearStar::Update()
{
	m_rGameLib.SetEndTime();
	PosOfStarYCoordinate(m_rGameLib.GetMilliSecond());
}

VOID ClearStar::Render()
{
	DefaultLight();

	D3DXMATRIX MatWorld;

	ConvertLocalToWorld(&MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 ClearColor(ColorMax, 0x98 / ColorMax, 0xFB / ColorMax, 0x98 / ColorMax);

	rEnemyStar.SetEmissive(&ClearColor);

	m_rGameLib.Render(rEnemyStar, MatWorld);
}
