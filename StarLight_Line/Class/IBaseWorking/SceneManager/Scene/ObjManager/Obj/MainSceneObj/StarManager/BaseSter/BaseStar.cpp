#include "BaseStar.h"

VOID BaseStar::Init()
{
	DefaultLight();

	D3DXVECTOR4 VertexColor(180.0f / ColorMax, 0 / ColorMax, 0 / ColorMax, 0 / ColorMax);
	m_rEnemyStar.SetDiffuse(&VertexColor);
	m_rEnemyStar.SetAmbient(&VertexColor);

	D3DXVECTOR4 SpecularColor(180.0f / ColorMax, 80 / ColorMax, 80 / ColorMax, 40 / ColorMax);
	m_rEnemyStar.SetSpecular(&SpecularColor);
	m_rEnemyStar.SetPower(1.0f);
}

VOID BaseStar::Render()
{
}

VOID BaseStar::Update()
{
	TransScreenPosByTime(m_rGameLib.GetMilliSecond());
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
	m_Info.m_Pos.y -= 150.0f;
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
	D3DXMATRIX MatTrans, MatScale, MatRotate;
	D3DXMatrixIdentity(pMatWorld);
	const float MODELSCALE = 0.52f;

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatScale);

	D3DXVECTOR3 cameraPos;
	m_rGameLib.GetCameraPos(&cameraPos);
	FLOAT tan = (cameraPos.z) ? cameraPos.y / cameraPos.z : 0.0f;

	// 演出用の回転
	D3DXMatrixRotationY(&MatRotate, static_cast<FLOAT>(D3DX_PI));
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatRotate);

	D3DXMatrixRotationZ(&MatRotate, static_cast<FLOAT>(D3DXToRadian(m_DegZ)));
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatRotate);

	++m_DegZ;

	m_Info.m_Pos.z = 0.999f;

	D3DXVECTOR3 ScreenBuff = m_Info.m_Pos;
	
	m_rGameLib.SetCameraPos(0.0f, 0.0f, 0.0f);
	m_rGameLib.SetCameraTransform();

	D3DXVECTOR3 WorldBuff;
	WorldBuff = m_rGameLib.TransWorld(ScreenBuff);

	const FLOAT START_Y = 30.0f;

	const FLOAT MOVE_X_MULTI = 1.65f;
	const FLOAT MOVE_Y_MULTI = MOVE_X_MULTI;

	WorldBuff =
	{
		WorldBuff.x * MOVE_X_MULTI,
		WorldBuff.y * MOVE_Y_MULTI + START_Y,
		WorldBuff.z
	};

	// 移動
	D3DXMatrixTranslation(&MatTrans, WorldBuff.x, WorldBuff.y, WorldBuff.z);
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatTrans);

	m_rGameLib.SetCameraPos(cameraPos);
	m_rGameLib.SetCameraTransform();

	m_Info.m_CollisionPos = m_rGameLib.TransScreen(WorldBuff);
}
