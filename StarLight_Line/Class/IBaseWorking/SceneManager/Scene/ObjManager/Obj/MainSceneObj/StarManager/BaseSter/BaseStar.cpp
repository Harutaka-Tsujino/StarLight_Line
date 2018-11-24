#include "BaseStar.h"

VOID BaseStar::InitBaseStar()
{
	m_rGameLib.SetStartTime();
}

VOID BaseStar::Init()
{
}

VOID BaseStar::Render()
{
}

VOID BaseStar::Update()
{
}

VOID BaseStar::PosOfStarYCoordinate()
{
	m_Info.m_Time = (((m_Info.m_Division * 4) + m_Info.m_StarsNumInDivision) * 60.f) / m_Info.m_DropPerMinute;
}

VOID BaseStar::FollingStarPosYTime(const LONGLONG& rCurrentTime)
{
	m_Info.m_Pos.y = (m_Info.m_Time - rCurrentTime / 1000.f);
}

VOID BaseStar::SetStarInfo(const struct StarPlace& rStarPlace)
{
	m_Info = rStarPlace;
}

VOID BaseStar::DefaultLight()
{
	D3DXVECTOR3 vecDirection(0.01f, 0.05f, 0.3f);
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	light.Specular.r = 1.f;
	light.Specular.b = 1.f;
	light.Specular.g = 1.f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);

	light.Range = 200.f;
	m_rGameLib.SetLight(light, 0);
}

VOID BaseStar::ConvertLocalToWorld(D3DXMATRIX* pMatWorld)
{
	D3DXMATRIX matTrans, matScale;
	D3DXMatrixIdentity(pMatWorld);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	const float ModelScale = 0.0005f;

	// ägëÂ
	D3DXMatrixScaling(&matScale, ModelScale, ModelScale, ModelScale);

	// ä|ÇØçáÇÌÇπ
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &matScale);

	m_Info.m_Pos.x = m_Info.m_Pos.x / 300.f;
	m_Info.m_Pos.y = m_Info.m_Pos.y / 100.f;

	// à⁄ìÆ
	D3DXMatrixTranslation(&matTrans, m_Info.m_Pos.x, m_Info.m_Pos.y, 0.01f);

	// ä|ÇØçáÇÌÇπ
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &matTrans);
}
