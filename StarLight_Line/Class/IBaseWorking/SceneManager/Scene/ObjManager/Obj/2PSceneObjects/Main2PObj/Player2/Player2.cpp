#include "Player2.h"

VOID PlayerTwo::Init()
{
	m_pTwoPlayerData = new TwoPlayerResultData(_T("PlayerTwo"), m_contrllerType);

	DefaultLight();

	m_rGameLib.CreateFbx(_T("Eiwi"), "3DModels/Eiwi/Eiwi.fbx");

	m_PlayerPoint = { 2,1,1 };
	m_PlayerPos.z = 0.2f;
	m_Speed.x = m_Speed.y = m_Speed.z = 0.0f;
	m_PlayerPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;	
	m_PlayerPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;

	m_rGameCollision.ResiterPlayerPoint(_T("PlayerTwo"), &m_PlayerPos);
}

VOID PlayerTwo::Update()
{
	CoordinatePoint PlayerPointBuffer = m_PlayerPoint;
	HIT_KEY HitKey;

	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	//キー入力によってプレイヤーの動きを決める
	//ジャイロの向きが上下左右反転してるのはコントローラーの都合(右側のみ)
	//y座標の移動
	if ((m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::UP_DIRECTION) ||
		m_rGameLib.InputGyroSensor(m_contrllerType, Joycon::DOWN_DIRECTION)) &&
		*pPoY > 0)
	{
		HitKey = UP;
	}

	if ((m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::DOWN_DIRECTION) ||
		m_rGameLib.InputGyroSensor(m_contrllerType, Joycon::UP_DIRECTION)) &&
		*pPoY < (m_MAXYARRAYNUM - 1))
	{
		HitKey = DOWN;
	}

	//x座標の移動
	if ((m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::LEFT_DIRECTION) ||
		m_rGameLib.InputGyroSensor(m_contrllerType, Joycon::RIGHT_DIRECTION)) &&
		*pPoX > 0)
	{
		HitKey = LEFT;
	}

	if ((m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::RIGHT_DIRECTION) ||
		m_rGameLib.InputGyroSensor(m_contrllerType, Joycon::LEFT_DIRECTION)) &&
		*pPoX < (m_MAXXARRAYNUM - 1))
	{
		HitKey = RIGHT;
	}

	DecideSpeed(&PlayerPointBuffer, HitKey);
	RestrictedMoving();

	m_pTwoPlayerData->Update();
}

VOID PlayerTwo::Render()
{
	D3DXMATRIX MatTrans, MatScale, MatRotate;
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.05f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);
	D3DXMatrixMultiply(&m_World, &m_World, &MatScale);

	static FLOAT deg = 0;
	deg += 1.0f;
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

	m_pTwoPlayerData->Render();
}

VOID PlayerTwo::SetPlayerFbxMaterial()
{
	FLOAT AdditionalColor = 60.0f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	D3DXVECTOR4 EiwiAmbient(0.7f, 255.0f / 255.0f, 0.f/ 255.0f, 0.f / 255.0f);
	rEiwi.SetAmbient(&EiwiAmbient);

	D3DXVECTOR4 EiwiEmissive(0.8f, 255.0f / 255.0f, 0.f / 255.0f, 0.f / 255.0f);
	rEiwi.SetEmissive(&EiwiEmissive);

	rEiwi.SetPower(0.8f);

	D3DXVECTOR4 VertexColor(255.0f, 255.0f, 100.0f, 100.0f);
	rEiwi.SetColor(&VertexColor);
}
