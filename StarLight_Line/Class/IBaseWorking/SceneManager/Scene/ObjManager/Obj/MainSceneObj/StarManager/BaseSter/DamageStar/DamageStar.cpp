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

	/*D3DXMatrixMultiply(&MatWorld, &MatWorld, m_pGameManager->GetCameraViewMatrix());

	D3DXMatrixMultiply(&MatWorld, &MatWorld, m_pGameManager->GetCameraProjectionMatrix());*/

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//êFÇÃê›íË
	D3DXVECTOR4 DamageColor(ColorMax / ColorMax, ColorMax*0.8f / ColorMax, ColorMax*0.8f / ColorMax, ColorMax*0.8f / ColorMax);
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