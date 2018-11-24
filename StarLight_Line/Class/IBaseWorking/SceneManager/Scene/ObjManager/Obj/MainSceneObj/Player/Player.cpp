#include "Player.h"

VOID Player::Init()
{
	m_PlayerPoint.x = m_MaxXArrayNum / 2;
	m_PlayerPoint.y = m_MaxYArrayNum / 2;
	m_Speed.x = m_Speed.y = 0.f;
	m_PlayerPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;	//真ん中に自機を置く
	m_PlayerPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;
}

VOID Player::Update()
{
	const float FrameNum = 5.f;	//何フレームで割るか(自機のスピードの)

	static CoordinatePoint PlayerPointBuffer = m_PlayerPoint;

	//キー入力によってプレイヤーの動きを決める
	//y座標の移動
	if (m_rGameLib.KeyboardIsPressed(DIK_W) &&
		m_PlayerPoint.y > 0)
	{
		memcpy(&PlayerPointBuffer, &m_PlayerPoint, sizeof(CoordinatePoint));
		--m_PlayerPoint.y;
		m_Speed.y = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y - m_PlayerPos.y) / FrameNum;
		m_Speed.x = 0.0f;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_S) &&
		m_PlayerPoint.y < (m_MaxYArrayNum - 1))
	{
		memcpy(&PlayerPointBuffer, &m_PlayerPoint, sizeof(CoordinatePoint));
		++m_PlayerPoint.y;
		m_Speed.y = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y - m_PlayerPos.y) / FrameNum;
		m_Speed.x = 0.0f;
	}

	//x座標の移動
	if (m_rGameLib.KeyboardIsPressed(DIK_A) &&
		m_PlayerPoint.x > 0)
	{
		memcpy(&PlayerPointBuffer, &m_PlayerPoint, sizeof(CoordinatePoint));
		--m_PlayerPoint.x;
		m_Speed.x = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x - m_PlayerPos.x) / FrameNum;
		m_Speed.y = 0.0f;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_D) &&
		m_PlayerPoint.x < (m_MaxXArrayNum - 1))
	{
		memcpy(&PlayerPointBuffer, &m_PlayerPoint, sizeof(CoordinatePoint));
		++m_PlayerPoint.x;
		m_Speed.x = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x - m_PlayerPos.x) / FrameNum;
		m_Speed.y = 0.0f;
	}
	
	CanMovePos(PlayerPointBuffer);
}

VOID Player::Render()
{
	D3DXVECTOR3 vecDirection(-0.5f, -1.0f, -1.0f);
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.5f;
	light.Diffuse.g = 1.5f;
	light.Diffuse.b = 1.5f;

	light.Specular.r = 10.0f;
	light.Specular.b = 10.0f;
	light.Specular.g = 10.0f;

	light.Ambient.r = 10.f;
	light.Ambient.b = 10.f;
	light.Ambient.g = 10.f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);

	m_rGameLib.SetLight(light, 1);
	light.Range = 200.f;

	D3DXMATRIX MatWorld, matTrans, matScale;
	D3DXMatrixIdentity(&MatWorld);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	const float ModelScale = 0.001f;

	// 拡大
	D3DXMatrixScaling(&matScale, ModelScale, ModelScale, ModelScale);

	// 掛け合わせ
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &matScale);

	// 移動
	D3DXMatrixTranslation(&matTrans, m_PlayerPos.x, m_PlayerPos.y, 0.02f);

	// 掛け合わせ
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &matTrans);

	//FbxRelated* pPlayerModel = m_pFBXStorage->GetFBX(_T("Player"));

	//D3DXVECTOR4 EiwiEmissive(0.0f, 0.3f, 0.3f, 0.01f);
	//pPlayerModel->SetEmissive(&EiwiEmissive);


	//m_pGameManager->Render(pPlayerModel, &MatWorld);
}

Player::~Player()
{
}

VOID Player::CanMovePos(const CoordinatePoint& PrevPoint)
{
	SurfaceCoordinate PrevPos, NextPos;

	PrevPos.x = m_BasePos[PrevPoint.y][PrevPoint.x].x;
	PrevPos.y = m_BasePos[PrevPoint.y][PrevPoint.x].y;

	NextPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;
	NextPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;

	m_PlayerPos.x += m_Speed.x;
	m_PlayerPos.y += m_Speed.y;

	if (m_Speed.x > 0)
	{
		m_PlayerPos.x = max(min(NextPos.x, m_PlayerPos.x), PrevPos.x);

		return;
	}

	m_PlayerPos.x = max(min(PrevPos.x, m_PlayerPos.x), NextPos.x);


	if (m_Speed.y > 0)
	{
		m_PlayerPos.y = max(min(NextPos.y, m_PlayerPos.y), PrevPos.y);

		return;
	}

	m_PlayerPos.y = max(min(PrevPos.y, m_PlayerPos.y), NextPos.y);
}