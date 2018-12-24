#include "PlayerResultData.h"

VOID PlayerResultData::Init()
{
	m_rGameLib.CreateTex(_T("Num"), _T("2DTextures/Main/Nums.png"));
	
	m_Data.m_score = 0;
	m_Data.m_clearStarsNum = 0;

	//スコアの描画矩形と一桁目の生成
	m_ScoreFont.push_back(new CustomVertex[4]);
	m_ScoreDigit.push_back(1);

	//クリアスターの数字矩形と一桁目の生成
	m_ClearStarNumsFont.push_back(new CustomVertex[4]);
	m_ClearStarNumsDigit.push_back(1);
}

VOID PlayerResultData::Update()
{
	const FLOAT PLAYER_RADIUS = 20.f;
	const FLOAT ENEMY_RADIUS  = 25.f;

	if (m_rGameCollision.HitSomething(_T("Player"), SCORE, PLAYER_RADIUS, ENEMY_RADIUS))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitBlue"));

		const INT BASIC_POINT = 100;

		m_Data.m_score += BASIC_POINT;
	}

	if (m_rGameCollision.HitSomething(_T("Player"), CLEAR, PLAYER_RADIUS, ENEMY_RADIUS))
	{
		m_rGameLib.StopSound(_T("HitGreen"));
		m_rGameLib.OneShotSimultaneousSound(_T("HitGreen"));

		const INT BONUS_POINT = 500;

		m_Data.m_score += BONUS_POINT;
		++m_Data.m_clearStarsNum;
	}

	//スコアとクリアスターの数字を増やす処理
	for (int i = 0;i < 2;++i)
	{
		IncreaseDigit(i);
	}
}

VOID PlayerResultData::Render()
{
	//スコアの数字描画
	for (int i = 0;i != m_ScoreDigit.size();++i)
	{
		ObjData Data;
		int DigitNum = (m_Data.m_score / m_ScoreDigit[i]) % 10;		//桁ごとに数字を分ける

		Data.m_center = { m_WND_SIZE.m_x * (0.83f - 0.015f * i) , m_WND_SIZE.m_y * 0.9f , 0.0f };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.01f , m_WND_SIZE.m_y * 0.04f , 0.f };

		DisplayNum(&Data.m_texUV, DigitNum);

		m_rGameLib.CreateRect(m_ScoreFont[i], Data);

		m_rGameLib.Render(m_ScoreFont[i], m_rGameLib.GetTex(_T("Num")));
	}

	//クリアスターの数字描画
	for (int i = 0;i != m_ClearStarNumsDigit.size();++i)
	{
		ObjData Data;
		int DigitNum = (m_Data.m_clearStarsNum / m_ScoreDigit[i]) % 10;		//桁ごとに数字を分ける

		Data.m_center = { m_WND_SIZE.m_x * (0.555f - 0.015f * i) , m_WND_SIZE.m_y * 0.9f , 0.0f };
		Data.m_halfScale = { m_WND_SIZE.m_x * 0.01f , m_WND_SIZE.m_y * 0.03f , 0.f };

		DisplayNum(&Data.m_texUV, DigitNum);

		m_rGameLib.CreateRect(m_ScoreFont[i], Data);

		m_rGameLib.Render(m_ScoreFont[i], m_rGameLib.GetTex(_T("Num")));
	}
}

VOID PlayerResultData::DisplayNum(TexUV* UV, const INT& Num)
{
	const FLOAT NUMS_ILLUST_SCALE = 32.0f;
	const INT NUMS_NUM_IN_ROW = 8;
	const INT NUMS_NUM_IN_COLUMN = 2;

	UV->m_startTU = NUMS_ILLUST_SCALE * (Num % NUMS_NUM_IN_ROW) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW);
	UV->m_startTV = NUMS_ILLUST_SCALE * (Num / NUMS_NUM_IN_ROW) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN);
	UV->m_endTU   = NUMS_ILLUST_SCALE * ((Num % NUMS_NUM_IN_ROW) + 1) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_ROW);
	UV->m_endTV   = NUMS_ILLUST_SCALE * ((Num / NUMS_NUM_IN_ROW) + 1) / (NUMS_ILLUST_SCALE * NUMS_NUM_IN_COLUMN);
}

VOID PlayerResultData::IncreaseDigit(const INT& Type)
{
	const INT INCREASE_BY_DIGIT = 10;

	switch (Type)
	{
	case 0:
		{
			INT Num = m_ScoreDigit[m_ScoreDigit.size() - 1];

			INT NextDigit = Num * INCREASE_BY_DIGIT;

			if (m_Data.m_score < NextDigit) return;

			m_ScoreFont.push_back(new CustomVertex[4]);

			m_ScoreDigit.push_back(NextDigit);
		}

		break;

	case 1:
		{
			INT Num = m_ClearStarNumsDigit[m_ClearStarNumsDigit.size() - 1];

			INT NextDigit = Num * INCREASE_BY_DIGIT;

			if (m_Data.m_clearStarsNum < NextDigit) return;

			m_ClearStarNumsFont.push_back(new CustomVertex[4]);

			m_ClearStarNumsDigit.push_back(NextDigit);
		}
		break;
	}
}

VOID PlayerResultData::Release()
{
	for (CustomVertex* pI : m_ScoreFont)
	{
		delete[] pI;
		pI = nullptr;
	}

	m_ScoreDigit.clear();
	m_ScoreFont.clear();

	for (CustomVertex* pI : m_ClearStarNumsFont)
	{
		delete[] pI;
		pI=nullptr;
	}

	m_ClearStarNumsDigit.clear();
	m_ClearStarNumsFont.clear();
}
