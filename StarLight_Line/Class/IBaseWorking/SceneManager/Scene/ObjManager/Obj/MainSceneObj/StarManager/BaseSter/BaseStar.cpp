#include "BaseStar.h"

VOID BaseStar::Init()
{
}

VOID BaseStar::Render()
{
}

VOID BaseStar::Update()
{
}

VOID BaseStar::TransScreenPosByTime(const LONGLONG& CurrentTime)
{
	const INT BEATS_NUM_IN_MEASURE = 4;

	const FLOAT SEC_TO__ms_MULTI = 1000.0f;
	const FLOAT MINUTE_TO__ms = 60.0f * SEC_TO__ms_MULTI;

	LONGLONG gap_ms = CurrentTime - m_Info.m_Time;
	if (gap_ms < 0) return;

	FLOAT oneNoteTakes_ms = (1.0f / m_Info.m_DropPerMinute) * MINUTE_TO__ms;

	m_Info.m_Pos.y = m_WND_SIZE.m_y * (gap_ms / oneNoteTakes_ms);

	m_Info.m_Pos.x = m_Info.m_Pos.y * tan(D3DXToRadian(-m_Info.m_XMovementDeg)) + m_Info.m_screenXBasePos;
}

VOID BaseStar::SetStarInfo(const struct StarPlace& StarPlace)
{
	m_Info = StarPlace;
}

VOID BaseStar::DefaultLight()
{
	D3DXVECTOR3 vecDirection(-0.5f, -0.5f, -1.0f);
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;

	light.Diffuse.r = 0.8f;
	light.Diffuse.g = 0.8f;
	light.Diffuse.b = 0.8f;

	light.Ambient.r = 0.5f;
	light.Ambient.b = 0.5f;
	light.Ambient.g = 0.5f;

	light.Specular.r = 0.5f;
	light.Specular.b = 0.5f;
	light.Specular.g = 0.5f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);

	m_rGameLib.SetLight(light, 0);
}

VOID BaseStar::ConvertLocalToWorld(D3DXMATRIX* pMatWorld)
{
	if (m_Info.m_Pos.y < -m_STAR_HALF_SCALE || m_Info.m_Pos.y > m_WND_SIZE.m_y + m_STAR_HALF_SCALE) return;

	D3DXMATRIX MatTrans, MatScale, MatRotate;
	D3DXMatrixIdentity(pMatWorld);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.003f;

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatScale);

	// 演出用の回転
	D3DXMatrixRotationZ(&MatRotate, D3DXToRadian(m_DegZ));
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatRotate);

	++m_DegZ;

	m_Info.m_Pos.z = 0.9f;

	D3DXVECTOR3 ScreenBuff = m_Info.m_Pos;
	m_Info.m_CollisionPos = ScreenBuff;

	D3DXVECTOR3 WorldBuff;
	WorldBuff = m_rGameLib.TransWorld(ScreenBuff);

	// 移動
	D3DXMatrixTranslation(&MatTrans, WorldBuff.x, WorldBuff.y, WorldBuff.z);
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatTrans);

	m_rGameLib.SetCameraTransform();
}
