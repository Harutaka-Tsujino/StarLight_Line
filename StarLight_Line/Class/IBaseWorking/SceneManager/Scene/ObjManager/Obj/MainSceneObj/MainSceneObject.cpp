#include "MainSceneObject.h"

#include "../../../../../../../GameLib/Wnd/Data/RectSize.h"

VOID MainBack::Init()
{
	m_rGameLib.CreateTex(_T("Back"), _T("2DTextures/Main/main_back01.png"));
}

VOID MainBack::Render()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, m_Z };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("Back")));
}

VOID PlayerLifeFrame::Init()
{
	m_rGameLib.CreateTex(_T("HpMax"), _T("2DTextures/Main/main_life.png"));
}

VOID PlayerLifeFrame::Render()
{
	m_rGameLib.SetCameraTransform();

	D3DXVECTOR3 Center, HalfScale;
	Center = { m_WND_SIZE.m_x * 0.25f, m_WND_SIZE.m_y * 0.9f, m_Z };
	HalfScale = { m_WND_SIZE.m_x * 0.25f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	TexUV UV;
	UV.m_endTV = 74.f / 512.f;

	CustomVertex PlayerLifeBack[4];
	m_rGameLib.CreateRect(PlayerLifeBack, Center, HalfScale,
		0xFFFFFFFF, UV.m_startTU, UV.m_startTV, UV.m_endTU, UV.m_endTV);

	m_rGameLib.Render(PlayerLifeBack, m_rGameLib.GetTex(_T("HpMax")));
}

VOID PlayerScoreFrame::Init()
{
	m_rGameLib.CreateTex(_T("ScoreFrame"), _T("2DTextures/Main/main_scoreframe.png"));
}

VOID PlayerScoreFrame::Render()
{
	m_rGameLib.SetCameraTransform();

	ObjData data;
	data.m_center = { m_WND_SIZE.m_x * 0.75f, m_WND_SIZE.m_y * 0.9f, 0.005f };
	data.m_halfScale = { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.05f, 0.0f };

	CustomVertex back[4];
	m_rGameLib.CreateRect(back, data);

	m_rGameLib.Render(back, m_rGameLib.GetTex(_T("ScoreFrame")));
}

VOID PlayerScore::Init()
{
	m_rGameLib.CreateTex(_T("Num"), _T("2DTextures/Main/Nums.png"));
	m_Score = 0;
	m_ScoreFont.push_back(new CustomVertex[4]);
	m_Digit.push_back(1);
}

VOID PlayerScore::Update()
{
	SearchDigitIncreasedAndCreateNewDigit();
}

VOID PlayerScore::Render()
{
	for (int i = 0;i != m_Digit.size();++i)
	{
		ObjData Data;
		int Buff = (m_Score / m_Digit[i]) % 10;

		Data.m_center = { m_WND_SIZE.m_x * (0.75f - 0.015f * i) , m_WND_SIZE.m_y * 0.9f , 0.0f };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.01f , m_WND_SIZE.m_y * 0.04f , 0.f };

		DisplayNum(&Data.m_texUV, Buff);

		m_rGameLib.CreateRect(m_ScoreFont[i], Data);

		m_rGameLib.Render(m_ScoreFont[i], m_rGameLib.GetTex(_T("Num")));
	}
}

VOID PlayerScore::DisplayNum(TexUV* UV, const INT& Num)
{
	const FLOAT NUMS_ILLUST_SCALE = 32.0f;
	const INT NUMS_NUM_IN_ROW = 8;
	const INT NUMS_NUM_IN_COLUMN = 2;
	const INT NUM_MAX = 10;

	UV->m_startTU = NUMS_ILLUST_SCALE * (Num % NUMS_NUM_IN_ROW)		  / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW);
	UV->m_startTV = NUMS_ILLUST_SCALE * (Num / NUMS_NUM_IN_ROW)		  / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN);
	UV->m_endTU	=	NUMS_ILLUST_SCALE *	((Num % NUMS_NUM_IN_ROW) + 1) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW);
	UV->m_endTV	=	NUMS_ILLUST_SCALE *	((Num / NUMS_NUM_IN_ROW) + 1) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN);
}

VOID PlayerScore::SearchDigitIncreasedAndCreateNewDigit()
{
	const INT INCREASE_BY_DIGIT = 10;

	if (m_Score < m_Digit[m_Digit.size() - 1] * INCREASE_BY_DIGIT) return;

	m_ScoreFont.push_back(new CustomVertex[4]);
	
	INT Num = m_Digit[m_Digit.size() - 1];

	INT NextDigit = Num * INCREASE_BY_DIGIT;
	m_Digit.push_back(NextDigit);
}

VOID PlayerScore::Release()
{
	for (int i = 0;i != m_ScoreFont.size();++i)
	{
		delete m_ScoreFont[i];
	}

	m_Digit.clear();
	m_ScoreFont.clear();
}
