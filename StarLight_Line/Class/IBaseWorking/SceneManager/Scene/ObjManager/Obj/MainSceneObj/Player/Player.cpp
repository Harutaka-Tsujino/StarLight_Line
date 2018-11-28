#include "Player.h"

VOID Player::Init()
{
	m_PlayerPoint.x = m_MAXXARRAYNUM / 2;
	m_PlayerPoint.y = m_MAXYARRAYNUM / 2;
	m_Speed.x = m_Speed.y = 0.0f;
	m_PlayerPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;	//�^�񒆂Ɏ��@��u��
	m_PlayerPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;
}

VOID Player::Update()
{
	static CoordinatePoint PlayerPointBuffer = m_PlayerPoint;

	HIT_KEY HitKey;

	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	//�L�[���͂ɂ���ăv���C���[�̓��������߂�
	//y���W�̈ړ�
	if (m_rGameLib.KeyboardIsPressed(DIK_W) &&
		*pPoY > 0)
	{
		HitKey = UP;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_S) &&
		*pPoY < (m_MAXYARRAYNUM - 1))
	{
		HitKey = DOWN;
	}

	//x���W�̈ړ�
	if (m_rGameLib.KeyboardIsPressed(DIK_A) &&
		*pPoX > 0)
	{
		HitKey = LEFT;
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_D) &&
		*pPoX < (m_MAXXARRAYNUM - 1))
	{
		HitKey = RIGHT;
	}
	
	DecideSpeed(&PlayerPointBuffer, HitKey);
	RestrictedMoving(PlayerPointBuffer);
}

VOID Player::Render()
{
	m_rGameLib.SetCameraTransform();
	
	D3DXMATRIX MatWorld, MatTrans, MatScale;
	D3DXMatrixIdentity(&MatWorld);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.007f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	// �g��
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);

	// �|�����킹
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatScale);

	// �ړ�
	D3DXMatrixTranslation(&MatTrans, m_PlayerPos.x, m_PlayerPos.y, 0.2f);

	// �|�����킹
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTrans);

	D3DXVECTOR4 EiwiEmissive(1.0f, 1.0f, 1.0f, 0.0f);
	rEiwi.SetEmissive(&EiwiEmissive);

	m_rGameLib.Render(rEiwi, MatWorld, m_rGameLib.GetTex(_T("PlayerTex")));
}

//���O�s���Ȃ̂ŕ�W��
//�v���C���[�̓����𐧌�����֐�
VOID Player::RestrictedMoving(const CoordinatePoint& PrevPoint)
{
	SurfaceCoordinate PrevPos, NextPos;
	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	PrevPos.x = m_BasePos[PrevPoint.y][PrevPoint.x].x;
	PrevPos.y = m_BasePos[PrevPoint.y][PrevPoint.x].y;

	NextPos.y = m_BasePos[*pPoY][*pPoX].y;
	NextPos.x = m_BasePos[*pPoY][*pPoX].x;

	//������
	m_PlayerPos.x += m_Speed.x;
	m_PlayerPos.y += m_Speed.y;

	//������������
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

VOID Player::DecideSpeed(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey)
{
	const float FRAMENUM = 5.f;	//���t���[���Ŋ��邩(���@�̃X�s�[�h��)

	memcpy(PrevPoint, &m_PlayerPoint, sizeof(CoordinatePoint));

	switch (HitKey)
	{
	case UP:
		--m_PlayerPoint.y;
		break;

	case DOWN:
		++m_PlayerPoint.y;
		break;

	case LEFT:
		--m_PlayerPoint.x;
		break;

	case RIGHT:
		++m_PlayerPoint.x;
		break;
	}

	if (HitKey == UP || HitKey == DOWN)
	{
		m_Speed.y = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y - m_PlayerPos.y) / FRAMENUM;
		m_Speed.x = 0.0f;
	}

	if (HitKey == LEFT || HitKey == RIGHT)
	{
		m_Speed.x = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x - m_PlayerPos.x) / FRAMENUM;
		m_Speed.y = 0.0f;
	}

}
