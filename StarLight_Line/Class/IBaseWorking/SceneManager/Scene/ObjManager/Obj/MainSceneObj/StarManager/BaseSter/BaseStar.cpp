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
	m_Info.m_Time = ((((m_Info.m_Measure - 1) *  (m_Info.m_Beat / 4)) + (m_Info.m_Line / m_Info.m_StarsNumInNote)) * 60.f) / m_Info.m_DropPerMinute;
}

VOID BaseStar::PosOfStarYCoordinate(const LONGLONG& CurrentTime)
{
	//星のy座標 =　落ち始める時間(ms) - (今の時間(秒) / 1200)
	m_Info.m_Pos.y = m_Info.m_Time - (CurrentTime / 1200.f);
}

VOID BaseStar::SetStarInfo(const struct StarPlace& StarPlace)
{
	m_Info = StarPlace;
}

VOID BaseStar::DefaultLight()
{
	D3DXVECTOR3 vecDirection(-1.0f, -0.5f, 1.0f);
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
	D3DXMATRIX MatTrans, MatScale;
	D3DXMatrixIdentity(pMatWorld);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.005f;

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);

	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatScale);

	m_Info.m_Pos.y /= 10.f;
	m_Info.m_Pos.z = 0.2f;

	D3DXVECTOR3 WorldBuff(0.f, m_Info.m_Pos.y, m_Info.m_Pos.z);	//スクリーン変換用バッファ
	D3DXVECTOR3 ScreenBuff;										//ワールド変換用
	ScreenBuff = m_rGameLib.TransScreen(WorldBuff);
	ScreenBuff.x = m_Info.m_Pos.x;	
	m_Info.m_CollisionPos = ScreenBuff;
	WorldBuff = m_rGameLib.TransWorld(ScreenBuff);

	// 移動
	D3DXMatrixTranslation(&MatTrans, WorldBuff.x, WorldBuff.y, m_Info.m_Pos.z);

	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatTrans);
}
