﻿/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#include "ResultSceneObj.h"

#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../../../../SceneManager.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Text.h"

VOID ResultSceneBack::RenderHead()
{
	TString resultString(_T("RESULT"));

	Text resultText(resultString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 27, 41 };

	//! RESULTの文字数の半分が3
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.5f - 2.0f * txtFormat.m_charHalfScale.m_x * 3 , 13.0f };

	resultText.Write(txtFormat);
}

VOID ResultDataScore::Render()
{
	RenderCase();

	RenderHead();

	SceneManager& rSceneManager = SceneManager::GetInstance();
	if (!rSceneManager.LatterTransitionStagingIsEnded()) return;

	INT stagingScore = static_cast<INT>(m_SCORE * (static_cast<FLOAT>(m_increaseStagingFrameCount) / m_INCREASE_STAGING_FRAME_COUNT_MAX));

	INT stagingScoreDigitsNum = static_cast<INT>(log10(stagingScore) + 1);

	TString scoreString(stagingScore, _T("%d"));

	Text scoreText(scoreString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 25, 37 };

	//! SCOREの文字数の半分が2.5f
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.85f - 2.0f * txtFormat.m_charHalfScale.m_x * stagingScoreDigitsNum , 150.0f };

	scoreText.Write(txtFormat);

	++m_increaseStagingFrameCount;

	if (m_increaseStagingFrameCount < m_INCREASE_STAGING_FRAME_COUNT_MAX) return;
		
	m_increaseStagingFrameCount = m_INCREASE_STAGING_FRAME_COUNT_MAX;

	m_stagingIsEnd = TRUE;
}

VOID ResultDataScore::RenderHead()
{
	TString resultString(_T("SCORE"));

	Text resultText(resultString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 25, 37 };

	//! SCOREの文字数の半分が2.5f
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.24f - 2.0f * txtFormat.m_charHalfScale.m_x * 2.5f , 150.0f };

	resultText.Write(txtFormat);
}

VOID ResultDataStage::Render()
{
	RenderCase();

	TString stageString;
	INT stageCharsNum = 0;

	GetStageStringAndCharsNum(&stageString, &stageCharsNum);

	Text stageText(stageString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 22, 35 };
	txtFormat.m_topLeft = { 396.0f - 2.0f * txtFormat.m_charHalfScale.m_x * stageCharsNum * 0.5f, 400.0f };

	stageText.Write(txtFormat);

	TString levelString;
	INT levelCharsNum = 0;

	GetStageLevelAndCharsNum(&levelString, &levelCharsNum);

	Text levelText(levelString, _T("2DTextures/Fonts/a_9.png"));

	txtFormat.m_topLeft.x = 393.0f - 2.0f * txtFormat.m_charHalfScale.m_x * levelCharsNum * 0.5f;
	txtFormat.m_topLeft.y += 120.0f;

	levelText.Write(txtFormat);
}

VOID ResultDataStage::GetStageStringAndCharsNum(TString* pTString, INT* pCharsNum)
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

	case STAGE_BLACK_HOLE:

		pTString->WriteInAll(_T("BLACK HOLE"));
		*pCharsNum = 10;

		break;
	}
}

VOID ResultDataStage::GetStageLevelAndCharsNum(TString* pTString, INT* pCharsNum)
{
	switch (m_stageData.m_level)
	{
	case SLK_EASY:

		pTString->WriteInAll(_T("EASY"));
		*pCharsNum = 4;

		break;

	case SLK_NORMAL:

		pTString->WriteInAll(_T("NORMAL"));
		*pCharsNum = 6;

		break;

	case SLK_HARD:

		pTString->WriteInAll(_T("HARD"));
		*pCharsNum = 4;

		break;

	case SLK_EXTREME:

		pTString->WriteInAll(_T("EXTREME"));
		*pCharsNum = 7;

		break;
	}
}

