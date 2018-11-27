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

/**
*@brief �G�̐��̗����Ă��鎞�Ԃ�ݒ肷��֐�
*/
VOID BaseStar::FallStarPosYTime()
{
	//���̗����n�߂鎞�� = (((���ߐ� * ����) + n������) * fps) / 1���Ԃɗ����Ă��鐯�̌�
	m_Info.m_Time = (((m_Info.m_Division * 4) + m_Info.m_StarsNumInDivision) * 60.f) / m_Info.m_DropPerMinute;
}

VOID BaseStar::PosOfStarYCoordinate(const LONGLONG& CurrentTime)
{
	//����y���W =�@�����n�߂鎞��(ms) - (���̎���(�b) / 1000)
	m_Info.m_Pos.y = m_Info.m_Time - (CurrentTime / 1000.f);
}

VOID BaseStar::SetStarInfo(const struct StarPlace& StarPlace)
{
	m_Info = StarPlace;
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

	const float MODELSCALE = 0.0005f;

	// �g��
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);

	// �|�����킹
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatScale);

	m_Info.m_Pos.x = m_Info.m_Pos.x / 300.f;
	m_Info.m_Pos.y = m_Info.m_Pos.y / 100.f;

	// �ړ�
	D3DXMatrixTranslation(&MatTrans, m_Info.m_Pos.x, m_Info.m_Pos.y, 0.01f);

	// �|�����킹
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &MatTrans);
}
