#include "Player.h"

VOID Player::Init()
{
	DefaultLight();

	m_rGameLib.CreateFbx(_T("Eiwi"), "3DModels/Eiwi/Eiwi.fbx");

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

		m_ResultData.JudgeGameFailure(8);	//引数はクリアの星の数
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

VOID Player::ObtainScoreToExist(const INT& LevelScore)
{
	if (m_Hp.GetHP() <= 0) return;

	int Score = 0;

	switch (LevelScore)
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
