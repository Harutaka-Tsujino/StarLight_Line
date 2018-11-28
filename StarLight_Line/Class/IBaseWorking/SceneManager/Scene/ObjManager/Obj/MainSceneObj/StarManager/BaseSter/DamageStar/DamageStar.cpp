#include"DamageStar.h"

VOID DamageStar::Update()
{
	m_rGameLib.SetEndTime();
	PosOfStarYCoordinate(m_rGameLib.GetMilliSecond());
}

VOID DamageStar::Render()
{
	DefaultLight();

	D3DXMATRIX MatWorld;

	ConvertLocalToWorld(&MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//êFÇÃê›íË
	D3DXVECTOR4 DamageColor(ColorMax, ColorMax, ColorMax, ColorMax);
	rEnemyStar.SetEmissive(&DamageColor);

	m_rGameLib.Render(rEnemyStar, MatWorld);
}

VOID DamageStar::Init()
{
	InitBaseStar();
}

DamageStar::~DamageStar()
{
}