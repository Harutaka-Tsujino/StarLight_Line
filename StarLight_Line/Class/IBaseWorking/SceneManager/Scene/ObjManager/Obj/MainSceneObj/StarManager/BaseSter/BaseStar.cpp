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

/**
*@brief 敵の星の落ちてくる時間を設定する関数
*/
VOID BaseStar::FallStarPosYTime()
{
	//星の落ち始める時間 = (((n小節目 * 拍数) + n分音符) * fps) / 1分間に落ちてくる星の個数
	m_Info.m_Time = ((((m_Info.m_Division - 1) * 4) + m_Info.m_StarsNumInDivision) * 60.f) / m_Info.m_DropPerMinute;
}

VOID BaseStar::PosOfStarYCoordinate(const LONGLONG& CurrentTime)
{
	//星のy座標 =　落ち始める時間(ms) - (今の時間(秒) / 1000)
	m_Info.m_Pos.y = m_Info.m_Time - (CurrentTime / 1000.f);
}

VOID BaseStar::SetStarInfo(const struct StarPlace& StarPlace)
{
	m_Info = StarPlace;
}

VOID BaseStar::DefaultLight()
{
	D3DXVECTOR3 vecDirection(0.f, 0.5f, 1.0f);
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	light.Specular.r = 0.5f;
	light.Specular.b = 0.5f;
	light.Specular.g = 0.5f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);

	m_rGameLib.SetLight(light, 0);
}

VOID BaseStar::ConvertLocalToWorld(D3DXMATRIX* pMatWorld)
{
	D3DXMATRIX MatTrans, MatScale;
	D3DXMatrixIdentity(pMatWorld);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.005f;

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);

	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatScale);

	m_Info.m_Pos.x /= 100.f;
	m_Info.m_Pos.y -= (m_Info.m_DropPerMinute / 3600.f);
	m_Info.m_Pos.z = 0.2f;

	// 移動
	D3DXMatrixTranslation(&MatTrans, m_Info.m_Pos.x, m_Info.m_Pos.y, m_Info.m_Pos.z);

	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatTrans);
}
