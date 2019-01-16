#include "2PResultData.h"

#include "../../../ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../../../ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../../../ADV/Chapter/Section/Text/NumText/NumText.h"

VOID TwoPlayerResultData::Init()
{
	m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Stage/HitBlueStar.mp3"), _T("HitBlue"));
	m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Stage/HitGreenStar.mp3"), _T("HitGreen"));
	m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Stage/HitWhiteStar.mp3"), _T("HitWhite"));
	m_rGameLib.AddSimultaneousSoundFile(_T("Sounds/Stage/HitLethal.mp3"), _T("HitLethal"));

	m_Score = 0;
}

VOID TwoPlayerResultData::Update()
{
	const FLOAT PLAYER_RADIUS = 20.f;
	const FLOAT ENEMY_RADIUS  = 30.f;

	if (m_rGameCollision.HitSomething(m_PlayerTypeKey, DAMAGE, PLAYER_RADIUS, ENEMY_RADIUS))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitWhite"));

		const INT DEMERIT_POINT = -2000;

		m_Score += DEMERIT_POINT;
	}

	if (m_rGameCollision.HitSomething(m_PlayerTypeKey, SCORE, PLAYER_RADIUS, ENEMY_RADIUS))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitBlue"));

		const INT BASIC_POINT = 200;

		m_Score += BASIC_POINT;
	}

	if (m_rGameCollision.HitSomething(m_PlayerTypeKey, CLEAR, PLAYER_RADIUS, ENEMY_RADIUS))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitGreen"));

		const INT BONUS_POINT = 2000;

		m_Score += BONUS_POINT;
	}

	//マイナスに行かないようにする
	m_Score = (m_Score < 0) ? 0 : m_Score;
}

VOID TwoPlayerResultData::Render()
{
	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 14, 14 };
	txtFormat.m_charGap = { -10.0f, 0.0f };
	txtFormat.m_topLeft = { 150, 175 + 215.0f };

	TString ScoreNum(m_Score, _T("%2d"));
	NumText ScoreText(ScoreNum, _T("2DTextures/Result/Nums.png"));
	ScoreText.Write(txtFormat);
}
