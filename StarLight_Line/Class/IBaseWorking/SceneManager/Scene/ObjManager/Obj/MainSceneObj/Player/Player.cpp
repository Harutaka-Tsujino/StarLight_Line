#include "Player.h"

VOID Player::Init()
{
	count = 0;
	m_PlayerPoint.x = m_MAXXARRAYNUM / 2;
	m_PlayerPoint.y = m_MAXYARRAYNUM / 2;
	m_Speed.x = m_Speed.y = 0.0f;
	m_PlayerPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;	//真ん中に自機を置く
	m_PlayerPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;
	m_PlayerPos.z = 0.2f;

	m_rGameCollision.ResiterPlayerPoint(_T("Player"), &m_PlayerPos);
}

VOID Player::Update()
{
	CoordinatePoint PlayerPointBuffer = m_PlayerPoint;
	HIT_KEY HitKey;

	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	m_Score.Update();
	m_Hp.Update();

	//キー入力によってプレイヤーの動きを決める
	//y座標の移動
	if (UpKeyIsPressed() &&
		*pPoY > 0)
	{
		HitKey = UP;
	}

	if (DownKeyIsPressed() &&
		*pPoY < (m_MAXYARRAYNUM - 1))
	{
		HitKey = DOWN;
	}

	//x座標の移動
	if (LeftKeyIsPressed() &&
		*pPoX > 0)
	{
		HitKey = LEFT;
	}

	if (RightKeyIsPressed() &&
		*pPoX < (m_MAXXARRAYNUM - 1))
	{
		HitKey = RIGHT;
	}
	
	DecideSpeed(&PlayerPointBuffer, HitKey);
	RestrictedMoving();

	//難易度で設定するスコアを変える
	//いま難易度のスコアをもらう処理が出来てないからとりあえず10に設定
	ObtainScoreToExist(10);
}

VOID Player::Render()
{
	m_rGameLib.SetCameraTransform();
	
	m_Score.Render();
	m_Hp.Render();

	D3DXMATRIX MatTrans, MatScale,MatRotate;
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.007f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);

	D3DXMatrixMultiply(&m_World, &m_World, &MatScale);

	static ULONGLONG deg = 0;
	deg += 2;
	D3DXMatrixRotationZ(&MatRotate, D3DXToRadian(deg));
	D3DXMatrixMultiply(&m_World, &m_World, &MatRotate);

	++deg;
	D3DXMatrixRotationX(&MatRotate, D3DXToRadian(deg));
	D3DXMatrixMultiply(&m_World, &m_World, &MatRotate);

	// 移動
	D3DXMatrixTranslation(&MatTrans, m_PlayerPos.x, m_PlayerPos.y, m_PlayerPos.z);

	D3DXMatrixMultiply(&m_World, &m_World, &MatTrans);

	D3DXVECTOR4 EiwiEmissive(0.0f, 170.0f / 255.0f, 160.0f / 255.0f, 0.0f);
	rEiwi.SetAmbient(&EiwiEmissive);

	rEiwi.SetPower(0.5f);
	
	D3DXVECTOR4 VertexColor(160.0f, 255.0f, 255.0f, 255.0f);
	rEiwi.SetColor(&VertexColor);

	m_rGameLib.Render(rEiwi, m_World, m_rGameLib.GetTex(_T("PlayerTex")));
}

//名前不安なので募集中
//プレイヤーの動きを制限する関数
VOID Player::RestrictedMoving()
{
	SurfaceCoordinate NextPos;
	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	NextPos.y = m_BasePos[*pPoY][*pPoX].y;
	NextPos.x = m_BasePos[*pPoY][*pPoX].x;

	//動かす
	m_PlayerPos.x += m_Speed.x;
	m_PlayerPos.y += m_Speed.y;

	//制限をかける
	if (m_Speed.x > 0)
	{
		m_PlayerPos.x = min(NextPos.x, m_PlayerPos.x);

		return;
	}

	m_PlayerPos.x = max(NextPos.x, m_PlayerPos.x);

	if (m_Speed.y > 0)
	{
		m_PlayerPos.y = min(NextPos.y, m_PlayerPos.y);

		return;
	}

	m_PlayerPos.y = max(NextPos.y, m_PlayerPos.y);
}

VOID Player::DecideSpeed(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey)
{
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

	const float FRAMENUM = 15.f;	//何フレームで割るか(自機のスピードの)

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

VOID Player::ObtainScoreToExist(const INT& LevelScore)
{
	if (m_Hp.GetHP() <= 0) return;

	if (count <= 60)
	{
		count++;
	}

	if (count == 60)
	{
		m_Score.SetScore(LevelScore);
		count = 0;
	}
}