VOID ResultDataClearStar::Render()
{
	RenderCase();

	RenderHead();

	const INT FRAME_ONE_STAR_TAKES = 15;

	ObjData* pStarData = nullptr;

	const INT DEFAULT_STARS_ROW_MAX = 8;
	const FLOAT STAR_HALF_SCALE = m_WND_SIZE.m_x * 0.03f;

	INT* pAlphaCount = nullptr;

	BYTE alpha = NULL;

	CustomVertex* pStar = nullptr;

	for (INT i = 0; i < m_CLEAR_STARS_MAX; ++i)
	{
		pStarData = &m_starsVec[i].m_objData;
		pStarData->m_center =
		{
			m_WND_SIZE.m_x * 0.65f + 2 * STAR_HALF_SCALE * (i % (DEFAULT_STARS_ROW_MAX / 2)),	//! 現物合わせ
			m_WND_SIZE.m_y * 0.7f + 2 * STAR_HALF_SCALE * (i / (DEFAULT_STARS_ROW_MAX / 2)),	//! 現物合わせ
			m_Z
		};

		pStarData->m_halfScale = { STAR_HALF_SCALE ,STAR_HALF_SCALE, 0.0f };

		pAlphaCount = &m_starsVec[i].m_alphaCount;

		if (i < (m_stagingCount / FRAME_ONE_STAR_TAKES) && m_CLEAR_STARS_NUM)
		{
			*pAlphaCount = (*pAlphaCount >= FRAME_ONE_STAR_TAKES) ? FRAME_ONE_STAR_TAKES : *pAlphaCount + 1;
			alpha = static_cast<INT>(255 * (static_cast<FLOAT>(*pAlphaCount) / FRAME_ONE_STAR_TAKES));

			pStarData->m_aRGB = D3DCOLOR_ARGB(alpha, 0xFF, 0xFF, 0xFF);
		}

		pStar = m_starsVec[i].m_customVertices;

		m_rGameLib.CreateRect(pStar, *pStarData);
		m_rGameLib.Render(pStar, m_rGameLib.GetTex(_T("Star")));
	}

	m_stageCountMax = (m_CLEAR_STARS_NUM <= 0) ? 5 : FRAME_ONE_STAR_TAKES * m_CLEAR_STARS_NUM;

	if (m_stagingCount) ++m_stagingCount;																//!演出の起動は他クラスで行う

	if (m_stagingCount < m_stageCountMax) return;

	m_stagingCount = m_stageCountMax;

	m_stagingIsEnd = TRUE;
}

VOID ResultDataClearStar::RenderHead()
{
	TString headString(_T("GREEN STAR"));

	Text headText(headString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 15, 22 };

	//! RESULTの文字数の半分が3
	txtFormat.m_topLeft = { m_WND_SIZE.m_x * 0.691f - 2.0f * txtFormat.m_charHalfScale.m_x * 3 , 390.0f };

	headText.Write(txtFormat);
}

VOID ResultSceneResultFont::Render()
{
	DarkenFontAround();

	ObjData resultFontData;
	resultFontData.m_center		= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.5f, 0.0f };
	resultFontData.m_halfScale	= { m_WND_SIZE.m_x * 0.5f, m_WND_SIZE.m_y * 0.14f, 0.0f };	//! 現物合わせ

	BYTE alpha = static_cast<BYTE>(255 * static_cast<FLOAT>(m_alphaCount) / m_ADDITIONAL_ALPHA_FRAME);
	resultFontData.m_aRGB = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	const FLOAT ILLUST_Y_SCALE = 512.0f;
	const FLOAT RESULT_Y_SCALE = 200.0f;

	resultFontData.m_texUV =
	{
		0.0f,
		RESULT_Y_SCALE * m_IS_FAILED / ILLUST_Y_SCALE,
		1.0f,
		RESULT_Y_SCALE * (m_IS_FAILED + 1) / ILLUST_Y_SCALE
	};

	CustomVertex resultFont[4];
	m_rGameLib.CreateRect(resultFont, resultFontData);

	m_rGameLib.Render(resultFont, m_rGameLib.GetTex(_T("ResultFont")));

	m_alphaCount = (m_alphaCount >= m_ADDITIONAL_ALPHA_FRAME) ? m_ADDITIONAL_ALPHA_FRAME : ++m_alphaCount;

	if (m_alphaCount != 1) return;

	if (m_IS_FAILED)
	{
		m_rGameLib.OneShotStartSound(_T("Failed"));

		return;
	}

	m_rGameLib.OneShotStartSound(_T("Clear"));
}

VOID ResultSceneContinue::Render()
{
	RenderFrame();

	RenderTexts();

	RenderTarget();
}

VOID ResultSceneResult::Update()
{
	m_pResultSceneResultData->Update();
	m_pResultSceneResultFont->Update();

	if (m_rGameLib.KeyboardAnyKeyIsPressed() &&
		m_pResultSceneResultData->StagingIsEnd() &&
		m_stagingGapFrameCount != m_STAGING_GAP_FRAME)
	{
		m_stagingGapFrameCount = m_STAGING_GAP_FRAME;

		return;
	}

	if (m_rGameLib.KeyboardAnyKeyIsPressed() &&
		!m_shouldShowContinue &&
		m_stagingGapFrameCount == m_STAGING_GAP_FRAME)
	{
		m_shouldShowContinue = TRUE;

		return;
	}

	if (m_shouldShowContinue) m_pResultSceneContinue->Update();
}
