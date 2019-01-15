#include "Player.h"

VOID Player::Init()
{
	DefaultLight();

	count = 0;
	m_PlayerPoint.x = m_MAXXARRAYNUM / 2;
	m_PlayerPoint.y = m_MAXYARRAYNUM / 2;
	m_PlayerPoint.z = 1;
	m_PlayerPos.z = 0.2f;
	m_Speed.x = m_Speed.y = m_Speed.z = 0.0f;
	m_PlayerPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;	//真ん中に自機を置く
	m_PlayerPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;

	SceneManager& rSceneManager = SceneManager::GetInstance();
	rSceneManager.GetStageData(&m_StageData);

	m_rGameCollision.ResiterPlayerPoint(_T("Player"), &m_PlayerPos);
}

VOID Player::Update()
{
	SceneManager& rSceneManager = SceneManager::GetInstance();

	if (m_Hp.GetHP() <= 0 && !rSceneManager.GetIsTutorial())
	{
		rSceneManager.SetTransitionMode(FALSE);

		m_ResultData.JudgeGameFailure(8); //引数は適当
		rSceneManager.SetResultData(m_ResultData.GetResultData());

		rSceneManager.SetNextScene(SK_RESULT);
	}

	if (m_rGameLib.KeyboardIsPressed(DIK_LSHIFT) && !rSceneManager.GetIsTutorial())
	{
		m_rGameLib.StopTime();
		rSceneManager.SetCanTransferSubScene(TRUE);
		rSceneManager.SetNextScene(SK_PAUSE);
	}

	CoordinatePoint PlayerPointBuffer = m_PlayerPoint;
	HIT_KEY HitKey;

	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

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
	ObtainScoreToExist(m_StageData.m_level);

	m_ResultData.Update();
	m_Hp.Update();
}

VOID Player::Render()
{
	D3DXMATRIX MatTrans, MatScale,MatRotate;
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.05f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);
	D3DXMatrixMultiply(&m_World, &m_World, &MatScale);

	static FLOAT deg = 0;
	deg += 1.0f + m_ResultData.GetAdditionalRotateSpeed();
	D3DXMatrixRotationZ(&MatRotate, D3DXToRadian(deg));
	D3DXMatrixMultiply(&m_World, &m_World, &MatRotate);

	deg += 0.5f;
	D3DXMatrixRotationX(&MatRotate, D3DXToRadian(deg));
	D3DXMatrixMultiply(&m_World, &m_World, &MatRotate);

	// 移動
	D3DXMatrixTranslation(&MatTrans, m_PlayerPos.x, m_PlayerPos.y, m_PlayerPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &MatTrans);

	SetPlayerFbxMaterial();

	m_rGameLib.Render(m_rGameLib.GetFbx(_T("Eiwi")), m_World, m_rGameLib.GetTex(_T("PlayerTex")));

	m_ResultData.Render();
	m_Hp.Render();
}

VOID Player::DefaultLight()
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
	m_PlayerPos.x = (m_Speed.x > 0) ? min(NextPos.x, m_PlayerPos.x) : max(NextPos.x, m_PlayerPos.x);
	m_PlayerPos.y = (m_Speed.y > 0) ? min(NextPos.y, m_PlayerPos.y) : max(NextPos.y, m_PlayerPos.y);

	if (NextPos.y == m_PlayerPos.y && NextPos.x == m_PlayerPos.x)
	{
		m_Speed.x = 0.0f;
		m_Speed.y = 0.0f;
	}
}

VOID Player::DecideSpeed(CoordinatePoint* PrevPoint, const HIT_KEY& HitKey)
{
	memcpy(PrevPoint, &m_PlayerPoint, sizeof(CoordinatePoint));

	switch (HitKey)
	{
	case UP:
		if (m_Speed.x) break;

		--m_PlayerPoint.y;

		break;

	case DOWN:
		if (m_Speed.x) break;

		++m_PlayerPoint.y;

		break;

	case LEFT:
		if (m_Speed.y) break;

		--m_PlayerPoint.x;
		break;

	case RIGHT:
		if (m_Speed.y) break;

		++m_PlayerPoint.x;
		break;
	}

	const float FRAMENUM = 15.f;	//何フレームで割るか(自機のスピードの)

	if (HitKey == UP || HitKey == DOWN)
	{
		m_Speed.y = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y - m_PlayerPos.y) / FRAMENUM;

		return;
	}

	if (HitKey == LEFT || HitKey == RIGHT)
	{
		m_Speed.x = (m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x - m_PlayerPos.x) / FRAMENUM;

		return;
	}
}

VOID Player::ObtainScoreToExist(const INT& Level)
{
	if (m_Hp.GetHP() <= 0) return;

	int Score = 0;

	switch (Level)
	{
	case SLK_EASY:
		Score = 10;
		break;

	case SLK_NORMAL:
		Score = 20;
		break;

	case SLK_HARD:
		Score = 30;
		break;
	}

	if (count <= 60)
	{
		count++;
	}

	if (count == 60)
	{
		m_ResultData.SetScore(Score);
		count = 0;
	}
}

VOID Player::DecideColorByHit(FLOAT* pAdditionalColor)
{
	if (m_Hp.GetAdditionalFlashMulti() == -1)
	{
		static BOOL Increases = FALSE;
		static INT AdditionalFlashCount = 0;

		const FLOAT ADDITIONAL_COLOR_MAX = -90.0f;
		const INT ADDITIONAL_FLASH_COUNT_MAX = 20;

		FLOAT AdditionalColorAbs = (ADDITIONAL_COLOR_MAX / ADDITIONAL_FLASH_COUNT_MAX) * AdditionalFlashCount;
		*pAdditionalColor = (Increases) ? -AdditionalColorAbs + ADDITIONAL_COLOR_MAX : AdditionalColorAbs;

		++AdditionalFlashCount;

		if (AdditionalFlashCount >= ADDITIONAL_FLASH_COUNT_MAX)
		{
			AdditionalFlashCount = 0;

			Increases = !Increases;
		}
	}
}

VOID Player::SetPlayerFbxMaterial()
{
	FLOAT AdditionalColor = 60.0f * (m_ResultData.GetAdditionalFlashMulti());
	DecideColorByHit(&AdditionalColor);
	
	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	D3DXVECTOR4 EiwiAmbient(0.7f, (170.0f + AdditionalColor) / 255.0f, (170.0f + AdditionalColor) / 255.0f, (-30.0f + AdditionalColor) / 255.0f);
	rEiwi.SetAmbient(&EiwiAmbient);

	D3DXVECTOR4 EiwiEmissive(0.8f, (150.0f + AdditionalColor) / 255.0f, (130.0f + AdditionalColor) / 255.0f, (-30.0f + AdditionalColor) / 255.0f);
	rEiwi.SetEmissive(&EiwiEmissive);

	rEiwi.SetPower(0.8f);

	D3DXVECTOR4 VertexColor(150.0f, 255.0f, 255.0f, 255.0f);
	rEiwi.SetColor(&VertexColor);
}
