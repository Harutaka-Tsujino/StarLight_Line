#include "2PResultData.h"

#include <math.h>

#include "../../../ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../../../ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../../../ADV/Chapter/Section/Text/Text.h"

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
	//当たり判定の取り方
	const INT HIT_MODE = 2;

	if (m_rGameCollision.HitSomething(m_PlayerTypeKey, DAMAGE, HIT_MODE))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitWhite"));

		const INT DEMERIT_POINT = -400;

		m_Score += DEMERIT_POINT;
	}

	if (m_rGameCollision.HitSomething(m_PlayerTypeKey, SCORE, HIT_MODE))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitBlue"));

		const INT BASIC_POINT = 200;

		m_Score += BASIC_POINT;
	}

	if (m_rGameCollision.HitSomething(m_PlayerTypeKey, CLEAR, HIT_MODE))
	{
		m_rGameLib.OneShotSimultaneousSound(_T("HitGreen"));

		const INT BONUS_POINT = 2000;

		m_Score += BONUS_POINT;
	}

	if (m_controllerType == Joycon::RIGHT_CONTROLLER)
	{
		m_rGameCollision.DisableEnemyHitForHit();
	}

	//マイナスに行かないようにする
	m_Score = (m_Score < 0) ? 0 : m_Score;
}

VOID TwoPlayerResultData::Render()
{
	INT ScoreDigit = m_Score;

	ScoreDigit = static_cast<int>(log10(ScoreDigit) + 1);

	if (m_Score == 0) ScoreDigit = 1;

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 15, 15 };
	txtFormat.m_charGap = { 10.0f, 0.0f };
	txtFormat.m_topLeft = { 500.f - ScoreDigit * txtFormat.m_charHalfScale.m_x * 2.0f + (630.f * m_controllerType), m_WND_SIZE.m_y * 0.88f };

	TString ScoreNum(m_Score, _T("%d"));
	Text ScoreText(ScoreNum, _T("2DTextures/Fonts/a_9.png"));
	ScoreText.Write(txtFormat);
}
