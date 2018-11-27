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
	m_rGameLib.SetCameraTransform();
	
	D3DXMATRIX MatWorld, MatTrans, MatScale;
	D3DXMatrixIdentity(&MatWorld);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float ModelScale = 0.007f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	// 拡大
	D3DXMatrixScaling(&MatScale, ModelScale, ModelScale, ModelScale);

	// 掛け合わせ
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatScale);

	// 移動
	D3DXMatrixTranslation(&MatTrans, m_PlayerPos.x, m_PlayerPos.y, 0.2f);

	// 掛け合わせ
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTrans);

	D3DXVECTOR4 EiwiEmissive(1.0f, 1.0f, 1.0f, 0.0f);
	rEiwi.SetEmissive(&EiwiEmissive);

	m_rGameLib.Render(rEiwi, MatWorld, m_rGameLib.GetTex(_T("PlayerTex")));
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