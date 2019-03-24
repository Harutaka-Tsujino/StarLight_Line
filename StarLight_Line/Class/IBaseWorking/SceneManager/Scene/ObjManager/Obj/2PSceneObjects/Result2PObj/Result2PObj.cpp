#include "Result2PObj.h"
#include "../../../../StageSelectScene/Enum/STAGE_KIND.h"
#include "../../../../StageSelectScene/Enum/STAGE_LEVEL_KIND.h"

VOID ResultTwoPlayerBack::TextRender()
{
	TString resultString(_T("RESULT"));

	Text resultText(resultString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 20, 30 };

	//! RESULTの文字数の半分が3
	txtFormat.m_topLeft = { 15.0f, 45.0f };

	resultText.Write(txtFormat);
}

VOID ResultTwoPlayerFrame::FrameRender()
{
	for (int i = 0;i < PLAYER_TYPE_MAX;++i)
	{
		ObjData data;
		data.m_center = { m_WND_SIZE.m_x * (0.25f +(0.25f * (i * 2))), m_WND_SIZE.m_y * 0.6f, m_Z };
		data.m_halfScale = { m_WND_SIZE.m_x * 0.23f, m_WND_SIZE.m_y * 0.38f, 0.0f };

		data.m_aRGB = D3DCOLOR_ARGB(60, 255, 255, 255);

		CustomVertex back[4];
		m_rGameLib.CreateRect(back, data);

		m_rGameLib.Render(back, nullptr);
	}
}

VOID ResultTwoPlayerFrame::PlayerTextRender()
{
	TString OnePlayerString(_T("1P SCORE"));

	Text OnePlayerText(OnePlayerString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txt1pFormat;
	txt1pFormat.m_charHalfScale = { 25, 30 };
	txt1pFormat.m_topLeft = { m_WND_SIZE.m_x * 0.25f - txt1pFormat.m_charHalfScale.m_x * 2.0f * 4.0f, m_WND_SIZE.m_y * 0.25f };
	txt1pFormat.m_color1 = 0xFFFFF462;
	txt1pFormat.m_color2 = 0xFFFFE5E5;
	txt1pFormat.m_gradationType = GT_OBLIQUE_BOTTOM_RIGHT;

	OnePlayerText.Write(txt1pFormat);

	TString TwoPlayerString(_T("2P SCORE"));

	Text TwoPlayerText(TwoPlayerString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txt2PFormat;
	txt2PFormat.m_charHalfScale = { 25, 30 };
	txt2PFormat.m_topLeft = { m_WND_SIZE.m_x * 0.75f - txt2PFormat.m_charHalfScale.m_x * 2.0f * 4.0f , m_WND_SIZE.m_y * 0.25f };
	txt2PFormat.m_color1 = 0xFFC9171E;
	txt2PFormat.m_color2 = 0xFFFFE5E5;
	txt2PFormat.m_gradationType = GT_OBLIQUE_BOTTOM_RIGHT;

	TwoPlayerText.Write(txt2PFormat);
}

VOID ResultTwoPlayerScore::Update()
{
	if (!m_stagingIsEnd) return;

	if (m_rGameLib.PushJoyconButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON))
	{
		m_pushButton[Joycon::LEFT_CONTROLLER] = TRUE;
	}

	if (m_rGameLib.PushJoyconButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON))
	{
		m_pushButton[Joycon::RIGHT_CONTROLLER] = TRUE;
	}

	if (!m_pushButton[Joycon::LEFT_CONTROLLER] ||
		!m_pushButton[Joycon::RIGHT_CONTROLLER])
	{
		return;
	}

	SceneManager& rSceneManager = SceneManager::GetInstance();
	rSceneManager.SetNextScene(SK_2P_STAGE_SELECT);
}

VOID ResultTwoPlayerScore::Render()
{
	SceneManager& rSceneManager = SceneManager::GetInstance();
	if (!rSceneManager.LatterTransitionStagingIsEnded()) return;
	
	ScoreRender();
	
	RenderCheckStar();

	if (!m_stagingIsEnd) return;

	if (m_Score[Joycon::LEFT_CONTROLLER] == m_Score[Joycon::RIGHT_CONTROLLER])
	{
		RenderDraw();

		return;
	}
	
	RenderWinner();

	RenderLoser();
}

