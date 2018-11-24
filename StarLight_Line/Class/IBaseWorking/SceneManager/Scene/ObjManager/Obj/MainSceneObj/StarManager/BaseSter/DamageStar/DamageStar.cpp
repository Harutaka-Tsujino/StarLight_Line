#include"DamageStar.h"

VOID DamageStar::Update()
{
	m_rGameLib.SetEndTime();
	FollingStarPosYTime(m_rGameLib.GetMilliSecond());
}

VOID DamageStar::Render()
{
	//m_pGameManager->SetTransForm();

	DefaultLight();

	D3DXMATRIX MatWorld;

	ConvertLocalToWorld(&MatWorld);

	/*D3DXMatrixMultiply(&MatWorld, &MatWorld, m_pGameManager->GetCameraViewMatrix());

	D3DXMatrixMultiply(&MatWorld, &MatWorld, m_pGameManager->GetCameraProjectionMatrix());*/

	//FbxRelated* pModel = m_FBXStorage->GetFBX(_T("StarFBX"));

	//F‚ÌÝ’è
	/*D3DXVECTOR4 DamageColor(ColorMax / ColorMax, ColorMax*0.8f / ColorMax, ColorMax*0.8f / ColorMax, ColorMax*0.8f / ColorMax);
	pModel->SetEmissive(&DamageColor);

	m_pGameManager->Render(pModel, &MatWorld);*/
}

VOID DamageStar::Init()
{
	InitBaseStar();
}

DamageStar::~DamageStar()
{
}