VOID ResultTwoPlayerScore::RenderCheckStar()
{
	CustomVertex CheckStar[4];

	for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
	{
		m_checkStarData[i].m_center = { m_WND_SIZE.m_x * (0.42f + 0.5f * i),m_WND_SIZE.m_y * 0.9f, 0.0f };
		m_checkStarData[i].m_halfScale = { 50.f,50.f,0.f };
		
		m_checkStarData[i].m_deg.z += 0.25f;

		m_checkStarData[i].m_aRGB = (m_pushButton[i]) ? D3DCOLOR_ARGB(255,  152, 217,  142):
										  D3DCOLOR_ARGB(80,   255, 255, 255);

		m_rGameLib.CreateRect(CheckStar, m_checkStarData[i]);

		m_rGameLib.Render(CheckStar, m_rGameLib.GetTex(_T("CheckStar")));
	}
}

VOID ResultTwoPlayerScore::ScoreRender()
{
	for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
	{
		INT stagingScore = static_cast<INT>(m_Score[i] * (static_cast<FLOAT>(m_increaseStagingFrameCount[i]) / m_INCREASE_STAGING_FRAME_COUNT_MAX));

		INT stagingScoreDigitsNum = static_cast<INT>(log10(stagingScore) + 1);

		if (stagingScore == 0) stagingScoreDigitsNum = 1;

		TString scoreString(stagingScore, _T("%d"));

		Text scoreText(scoreString, _T("2DTextures/Fonts/a_9.png"));

		TextFormat txtFormat;
		txtFormat.m_charHalfScale = { 30, 40 };
		txtFormat.m_color1 = 0xFFF5F5F5;

		//! SCOREの文字数の半分が2.5f
		txtFormat.m_topLeft = { m_WND_SIZE.m_x * (0.25f + (0.25f * (i * 2))) - 2.0f * txtFormat.m_charHalfScale.m_x * stagingScoreDigitsNum * 0.5f , 400.0f };

		scoreText.Write(txtFormat);

		++m_increaseStagingFrameCount[i];


		if (m_increaseStagingFrameCount[i] < m_INCREASE_STAGING_FRAME_COUNT_MAX) continue;

		m_increaseStagingFrameCount[i] = m_INCREASE_STAGING_FRAME_COUNT_MAX;

		m_stagingIsEnd = TRUE;
	}
}

VOID ResultTwoPlayerScore::RenderDraw()
{
	TString drawString(_T("DRAW"));
	Text drawText(drawString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	
	for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
	{
		txtFormat.m_charHalfScale = { 30,40 };
		txtFormat.m_topLeft = { m_WND_SIZE.m_x * (0.25f + (0.25f * (i * 2))) - 2.0f * txtFormat.m_charHalfScale.m_x * 2.0f,m_WND_SIZE.m_y * 0.7f };
		txtFormat.m_color1 = 0xFFE5E5E5;
		txtFormat.m_color2 = 0xFFFAFAFA;
		txtFormat.m_gradationType = GT_HIGH_LOW;

		drawText.Write(txtFormat);
	}	
}

VOID ResultTwoPlayerScore::RenderWinner()
{
	TString winnerString(_T("WINNER"));
	Text winnerText(winnerString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;

	txtFormat.m_charHalfScale = { 30,40 };
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.75f - 2.0f * txtFormat.m_charHalfScale.m_x * 3.0f,m_WND_SIZE.m_y * 0.7f };
	txtFormat.m_color1 = 0xFFEA5532;
	txtFormat.m_color2 = 0xFFE5FFFF;
	txtFormat.m_gradationType = GT_OBLIQUE_BOTTOM_RIGHT;

	if (m_Score[Joycon::LEFT_CONTROLLER] > m_Score[Joycon::RIGHT_CONTROLLER])
	{
		txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.25f - 2.0f * txtFormat.m_charHalfScale.m_x * 3.0f,m_WND_SIZE.m_y * 0.7f };
	}
	
	winnerText.Write(txtFormat);
}

VOID ResultTwoPlayerScore::RenderLoser()
{
	TString winnerString(_T("LOSER"));
	Text winnerText(winnerString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;

	txtFormat.m_charHalfScale = { 30,40 };
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.75f - 2.0f * txtFormat.m_charHalfScale.m_x * 2.5f,m_WND_SIZE.m_y * 0.7f };
	txtFormat.m_color1 = 0xFF00A1E9;
	txtFormat.m_color2 = 0xFFFFE5FF;
	txtFormat.m_gradationType = GT_OBLIQUE_BOTTOM_RIGHT;

	if (m_Score[Joycon::LEFT_CONTROLLER] < m_Score[Joycon::RIGHT_CONTROLLER])
	{
		txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.25f - 2.0f * txtFormat.m_charHalfScale.m_x * 2.5f,m_WND_SIZE.m_y * 0.7f };
	}

	winnerText.Write(txtFormat);
}

VOID ResultTwoPlayerStage::Render()
{
	TString stageString;
	INT stageCharsNum = 0;

	GetStageStringAndCharsNum(&stageString, &stageCharsNum);

	Text stageText(stageString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 28, 40 };
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.5f - 2.0f * txtFormat.m_charHalfScale.m_x * stageCharsNum * 0.5f,  m_WND_SIZE.m_y * 0.02f };

	stageText.Write(txtFormat);

	TString levelString;
	INT levelCharsNum = 0;

	GetStageLevelAndCharsNum(&levelString, &levelCharsNum, &txtFormat);

	Text levelText(levelString, _T("2DTextures/Fonts/a_9.png"));
	txtFormat.m_charHalfScale = { 17, 25 };
	txtFormat.m_topLeft.x = m_WND_SIZE.m_x * 0.5f - 2.0f * txtFormat.m_charHalfScale.m_x * levelCharsNum * 0.5f;
	txtFormat.m_topLeft.y += 3.4f * txtFormat.m_charHalfScale.m_y;

	levelText.Write(txtFormat);
}

VOID ResultTwoPlayerStage::GetStageStringAndCharsNum(TString* pTString, INT* pCharsNum)
{
	switch (m_stageData.m_stage)
	{
	case STAGE_TAURUS:

		pTString->WriteInAll(_T("TAURUS"));
		*pCharsNum = 6;

		break;

	case STAGE_LIBRA:

		pTString->WriteInAll(_T("LIBRA"));
		*pCharsNum = 5;

		break;

	case STAGE_VIRGO:

		pTString->WriteInAll(_T("VIRGO"));
		*pCharsNum = 5;

		break;

	case STAGE_ARIES:

		pTString->WriteInAll(_T("ARIES"));
		*pCharsNum = 5;

		break;

	case STAGE_GEMINI:

		pTString->WriteInAll(_T("GEMINI"));
		*pCharsNum = 6;

		break;

	case STAGE_SCORPIUS:

		pTString->WriteInAll(_T("SCORPIUS"));
		*pCharsNum = 8;

		break;

	case STAGE_PISCORPIUS:

		pTString->WriteInAll(_T("PISCORPIUS"));
		*pCharsNum = 10;

		break;

	case STAGE_LEO:

		pTString->WriteInAll(_T("LEO"));
		*pCharsNum = 3;

		break;

	case STAGE_CAPRICORNUS:

		pTString->WriteInAll(_T("CAPRICORNUS"));
		*pCharsNum = 11;

		break;

	case STAGE_AQUARIUS:

		pTString->WriteInAll(_T("AQUARIUS"));
		*pCharsNum = 8;

		break;

	case STAGE_SAGITTARIUS:

		pTString->WriteInAll(_T("SAGITTARIUS"));
		*pCharsNum = 11;

		break;

	case STAGE_CANCER:

		pTString->WriteInAll(_T("CANCER"));
		*pCharsNum = 6;

		break;
	}
}

VOID ResultTwoPlayerStage::GetStageLevelAndCharsNum(TString* pTString, INT* pCharsNum, TextFormat* pTextFormat)
{
	switch (m_stageData.m_level)
	{
	case SLK_EASY:

		pTString->WriteInAll(_T("EASY"));
		*pCharsNum = 4;

		pTextFormat->m_color1 = 0xEE23FF23;
		pTextFormat->m_color2 = 0xEEE5FFE5;

		break;

	case SLK_NORMAL:

		pTString->WriteInAll(_T("NORMAL"));
		*pCharsNum = 6;

		pTextFormat->m_color1 = 0xEE23FFFF;
		pTextFormat->m_color2 = 0xEEE5FFFF;

		break;

	case SLK_HARD:

		pTString->WriteInAll(_T("HARD"));
		*pCharsNum = 4;

		pTextFormat->m_color1 = 0xEEFF23FF;
		pTextFormat->m_color2 = 0xEEFFE5FF;

		break;
	}

	pTextFormat->m_gradationType = GT_OBLIQUE_BOTTOM_RIGHT;
}
